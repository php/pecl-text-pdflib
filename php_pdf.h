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

#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_activate_item);
#endif /* PDFlib >= 6.0.0 */
PHP_FUNCTION(pdf_add_bookmark);
PHP_FUNCTION(pdf_add_launchlink);
PHP_FUNCTION(pdf_add_locallink);
PHP_FUNCTION(pdf_add_nameddest);
PHP_FUNCTION(pdf_add_note);
PHP_FUNCTION(pdf_add_pdflink);
PHP_FUNCTION(pdf_add_thumbnail);
PHP_FUNCTION(pdf_add_weblink);
PHP_FUNCTION(pdf_arc);
PHP_FUNCTION(pdf_arcn);
PHP_FUNCTION(pdf_attach_file);
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_begin_document);
#endif /* PDFlib >= 6.0.0 */
PHP_FUNCTION(pdf_begin_font);
PHP_FUNCTION(pdf_begin_glyph);
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_begin_item);
PHP_FUNCTION(pdf_begin_layer);
#endif /* PDFlib >= 6.0.0 */
PHP_FUNCTION(pdf_begin_page);
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_begin_page_ext);
#endif /* PDFlib >= 6.0.0 */
PHP_FUNCTION(pdf_begin_pattern);
PHP_FUNCTION(pdf_begin_template);
PHP_FUNCTION(pdf_circle);
PHP_FUNCTION(pdf_clip);
PHP_FUNCTION(pdf_close);
PHP_FUNCTION(pdf_close_image);
PHP_FUNCTION(pdf_close_pdi);
PHP_FUNCTION(pdf_close_pdi_page);
PHP_FUNCTION(pdf_closepath);
PHP_FUNCTION(pdf_closepath_fill_stroke);
PHP_FUNCTION(pdf_closepath_stroke);
PHP_FUNCTION(pdf_concat);
PHP_FUNCTION(pdf_continue_text);
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_create_action);
PHP_FUNCTION(pdf_create_annotation);
PHP_FUNCTION(pdf_create_bookmark);
PHP_FUNCTION(pdf_create_field);
PHP_FUNCTION(pdf_create_fieldgroup);
#endif /* PDFlib >= 6.0.0 */
PHP_FUNCTION(pdf_create_gstate);
PHP_FUNCTION(pdf_create_pvf);
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_create_textflow);
#endif /* PDFlib >= 6.0.0 */
PHP_FUNCTION(pdf_curveto);
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_define_layer);
#endif /* PDFlib >= 6.0.0 */
PHP_FUNCTION(pdf_delete);
PHP_FUNCTION(pdf_delete_pvf);
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_delete_textflow);
#endif /* PDFlib >= 6.0.0 */
PHP_FUNCTION(pdf_encoding_set_char);
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_end_document);
#endif /* PDFlib >= 6.0.0 */
PHP_FUNCTION(pdf_end_font);
PHP_FUNCTION(pdf_end_glyph);
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_end_item);
PHP_FUNCTION(pdf_end_layer);
#endif /* PDFlib >= 6.0.0 */
PHP_FUNCTION(pdf_end_page);
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_end_page_ext);
#endif /* PDFlib >= 6.0.0 */
PHP_FUNCTION(pdf_end_pattern);
PHP_FUNCTION(pdf_end_template);
PHP_FUNCTION(pdf_endpath);
PHP_FUNCTION(pdf_fill);
PHP_FUNCTION(pdf_fill_imageblock);
PHP_FUNCTION(pdf_fill_pdfblock);
PHP_FUNCTION(pdf_fill_stroke);
PHP_FUNCTION(pdf_fill_textblock);
PHP_FUNCTION(pdf_findfont);
PHP_FUNCTION(pdf_fit_image);
PHP_FUNCTION(pdf_fit_pdi_page);
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_fit_textflow);
#endif /* PDFlib >= 6.0.0 */
PHP_FUNCTION(pdf_fit_textline);
PHP_FUNCTION(pdf_get_apiname);
PHP_FUNCTION(pdf_get_buffer);
PHP_FUNCTION(pdf_get_errmsg);
PHP_FUNCTION(pdf_get_errnum);
PHP_FUNCTION(pdf_get_parameter);
PHP_FUNCTION(pdf_get_pdi_parameter);
PHP_FUNCTION(pdf_get_pdi_value);
PHP_FUNCTION(pdf_get_value);
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_info_textflow);
#endif /* PDFlib >= 6.0.0 */
PHP_FUNCTION(pdf_initgraphics);
PHP_FUNCTION(pdf_lineto);
PHP_FUNCTION(pdf_load_font);
PHP_FUNCTION(pdf_load_iccprofile);
PHP_FUNCTION(pdf_load_image);
PHP_FUNCTION(pdf_makespotcolor);
PHP_FUNCTION(pdf_moveto);
PHP_FUNCTION(pdf_new);
PHP_FUNCTION(pdf_open_ccitt);
PHP_FUNCTION(pdf_open_file);
PHP_FUNCTION(pdf_open_image);
PHP_FUNCTION(pdf_open_image_file);
PHP_FUNCTION(pdf_open_pdi);
PHP_FUNCTION(pdf_open_pdi_page);
PHP_FUNCTION(pdf_place_image);
PHP_FUNCTION(pdf_place_pdi_page);
PHP_FUNCTION(pdf_process_pdi);
PHP_FUNCTION(pdf_rect);
PHP_FUNCTION(pdf_restore);
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_resume_page);
#endif /* PDFlib >= 6.0.0 */
PHP_FUNCTION(pdf_rotate);
PHP_FUNCTION(pdf_save);
PHP_FUNCTION(pdf_scale);
PHP_FUNCTION(pdf_set_border_color);
PHP_FUNCTION(pdf_set_border_dash);
PHP_FUNCTION(pdf_set_border_style);
PHP_FUNCTION(pdf_set_gstate);
PHP_FUNCTION(pdf_set_info);
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_set_layer_dependency);
#endif /* PDFlib >= 6.0.0 */
PHP_FUNCTION(pdf_set_parameter);
PHP_FUNCTION(pdf_set_text_pos);
PHP_FUNCTION(pdf_set_value);
PHP_FUNCTION(pdf_setcolor);
PHP_FUNCTION(pdf_setdash);
PHP_FUNCTION(pdf_setdashpattern);
PHP_FUNCTION(pdf_setflat);
PHP_FUNCTION(pdf_setfont);
PHP_FUNCTION(pdf_setlinecap);
PHP_FUNCTION(pdf_setlinejoin);
PHP_FUNCTION(pdf_setlinewidth);
PHP_FUNCTION(pdf_setmatrix);
PHP_FUNCTION(pdf_setmiterlimit);
PHP_FUNCTION(pdf_setpolydash);
PHP_FUNCTION(pdf_shading);
PHP_FUNCTION(pdf_shading_pattern);
PHP_FUNCTION(pdf_shfill);
PHP_FUNCTION(pdf_show);
PHP_FUNCTION(pdf_show_boxed);
PHP_FUNCTION(pdf_show_xy);
PHP_FUNCTION(pdf_skew);
PHP_FUNCTION(pdf_stringwidth);
PHP_FUNCTION(pdf_stroke);
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_suspend_page);
#endif /* PDFlib >= 6.0.0 */
PHP_FUNCTION(pdf_translate);
#if PDFLIB_MAJORVERSION >= 6
PHP_FUNCTION(pdf_utf16_to_utf8);
PHP_FUNCTION(pdf_utf8_to_utf16);
#endif /* PDFlib >= 6.0.0 */


#if HAVE_LIBGD13
/* not supported by PDFlib GmbH */
PHP_FUNCTION(pdf_open_memory_image);
#endif

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
