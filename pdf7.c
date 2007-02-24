/* $Id$ */

/* With PDFlib 7 we start a new wrapper source as most of the code will be
 * created automatically.
 */

#include "php_pdf7.h"

#undef VIRTUAL_DIR
#undef PDFLIB_CHECK_OPEN_BASEDIR

#ifndef safe_emalloc		/* to be compatible with older PHP versions */
#define safe_emalloc(a,b,c)	emalloc((a) * (b))
#endif

/* {{{ pdf_functions[]
 */

static int le_pdf;

function_entry pdf_functions[] = {
#define _WRAP_FUNCTION_ENTRY
#include "php_wrapped.c"
#undef _WRAP_FUNCTION_ENTRY
	PHP_FE(pdf_utf16_to_utf8, NULL)
	PHP_FE(pdf_utf8_to_utf16, NULL)
	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ pdflib_funcs[] OO-Mapping
 */

zend_class_entry *pdflib_class;
zend_class_entry *pdflib_exception_class;

#if PHP_MAJOR_VERSION >= 5

/* allow to be compiled with various PHP Versions allthough
   the API of the PHP_ME_MAPPING() Macro changed */
#if PHP_MAJOR_VERSION >= 5 && PHP_MINOR_VERSION >= 2
	#define PDF_ME_MAPPING(a, b, c) PHP_ME_MAPPING(a, b, c, 0)
#else /* PHP_MAJOR_VERSION >= 5 && PHP_MINOR_VERSION >= 2 */
	#define PDF_ME_MAPPING(a, b, c) PHP_ME_MAPPING(a, b, c)
#endif /* PHP_MAJOR_VERSION >= 5 && PHP_MINOR_VERSION >= 2 */

static zend_object_handlers pdflib_handlers;

typedef struct _pdflib_object {
	zend_object	std;
	PDF *p;
} pdflib_object;

function_entry pdflib_funcs[] = {
#define _WRAP_FUNCTION_ENTRY2
#include "php_wrapped.c"
#undef _WRAP_FUNCTION_ENTRY2
	PDF_ME_MAPPING(open_pdi, pdf_open_pdi, NULL)
	PDF_ME_MAPPING(__construct, pdf_new, NULL)
	PDF_ME_MAPPING(delete, pdf_delete, NULL)
	PDF_ME_MAPPING(utf16_to_utf8, pdf_utf16_to_utf8, NULL)
	PDF_ME_MAPPING(utf8_to_utf16, pdf_utf8_to_utf16, NULL)
	{NULL, NULL, NULL}
};

#endif /* PHP_MAJOR_VERSION >= 5 */

/* }}} */

/* {{{ pdf_module_entry
 */
zend_module_entry pdf_module_entry = {
    STANDARD_MODULE_HEADER,
	"pdf",
	pdf_functions,
	PHP_MINIT(pdf),
	PHP_MSHUTDOWN(pdf),
	NULL,
	NULL,
	PHP_MINFO(pdf),
	PDFLIB_PECL_VERSIONSTRING,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PDF
ZEND_GET_MODULE(pdf)
#endif /* COMPILE_DL_PDF */

/* exception handling */
/* {{{ pdf_try/pdf_catch _pdfexception */

#if PHP_MAJOR_VERSION >= 5
PHP_METHOD(PDFlibException, get_apiname);
PHP_METHOD(PDFlibException, get_errmsg);
PHP_METHOD(PDFlibException, get_errnum);

static zend_function_entry PDFlibException_functions[] = {
	PHP_ME(PDFlibException, get_apiname, NULL, 0)
	PHP_ME(PDFlibException, get_errmsg, NULL, 0)
	PHP_ME(PDFlibException, get_errnum, NULL, 0)
	{NULL, NULL, NULL}
};
#endif /* PHP_MAJOR_VERSION >= 5 */

#define pdf_try		PDF_TRY(pdf)

#define pdf_catch	PDF_CATCH(pdf) { \
	_pdf_exception(PDF_get_errnum(pdf), PDF_get_apiname(pdf), PDF_get_errmsg(pdf) TSRMLS_CC); \
	}

#if PHP_MAJOR_VERSION >= 5
/* use our own version of WRONG_PARAM_COUNT and ZEND_FETCH_RESOURCE
 * to change error handling to exceptions in case of problems. */

#undef WRONG_PARAM_COUNT
#define WRONG_PARAM_COUNT \
{\
	php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC); \
    zend_wrong_param_count(TSRMLS_C); \
	php_std_error_handling(); \
	return;\
}

#undef WRONG_PARAM_COUNT_WITH_RETVAL
#define WRONG_PARAM_COUNT_WITH_RETVAL(ret) \
{\
	php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC); \
    zend_wrong_param_count(TSRMLS_C); \
	php_std_error_handling(); \
	return ret;\
}

#undef ZEND_FETCH_RESOURCE
#define ZEND_FETCH_RESOURCE(rsrc, rsrc_type, passed_id, \
				default_id, resource_type_name, resource_type)  \
	php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC); \
	rsrc = (rsrc_type) zend_fetch_resource(passed_id TSRMLS_CC, \
			default_id, resource_type_name, NULL, 1, resource_type);    \
	php_std_error_handling(); \
	ZEND_VERIFY_RESOURCE(rsrc);

#define P_FROM_OBJECT(pdf, object) \
    { \
        pdflib_object *obj = (pdflib_object*) \
			zend_object_store_get_object(object TSRMLS_CC); \
        pdf = obj->p; \
        if (!pdf) { \
            php_error_docref(NULL TSRMLS_CC, E_WARNING, "No PDFlib object available"); \
			php_std_error_handling(); \
            RETURN_NULL(); \
        } \
    }

#else  /* ! PHP_MAJOR_VERSION >= 5  */

#if defined(PHP_MAJOR_VERSION) /* PHP 4.3.0 or newer */
#define P_FROM_OBJECT(pdf, object) \
    { \
        pdflib_object *obj = (pdflib_object*) \
			zend_object_store_get_object(object TSRMLS_CC); \
        pdf = obj->p; \
        if (!pdf) { \
            php_error_docref(NULL TSRMLS_CC, E_WARNING, "No PDFlib object available"); \
            RETURN_NULL(); \
        } \
    }
#else /* !PHP 4.3.0 or newer */
#define P_FROM_OBJECT(pdf, object) \
    { \
        pdflib_object *obj = (pdflib_object*) \
			zend_object_store_get_object(object TSRMLS_CC); \
        pdf = obj->p; \
        if (!pdf) { \
            php_error_docref(NULL TSRMLS_CC, E_WARNING, "No PDFlib object available"); \
            RETURN_NULL(); \
        } \
    }
#endif /* PHP 4.3.0 or newer */

#endif /* PHP_MAJOR_VERSION >= 5  */




zend_class_entry *default_exception_ce;

static void _pdf_exception(int errnum, const char *apiname, const char *errmsg TSRMLS_DC)
{
	char msgbuf[2048];

	snprintf(msgbuf, sizeof(msgbuf), "[%d] %s: %s", errnum, apiname, errmsg);

#if PHP_MAJOR_VERSION >= 5
	{
		zval *ex;
		MAKE_STD_ZVAL(ex);
		object_init_ex(ex, pdflib_exception_class);
		if (apiname) {
		   zend_update_property_string(pdflib_exception_class, ex, "apiname",
							sizeof("apiname")-1, (char *)apiname TSRMLS_CC);
		}
		zend_throw_exception(pdflib_exception_class, (char *)errmsg, (long)errnum TSRMLS_CC);
	}
#else /* ! >= 5 */
#if defined(PHP_MAJOR_VERSION) /* PHP 4.3.0 or newer */
	php_error_docref(NULL TSRMLS_CC, E_ERROR, msgbuf);
#else
	php_error(E_ERROR, msgbuf);
#endif
#endif /* >= 5 */
}
/* }}} */

/* PHP/PDFlib internal functions */
/* {{{ _free_pdf_doc
 */
static void _free_pdf_doc(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	PDF *pdf = (PDF *)rsrc->ptr;
	PDF_delete(pdf);
}
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

#if PHP_MAJOR_VERSION >= 5
/* {{{ pdflib_object_dtor */
static void
pdflib_object_dtor(void *object TSRMLS_DC)
{
	pdflib_object *intern = (pdflib_object *)object;

	zend_hash_destroy(intern->std.properties);
	FREE_HASHTABLE(intern->std.properties);

	if (intern->p) {
		PDF_delete(intern->p);
		intern->p = (PDF *)0;
	}
	efree(object);
}
/* }}} */

/* {{{ pdflib_object_new_ex
 */
static zend_object_value
pdflib_object_new_ex(zend_class_entry *class_type, pdflib_object**obj TSRMLS_DC)
{
	zend_object_value retval;
	pdflib_object *intern;
	zval *tmp;


	intern = emalloc(sizeof(pdflib_object));
	memset(intern, 0, sizeof(pdflib_object));
	intern->std.ce = class_type;
	*obj = intern;

	ALLOC_HASHTABLE(intern->std.properties);
	zend_hash_init(intern->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
	zend_hash_copy(intern->std.properties,
			&class_type->default_properties,
			(copy_ctor_func_t) zval_add_ref,
			(void *) &tmp, sizeof(zval *));

	retval.handle = zend_objects_store_put(intern,  NULL,
			(zend_objects_free_object_storage_t)pdflib_object_dtor,
			NULL TSRMLS_CC);
	retval.handlers = &pdflib_handlers;
	return retval;
}
/* }}} */

/* {{{ pdflib_object_new
 */
static zend_object_value
pdflib_object_new(zend_class_entry *class_type TSRMLS_DC)
{
	pdflib_object *tmp;

	return pdflib_object_new_ex(class_type, &tmp TSRMLS_CC);
}
/* }}} */

/* {{{ proto bool pdf::__construct()
 * Constructs a new PDFlib object. */
PHP_METHOD(dir, __construct)
{
	zval *object = getThis();
	pdflib_object *intern;

	intern = (pdflib_object *)zend_object_store_get_object(object TSRMLS_CC);
	intern->p = PDF_new();
}

#endif /* PHP_MAJOR_VERSION >= 5 */
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(pdf)
{
	char tmp[32];

	snprintf(tmp, 31, "%d.%02d", PDF_get_majorversion(), PDF_get_minorversion() );
	tmp[31]=0;

	php_info_print_table_start();
	php_info_print_table_row(2, "PDF Support", "enabled" );
#ifdef PDF_FEATURE_INTERNAL
	php_info_print_table_row(2, "PDFlib GmbH Binary-Version", PDFLIB_VERSIONSTRING );
#else /* PDF_FEATURE_INTERNAL */
	php_info_print_table_row(2, "PDFlib GmbH Version", PDFLIB_VERSIONSTRING );
#endif /* PDF_FEATURE_INTERNAL */
	php_info_print_table_row(2, "PECL Version", PDFLIB_PECL_VERSIONSTRING);
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
#if defined(PHP_MAJOR_VERSION) /* PHP 4.3.0 or newer */
		php_error_docref(NULL TSRMLS_CC, E_ERROR,"PDFlib error: Version mismatch in wrapper code");
#else
		php_error(E_ERROR,"PDFlib error: Version mismatch in wrapper code");
#endif
	}
	le_pdf = zend_register_list_destructors_ex(_free_pdf_doc, NULL, "pdf object", module_number);

	/* this does something like setlocale("C", ...) in PDFlib 3.x */
	PDF_boot();

#if PHP_MAJOR_VERSION >= 5
	/* add PDFlibException class */
	{
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "PDFlibException", PDFlibException_functions);
    pdflib_exception_class = zend_register_internal_class_ex(&ce,
#if PHP_MAJOR_VERSION >= 5 && PHP_MINOR_VERSION >= 2
            zend_exception_get_default(TSRMLS_C),
#else
            zend_exception_get_default(),
#endif
			 NULL TSRMLS_CC);

	zend_declare_property_string(pdflib_exception_class, "apiname",
			sizeof("apiname")-1, "", ZEND_ACC_PROTECTED TSRMLS_CC);
    pdflib_exception_class->ce_flags |= ZEND_ACC_FINAL;
    pdflib_exception_class->constructor->common.fn_flags
			|= ZEND_ACC_PROTECTED;

	INIT_CLASS_ENTRY(ce, "PDFlib", pdflib_funcs);
	ce.create_object = pdflib_object_new;
    pdflib_class = zend_register_internal_class(&ce TSRMLS_CC);
	memcpy(&pdflib_handlers,
			zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	pdflib_handlers.clone_obj = NULL;
    pdflib_class->ce_flags |= ZEND_ACC_FINAL_CLASS;
    pdflib_class->constructor->common.fn_flags |= ZEND_ACC_PROTECTED;
    }
#endif /* PHP_MAJOR_VERSION >= 5 */

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


#if PHP_MAJOR_VERSION >= 5
/* The PDFlibException Methods */
PHP_METHOD(PDFlibException, get_apiname)
{
	zval *apiname;
	char *retbuf;

	apiname = zend_read_property(pdflib_exception_class, this_ptr, "apiname",
				sizeof("apiname")-1, 1 TSRMLS_CC);
	retbuf = Z_STRVAL_P(apiname);

	RETURN_STRING(retbuf ? (char *)retbuf : "", 1);
}

PHP_METHOD(PDFlibException, get_errmsg)
{
	zval *message;
	char *retbuf;

	message = zend_read_property(pdflib_exception_class, this_ptr, "message",
				sizeof("message")-1, 1 TSRMLS_CC);
	retbuf = Z_STRVAL_P(message);

	RETURN_STRING(retbuf ? (char *)retbuf : "", 1);
}

PHP_METHOD(PDFlibException, get_errnum)
{
	zval *code;
	long retval;

	code = zend_read_property(pdflib_exception_class, this_ptr, "code",
				sizeof("code")-1, 1 TSRMLS_CC);
	retval = Z_LVAL_P(code);

	RETURN_LONG(retval);
}

#endif /* PHP_MAJOR_VERSION >= 5 */
/* The PDFlib API */

#define _WRAP_CODE
#include "php_wrapped.c"
#undef _WRAP_CODE

/* {{{ proto int pdf_open_pdi(resource p, string filename, string optlist, int reserved);
 * Open a disk-based or virtual PDF document and prepare it for later use. */
PHP_FUNCTION(pdf_open_pdi)
{
	PDF *pdf;
	char *filename, *optlist;
	int flen, olen;
	long len;
	char *vfilename;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ssl", &filename, &flen, &optlist, &olen, &len)) {
			php_std_error_handling();
			return;
		}
		P_FROM_OBJECT(pdf, object);
	} else {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
	#endif /* PHP_MAJOR_VERSION >= 5 */
		{
			zval *p;
			if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"rssl", &p, &filename, &flen, &optlist, &olen, &len)) {
	#if PHP_MAJOR_VERSION >= 5
				php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */
				return;
			}
			ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

#ifdef VIRTUAL_DIR
	virtual_filepath(filename, &vfilename TSRMLS_CC);
#else /* !VIRTUAL_DIR */
	vfilename = filename;
#endif /* VIRTUAL_DIR */

#ifdef PDFLIB_CHECK_OPEN_BASEDIR
	if (php_check_open_basedir(vfilename TSRMLS_CC) || (PG(safe_mode) && !php_checkuid(vfilename, "rb+", CHECKUID_CHECK_MODE_PARAM))) {
		RETURN_FALSE;
	}
#endif /* PDFLIB_CHECK_OPEN_BASEDIR */

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
	PDF *pdf;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"")) {
			php_std_error_handling();
			return;
		}
		P_FROM_OBJECT(pdf, object);
	} else {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
	#endif /* PHP_MAJOR_VERSION >= 5 */
		{
			zval *p;
			if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"r", &p)) {
	#if PHP_MAJOR_VERSION >= 5
				php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */
				return;
			}
			ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
			zend_list_delete(Z_RESVAL_PP(&p));
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto int pdf_new()
 * Create a new PDFlib object with default settings. */
PHP_FUNCTION(pdf_new)
{
	PDF *pdf;
#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();
	pdflib_object *intern;
#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf = PDF_new2(NULL, pdf_emalloc, pdf_realloc, pdf_efree, NULL);

	if (pdf != NULL) {
		pdf_try {
			/* Trigger special handling of PDFlib-handles for PHP */
			PDF_set_parameter(pdf, "hastobepos", "true");
#if PHP_MAJOR_VERSION >= 5
			PDF_set_parameter(pdf, "binding", "PHP5");
#else  /* !PHP_MAJOR_VERSION >= 5 */
			PDF_set_parameter(pdf, "binding", "PHP");
#endif /* PHP_MAJOR_VERSION >= 5 */
		} pdf_catch;
	} else {
		_pdf_exception(99, "PDF_new", "PDF_new: internal error" TSRMLS_CC);
	}

#if PHP_MAJOR_VERSION >= 5
	if (object) {
		PDF_set_parameter(pdf, "objorient", "true");
		intern =(pdflib_object *)zend_object_store_get_object(object TSRMLS_CC);
		intern->p = pdf;
	} else {
#endif /* PHP_MAJOR_VERSION >= 5 */
		ZEND_REGISTER_RESOURCE(return_value, pdf, le_pdf);
#if PHP_MAJOR_VERSION >= 5
	}
#endif /* PHP_MAJOR_VERSION >= 5 */
}
/* }}} */

/* {{{ proto int pdf_open_image(resource p, string imagetype, string source, string data, long length, int width, int height, int components, int bpc, string params)
 * Deprecated, use PDF_load_image() with virtual files. */
PHP_FUNCTION(pdf_open_image)
{
	PDF *pdf;
	char *imagetype, *source, *data, *params;
	int ilen, dlen, slen, plen;
	long length, width, height, components, bpc;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"sssllllls", &imagetype, &ilen, &source, &slen,
						&data, &dlen, &length, &width, &height, &components,
						&bpc, &params, &plen)) {
			php_std_error_handling();
			return;
		}
		P_FROM_OBJECT(pdf, object);
	} else {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
	#endif /* PHP_MAJOR_VERSION >= 5 */
		{
			zval *p;
			if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"rsssllllls", &p, &imagetype, &ilen, &source, &slen,
						&data, &dlen, &length, &width, &height, &components,
						&bpc, &params, &plen)) {
	#if PHP_MAJOR_VERSION >= 5
				php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */
				return;
			}
			ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		retval = PDF_open_image(pdf, imagetype, source, data, length,
			(int)width, (int)height, (int)components, (int)bpc, params);
	} pdf_catch;

	RETURN_LONG(retval); /* offset handled in PDFlib Kernel */
}
/* }}} */

/* {{{ proto bool pdf_setpolydash(resource p, double darray)
 * Deprecated, use PDF_setdashpattern(). */
PHP_FUNCTION(pdf_setpolydash)
{
	zval **p, **darray;
	HashTable *array;
	int len, i;
	float *xarray;
	PDF *pdf;

	if (ZEND_NUM_ARGS() != 2 || zend_get_parameters_ex(2, &p, &darray) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);

	convert_to_array_ex(darray);
	array = Z_ARRVAL_PP(darray);
	len = zend_hash_num_elements(array);

	xarray = safe_emalloc(len, sizeof(float), 0);

	zend_hash_internal_pointer_reset(array);
	for (i=0; i<len; i++) {
	    zval *keydata, **keydataptr;

	    zend_hash_get_current_data(array, (void **) &keydataptr);
	    keydata = *keydataptr;
	    if (Z_TYPE_P(keydata) == IS_DOUBLE) {
			xarray[i] = (float) Z_DVAL_P(keydata);
	    } else if (Z_TYPE_P(keydata) == IS_LONG) {
			xarray[i] = (float) Z_LVAL_P(keydata);
	    } else {
			_pdf_exception(99, "PDF_set_polydash", "illegal darray value" TSRMLS_CC);
	    }
	    zend_hash_move_forward(array);
	}

	pdf_try {
		PDF_setpolydash(pdf, xarray, len);
	} pdf_catch;

	efree(xarray);
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string PDF_utf16_to_utf8(resource p, string utf16string);
 * Convert a string from UTF-16 format to UTF-8. */
PHP_FUNCTION(pdf_utf16_to_utf8)
{
	PDF *pdf;
	char *utf16string;
	int ulen;
	const char *retbuf = NULL;
	int size;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"s", &utf16string, &ulen)) {
			php_std_error_handling();
			return;
		}
		P_FROM_OBJECT(pdf, object);
	} else {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
	#endif /* PHP_MAJOR_VERSION >= 5 */
		{
			zval *p;
			if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"rs", &p, &utf16string, &ulen)) {
	#if PHP_MAJOR_VERSION >= 5
				php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */
				return;
			}
			ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		retbuf = PDF_utf16_to_utf8(pdf, utf16string, ulen, &size);
	} pdf_catch;

	RETURN_STRINGL((char *)retbuf, size, 1);
}
/* }}} */

/* {{{ proto string PDF_utf8_to_utf16(resource p, string utf8string, string ordering);
 * Convert a string from UTF-8 format to UTF-16. */
PHP_FUNCTION(pdf_utf8_to_utf16)
{
	PDF *pdf;
	char *utf8string;
	char *ordering;
	int ulen;
	int olen;
	const char *retbuf = NULL;
	int size;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ss", &utf8string, &ulen, &ordering, &olen)) {
			php_std_error_handling();
			return;
		}
		P_FROM_OBJECT(pdf, object);
	} else {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
	#endif /* PHP_MAJOR_VERSION >= 5 */
		{
			zval *p;
			if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"rss", &p, &utf8string, &ulen, &ordering, &olen)) {
	#if PHP_MAJOR_VERSION >= 5
				php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */
				return;
			}
			ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		retbuf = PDF_utf8_to_utf16(pdf, utf8string, ordering, &size);
	} pdf_catch;

	RETURN_STRINGL((char *)retbuf, size, 1);
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
