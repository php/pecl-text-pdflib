/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2004 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.0 of the PHP license,       |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_0.txt.                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Uwe Steinmann <Uwe.Steinmann@fernuni-hagen.de>              |
   |          Rainer Schaaf <rjs@pdflib.com>                              |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

/* Copyright (C) 1997-1999 Thomas Merz. 2000-2013 PDFlib GmbH */
/* Note that there is no code from the pdflib package in this file */

/*
    As the optionlist may contain filenames on various places the
    VIRTUAL_DIR support and the CHECK_OPEN_BASEDIR checks implemented
    in the wrapper will not work reliable too. So VIRTUAL_DIR support
    and the CHECK_OPEN_BASEDIR checking is disabled here too, as it would
    only work for some of the files used with PDFlib.

    The main changes:
    - adds an Object Oriented API to PDFlib
    - uses PHP exceptions
    - only official PDFlib APIs are included (plus pdf_open_memory_image)
    - disables VIRTUAL_DIR support (use SerachPath instead)
    - disables CHECK_OPEN_BASEDIR checks
    - changed old API's with varargs to only accept all args
*/

/* Bootstrap of PDFlib Feature setup */

#if _MSC_VER >= 1310    /* VS .NET 2003 and later */
#pragma warning(disable: 4995)  /* ignore deprecated warnings */
#pragma warning(disable: 4101)  /* ignore unused variables */
#endif

/* Extension version */
#include "php_pdflib.h"

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif /* HAVE_CONFIG_H */

#include "php.h"
#include "php_ini.h"
#include "php_globals.h"
#include "php_streams.h"
#include "zend_list.h"
#include "ext/standard/head.h"
#include "ext/standard/info.h"
#include "ext/standard/file.h"
#include "Zend/zend_exceptions.h"

#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif /* HAVE_UNISTD_H */

#ifdef PHP_WIN32
# include <io.h>
# include <fcntl.h>
#endif /* PHP_WIN32 */


#if HAVE_PDFLIB
#include "pdflib.h"

#if PDFLIB_MAJORVERSION <= 6
#error PDFlib 6 and earlier are no longer supported (use pdflib-2.x.x pecl package instead)
#endif /* PDFLIB_MAJORVERSION <= 6 */


/* With PDFlib 7 we start a new wrapper source as most of the code will be
 * created automatically.
 */

#include "php_pdf.h"

#undef VIRTUAL_DIR
#undef PDFLIB_CHECK_OPEN_BASEDIR

#ifndef safe_emalloc        /* to be compatible with older PHP versions */
#define safe_emalloc(a,b,c) emalloc((a) * (b))
#endif

/* {{{ pdf_functions[]
 */

static int le_pdf;

zend_function_entry pdf_functions[] = {
#define _WRAP_FUNCTION_ENTRY
#include "php_wrapped.c"
#undef _WRAP_FUNCTION_ENTRY
    PHP_FE(pdf_new, NULL)
    PHP_FE(pdf_delete, NULL)
    PHP_FE(pdf_get_pdi_parameter, NULL)
    PHP_FE(pdf_open_image, NULL)
    PHP_FE(pdf_open_pdi, NULL)
    PHP_FE(pdf_setpolydash, NULL)
    PHP_FE(pdf_show_boxed, NULL)
    {NULL, NULL, NULL}
};
/* }}} */

/* {{{ pdflib_funcs[] OO-Mapping
 */

zend_class_entry *pdflib_class;
zend_class_entry *pdflib_exception_class;


/* allow to be compiled with various PHP Versions allthough
   the API of the PHP_ME_MAPPING() Macro changed */
#define PDF_ME_MAPPING(a, b, c) PHP_ME_MAPPING(a, b, c, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)

static zend_object_handlers pdflib_handlers;

typedef struct _pdflib_object {
#if PHP_MAJOR_VERSION >= 7
    PDF *p;
    zend_object zobj;
#else
    zend_object zobj;
    PDF *p;
#endif
} pdflib_object;

zend_function_entry pdflib_funcs[] = {
#define _WRAP_FUNCTION_ENTRY2
#include "php_wrapped.c"
#undef _WRAP_FUNCTION_ENTRY2
    /* if we make the class PDFlib extendable, the constructor should
     * not become final */
    PHP_ME_MAPPING(__construct, pdf_new, NULL, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
    PDF_ME_MAPPING(delete, pdf_delete, NULL)
    PDF_ME_MAPPING(get_pdi_parameter, pdf_get_pdi_parameter, NULL)
    PDF_ME_MAPPING(open_pdi, pdf_open_pdi, NULL)
    PDF_ME_MAPPING(open_image, pdf_open_image, NULL)
    PDF_ME_MAPPING(setpolydash, pdf_setpolydash, NULL)
    PDF_ME_MAPPING(show_boxed, pdf_show_boxed, NULL)
#if PHP_MAJOR_VERSION >= 7
    PDF_ME_MAPPING(__destruct, _free_pdf_doc, NULL)
#endif
    {NULL, NULL, NULL}
};

/* }}} */

/* {{{ pdf_module_entry
 */
zend_module_entry pdf_module_entry = {
    STANDARD_MODULE_HEADER,
    "PDFlib",
    pdf_functions,
    PHP_MINIT(pdf),
    PHP_MSHUTDOWN(pdf),
    NULL,
    NULL,
    PHP_MINFO(pdf),
    PHP_PDFLIB_VERSION,
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#if defined(COMPILE_DL_PDF) || defined(COMPILE_DL_PDFLIB)
ZEND_GET_MODULE(pdf)
#endif /* COMPILE_DL_PDF */

/* exception handling */
/* {{{ pdf_try/pdf_catch _pdfexception */

PHP_METHOD(PDFlibException, get_apiname);
PHP_METHOD(PDFlibException, get_errmsg);
PHP_METHOD(PDFlibException, get_errnum);

static zend_function_entry PDFlibException_functions[] = {
    PHP_ME(PDFlibException, get_apiname, NULL, 0)
    PHP_ME(PDFlibException, get_errmsg, NULL, 0)
    PHP_ME(PDFlibException, get_errnum, NULL, 0)
    {NULL, NULL, NULL}
};

#define pdf_try     PDF_TRY(pdf)

#define pdf_catch   PDF_CATCH(pdf) { \
    _pdf_exception(PDF_get_errnum(pdf), PDF_get_apiname(pdf), \
        PDF_get_errmsg(pdf) TSRMLS_CC); \
    RETURN_FALSE; \
    }

/* use our own version of WRONG_PARAM_COUNT and ZEND_FETCH_RESOURCE
 * to change error handling to exceptions in case of problems. */

#if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION >= 3) || PHP_MAJOR_VERSION > 5
/* PHP-5.3 makes php_std_error_handling() and php_set_error_handling()
 * deprecated, so we have to change it to use the new zend functions now
 */
#define DEFINE_ERROR_HANDLER	zend_error_handling error_handling;
#define SET_ERROR_HANDLING(type, handler) \
    zend_replace_error_handling(type, handler, &error_handling TSRMLS_CC)
#define RESTORE_ERROR_HANDLING() \
    zend_restore_error_handling(&error_handling TSRMLS_CC)
#else /* !((PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION >= 3) || PHP_MAJOR_VERSION > 5) */
#define DEFINE_ERROR_HANDLER
#define SET_ERROR_HANDLING(type, handler) \
    php_set_error_handling(type, handler  TSRMLS_CC)
#define RESTORE_ERROR_HANDLING()  php_std_error_handling()
#endif /* (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION >= 3) || PHP_MAJOR_VERSION > 5 */


#undef WRONG_PARAM_COUNT
#define WRONG_PARAM_COUNT \
{\
    DEFINE_ERROR_HANDLER \
    SET_ERROR_HANDLING(EH_NORMAL, pdflib_exception_class); \
    zend_wrong_param_count(TSRMLS_C); \
    RESTORE_ERROR_HANDLING(); \
    return;\
}

#undef WRONG_PARAM_COUNT_WITH_RETVAL
#define WRONG_PARAM_COUNT_WITH_RETVAL(ret) \
{\
    DEFINE_ERROR_HANDLER \
    SET_ERROR_HANDLING(EH_NORMAL, pdflib_exception_class); \
    zend_wrong_param_count(TSRMLS_C); \
    RESTORE_ERROR_HANDLING(); \
    return ret;\
}

#undef ZEND_FETCH_RESOURCE
#if PHP_MAJOR_VERSION >= 7
#define ZEND_FETCH_RESOURCE(rsrc, rsrc_type, passed_id, \
                default_id, resource_type_name, resource_type)  \
{\
    DEFINE_ERROR_HANDLER \
    SET_ERROR_HANDLING(EH_NORMAL, pdflib_exception_class); \
    if ((rsrc = (rsrc_type) zend_fetch_resource(Z_RES_P(passed_id), resource_type_name, resource_type)) == NULL) { \
        RESTORE_ERROR_HANDLING(); \
        RETURN_FALSE; \
    } \
    RESTORE_ERROR_HANDLING(); \
}

#define P_FROM_OBJECT(pdf, object) \
    { \
	DEFINE_ERROR_HANDLER \
        zend_object *zobj = Z_OBJ_P(object); \
        pdflib_object *pobj = (pdflib_object *) \
          ((char *)zobj - offsetof(pdflib_object, zobj)); \
        pdf = pobj->p; \
        if (!pdf) { \
            php_error_docref(NULL TSRMLS_CC, E_WARNING, \
                "No PDFlib object available"); \
            RESTORE_ERROR_HANDLING(); \
            RETURN_NULL(); \
        } \
    }
#else /* PHP_MAJOR_VERSION >= 7 */
#define ZEND_FETCH_RESOURCE(rsrc, rsrc_type, passed_id, \
                default_id, resource_type_name, resource_type)  \
{\
    DEFINE_ERROR_HANDLER \
    SET_ERROR_HANDLING(EH_NORMAL, pdflib_exception_class); \
    rsrc = (rsrc_type) zend_fetch_resource(passed_id TSRMLS_CC, \
            default_id, resource_type_name, NULL, 1, resource_type);    \
    RESTORE_ERROR_HANDLING(); \
    ZEND_VERIFY_RESOURCE(rsrc); \
}

#define P_FROM_OBJECT(pdf, object) \
    { \
	DEFINE_ERROR_HANDLER \
        pdflib_object *obj = (pdflib_object*) \
            zend_object_store_get_object(object TSRMLS_CC); \
        pdf = obj->p; \
        if (!pdf) { \
            php_error_docref(NULL TSRMLS_CC, E_WARNING, \
                "No PDFlib object available"); \
            RESTORE_ERROR_HANDLING(); \
            RETURN_NULL(); \
        } \
    }
#endif /* PHP_MAJOR_VERSION >= 7 */

zend_class_entry *default_exception_ce;

static void _pdf_exception(int errnum, const char *apiname,
    const char *errmsg TSRMLS_DC)
{
    char msgbuf[2048];

    snprintf(msgbuf, sizeof(msgbuf), "[%d] %s: %s", errnum, apiname, errmsg);

    {
#if PHP_MAJOR_VERSION >= 7
        zval ex;
        zend_class_entry *def_ex;
        def_ex = zend_exception_get_default(TSRMLS_C);
        object_init_ex(&ex, pdflib_exception_class);

        if (apiname) {
           zend_update_property_string(def_ex, &ex, "apiname",
                            sizeof("apiname")-1, (char *)apiname TSRMLS_CC);
        }
        if (errmsg) {
           zend_update_property_string(def_ex, &ex, "message",
                            sizeof("message")-1, (char *)errmsg TSRMLS_CC);
        }
        zend_update_property_long(def_ex, &ex, "code", sizeof("code")-1,
            errnum TSRMLS_CC);
        zend_throw_exception_object(&ex TSRMLS_CC);
#else /* PHP_MAJOR_VERSION >= 7 */
        zval *ex;
        zend_class_entry *def_ex;
        def_ex = zend_exception_get_default(TSRMLS_C);
        MAKE_STD_ZVAL(ex);
        object_init_ex(ex, pdflib_exception_class);

        if (apiname) {
           zend_update_property_string(def_ex, ex, "apiname",
                            sizeof("apiname")-1, (char *)apiname TSRMLS_CC);
        }
        if (errmsg) {
           zend_update_property_string(def_ex, ex, "message",
                            sizeof("message")-1, (char *)errmsg TSRMLS_CC);
        }
        zend_update_property_long(def_ex, ex, "code", sizeof("code")-1,
            errnum TSRMLS_CC);
        zend_throw_exception_object(ex TSRMLS_CC);
#endif /* PHP_MAJOR_VERSION >= 7 */
    }
}
/* }}} */

/* PHP/PDFlib internal functions */
/* {{{ _free_pdf_doc
 */
#if PHP_MAJOR_VERSION >= 7
PHP_FUNCTION(_free_pdf_doc)
{
    PDF *pdf;
    zval *object = getThis();

    if (object) {
        P_FROM_OBJECT(pdf, object);
        PDF_delete(pdf);
    }
}
static void _free_pdf_doc(zend_resource *rsrc);
static void _free_pdf_doc(zend_resource *rsrc)
{
    PDF *pdf = (PDF *)rsrc->ptr;
    PDF_delete(pdf);
}
#else /* PHP_MAJOR_VERSION >= 7 */
static void _free_pdf_doc(zend_rsrc_list_entry *rsrc TSRMLS_DC);
static void _free_pdf_doc(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
    PDF *pdf = (PDF *)rsrc->ptr;
    PDF_delete(pdf);
}
#endif /* PHP_MAJOR_VERSION >= 7 */
/* }}} */

/* {{{ pdf_emalloc
 */
static void *pdf_emalloc(PDF *p, size_t size, const char *caller)
{
    return(emalloc(size));
}
/* }}} */

/* {{{ pdf_realloc
 */
static void *pdf_realloc(PDF *p, void *mem, size_t size, const char *caller)
{
    return(erealloc(mem, size));
}
/* }}} */

/* {{{ pdf_efree
 */
static void pdf_efree(PDF *p, void *mem)
{
    efree(mem);
}
/* }}} */

/* {{{ pdflib_object_dtor */
static void
pdflib_object_dtor(void *object TSRMLS_DC)
{
    pdflib_object *intern = (pdflib_object *)object;

    zend_object_std_dtor(&intern->zobj TSRMLS_CC);

    if (intern->p) {
        PDF_delete(intern->p);
        intern->p = (PDF *)0;
    }
    efree(object);
}
/* }}} */

/* {{{ pdflib_object_new
 */
#if PHP_MAJOR_VERSION >= 7
static zend_object*
pdflib_object_new(zend_class_entry *class_type TSRMLS_DC)
{
#else /* PHP_MAJOR_VERSION >= 7 */
static zend_object_value
pdflib_object_new(zend_class_entry *class_type TSRMLS_DC)
{
    zend_object_value retval;
#endif /* PHP_MAJOR_VERSION >= 7 */
    pdflib_object *object = (pdflib_object*)emalloc(sizeof(pdflib_object));
    memset(object, 0, sizeof(pdflib_object));
    object->zobj.ce = class_type;
    zend_object_std_init(&object->zobj, class_type TSRMLS_CC);

#if PHP_VERSION_ID < 50399
    {
    zval *tmp;
    zend_hash_copy(object->zobj.properties,
            &class_type->default_properties,
            (copy_ctor_func_t) zval_add_ref,
            (void *) &tmp, sizeof(zval *));
    }
#else /* PHP_VERSION_ID < 50399 */
    object_properties_init(&(object->zobj), class_type);
#endif /* PHP_VERSION_ID < 50399 */

#if PHP_MAJOR_VERSION >= 7
    object->zobj.handlers = &pdflib_handlers;
    return &object->zobj;
#else /* PHP_MAJOR_VERSION >= 7 */
    retval.handlers = &pdflib_handlers;
    retval.handle = zend_objects_store_put(object,  NULL,
            (zend_objects_free_object_storage_t)pdflib_object_dtor,
            NULL TSRMLS_CC);
    return retval;
#endif /* PHP_MAJOR_VERSION >= 7 */
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(pdf)
{
    char tmp[32];

    snprintf(tmp, 31, "%d.%02d", PDF_get_majorversion(),
		PDF_get_minorversion() );
    tmp[31]=0;

    php_info_print_table_start();
    php_info_print_table_header(2, "PDFlib Support", "enabled" );
    php_info_print_table_row(2, "PDFlib GmbH Version", 
#if PDFLIB_MAJORVERSION >= 8
        PDFLIB_LONG_VERSIONSTRING
#else
        PDFLIB_VERSIONSTRING
#endif
	);
    php_info_print_table_row(2, "PECL Version", PHP_PDFLIB_VERSION);
    php_info_print_table_row(2, "Revision", "$Revision$" );
    php_info_print_table_end();

}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(pdf)
{
    if ((PDF_get_majorversion() != PDFLIB_MAJORVERSION) ||
            (PDF_get_minorversion() != PDFLIB_MINORVERSION)) {
        php_error_docref(NULL TSRMLS_CC, E_ERROR,
            "PDFlib error: Version mismatch in wrapper code");
    }
#if PHP_MAJOR_VERSION >= 7
    le_pdf = zend_register_list_destructors_ex(_free_pdf_doc, NULL,
		"pdf object", module_number);
#else /* PHP_MAJOR_VERSION >= 7 */
    le_pdf = zend_register_list_destructors_ex(_free_pdf_doc, NULL,
		"pdf object", module_number);
#endif /* PHP_MAJOR_VERSION >= 7 */

    /* this does something like setlocale("C", ...) in PDFlib 3.x */
    PDF_boot();

    {
    /* add PDFlibException class */
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "PDFlibException", PDFlibException_functions);
#if PHP_MAJOR_VERSION >= 7
    pdflib_exception_class = zend_register_internal_class_ex(&ce,
            zend_exception_get_default(TSRMLS_C) TSRMLS_CC);
#else /* PHP_MAJOR_VERSION >= 7 */
    pdflib_exception_class = zend_register_internal_class_ex(&ce,
            zend_exception_get_default(TSRMLS_C), NULL TSRMLS_CC);
#endif /* PHP_MAJOR_VERSION >= 7 */

    zend_declare_property_string(pdflib_exception_class, "apiname",
            sizeof("apiname")-1, "", ZEND_ACC_PROTECTED TSRMLS_CC);
    pdflib_exception_class->constructor->common.fn_flags
            |= ZEND_ACC_PROTECTED;

    /* add PDFlib class */
    INIT_CLASS_ENTRY(ce, "PDFlib", pdflib_funcs);
    ce.create_object = pdflib_object_new;
    pdflib_class = zend_register_internal_class(&ce TSRMLS_CC);
    memcpy(&pdflib_handlers,
            zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    pdflib_handlers.clone_obj = NULL;
    pdflib_class->constructor->common.fn_flags |= ZEND_ACC_PROTECTED;
    }

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(pdf)
{
    PDF_shutdown();
    return SUCCESS;
}
/* }}} */


/* The PDFlibException Methods */
PHP_METHOD(PDFlibException, get_apiname)
{
#if PHP_MAJOR_VERSION >= 7
    zval rv, *this_ptr = getThis();
    zend_string *apiname;

    apiname = zval_get_string(zend_read_property(pdflib_exception_class,
                        this_ptr, "apiname", sizeof("apiname")-1, 1, &rv));
    RETURN_STR(apiname)
#else /* PHP_MAJOR_VERSION >= 7 */
    zval *apiname;
    char *retbuf;

    apiname = zend_read_property(pdflib_exception_class, this_ptr, "apiname",
                sizeof("apiname")-1, 1 TSRMLS_CC);
    retbuf = Z_STRVAL_P(apiname);

    RETURN_STRING(retbuf ? (char *)retbuf : "", 1);
#endif /* PHP_MAJOR_VERSION >= 7 */
}

PHP_METHOD(PDFlibException, get_errmsg)
{
#if PHP_MAJOR_VERSION >= 7
    zval rv, *this_ptr = getThis();
    zend_string *message;

    message = zval_get_string(zend_read_property(pdflib_exception_class, this_ptr, "message",
                sizeof("message")-1, 1, &rv));
    RETURN_STR(message)
#else /* PHP_MAJOR_VERSION >= 7 */
    zval *message;
    char *retbuf;

    message = zend_read_property(pdflib_exception_class, this_ptr, "message",
                sizeof("message")-1, 1 TSRMLS_CC);
    retbuf = Z_STRVAL_P(message);

    RETURN_STRING(retbuf ? (char *)retbuf : "", 1);
#endif /* PHP_MAJOR_VERSION >= 7 */
}

PHP_METHOD(PDFlibException, get_errnum)
{
#if PHP_MAJOR_VERSION >= 7
    zval *code, rv;
    zval *this_ptr = getThis();
    long retval;

    code = zend_read_property(pdflib_exception_class, this_ptr, "code",
                sizeof("code")-1, 1, &rv);
    retval = Z_LVAL_P(code);

    RETURN_LONG(retval);
#else /* PHP_MAJOR_VERSION >= 7 */
    zval *code;
    long retval;

    code = zend_read_property(pdflib_exception_class, this_ptr, "code",
                sizeof("code")-1, 1 TSRMLS_CC);
    retval = Z_LVAL_P(code);

    RETURN_LONG(retval);
#endif /* PHP_MAJOR_VERSION >= 7 */
}

/* The PDFlib API */

#define _WRAP_CODE
#include "php_wrapped.c"
#undef _WRAP_CODE

/* {{{ proto string PDF_get_pdi_parameter(
resource p, string key, int doc, int page, int reserved)
 * Deprecated, use PDF_pcos_get_string(). */
PHP_FUNCTION(pdf_get_pdi_parameter)
{
    PDF *pdf;
#if PHP_MAJOR_VERSION >= 7
    zend_string * z_key;
    const char * key;
    int key_len;
#else /* PHP_MAJOR_VERSION >= 7 */
    const char * key;
    int key_len;
#endif /* PHP_MAJOR_VERSION >= 7 */
    long doc;
    long page;
    long reserved;
    int len;
    const char *_result = NULL;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "Slll",&z_key, &doc, &page, &reserved)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        key = ZSTR_VAL(z_key);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "slll",&key, &key_len,&doc,&page,&reserved)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#endif /* PHP_MAJOR_VERSION >= 7 */
        P_FROM_OBJECT(pdf, object);
    } else {
        SET_ERROR_HANDLING(EH_NORMAL, pdflib_exception_class);
        {
            zval *p;
#if PHP_MAJOR_VERSION >= 7
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zSlll", &p,&z_key, &doc,&page,&reserved)) {
                RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
            key = ZSTR_VAL(z_key);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rslll", &p,&key, &key_len,&doc,&page,&reserved)) {
                RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

#if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION >= 3) || PHP_MAJOR_VERSION > 5
    php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_pcos_get_string().");
#endif /* (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION >= 3) || PHP_MAJOR_VERSION > 5 */

    pdf_try {
	_result =  (const char *)PDF_get_pdi_parameter(pdf, key, doc, page, reserved, &len);
    } pdf_catch;

#if PHP_MAJOR_VERSION >= 7
    {
        zend_string *z_result;
        if (_result) {
            z_result = zend_string_init(_result, len, 0);
        } else {
            z_result = zend_string_init("", 1, 0);
        }
        RETURN_STR(z_result);
    }
#else /* PHP_MAJOR_VERSION >= 7 */
    RETURN_STRINGL(_result ? (char *)_result : "", len, 1);
#endif /* PHP_MAJOR_VERSION >= 7 */
} /* }}} */

/* {{{ proto int pdf_open_pdi(resource p, string filename, string optlist,
 * int reserved);
 * Open a disk-based or virtual PDF document and prepare it for later use. */
PHP_FUNCTION(pdf_open_pdi)
{
    PDF *pdf;
#if PHP_MAJOR_VERSION >= 7
    zend_string *z_filename, *z_optlist;
    char *filename, *optlist;
#else /* PHP_MAJOR_VERSION >= 7 */
    char *filename, *optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    int flen, olen;
    long len;
    char *vfilename;
    long retval = 0;

    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
                        "SSl", &z_filename, &z_optlist, &len)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        filename = ZSTR_VAL(z_filename);
        optlist =  ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
                        "ssl", &filename, &flen, &optlist, &olen, &len)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#endif /* PHP_MAJOR_VERSION >= 7 */
        P_FROM_OBJECT(pdf, object);
    } else {
        SET_ERROR_HANDLING(EH_NORMAL, pdflib_exception_class);
        {
            zval *p;
#if PHP_MAJOR_VERSION >= 7
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
                        "zSSl", &p, &z_filename, &z_optlist, &len)) {
                RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
            filename = ZSTR_VAL(z_filename);
            optlist =  ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
                        "rssl", &p, &filename, &flen, &optlist, &olen, &len)) {
                RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

#ifdef VIRTUAL_DIR
    virtual_filepath(filename, &vfilename TSRMLS_CC);
#else /* !VIRTUAL_DIR */
    vfilename = filename;
#endif /* VIRTUAL_DIR */

#ifdef PDFLIB_CHECK_OPEN_BASEDIR
    if (vfilname && *vfilename) {
	if (php_check_open_basedir(vfilename TSRMLS_CC) || (PG(safe_mode) &&
		!php_checkuid(vfilename, "rb+", CHECKUID_CHECK_MODE_PARAM))) {
	    RETURN_FALSE;
	}
    }
#endif /* PDFLIB_CHECK_OPEN_BASEDIR */

#if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION >= 3) || PHP_MAJOR_VERSION > 5
    php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_open_pdi_document().");
#endif /* (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION >= 3) || PHP_MAJOR_VERSION > 5 */

    pdf_try {
        retval = PDF_open_pdi(pdf, vfilename, optlist, (int)len);
    } pdf_catch;

    RETURN_LONG(retval); /* offset handled in PDFlib Kernel */
}
/* }}} */

/* {{{ proto bool pdf_delete(int p)
 * Delete a PDFlib object and free all internal resources. */
PHP_FUNCTION(pdf_delete)
{
    RETURN_TRUE; /* This is done in the destructor */
}
/* }}} */

/* {{{ proto resource pdf_new()
 * Create a new PDFlib object with default settings. */
PHP_FUNCTION(pdf_new)
{
    PDF *pdf;
    zval *object = getThis();
    DEFINE_ERROR_HANDLER
    pdflib_object *intern;

    pdf = PDF_new2(NULL, pdf_emalloc, pdf_realloc, pdf_efree, NULL);

    if (pdf != NULL) {
        pdf_try {
            /* Trigger special handling of PDFlib-handles for PHP */
            PDF_set_parameter(pdf, "hastobepos", "true");
#if PHP_MAJOR_VERSION >= 7
            PDF_set_parameter(pdf, "binding", "PHP7");
#else /* PHP_MAJOR_VERSION >= 7 */
            PDF_set_parameter(pdf, "binding", "PHP5");
#endif /* PHP_MAJOR_VERSION >= 7 */
        } pdf_catch;
    } else {
        _pdf_exception(99, "PDF_new", "PDF_new: internal error" TSRMLS_CC);
    }

    if (object) {
        pdf_try {
            PDF_set_parameter(pdf, "objorient", "true");
        } pdf_catch;
#if PHP_MAJOR_VERSION >= 7
        zend_object *zobj = Z_OBJ_P(getThis());
        pdflib_object *pobj = (pdflib_object *)
          ((char *)zobj - offsetof(pdflib_object, zobj));
        pobj->p = pdf;
#else /* PHP_MAJOR_VERSION >= 7 */
        intern =(pdflib_object *)zend_object_store_get_object(object TSRMLS_CC);
        intern->p = pdf;
#endif /* PHP_MAJOR_VERSION >= 7 */
    } else {
#if PHP_MAJOR_VERSION >= 7
        zend_resource *ret = zend_register_resource(pdf, le_pdf);
        RETURN_RES(ret);
#else /* PHP_MAJOR_VERSION >= 7 */
        ZEND_REGISTER_RESOURCE(return_value, pdf, le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
    }
}
/* }}} */

/* {{{ proto int pdf_open_image(resource p, string imagetype, string source,
 * string data, int length, int width, int height, int components, int bpc,
 * string params)
 * Deprecated, use PDF_load_image() with virtual files. */
PHP_FUNCTION(pdf_open_image)
{
    PDF *pdf;
#if PHP_MAJOR_VERSION >= 7
    char *imagetype, *source, *data, *params;
    zend_string *z_imagetype, *z_source, *z_data, *z_params;
#else /* PHP_MAJOR_VERSION >= 7 */
    char *imagetype, *source, *data, *params;
    int ilen, dlen, slen, plen;
#endif /* PHP_MAJOR_VERSION >= 7 */
    long length, width, height, components, bpc;
    long retval = 0;

    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
                        "SSSlllllS", &z_imagetype, &z_source,
                        z_data, &length, &width, &height, &components,
                        &bpc, &z_params)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        imagetype = ZSTR_VAL(z_imagetype);
        source = ZSTR_VAL(z_source);
        data = ZSTR_VAL(z_data);
        params = ZSTR_VAL(z_params);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
                        "sssllllls", &imagetype, &ilen, &source, &slen,
                        &data, &dlen, &length, &width, &height, &components,
                        &bpc, &params, &plen)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#endif /* PHP_MAJOR_VERSION >= 7 */
        P_FROM_OBJECT(pdf, object);
    } else {
        SET_ERROR_HANDLING(EH_NORMAL, pdflib_exception_class);
        {
            zval *p;
#if PHP_MAJOR_VERSION >= 7
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
                        "zSSSlllllS", &p, &z_imagetype, &z_source,
                        &z_data, &length, &width, &height, &components,
                        &bpc, &z_params)) {
                RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
            imagetype = ZSTR_VAL(z_imagetype);
            source = ZSTR_VAL(z_source);
            data = ZSTR_VAL(z_data);
            params = ZSTR_VAL(z_params);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
                        "rsssllllls", &p, &imagetype, &ilen, &source, &slen,
                        &data, &dlen, &length, &width, &height, &components,
                        &bpc, &params, &plen)) {
                RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

#if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION >= 3) || PHP_MAJOR_VERSION > 5
    php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_load_image() with virtual files.");
#endif /* (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION >= 3) || PHP_MAJOR_VERSION > 5 */

    pdf_try {
        retval = PDF_open_image(pdf, imagetype, source, data, length,
            (int)width, (int)height, (int)components, (int)bpc, params);
    } pdf_catch;

    RETURN_LONG(retval); /* offset handled in PDFlib Kernel */
}
/* }}} */

/* no longer supported */
/* {{{ proto bool pdf_setpolydash(resource p, double darray)
 * Deprecated, use PDF_setdashpattern(). */
PHP_FUNCTION(pdf_setpolydash)
{

    _pdf_exception(99, "PDF_set_polydash",
	"function is no longer supported use PDF_setdashpattern()" TSRMLS_CC);

    RETURN_TRUE;
}

/* {{{ proto int PDF_show_boxed(resource p, string text, double left, double top, double width, double height, string hmode, string feature)
 * Deprecated, use PDF_fit_textline() or PDF_fit_textflow(). */
PHP_FUNCTION(pdf_show_boxed)
{
    PDF *pdf;
#if PHP_MAJOR_VERSION >= 7
    const char * text;
    const char * hmode;
    const char * feature;
    zend_string * z_text;
    zend_string * z_hmode;
    zend_string * z_feature;
#else /* PHP_MAJOR_VERSION >= 7 */
    const char * text;
    const char * hmode;
    const char * feature;
    int text_len;
    int hmode_len;
    int feature_len;
#endif /* PHP_MAJOR_VERSION >= 7 */
    double left;
    double top;
    double width;
    double height;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
                        "SddddSS", &z_text, &left, &top, &width, &height, &z_hmode, &z_feature)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        text = ZSTR_VAL(z_text);
        hmode = ZSTR_VAL(z_hmode);
        feature = ZSTR_VAL(z_feature);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
                        "sddddss", &text, &text_len, &left, &top, &width, &height, &hmode, &hmode_len, &feature, &feature_len)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#endif /* PHP_MAJOR_VERSION >= 7 */
        P_FROM_OBJECT(pdf, object);
    } else {
        SET_ERROR_HANDLING(EH_NORMAL, pdflib_exception_class);
        {
            zval *p;
#if PHP_MAJOR_VERSION >= 7
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
                        "zSddddSS", &p, &z_text, &left, &top, &width, &height, &z_hmode, &z_feature)) {
                RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
            text = ZSTR_VAL(z_text);
            hmode = ZSTR_VAL(z_hmode);
            feature = ZSTR_VAL(z_feature);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
                        "rsddddss", &p, &text, &text_len, &left, &top, &width, &height, &hmode, &hmode_len, &feature, &feature_len)) {
                RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

#if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION >= 3) || PHP_MAJOR_VERSION > 5
    php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_fit_textline() or PDF_fit_textflow().");
#endif /* (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION >= 3) || PHP_MAJOR_VERSION > 5 */

    pdf_try {
	_result = PDF_show_boxed(pdf, text, left, top, width, height, hmode, feature);
    } pdf_catch;

    
    RETURN_LONG(_result);
} /* }}} */
    
/*
 * Local variables:
 * tab-width: 8
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=8
 */

#endif /* HAVE_PDFLIB */
