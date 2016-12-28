
/* $Id$ */
/* Derived from:
    Id: php_pdf.h,v 1.22 2001/11/30 04:46:35 sniper Exp */

#ifndef PHP_PDF_H
#define PHP_PDF_H

extern zend_module_entry PDFlib_module_entry;
#define phpext_pdf_ptr &PDFlib_module_entry

#ifdef PHP_WIN32
#   define PHP_PDFLIB_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#   define PHP_PDFLIB_API __attribute__ ((visibility("default")))
#else
#   define PHP_PDFLIB_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#ifndef PHP_FE_END
#define PHP_FE_END {NULL, NULL, NULL}
#endif


PHP_MINFO_FUNCTION(PDFlib);
PHP_MINIT_FUNCTION(PDFlib);
PHP_MSHUTDOWN_FUNCTION(PDFlib);

#define _WRAP_FUNCTION_ENTRY3
#include "php_wrapped.c"
#undef _WRAP_FUNCTION_ENTRY3

PHP_FUNCTION(pdf_new);
PHP_FUNCTION(pdf_delete);
PHP_FUNCTION(pdf_get_pdi_parameter);
PHP_FUNCTION(pdf_open_pdi);
PHP_FUNCTION(pdf_open_image);
PHP_FUNCTION(pdf_show_boxed);
PHP_FUNCTION(pdf_setpolydash);
PHP_FUNCTION(pdf_utf16_to_utf8);
PHP_FUNCTION(pdf_utf32_to_utf16);
PHP_FUNCTION(pdf_utf8_to_utf16);
PHP_FUNCTION(pdf_utf32_to_utf8);
PHP_FUNCTION(pdf_utf8_to_utf32);
PHP_FUNCTION(pdf_utf16_to_utf32);

#if PHP_MAJOR_VERSION >= 7
#if defined(ZTS) && defined(COMPILE_DL_PDFLIB)
ZEND_TSRMLS_CACHE_EXTERN();
#endif
#endif /* PHP_MAJOR_VERSION >= 7 */

#endif
