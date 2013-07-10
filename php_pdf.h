
/* $Id$ */
/* Derived from:
    Id: php_pdf.h,v 1.22 2001/11/30 04:46:35 sniper Exp */

#ifndef PHP_PDF_H
#define PHP_PDF_H

#if HAVE_PDFLIB

#include <pdflib.h>

extern zend_module_entry pdf_module_entry;
#define pdf_module_ptr &pdf_module_entry

PHP_MINFO_FUNCTION(pdf);
PHP_MINIT_FUNCTION(pdf);
PHP_MSHUTDOWN_FUNCTION(pdf);

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

#ifdef ZTS
#define PDFG(v) TSRMG(pdf_globals_id, php_pdf_globals *, v)
#else
#define PDFG(v) (pdf_globals.v)
#endif


#else
#define pdf_module_ptr NULL
#endif

#define phpext_pdf_ptr pdf_module_ptr
#endif /* PHP_PDF_H */
