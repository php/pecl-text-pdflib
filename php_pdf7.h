/*
   +----------------------------------------------------------------------+
   | PHP version 4.0                                                      |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2001 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 2.02 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available at through the world-wide-web at                           |
   | http://www.php.net/license/2_02.txt.                                 |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Uwe Steinmann <Uwe.Steinmann@fernuni-hagen.de>              |
   +----------------------------------------------------------------------+
*/

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

PHP_FUNCTION(pdf_open_pdi);
PHP_FUNCTION(pdf_open_ccitt);
PHP_FUNCTION(pdf_show_boxed);
PHP_FUNCTION(pdf_utf16_to_utf8);
PHP_FUNCTION(pdf_utf32_to_utf16);
PHP_FUNCTION(pdf_utf8_to_utf16);

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
