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

/* {{{ Comments about the module */

/* derived from:
   $Id$
   synced with pdflib.h 1.237 */

/* PDFlib 2.02 ... 4.0.x is subject to the ALADDIN FREE PUBLIC LICENSE.
   PDFlib 5.0.x ... 6.0.x is subject to the  PDFlib Lite License Agreement
   Copyright (C) 1997-1999 Thomas Merz. 2000-2004 PDFlib GmbH */
/* Note that there is no code from the pdflib package in this file */

/*
	This PDFlib Wrapper Code works with PDFlib 5 and higher.

	A new module was introduced, as PDFlib 5 supports a method to
	handle the special returnvalues needed for PHP in the PDFlib core now.

	This is necesarry, as the new concept of optionlists in PDFlib allows
	to pass handles to PDFlib objects and filenames inside of optionlists.

	Before the wrapper added some offset to handles returned by PDFlib
	to fit into scheme used by php to return 0 in case of errors, whereas
	in PDFlib the errorcode is -1 and "0" is a valid handle.

	As the optionlist may contain filenames on various places the 
	VIRTUAL_DIR support and the CHECK_OPEN_BASEDIR checks implemented
	in the wrapper will not work reliable too. So VIRTUAL_DIR support
	and the CHECK_OPEN_BASEDIR checking is disabled here too, as it would
	only work for some of the files used with PDFlib.

	The main changes:
	- supports PDFlib 5 and PDFlib 6
	- adds an Object Oriented API to PDFlib (for PHP 5 only)
	- uses PHP exceptions (for PHP 5 only)
	- only official PDFlib API's are included (plus pdf_open_memory_image)
	- builds with older PHP Version too
	  (tested with PHP 4.1.0, 4.2.1, 4.3.0, and 5.0.0RC2.)
	- disables VIRTUAL_DIR support (use SerachPath instead)
	- disables CHECK_OPEN_BASEDIR checks
	- changed old API's with varargs to only accept all args now
*/

/* Bootstrap of PDFlib Feature setup */
#define PDF_FEATURE_INTERNAL
#define   PDFLIB_PECL_VERSIONSTRING "2.0.5"

/* set this define if you want to include GD support
 * this adds the (unofficial) function pdf_open_memory_image()
#define PDFLIB_WITH_GD_SUPPORT
*/

/* }}} */

/* {{{ includes
 */

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
#if PHP_MAJOR_VERSION >= 5
# include "Zend/zend_exceptions.h"
#endif /* PHP_MAJOR_VERSION >= 5 */

#if PDFLIB_WITH_GD_SUPPORT
#if HAVE_LIBGD13
# include "ext/gd/php_gd.h"
# if HAVE_GD_BUNDLED
#  include "ext/gd/libgd/gd.h"
# else /* !HAVE_GD_BUNDLED */
#  include "gd.h"
# endif /* HAVE_GD_BUNDLED */
 static int le_gd;
#endif /* HAVE_LIBGD13 */
#endif /* PDFLIB_WITH_GD_SUPPORT */

#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif /* HAVE_UNISTD_H */

#ifdef PHP_WIN32
# include <io.h>
# include <fcntl.h>
#endif /* PHP_WIN32 */

#if HAVE_PDFLIB
#include "pdflib.h"

#if PDFLIB_MAJORVERSION >= 5
	/* This wrapper code will work only with PDFlib V5 or greater,
	 * because the special handling for returning 0 instead of -1
	 * for PHP is now done in the PDFlib kernel */

/* }}} */

#include "php_pdf.h"

#undef VIRTUAL_DIR
#undef PDFLIB_CHECK_OPEN_BASEDIR

#ifndef safe_emalloc		/* to be compatible with older PHP versions */
#define safe_emalloc(a,b,c)	emalloc((a) * (b))
#endif

/* {{{ pdf_functions[]
 */

static int le_pdf;

function_entry pdf_functions[] = {
#if PDFLIB_MAJORVERSION >= 6
	PHP_FE(pdf_activate_item, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_FE(pdf_add_bookmark, NULL)
	PHP_FE(pdf_add_launchlink, NULL)
	PHP_FE(pdf_add_locallink, NULL)
	PHP_FE(pdf_add_nameddest, NULL)
	PHP_FE(pdf_add_note, NULL)
	PHP_FE(pdf_add_pdflink, NULL)
	PHP_FE(pdf_add_thumbnail, NULL)
	PHP_FE(pdf_add_weblink, NULL)
	PHP_FE(pdf_arc, NULL)
	PHP_FE(pdf_arcn, NULL)
	PHP_FE(pdf_attach_file, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_FE(pdf_begin_document, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_FE(pdf_begin_font, NULL)
	PHP_FE(pdf_begin_glyph, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_FE(pdf_begin_item, NULL)
	PHP_FE(pdf_begin_layer, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_FE(pdf_begin_page, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_FE(pdf_begin_page_ext, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_FE(pdf_begin_pattern, NULL)
	PHP_FE(pdf_begin_template, NULL)
	PHP_FE(pdf_circle, NULL)
	PHP_FE(pdf_clip, NULL)
	PHP_FE(pdf_close, NULL)
	PHP_FE(pdf_close_image, NULL)
	PHP_FE(pdf_close_pdi, NULL)
	PHP_FE(pdf_close_pdi_page, NULL)
	PHP_FE(pdf_closepath, NULL)
	PHP_FE(pdf_closepath_fill_stroke, NULL)
	PHP_FE(pdf_closepath_stroke, NULL)
	PHP_FE(pdf_concat, NULL)
	PHP_FE(pdf_continue_text, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_FE(pdf_create_action, NULL)
	PHP_FE(pdf_create_annotation, NULL)
	PHP_FE(pdf_create_bookmark, NULL)
	PHP_FE(pdf_create_field, NULL)
	PHP_FE(pdf_create_fieldgroup, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_FE(pdf_create_gstate, NULL)
	PHP_FE(pdf_create_pvf, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_FE(pdf_create_textflow, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_FE(pdf_curveto, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_FE(pdf_define_layer, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_FE(pdf_delete, NULL)
	PHP_FE(pdf_delete_pvf, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_FE(pdf_delete_textflow, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_FE(pdf_encoding_set_char, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_FE(pdf_end_document, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_FE(pdf_end_font, NULL)
	PHP_FE(pdf_end_glyph, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_FE(pdf_end_item, NULL)
	PHP_FE(pdf_end_layer, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_FE(pdf_end_page, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_FE(pdf_end_page_ext, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_FE(pdf_end_pattern, NULL)
	PHP_FE(pdf_end_template, NULL)
	PHP_FE(pdf_endpath, NULL)
	PHP_FE(pdf_fill, NULL)
	PHP_FE(pdf_fill_imageblock, NULL)
	PHP_FE(pdf_fill_pdfblock, NULL)
	PHP_FE(pdf_fill_stroke, NULL)
	PHP_FE(pdf_fill_textblock, NULL)
	PHP_FE(pdf_findfont, NULL)
	PHP_FE(pdf_fit_image, NULL)
	PHP_FE(pdf_fit_pdi_page, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_FE(pdf_fit_textflow, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_FE(pdf_fit_textline, NULL)
	PHP_FE(pdf_get_apiname, NULL)
	PHP_FE(pdf_get_buffer, NULL)
	PHP_FE(pdf_get_errmsg, NULL)
	PHP_FE(pdf_get_errnum, NULL)
	PHP_FE(pdf_get_parameter, NULL)
	PHP_FE(pdf_get_pdi_parameter, NULL)
	PHP_FE(pdf_get_pdi_value, NULL)
	PHP_FE(pdf_get_value, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_FE(pdf_info_textflow, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_FE(pdf_initgraphics, NULL)
	PHP_FE(pdf_lineto, NULL)
	PHP_FE(pdf_load_font, NULL)
	PHP_FE(pdf_load_iccprofile, NULL)
	PHP_FE(pdf_load_image, NULL)
	PHP_FE(pdf_makespotcolor, NULL)
	PHP_FE(pdf_moveto, NULL)
	PHP_FE(pdf_new, NULL)
	PHP_FE(pdf_open_ccitt, NULL)
	PHP_FE(pdf_open_file, NULL)
	PHP_FE(pdf_open_image, NULL)
	PHP_FE(pdf_open_image_file, NULL)
	PHP_FE(pdf_open_pdi, NULL)
	PHP_FE(pdf_open_pdi_page, NULL)
	PHP_FE(pdf_place_image, NULL)
	PHP_FE(pdf_place_pdi_page, NULL)
	PHP_FE(pdf_process_pdi, NULL)
	PHP_FE(pdf_rect, NULL)
	PHP_FE(pdf_restore, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_FE(pdf_resume_page, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_FE(pdf_rotate, NULL)
	PHP_FE(pdf_save, NULL)
	PHP_FE(pdf_scale, NULL)
	PHP_FE(pdf_set_border_color, NULL)
	PHP_FE(pdf_set_border_dash, NULL)
	PHP_FE(pdf_set_border_style, NULL)
	PHP_FE(pdf_set_gstate, NULL)
	PHP_FE(pdf_set_info, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_FE(pdf_set_layer_dependency, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_FE(pdf_set_parameter, NULL)
	PHP_FE(pdf_set_text_pos, NULL)
	PHP_FE(pdf_set_value, NULL)
	PHP_FE(pdf_setcolor, NULL)
	PHP_FE(pdf_setdash, NULL)
	PHP_FE(pdf_setdashpattern, NULL)
	PHP_FE(pdf_setflat, NULL)
	PHP_FE(pdf_setfont, NULL)
	PHP_FE(pdf_setlinecap, NULL)
	PHP_FE(pdf_setlinejoin, NULL)
	PHP_FE(pdf_setlinewidth, NULL)
	PHP_FE(pdf_setmatrix, NULL)
	PHP_FE(pdf_setmiterlimit, NULL)
	PHP_FE(pdf_setpolydash, NULL)
	PHP_FE(pdf_shading, NULL)
	PHP_FE(pdf_shading_pattern, NULL)
	PHP_FE(pdf_shfill, NULL)
	PHP_FE(pdf_show, NULL)
	PHP_FE(pdf_show_boxed, NULL)
	PHP_FE(pdf_show_xy, NULL)
	PHP_FE(pdf_skew, NULL)
	PHP_FE(pdf_stringwidth, NULL)
	PHP_FE(pdf_stroke, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_FE(pdf_suspend_page, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_FE(pdf_translate, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_FE(pdf_utf16_to_utf8, NULL)
	PHP_FE(pdf_utf8_to_utf16, NULL)
#endif /* PDFlib >= 6.0.0 */

	/* End of the official PDFLIB API */

#if PDFLIB_WITH_GD_SUPPORT
#if HAVE_LIBGD13
	/* not supported by PDFlib GmbH */
	PHP_FE(pdf_open_memory_image, NULL)
#endif /* HAVE_LIBGD13 */
#endif /* PDFLIB_WITH_GD_SUPPORT */

	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ pdflib_funcs[] OO-Mapping
 */

zend_class_entry *pdflib_class;
zend_class_entry *pdflib_exception_class;

#if PHP_MAJOR_VERSION >= 5
static zend_object_handlers pdflib_handlers;

typedef struct _pdflib_object {
	zend_object	std;
	PDF *p;
} pdflib_object;

function_entry pdflib_funcs[] = {
#if PDFLIB_MAJORVERSION >= 6
	PHP_ME_MAPPING(activate_item, pdf_activate_item, NULL)
#endif /* PDFlib >= 6.0.0 */
/* 	PHP_ME_MAPPING(add_bookmark, pdf_add_bookmark, NULL) deprecated */
/* 	PHP_ME_MAPPING(add_launchlink, pdf_add_launchlink, NULL) deprecated */
/* 	PHP_ME_MAPPING(add_locallink, pdf_add_locallink, NULL) deprecated */
	PHP_ME_MAPPING(add_nameddest, pdf_add_nameddest, NULL)
/* 	PHP_ME_MAPPING(add_note, pdf_add_note, NULL) deprecated */
/* 	PHP_ME_MAPPING(add_pdflink, pdf_add_pdflink, NULL) deprecated */
	PHP_ME_MAPPING(add_thumbnail, pdf_add_thumbnail, NULL)
/* 	PHP_ME_MAPPING(add_weblink, pdf_add_weblink, NULL) deprecated */
	PHP_ME_MAPPING(arc, pdf_arc, NULL)
	PHP_ME_MAPPING(arcn, pdf_arcn, NULL)
/* 	PHP_ME_MAPPING(attach_file, pdf_attach_file, NULL) deprecated */
#if PDFLIB_MAJORVERSION >= 6
	PHP_ME_MAPPING(begin_document, pdf_begin_document, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_ME_MAPPING(begin_font, pdf_begin_font, NULL)
	PHP_ME_MAPPING(begin_glyph, pdf_begin_glyph, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_ME_MAPPING(begin_item, pdf_begin_item, NULL)
	PHP_ME_MAPPING(begin_layer, pdf_begin_layer, NULL)
#endif /* PDFlib >= 6.0.0 */
/* 	PHP_ME_MAPPING(begin_page, pdf_begin_page, NULL) deprecated */
#if PDFLIB_MAJORVERSION >= 6
	PHP_ME_MAPPING(begin_page_ext, pdf_begin_page_ext, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_ME_MAPPING(begin_pattern, pdf_begin_pattern, NULL)
	PHP_ME_MAPPING(begin_template, pdf_begin_template, NULL)
	PHP_ME_MAPPING(circle, pdf_circle, NULL)
	PHP_ME_MAPPING(clip, pdf_clip, NULL)
/* 	PHP_ME_MAPPING(close, pdf_close, NULL) deprecated */
	PHP_ME_MAPPING(close_image, pdf_close_image, NULL)
	PHP_ME_MAPPING(close_pdi, pdf_close_pdi, NULL)
	PHP_ME_MAPPING(close_pdi_page, pdf_close_pdi_page, NULL)
	PHP_ME_MAPPING(closepath, pdf_closepath, NULL)
	PHP_ME_MAPPING(closepath_fill_stroke, pdf_closepath_fill_stroke, NULL)
	PHP_ME_MAPPING(closepath_stroke, pdf_closepath_stroke, NULL)
	PHP_ME_MAPPING(concat, pdf_concat, NULL)
	PHP_ME_MAPPING(continue_text, pdf_continue_text, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_ME_MAPPING(create_action, pdf_create_action, NULL)
	PHP_ME_MAPPING(create_annotation, pdf_create_annotation, NULL)
	PHP_ME_MAPPING(create_bookmark, pdf_create_bookmark, NULL)
	PHP_ME_MAPPING(create_field, pdf_create_field, NULL)
	PHP_ME_MAPPING(create_fieldgroup, pdf_create_fieldgroup, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_ME_MAPPING(create_gstate, pdf_create_gstate, NULL)
	PHP_ME_MAPPING(create_pvf, pdf_create_pvf, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_ME_MAPPING(create_textflow, pdf_create_textflow, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_ME_MAPPING(curveto, pdf_curveto, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_ME_MAPPING(define_layer, pdf_define_layer, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_ME_MAPPING(delete, pdf_delete, NULL)
	PHP_ME_MAPPING(delete_pvf, pdf_delete_pvf, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_ME_MAPPING(delete_textflow, pdf_delete_textflow, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_ME_MAPPING(encoding_set_char, pdf_encoding_set_char, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_ME_MAPPING(end_document, pdf_end_document, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_ME_MAPPING(end_font, pdf_end_font, NULL)
	PHP_ME_MAPPING(end_glyph, pdf_end_glyph, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_ME_MAPPING(end_item, pdf_end_item, NULL)
	PHP_ME_MAPPING(end_layer, pdf_end_layer, NULL)
#endif /* PDFlib >= 6.0.0 */
/* 	PHP_ME_MAPPING(end_page, pdf_end_page, NULL) deprecated */
#if PDFLIB_MAJORVERSION >= 6
	PHP_ME_MAPPING(end_page_ext, pdf_end_page_ext, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_ME_MAPPING(end_pattern, pdf_end_pattern, NULL)
	PHP_ME_MAPPING(end_template, pdf_end_template, NULL)
	PHP_ME_MAPPING(endpath, pdf_endpath, NULL)
	PHP_ME_MAPPING(fill, pdf_fill, NULL)
	PHP_ME_MAPPING(fill_imageblock, pdf_fill_imageblock, NULL)
	PHP_ME_MAPPING(fill_pdfblock, pdf_fill_pdfblock, NULL)
	PHP_ME_MAPPING(fill_stroke, pdf_fill_stroke, NULL)
	PHP_ME_MAPPING(fill_textblock, pdf_fill_textblock, NULL)
/* 	PHP_ME_MAPPING(findfont, pdf_findfont, NULL) deprecated */
	PHP_ME_MAPPING(fit_image, pdf_fit_image, NULL)
	PHP_ME_MAPPING(fit_pdi_page, pdf_fit_pdi_page, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_ME_MAPPING(fit_textflow, pdf_fit_textflow, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_ME_MAPPING(fit_textline, pdf_fit_textline, NULL)
	PHP_ME_MAPPING(get_apiname, pdf_get_apiname, NULL)
	PHP_ME_MAPPING(get_buffer, pdf_get_buffer, NULL)
	PHP_ME_MAPPING(get_errmsg, pdf_get_errmsg, NULL)
	PHP_ME_MAPPING(get_errnum, pdf_get_errnum, NULL)
	PHP_ME_MAPPING(get_parameter, pdf_get_parameter, NULL)
	PHP_ME_MAPPING(get_pdi_parameter, pdf_get_pdi_parameter, NULL)
	PHP_ME_MAPPING(get_pdi_value, pdf_get_pdi_value, NULL)
	PHP_ME_MAPPING(get_value, pdf_get_value, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_ME_MAPPING(info_textflow, pdf_info_textflow, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_ME_MAPPING(initgraphics, pdf_initgraphics, NULL)
	PHP_ME_MAPPING(lineto, pdf_lineto, NULL)
	PHP_ME_MAPPING(load_font, pdf_load_font, NULL)
	PHP_ME_MAPPING(load_iccprofile, pdf_load_iccprofile, NULL)
	PHP_ME_MAPPING(load_image, pdf_load_image, NULL)
	PHP_ME_MAPPING(makespotcolor, pdf_makespotcolor, NULL)
	PHP_ME_MAPPING(moveto, pdf_moveto, NULL)
	PHP_ME_MAPPING(__construct, pdf_new, NULL)
/* 	PHP_ME_MAPPING(open_ccitt, pdf_open_ccitt, NULL) deprecated */
/* 	PHP_ME_MAPPING(open_file, pdf_open_file, NULL) deprecated */
/* 	PHP_ME_MAPPING(open_image, pdf_open_image, NULL) deprecated */
/* 	PHP_ME_MAPPING(open_image_file, pdf_open_image_file, NULL) deprecated */
	PHP_ME_MAPPING(open_pdi, pdf_open_pdi, NULL)
	PHP_ME_MAPPING(open_pdi_page, pdf_open_pdi_page, NULL)
/* 	PHP_ME_MAPPING(place_image, pdf_place_image, NULL) deprecated */
/* 	PHP_ME_MAPPING(place_pdi_page, pdf_place_pdi_page, NULL) deprecated */
	PHP_ME_MAPPING(process_pdi, pdf_process_pdi, NULL)
	PHP_ME_MAPPING(rect, pdf_rect, NULL)
	PHP_ME_MAPPING(restore, pdf_restore, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_ME_MAPPING(resume_page, pdf_resume_page, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_ME_MAPPING(rotate, pdf_rotate, NULL)
	PHP_ME_MAPPING(save, pdf_save, NULL)
	PHP_ME_MAPPING(scale, pdf_scale, NULL)
/* 	PHP_ME_MAPPING(set_border_color, pdf_set_border_color, NULL) deprecated */
/* 	PHP_ME_MAPPING(set_border_dash, pdf_set_border_dash, NULL) deprecated */
/* 	PHP_ME_MAPPING(set_border_style, pdf_set_border_style, NULL) deprecated */
	PHP_ME_MAPPING(set_gstate, pdf_set_gstate, NULL)
	PHP_ME_MAPPING(set_info, pdf_set_info, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_ME_MAPPING(set_layer_dependency, pdf_set_layer_dependency, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_ME_MAPPING(set_parameter, pdf_set_parameter, NULL)
	PHP_ME_MAPPING(set_text_pos, pdf_set_text_pos, NULL)
	PHP_ME_MAPPING(set_value, pdf_set_value, NULL)
	PHP_ME_MAPPING(setcolor, pdf_setcolor, NULL)
	PHP_ME_MAPPING(setdash, pdf_setdash, NULL)
	PHP_ME_MAPPING(setdashpattern, pdf_setdashpattern, NULL)
	PHP_ME_MAPPING(setflat, pdf_setflat, NULL)
	PHP_ME_MAPPING(setfont, pdf_setfont, NULL)
	PHP_ME_MAPPING(setlinecap, pdf_setlinecap, NULL)
	PHP_ME_MAPPING(setlinejoin, pdf_setlinejoin, NULL)
	PHP_ME_MAPPING(setlinewidth, pdf_setlinewidth, NULL)
	PHP_ME_MAPPING(setmatrix, pdf_setmatrix, NULL)
	PHP_ME_MAPPING(setmiterlimit, pdf_setmiterlimit, NULL)
/* 	PHP_ME_MAPPING(setpolydash, pdf_setpolydash, NULL) deprecated */
	PHP_ME_MAPPING(shading, pdf_shading, NULL)
	PHP_ME_MAPPING(shading_pattern, pdf_shading_pattern, NULL)
	PHP_ME_MAPPING(shfill, pdf_shfill, NULL)
	PHP_ME_MAPPING(show, pdf_show, NULL)
	PHP_ME_MAPPING(show_boxed, pdf_show_boxed, NULL)
	PHP_ME_MAPPING(show_xy, pdf_show_xy, NULL)
	PHP_ME_MAPPING(skew, pdf_skew, NULL)
	PHP_ME_MAPPING(stringwidth, pdf_stringwidth, NULL)
	PHP_ME_MAPPING(stroke, pdf_stroke, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_ME_MAPPING(suspend_page, pdf_suspend_page, NULL)
#endif /* PDFlib >= 6.0.0 */
	PHP_ME_MAPPING(translate, pdf_translate, NULL)
#if PDFLIB_MAJORVERSION >= 6
	PHP_ME_MAPPING(utf16_to_utf8, pdf_utf16_to_utf8, NULL)
	PHP_ME_MAPPING(utf8_to_utf16, pdf_utf8_to_utf16, NULL)
#endif /* PDFlib >= 6.0.0 */

	/* End of the official PDFLIB API */

#if PDFLIB_WITH_GD_SUPPORT
#if HAVE_LIBGD13
	/* not supported by PDFlib GmbH */
	/* PHP_ME_MAPPING(open_memory_image, pdf_open_memory_image, NULL) */
#endif /* HAVE_LIBGD13 */
#endif /* PDFLIB_WITH_GD_SUPPORT */

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

	sprintf(msgbuf, "[%d] %s: %s", errnum, apiname, errmsg);

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
	php_info_print_table_row(2, "PDFlib GmbH Version", PDFLIB_VERSIONSTRING );
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
			zend_exception_get_default(), NULL TSRMLS_CC);
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
/* {{{ proto bool PDF_activate_item(resource p, int id)
 * Activate a previously created structure element or other content item. */
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_activate_item)
{
	PDF *pdf;
	long id;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"l", &id)) {
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
						"rl", &p, &id)) {
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
		PDF_activate_item(pdf, (int)id);
	} pdf_catch;

	RETURN_TRUE;
}
#endif /* PDFlib >= 6.0.0 */
/* }}} */

/* {{{ proto int pdf_add_bookmark(resource p, string text, int parent, int open)
 * Deprecated, use  PDF_create_bookmark(). */
PHP_FUNCTION(pdf_add_bookmark)
{
	long retval = 0;
	PDF *pdf;
	char *text;
	int tlen;
	long parent;
	long open;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"sll", &text, &tlen, &parent, &open)) {
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
						"rsll", &p, &text, &tlen, &parent, &open)) {
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
		/* will never return 0 */
		retval = PDF_add_bookmark2(pdf, text, tlen, (int)parent, open);
	} pdf_catch;

	RETURN_LONG(retval);
}
/* }}} */

/* {{{ proto bool pdf_add_launchlink(resource p, double llx, double lly, double urx, double ury, string filename)
 * Deprecated, use PDF_create_action() and PDF_create_annotation(). */
PHP_FUNCTION(pdf_add_launchlink)
{
	PDF *pdf;
	double llx, lly, urx, ury;
	char *filename;
	int flen;
	const char * vfilename;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dddds", &llx, &lly, &urx, &ury, &filename, &flen)) {
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
					"rdddds", &p, &llx, &lly, &urx, &ury, &filename, &flen)) {
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
#else /* ! VIRTUAL_DIR */
	vfilename = filename;
#endif /* VIRTUAL_DIR */

#ifdef PDFLIB_CHECK_OPEN_BASEDIR
	if (php_check_open_basedir(vfilename TSRMLS_CC) || (PG(safe_mode) && !php_checkuid(vfilename, "rb+", CHECKUID_CHECK_MODE_PARAM))) {
		RETURN_FALSE;
	}
#endif /* PDFLIB_CHECK_OPEN_BASEDIR */

	pdf_try {
		PDF_add_launchlink(pdf, llx, lly, urx, ury, vfilename);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_add_locallink(resource p, double llx, double lly, double urx, double ury, int page, string optlist)
 * Deprecated, use PDF_create_action() and PDF_create_annotation(). */
PHP_FUNCTION(pdf_add_locallink)
{
	PDF *pdf;
	double llx, lly, urx, ury;
	long page;
	char *optlist;
	int olen;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
					"ddddls", &llx, &lly, &urx, &ury, &page, &optlist, &olen)) {
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
				"rddddls", &p, &llx, &lly, &urx, &ury, &page, &optlist, &olen)){
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
		PDF_add_locallink(pdf, llx, lly, urx, ury, (int)page, optlist);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_add_nameddest(resource p, string name, string optlist)
 * Create a named destination on an arbitrary page in the current document.*/
PHP_FUNCTION(pdf_add_nameddest)
{
	PDF *pdf;
	char *name;
	int len;
	char *optlist;
	int olen;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ss", &name, &len, &optlist, &olen)) {
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
						"rss", &p, &name, &len, &optlist, &olen)) {
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
		PDF_add_nameddest(pdf, name, len, optlist);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_add_note(resource p, double llx, double lly, double urx, double ury, string contents, string title, string icon, int open)
 * Deprecated, use PDF_create_annotation() instead. */
PHP_FUNCTION(pdf_add_note)
{
	PDF *pdf;
	double llx, lly, urx, ury;
	char *contents, *title, *icon;
	long open;
	int clen, tlen, ilen;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ddddsssl", &llx, &lly, &urx, &ury, &contents, &clen,
						&title, &tlen, &icon, &ilen, &open)) {
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
					"rddddsssl", &p, &llx, &lly, &urx, &ury, &contents, &clen,
					&title, &tlen, &icon, &ilen, &open)) {
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
		PDF_add_note2(pdf, llx, lly, urx, ury, contents, clen, title,
						 tlen, icon, (int)open);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_add_pdflink(resource p, double llx, double lly, double urx, double ury, string filename, int page, string optlist)
 * Deprecated, use PDF_create_action() and PDF_create_annotation(). */
PHP_FUNCTION(pdf_add_pdflink)
{
	PDF *pdf;
	double llx, lly, urx, ury;
	char *filename, *optlist;
	long page;
	int flen, olen;
	const char * vfilename;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ddddsls", &llx, &lly, &urx, &ury,
						&filename, &flen, &page, &optlist, &olen)) {
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
						"rddddsls", &p, &llx, &lly, &urx, &ury,
						&filename, &flen, &page, &optlist, &olen)) {
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
		PDF_add_pdflink(pdf, llx, lly, urx, ury, vfilename, (int)page, optlist);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_add_thumbnail(resource p, int image);
 * Add an existing image as thumbnail for the current page. */
PHP_FUNCTION(pdf_add_thumbnail)
{
	PDF *pdf;
	long image;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"l", &image)) {
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
						"rl", &p, &image)) {
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
		PDF_add_thumbnail(pdf, (int)image);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_add_weblink(resource p, double llx, double lly, double urx, double ury, string url)
 * Deprecated, use PDF_create_action() and PDF_create_annotation(). */
PHP_FUNCTION(pdf_add_weblink)
{
	PDF *pdf;
	double llx, lly, urx, ury;
	char *url;
	int ulen;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dddds", &llx, &lly, &urx, &ury, &url, &ulen)) {
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
						"rdddds", &p, &llx, &lly, &urx, &ury, &url, &ulen)) {
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
		PDF_add_weblink(pdf, llx, lly, urx, ury, url);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_arc(resource p, double x, double y, double r, double alpha, double beta)
 * Draw a counterclockwise circular arc segment. */
PHP_FUNCTION(pdf_arc)
{
	PDF *pdf;
	double x, y, r, alpha, beta;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ddddd", &x, &y, &r, &alpha, &beta)) {
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
						"rddddd", &p, &x, &y, &r, &alpha, &beta)) {
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
		PDF_arc(pdf, x, y, r, alpha, beta);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_arcn(resource p, double x, double y, double r, double alpha, double beta);
 * Draw a clockwise circular arc segment. */
PHP_FUNCTION(pdf_arcn)
{
	PDF *pdf;
	double x, y, r, alpha, beta;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ddddd", &x, &y, &r, &alpha, &beta)) {
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
						"rddddd", &p, &x, &y, &r, &alpha, &beta)) {
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
		PDF_arcn(pdf, x, y, r, alpha, beta);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_attach_file(resource p, double lly, double lly, double urx, double ury, string filename, string description, string author, string mimetype, string icon)
 * Deprecated, use  PDF_create_annotation() instead. */
PHP_FUNCTION(pdf_attach_file)
{
	PDF *pdf;
	double llx, lly, urx, ury;
	char *filename, *description, *author, *mimetype, *icon;
	int flen, dlen, alen, mlen, ilen;
	const char * vfilename;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ddddsssss", &llx, &lly, &urx, &ury,
						&filename, &flen, &description, &dlen, &author, &alen,
						&mimetype, &mlen, &icon, &ilen)) {
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
						"rddddsssss", &p, &llx, &lly, &urx, &ury,
						&filename, &flen, &description, &dlen, &author, &alen,
						&mimetype, &mlen, &icon, &ilen)) {
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
		/* len has to be 0, len only in C */
		PDF_attach_file2(pdf, llx, lly, urx, ury, vfilename, 0,
			description, dlen, author, alen, mimetype, icon);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto int pdf_begin_document(resource p, string filname, string optlist);
 * Create a new PDF file subject to various options. */
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_begin_document)
{
	PDF *pdf;
	char *filename, *optlist;
	int flen = 0;
	int olen = 0;
	long retval = 0;
	const char * vfilename;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ss", &filename, &flen, &optlist, &olen)) {
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
						"rss", &p, &filename, &flen, &optlist, &olen)) {
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
		/* len has to be 0, len only in C */
		retval = PDF_begin_document(pdf, vfilename, 0, optlist);
	} pdf_catch;

	RETURN_LONG(retval); /* change return from -1 to 0 handled by PDFlib */
}
#endif /* PDFlib >= 6.0.0 */

/* }}} */

/* {{{ proto bool pdf_begin_font(string fontname, double a, double b,
    double c, double d, double e, double f, string optlist);
 * Start a Type 3 font definition. */
PHP_FUNCTION(pdf_begin_font)
{
	PDF *pdf;
	char *fontname, *optlist;
	int flen, olen;
	double a, b, c, d, e, f;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"sdddddds", &fontname, &flen, &a, &b,
						&c, &d, &e, &f, &optlist, &olen)) {
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
						"rsdddddds", &p, &fontname, &flen, &a, &b,
						&c, &d, &e, &f, &optlist, &olen)) {
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
		/* has to be 0, len only in C */
		PDF_begin_font(pdf, fontname, 0, a, b, c, d, e, f, optlist);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_begin_glyph(resource p, string glyphname, double wx, double llx, double lly, double urx, double ury)
 * Start a glyph definition for a Type 3 font. */
PHP_FUNCTION(pdf_begin_glyph)
{
	PDF *pdf;
	char *glyphname;
	int glen;
	double wx, llx, lly, urx, ury;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
					"sddddd", &glyphname, &glen, &wx, &llx, &lly, &urx, &ury)) {
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
			"rsddddd", &p, &glyphname, &glen, &wx, &llx, &lly, &urx, &ury)) {
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
		PDF_begin_glyph(pdf, glyphname, wx, llx, lly, urx, ury);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto int pdf_begin_item(resource p, string tag, string optlist)
 * Open a structure element or other content item with attributes supplied as options. */
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_begin_item)
{
	PDF *pdf;
	char *tag, *optlist;
	int tlen, olen;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ss", &tag, &tlen, &optlist, &olen)) {
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
					"rss", &p, &tag, &tlen, &optlist, &olen)) {
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
		retval = PDF_begin_item(pdf, tag, optlist);
	} pdf_catch;

	RETURN_LONG(retval);
}
#endif /* PDFlib >= 6.0.0 */
/* }}} */

/* {{{ proto bool pdf_begin_layer(resource p, int layer)
 * Start a new layer for subsequent output on the page (requires PDF 1.5). */
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_begin_layer)
{
	PDF *pdf;
	long layer;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"l", &layer)) {
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
						"rl", &p, &layer)) {
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
		PDF_begin_layer(pdf, (int)layer);
	} pdf_catch;

	RETURN_TRUE;
}
#endif /* PDFlib >= 6.0.0 */
/* }}} */

/* {{{ proto bool pdf_begin_page(resource p, double width, double height)
 * Deprecated, use PDF_begin_page_ext(). */
PHP_FUNCTION(pdf_begin_page)
{
	PDF *pdf;
	double width, height;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dd", &width, &height)) {
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
						"rdd", &p, &width, &height)) {
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
		PDF_begin_page(pdf, width, height);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_begin_page_ext(resource p, double width, double height, string optlist)
 * Add a new page to the document, and specify various options. */
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_begin_page_ext)
{
	PDF *pdf;
	double width;
	double height;
	char *optlist;
	int olen;
	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
					"dds", &width, &height, &optlist, &olen)) {
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
					"rdds", &p, &width, &height, &optlist, &olen)) {
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
		PDF_begin_page_ext(pdf, width, height, optlist);
	} pdf_catch;

	RETURN_TRUE;
}
#endif
/* }}} */

/* {{{ proto int pdf_begin_pattern(resource p, double width, double height, double xstep, double ystep, int painttype);
 * Start a pattern definition. */
PHP_FUNCTION(pdf_begin_pattern)
{
	PDF *pdf;
	double width, height, xstep, ystep;
	long painttype;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ddddl", &width, &height, &xstep, &ystep, &painttype)) {
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
					"rddddl", &p, &width, &height, &xstep, &ystep, &painttype)) {
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
		retval = PDF_begin_pattern(pdf, width, height, xstep, ystep, (int)painttype);
	} pdf_catch;

	RETURN_LONG(retval); /* offset handled in PDFlib Kernel */
}
/* }}} */

/* {{{ proto int pdf_begin_template(resource p, double width, double height);
 * Start a template definition. */
PHP_FUNCTION(pdf_begin_template)
{
	PDF *pdf;
	double width, height;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dd", &width, &height)) {
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
						"rdd", &p, &width, &height)) {
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
		retval = PDF_begin_template(pdf, width, height);
	} pdf_catch;

	RETURN_LONG(retval); /* offset handled in PDFlib Kernel */
}
/* }}} */

/* {{{ proto bool pdf_circle(resource p, double x, double y, double r)
 * Draw a circle. */
PHP_FUNCTION(pdf_circle)
{
	PDF *pdf;
	double x, y, r;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ddd", &x, &y, &r)) {
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
						"rddd", &p, &x, &y, &r)) {
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
		PDF_circle(pdf, x, y, r);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_clip(int p)
 * Use the current path as clipping path, and terminate the path. */
PHP_FUNCTION(pdf_clip)
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
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		PDF_clip(pdf);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_close(int p)
 * Deprecated, use PDF_end_document(). */
PHP_FUNCTION(pdf_close)
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
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		PDF_close(pdf);
	} pdf_catch;

	RETURN_TRUE;
}

/* }}} */

/* {{{ proto bool pdf_close_image(resource p, int image)
 * Close an image. */
PHP_FUNCTION(pdf_close_image)
{
	PDF *pdf;
	long image;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"l", &image)) {
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
						"rl", &p, &image)) {
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
		PDF_close_image(pdf, (int)image);
	} pdf_catch;
}
/* }}} */

/* {{{ proto bool pdf_close_pdi(resource p, int doc);
 * Close all open page handles, and close the input PDF document. */
PHP_FUNCTION(pdf_close_pdi)
{
	PDF *pdf;
	long doc;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"l", &doc)) {
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
						"rl", &p, &doc)) {
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
		PDF_close_pdi(pdf, (int)doc);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_close_pdi_page(resource p, int page);
 * Close the page handle, and free all page-related resources. */
PHP_FUNCTION(pdf_close_pdi_page)
{
	PDF *pdf;
	long page;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"l", &page)) {
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
						"rl", &p, &page)) {
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
		PDF_close_pdi_page(pdf, (int)page);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_closepath(int p)
 * Close the current path. */
PHP_FUNCTION(pdf_closepath)
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
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		PDF_closepath(pdf);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_closepath_fill_stroke(int p)
 * Close the path, fill, and stroke it. */
PHP_FUNCTION(pdf_closepath_fill_stroke)
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
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		PDF_closepath_fill_stroke(pdf);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_closepath_stroke(int p)
 * Close the path, and stroke it. */
PHP_FUNCTION(pdf_closepath_stroke)
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
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		PDF_closepath_stroke(pdf);
	} pdf_catch;
	
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_concat(resource p, double a, double b, double c, double d, double e, double f)
 * Concatenate a matrix to the current transformation matrix. */
PHP_FUNCTION(pdf_concat)
{
	PDF *pdf;
	double a, b, c, d, e, f;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dddddd", &a, &b, &c, &d, &e, &f)) {
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
						"rdddddd", &p, &a, &b, &c, &d, &e, &f)) {
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
		PDF_concat(pdf, a, b, c, d, e, f);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_continue_text(resource p, string text)
 * Print text at the next line. */
PHP_FUNCTION(pdf_continue_text)
{
	PDF *pdf;
	char *text;
	int tlen;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"s", &text, &tlen)) {
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
						"rs", &p, &text, &tlen)) {
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
		PDF_continue_text2(pdf, text, tlen);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto int pdf_create_action(resource p, string type, string optlist);
 * Create an action which can be applied to various objects and events. */
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_create_action)
{
	PDF *pdf;
	char *type, *optlist;
	int tlen, olen;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ss", &type, &tlen, &optlist, &olen)) {
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
						"rss", &p, &type, &tlen, &optlist, &olen)) {
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
		retval = PDF_create_action(pdf, type, optlist);
	} pdf_catch;

	RETURN_LONG(retval); /* offset handled in PDFlib Kernel */
}
#endif /* PDFlib >= 6.0.0 */
/* }}} */

/* {{{ proto bool pdf_create_annotation(resource p, double llx, double lly, double urx, double ury, string type, string optlist)
 * Create a rectangular annotation on the current page. */
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_create_annotation)
{
	PDF *pdf;
	double llx, lly, urx, ury;
	char *type, *optlist;
	int tlen, olen;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ddddss", &llx, &lly, &urx, &ury,
						&type, &tlen, &optlist, &olen)) {
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
						"rddddss", &p, &llx, &lly, &urx, &ury,
						&type, &tlen, &optlist, &olen)) {
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
		PDF_create_annotation(pdf, llx, lly, urx, ury, type, optlist);
	} pdf_catch;

	RETURN_TRUE;
}
#endif /* PDFlib >= 6.0.0 */
/* }}} */

/* {{{ proto int pdf_create_bookmark(resource p, string text, string optlist)
 * Create a bookmark subject to various options. */
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_create_bookmark)
{
	PDF *pdf;
	char *text, *optlist;
	int tlen, olen;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ss", &text, &tlen, &optlist, &olen)) {
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
						"rss", &p, &text, &tlen, &optlist, &olen)) {
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
		retval = PDF_create_bookmark(pdf, text, tlen, optlist);
	} pdf_catch;

	RETURN_LONG(retval); /* offset handled in PDFlib Kernel */
}
#endif /* PDFlib >= 6.0.0 */
/* }}} */

/* {{{ proto bool pdf_create_field(resource p, double llx, double lly, double urx, double ury, string name, string type, string optlist)
 * Create a form field on the current page subject to various options. */
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_create_field)
{
	PDF *pdf;
	double llx, lly, urx, ury;
	char *name, *type, *optlist;
	int nlen, tlen, olen;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ddddsss", &llx, &lly, &urx, &ury, &name, &nlen,
						&type, &tlen, &optlist, &olen)) {
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
						"rddddsss", &p, &llx, &lly, &urx, &ury, &name, &nlen,
						&type, &tlen, &optlist, &olen)) {
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
		PDF_create_field(pdf, llx, lly, urx, ury, name, nlen, type, optlist);
	} pdf_catch;

	RETURN_TRUE;
}
#endif /* PDFlib >= 6.0.0 */
/* }}} */

/* {{{ proto bool pdf_create_fieldgroup(resource p, string name, string optlist);
 * Create a form field group subject to various options. */
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_create_fieldgroup)
{
	PDF *pdf;
	char *name, *optlist;
	int nlen, olen;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ss", &name, &nlen, &optlist, &olen)) {
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
						"rss", &p, &name, &nlen, &optlist, &olen)) {
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
		PDF_create_fieldgroup(pdf, name, nlen, optlist);
	} pdf_catch;

	RETURN_TRUE
}
#endif /* PDFlib >= 6.0.0 */
/* }}} */

/* {{{ proto int pdf_create_gstate(resource p, string optlist);
 * Create a graphics state object subject to various options. */
PHP_FUNCTION(pdf_create_gstate)
{
	PDF *pdf;
	char *optlist;
	int olen;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"s", &optlist, &olen)) {
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
						"rs", &p, &optlist, &olen)) {
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
		retval = PDF_create_gstate(pdf, optlist);
	} pdf_catch;

	RETURN_LONG(retval); /* offset handled in PDFlib Kernel */
}
/* }}} */

/* {{{ proto bool pdf_create_pvf(resource p, string filename, string data, string optlist);
 * Create a named virtual read-only file from data provided in memory. */
PHP_FUNCTION(pdf_create_pvf)
{
	char *filename, *data, *optlist;
	int flen, dlen, olen;
	PDF *pdf;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
					"sss", &filename, &flen, &data, &dlen, &optlist, &olen)) {
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
				"rsss", &p, &filename, &flen, &data, &dlen, &optlist, &olen)) {
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
		/* has to be 0, len only in C */
		PDF_create_pvf(pdf, filename, 0, data, dlen, optlist);
	} pdf_catch;

	RETURN_TRUE
}
/* }}} */

/* {{{ proto int pdf_create_textflow(resource p, string text, string optlist);
 * Preprocess text for later formatting and create a textflow object. */
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_create_textflow)
{
	PDF *pdf;
	char *text, *optlist;
	int tlen, olen;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ss", &text, &tlen, &optlist, &olen)) {
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
						"rss", &p, &text, &tlen, &optlist, &olen)) {
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
		retval = PDF_create_textflow(pdf, text, tlen, optlist);
	} pdf_catch;

	RETURN_LONG(retval);
}
#endif /* PDFlib >= 6.0.0 */
/* }}} */

/* {{{ proto bool pdf_curveto(resource p, double x1, double y1, double x2, double y2, double x3, double y3)
 * Draw a Bezier curve from the current point, using 3 more control points. */
PHP_FUNCTION(pdf_curveto)
{
	double x1, y1, x2, y2, x3, y3;
	PDF *pdf;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dddddd", &x1, &y1, &x2, &y2, &x3, &y3)) {
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
						"rdddddd", &p, &x1, &y1, &x2, &y2, &x3, &y3)) {
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
		PDF_curveto(pdf, x1, y1, x2, y2, x3, y3);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_define_layer(resource p, string name, string optlist);
 * Create a new layer definition (requires PDF 1.5). */
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_define_layer)
{
	PDF *pdf;
	char *name, *optlist;
	int nlen, olen;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ss", &name, &nlen, &optlist, &olen)) {
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
						"rss", &p, &name, &nlen, &optlist, &olen)) {
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
		retval = PDF_define_layer(pdf, name, nlen, optlist);
	} pdf_catch;

	RETURN_LONG(retval);
}
#endif /* PDFlib >= 6.0.0 */
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

/* {{{ proto int pdf_delete_pvf(resource p, string filname);
 * Delete a named virtual file and free its data structures (but not the contents).*/
PHP_FUNCTION(pdf_delete_pvf)
{
	PDF *pdf;
	char *filename;
	int flen;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"s", &filename, &flen)) {
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
						"rs", &p, &filename, &flen)) {
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
		/* len only in c allowed */
		retval = PDF_delete_pvf(pdf, filename, 0);
	} pdf_catch;

	RETURN_LONG(retval); /* change return from -1 to 0 handled by PDFlib */
}
/* }}} */

/* {{{ proto bool pdf_delete_textflow(resource p, int textflow);
 * Delete a textflow and the associated data structures. */
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_delete_textflow)
{
	PDF *pdf;
	long textflow;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"l", &textflow)) {
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
						"rl", &p, &textflow)) {
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
		PDF_delete_textflow(pdf, (int)textflow);
	} pdf_catch;

	RETURN_TRUE;
}
#endif /* PDFlib >= 6.0.0 */
/* }}} */

/* {{{ proto bool pdf_encoding_set_char(resource p, string encoding, int slot, string glyphname, int uv);
 * Add a glyph name and/or Unicode value to a custom encoding. */
PHP_FUNCTION(pdf_encoding_set_char)
{
	PDF *pdf;
	char *encoding, *glyphname;
	int elen, glen;
	long slot, uv;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
					"slsl", &encoding, &elen, &slot, &glyphname, &glen, &uv)) {
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
				"rslsl", &p, &encoding, &elen, &slot, &glyphname, &glen, &uv)) {
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
		PDF_encoding_set_char(pdf, encoding, (int)slot, glyphname, (int)uv);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_end_document(resource p, string optlist)
 * Close the generated PDF file and apply various options. */
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_end_document)
{
	PDF *pdf;
	char *optlist;
	int olen;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"s", &optlist, &olen)) {
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
						"rs", &p, &optlist, &olen)) {
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
		PDF_end_document(pdf, optlist);
	} pdf_catch;

	RETURN_TRUE;
}
#endif /* PDFlib >= 6.0.0 */
/* }}} */

/* {{{ proto bool pdf_end_font(int p);
 * Terminate a type 3 font definition. */
PHP_FUNCTION(pdf_end_font)
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
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		PDF_end_font(pdf);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_end_glyph(int p);
 * Terminate a glyph definition for a Type 3 font. */
PHP_FUNCTION(pdf_end_glyph)
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
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		PDF_end_glyph(pdf);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_end_item(resource p, int id);
 * Close a structure element or other content item. */
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_end_item)
{
	PDF *pdf;
	long id;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"l", &id)) {
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
						"rl", &p, &id)) {
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
		PDF_end_item(pdf, (int)id);
	} pdf_catch;

	RETURN_TRUE;
}
#endif /* PDFlib >= 6.0.0 */
/* }}} */

/* {{{ proto bool pdf_end_layer(int p);
 * Deactivate all active layers (requires PDF 1.5). */
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_end_layer)
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
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		PDF_end_layer(pdf);
	} pdf_catch;

	RETURN_TRUE;
}
#endif /* PDFlib >= 6.0.0 */
/* }}} */

/* {{{ proto bool pdf_end_page(int p)
 * Deprecated, use PDF_end_page_ext(). */
PHP_FUNCTION(pdf_end_page)
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
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		PDF_end_page(pdf);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_end_page_ext(resource p, string optlist)
 * Finish a page, and apply various options. */
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_end_page_ext)
{
	PDF *pdf;
	char *optlist;
	int olen;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"s", &optlist, &olen)) {
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
						"rs", &p, &optlist, &olen)) {
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
		PDF_end_page_ext(pdf, optlist);
	} pdf_catch;

	RETURN_TRUE;
}
#endif /* PDFlib >= 6.0.0 */
/* }}} */

/* {{{ proto bool pdf_end_pattern(int p);
 * Finish a pattern definition. */
PHP_FUNCTION(pdf_end_pattern)
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
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		PDF_end_pattern(pdf);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_end_template(int p);
 * Finish a template definition. */
PHP_FUNCTION(pdf_end_template)
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
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		PDF_end_template(pdf);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_endpath(int p)
 *  End the current path without filling or stroking it. */
PHP_FUNCTION(pdf_endpath)
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
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		PDF_endpath(pdf);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_fill(int p)
 * Fill the interior of the path with the current fill color. */
PHP_FUNCTION(pdf_fill)
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
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		PDF_fill(pdf);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto int pdf_fill_imageblock(resource p, int page, string blockname, int image, string optlist);
 * Fill an image block with variable data according to its properties. */
PHP_FUNCTION(pdf_fill_imageblock)
{
	PDF *pdf;
	long page, image;
	int blen, olen;
	char *blockname, *optlist;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
				"lsls", &page, &blockname, &blen, &image, &optlist, &olen)) {
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
			"rlsls", &p, &page, &blockname, &blen, &image, &optlist, &olen)) {
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
		retval = PDF_fill_imageblock(pdf, (int)page, blockname, (int)image, optlist);
	} pdf_catch;

	RETURN_LONG(retval); /* change return from -1 to 0 handled by PDFlib */
}
/* }}} */

/* {{{ proto int pdf_fill_pdfblock(resource p, int page, string blockname, int contents, string optlist);
 * Fill a PDF block with variable data according to its properties. */
PHP_FUNCTION(pdf_fill_pdfblock)
{
	PDF *pdf;
	long page, contents;
	int blen, olen;
	char *blockname, *optlist;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
				"lsls", &page, &blockname, &blen, &contents, &optlist, &olen)) {
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
			"rlsls", &p, &page, &blockname, &blen, &contents, &optlist, &olen)){
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
		retval = PDF_fill_pdfblock(pdf, (int)page, blockname, (int)contents, optlist);
	} pdf_catch;

	RETURN_LONG(retval); /* change return from -1 to 0 handled by PDFlib */
}
/* }}} */

/* {{{ proto bool pdf_fill_stroke(int p)
 * Fill and stroke the path with the current fill and stroke color. */
PHP_FUNCTION(pdf_fill_stroke)
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
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		PDF_fill_stroke(pdf);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto int pdf_fill_textblock(resource p, int page, string spotname, string text, string optlist);
 * Fill a text block with variable data according to its properties. */
PHP_FUNCTION(pdf_fill_textblock)
{
	PDF *pdf;
	long page;
	int blen, tlen, olen;
	char *blockname, *text, *optlist;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
			"lsss", &page, &blockname, &blen, &text, &tlen, &optlist, &olen)) {
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
		"rlsss", &p, &page, &blockname, &blen, &text, &tlen, &optlist, &olen)) {
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
		retval = PDF_fill_textblock(pdf, (int)page, blockname, text, tlen, optlist);
	} pdf_catch;

	RETURN_LONG(retval); /* change return from -1 to 0 handled by PDFlib */
}
/* }}} */

/* {{{ proto int pdf_findfont(resource p, string fontname, string encoding, int embed)
 * Deprecated, use  PDF_load_font().*/
PHP_FUNCTION(pdf_findfont)
{
	PDF *pdf;
	char *fontname, *encoding;
	int flen, elen;
	long embed;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ssl", &fontname, &flen, &encoding, &elen, &embed)) {
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
					"rssl", &p, &fontname, &flen, &encoding, &elen, &embed)) {
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
		retval = PDF_findfont(pdf, fontname, encoding, (int)embed);
	} pdf_catch;

	RETURN_LONG(retval); /* offset handled in PDFlib Kernel */
}
/* }}} */

/* {{{ proto bool pdf_fit_image(resource p, int image, double x, double y, string optlist);
 * Place an image or template at on the page, subject to various options. */
PHP_FUNCTION(pdf_fit_image)
{
	PDF *pdf;
	long image;
	int olen;
	double x, y;
	char *optlist;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ldds", &image, &x, &y, &optlist, &olen)) {
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
						"rldds", &p, &image, &x, &y, &optlist, &olen)) {
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
		PDF_fit_image(pdf, (int)image, x, y, optlist);
	} pdf_catch;

	RETURN_TRUE
}
/* }}} */

/* {{{ proto bool pdf_fit_pdi_page(resource p, int page, double x, double y, string optlist);
 * Place an imported PDF page on the page subject to various options. */
PHP_FUNCTION(pdf_fit_pdi_page)
{
	PDF *pdf;
	long page;
	int olen;
	char *optlist;
	double x, y;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ldds", &page, &x, &y, &optlist, &olen)) {
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
						"rldds", &p, &page, &x, &y, &optlist, &olen)) {
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
		PDF_fit_pdi_page(pdf, (int)page, x, y, optlist);
	} pdf_catch;

	RETURN_TRUE
}
/* }}} */

/* {{{ proto string pdf_fit_textflow(resource p, int textflow, double llx, double lly, double urx, double ury, string optlist)
 * Format the next portion of a textflow into a rectangular area. */
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_fit_textflow)
{
	PDF *pdf;
	long textflow;
	int olen;
	double llx, lly, urx, ury;
	char *optlist;
	const char *retbuf = NULL;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
				"ldddds", &textflow, &llx, &lly, &urx, &ury, &optlist, &olen)) {
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
		"rldddds", &p, &textflow, &llx, &lly, &urx, &ury, &optlist, &olen)) {
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
		retbuf = PDF_fit_textflow(pdf, (int)textflow, llx, lly, urx, ury, optlist);
	} pdf_catch;

	RETURN_STRING(retbuf ? (char *)retbuf : "", 1);
}
#endif /* PDFlib >= 6.0.0 */
/* }}} */

/* {{{ proto bool pdf_fit_textline(resource p, string text, double x, double y, string optlist);
 * Place a single line of text at position (x, y) subject to various options. */
PHP_FUNCTION(pdf_fit_textline)
{
	PDF *pdf;
	char *text, *optlist;
	int tlen, olen;
	double x, y;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"sdds", &text, &tlen, &x, &y, &optlist, &olen)) {
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
						"rsdds", &p, &text, &tlen, &x, &y, &optlist, &olen)) {
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
		PDF_fit_textline(pdf, text, tlen, x, y, optlist);
	} pdf_catch;

	RETURN_TRUE
}
/* }}} */

/* {{{ proto int pdf_get_apiname(int p);
 * Get the name of the API function which threw the last exception or failed. */
PHP_FUNCTION(pdf_get_apiname)
{
	PDF *pdf;
	const char *retbuf = NULL;

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
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */


	pdf_try {
        retbuf = PDF_get_apiname(pdf);
	} pdf_catch;

	RETURN_STRING(retbuf ? (char *)retbuf : "", 1);
}
/* }}} */

/* {{{ proto int pdf_get_buffer(int p)
 * Get the contents of the PDF output buffer. */
PHP_FUNCTION(pdf_get_buffer)
{
	long size;
	PDF *pdf;
	const char *retbuf = NULL;

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
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		retbuf = PDF_get_buffer(pdf, &size);
	} pdf_catch;

	RETURN_STRINGL(retbuf ? (char *)retbuf : "", size, 1);
}

/* }}} */

/* {{{ proto int pdf_get_errmsg(int p);
 * Get the descriptive text of the last thrown exception or the reason of
  a failed function call.*/
PHP_FUNCTION(pdf_get_errmsg)
{
	PDF *pdf;
	const char *retbuf = NULL;

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
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
        retbuf = PDF_get_errmsg(pdf);
	} pdf_catch;

	RETURN_STRING(retbuf ? (char *)retbuf : "", 1);
}
/* }}} */

/* {{{ proto int pdf_get_errnum(int p);
 * Get the number of the last thrown exception or the reason of a failed
  function call. */
PHP_FUNCTION(pdf_get_errnum)
{
	PDF *pdf;
	long retval = 0;

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
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		retval = PDF_get_errnum(pdf);
	} pdf_catch;

	RETURN_LONG(retval);
}
/* }}} */

/* {{{ proto string pdf_get_parameter(resource p, string key, double modifier)
 * Get the contents of some PDFlib parameter with string type. */
PHP_FUNCTION(pdf_get_parameter)
{
	PDF *pdf;
	char *key;
	double modifier;
	char *retbuf = NULL;


	#if PHP_MAJOR_VERSION >= 5
	int klen;
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"sd", &key, &klen, &modifier)) {
			php_std_error_handling();
			return;
		}
		P_FROM_OBJECT(pdf, object);
	} else {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
	#endif /* PHP_MAJOR_VERSION >= 5 */
		{
			zval *p;
			zval **argv[3];
			int argc = ZEND_NUM_ARGS();

			if((argc != 3) ||
						zend_get_parameters_array_ex(argc, argv) == FAILURE) {
			        WRONG_PARAM_COUNT;
	#if PHP_MAJOR_VERSION >= 5
					php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */
					return;
			}

			convert_to_string_ex(argv[1]);
			key = Z_STRVAL_PP(argv[1]);
			if(0 == (strcmp(key, "version"))) {
				retbuf = (char *)PDF_get_parameter(0, key, 0);
	#if PHP_MAJOR_VERSION >= 5
				php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */
				RETURN_STRING(retbuf ? (char *)retbuf : "", 1);
			} else if(0 == (strcmp(key, "pdi"))) {
				retbuf = (char *)PDF_get_parameter(0, key, 0);
	#if PHP_MAJOR_VERSION >= 5
				php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */
				RETURN_STRING(retbuf ? (char *)retbuf : "", 1);
			} else {
				ZEND_FETCH_RESOURCE(pdf, PDF *, argv[0], -1,
						"pdf object", le_pdf);
			}
			convert_to_double_ex(argv[2]);
			modifier = Z_DVAL_PP(argv[2]);
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		retbuf = (char *)PDF_get_parameter(pdf, key, modifier);
	} pdf_catch;

	RETURN_STRING(retbuf ? (char *)retbuf : "", 1);
}
/* }}} */

/* {{{ proto string pdf_get_pdi_parameter(resource p, string key, int doc, int page, int reserved);
 * Get some PDI document parameter with string type. */
PHP_FUNCTION(pdf_get_pdi_parameter)
{
	PDF *pdf;
	char *key;
	long doc, page, reserved;
	int klen;
	const char *retbuf = NULL;
	int size;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"slll", &key, &klen, &doc, &page, &reserved)) {
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
						"rslll", &p, &key, &klen, &doc, &page, &reserved)) {
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
		retbuf = PDF_get_pdi_parameter(pdf, key, (int)doc, (int)page, (int)reserved, &size);
	} pdf_catch;

	RETURN_STRING(retbuf ? (char *)retbuf : "", 1);
}
/* }}} */

/* {{{ proto double pdf_get_pdi_value(resource p, string key, int doc, int page, int reserved);
 * Get some PDI document parameter with numerical type. */
PHP_FUNCTION(pdf_get_pdi_value)
{
	PDF *pdf;
	char *key;
	int klen;
	long doc, page, reserved;
	double retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"slll", &key, &klen, &doc, &page, &reserved)) {
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
						"rslll", &p, &key, &klen, &doc, &page, &reserved)) {
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
		retval = PDF_get_pdi_value(pdf, key, (int)doc, (int)page, (int)reserved);
	} pdf_catch;

	RETURN_DOUBLE(retval);
}
/* }}} */

/* {{{ proto double pdf_get_value(resource p, string key, double modifier)
 * Get the value of some PDFlib parameter with numerical type. */
PHP_FUNCTION(pdf_get_value)
{
	PDF *pdf;
	char *key;
	int klen;
	double modifier;
	double retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"sd", &key, &klen, &modifier)) {
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
						"rsd", &p, &key, &klen, &modifier)) {
	#if PHP_MAJOR_VERSION >= 5
				php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */
				return;
			}
	#if PHP_MAJOR_VERSION >= 5
			php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */
			if(0 == (strcmp(key, "major"))) {
				retval = PDF_get_value(0, key, 0);
				RETURN_DOUBLE(retval);
			} else if(0 == (strcmp(key, "minor"))) {
				retval = PDF_get_value(0, key, 0);
				RETURN_DOUBLE(retval);
			} else if(0 == (strcmp(key, "revision"))) {
				retval = PDF_get_value(0, key, 0);
				RETURN_DOUBLE(retval);
			}
			ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		retval = PDF_get_value(pdf, key, modifier);
	} pdf_catch;

	RETURN_DOUBLE(retval);
}
/* }}} */

/* {{{ proto double pdf_info_textflow(resource p, int textflow, string keyword);
 * Query the current state of a textflow. */
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_info_textflow)
{
	PDF *pdf;
	char *keyword;
	long textflow;
	int klen;
	double retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ls", &textflow, &keyword, &klen)) {
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
						"rls", &p, &textflow, &keyword, &klen)) {
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
		retval = PDF_info_textflow(pdf, (int)textflow, keyword);
	} pdf_catch;

	RETURN_DOUBLE(retval);
}
#endif /* PDFlib >= 6.0.0 */
/* }}} */

/* {{{ proto bool pdf_initgraphics(int p);
 * Reset all color and graphics state parameters to their defaults. */
PHP_FUNCTION(pdf_initgraphics)
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
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		PDF_initgraphics(pdf);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_lineto(resource p, double x, double y)
 * Draw a line from the current point to another point. */
PHP_FUNCTION(pdf_lineto)
{
	PDF *pdf;
	double x, y;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dd", &x, &y)) {
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
						"rdd", &p, &x, &y)) {
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
		PDF_lineto(pdf, x, y);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto int pdf_load_font(resource p, string fontname, string encoding, string optlist);
 * Search for a font and prepare it for later use. */
PHP_FUNCTION(pdf_load_font)
{
	PDF *pdf;
	char *fontname, *encoding, *optlist;
	int flen, elen, olen;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
				"sss", &fontname, &flen, &encoding, &elen, &optlist, &olen)) {
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
			"rsss", &p, &fontname, &flen, &encoding, &elen, &optlist, &olen)) {
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
		/* len has to be 0, len only in C */
		retval = PDF_load_font(pdf, fontname, 0, encoding, optlist);
	} pdf_catch;

	RETURN_LONG(retval); /* offset handled in PDFlib Kernel */
}
/* }}} */

/* {{{ proto int pdf_load_iccprofile(resource p, string profilename, string optlist);
 * Search for an ICC profile, and prepare it for later use. */
PHP_FUNCTION(pdf_load_iccprofile)
{
	PDF *pdf;
	char *profilename, *optlist;
	int plen, olen;
	char * vprofilename;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ss", &profilename, &plen, &optlist, &olen)) {
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
						"rss", &p, &profilename, &plen, &optlist, &olen)) {
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
	virtual_filepath(profilename, &vprofilename TSRMLS_CC);
#else /* !VIRTUAL_DIR */
	vprofilename = profilename;
#endif /* VIRTUAL_DIR */

#ifdef PDFLIB_CHECK_OPEN_BASEDIR
	if (php_check_open_basedir(vfilename TSRMLS_CC) || (PG(safe_mode) && !php_checkuid(vfilename, "rb+", CHECKUID_CHECK_MODE_PARAM))) {
		RETURN_FALSE;
	}
#endif /* PDFLIB_CHECK_OPEN_BASEDIR */

	pdf_try {
		/* len has to be 0, len only in C */
		retval = PDF_load_iccprofile(pdf, vprofilename, 0, optlist);
	} pdf_catch;

	RETURN_LONG(retval); /* offset handled in PDFlib Kernel */
}
/* }}} */

/* {{{ proto int pdf_load_image(resource p, string imagetype, string filename, string optlist);
 * Open a disk-based or virtual image file subject to various options. */
PHP_FUNCTION(pdf_load_image)
{
	PDF *pdf;
	char *imagetype, *filename, *optlist;
	int ilen, flen, olen;
	const char *vfilename;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
				"sss", &imagetype, &ilen, &filename, &flen, &optlist, &olen)) {
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
			"rsss", &p, &imagetype, &ilen, &filename, &flen, &optlist, &olen)) {
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
		/* has to be 0, len only in C */
		retval = PDF_load_image(pdf, imagetype, vfilename, 0, optlist);
	} pdf_catch;

	RETURN_LONG(retval); /* offset handled in PDFlib Kernel */
}
/* }}} */

/* {{{ proto int pdf_makespotcolor(resource p, string spotname);
 * Find a built-in spot color name, or make a named spot color from the
  current fill color. */
PHP_FUNCTION(pdf_makespotcolor)
{
	PDF *pdf;
	char *spotname;
	int slen;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"s", &spotname, &slen)) {
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
						"rs", &p, &spotname, &slen)) {
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
		/* len has to be 0, len only in C */
		retval = PDF_makespotcolor(pdf, spotname, 0);
	} pdf_catch;

	RETURN_LONG(retval); /* offset handled in PDFlib Kernel */
}
/* }}} */

/* {{{ proto bool pdf_moveto(resource p, double x, double y)
 * Set the current point. */
PHP_FUNCTION(pdf_moveto)
{
	PDF *pdf;
	double x, y;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dd", &x, &y)) {
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
						"rdd", &p, &x, &y)) {
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
		PDF_moveto(pdf, x, y);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto int pdf_new()
 * Create a new PDFlib object with default settings. */
PHP_FUNCTION(pdf_new)
{
	PDF *pdf;
	zval *object = getThis();
#if PHP_MAJOR_VERSION >= 5
	pdflib_object *intern;
#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf = PDF_new2(NULL, pdf_emalloc, pdf_realloc, pdf_efree, NULL);

	if (pdf != NULL) {
		pdf_try {
			PDF_set_parameter(pdf, "imagewarning", "true");
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

/* {{{ proto int pdf_open_ccitt(resource p, string filename, int width, int height, int bitreverse, int k, int blackls1)
 * Deprecated, use PDF_load_image(). */
PHP_FUNCTION(pdf_open_ccitt)
{
	PDF *pdf;
	char *filename;
	int flen;
	long width, height, bitreverse, k, blackis1;
	char *vfilename;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
					"slllll", &filename, &flen, &width, &height,
					&bitreverse, &k, &blackis1)) {
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
					"rslllll", &p, &filename, &flen, &width, &height,
					&bitreverse, &k, &blackis1)) {
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
		retval = PDF_open_CCITT(pdf, vfilename, (int)width, (int)height,
				(int)bitreverse, (int)k, (int)blackis1);
	} pdf_catch;

	RETURN_LONG(retval); /* offset handled in PDFlib Kernel */
}
/* }}} */

/* {{{ proto int pdf_open_file(resource p, char filename)
 * Deprecated, use PDF_begin_document(). */
PHP_FUNCTION(pdf_open_file)
{
	PDF *pdf;
	char *filename;
	int flen;
	const char *vfilename;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"s", &filename, &flen)) {
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
						"rs", &p, &filename, &flen)) {
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
	if (flen) {
		virtual_filepath(filename, &vfilename TSRMLS_CC);
	} else {
		vfilename = filename;
	}
#else /* !VIRTUAL_DIR */
	vfilename = filename;
#endif /* VIRTUAL_DIR */

#ifdef PDFLIB_CHECK_OPEN_BASEDIR
	if (php_check_open_basedir(vfilename TSRMLS_CC) || (PG(safe_mode) && !php_checkuid(vfilename, "rb+", CHECKUID_CHECK_MODE_PARAM))) {
		RETURN_FALSE;
	}
#endif /* PDFLIB_CHECK_OPEN_BASEDIR */

	pdf_try {
		retval = PDF_open_file(pdf, vfilename);
	} pdf_catch;

	RETURN_LONG(retval); /* change return from -1 to 0 handled by PDFlib */
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

/* {{{ proto int pdf_open_image_file(resource p, string imagetype, string filename, string stringparam, int intparam)
 * Deprecated, use PDF_load_image(). */
PHP_FUNCTION(pdf_open_image_file)
{
	PDF *pdf;
	char *imagetype, *filename, *stringparam;
	int ilen, flen, slen;
	long intparam;
	const char *vfilename;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"sssl", &imagetype, &ilen, &filename, &flen,
						&stringparam, &slen, &intparam)) {
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
						"rsssl", &p, &imagetype, &ilen, &filename, &flen,
						&stringparam, &slen, &intparam)) {
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
		retval = PDF_open_image_file(pdf, imagetype, vfilename, stringparam,
					(int)intparam);
	} pdf_catch;

	RETURN_LONG(retval); /* offset handled in PDFlib Kernel */

}
/* }}} */

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

/* {{{ proto int pdf_open_pdi_page(resource p, int doc, int pagenumber, string optlist);
 * Prepare a page for later use with PDF_fit_pdi_page(). */
PHP_FUNCTION(pdf_open_pdi_page)
{
	PDF *pdf;
	long doc, pagenumber;
	int olen;
	char *optlist;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"lls", &doc, &pagenumber, &optlist, &olen)) {
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
						"rlls", &p, &doc, &pagenumber, &optlist, &olen)) {
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
		retval = PDF_open_pdi_page(pdf, (int)doc, (int)pagenumber, optlist);
	} pdf_catch;

	RETURN_LONG(retval); /* offset handled in PDFlib Kernel */
}
/* }}} */

/* {{{ proto bool pdf_place_image(resource p, int image, double x, double y, double scale)
 * Deprecated, use PDF_fit_image(). */
PHP_FUNCTION(pdf_place_image)
{
	PDF *pdf;
	long image;
	double x, y, scale;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"lddd", &image, &x, &y, &scale)) {
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
						"rlddd", &p, &image, &x, &y, &scale)) {
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
		PDF_place_image(pdf, (int)image, x, y, scale);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_place_pdi_page(resource p, int page, double x, double y, double sx, double sy)
 * Deprecated, use PDF_fit_pdi_page(). */
PHP_FUNCTION(pdf_place_pdi_page)
{
	PDF *pdf;
	long page;
	double x, y, sx, sy;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ldddd", &page, &x, &y, &sx, &sy)) {
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
						"rldddd", &p, &page, &x, &y, &sx, &sy)) {
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
		PDF_place_pdi_page(pdf, (int)page, x, y, sx, sy);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto int pdf_process_pdi(resource p, int doc, int page, string optlist);
 * Process certain elements of an imported PDF document. */
PHP_FUNCTION(pdf_process_pdi)
{
	PDF *pdf;
	long doc, page;
	int olen;
	char *optlist;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"lls", &doc, &page, &optlist, &olen)) {
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
						"rlls", &p, &doc, &page, &optlist, &olen)) {
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
		retval = PDF_process_pdi(pdf, (int)doc, (int)page, optlist);
	} pdf_catch;

	RETURN_LONG(retval); /* offset handled in PDFlib Kernel */
}
/* }}} */

/* {{{ proto bool pdf_rect(resource p, double x, double y, double width, double height)
 * Draw a rectangle. */
PHP_FUNCTION(pdf_rect)
{
	PDF *pdf;
	double x, y, width, height;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dddd", &x, &y, &width, &height)) {
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
						"rdddd", &p, &x, &y, &width, &height)) {
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
		PDF_rect(pdf, x, y, width, height);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_restore(int p)
 * Restore the most recently saved graphics state from the stack. */
PHP_FUNCTION(pdf_restore)
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
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */
	
	pdf_try {
		PDF_restore(pdf);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_resume_page(resource p, string optlist);
 * Resume a page to add more content to it. */
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_resume_page)
{
	PDF *pdf;
	char *optlist;
	int olen;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"s", &optlist, &olen)) {
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
						"rs", &p, &optlist, &olen)) {
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
		PDF_resume_page(pdf, optlist);
	} pdf_catch;

	RETURN_TRUE;
}
#endif /* PDFlib >= 6.0.0 */
/* }}} */

/* {{{ proto bool pdf_rotate(resource p, double angle)
 * Rotate the coordinate system. */
PHP_FUNCTION(pdf_rotate)
{
	PDF *pdf;
	double angle;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"d", &angle)) {
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
						"rd", &p, &angle)) {
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
		PDF_rotate(pdf, angle);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_save(int p)
 * Save the current graphics state to a stack. */
PHP_FUNCTION(pdf_save)
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
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		PDF_save(pdf);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_scale(resource p, double sx, double sy)
 * Scale the coordinate system. */
PHP_FUNCTION(pdf_scale)
{
	PDF *pdf;
	double sx, sy;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dd", &sx, &sy)) {
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
						"rdd", &p, &sx, &sy)) {
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
		PDF_scale(pdf, sx, sy);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_set_border_color(resource p, double red, double green, double blue)
 * Deprecated, use PDF_create_annotation(). */
PHP_FUNCTION(pdf_set_border_color)
{
	PDF *pdf;
	double red, green, blue;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ddd", &red, &green, &blue)) {
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
						"rddd", &p, &red, &green, &blue)) {
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
		PDF_set_border_color(pdf, red, green, blue);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_set_border_dash(resource p, double b, double w)
 * Deprecated, use PDF_create_annotation(). */
PHP_FUNCTION(pdf_set_border_dash)
{
	PDF *pdf;
	double b, w;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dd", &b, &w)) {
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
						"rdd", &p, &b, &w)) {
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
		PDF_set_border_dash(pdf, b, w);
	} pdf_catch;
	
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_set_border_style(resource p, string style, double width)
 * Deprecated, use PDF_create_annotation(). */
PHP_FUNCTION(pdf_set_border_style)
{
	PDF *pdf;
	char *style;
	int slen;
	double width;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"sd", &style, &slen, &width)) {
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
						"rsd", &p, &style, &slen, &width)) {
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
		PDF_set_border_style(pdf, style, width);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_set_gstate(resource p, int gstate);
 * Activate a gstate object. */
PHP_FUNCTION(pdf_set_gstate)
{
	PDF *pdf;
	long gstate;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"l", &gstate)) {
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
						"rl", &p, &gstate)) {
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
		PDF_set_gstate(pdf, (int)gstate);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_set_info(resource p, string key, string value)
 * Fill document information field key with value. */
PHP_FUNCTION(pdf_set_info)
{
	PDF *pdf;
	char *key, *value;
	int klen, vlen;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ss", &key, &klen, &value, &vlen)) {
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
						"rss", &p, &key, &klen, &value, &vlen)) {
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
		PDF_set_info2(pdf, key, value, vlen);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_set_layer_dependency(resource p, string type, string optlist);
 * Define hierarchical and group relationships among layers (requires
  PDF 1.5).*/
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_set_layer_dependency)
{
	PDF *pdf;
	char *type, *optlist;
	int tlen, olen;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ss", &type, &tlen, &optlist, &olen)) {
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
						"rss", &p, &type, &tlen, &optlist, &olen)) {
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
		PDF_set_layer_dependency(pdf, type, optlist);
	} pdf_catch;

	RETURN_TRUE
}
#endif /* PDFlib >= 6.0.0 */
/* }}} */

/* {{{ proto bool pdf_set_parameter(resource p, string key, string value)
 *  Set some PDFlib parameter with string type. */
PHP_FUNCTION(pdf_set_parameter)
{
	PDF *pdf;
	char *key, *value;
	int klen, vlen;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ss", &key, &klen, &value, &vlen)) {
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
						"rss", &p, &key, &klen, &value, &vlen)) {
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
		PDF_set_parameter(pdf, key, value);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_set_text_pos(resource p, double x, double y)
 * Set the position for text output on the page. */
PHP_FUNCTION(pdf_set_text_pos)
{
	double x, y;
	PDF *pdf;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dd", &x, &y)) {
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
						"rdd", &p, &x, &y)) {
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
		PDF_set_text_pos(pdf, x, y);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_set_value(resource p, string key, double value)
 * Set the value of some PDFlib parameter with numerical type. */
PHP_FUNCTION(pdf_set_value)
{
	PDF *pdf;
	char *key;
	int klen;
	double value;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"sd", &key, &klen, &value)) {
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
						"rsd", &p, &key, &klen, &value)) {
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
		PDF_set_value(pdf, key, value);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_setcolor(resource p, string fstype, string colorspace, double c1, double c2, double c3, double c4);
 * Set the current color space and color.*/
PHP_FUNCTION(pdf_setcolor)
{
	PDF *pdf;
	char *fstype, *colorspace;
	int flen, clen;
	double c1, c2, c3, c4;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ssdddd", &fstype, &flen, &colorspace, &clen,
						&c1, &c2, &c3, &c4)) {
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
						"rssdddd", &p, &fstype, &flen, &colorspace, &clen,
						&c1, &c2, &c3, &c4)) {
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
		PDF_setcolor(pdf, fstype, colorspace, c1, c2, c3,  c4);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_setdash(resource p, double b, double w)
 * Set the current dash pattern. */
PHP_FUNCTION(pdf_setdash)
{
	PDF *pdf;
	double b, w;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dd", &b, &w)) {
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
						"rdd", &p, &b, &w)) {
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
		PDF_setdash(pdf, b, w);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_setdashpattern(resource p, string optlist)
 * Set a dash pattern defined by an option list. */
PHP_FUNCTION(pdf_setdashpattern)
{
	PDF *pdf;
	char *optlist;
	int olen;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"s", &optlist, &olen)) {
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
						"rs", &p, &optlist, &olen)) {
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
		PDF_setdashpattern(pdf, optlist);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_setflat(resource p, double flatness)
 * Set the flatness parameter. */
PHP_FUNCTION(pdf_setflat)
{
	PDF *pdf;
	double flatness;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"d", &flatness)) {
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
						"rd", &p, &flatness)) {
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
		PDF_setflat(pdf, flatness);
	} pdf_catch;
	
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_setfont(resource p, int font, double fontsize)
 * Set the current font in the specified size. */
PHP_FUNCTION(pdf_setfont)
{
	long font;
	double fontsize;
	PDF *pdf;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ld", &font, &fontsize)) {
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
						"rld", &p, &font, &fontsize)) {
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
		PDF_setfont(pdf, (int)font, fontsize);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_setlinecap(resource p, int linecap)
 * Set the linecap parameter. */
PHP_FUNCTION(pdf_setlinecap)
{
	PDF *pdf;
	long linecap;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"l", &linecap)) {
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
						"rl", &p, &linecap)) {
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
		PDF_setlinecap(pdf, (int)linecap);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_setlinejoin(resource p, int linejoin)
 * Set the linejoin parameter. */
PHP_FUNCTION(pdf_setlinejoin)
{
	PDF *pdf;
	long linejoin;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"l", &linejoin)) {
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
						"rl", &p, &linejoin)) {
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
		PDF_setlinejoin(pdf, (int)linejoin);
	} pdf_catch;
	
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_setlinewidth(resource p, double width)
 * Set the current linewidth. */
PHP_FUNCTION(pdf_setlinewidth)
{
	PDF *pdf;
	double width;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"d", &width)) {
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
						"rd", &p, &width)) {
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
		PDF_setlinewidth(pdf, width);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_setmatrix(resource p, double a, double b, double c, double d, double e, double f)
 * Explicitly set the current transformation matrix. */
PHP_FUNCTION(pdf_setmatrix)
{
	PDF *pdf;
	double a, b, c, d, e, f;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dddddd", &a, &b, &c, &d, &e, &f)) {
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
						"rdddddd", &p, &a, &b, &c, &d, &e, &f)) {
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
		PDF_setmatrix(pdf, a, b, c, d, e, f);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_setmiterlimit(resource p, double miter)
 * Set the miter limit. */
PHP_FUNCTION(pdf_setmiterlimit)
{
	PDF *pdf;
	double miter;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"d", &miter)) {
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
						"rd", &p, &miter)) {
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
		PDF_setmiterlimit(pdf, miter);
	} pdf_catch;

	RETURN_TRUE;
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

/* {{{ proto int pdf_shading(resource p, string type, double x0, double y0, double x1, double y1, double c1, double c2, double c3, double c4, string optlist);
 * Define a blend from the current fill color to another color (requires
  PDF 1.4 or above). */
PHP_FUNCTION(pdf_shading)
{
	PDF *pdf;
	char *type, *optlist;
	int tlen, olen;
	double x0, y0, x1, y1, c1, c2, c3, c4;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"sdddddddds", &type, &tlen, &x0, &y0, &x1, &y1,
						&c1, &c2, &c3, &c4, &optlist, &olen)) {
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
						"rsdddddddds", &p, &type, &tlen, &x0, &y0, &x1, &y1,
						&c1, &c2, &c3, &c4, &optlist, &olen)) {
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
		retval = PDF_shading(pdf, type, x0, y0, x1, y1, c1, c2, c3,
				c4, optlist);
	} pdf_catch;

	RETURN_LONG(retval); /* offset handled in PDFlib Kernel */
}
/* }}} */

/* {{{ proto int pdf_shading_pattern(resource p, int shading, string optlist);
 * Define a shading pattern using a shading object (requires PDF 1.4 or
  above). */
PHP_FUNCTION(pdf_shading_pattern)
{
	PDF *pdf;
	long shading;
	int olen;
	char *optlist;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ls", &shading, &optlist, &olen)) {
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
						"rls", &p, &shading, &optlist, &olen)) {
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
		retval = PDF_shading_pattern(pdf, (int)shading, optlist);
	} pdf_catch;

	RETURN_LONG(retval); /* offset handled in PDFlib Kernel */
}
/* }}} */

/* {{{ proto bool pdf_shfill(resource p, int shading);
 * Fill an area with a shading, based on a shading object (requires PDF 1.4
  or above). */
PHP_FUNCTION(pdf_shfill)
{
	PDF *pdf;
	long shading;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"l", &shading)) {
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
						"rl", &p, &shading)) {
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
		PDF_shfill(pdf, (int)shading);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_show(resource p, string text)
 * Print text in the current font and size at the current position. */
PHP_FUNCTION(pdf_show)
{
	PDF *pdf;
	char *text;
	int len;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"s", &text, &len)) {
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
						"rs", &p, &text, &len)) {
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
		PDF_show2(pdf, text, len);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto int pdf_show_boxed(resource p, string text, double left, double top, double width, double height, string hmode, string feature])
 * Deprecated, use PDF_fit_textline() or PDF_fit_textflow(). */
PHP_FUNCTION(pdf_show_boxed)
{
	PDF *pdf;
	char *text, *hmode, *feature;
	int tlen, hlen, flen;
	double left, top, width, height;
	long retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"sddddss", &text, &tlen, &left, &top, &width, &height,
						&hmode, &hlen, &feature, &flen)) {
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
					"rsddddss", &p, &text, &tlen, &left, &top, &width, &height,
						&hmode, &hlen, &feature, &flen)) {
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
		retval = PDF_show_boxed2(pdf, text, tlen, left, top, width, height,
					hmode, feature);
	} pdf_catch;

	RETURN_LONG(retval);
}
/* }}} */

/* {{{ proto bool pdf_show_xy(resource p, string text, double x, double y)
 * Print text in the current font. */
PHP_FUNCTION(pdf_show_xy)
{
	PDF *pdf;
	char *text;
	int tlen;
	double x, y;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"sdd", &text, &tlen, &x, &y)) {
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
						"rsdd", &p, &text, &tlen, &x, &y)) {
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
		PDF_show_xy2(pdf, text, tlen, x, y);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_skew(resource p, double alpha, double beta)
 * Skew the coordinate system. */
PHP_FUNCTION(pdf_skew)
{
	PDF *pdf;
	double alpha, beta;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dd", &alpha, &beta)) {
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
						"rdd", &p, &alpha, &beta)) {
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
		PDF_skew(pdf, alpha, beta);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto double pdf_stringwidth(resource p, string text, int font, double fontsize)
 * Return the width of text in an arbitrary font. */
PHP_FUNCTION(pdf_stringwidth)
{
	PDF *pdf;
	char *text;
	int tlen;
	long font;
	double  fontsize;
	double retval = 0;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"sld", &text, &tlen, &font, &fontsize)) {
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
						"rsld", &p, &text, &tlen, &font, &fontsize)) {
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
		retval = PDF_stringwidth2(pdf, text, tlen, (int)font, fontsize);
	} pdf_catch;

	RETURN_DOUBLE(retval);
}
/* }}} */

/* {{{ proto bool pdf_stroke(int p)
 * Stroke the path with the current color and line width, and clear it. */
PHP_FUNCTION(pdf_stroke)
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
		}
	#if PHP_MAJOR_VERSION >= 5
	}
	php_std_error_handling();
	#endif /* PHP_MAJOR_VERSION >= 5 */

	pdf_try {
		PDF_stroke(pdf);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto bool pdf_suspend_page(resource p, string optlist)
 * Suspend the current page so that it can later be resumed. */
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_suspend_page)
{
	PDF *pdf;
	char *optlist;
	int olen;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"s", &optlist, &olen)) {
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
						"rs", &p, &optlist, &olen)) {
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
		PDF_suspend_page(pdf, optlist);
	} pdf_catch;

	RETURN_TRUE;
}
#endif /* PDFlib >= 6.0.0 */
/* }}} */

/* {{{ proto bool pdf_translate(resource p, double x, double y)
 * Translate the origin of the coordinate system. */
PHP_FUNCTION(pdf_translate)
{
	PDF *pdf;
	double x, y;

	#if PHP_MAJOR_VERSION >= 5
	zval *object = getThis();

	if (object) {
		php_set_error_handling(EH_THROW, pdflib_exception_class TSRMLS_CC);
		if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dd", &x, &y)) {
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
						"rdd", &p, &x, &y)) {
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
		PDF_translate(pdf, x, y);
	} pdf_catch;

	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string PDF_utf16_to_utf8(resource p, string utf16string);
 * Convert a string from UTF-16 format to UTF-8. */
#if PDFLIB_MAJORVERSION >= 6
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
#endif /* PDFLIB_MAJORVERSION >= 6 */
/* }}} */

/* {{{ proto string PDF_utf8_to_utf16(resource p, string utf8string, string ordering);
 * Convert a string from UTF-8 format to UTF-16. */
#if PDFLIB_MAJORVERSION >= 6
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
#endif /* PDFLIB_MAJORVERSION >= 6 */
/* }}} */



#if PDFLIB_WITH_GD_SUPPORT
#if HAVE_LIBGD13
/* {{{ proto int pdf_open_memory_image(resource p, int image)
   Takes an GD image and returns an image for placement in a PDF document */
PHP_FUNCTION(pdf_open_memory_image)
{
	zval **p, **image;
	int i, j, color;
	long pdf_image;
	gdImagePtr im;
	unsigned char *buffer, *ptr;
	PDF *pdf;

	if (ZEND_NUM_ARGS() != 2 || zend_get_parameters_ex(2, &p, &image) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
	ZEND_GET_RESOURCE_TYPE_ID(le_gd,"gd");
	if(!le_gd)
	{
#if defined(PHP_MAJOR_VERSION) /* PHP 4.3.0 or newer */
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Unable to find handle for GD image stream. Please check the GD extension is loaded.");
#else
		php_error(E_ERROR, "Unable to find handle for GD image stream. Please check the GD extension is loaded.");
#endif
	}
	ZEND_FETCH_RESOURCE(im, gdImagePtr, image, -1, "Image", le_gd);

	buffer = (unsigned char *) safe_emalloc(3 * im->sx, im->sy, 0);

	ptr = buffer;
	for(i=0; i<im->sy; i++) {
		for(j=0; j<im->sx; j++) {
#if HAVE_LIBGD20
			if(gdImageTrueColor(im)) {
				if (im->tpixels && gdImageBoundsSafe(im, j, i)) {
					color = gdImageTrueColorPixel(im, j, i);
                    *ptr++ = (color >> 16) & 0xFF;
                    *ptr++ = (color >> 8) & 0xFF;
                    *ptr++ = color & 0xFF;
				}
			} else {
#endif /* HAVE_LIBGD20 */
				if (im->pixels && gdImageBoundsSafe(im, j, i)) {
					color = im->pixels[i][j];
					*ptr++ = im->red[color];
					*ptr++ = im->green[color];
					*ptr++ = im->blue[color];
				}
#if HAVE_LIBGD20
			}
#endif /* HAVE_LIBGD20 */
		}
	}

	pdf_try {
		pdf_image = PDF_open_image(pdf,
		"raw",
		"memory",
		buffer,
		im->sx*im->sy*3,
		im->sx,
		im->sy,
		3,
		8,
		NULL);
	} pdf_catch;

	efree(buffer);

	if (pdf_image == 0) {
		efree(buffer);
		RETURN_FALSE;
	}

	RETURN_LONG(pdf_image); /* offset handled in PDFlib Kernel */
}
/* }}} */
#endif /* HAVE_LIBGD13 */
#endif /* PDFLIB_WITH_GD_SUPPORT */

#else /* PDFLIB_MAJORVERSION < 5 */
/* use the old wrapper for PDFlib 4 and earlier */
#include "pdf4.c"

#endif /* PDFlib >= 5.0.0 */

#endif /* HAVE_PDFLIB */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
