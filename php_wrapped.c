#if defined(_WRAP_CODE)

    
/* {{{ proto bool PDF_activate_item(
resource p, int id)
 * Activate a previously created structure element or other content item */
PHP_FUNCTION(pdf_activate_item)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long id;
#else
    long id;
#endif


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &id)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &id)) {
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
"zl", &p, &id)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rl", &p, &id)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_activate_item(pdf, (int)id);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto int PDF_add_bookmark(
resource p, string text, int parent, int open)
 * Deprecated, use  PDF_create_bookmark() */
PHP_FUNCTION(pdf_add_bookmark)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_text;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * text;
    size_t text_len;

#if PHP_MAJOR_VERSION >= 7
    zend_long parent;
#else
    long parent;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_long open;
#else
    long open;
#endif
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"Sll", &z_text, &parent, &open)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"sll", &text, &text_len, &parent, &open)) {
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
"zSll", &p, &z_text, &parent, &open)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rsll", &p, &text, &text_len, &parent, &open)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use  PDF_create_bookmark()");

    pdf_try {
	_result = PDF_add_bookmark2(pdf, text, (int)text_len, (int)parent, (int)open);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto bool PDF_add_launchlink(
resource p, double llx, double lly, double urx, double ury, string filename)
 * Deprecated, use PDF_create_action() and PDF_create_annotation() */
PHP_FUNCTION(pdf_add_launchlink)
{
    PDF *pdf;
    double llx;
    double lly;
    double urx;
    double ury;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_filename;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * filename;
    size_t filename_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddddS", &llx, &lly, &urx, &ury, &z_filename)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        filename = ZSTR_VAL(z_filename);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dddds", &llx, &lly, &urx, &ury, &filename, &filename_len)) {
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
"zddddS", &p, &llx, &lly, &urx, &ury, &z_filename)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        filename = ZSTR_VAL(z_filename);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdddds", &p, &llx, &lly, &urx, &ury, &filename, &filename_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_create_action() and PDF_create_annotation()");

    pdf_try {
	PDF_add_launchlink(pdf, llx, lly, urx, ury, filename);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_add_locallink(
resource p, double llx, double lly, double urx, double ury, int page, string optlist)
 * Deprecated, use PDF_create_action() and PDF_create_annotation() */
PHP_FUNCTION(pdf_add_locallink)
{
    PDF *pdf;
    double llx;
    double lly;
    double urx;
    double ury;

#if PHP_MAJOR_VERSION >= 7
    zend_long page;
#else
    long page;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddddlS", &llx, &lly, &urx, &ury, &page, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddddls", &llx, &lly, &urx, &ury, &page, &optlist, &optlist_len)) {
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
"zddddlS", &p, &llx, &lly, &urx, &ury, &page, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rddddls", &p, &llx, &lly, &urx, &ury, &page, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_create_action() and PDF_create_annotation()");

    pdf_try {
	PDF_add_locallink(pdf, llx, lly, urx, ury, (int)page, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_add_nameddest(
resource p, string name, string optlist)
 * Create a named destination on a page in the document */
PHP_FUNCTION(pdf_add_nameddest)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_name;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * name;
    size_t name_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_name, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        name = ZSTR_VAL(z_name);
        name_len = ZSTR_LEN(z_name);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &name, &name_len, &optlist, &optlist_len)) {
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
"zSS", &p, &z_name, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        name = ZSTR_VAL(z_name);
        name_len = ZSTR_LEN(z_name);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &name, &name_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_add_nameddest(pdf, name, (int)name_len, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_add_note(
resource p, double llx, double lly, double urx, double ury, string contents, string title, string icon, int open)
 * Deprecated, use PDF_create_annotation() */
PHP_FUNCTION(pdf_add_note)
{
    PDF *pdf;
    double llx;
    double lly;
    double urx;
    double ury;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_contents;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * contents;
    size_t contents_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_title;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * title;
    size_t title_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_icon;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * icon;
    size_t icon_len;

#if PHP_MAJOR_VERSION >= 7
    zend_long open;
#else
    long open;
#endif


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddddSSSl", &llx, &lly, &urx, &ury, &z_contents, &z_title, &z_icon, &open)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        contents = ZSTR_VAL(z_contents);
        contents_len = ZSTR_LEN(z_contents);
        title = ZSTR_VAL(z_title);
        title_len = ZSTR_LEN(z_title);
        icon = ZSTR_VAL(z_icon);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddddsssl", &llx, &lly, &urx, &ury, &contents, &contents_len, &title, &title_len, &icon, &icon_len, &open)) {
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
"zddddSSSl", &p, &llx, &lly, &urx, &ury, &z_contents, &z_title, &z_icon, &open)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        contents = ZSTR_VAL(z_contents);
        contents_len = ZSTR_LEN(z_contents);
        title = ZSTR_VAL(z_title);
        title_len = ZSTR_LEN(z_title);
        icon = ZSTR_VAL(z_icon);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rddddsssl", &p, &llx, &lly, &urx, &ury, &contents, &contents_len, &title, &title_len, &icon, &icon_len, &open)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_create_annotation()");

    pdf_try {
	PDF_add_note2(pdf, llx, lly, urx, ury, contents, (int)contents_len, title, (int)title_len, icon, (int)open);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto int PDF_add_path_point(
resource p, int path, double x, double y, string type, string optlist)
 * Add a point to a new or existing path object */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_add_path_point)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long path;
#else
    long path;
#endif
    double x;
    double y;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_type;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * type;
    size_t type_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lddSS", &path, &x, &y, &z_type, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        type = ZSTR_VAL(z_type);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lddss", &path, &x, &y, &type, &type_len, &optlist, &optlist_len)) {
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
"zlddSS", &p, &path, &x, &y, &z_type, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        type = ZSTR_VAL(z_type);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rlddss", &p, &path, &x, &y, &type, &type_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_add_path_point(pdf, (int)path, x, y, type, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
#endif /* PDFLIB_MAJORVERSION >= 8 */
/* }}} */

    
/* {{{ proto bool PDF_add_pdflink(
resource p, double llx, double lly, double urx, double ury, string filename, int page, string optlist)
 * Deprecated, use PDF_create_action() and PDF_create_annotation() */
PHP_FUNCTION(pdf_add_pdflink)
{
    PDF *pdf;
    double llx;
    double lly;
    double urx;
    double ury;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_filename;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * filename;
    size_t filename_len;

#if PHP_MAJOR_VERSION >= 7
    zend_long page;
#else
    long page;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddddSlS", &llx, &lly, &urx, &ury, &z_filename, &page, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        filename = ZSTR_VAL(z_filename);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddddsls", &llx, &lly, &urx, &ury, &filename, &filename_len, &page, &optlist, &optlist_len)) {
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
"zddddSlS", &p, &llx, &lly, &urx, &ury, &z_filename, &page, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        filename = ZSTR_VAL(z_filename);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rddddsls", &p, &llx, &lly, &urx, &ury, &filename, &filename_len, &page, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_create_action() and PDF_create_annotation()");

    pdf_try {
	PDF_add_pdflink(pdf, llx, lly, urx, ury, filename, (int)page, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto int PDF_add_portfolio_file(
resource p, int folder, string filename, string optlist)
 * Add a file to a portfolio folder or a package (requires PDF 1.7) */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_add_portfolio_file)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long folder;
#else
    long folder;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_filename;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * filename;
    size_t filename_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lSS", &folder, &z_filename, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        filename = ZSTR_VAL(z_filename);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lss", &folder, &filename, &filename_len, &optlist, &optlist_len)) {
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
"zlSS", &p, &folder, &z_filename, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        filename = ZSTR_VAL(z_filename);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rlss", &p, &folder, &filename, &filename_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_add_portfolio_file(pdf, (int)folder, filename, 0, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
#endif /* PDFLIB_MAJORVERSION >= 8 */
/* }}} */

    
/* {{{ proto int PDF_add_portfolio_folder(
resource p, int parent, string foldername, string optlist)
 * Add a folder to a new or existing portfolio (requires PDF 1.7ext3) */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_add_portfolio_folder)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long parent;
#else
    long parent;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_foldername;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * foldername;
    size_t foldername_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lSS", &parent, &z_foldername, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        foldername = ZSTR_VAL(z_foldername);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lss", &parent, &foldername, &foldername_len, &optlist, &optlist_len)) {
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
"zlSS", &p, &parent, &z_foldername, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        foldername = ZSTR_VAL(z_foldername);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rlss", &p, &parent, &foldername, &foldername_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_add_portfolio_folder(pdf, (int)parent, foldername, 0, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
#endif /* PDFLIB_MAJORVERSION >= 8 */
/* }}} */

    
/* {{{ proto int PDF_add_table_cell(
resource p, int table, int column, int row, string text, string optlist)
 * Add a cell to a new or existing table */
PHP_FUNCTION(pdf_add_table_cell)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long table;
#else
    long table;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_long column;
#else
    long column;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_long row;
#else
    long row;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_text;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * text;
    size_t text_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lllSS", &table, &column, &row, &z_text, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lllss", &table, &column, &row, &text, &text_len, &optlist, &optlist_len)) {
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
"zlllSS", &p, &table, &column, &row, &z_text, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rlllss", &p, &table, &column, &row, &text, &text_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_add_table_cell(pdf, (int)table, (int)column, (int)row, text, (int)text_len, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto int PDF_add_textflow(
resource p, int textflow, string text, string optlist)
 * Create a Textflow object, or add text and explicit options to an existing Textflow */
PHP_FUNCTION(pdf_add_textflow)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long textflow;
#else
    long textflow;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_text;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * text;
    size_t text_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lSS", &textflow, &z_text, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lss", &textflow, &text, &text_len, &optlist, &optlist_len)) {
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
"zlSS", &p, &textflow, &z_text, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rlss", &p, &textflow, &text, &text_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_add_textflow(pdf, (int)textflow, text, (int)text_len, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto bool PDF_add_thumbnail(
resource p, int image)
 * Deprecated */
PHP_FUNCTION(pdf_add_thumbnail)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long image;
#else
    long image;
#endif


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &image)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &image)) {
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
"zl", &p, &image)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rl", &p, &image)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
    #if PDFLIB_MAJORVERSION >= 9
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated");
    #endif /* PDFLIB_MAJORVERSION >= 9 */

    pdf_try {
	PDF_add_thumbnail(pdf, (int)image);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_add_weblink(
resource p, double llx, double lly, double urx, double ury, string url)
 * Deprecated, use PDF_create_action() and PDF_create_annotation() */
PHP_FUNCTION(pdf_add_weblink)
{
    PDF *pdf;
    double llx;
    double lly;
    double urx;
    double ury;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_url;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * url;
    size_t url_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddddS", &llx, &lly, &urx, &ury, &z_url)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        url = ZSTR_VAL(z_url);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dddds", &llx, &lly, &urx, &ury, &url, &url_len)) {
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
"zddddS", &p, &llx, &lly, &urx, &ury, &z_url)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        url = ZSTR_VAL(z_url);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdddds", &p, &llx, &lly, &urx, &ury, &url, &url_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_create_action() and PDF_create_annotation()");

    pdf_try {
	PDF_add_weblink(pdf, llx, lly, urx, ury, url);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_align(
resource p, double dx, double dy)
 * Align the coordinate system with a relative vector */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_align)
{
    PDF *pdf;
    double dx;
    double dy;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &dx, &dy)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &dx, &dy)) {
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
"zdd", &p, &dx, &dy)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdd", &p, &dx, &dy)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_align(pdf, dx, dy);
    } pdf_catch;

    
    RETURN_TRUE;
}
#endif /* PDFLIB_MAJORVERSION >= 8 */
/* }}} */

    
/* {{{ proto bool PDF_arc(
resource p, double x, double y, double r, double alpha, double beta)
 * Draw a counterclockwise circular arc segment */
PHP_FUNCTION(pdf_arc)
{
    PDF *pdf;
    double x;
    double y;
    double r;
    double alpha;
    double beta;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddddd", &x, &y, &r, &alpha, &beta)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddddd", &x, &y, &r, &alpha, &beta)) {
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
"zddddd", &p, &x, &y, &r, &alpha, &beta)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rddddd", &p, &x, &y, &r, &alpha, &beta)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_arc(pdf, x, y, r, alpha, beta);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_arcn(
resource p, double x, double y, double r, double alpha, double beta)
 * Draw a clockwise circular arc segment */
PHP_FUNCTION(pdf_arcn)
{
    PDF *pdf;
    double x;
    double y;
    double r;
    double alpha;
    double beta;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddddd", &x, &y, &r, &alpha, &beta)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddddd", &x, &y, &r, &alpha, &beta)) {
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
"zddddd", &p, &x, &y, &r, &alpha, &beta)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rddddd", &p, &x, &y, &r, &alpha, &beta)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_arcn(pdf, x, y, r, alpha, beta);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_attach_file(
resource p, double llx, double lly, double urx, double ury, string filename, string description, string author, string mimetype, string icon)
 * Deprecated, use  PDF_create_annotation() */
PHP_FUNCTION(pdf_attach_file)
{
    PDF *pdf;
    double llx;
    double lly;
    double urx;
    double ury;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_filename;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * filename;
    size_t filename_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_description;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * description;
    size_t description_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_author;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * author;
    size_t author_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_mimetype;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * mimetype;
    size_t mimetype_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_icon;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * icon;
    size_t icon_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddddSSSSS", &llx, &lly, &urx, &ury, &z_filename, &z_description, &z_author, &z_mimetype, &z_icon)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        filename = ZSTR_VAL(z_filename);
        description = ZSTR_VAL(z_description);
        description_len = ZSTR_LEN(z_description);
        author = ZSTR_VAL(z_author);
        author_len = ZSTR_LEN(z_author);
        mimetype = ZSTR_VAL(z_mimetype);
        icon = ZSTR_VAL(z_icon);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddddsssss", &llx, &lly, &urx, &ury, &filename, &filename_len, &description, &description_len, &author, &author_len, &mimetype, &mimetype_len, &icon, &icon_len)) {
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
"zddddSSSSS", &p, &llx, &lly, &urx, &ury, &z_filename, &z_description, &z_author, &z_mimetype, &z_icon)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        filename = ZSTR_VAL(z_filename);
        description = ZSTR_VAL(z_description);
        description_len = ZSTR_LEN(z_description);
        author = ZSTR_VAL(z_author);
        author_len = ZSTR_LEN(z_author);
        mimetype = ZSTR_VAL(z_mimetype);
        icon = ZSTR_VAL(z_icon);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rddddsssss", &p, &llx, &lly, &urx, &ury, &filename, &filename_len, &description, &description_len, &author, &author_len, &mimetype, &mimetype_len, &icon, &icon_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use  PDF_create_annotation()");

    pdf_try {
	PDF_attach_file2(pdf, llx, lly, urx, ury, filename, 0, description, (int)description_len, author, (int)author_len, mimetype, icon);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto int PDF_begin_document(
resource p, string filename, string optlist)
 * Create a new PDF file subject to various options */
PHP_FUNCTION(pdf_begin_document)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_filename;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * filename;
    size_t filename_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_filename, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        filename = ZSTR_VAL(z_filename);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &filename, &filename_len, &optlist, &optlist_len)) {
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
"zSS", &p, &z_filename, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        filename = ZSTR_VAL(z_filename);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &filename, &filename_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

	if (filename && *filename) {
	    if (php_check_open_basedir(filename TSRMLS_CC)) {
		RETURN_FALSE;
	    }
	}
	
    pdf_try {
	_result = PDF_begin_document(pdf, filename, 0, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto bool PDF_begin_dpart(
resource p, string optlist)
 * Create a new node in the document part hierarchy (requires PDF/VT or   PDF 2.0) */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_begin_dpart)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"S", &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"s", &optlist, &optlist_len)) {
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
"zS", &p, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rs", &p, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_begin_dpart(pdf, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
/* }}} */

    
/* {{{ proto bool PDF_begin_font(
resource p, string fontname, double a, double b, double c, double d, double e, double f, string optlist)
 * Start a Type 3 font definition */
PHP_FUNCTION(pdf_begin_font)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_fontname;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * fontname;
    size_t fontname_len;
    double a;
    double b;
    double c;
    double d;
    double e;
    double f;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SddddddS", &z_fontname, &a, &b, &c, &d, &e, &f, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        fontname = ZSTR_VAL(z_fontname);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"sdddddds", &fontname, &fontname_len, &a, &b, &c, &d, &e, &f, &optlist, &optlist_len)) {
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
"zSddddddS", &p, &z_fontname, &a, &b, &c, &d, &e, &f, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        fontname = ZSTR_VAL(z_fontname);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rsdddddds", &p, &fontname, &fontname_len, &a, &b, &c, &d, &e, &f, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_begin_font(pdf, fontname, 0, a, b, c, d, e, f, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_begin_glyph(
resource p, string glyphname, double wx, double llx, double lly, double urx, double ury)
 * Deprecated, use PDF_begin_glyph_ext() */
PHP_FUNCTION(pdf_begin_glyph)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_glyphname;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * glyphname;
    size_t glyphname_len;
    double wx;
    double llx;
    double lly;
    double urx;
    double ury;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"Sddddd", &z_glyphname, &wx, &llx, &lly, &urx, &ury)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        glyphname = ZSTR_VAL(z_glyphname);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"sddddd", &glyphname, &glyphname_len, &wx, &llx, &lly, &urx, &ury)) {
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
"zSddddd", &p, &z_glyphname, &wx, &llx, &lly, &urx, &ury)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        glyphname = ZSTR_VAL(z_glyphname);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rsddddd", &p, &glyphname, &glyphname_len, &wx, &llx, &lly, &urx, &ury)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
    #if PDFLIB_MAJORVERSION >= 9
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_begin_glyph_ext()");
    #endif /* PDFLIB_MAJORVERSION >= 9 */

    pdf_try {
	PDF_begin_glyph(pdf, glyphname, wx, llx, lly, urx, ury);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_begin_glyph_ext(
resource p, int uv, string optlist)
 * Start a glyph definition for a Type 3 font */
#if PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_begin_glyph_ext)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long uv;
#else
    long uv;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lS", &uv, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ls", &uv, &optlist, &optlist_len)) {
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
"zlS", &p, &uv, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rls", &p, &uv, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_begin_glyph_ext(pdf, (int)uv, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
#endif /* PDFLIB_MAJORVERSION >= 9 */
/* }}} */

    
/* {{{ proto int PDF_begin_item(
resource p, string tagname, string optlist)
 * Open a structure element or other content item with attributes supplied as options */
PHP_FUNCTION(pdf_begin_item)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_tagname;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * tagname;
    size_t tagname_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_tagname, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        tagname = ZSTR_VAL(z_tagname);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &tagname, &tagname_len, &optlist, &optlist_len)) {
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
"zSS", &p, &z_tagname, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        tagname = ZSTR_VAL(z_tagname);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &tagname, &tagname_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_begin_item(pdf, tagname, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto bool PDF_begin_layer(
resource p, int layer)
 * Start a layer for subsequent output on the page (requires PDF 1.5) */
PHP_FUNCTION(pdf_begin_layer)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long layer;
#else
    long layer;
#endif


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &layer)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &layer)) {
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
"zl", &p, &layer)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rl", &p, &layer)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_begin_layer(pdf, (int)layer);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_begin_mc(
resource p, string tagname, string optlist)
 * Begin a marked content sequence with optional properties */
PHP_FUNCTION(pdf_begin_mc)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_tagname;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * tagname;
    size_t tagname_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_tagname, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        tagname = ZSTR_VAL(z_tagname);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &tagname, &tagname_len, &optlist, &optlist_len)) {
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
"zSS", &p, &z_tagname, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        tagname = ZSTR_VAL(z_tagname);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &tagname, &tagname_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_begin_mc(pdf, tagname, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_begin_page(
resource p, double width, double height)
 * Deprecated, use PDF_begin_page_ext() */
PHP_FUNCTION(pdf_begin_page)
{
    PDF *pdf;
    double width;
    double height;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &width, &height)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &width, &height)) {
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
"zdd", &p, &width, &height)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdd", &p, &width, &height)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_begin_page_ext()");

    pdf_try {
	PDF_begin_page(pdf, width, height);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_begin_page_ext(
resource p, double width, double height, string optlist)
 * Add a new page to the document, and specify various options */
PHP_FUNCTION(pdf_begin_page_ext)
{
    PDF *pdf;
    double width;
    double height;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddS", &width, &height, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dds", &width, &height, &optlist, &optlist_len)) {
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
"zddS", &p, &width, &height, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdds", &p, &width, &height, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_begin_page_ext(pdf, width, height, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto int PDF_begin_pattern(
resource p, double width, double height, double xstep, double ystep, int painttype)
 * Deprecated, use PDF_begin_pattern_ext() */
PHP_FUNCTION(pdf_begin_pattern)
{
    PDF *pdf;
    double width;
    double height;
    double xstep;
    double ystep;

#if PHP_MAJOR_VERSION >= 7
    zend_long painttype;
#else
    long painttype;
#endif
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddddl", &width, &height, &xstep, &ystep, &painttype)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddddl", &width, &height, &xstep, &ystep, &painttype)) {
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
"zddddl", &p, &width, &height, &xstep, &ystep, &painttype)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rddddl", &p, &width, &height, &xstep, &ystep, &painttype)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
    #if PDFLIB_MAJORVERSION >= 9 && (PDFLIB_MINORVERSION >= 1 || PDFLIB_REVISION >= 2)
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_begin_pattern_ext()");
    #endif /* PDFLIB_MAJORVERSION >= 9 && (PDFLIB_MINORVERSION >= 1 || PDFLIB_REVISION >= 2) */

    pdf_try {
	_result = PDF_begin_pattern(pdf, width, height, xstep, ystep, (int)painttype);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto int PDF_begin_pattern_ext(
resource p, double width, double height, string optlist)
 * Start a pattern definition with options */
#if PDFLIB_MAJORVERSION >= 9 && (PDFLIB_MINORVERSION >= 1 || PDFLIB_REVISION >= 2)
PHP_FUNCTION(pdf_begin_pattern_ext)
{
    PDF *pdf;
    double width;
    double height;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddS", &width, &height, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dds", &width, &height, &optlist, &optlist_len)) {
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
"zddS", &p, &width, &height, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdds", &p, &width, &height, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_begin_pattern_ext(pdf, width, height, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
#endif /* PDFLIB_MAJORVERSION >= 9 && (PDFLIB_MINORVERSION >= 1 || PDFLIB_REVISION >= 2) */
/* }}} */

    
/* {{{ proto int PDF_begin_template(
resource p, double width, double height)
 * Deprecated, use PDF_begin_template_ext() */
PHP_FUNCTION(pdf_begin_template)
{
    PDF *pdf;
    double width;
    double height;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &width, &height)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &width, &height)) {
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
"zdd", &p, &width, &height)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdd", &p, &width, &height)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_begin_template_ext()");

    pdf_try {
	_result = PDF_begin_template(pdf, width, height);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto int PDF_begin_template_ext(
resource p, double width, double height, string optlist)
 * Start a template definition */
PHP_FUNCTION(pdf_begin_template_ext)
{
    PDF *pdf;
    double width;
    double height;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddS", &width, &height, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dds", &width, &height, &optlist, &optlist_len)) {
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
"zddS", &p, &width, &height, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdds", &p, &width, &height, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_begin_template_ext(pdf, width, height, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto bool PDF_circle(
resource p, double x, double y, double r)
 * Draw a circle */
PHP_FUNCTION(pdf_circle)
{
    PDF *pdf;
    double x;
    double y;
    double r;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddd", &x, &y, &r)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddd", &x, &y, &r)) {
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
"zddd", &p, &x, &y, &r)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rddd", &p, &x, &y, &r)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_circle(pdf, x, y, r);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_circular_arc(
resource p, double x1, double y1, double x2, double y2)
 * Draw a circular arc segment defined by three points */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_circular_arc)
{
    PDF *pdf;
    double x1;
    double y1;
    double x2;
    double y2;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dddd", &x1, &y1, &x2, &y2)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dddd", &x1, &y1, &x2, &y2)) {
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
"zdddd", &p, &x1, &y1, &x2, &y2)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdddd", &p, &x1, &y1, &x2, &y2)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_circular_arc(pdf, x1, y1, x2, y2);
    } pdf_catch;

    
    RETURN_TRUE;
}
#endif /* PDFLIB_MAJORVERSION >= 8 */
/* }}} */

    
/* {{{ proto bool PDF_clip(
resource p)
 * Use the current path as clipping path, and terminate the path */
PHP_FUNCTION(pdf_clip)
{
    PDF *pdf;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_clip(pdf);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_close(
resource p)
 * Deprecated, use PDF_end_document() */
PHP_FUNCTION(pdf_close)
{
    PDF *pdf;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_end_document()");

    pdf_try {
	PDF_close(pdf);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_close_font(
resource p, int font)
 * Close an open font handle which has not yet been used in the document */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_close_font)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long font;
#else
    long font;
#endif


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &font)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &font)) {
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
"zl", &p, &font)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rl", &p, &font)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_close_font(pdf, (int)font);
    } pdf_catch;

    
    RETURN_TRUE;
}
#endif /* PDFLIB_MAJORVERSION >= 8 */
/* }}} */

    
/* {{{ proto bool PDF_close_graphics(
resource p, int graphics)
 * Close vector graphics */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_close_graphics)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long graphics;
#else
    long graphics;
#endif


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &graphics)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &graphics)) {
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
"zl", &p, &graphics)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rl", &p, &graphics)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_close_graphics(pdf, (int)graphics);
    } pdf_catch;

    
    RETURN_TRUE;
}
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
/* }}} */

    
/* {{{ proto bool PDF_close_image(
resource p, int image)
 * Close an image or template */
PHP_FUNCTION(pdf_close_image)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long image;
#else
    long image;
#endif


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &image)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &image)) {
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
"zl", &p, &image)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rl", &p, &image)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_close_image(pdf, (int)image);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_close_pdi(
resource p, int doc)
 * Deprecated, use PDF_close_pdi_document() */
PHP_FUNCTION(pdf_close_pdi)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long doc;
#else
    long doc;
#endif


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &doc)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &doc)) {
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
"zl", &p, &doc)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rl", &p, &doc)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_close_pdi_document()");

    pdf_try {
	PDF_close_pdi(pdf, (int)doc);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_close_pdi_document(
resource p, int doc)
 * Close all open PDI page handles, and close the input PDF document */
PHP_FUNCTION(pdf_close_pdi_document)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long doc;
#else
    long doc;
#endif


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &doc)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &doc)) {
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
"zl", &p, &doc)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rl", &p, &doc)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_close_pdi_document(pdf, (int)doc);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_close_pdi_page(
resource p, int page)
 * Close the page handle and free all page-related resources */
PHP_FUNCTION(pdf_close_pdi_page)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long page;
#else
    long page;
#endif


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &page)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &page)) {
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
"zl", &p, &page)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rl", &p, &page)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_close_pdi_page(pdf, (int)page);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_closepath(
resource p)
 * Close the current path */
PHP_FUNCTION(pdf_closepath)
{
    PDF *pdf;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_closepath(pdf);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_closepath_fill_stroke(
resource p)
 * Close the path, fill, and stroke it */
PHP_FUNCTION(pdf_closepath_fill_stroke)
{
    PDF *pdf;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_closepath_fill_stroke(pdf);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_closepath_stroke(
resource p)
 * Close the path, and stroke it */
PHP_FUNCTION(pdf_closepath_stroke)
{
    PDF *pdf;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_closepath_stroke(pdf);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_concat(
resource p, double a, double b, double c, double d, double e, double f)
 * Apply a transformation matrix to the current coordinate system */
PHP_FUNCTION(pdf_concat)
{
    PDF *pdf;
    double a;
    double b;
    double c;
    double d;
    double e;
    double f;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dddddd", &a, &b, &c, &d, &e, &f)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dddddd", &a, &b, &c, &d, &e, &f)) {
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
"zdddddd", &p, &a, &b, &c, &d, &e, &f)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdddddd", &p, &a, &b, &c, &d, &e, &f)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_concat(pdf, a, b, c, d, e, f);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_continue_text(
resource p, string text)
 * Print text at the next line */
PHP_FUNCTION(pdf_continue_text)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_text;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * text;
    size_t text_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"S", &z_text)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"s", &text, &text_len)) {
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
"zS", &p, &z_text)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rs", &p, &text, &text_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_continue_text2(pdf, text, (int)text_len);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto string PDF_convert_to_unicode(
resource p, string inputformat, string inputstring, string optlist)
 * Convert a string in an arbitrary encoding to a Unicode string in various formats */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_convert_to_unicode)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_inputformat;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * inputformat;
    size_t inputformat_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_inputstring;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * inputstring;
    size_t inputstring_len;
    int outputlen;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    const char *_result = NULL;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SSS", &z_inputformat, &z_inputstring, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        inputformat = ZSTR_VAL(z_inputformat);
        inputstring = ZSTR_VAL(z_inputstring);
        inputstring_len = ZSTR_LEN(z_inputstring);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"sss", &inputformat, &inputformat_len, &inputstring, &inputstring_len, &optlist, &optlist_len)) {
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
"zSSS", &p, &z_inputformat, &z_inputstring, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        inputformat = ZSTR_VAL(z_inputformat);
        inputstring = ZSTR_VAL(z_inputstring);
        inputstring_len = ZSTR_LEN(z_inputstring);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rsss", &p, &inputformat, &inputformat_len, &inputstring, &inputstring_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result =  (const char *)PDF_convert_to_unicode(pdf, inputformat, inputstring, (int)inputstring_len, &outputlen, optlist);
    } pdf_catch;

    
#if PHP_MAJOR_VERSION >= 7
    {
        zend_string *z_result;
        if (_result) {
            z_result = zend_string_alloc(outputlen, 0);
            memcpy(z_result->val, _result, outputlen);
        } else {
            z_result = zend_string_init("", 1, 0);
        }
        RETURN_STR(z_result);
    }
#else /* PHP_MAJOR_VERSION >= 7 */
    RETURN_STRINGL(_result ? (char *)_result : "", outputlen, 1);
#endif /* PHP_MAJOR_VERSION >= 7 */
}
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
/* }}} */

    
/* {{{ proto int PDF_create_3dview(
resource p, string username, string optlist)
 * Create a 3D view (requires PDF 1.6) */
PHP_FUNCTION(pdf_create_3dview)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_username;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * username;
    size_t username_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_username, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        username = ZSTR_VAL(z_username);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &username, &username_len, &optlist, &optlist_len)) {
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
"zSS", &p, &z_username, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        username = ZSTR_VAL(z_username);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &username, &username_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_create_3dview(pdf, username, 0, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto int PDF_create_action(
resource p, string type, string optlist)
 * Create an action which can be applied to various objects and events */
PHP_FUNCTION(pdf_create_action)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_type;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * type;
    size_t type_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_type, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        type = ZSTR_VAL(z_type);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &type, &type_len, &optlist, &optlist_len)) {
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
"zSS", &p, &z_type, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        type = ZSTR_VAL(z_type);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &type, &type_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_create_action(pdf, type, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto bool PDF_create_annotation(
resource p, double llx, double lly, double urx, double ury, string type, string optlist)
 * Create an annotation on the current page */
PHP_FUNCTION(pdf_create_annotation)
{
    PDF *pdf;
    double llx;
    double lly;
    double urx;
    double ury;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_type;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * type;
    size_t type_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddddSS", &llx, &lly, &urx, &ury, &z_type, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        type = ZSTR_VAL(z_type);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddddss", &llx, &lly, &urx, &ury, &type, &type_len, &optlist, &optlist_len)) {
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
"zddddSS", &p, &llx, &lly, &urx, &ury, &z_type, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        type = ZSTR_VAL(z_type);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rddddss", &p, &llx, &lly, &urx, &ury, &type, &type_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_create_annotation(pdf, llx, lly, urx, ury, type, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto int PDF_create_devicen(
resource p, string optlist)
 * Create a DeviceN colorspace with an arbitrary number of color components */
#if PDFLIB_MAJORVERSION >= 9 && PDFLIB_MINORVERSION >= 1
PHP_FUNCTION(pdf_create_devicen)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"S", &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"s", &optlist, &optlist_len)) {
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
"zS", &p, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rs", &p, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_create_devicen(pdf, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
#endif /* PDFLIB_MAJORVERSION >= 9 && PDFLIB_MINORVERSION >= 1 */
/* }}} */

    
/* {{{ proto int PDF_create_bookmark(
resource p, string text, string optlist)
 * Create a bookmark subject to various options */
PHP_FUNCTION(pdf_create_bookmark)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_text;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * text;
    size_t text_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_text, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &text, &text_len, &optlist, &optlist_len)) {
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
"zSS", &p, &z_text, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &text, &text_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_create_bookmark(pdf, text, (int)text_len, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto bool PDF_create_field(
resource p, double llx, double lly, double urx, double ury, string name, string type, string optlist)
 * Create a form field on the current page subject to various options */
PHP_FUNCTION(pdf_create_field)
{
    PDF *pdf;
    double llx;
    double lly;
    double urx;
    double ury;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_name;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * name;
    size_t name_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_type;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * type;
    size_t type_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddddSSS", &llx, &lly, &urx, &ury, &z_name, &z_type, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        name = ZSTR_VAL(z_name);
        name_len = ZSTR_LEN(z_name);
        type = ZSTR_VAL(z_type);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddddsss", &llx, &lly, &urx, &ury, &name, &name_len, &type, &type_len, &optlist, &optlist_len)) {
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
"zddddSSS", &p, &llx, &lly, &urx, &ury, &z_name, &z_type, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        name = ZSTR_VAL(z_name);
        name_len = ZSTR_LEN(z_name);
        type = ZSTR_VAL(z_type);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rddddsss", &p, &llx, &lly, &urx, &ury, &name, &name_len, &type, &type_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_create_field(pdf, llx, lly, urx, ury, name, (int)name_len, type, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_create_fieldgroup(
resource p, string name, string optlist)
 * Create a form field group subject to various options */
PHP_FUNCTION(pdf_create_fieldgroup)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_name;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * name;
    size_t name_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_name, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        name = ZSTR_VAL(z_name);
        name_len = ZSTR_LEN(z_name);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &name, &name_len, &optlist, &optlist_len)) {
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
"zSS", &p, &z_name, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        name = ZSTR_VAL(z_name);
        name_len = ZSTR_LEN(z_name);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &name, &name_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_create_fieldgroup(pdf, name, (int)name_len, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto int PDF_create_gstate(
resource p, string optlist)
 * Create a graphics state object subject to various options */
PHP_FUNCTION(pdf_create_gstate)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"S", &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"s", &optlist, &optlist_len)) {
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
"zS", &p, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rs", &p, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_create_gstate(pdf, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto bool PDF_create_pvf(
resource p, string filename, string data, string optlist)
 * Create a named virtual read-only file from data provided in memory */
PHP_FUNCTION(pdf_create_pvf)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_filename;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * filename;
    size_t filename_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_data;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const void * data;
    size_t data_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SSS", &z_filename, &z_data, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        filename = ZSTR_VAL(z_filename);
        data = ZSTR_VAL(z_data);
        data_len = ZSTR_LEN(z_data);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"sss", &filename, &filename_len, &data, &data_len, &optlist, &optlist_len)) {
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
"zSSS", &p, &z_filename, &z_data, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        filename = ZSTR_VAL(z_filename);
        data = ZSTR_VAL(z_data);
        data_len = ZSTR_LEN(z_data);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rsss", &p, &filename, &filename_len, &data, &data_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_create_pvf(pdf, filename, 0, data, (int)data_len, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto int PDF_create_textflow(
resource p, string text, string optlist)
 * Create a Textflow object from text contents, inline options, and explicit options */
PHP_FUNCTION(pdf_create_textflow)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_text;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * text;
    size_t text_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_text, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &text, &text_len, &optlist, &optlist_len)) {
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
"zSS", &p, &z_text, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &text, &text_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_create_textflow(pdf, text, (int)text_len, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto bool PDF_curveto(
resource p, double x1, double y1, double x2, double y2, double x3, double y3)
 * Draw a Bezier curve from the current point, using 3 more control points */
PHP_FUNCTION(pdf_curveto)
{
    PDF *pdf;
    double x1;
    double y1;
    double x2;
    double y2;
    double x3;
    double y3;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dddddd", &x1, &y1, &x2, &y2, &x3, &y3)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dddddd", &x1, &y1, &x2, &y2, &x3, &y3)) {
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
"zdddddd", &p, &x1, &y1, &x2, &y2, &x3, &y3)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdddddd", &p, &x1, &y1, &x2, &y2, &x3, &y3)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_curveto(pdf, x1, y1, x2, y2, x3, y3);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto int PDF_define_layer(
resource p, string name, string optlist)
 * Create a new layer definition (requires PDF 1.5) */
PHP_FUNCTION(pdf_define_layer)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_name;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * name;
    size_t name_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_name, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        name = ZSTR_VAL(z_name);
        name_len = ZSTR_LEN(z_name);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &name, &name_len, &optlist, &optlist_len)) {
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
"zSS", &p, &z_name, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        name = ZSTR_VAL(z_name);
        name_len = ZSTR_LEN(z_name);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &name, &name_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_define_layer(pdf, name, (int)name_len, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto bool PDF_delete_path(
resource p, int path)
 * Delete a path object */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_delete_path)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long path;
#else
    long path;
#endif


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &path)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &path)) {
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
"zl", &p, &path)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rl", &p, &path)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_delete_path(pdf, (int)path);
    } pdf_catch;

    
    RETURN_TRUE;
}
#endif /* PDFLIB_MAJORVERSION >= 8 */
/* }}} */

    
/* {{{ proto int PDF_delete_pvf(
resource p, string filename)
 * Delete a named virtual file and free its data structures (but not the contents) */
PHP_FUNCTION(pdf_delete_pvf)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_filename;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * filename;
    size_t filename_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"S", &z_filename)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        filename = ZSTR_VAL(z_filename);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"s", &filename, &filename_len)) {
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
"zS", &p, &z_filename)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        filename = ZSTR_VAL(z_filename);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rs", &p, &filename, &filename_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_delete_pvf(pdf, filename, 0);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto bool PDF_delete_table(
resource p, int table, string optlist)
 * Delete a table and all associated data structures */
PHP_FUNCTION(pdf_delete_table)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long table;
#else
    long table;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lS", &table, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ls", &table, &optlist, &optlist_len)) {
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
"zlS", &p, &table, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rls", &p, &table, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_delete_table(pdf, (int)table, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_delete_textflow(
resource p, int textflow)
 * Delete a textflow and all associated data structures */
PHP_FUNCTION(pdf_delete_textflow)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long textflow;
#else
    long textflow;
#endif


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &textflow)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &textflow)) {
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
"zl", &p, &textflow)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rl", &p, &textflow)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_delete_textflow(pdf, (int)textflow);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_draw_path(
resource p, int path, double x, double y, string optlist)
 * Draw a path object */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_draw_path)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long path;
#else
    long path;
#endif
    double x;
    double y;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lddS", &path, &x, &y, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ldds", &path, &x, &y, &optlist, &optlist_len)) {
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
"zlddS", &p, &path, &x, &y, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rldds", &p, &path, &x, &y, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_draw_path(pdf, (int)path, x, y, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
#endif /* PDFLIB_MAJORVERSION >= 8 */
/* }}} */

    
/* {{{ proto bool PDF_ellipse(
resource p, double x, double y, double rx, double ry)
 * Draw an ellipse */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_ellipse)
{
    PDF *pdf;
    double x;
    double y;
    double rx;
    double ry;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dddd", &x, &y, &rx, &ry)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dddd", &x, &y, &rx, &ry)) {
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
"zdddd", &p, &x, &y, &rx, &ry)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdddd", &p, &x, &y, &rx, &ry)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_ellipse(pdf, x, y, rx, ry);
    } pdf_catch;

    
    RETURN_TRUE;
}
#endif /* PDFLIB_MAJORVERSION >= 8 */
/* }}} */

    
/* {{{ proto bool PDF_elliptical_arc(
resource p, double x, double y, double rx, double ry, string optlist)
 * Draw an elliptical arc segment from the current point */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_elliptical_arc)
{
    PDF *pdf;
    double x;
    double y;
    double rx;
    double ry;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddddS", &x, &y, &rx, &ry, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dddds", &x, &y, &rx, &ry, &optlist, &optlist_len)) {
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
"zddddS", &p, &x, &y, &rx, &ry, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdddds", &p, &x, &y, &rx, &ry, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_elliptical_arc(pdf, x, y, rx, ry, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
/* }}} */

    
/* {{{ proto bool PDF_encoding_set_char(
resource p, string encoding, int slot, string glyphname, int uv)
 * Add a glyph name and/or Unicode value to a custom 8-bit encoding */
PHP_FUNCTION(pdf_encoding_set_char)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_encoding;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * encoding;
    size_t encoding_len;

#if PHP_MAJOR_VERSION >= 7
    zend_long slot;
#else
    long slot;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_glyphname;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * glyphname;
    size_t glyphname_len;

#if PHP_MAJOR_VERSION >= 7
    zend_long uv;
#else
    long uv;
#endif


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SlSl", &z_encoding, &slot, &z_glyphname, &uv)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        encoding = ZSTR_VAL(z_encoding);
        glyphname = ZSTR_VAL(z_glyphname);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"slsl", &encoding, &encoding_len, &slot, &glyphname, &glyphname_len, &uv)) {
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
"zSlSl", &p, &z_encoding, &slot, &z_glyphname, &uv)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        encoding = ZSTR_VAL(z_encoding);
        glyphname = ZSTR_VAL(z_glyphname);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rslsl", &p, &encoding, &encoding_len, &slot, &glyphname, &glyphname_len, &uv)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_encoding_set_char(pdf, encoding, (int)slot, glyphname, (int)uv);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_end_document(
resource p, string optlist)
 * Close the generated PDF document and apply various options */
PHP_FUNCTION(pdf_end_document)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"S", &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"s", &optlist, &optlist_len)) {
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
"zS", &p, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rs", &p, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_end_document(pdf, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_end_dpart(
resource p, string optlist)
 * Close a node in the document part hierarchy (requires PDF/VT or PDF 2.0) */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_end_dpart)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"S", &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"s", &optlist, &optlist_len)) {
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
"zS", &p, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rs", &p, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_end_dpart(pdf, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
/* }}} */

    
/* {{{ proto bool PDF_end_font(
resource p)
 * Terminate a Type 3 font definition */
PHP_FUNCTION(pdf_end_font)
{
    PDF *pdf;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_end_font(pdf);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_end_glyph(
resource p)
 * Terminate a glyph definition for a Type 3 font */
PHP_FUNCTION(pdf_end_glyph)
{
    PDF *pdf;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_end_glyph(pdf);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_end_item(
resource p, int id)
 * Close a structure element or other content item */
PHP_FUNCTION(pdf_end_item)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long id;
#else
    long id;
#endif


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &id)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &id)) {
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
"zl", &p, &id)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rl", &p, &id)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_end_item(pdf, (int)id);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_end_layer(
resource p)
 * Deactivate all active layers (requires PDF 1.5) */
PHP_FUNCTION(pdf_end_layer)
{
    PDF *pdf;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_end_layer(pdf);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_end_mc(
resource p)
 * End the least recently opened marked content sequence */
PHP_FUNCTION(pdf_end_mc)
{
    PDF *pdf;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_end_mc(pdf);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_end_page(
resource p)
 * Deprecated, use PDF_end_page_ext() */
PHP_FUNCTION(pdf_end_page)
{
    PDF *pdf;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_end_page_ext()");

    pdf_try {
	PDF_end_page(pdf);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_end_page_ext(
resource p, string optlist)
 * Finish a page, and apply various options */
PHP_FUNCTION(pdf_end_page_ext)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"S", &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"s", &optlist, &optlist_len)) {
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
"zS", &p, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rs", &p, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_end_page_ext(pdf, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_end_pattern(
resource p)
 * Finish a pattern definition */
PHP_FUNCTION(pdf_end_pattern)
{
    PDF *pdf;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_end_pattern(pdf);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_end_template(
resource p)
 * Deprecated, use PDF_end_template_ext() */
PHP_FUNCTION(pdf_end_template)
{
    PDF *pdf;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
    #if PDFLIB_MAJORVERSION >= 8
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_end_template_ext()");
    #endif /* PDFLIB_MAJORVERSION >= 8 */

    pdf_try {
	PDF_end_template(pdf);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_end_template_ext(
resource p, double width, double height)
 * Finish a template definition */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_end_template_ext)
{
    PDF *pdf;
    double width;
    double height;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &width, &height)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &width, &height)) {
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
"zdd", &p, &width, &height)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdd", &p, &width, &height)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_end_template_ext(pdf, width, height);
    } pdf_catch;

    
    RETURN_TRUE;
}
#endif /* PDFLIB_MAJORVERSION >= 8 */
/* }}} */

    
/* {{{ proto bool PDF_endpath(
resource p)
 * End the current path without filling or stroking it */
PHP_FUNCTION(pdf_endpath)
{
    PDF *pdf;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_endpath(pdf);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_fill(
resource p)
 * Fill the interior of the path with the current fill color */
PHP_FUNCTION(pdf_fill)
{
    PDF *pdf;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_fill(pdf);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto int PDF_fill_graphicsblock(
resource p, int page, string blockname, int graphics, string optlist)
 * Fill a graphics block with variable data according to its properties */
#if PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_fill_graphicsblock)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long page;
#else
    long page;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_blockname;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * blockname;
    size_t blockname_len;

#if PHP_MAJOR_VERSION >= 7
    zend_long graphics;
#else
    long graphics;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lSlS", &page, &z_blockname, &graphics, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        blockname = ZSTR_VAL(z_blockname);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lsls", &page, &blockname, &blockname_len, &graphics, &optlist, &optlist_len)) {
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
"zlSlS", &p, &page, &z_blockname, &graphics, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        blockname = ZSTR_VAL(z_blockname);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rlsls", &p, &page, &blockname, &blockname_len, &graphics, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_fill_graphicsblock(pdf, (int)page, blockname, (int)graphics, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
#endif /* PDFLIB_MAJORVERSION >= 9 */
/* }}} */

    
/* {{{ proto int PDF_fill_imageblock(
resource p, int page, string blockname, int image, string optlist)
 * Fill an image block with variable data according to its properties */
PHP_FUNCTION(pdf_fill_imageblock)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long page;
#else
    long page;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_blockname;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * blockname;
    size_t blockname_len;

#if PHP_MAJOR_VERSION >= 7
    zend_long image;
#else
    long image;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lSlS", &page, &z_blockname, &image, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        blockname = ZSTR_VAL(z_blockname);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lsls", &page, &blockname, &blockname_len, &image, &optlist, &optlist_len)) {
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
"zlSlS", &p, &page, &z_blockname, &image, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        blockname = ZSTR_VAL(z_blockname);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rlsls", &p, &page, &blockname, &blockname_len, &image, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_fill_imageblock(pdf, (int)page, blockname, (int)image, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto int PDF_fill_pdfblock(
resource p, int page, string blockname, int contents, string optlist)
 * Fill a PDF block with variable data according to its properties */
PHP_FUNCTION(pdf_fill_pdfblock)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long page;
#else
    long page;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_blockname;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * blockname;
    size_t blockname_len;

#if PHP_MAJOR_VERSION >= 7
    zend_long contents;
#else
    long contents;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lSlS", &page, &z_blockname, &contents, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        blockname = ZSTR_VAL(z_blockname);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lsls", &page, &blockname, &blockname_len, &contents, &optlist, &optlist_len)) {
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
"zlSlS", &p, &page, &z_blockname, &contents, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        blockname = ZSTR_VAL(z_blockname);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rlsls", &p, &page, &blockname, &blockname_len, &contents, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_fill_pdfblock(pdf, (int)page, blockname, (int)contents, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto bool PDF_fill_stroke(
resource p)
 * Fill a Textline or Textflow Block with variable data according to its properties */
PHP_FUNCTION(pdf_fill_stroke)
{
    PDF *pdf;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_fill_stroke(pdf);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto int PDF_fill_textblock(
resource p, int page, string blockname, string text, string optlist)
 * Fill a Textline or Textflow Block with variable data according to its properties */
PHP_FUNCTION(pdf_fill_textblock)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long page;
#else
    long page;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_blockname;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * blockname;
    size_t blockname_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_text;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * text;
    size_t text_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lSSS", &page, &z_blockname, &z_text, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        blockname = ZSTR_VAL(z_blockname);
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lsss", &page, &blockname, &blockname_len, &text, &text_len, &optlist, &optlist_len)) {
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
"zlSSS", &p, &page, &z_blockname, &z_text, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        blockname = ZSTR_VAL(z_blockname);
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rlsss", &p, &page, &blockname, &blockname_len, &text, &text_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_fill_textblock(pdf, (int)page, blockname, text, (int)text_len, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto int PDF_findfont(
resource p, string fontname, string encoding, int embed)
 * Deprecated, use  PDF_load_font() */
PHP_FUNCTION(pdf_findfont)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_fontname;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * fontname;
    size_t fontname_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_encoding;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * encoding;
    size_t encoding_len;

#if PHP_MAJOR_VERSION >= 7
    zend_long embed;
#else
    long embed;
#endif
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SSl", &z_fontname, &z_encoding, &embed)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        fontname = ZSTR_VAL(z_fontname);
        encoding = ZSTR_VAL(z_encoding);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ssl", &fontname, &fontname_len, &encoding, &encoding_len, &embed)) {
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
"zSSl", &p, &z_fontname, &z_encoding, &embed)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        fontname = ZSTR_VAL(z_fontname);
        encoding = ZSTR_VAL(z_encoding);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rssl", &p, &fontname, &fontname_len, &encoding, &encoding_len, &embed)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use  PDF_load_font()");

    pdf_try {
	_result = PDF_findfont(pdf, fontname, encoding, (int)embed);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto bool PDF_fit_graphics(
resource p, int graphics, double x, double y, string optlist)
 * Place vector graphics on a content stream, subject to various options */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_fit_graphics)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long graphics;
#else
    long graphics;
#endif
    double x;
    double y;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lddS", &graphics, &x, &y, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ldds", &graphics, &x, &y, &optlist, &optlist_len)) {
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
"zlddS", &p, &graphics, &x, &y, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rldds", &p, &graphics, &x, &y, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_fit_graphics(pdf, (int)graphics, x, y, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
/* }}} */

    
/* {{{ proto bool PDF_fit_image(
resource p, int image, double x, double y, string optlist)
 * Place an image or template on the page, subject to various options */
PHP_FUNCTION(pdf_fit_image)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long image;
#else
    long image;
#endif
    double x;
    double y;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lddS", &image, &x, &y, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ldds", &image, &x, &y, &optlist, &optlist_len)) {
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
"zlddS", &p, &image, &x, &y, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rldds", &p, &image, &x, &y, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_fit_image(pdf, (int)image, x, y, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_fit_pdi_page(
resource p, int page, double x, double y, string optlist)
 * Place an imported PDF page on the page subject to various options */
PHP_FUNCTION(pdf_fit_pdi_page)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long page;
#else
    long page;
#endif
    double x;
    double y;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lddS", &page, &x, &y, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ldds", &page, &x, &y, &optlist, &optlist_len)) {
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
"zlddS", &p, &page, &x, &y, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rldds", &p, &page, &x, &y, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_fit_pdi_page(pdf, (int)page, x, y, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto string PDF_fit_table(
resource p, int table, double llx, double lly, double urx, double ury, string optlist)
 * Fully or partially place a table on the page */
PHP_FUNCTION(pdf_fit_table)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long table;
#else
    long table;
#endif
    double llx;
    double lly;
    double urx;
    double ury;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    const char *_result = NULL;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lddddS", &table, &llx, &lly, &urx, &ury, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ldddds", &table, &llx, &lly, &urx, &ury, &optlist, &optlist_len)) {
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
"zlddddS", &p, &table, &llx, &lly, &urx, &ury, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rldddds", &p, &table, &llx, &lly, &urx, &ury, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_fit_table(pdf, (int)table, llx, lly, urx, ury, optlist);
    } pdf_catch;

    
#if PHP_MAJOR_VERSION >= 7
    {
        zend_string *z_result;
        if (_result) {
            z_result = zend_string_init(_result, strlen(_result), 0);
        } else {
            z_result = zend_string_init("", 1, 0);
        }
        RETURN_STR(z_result);
    }
#else /* PHP_MAJOR_VERSION >= 7 */
    RETURN_STRING(_result ? (char *)_result : "", 1);
#endif /* PHP_MAJOR_VERSION >= 7 */
}
/* }}} */

    
/* {{{ proto string PDF_fit_textflow(
resource p, int textflow, double llx, double lly, double urx, double ury, string optlist)
 * Format the next portion of a Textflow */
PHP_FUNCTION(pdf_fit_textflow)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long textflow;
#else
    long textflow;
#endif
    double llx;
    double lly;
    double urx;
    double ury;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    const char *_result = NULL;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lddddS", &textflow, &llx, &lly, &urx, &ury, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ldddds", &textflow, &llx, &lly, &urx, &ury, &optlist, &optlist_len)) {
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
"zlddddS", &p, &textflow, &llx, &lly, &urx, &ury, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rldddds", &p, &textflow, &llx, &lly, &urx, &ury, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_fit_textflow(pdf, (int)textflow, llx, lly, urx, ury, optlist);
    } pdf_catch;

    
#if PHP_MAJOR_VERSION >= 7
    {
        zend_string *z_result;
        if (_result) {
            z_result = zend_string_init(_result, strlen(_result), 0);
        } else {
            z_result = zend_string_init("", 1, 0);
        }
        RETURN_STR(z_result);
    }
#else /* PHP_MAJOR_VERSION >= 7 */
    RETURN_STRING(_result ? (char *)_result : "", 1);
#endif /* PHP_MAJOR_VERSION >= 7 */
}
/* }}} */

    
/* {{{ proto bool PDF_fit_textline(
resource p, string text, double x, double y, string optlist)
 * Place a single line of text at position (x, y) subject to various options */
PHP_FUNCTION(pdf_fit_textline)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_text;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * text;
    size_t text_len;
    double x;
    double y;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SddS", &z_text, &x, &y, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"sdds", &text, &text_len, &x, &y, &optlist, &optlist_len)) {
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
"zSddS", &p, &z_text, &x, &y, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rsdds", &p, &text, &text_len, &x, &y, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_fit_textline(pdf, text, (int)text_len, x, y, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto string PDF_get_apiname(
resource p)
 * Get the name of the API function which threw the last exception or failed */
PHP_FUNCTION(pdf_get_apiname)
{
    PDF *pdf;
    const char *_result = NULL;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_get_apiname(pdf);
    } pdf_catch;

    
#if PHP_MAJOR_VERSION >= 7
    {
        zend_string *z_result;
        if (_result) {
            z_result = zend_string_init(_result, strlen(_result), 0);
        } else {
            z_result = zend_string_init("", 1, 0);
        }
        RETURN_STR(z_result);
    }
#else /* PHP_MAJOR_VERSION >= 7 */
    RETURN_STRING(_result ? (char *)_result : "", 1);
#endif /* PHP_MAJOR_VERSION >= 7 */
}
/* }}} */

    
/* {{{ proto string PDF_get_buffer(
resource p)
 * Get the contents of the PDF output buffer */
PHP_FUNCTION(pdf_get_buffer)
{
    PDF *pdf;
    long outputlen;
    const char *_result = NULL;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result =  (const char *)PDF_get_buffer(pdf, &outputlen);
    } pdf_catch;

    
#if PHP_MAJOR_VERSION >= 7
    {
        zend_string *z_result;
        if (_result) {
            z_result = zend_string_alloc(outputlen, 0);
            memcpy(z_result->val, _result, outputlen);
        } else {
            z_result = zend_string_init("", 1, 0);
        }
        RETURN_STR(z_result);
    }
#else /* PHP_MAJOR_VERSION >= 7 */
    RETURN_STRINGL(_result ? (char *)_result : "", outputlen, 1);
#endif /* PHP_MAJOR_VERSION >= 7 */
}
/* }}} */

    
/* {{{ proto string PDF_get_errmsg(
resource p)
 * Get the text of the last thrown exception or the reason of a failed function call */
PHP_FUNCTION(pdf_get_errmsg)
{
    PDF *pdf;
    const char *_result = NULL;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_get_errmsg(pdf);
    } pdf_catch;

    
#if PHP_MAJOR_VERSION >= 7
    {
        zend_string *z_result;
        if (_result) {
            z_result = zend_string_init(_result, strlen(_result), 0);
        } else {
            z_result = zend_string_init("", 1, 0);
        }
        RETURN_STR(z_result);
    }
#else /* PHP_MAJOR_VERSION >= 7 */
    RETURN_STRING(_result ? (char *)_result : "", 1);
#endif /* PHP_MAJOR_VERSION >= 7 */
}
/* }}} */

    
/* {{{ proto int PDF_get_errnum(
resource p)
 * Get the number of the last thrown exception or the reason of a failed function call */
PHP_FUNCTION(pdf_get_errnum)
{
    PDF *pdf;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_get_errnum(pdf);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto double PDF_get_option(
resource p, string keyword, string optlist)
 * Retrieve some option or other value */
#if PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_get_option)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_keyword;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * keyword;
    size_t keyword_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    double _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_keyword, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        keyword = ZSTR_VAL(z_keyword);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &keyword, &keyword_len, &optlist, &optlist_len)) {
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
"zSS", &p, &z_keyword, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        keyword = ZSTR_VAL(z_keyword);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &keyword, &keyword_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_get_option(pdf, keyword, optlist);
    } pdf_catch;

    
    RETURN_DOUBLE(_result);
}
#endif /* PDFLIB_MAJORVERSION >= 9 */
/* }}} */

    
/* {{{ proto string PDF_get_parameter(
resource p, string key, double modifier)
 * Deprecated, use PDF_get_option() and PDF_get_string() */
PHP_FUNCTION(pdf_get_parameter)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_key;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * key;
    size_t key_len;
    double modifier;
    const char *_result = NULL;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"Sd", &z_key, &modifier)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        key = ZSTR_VAL(z_key);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"sd", &key, &key_len, &modifier)) {
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
"zSd", &p, &z_key, &modifier)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        key = ZSTR_VAL(z_key);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rsd", &p, &key, &key_len, &modifier)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
    #if PDFLIB_MAJORVERSION >= 9
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_get_option() and PDF_get_string()");
    #endif /* PDFLIB_MAJORVERSION >= 9 */

    pdf_try {
	_result = PDF_get_parameter(pdf, key, modifier);
    } pdf_catch;

    
#if PHP_MAJOR_VERSION >= 7
    {
        zend_string *z_result;
        if (_result) {
            z_result = zend_string_init(_result, strlen(_result), 0);
        } else {
            z_result = zend_string_init("", 1, 0);
        }
        RETURN_STR(z_result);
    }
#else /* PHP_MAJOR_VERSION >= 7 */
    RETURN_STRING(_result ? (char *)_result : "", 1);
#endif /* PHP_MAJOR_VERSION >= 7 */
}
/* }}} */

    
/* {{{ proto double PDF_get_pdi_value(
resource p, string key, int doc, int page, int reserved)
 * Deprecated, use PDF_pcos_get_number() */
PHP_FUNCTION(pdf_get_pdi_value)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_key;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * key;
    size_t key_len;

#if PHP_MAJOR_VERSION >= 7
    zend_long doc;
#else
    long doc;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_long page;
#else
    long page;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_long reserved;
#else
    long reserved;
#endif
    double _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"Slll", &z_key, &doc, &page, &reserved)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        key = ZSTR_VAL(z_key);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"slll", &key, &key_len, &doc, &page, &reserved)) {
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
"zSlll", &p, &z_key, &doc, &page, &reserved)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        key = ZSTR_VAL(z_key);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rslll", &p, &key, &key_len, &doc, &page, &reserved)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_pcos_get_number()");

    pdf_try {
	_result = PDF_get_pdi_value(pdf, key, (int)doc, (int)page, (int)reserved);
    } pdf_catch;

    
    RETURN_DOUBLE(_result);
}
/* }}} */

    
/* {{{ proto string PDF_get_string(
resource p, int idx, string optlist)
 * Retrieve a string value */
#if PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_get_string)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long idx;
#else
    long idx;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    const char *_result = NULL;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lS", &idx, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ls", &idx, &optlist, &optlist_len)) {
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
"zlS", &p, &idx, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rls", &p, &idx, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_get_string(pdf, (int)idx, optlist);
    } pdf_catch;

    
#if PHP_MAJOR_VERSION >= 7
    {
        zend_string *z_result;
        if (_result) {
            z_result = zend_string_init(_result, strlen(_result), 0);
        } else {
            z_result = zend_string_init("", 1, 0);
        }
        RETURN_STR(z_result);
    }
#else /* PHP_MAJOR_VERSION >= 7 */
    RETURN_STRING(_result ? (char *)_result : "", 1);
#endif /* PHP_MAJOR_VERSION >= 7 */
}
#endif /* PDFLIB_MAJORVERSION >= 9 */
/* }}} */

    
/* {{{ proto double PDF_get_value(
resource p, string key, double modifier)
 * Deprecated, use PDF_get_option() */
PHP_FUNCTION(pdf_get_value)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_key;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * key;
    size_t key_len;
    double modifier;
    double _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"Sd", &z_key, &modifier)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        key = ZSTR_VAL(z_key);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"sd", &key, &key_len, &modifier)) {
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
"zSd", &p, &z_key, &modifier)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        key = ZSTR_VAL(z_key);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rsd", &p, &key, &key_len, &modifier)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
    #if PDFLIB_MAJORVERSION >= 9
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_get_option()");
    #endif /* PDFLIB_MAJORVERSION >= 9 */

    pdf_try {
	_result = PDF_get_value(pdf, key, modifier);
    } pdf_catch;

    
    RETURN_DOUBLE(_result);
}
/* }}} */

    
/* {{{ proto double PDF_info_font(
resource p, int font, string keyword, string optlist)
 * Query detailed information about a loaded font */
PHP_FUNCTION(pdf_info_font)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long font;
#else
    long font;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_keyword;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * keyword;
    size_t keyword_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    double _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lSS", &font, &z_keyword, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        keyword = ZSTR_VAL(z_keyword);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lss", &font, &keyword, &keyword_len, &optlist, &optlist_len)) {
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
"zlSS", &p, &font, &z_keyword, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        keyword = ZSTR_VAL(z_keyword);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rlss", &p, &font, &keyword, &keyword_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_info_font(pdf, (int)font, keyword, optlist);
    } pdf_catch;

    
    RETURN_DOUBLE(_result);
}
/* }}} */

    
/* {{{ proto double PDF_info_graphics(
resource p, int graphics, string keyword, string optlist)
 * Format vector graphics and query metrics and other properties */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_info_graphics)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long graphics;
#else
    long graphics;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_keyword;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * keyword;
    size_t keyword_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    double _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lSS", &graphics, &z_keyword, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        keyword = ZSTR_VAL(z_keyword);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lss", &graphics, &keyword, &keyword_len, &optlist, &optlist_len)) {
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
"zlSS", &p, &graphics, &z_keyword, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        keyword = ZSTR_VAL(z_keyword);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rlss", &p, &graphics, &keyword, &keyword_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_info_graphics(pdf, (int)graphics, keyword, optlist);
    } pdf_catch;

    
    RETURN_DOUBLE(_result);
}
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
/* }}} */

    
/* {{{ proto double PDF_info_image(
resource p, int image, string keyword, string optlist)
 * Format an image and query metrics and other image properties */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_info_image)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long image;
#else
    long image;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_keyword;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * keyword;
    size_t keyword_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    double _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lSS", &image, &z_keyword, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        keyword = ZSTR_VAL(z_keyword);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lss", &image, &keyword, &keyword_len, &optlist, &optlist_len)) {
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
"zlSS", &p, &image, &z_keyword, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        keyword = ZSTR_VAL(z_keyword);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rlss", &p, &image, &keyword, &keyword_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_info_image(pdf, (int)image, keyword, optlist);
    } pdf_catch;

    
    RETURN_DOUBLE(_result);
}
#endif /* PDFLIB_MAJORVERSION >= 8 */
/* }}} */

    
/* {{{ proto double PDF_info_matchbox(
resource p, string boxname, int num, string keyword)
 * Query information about a matchbox on the current page */
PHP_FUNCTION(pdf_info_matchbox)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_boxname;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * boxname;
    size_t boxname_len;

#if PHP_MAJOR_VERSION >= 7
    zend_long num;
#else
    long num;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_keyword;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * keyword;
    size_t keyword_len;
    double _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SlS", &z_boxname, &num, &z_keyword)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        boxname = ZSTR_VAL(z_boxname);
        keyword = ZSTR_VAL(z_keyword);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"sls", &boxname, &boxname_len, &num, &keyword, &keyword_len)) {
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
"zSlS", &p, &z_boxname, &num, &z_keyword)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        boxname = ZSTR_VAL(z_boxname);
        keyword = ZSTR_VAL(z_keyword);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rsls", &p, &boxname, &boxname_len, &num, &keyword, &keyword_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_info_matchbox(pdf, boxname, 0, (int)num, keyword);
    } pdf_catch;

    
    RETURN_DOUBLE(_result);
}
/* }}} */

    
/* {{{ proto double PDF_info_path(
resource p, int path, string keyword, string optlist)
 * Query the results of drawing a path object without actually drawing it */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_info_path)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long path;
#else
    long path;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_keyword;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * keyword;
    size_t keyword_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    double _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lSS", &path, &z_keyword, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        keyword = ZSTR_VAL(z_keyword);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lss", &path, &keyword, &keyword_len, &optlist, &optlist_len)) {
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
"zlSS", &p, &path, &z_keyword, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        keyword = ZSTR_VAL(z_keyword);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rlss", &p, &path, &keyword, &keyword_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_info_path(pdf, (int)path, keyword, optlist);
    } pdf_catch;

    
    RETURN_DOUBLE(_result);
}
#endif /* PDFLIB_MAJORVERSION >= 8 */
/* }}} */

    
/* {{{ proto double PDF_info_pdi_page(
resource p, int page, string keyword, string optlist)
 * Perform formatting calculations for a PDI page and query the resulting metrics */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_info_pdi_page)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long page;
#else
    long page;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_keyword;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * keyword;
    size_t keyword_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    double _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lSS", &page, &z_keyword, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        keyword = ZSTR_VAL(z_keyword);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lss", &page, &keyword, &keyword_len, &optlist, &optlist_len)) {
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
"zlSS", &p, &page, &z_keyword, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        keyword = ZSTR_VAL(z_keyword);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rlss", &p, &page, &keyword, &keyword_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_info_pdi_page(pdf, (int)page, keyword, optlist);
    } pdf_catch;

    
    RETURN_DOUBLE(_result);
}
#endif /* PDFLIB_MAJORVERSION >= 8 */
/* }}} */

    
/* {{{ proto double PDF_info_pvf(
resource p, string filename, string keyword)
 * Query properties of a virtual file or the PDFlib Virtual Filesystem (PVF) */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_info_pvf)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_filename;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * filename;
    size_t filename_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_keyword;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * keyword;
    size_t keyword_len;
    double _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_filename, &z_keyword)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        filename = ZSTR_VAL(z_filename);
        keyword = ZSTR_VAL(z_keyword);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &filename, &filename_len, &keyword, &keyword_len)) {
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
"zSS", &p, &z_filename, &z_keyword)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        filename = ZSTR_VAL(z_filename);
        keyword = ZSTR_VAL(z_keyword);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &filename, &filename_len, &keyword, &keyword_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_info_pvf(pdf, filename, 0, keyword);
    } pdf_catch;

    
    RETURN_DOUBLE(_result);
}
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
/* }}} */

    
/* {{{ proto double PDF_info_table(
resource p, int table, string keyword)
 * Query table information related to the most recently placed table instance */
PHP_FUNCTION(pdf_info_table)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long table;
#else
    long table;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_keyword;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * keyword;
    size_t keyword_len;
    double _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lS", &table, &z_keyword)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        keyword = ZSTR_VAL(z_keyword);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ls", &table, &keyword, &keyword_len)) {
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
"zlS", &p, &table, &z_keyword)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        keyword = ZSTR_VAL(z_keyword);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rls", &p, &table, &keyword, &keyword_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_info_table(pdf, (int)table, keyword);
    } pdf_catch;

    
    RETURN_DOUBLE(_result);
}
/* }}} */

    
/* {{{ proto double PDF_info_textflow(
resource p, int textflow, string keyword)
 * Query the current state of a Textflow */
PHP_FUNCTION(pdf_info_textflow)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long textflow;
#else
    long textflow;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_keyword;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * keyword;
    size_t keyword_len;
    double _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lS", &textflow, &z_keyword)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        keyword = ZSTR_VAL(z_keyword);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ls", &textflow, &keyword, &keyword_len)) {
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
"zlS", &p, &textflow, &z_keyword)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        keyword = ZSTR_VAL(z_keyword);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rls", &p, &textflow, &keyword, &keyword_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_info_textflow(pdf, (int)textflow, keyword);
    } pdf_catch;

    
    RETURN_DOUBLE(_result);
}
/* }}} */

    
/* {{{ proto double PDF_info_textline(
resource p, string text, string keyword, string optlist)
 * Perform textline formatting without creating output and query the resulting metrics */
PHP_FUNCTION(pdf_info_textline)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_text;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * text;
    size_t text_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_keyword;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * keyword;
    size_t keyword_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    double _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SSS", &z_text, &z_keyword, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);
        keyword = ZSTR_VAL(z_keyword);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"sss", &text, &text_len, &keyword, &keyword_len, &optlist, &optlist_len)) {
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
"zSSS", &p, &z_text, &z_keyword, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);
        keyword = ZSTR_VAL(z_keyword);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rsss", &p, &text, &text_len, &keyword, &keyword_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_info_textline(pdf, text, (int)text_len, keyword, optlist);
    } pdf_catch;

    
    RETURN_DOUBLE(_result);
}
/* }}} */

    
/* {{{ proto bool PDF_initgraphics(
resource p)
 * Deprecated, use PDF_set_graphics_option() */
PHP_FUNCTION(pdf_initgraphics)
{
    PDF *pdf;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
    #if PDFLIB_MAJORVERSION >= 9
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_set_graphics_option()");
    #endif /* PDFLIB_MAJORVERSION >= 9 */

    pdf_try {
	PDF_initgraphics(pdf);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_lineto(
resource p, double x, double y)
 * Draw a line from the current point to another point */
PHP_FUNCTION(pdf_lineto)
{
    PDF *pdf;
    double x;
    double y;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &x, &y)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &x, &y)) {
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
"zdd", &p, &x, &y)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdd", &p, &x, &y)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_lineto(pdf, x, y);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto int PDF_load_3ddata(
resource p, string filename, string optlist)
 * Load a 3D model from a disk-based or virtual file (requires PDF 1.6) */
PHP_FUNCTION(pdf_load_3ddata)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_filename;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * filename;
    size_t filename_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_filename, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        filename = ZSTR_VAL(z_filename);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &filename, &filename_len, &optlist, &optlist_len)) {
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
"zSS", &p, &z_filename, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        filename = ZSTR_VAL(z_filename);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &filename, &filename_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_load_3ddata(pdf, filename, 0, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto int PDF_load_asset(
resource p, string type, string filename, string optlist)
 * Load a rich media asset or file attachment from a disk-based or virtual file */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_load_asset)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_type;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * type;
    size_t type_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_filename;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * filename;
    size_t filename_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SSS", &z_type, &z_filename, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        type = ZSTR_VAL(z_type);
        filename = ZSTR_VAL(z_filename);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"sss", &type, &type_len, &filename, &filename_len, &optlist, &optlist_len)) {
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
"zSSS", &p, &z_type, &z_filename, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        type = ZSTR_VAL(z_type);
        filename = ZSTR_VAL(z_filename);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rsss", &p, &type, &type_len, &filename, &filename_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_load_asset(pdf, type, filename, 0, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
/* }}} */

    
/* {{{ proto int PDF_load_font(
resource p, string fontname, string encoding, string optlist)
 * Search for a font and prepare it for later use */
PHP_FUNCTION(pdf_load_font)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_fontname;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * fontname;
    size_t fontname_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_encoding;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * encoding;
    size_t encoding_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SSS", &z_fontname, &z_encoding, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        fontname = ZSTR_VAL(z_fontname);
        encoding = ZSTR_VAL(z_encoding);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"sss", &fontname, &fontname_len, &encoding, &encoding_len, &optlist, &optlist_len)) {
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
"zSSS", &p, &z_fontname, &z_encoding, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        fontname = ZSTR_VAL(z_fontname);
        encoding = ZSTR_VAL(z_encoding);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rsss", &p, &fontname, &fontname_len, &encoding, &encoding_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_load_font(pdf, fontname, 0, encoding, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto int PDF_load_graphics(
resource p, string type, string filename, string optlist)
 * Open a disk-based or virtual vector graphics file subject to various options */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_load_graphics)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_type;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * type;
    size_t type_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_filename;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * filename;
    size_t filename_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SSS", &z_type, &z_filename, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        type = ZSTR_VAL(z_type);
        filename = ZSTR_VAL(z_filename);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"sss", &type, &type_len, &filename, &filename_len, &optlist, &optlist_len)) {
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
"zSSS", &p, &z_type, &z_filename, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        type = ZSTR_VAL(z_type);
        filename = ZSTR_VAL(z_filename);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rsss", &p, &type, &type_len, &filename, &filename_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_load_graphics(pdf, type, filename, 0, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
/* }}} */

    
/* {{{ proto int PDF_load_iccprofile(
resource p, string profilename, string optlist)
 * Search for an ICC profile, and prepare it for later use */
PHP_FUNCTION(pdf_load_iccprofile)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_profilename;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * profilename;
    size_t profilename_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_profilename, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        profilename = ZSTR_VAL(z_profilename);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &profilename, &profilename_len, &optlist, &optlist_len)) {
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
"zSS", &p, &z_profilename, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        profilename = ZSTR_VAL(z_profilename);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &profilename, &profilename_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_load_iccprofile(pdf, profilename, 0, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto int PDF_load_image(
resource p, string imagetype, string filename, string optlist)
 * Open a disk-based or virtual image file subject to various options */
PHP_FUNCTION(pdf_load_image)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_imagetype;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * imagetype;
    size_t imagetype_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_filename;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * filename;
    size_t filename_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SSS", &z_imagetype, &z_filename, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        imagetype = ZSTR_VAL(z_imagetype);
        filename = ZSTR_VAL(z_filename);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"sss", &imagetype, &imagetype_len, &filename, &filename_len, &optlist, &optlist_len)) {
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
"zSSS", &p, &z_imagetype, &z_filename, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        imagetype = ZSTR_VAL(z_imagetype);
        filename = ZSTR_VAL(z_filename);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rsss", &p, &imagetype, &imagetype_len, &filename, &filename_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_load_image(pdf, imagetype, filename, 0, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto int PDF_makespotcolor(
resource p, string spotname)
 * Find a built-in spot color name, or make a named spot color from the current fill color */
PHP_FUNCTION(pdf_makespotcolor)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_spotname;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * spotname;
    size_t spotname_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"S", &z_spotname)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        spotname = ZSTR_VAL(z_spotname);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"s", &spotname, &spotname_len)) {
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
"zS", &p, &z_spotname)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        spotname = ZSTR_VAL(z_spotname);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rs", &p, &spotname, &spotname_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_makespotcolor(pdf, spotname, 0);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto bool PDF_mc_point(
resource p, string tagname, string optlist)
 * Add a marked content point with optional properties */
PHP_FUNCTION(pdf_mc_point)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_tagname;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * tagname;
    size_t tagname_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_tagname, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        tagname = ZSTR_VAL(z_tagname);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &tagname, &tagname_len, &optlist, &optlist_len)) {
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
"zSS", &p, &z_tagname, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        tagname = ZSTR_VAL(z_tagname);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &tagname, &tagname_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_mc_point(pdf, tagname, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_moveto(
resource p, double x, double y)
 * Set the current point for graphics output */
PHP_FUNCTION(pdf_moveto)
{
    PDF *pdf;
    double x;
    double y;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &x, &y)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &x, &y)) {
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
"zdd", &p, &x, &y)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdd", &p, &x, &y)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_moveto(pdf, x, y);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto int PDF_open_ccitt(
resource p, string filename, int width, int height, int BitReverse, int K, int BlackIs1)
 * Deprecated, use PDF_load_image() */
PHP_FUNCTION(pdf_open_ccitt)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_filename;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * filename;
    size_t filename_len;

#if PHP_MAJOR_VERSION >= 7
    zend_long width;
#else
    long width;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_long height;
#else
    long height;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_long BitReverse;
#else
    long BitReverse;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_long K;
#else
    long K;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_long BlackIs1;
#else
    long BlackIs1;
#endif
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"Slllll", &z_filename, &width, &height, &BitReverse, &K, &BlackIs1)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        filename = ZSTR_VAL(z_filename);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"slllll", &filename, &filename_len, &width, &height, &BitReverse, &K, &BlackIs1)) {
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
"zSlllll", &p, &z_filename, &width, &height, &BitReverse, &K, &BlackIs1)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        filename = ZSTR_VAL(z_filename);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rslllll", &p, &filename, &filename_len, &width, &height, &BitReverse, &K, &BlackIs1)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_load_image()");

    pdf_try {
	_result = PDF_open_CCITT(pdf, filename, (int)width, (int)height, (int)BitReverse, (int)K, (int)BlackIs1);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto int PDF_open_file(
resource p, string filename)
 * Deprecated, use PDF_begin_document() */
PHP_FUNCTION(pdf_open_file)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_filename;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * filename;
    size_t filename_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"S", &z_filename)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        filename = ZSTR_VAL(z_filename);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"s", &filename, &filename_len)) {
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
"zS", &p, &z_filename)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        filename = ZSTR_VAL(z_filename);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rs", &p, &filename, &filename_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_begin_document()");

	if (filename && *filename) {
	    if (php_check_open_basedir(filename TSRMLS_CC)) {
		RETURN_FALSE;
	    }
	}
	
    pdf_try {
	_result = PDF_open_file(pdf, filename);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto int PDF_open_image_file(
resource p, string imagetype, string filename, string stringparam, int intparam)
 * Deprecated, use PDF_load_image() */
PHP_FUNCTION(pdf_open_image_file)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_imagetype;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * imagetype;
    size_t imagetype_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_filename;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * filename;
    size_t filename_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_stringparam;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * stringparam;
    size_t stringparam_len;

#if PHP_MAJOR_VERSION >= 7
    zend_long intparam;
#else
    long intparam;
#endif
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SSSl", &z_imagetype, &z_filename, &z_stringparam, &intparam)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        imagetype = ZSTR_VAL(z_imagetype);
        filename = ZSTR_VAL(z_filename);
        stringparam = ZSTR_VAL(z_stringparam);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"sssl", &imagetype, &imagetype_len, &filename, &filename_len, &stringparam, &stringparam_len, &intparam)) {
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
"zSSSl", &p, &z_imagetype, &z_filename, &z_stringparam, &intparam)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        imagetype = ZSTR_VAL(z_imagetype);
        filename = ZSTR_VAL(z_filename);
        stringparam = ZSTR_VAL(z_stringparam);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rsssl", &p, &imagetype, &imagetype_len, &filename, &filename_len, &stringparam, &stringparam_len, &intparam)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_load_image()");

    pdf_try {
	_result = PDF_open_image_file(pdf, imagetype, filename, stringparam, (int)intparam);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto int PDF_open_pdi_document(
resource p, string filename, string optlist)
 * Open a disk-based or virtual PDF document and prepare it for later use */
PHP_FUNCTION(pdf_open_pdi_document)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_filename;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * filename;
    size_t filename_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_filename, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        filename = ZSTR_VAL(z_filename);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &filename, &filename_len, &optlist, &optlist_len)) {
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
"zSS", &p, &z_filename, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        filename = ZSTR_VAL(z_filename);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &filename, &filename_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_open_pdi_document(pdf, filename, 0, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto int PDF_open_pdi_page(
resource p, int doc, int pagenumber, string optlist)
 * Prepare a page for later use with PDF_fit_pdi_page() */
PHP_FUNCTION(pdf_open_pdi_page)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long doc;
#else
    long doc;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_long pagenumber;
#else
    long pagenumber;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"llS", &doc, &pagenumber, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lls", &doc, &pagenumber, &optlist, &optlist_len)) {
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
"zllS", &p, &doc, &pagenumber, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rlls", &p, &doc, &pagenumber, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_open_pdi_page(pdf, (int)doc, (int)pagenumber, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto double PDF_pcos_get_number(
resource p, int doc, string path)
 * Get the value of a pCOS path with type number or boolean */
PHP_FUNCTION(pdf_pcos_get_number)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long doc;
#else
    long doc;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_path;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * path;
    size_t path_len;
    double _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lS", &doc, &z_path)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        path = ZSTR_VAL(z_path);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ls", &doc, &path, &path_len)) {
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
"zlS", &p, &doc, &z_path)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        path = ZSTR_VAL(z_path);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rls", &p, &doc, &path, &path_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_pcos_get_number(pdf, (int)doc, "%s", path);
    } pdf_catch;

    
    RETURN_DOUBLE(_result);
}
/* }}} */

    
/* {{{ proto string PDF_pcos_get_string(
resource p, int doc, string path)
 * Get the value of a pCOS path with type name, number, string, or boolean */
PHP_FUNCTION(pdf_pcos_get_string)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long doc;
#else
    long doc;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_path;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * path;
    size_t path_len;
    const char *_result = NULL;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lS", &doc, &z_path)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        path = ZSTR_VAL(z_path);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ls", &doc, &path, &path_len)) {
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
"zlS", &p, &doc, &z_path)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        path = ZSTR_VAL(z_path);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rls", &p, &doc, &path, &path_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_pcos_get_string(pdf, (int)doc, "%s", path);
    } pdf_catch;

    
#if PHP_MAJOR_VERSION >= 7
    {
        zend_string *z_result;
        if (_result) {
            z_result = zend_string_init(_result, strlen(_result), 0);
        } else {
            z_result = zend_string_init("", 1, 0);
        }
        RETURN_STR(z_result);
    }
#else /* PHP_MAJOR_VERSION >= 7 */
    RETURN_STRING(_result ? (char *)_result : "", 1);
#endif /* PHP_MAJOR_VERSION >= 7 */
}
/* }}} */

    
/* {{{ proto string PDF_pcos_get_stream(
resource p, int doc, string optlist, string path)
 * Get the contents of a pCOS path with type stream, fstream, or string */
PHP_FUNCTION(pdf_pcos_get_stream)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long doc;
#else
    long doc;
#endif
    int outputlen;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_path;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * path;
    size_t path_len;
    const unsigned char *_result = NULL;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lSS", &doc, &z_optlist, &z_path)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
        path = ZSTR_VAL(z_path);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lss", &doc, &optlist, &optlist_len, &path, &path_len)) {
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
"zlSS", &p, &doc, &z_optlist, &z_path)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);
        path = ZSTR_VAL(z_path);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rlss", &p, &doc, &optlist, &optlist_len, &path, &path_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result =  (const unsigned char *)PDF_pcos_get_stream(pdf, (int)doc, &outputlen, optlist, "%s", path);
    } pdf_catch;

    
#if PHP_MAJOR_VERSION >= 7
    {
        zend_string *z_result;
        if (_result) {
            z_result = zend_string_alloc(outputlen, 0);
            memcpy(z_result->val, _result, outputlen);
        } else {
            z_result = zend_string_init("", 1, 0);
        }
        RETURN_STR(z_result);
    }
#else /* PHP_MAJOR_VERSION >= 7 */
    RETURN_STRINGL(_result ? (char *)_result : "", outputlen, 1);
#endif /* PHP_MAJOR_VERSION >= 7 */
}
/* }}} */

    
/* {{{ proto bool PDF_place_image(
resource p, int image, double x, double y, double scale)
 * Deprecated, use PDF_fit_image() */
PHP_FUNCTION(pdf_place_image)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long image;
#else
    long image;
#endif
    double x;
    double y;
    double scale;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lddd", &image, &x, &y, &scale)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lddd", &image, &x, &y, &scale)) {
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
"zlddd", &p, &image, &x, &y, &scale)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rlddd", &p, &image, &x, &y, &scale)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_fit_image()");

    pdf_try {
	PDF_place_image(pdf, (int)image, x, y, scale);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_place_pdi_page(
resource p, int page, double x, double y, double sx, double sy)
 * Deprecated, use PDF_fit_pdi_page() */
PHP_FUNCTION(pdf_place_pdi_page)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long page;
#else
    long page;
#endif
    double x;
    double y;
    double sx;
    double sy;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ldddd", &page, &x, &y, &sx, &sy)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ldddd", &page, &x, &y, &sx, &sy)) {
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
"zldddd", &p, &page, &x, &y, &sx, &sy)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rldddd", &p, &page, &x, &y, &sx, &sy)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_fit_pdi_page()");

    pdf_try {
	PDF_place_pdi_page(pdf, (int)page, x, y, sx, sy);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_poca_delete(
resource p, int container, string optlist)
 * Delete a PDF container object */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_poca_delete)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long container;
#else
    long container;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lS", &container, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ls", &container, &optlist, &optlist_len)) {
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
"zlS", &p, &container, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rls", &p, &container, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_poca_delete(pdf, (int)container, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
/* }}} */

    
/* {{{ proto bool PDF_poca_insert(
resource p, int container, string optlist)
 * Insert a simple or container object in a PDF container object */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_poca_insert)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long container;
#else
    long container;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lS", &container, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ls", &container, &optlist, &optlist_len)) {
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
"zlS", &p, &container, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rls", &p, &container, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_poca_insert(pdf, (int)container, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
/* }}} */

    
/* {{{ proto int PDF_poca_new(
resource p, string optlist)
 * Create a new PDF container object of type dictionary, array, or stream and insert objects */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_poca_new)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"S", &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"s", &optlist, &optlist_len)) {
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
"zS", &p, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rs", &p, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_poca_new(pdf, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
/* }}} */

    
/* {{{ proto bool PDF_poca_remove(
resource p, int container, string optlist)
 * Remove a simple or container object from a PDF container object */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_poca_remove)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long container;
#else
    long container;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lS", &container, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ls", &container, &optlist, &optlist_len)) {
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
"zlS", &p, &container, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rls", &p, &container, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_poca_remove(pdf, (int)container, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
/* }}} */

    
/* {{{ proto int PDF_process_pdi(
resource p, int doc, int page, string optlist)
 * Process certain elements of an imported PDF document */
PHP_FUNCTION(pdf_process_pdi)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long doc;
#else
    long doc;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_long page;
#else
    long page;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"llS", &doc, &page, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lls", &doc, &page, &optlist, &optlist_len)) {
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
"zllS", &p, &doc, &page, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rlls", &p, &doc, &page, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_process_pdi(pdf, (int)doc, (int)page, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto bool PDF_rect(
resource p, double x, double y, double width, double height)
 * Draw a rectangle */
PHP_FUNCTION(pdf_rect)
{
    PDF *pdf;
    double x;
    double y;
    double width;
    double height;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dddd", &x, &y, &width, &height)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dddd", &x, &y, &width, &height)) {
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
"zdddd", &p, &x, &y, &width, &height)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdddd", &p, &x, &y, &width, &height)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_rect(pdf, x, y, width, height);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_restore(
resource p)
 * Restore the most recently saved graphics state from the stack */
PHP_FUNCTION(pdf_restore)
{
    PDF *pdf;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_restore(pdf);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_resume_page(
resource p, string optlist)
 * Resume a page to add more content to it */
PHP_FUNCTION(pdf_resume_page)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"S", &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"s", &optlist, &optlist_len)) {
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
"zS", &p, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rs", &p, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_resume_page(pdf, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_rotate(
resource p, double phi)
 * Rotate the coordinate system */
PHP_FUNCTION(pdf_rotate)
{
    PDF *pdf;
    double phi;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"d", &phi)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"d", &phi)) {
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
"zd", &p, &phi)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rd", &p, &phi)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_rotate(pdf, phi);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_save(
resource p)
 * Save the current graphics state to a stack */
PHP_FUNCTION(pdf_save)
{
    PDF *pdf;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_save(pdf);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_scale(
resource p, double sx, double sy)
 * Scale the coordinate system */
PHP_FUNCTION(pdf_scale)
{
    PDF *pdf;
    double sx;
    double sy;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &sx, &sy)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &sx, &sy)) {
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
"zdd", &p, &sx, &sy)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdd", &p, &sx, &sy)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_scale(pdf, sx, sy);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_set_border_color(
resource p, double red, double green, double blue)
 * Deprecated, use PDF_create_annotation() */
PHP_FUNCTION(pdf_set_border_color)
{
    PDF *pdf;
    double red;
    double green;
    double blue;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddd", &red, &green, &blue)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddd", &red, &green, &blue)) {
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
"zddd", &p, &red, &green, &blue)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rddd", &p, &red, &green, &blue)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_create_annotation()");

    pdf_try {
	PDF_set_border_color(pdf, red, green, blue);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_set_border_dash(
resource p, double b, double w)
 * Deprecated, use PDF_create_annotation() */
PHP_FUNCTION(pdf_set_border_dash)
{
    PDF *pdf;
    double b;
    double w;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &b, &w)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &b, &w)) {
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
"zdd", &p, &b, &w)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdd", &p, &b, &w)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_create_annotation()");

    pdf_try {
	PDF_set_border_dash(pdf, b, w);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_set_border_style(
resource p, string style, double width)
 * Deprecated, use PDF_create_annotation() */
PHP_FUNCTION(pdf_set_border_style)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_style;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * style;
    size_t style_len;
    double width;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"Sd", &z_style, &width)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        style = ZSTR_VAL(z_style);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"sd", &style, &style_len, &width)) {
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
"zSd", &p, &z_style, &width)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        style = ZSTR_VAL(z_style);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rsd", &p, &style, &style_len, &width)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_create_annotation()");

    pdf_try {
	PDF_set_border_style(pdf, style, width);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_set_graphics_option(
resource p, string optlist)
 * Set one or more graphics appearance options */
#if PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_set_graphics_option)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"S", &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"s", &optlist, &optlist_len)) {
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
"zS", &p, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rs", &p, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_set_graphics_option(pdf, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
#endif /* PDFLIB_MAJORVERSION >= 9 */
/* }}} */

    
/* {{{ proto bool PDF_set_gstate(
resource p, int gstate)
 * Activate a graphics state object */
PHP_FUNCTION(pdf_set_gstate)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long gstate;
#else
    long gstate;
#endif


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &gstate)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &gstate)) {
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
"zl", &p, &gstate)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rl", &p, &gstate)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_set_gstate(pdf, (int)gstate);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_set_info(
resource p, string key, string value)
 * Fill document information field key with value */
PHP_FUNCTION(pdf_set_info)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_key;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * key;
    size_t key_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_value;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * value;
    size_t value_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_key, &z_value)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        key = ZSTR_VAL(z_key);
        value = ZSTR_VAL(z_value);
        value_len = ZSTR_LEN(z_value);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &key, &key_len, &value, &value_len)) {
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
"zSS", &p, &z_key, &z_value)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        key = ZSTR_VAL(z_key);
        value = ZSTR_VAL(z_value);
        value_len = ZSTR_LEN(z_value);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &key, &key_len, &value, &value_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_set_info2(pdf, key, value, (int)value_len);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_set_layer_dependency(
resource p, string type, string optlist)
 * Define layer relationships (requires PDF 1.5) */
PHP_FUNCTION(pdf_set_layer_dependency)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_type;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * type;
    size_t type_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_type, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        type = ZSTR_VAL(z_type);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &type, &type_len, &optlist, &optlist_len)) {
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
"zSS", &p, &z_type, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        type = ZSTR_VAL(z_type);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &type, &type_len, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_set_layer_dependency(pdf, type, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_set_option(
resource p, string optlist)
 * Set one or more global options */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_set_option)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"S", &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"s", &optlist, &optlist_len)) {
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
"zS", &p, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rs", &p, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_set_option(pdf, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
#endif /* PDFLIB_MAJORVERSION >= 8 */
/* }}} */

    
/* {{{ proto bool PDF_set_parameter(
resource p, string key, string value)
 * Deprecated, use PDF_set_option(), PDF_set_text_option() and PDF_set_graphics_option() */
PHP_FUNCTION(pdf_set_parameter)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_key;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * key;
    size_t key_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_value;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * value;
    size_t value_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_key, &z_value)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        key = ZSTR_VAL(z_key);
        value = ZSTR_VAL(z_value);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &key, &key_len, &value, &value_len)) {
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
"zSS", &p, &z_key, &z_value)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        key = ZSTR_VAL(z_key);
        value = ZSTR_VAL(z_value);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &key, &key_len, &value, &value_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
    #if PDFLIB_MAJORVERSION >= 9
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_set_option(), PDF_set_text_option() and PDF_set_graphics_option()");
    #endif /* PDFLIB_MAJORVERSION >= 9 */

    pdf_try {
	PDF_set_parameter(pdf, key, value);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_set_text_option(
resource p, string optlist)
 * Set one or more text filter or text appearance options for simple text output functions */
#if PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_set_text_option)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"S", &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"s", &optlist, &optlist_len)) {
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
"zS", &p, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rs", &p, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_set_text_option(pdf, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
#endif /* PDFLIB_MAJORVERSION >= 9 */
/* }}} */

    
/* {{{ proto bool PDF_set_text_pos(
resource p, double x, double y)
 * Set the position for simple text output on the page */
PHP_FUNCTION(pdf_set_text_pos)
{
    PDF *pdf;
    double x;
    double y;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &x, &y)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &x, &y)) {
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
"zdd", &p, &x, &y)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdd", &p, &x, &y)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_set_text_pos(pdf, x, y);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_set_value(
resource p, string key, double value)
 * Deprecated, use PDF_set_option(), PDF_set_text_option() and PDF_set_graphics_option(). */
PHP_FUNCTION(pdf_set_value)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_key;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * key;
    size_t key_len;
    double value;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"Sd", &z_key, &value)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        key = ZSTR_VAL(z_key);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"sd", &key, &key_len, &value)) {
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
"zSd", &p, &z_key, &value)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        key = ZSTR_VAL(z_key);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rsd", &p, &key, &key_len, &value)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
    #if PDFLIB_MAJORVERSION >= 9
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_set_option(), PDF_set_text_option() and PDF_set_graphics_option().");
    #endif /* PDFLIB_MAJORVERSION >= 9 */

    pdf_try {
	PDF_set_value(pdf, key, value);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_setcolor(
resource p, string fstype, string colorspace, double c1, double c2, double c3, double c4)
 * Set the color space and color for the graphics and text state. */
PHP_FUNCTION(pdf_setcolor)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_fstype;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * fstype;
    size_t fstype_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_colorspace;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * colorspace;
    size_t colorspace_len;
    double c1;
    double c2;
    double c3;
    double c4;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SSdddd", &z_fstype, &z_colorspace, &c1, &c2, &c3, &c4)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        fstype = ZSTR_VAL(z_fstype);
        colorspace = ZSTR_VAL(z_colorspace);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ssdddd", &fstype, &fstype_len, &colorspace, &colorspace_len, &c1, &c2, &c3, &c4)) {
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
"zSSdddd", &p, &z_fstype, &z_colorspace, &c1, &c2, &c3, &c4)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        fstype = ZSTR_VAL(z_fstype);
        colorspace = ZSTR_VAL(z_colorspace);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rssdddd", &p, &fstype, &fstype_len, &colorspace, &colorspace_len, &c1, &c2, &c3, &c4)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_setcolor(pdf, fstype, colorspace, c1, c2, c3, c4);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_setdash(
resource p, double b, double w)
 * Deprecated, use PDF_set_graphics_option() */
PHP_FUNCTION(pdf_setdash)
{
    PDF *pdf;
    double b;
    double w;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &b, &w)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &b, &w)) {
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
"zdd", &p, &b, &w)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdd", &p, &b, &w)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
    #if PDFLIB_MAJORVERSION >= 9
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_set_graphics_option()");
    #endif /* PDFLIB_MAJORVERSION >= 9 */

    pdf_try {
	PDF_setdash(pdf, b, w);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_setdashpattern(
resource p, string optlist)
 * Deprecated, use PDF_set_graphics_option() */
PHP_FUNCTION(pdf_setdashpattern)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"S", &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"s", &optlist, &optlist_len)) {
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
"zS", &p, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rs", &p, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
    #if PDFLIB_MAJORVERSION >= 9
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_set_graphics_option()");
    #endif /* PDFLIB_MAJORVERSION >= 9 */

    pdf_try {
	PDF_setdashpattern(pdf, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_setflat(
resource p, double flatness)
 * Deprecated, use PDF_set_graphics_option() */
PHP_FUNCTION(pdf_setflat)
{
    PDF *pdf;
    double flatness;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"d", &flatness)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"d", &flatness)) {
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
"zd", &p, &flatness)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rd", &p, &flatness)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
    #if PDFLIB_MAJORVERSION >= 9
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_set_graphics_option()");
    #endif /* PDFLIB_MAJORVERSION >= 9 */

    pdf_try {
	PDF_setflat(pdf, flatness);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_setfont(
resource p, int font, double fontsize)
 * Set the current font in the specified size */
PHP_FUNCTION(pdf_setfont)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long font;
#else
    long font;
#endif
    double fontsize;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ld", &font, &fontsize)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ld", &font, &fontsize)) {
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
"zld", &p, &font, &fontsize)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rld", &p, &font, &fontsize)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_setfont(pdf, (int)font, fontsize);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_setgray(
resource p, double gray)
 * Deprecated, use PDF_setcolor() */
PHP_FUNCTION(pdf_setgray)
{
    PDF *pdf;
    double gray;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"d", &gray)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"d", &gray)) {
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
"zd", &p, &gray)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rd", &p, &gray)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_setcolor()");

    pdf_try {
	PDF_setgray(pdf, gray);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_setgray_fill(
resource p, double gray)
 * Deprecated, use PDF_setcolor() */
PHP_FUNCTION(pdf_setgray_fill)
{
    PDF *pdf;
    double gray;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"d", &gray)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"d", &gray)) {
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
"zd", &p, &gray)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rd", &p, &gray)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_setcolor()");

    pdf_try {
	PDF_setgray_fill(pdf, gray);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_setgray_stroke(
resource p, double gray)
 * Deprecated, use PDF_setcolor() */
PHP_FUNCTION(pdf_setgray_stroke)
{
    PDF *pdf;
    double gray;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"d", &gray)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"d", &gray)) {
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
"zd", &p, &gray)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rd", &p, &gray)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_setcolor()");

    pdf_try {
	PDF_setgray_stroke(pdf, gray);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_setlinecap(
resource p, int linecap)
 * Deprecated, use PDF_set_graphics_option() */
PHP_FUNCTION(pdf_setlinecap)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long linecap;
#else
    long linecap;
#endif


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &linecap)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &linecap)) {
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
"zl", &p, &linecap)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rl", &p, &linecap)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
    #if PDFLIB_MAJORVERSION >= 9
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_set_graphics_option()");
    #endif /* PDFLIB_MAJORVERSION >= 9 */

    pdf_try {
	PDF_setlinecap(pdf, (int)linecap);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_setlinejoin(
resource p, int linejoin)
 * Deprecated, use PDF_set_graphics_option() */
PHP_FUNCTION(pdf_setlinejoin)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long linejoin;
#else
    long linejoin;
#endif


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &linejoin)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &linejoin)) {
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
"zl", &p, &linejoin)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rl", &p, &linejoin)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
    #if PDFLIB_MAJORVERSION >= 9
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_set_graphics_option()");
    #endif /* PDFLIB_MAJORVERSION >= 9 */

    pdf_try {
	PDF_setlinejoin(pdf, (int)linejoin);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_setlinewidth(
resource p, double width)
 * Set the current linewidth */
PHP_FUNCTION(pdf_setlinewidth)
{
    PDF *pdf;
    double width;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"d", &width)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"d", &width)) {
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
"zd", &p, &width)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rd", &p, &width)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_setlinewidth(pdf, width);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_setmatrix(
resource p, double a, double b, double c, double d, double e, double f)
 * Explicitly set the current transformation matrix */
PHP_FUNCTION(pdf_setmatrix)
{
    PDF *pdf;
    double a;
    double b;
    double c;
    double d;
    double e;
    double f;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dddddd", &a, &b, &c, &d, &e, &f)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dddddd", &a, &b, &c, &d, &e, &f)) {
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
"zdddddd", &p, &a, &b, &c, &d, &e, &f)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdddddd", &p, &a, &b, &c, &d, &e, &f)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_setmatrix(pdf, a, b, c, d, e, f);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_setmiterlimit(
resource p, double miter)
 * Deprecated, use PDF_set_graphics_option() */
PHP_FUNCTION(pdf_setmiterlimit)
{
    PDF *pdf;
    double miter;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"d", &miter)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"d", &miter)) {
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
"zd", &p, &miter)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rd", &p, &miter)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
    #if PDFLIB_MAJORVERSION >= 9
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_set_graphics_option()");
    #endif /* PDFLIB_MAJORVERSION >= 9 */

    pdf_try {
	PDF_setmiterlimit(pdf, miter);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_setrgbcolor(
resource p, double red, double green, double blue)
 * Deprecated, use PDF_setcolor() */
PHP_FUNCTION(pdf_setrgbcolor)
{
    PDF *pdf;
    double red;
    double green;
    double blue;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddd", &red, &green, &blue)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddd", &red, &green, &blue)) {
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
"zddd", &p, &red, &green, &blue)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rddd", &p, &red, &green, &blue)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_setcolor()");

    pdf_try {
	PDF_setrgbcolor(pdf, red, green, blue);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_setrgbcolor_fill(
resource p, double red, double green, double blue)
 * Deprecated, use PDF_setcolor() */
PHP_FUNCTION(pdf_setrgbcolor_fill)
{
    PDF *pdf;
    double red;
    double green;
    double blue;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddd", &red, &green, &blue)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddd", &red, &green, &blue)) {
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
"zddd", &p, &red, &green, &blue)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rddd", &p, &red, &green, &blue)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_setcolor()");

    pdf_try {
	PDF_setrgbcolor_fill(pdf, red, green, blue);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_setrgbcolor_stroke(
resource p, double red, double green, double blue)
 * Deprecated, use PDF_setcolor() */
PHP_FUNCTION(pdf_setrgbcolor_stroke)
{
    PDF *pdf;
    double red;
    double green;
    double blue;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddd", &red, &green, &blue)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ddd", &red, &green, &blue)) {
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
"zddd", &p, &red, &green, &blue)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rddd", &p, &red, &green, &blue)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_setcolor()");

    pdf_try {
	PDF_setrgbcolor_stroke(pdf, red, green, blue);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto int PDF_shading(
resource p, string type, double x0, double y0, double x1, double y1, double c1, double c2, double c3, double c4, string optlist)
 * Define a shading (color gradient) between two or more colors */
PHP_FUNCTION(pdf_shading)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_type;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * type;
    size_t type_len;
    double x0;
    double y0;
    double x1;
    double y1;
    double c1;
    double c2;
    double c3;
    double c4;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SddddddddS", &z_type, &x0, &y0, &x1, &y1, &c1, &c2, &c3, &c4, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        type = ZSTR_VAL(z_type);
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"sdddddddds", &type, &type_len, &x0, &y0, &x1, &y1, &c1, &c2, &c3, &c4, &optlist, &optlist_len)) {
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
"zSddddddddS", &p, &z_type, &x0, &y0, &x1, &y1, &c1, &c2, &c3, &c4, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        type = ZSTR_VAL(z_type);
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rsdddddddds", &p, &type, &type_len, &x0, &y0, &x1, &y1, &c1, &c2, &c3, &c4, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_shading(pdf, type, x0, y0, x1, y1, c1, c2, c3, c4, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto int PDF_shading_pattern(
resource p, int shading, string optlist)
 * Define a shading pattern using a shading object */
PHP_FUNCTION(pdf_shading_pattern)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long shading;
#else
    long shading;
#endif

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;
    int _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"lS", &shading, &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ls", &shading, &optlist, &optlist_len)) {
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
"zlS", &p, &shading, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rls", &p, &shading, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_shading_pattern(pdf, (int)shading, optlist);
    } pdf_catch;

    
    RETURN_LONG(_result);
}
/* }}} */

    
/* {{{ proto bool PDF_shfill(
resource p, int shading)
 * Fill an area with a shading, based on a shading object */
PHP_FUNCTION(pdf_shfill)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_long shading;
#else
    long shading;
#endif


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &shading)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"l", &shading)) {
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
"zl", &p, &shading)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rl", &p, &shading)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_shfill(pdf, (int)shading);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_show(
resource p, string text)
 * Print text in the current font and size at the current position */
PHP_FUNCTION(pdf_show)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_text;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * text;
    size_t text_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"S", &z_text)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"s", &text, &text_len)) {
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
"zS", &p, &z_text)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rs", &p, &text, &text_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_show2(pdf, text, (int)text_len);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_show_xy(
resource p, string text, double x, double y)
 * Print text in the current font at the specified position */
PHP_FUNCTION(pdf_show_xy)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_text;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * text;
    size_t text_len;
    double x;
    double y;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"Sdd", &z_text, &x, &y)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"sdd", &text, &text_len, &x, &y)) {
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
"zSdd", &p, &z_text, &x, &y)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rsdd", &p, &text, &text_len, &x, &y)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_show_xy2(pdf, text, (int)text_len, x, y);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_skew(
resource p, double alpha, double beta)
 * Skew the coordinate system */
PHP_FUNCTION(pdf_skew)
{
    PDF *pdf;
    double alpha;
    double beta;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &alpha, &beta)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &alpha, &beta)) {
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
"zdd", &p, &alpha, &beta)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdd", &p, &alpha, &beta)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_skew(pdf, alpha, beta);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto double PDF_stringwidth(
resource p, string text, int font, double fontsize)
 * Calculate the width of text in an arbitrary font */
PHP_FUNCTION(pdf_stringwidth)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_text;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * text;
    size_t text_len;

#if PHP_MAJOR_VERSION >= 7
    zend_long font;
#else
    long font;
#endif
    double fontsize;
    double _result = 0;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"Sld", &z_text, &font, &fontsize)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"sld", &text, &text_len, &font, &fontsize)) {
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
"zSld", &p, &z_text, &font, &fontsize)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        text = ZSTR_VAL(z_text);
        text_len = ZSTR_LEN(z_text);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rsld", &p, &text, &text_len, &font, &fontsize)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	_result = PDF_stringwidth2(pdf, text, (int)text_len, (int)font, fontsize);
    } pdf_catch;

    
    RETURN_DOUBLE(_result);
}
/* }}} */

    
/* {{{ proto bool PDF_stroke(
resource p)
 * Stroke the path with the current color and line width, and clear it */
PHP_FUNCTION(pdf_stroke)
{
    PDF *pdf;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"")) {
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
"z", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"r", &p)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_stroke(pdf);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_suspend_page(
resource p, string optlist)
 * Suspend the current page so that it can later be resumed */
PHP_FUNCTION(pdf_suspend_page)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_optlist;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * optlist;
    size_t optlist_len;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"S", &z_optlist)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        optlist = ZSTR_VAL(z_optlist);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"s", &optlist, &optlist_len)) {
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
"zS", &p, &z_optlist)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        optlist = ZSTR_VAL(z_optlist);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rs", &p, &optlist, &optlist_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_suspend_page(pdf, optlist);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto bool PDF_translate(
resource p, double tx, double ty)
 * Translate the origin of the coordinate system */
PHP_FUNCTION(pdf_translate)
{
    PDF *pdf;
    double tx;
    double ty;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &tx, &ty)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"dd", &tx, &ty)) {
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
"zdd", &p, &tx, &ty)) {
		RESTORE_ERROR_HANDLING();
                return;
            }

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rdd", &p, &tx, &ty)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();

    pdf_try {
	PDF_translate(pdf, tx, ty);
    } pdf_catch;

    
    RETURN_TRUE;
}
/* }}} */

    
/* {{{ proto string PDF_utf16_to_utf8(
resource p, string utf16string)
 * Deprecated, use PDF_convert_to_unicode() */
PHP_FUNCTION(pdf_utf16_to_utf8)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_utf16string;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * utf16string;
    size_t utf16string_len;
    int outputlen;
    const char *_result = NULL;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"S", &z_utf16string)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        utf16string = ZSTR_VAL(z_utf16string);
        utf16string_len = ZSTR_LEN(z_utf16string);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"s", &utf16string, &utf16string_len)) {
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
"zS", &p, &z_utf16string)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        utf16string = ZSTR_VAL(z_utf16string);
        utf16string_len = ZSTR_LEN(z_utf16string);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rs", &p, &utf16string, &utf16string_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
    #if PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_convert_to_unicode()");
    #endif /* PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1 */

    pdf_try {
	_result =  (const char *)PDF_utf16_to_utf8(pdf, utf16string, (int)utf16string_len, &outputlen);
    } pdf_catch;

    
#if PHP_MAJOR_VERSION >= 7
    {
        zend_string *z_result;
        if (_result) {
            z_result = zend_string_alloc(outputlen, 0);
            memcpy(z_result->val, _result, outputlen);
        } else {
            z_result = zend_string_init("", 1, 0);
        }
        RETURN_STR(z_result);
    }
#else /* PHP_MAJOR_VERSION >= 7 */
    RETURN_STRINGL(_result ? (char *)_result : "", outputlen, 1);
#endif /* PHP_MAJOR_VERSION >= 7 */
}
/* }}} */

    
/* {{{ proto string PDF_utf8_to_utf16(
resource p, string utf8string, string ordering)
 * Deprecated, use PDF_convert_to_unicode() */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_utf8_to_utf16)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_utf8string;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * utf8string;
    size_t utf8string_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_ordering;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * ordering;
    size_t ordering_len;
    int outputlen;
    const char *_result = NULL;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_utf8string, &z_ordering)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        utf8string = ZSTR_VAL(z_utf8string);
        ordering = ZSTR_VAL(z_ordering);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &utf8string, &utf8string_len, &ordering, &ordering_len)) {
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
"zSS", &p, &z_utf8string, &z_ordering)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        utf8string = ZSTR_VAL(z_utf8string);
        ordering = ZSTR_VAL(z_ordering);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &utf8string, &utf8string_len, &ordering, &ordering_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
    #if PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_convert_to_unicode()");
    #endif /* PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1 */

    pdf_try {
	_result =  (const char *)PDF_utf8_to_utf16(pdf, utf8string, ordering, &outputlen);
    } pdf_catch;

    
#if PHP_MAJOR_VERSION >= 7
    {
        zend_string *z_result;
        if (_result) {
            z_result = zend_string_alloc(outputlen, 0);
            memcpy(z_result->val, _result, outputlen);
        } else {
            z_result = zend_string_init("", 1, 0);
        }
        RETURN_STR(z_result);
    }
#else /* PHP_MAJOR_VERSION >= 7 */
    RETURN_STRINGL(_result ? (char *)_result : "", outputlen, 1);
#endif /* PHP_MAJOR_VERSION >= 7 */
}
#endif /* PDFLIB_MAJORVERSION >= 8 */
/* }}} */

    
/* {{{ proto string PDF_utf32_to_utf8(
resource p, string utf32string)
 * Deprecated, use PDF_convert_to_unicode() */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_utf32_to_utf8)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_utf32string;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * utf32string;
    size_t utf32string_len;
    int outputlen;
    const char *_result = NULL;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"S", &z_utf32string)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        utf32string = ZSTR_VAL(z_utf32string);
        utf32string_len = ZSTR_LEN(z_utf32string);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"s", &utf32string, &utf32string_len)) {
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
"zS", &p, &z_utf32string)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        utf32string = ZSTR_VAL(z_utf32string);
        utf32string_len = ZSTR_LEN(z_utf32string);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rs", &p, &utf32string, &utf32string_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
    #if PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_convert_to_unicode()");
    #endif /* PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1 */

    pdf_try {
	_result =  (const char *)PDF_utf32_to_utf8(pdf, utf32string, (int)utf32string_len, &outputlen);
    } pdf_catch;

    
#if PHP_MAJOR_VERSION >= 7
    {
        zend_string *z_result;
        if (_result) {
            z_result = zend_string_alloc(outputlen, 0);
            memcpy(z_result->val, _result, outputlen);
        } else {
            z_result = zend_string_init("", 1, 0);
        }
        RETURN_STR(z_result);
    }
#else /* PHP_MAJOR_VERSION >= 7 */
    RETURN_STRINGL(_result ? (char *)_result : "", outputlen, 1);
#endif /* PHP_MAJOR_VERSION >= 7 */
}
#endif /* PDFLIB_MAJORVERSION >= 8 */
/* }}} */

    
/* {{{ proto string PDF_utf8_to_utf32(
resource p, string utf8string, string ordering)
 * Deprecated, use PDF_convert_to_unicode() */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_utf8_to_utf32)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_utf8string;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * utf8string;
    size_t utf8string_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_ordering;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * ordering;
    size_t ordering_len;
    int outputlen;
    const char *_result = NULL;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_utf8string, &z_ordering)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        utf8string = ZSTR_VAL(z_utf8string);
        ordering = ZSTR_VAL(z_ordering);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &utf8string, &utf8string_len, &ordering, &ordering_len)) {
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
"zSS", &p, &z_utf8string, &z_ordering)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        utf8string = ZSTR_VAL(z_utf8string);
        ordering = ZSTR_VAL(z_ordering);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &utf8string, &utf8string_len, &ordering, &ordering_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
    #if PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_convert_to_unicode()");
    #endif /* PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1 */

    pdf_try {
	_result =  (const char *)PDF_utf8_to_utf32(pdf, utf8string, ordering, &outputlen);
    } pdf_catch;

    
#if PHP_MAJOR_VERSION >= 7
    {
        zend_string *z_result;
        if (_result) {
            z_result = zend_string_alloc(outputlen, 0);
            memcpy(z_result->val, _result, outputlen);
        } else {
            z_result = zend_string_init("", 1, 0);
        }
        RETURN_STR(z_result);
    }
#else /* PHP_MAJOR_VERSION >= 7 */
    RETURN_STRINGL(_result ? (char *)_result : "", outputlen, 1);
#endif /* PHP_MAJOR_VERSION >= 7 */
}
#endif /* PDFLIB_MAJORVERSION >= 8 */
/* }}} */

    
/* {{{ proto string PDF_utf16_to_utf32(
resource p, string utf16string, string ordering)
 * Deprecated, use PDF_convert_to_unicode() */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_utf16_to_utf32)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_utf16string;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * utf16string;
    size_t utf16string_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_ordering;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * ordering;
    size_t ordering_len;
    int outputlen;
    const char *_result = NULL;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_utf16string, &z_ordering)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        utf16string = ZSTR_VAL(z_utf16string);
        utf16string_len = ZSTR_LEN(z_utf16string);
        ordering = ZSTR_VAL(z_ordering);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &utf16string, &utf16string_len, &ordering, &ordering_len)) {
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
"zSS", &p, &z_utf16string, &z_ordering)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        utf16string = ZSTR_VAL(z_utf16string);
        utf16string_len = ZSTR_LEN(z_utf16string);
        ordering = ZSTR_VAL(z_ordering);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &utf16string, &utf16string_len, &ordering, &ordering_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
    #if PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_convert_to_unicode()");
    #endif /* PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1 */

    pdf_try {
	_result =  (const char *)PDF_utf16_to_utf32(pdf, utf16string, (int)utf16string_len, ordering, &outputlen);
    } pdf_catch;

    
#if PHP_MAJOR_VERSION >= 7
    {
        zend_string *z_result;
        if (_result) {
            z_result = zend_string_alloc(outputlen, 0);
            memcpy(z_result->val, _result, outputlen);
        } else {
            z_result = zend_string_init("", 1, 0);
        }
        RETURN_STR(z_result);
    }
#else /* PHP_MAJOR_VERSION >= 7 */
    RETURN_STRINGL(_result ? (char *)_result : "", outputlen, 1);
#endif /* PHP_MAJOR_VERSION >= 7 */
}
#endif /* PDFLIB_MAJORVERSION >= 8 */
/* }}} */

    
/* {{{ proto string PDF_utf32_to_utf16(
resource p, string utf32string, string ordering)
 * Deprecated, use PDF_convert_to_unicode() */
PHP_FUNCTION(pdf_utf32_to_utf16)
{
    PDF *pdf;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_utf32string;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * utf32string;
    size_t utf32string_len;

#if PHP_MAJOR_VERSION >= 7
    zend_string * z_ordering;
#endif /* PHP_MAJOR_VERSION >= 7 */
    const char * ordering;
    size_t ordering_len;
    int outputlen;
    const char *_result = NULL;


    zval *object = getThis();
    DEFINE_ERROR_HANDLER

    if (object) {
        SET_ERROR_HANDLING(EH_THROW, pdflib_exception_class);
#if PHP_MAJOR_VERSION >= 7
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"SS", &z_utf32string, &z_ordering)) {
            RESTORE_ERROR_HANDLING();
            return;
        }
        utf32string = ZSTR_VAL(z_utf32string);
        utf32string_len = ZSTR_LEN(z_utf32string);
        ordering = ZSTR_VAL(z_ordering);
#else /* PHP_MAJOR_VERSION >= 7 */
        if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"ss", &utf32string, &utf32string_len, &ordering, &ordering_len)) {
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
"zSS", &p, &z_utf32string, &z_ordering)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
        utf32string = ZSTR_VAL(z_utf32string);
        utf32string_len = ZSTR_LEN(z_utf32string);
        ordering = ZSTR_VAL(z_ordering);

            ZEND_FETCH_RESOURCE(pdf, PDF *, p, -1, "pdf object", le_pdf);
#else /* PHP_MAJOR_VERSION >= 7 */
            if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
"rss", &p, &utf32string, &utf32string_len, &ordering, &ordering_len)) {
		RESTORE_ERROR_HANDLING();
                return;
            }
            ZEND_FETCH_RESOURCE(pdf, PDF *, &p, -1, "pdf object", le_pdf);
#endif /* PHP_MAJOR_VERSION >= 7 */
        }
    }
    RESTORE_ERROR_HANDLING();
    #if PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1
php_error_docref(NULL TSRMLS_CC, E_DEPRECATED, "Deprecated, use PDF_convert_to_unicode()");
    #endif /* PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1 */

    pdf_try {
	_result =  (const char *)PDF_utf32_to_utf16(pdf, utf32string, (int)utf32string_len, ordering, &outputlen);
    } pdf_catch;

    
#if PHP_MAJOR_VERSION >= 7
    {
        zend_string *z_result;
        if (_result) {
            z_result = zend_string_alloc(outputlen, 0);
            memcpy(z_result->val, _result, outputlen);
        } else {
            z_result = zend_string_init("", 1, 0);
        }
        RETURN_STR(z_result);
    }
#else /* PHP_MAJOR_VERSION >= 7 */
    RETURN_STRINGL(_result ? (char *)_result : "", outputlen, 1);
#endif /* PHP_MAJOR_VERSION >= 7 */
}
/* }}} */
#endif /* defined(_WRAP_CODE) */
#if defined(_WRAP_FUNCTION_ENTRY)
    PHP_FE(pdf_activate_item, NULL)
    PHP_FE(pdf_add_bookmark, NULL)
    PHP_FE(pdf_add_launchlink, NULL)
    PHP_FE(pdf_add_locallink, NULL)
    PHP_FE(pdf_add_nameddest, NULL)
    PHP_FE(pdf_add_note, NULL)
#if PDFLIB_MAJORVERSION >= 8
    PHP_FE(pdf_add_path_point, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
    PHP_FE(pdf_add_pdflink, NULL)
#if PDFLIB_MAJORVERSION >= 8
    PHP_FE(pdf_add_portfolio_file, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if PDFLIB_MAJORVERSION >= 8
    PHP_FE(pdf_add_portfolio_folder, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
    PHP_FE(pdf_add_table_cell, NULL)
    PHP_FE(pdf_add_textflow, NULL)
    PHP_FE(pdf_add_thumbnail, NULL)
    PHP_FE(pdf_add_weblink, NULL)
#if PDFLIB_MAJORVERSION >= 8
    PHP_FE(pdf_align, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
    PHP_FE(pdf_arc, NULL)
    PHP_FE(pdf_arcn, NULL)
    PHP_FE(pdf_attach_file, NULL)
    PHP_FE(pdf_begin_document, NULL)
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PHP_FE(pdf_begin_dpart, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
    PHP_FE(pdf_begin_font, NULL)
    PHP_FE(pdf_begin_glyph, NULL)
#if PDFLIB_MAJORVERSION >= 9
    PHP_FE(pdf_begin_glyph_ext, NULL)
#endif /* PDFLIB_MAJORVERSION >= 9 */
    PHP_FE(pdf_begin_item, NULL)
    PHP_FE(pdf_begin_layer, NULL)
    PHP_FE(pdf_begin_mc, NULL)
    PHP_FE(pdf_begin_page, NULL)
    PHP_FE(pdf_begin_page_ext, NULL)
    PHP_FE(pdf_begin_pattern, NULL)
#if PDFLIB_MAJORVERSION >= 9 && (PDFLIB_MINORVERSION >= 1 || PDFLIB_REVISION >= 2)
    PHP_FE(pdf_begin_pattern_ext, NULL)
#endif /* PDFLIB_MAJORVERSION >= 9 && (PDFLIB_MINORVERSION >= 1 || PDFLIB_REVISION >= 2) */
    PHP_FE(pdf_begin_template, NULL)
    PHP_FE(pdf_begin_template_ext, NULL)
    PHP_FE(pdf_circle, NULL)
#if PDFLIB_MAJORVERSION >= 8
    PHP_FE(pdf_circular_arc, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
    PHP_FE(pdf_clip, NULL)
    PHP_FE(pdf_close, NULL)
#if PDFLIB_MAJORVERSION >= 8
    PHP_FE(pdf_close_font, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PHP_FE(pdf_close_graphics, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
    PHP_FE(pdf_close_image, NULL)
    PHP_FE(pdf_close_pdi, NULL)
    PHP_FE(pdf_close_pdi_document, NULL)
    PHP_FE(pdf_close_pdi_page, NULL)
    PHP_FE(pdf_closepath, NULL)
    PHP_FE(pdf_closepath_fill_stroke, NULL)
    PHP_FE(pdf_closepath_stroke, NULL)
    PHP_FE(pdf_concat, NULL)
    PHP_FE(pdf_continue_text, NULL)
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PHP_FE(pdf_convert_to_unicode, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
    PHP_FE(pdf_create_3dview, NULL)
    PHP_FE(pdf_create_action, NULL)
    PHP_FE(pdf_create_annotation, NULL)
#if PDFLIB_MAJORVERSION >= 9 && PDFLIB_MINORVERSION >= 1
    PHP_FE(pdf_create_devicen, NULL)
#endif /* PDFLIB_MAJORVERSION >= 9 && PDFLIB_MINORVERSION >= 1 */
    PHP_FE(pdf_create_bookmark, NULL)
    PHP_FE(pdf_create_field, NULL)
    PHP_FE(pdf_create_fieldgroup, NULL)
    PHP_FE(pdf_create_gstate, NULL)
    PHP_FE(pdf_create_pvf, NULL)
    PHP_FE(pdf_create_textflow, NULL)
    PHP_FE(pdf_curveto, NULL)
    PHP_FE(pdf_define_layer, NULL)
#if PDFLIB_MAJORVERSION >= 8
    PHP_FE(pdf_delete_path, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
    PHP_FE(pdf_delete_pvf, NULL)
    PHP_FE(pdf_delete_table, NULL)
    PHP_FE(pdf_delete_textflow, NULL)
#if PDFLIB_MAJORVERSION >= 8
    PHP_FE(pdf_draw_path, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if PDFLIB_MAJORVERSION >= 8
    PHP_FE(pdf_ellipse, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PHP_FE(pdf_elliptical_arc, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
    PHP_FE(pdf_encoding_set_char, NULL)
    PHP_FE(pdf_end_document, NULL)
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PHP_FE(pdf_end_dpart, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
    PHP_FE(pdf_end_font, NULL)
    PHP_FE(pdf_end_glyph, NULL)
    PHP_FE(pdf_end_item, NULL)
    PHP_FE(pdf_end_layer, NULL)
    PHP_FE(pdf_end_mc, NULL)
    PHP_FE(pdf_end_page, NULL)
    PHP_FE(pdf_end_page_ext, NULL)
    PHP_FE(pdf_end_pattern, NULL)
    PHP_FE(pdf_end_template, NULL)
#if PDFLIB_MAJORVERSION >= 8
    PHP_FE(pdf_end_template_ext, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
    PHP_FE(pdf_endpath, NULL)
    PHP_FE(pdf_fill, NULL)
#if PDFLIB_MAJORVERSION >= 9
    PHP_FE(pdf_fill_graphicsblock, NULL)
#endif /* PDFLIB_MAJORVERSION >= 9 */
    PHP_FE(pdf_fill_imageblock, NULL)
    PHP_FE(pdf_fill_pdfblock, NULL)
    PHP_FE(pdf_fill_stroke, NULL)
    PHP_FE(pdf_fill_textblock, NULL)
    PHP_FE(pdf_findfont, NULL)
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PHP_FE(pdf_fit_graphics, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
    PHP_FE(pdf_fit_image, NULL)
    PHP_FE(pdf_fit_pdi_page, NULL)
    PHP_FE(pdf_fit_table, NULL)
    PHP_FE(pdf_fit_textflow, NULL)
    PHP_FE(pdf_fit_textline, NULL)
    PHP_FE(pdf_get_apiname, NULL)
    PHP_FE(pdf_get_buffer, NULL)
    PHP_FE(pdf_get_errmsg, NULL)
    PHP_FE(pdf_get_errnum, NULL)
#if PDFLIB_MAJORVERSION >= 9
    PHP_FE(pdf_get_option, NULL)
#endif /* PDFLIB_MAJORVERSION >= 9 */
    PHP_FE(pdf_get_parameter, NULL)
    PHP_FE(pdf_get_pdi_value, NULL)
#if PDFLIB_MAJORVERSION >= 9
    PHP_FE(pdf_get_string, NULL)
#endif /* PDFLIB_MAJORVERSION >= 9 */
    PHP_FE(pdf_get_value, NULL)
    PHP_FE(pdf_info_font, NULL)
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PHP_FE(pdf_info_graphics, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
#if PDFLIB_MAJORVERSION >= 8
    PHP_FE(pdf_info_image, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
    PHP_FE(pdf_info_matchbox, NULL)
#if PDFLIB_MAJORVERSION >= 8
    PHP_FE(pdf_info_path, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if PDFLIB_MAJORVERSION >= 8
    PHP_FE(pdf_info_pdi_page, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PHP_FE(pdf_info_pvf, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
    PHP_FE(pdf_info_table, NULL)
    PHP_FE(pdf_info_textflow, NULL)
    PHP_FE(pdf_info_textline, NULL)
    PHP_FE(pdf_initgraphics, NULL)
    PHP_FE(pdf_lineto, NULL)
    PHP_FE(pdf_load_3ddata, NULL)
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PHP_FE(pdf_load_asset, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
    PHP_FE(pdf_load_font, NULL)
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PHP_FE(pdf_load_graphics, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
    PHP_FE(pdf_load_iccprofile, NULL)
    PHP_FE(pdf_load_image, NULL)
    PHP_FE(pdf_makespotcolor, NULL)
    PHP_FE(pdf_mc_point, NULL)
    PHP_FE(pdf_moveto, NULL)
    PHP_FE(pdf_open_ccitt, NULL)
    PHP_FE(pdf_open_file, NULL)
    PHP_FE(pdf_open_image_file, NULL)
    PHP_FE(pdf_open_pdi_document, NULL)
    PHP_FE(pdf_open_pdi_page, NULL)
    PHP_FE(pdf_pcos_get_number, NULL)
    PHP_FE(pdf_pcos_get_string, NULL)
    PHP_FE(pdf_pcos_get_stream, NULL)
    PHP_FE(pdf_place_image, NULL)
    PHP_FE(pdf_place_pdi_page, NULL)
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PHP_FE(pdf_poca_delete, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PHP_FE(pdf_poca_insert, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PHP_FE(pdf_poca_new, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PHP_FE(pdf_poca_remove, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
    PHP_FE(pdf_process_pdi, NULL)
    PHP_FE(pdf_rect, NULL)
    PHP_FE(pdf_restore, NULL)
    PHP_FE(pdf_resume_page, NULL)
    PHP_FE(pdf_rotate, NULL)
    PHP_FE(pdf_save, NULL)
    PHP_FE(pdf_scale, NULL)
    PHP_FE(pdf_set_border_color, NULL)
    PHP_FE(pdf_set_border_dash, NULL)
    PHP_FE(pdf_set_border_style, NULL)
#if PDFLIB_MAJORVERSION >= 9
    PHP_FE(pdf_set_graphics_option, NULL)
#endif /* PDFLIB_MAJORVERSION >= 9 */
    PHP_FE(pdf_set_gstate, NULL)
    PHP_FE(pdf_set_info, NULL)
    PHP_FE(pdf_set_layer_dependency, NULL)
#if PDFLIB_MAJORVERSION >= 8
    PHP_FE(pdf_set_option, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
    PHP_FE(pdf_set_parameter, NULL)
#if PDFLIB_MAJORVERSION >= 9
    PHP_FE(pdf_set_text_option, NULL)
#endif /* PDFLIB_MAJORVERSION >= 9 */
    PHP_FE(pdf_set_text_pos, NULL)
    PHP_FE(pdf_set_value, NULL)
    PHP_FE(pdf_setcolor, NULL)
    PHP_FE(pdf_setdash, NULL)
    PHP_FE(pdf_setdashpattern, NULL)
    PHP_FE(pdf_setflat, NULL)
    PHP_FE(pdf_setfont, NULL)
    PHP_FE(pdf_setgray, NULL)
    PHP_FE(pdf_setgray_fill, NULL)
    PHP_FE(pdf_setgray_stroke, NULL)
    PHP_FE(pdf_setlinecap, NULL)
    PHP_FE(pdf_setlinejoin, NULL)
    PHP_FE(pdf_setlinewidth, NULL)
    PHP_FE(pdf_setmatrix, NULL)
    PHP_FE(pdf_setmiterlimit, NULL)
    PHP_FE(pdf_setrgbcolor, NULL)
    PHP_FE(pdf_setrgbcolor_fill, NULL)
    PHP_FE(pdf_setrgbcolor_stroke, NULL)
    PHP_FE(pdf_shading, NULL)
    PHP_FE(pdf_shading_pattern, NULL)
    PHP_FE(pdf_shfill, NULL)
    PHP_FE(pdf_show, NULL)
    PHP_FE(pdf_show_xy, NULL)
    PHP_FE(pdf_skew, NULL)
    PHP_FE(pdf_stringwidth, NULL)
    PHP_FE(pdf_stroke, NULL)
    PHP_FE(pdf_suspend_page, NULL)
    PHP_FE(pdf_translate, NULL)
    PHP_FE(pdf_utf16_to_utf8, NULL)
#if PDFLIB_MAJORVERSION >= 8
    PHP_FE(pdf_utf8_to_utf16, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if PDFLIB_MAJORVERSION >= 8
    PHP_FE(pdf_utf32_to_utf8, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if PDFLIB_MAJORVERSION >= 8
    PHP_FE(pdf_utf8_to_utf32, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if PDFLIB_MAJORVERSION >= 8
    PHP_FE(pdf_utf16_to_utf32, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
    PHP_FE(pdf_utf32_to_utf16, NULL)
#endif /* defined(_WRAP_FUNCTION_ENTRY)*/
#if defined(_WRAP_FUNCTION_ENTRY2)
    PDF_ME_MAPPING(activate_item, pdf_activate_item, NULL)
    PDF_ME_MAPPING(add_nameddest, pdf_add_nameddest, NULL)
#if PDFLIB_MAJORVERSION >= 8
    PDF_ME_MAPPING(add_path_point, pdf_add_path_point, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if PDFLIB_MAJORVERSION >= 8
    PDF_ME_MAPPING(add_portfolio_file, pdf_add_portfolio_file, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if PDFLIB_MAJORVERSION >= 8
    PDF_ME_MAPPING(add_portfolio_folder, pdf_add_portfolio_folder, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
    PDF_ME_MAPPING(add_table_cell, pdf_add_table_cell, NULL)
    PDF_ME_MAPPING(add_textflow, pdf_add_textflow, NULL)
    PDF_ME_MAPPING(add_thumbnail, pdf_add_thumbnail, NULL)
#if PDFLIB_MAJORVERSION >= 8
    PDF_ME_MAPPING(align, pdf_align, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
    PDF_ME_MAPPING(arc, pdf_arc, NULL)
    PDF_ME_MAPPING(arcn, pdf_arcn, NULL)
    PDF_ME_MAPPING(begin_document, pdf_begin_document, NULL)
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PDF_ME_MAPPING(begin_dpart, pdf_begin_dpart, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
    PDF_ME_MAPPING(begin_font, pdf_begin_font, NULL)
    PDF_ME_MAPPING(begin_glyph, pdf_begin_glyph, NULL)
#if PDFLIB_MAJORVERSION >= 9
    PDF_ME_MAPPING(begin_glyph_ext, pdf_begin_glyph_ext, NULL)
#endif /* PDFLIB_MAJORVERSION >= 9 */
    PDF_ME_MAPPING(begin_item, pdf_begin_item, NULL)
    PDF_ME_MAPPING(begin_layer, pdf_begin_layer, NULL)
    PDF_ME_MAPPING(begin_mc, pdf_begin_mc, NULL)
    PDF_ME_MAPPING(begin_page_ext, pdf_begin_page_ext, NULL)
    PDF_ME_MAPPING(begin_pattern, pdf_begin_pattern, NULL)
#if PDFLIB_MAJORVERSION >= 9 && (PDFLIB_MINORVERSION >= 1 || PDFLIB_REVISION >= 2)
    PDF_ME_MAPPING(begin_pattern_ext, pdf_begin_pattern_ext, NULL)
#endif /* PDFLIB_MAJORVERSION >= 9 && (PDFLIB_MINORVERSION >= 1 || PDFLIB_REVISION >= 2) */
    PDF_ME_MAPPING(begin_template, pdf_begin_template, NULL)
    PDF_ME_MAPPING(begin_template_ext, pdf_begin_template_ext, NULL)
    PDF_ME_MAPPING(circle, pdf_circle, NULL)
#if PDFLIB_MAJORVERSION >= 8
    PDF_ME_MAPPING(circular_arc, pdf_circular_arc, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
    PDF_ME_MAPPING(clip, pdf_clip, NULL)
#if PDFLIB_MAJORVERSION >= 8
    PDF_ME_MAPPING(close_font, pdf_close_font, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PDF_ME_MAPPING(close_graphics, pdf_close_graphics, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
    PDF_ME_MAPPING(close_image, pdf_close_image, NULL)
    PDF_ME_MAPPING(close_pdi, pdf_close_pdi, NULL)
    PDF_ME_MAPPING(close_pdi_document, pdf_close_pdi_document, NULL)
    PDF_ME_MAPPING(close_pdi_page, pdf_close_pdi_page, NULL)
    PDF_ME_MAPPING(closepath, pdf_closepath, NULL)
    PDF_ME_MAPPING(closepath_fill_stroke, pdf_closepath_fill_stroke, NULL)
    PDF_ME_MAPPING(closepath_stroke, pdf_closepath_stroke, NULL)
    PDF_ME_MAPPING(concat, pdf_concat, NULL)
    PDF_ME_MAPPING(continue_text, pdf_continue_text, NULL)
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PDF_ME_MAPPING(convert_to_unicode, pdf_convert_to_unicode, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
    PDF_ME_MAPPING(create_3dview, pdf_create_3dview, NULL)
    PDF_ME_MAPPING(create_action, pdf_create_action, NULL)
    PDF_ME_MAPPING(create_annotation, pdf_create_annotation, NULL)
#if PDFLIB_MAJORVERSION >= 9 && PDFLIB_MINORVERSION >= 1
    PDF_ME_MAPPING(create_devicen, pdf_create_devicen, NULL)
#endif /* PDFLIB_MAJORVERSION >= 9 && PDFLIB_MINORVERSION >= 1 */
    PDF_ME_MAPPING(create_bookmark, pdf_create_bookmark, NULL)
    PDF_ME_MAPPING(create_field, pdf_create_field, NULL)
    PDF_ME_MAPPING(create_fieldgroup, pdf_create_fieldgroup, NULL)
    PDF_ME_MAPPING(create_gstate, pdf_create_gstate, NULL)
    PDF_ME_MAPPING(create_pvf, pdf_create_pvf, NULL)
    PDF_ME_MAPPING(create_textflow, pdf_create_textflow, NULL)
    PDF_ME_MAPPING(curveto, pdf_curveto, NULL)
    PDF_ME_MAPPING(define_layer, pdf_define_layer, NULL)
#if PDFLIB_MAJORVERSION >= 8
    PDF_ME_MAPPING(delete_path, pdf_delete_path, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
    PDF_ME_MAPPING(delete_pvf, pdf_delete_pvf, NULL)
    PDF_ME_MAPPING(delete_table, pdf_delete_table, NULL)
    PDF_ME_MAPPING(delete_textflow, pdf_delete_textflow, NULL)
#if PDFLIB_MAJORVERSION >= 8
    PDF_ME_MAPPING(draw_path, pdf_draw_path, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if PDFLIB_MAJORVERSION >= 8
    PDF_ME_MAPPING(ellipse, pdf_ellipse, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PDF_ME_MAPPING(elliptical_arc, pdf_elliptical_arc, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
    PDF_ME_MAPPING(encoding_set_char, pdf_encoding_set_char, NULL)
    PDF_ME_MAPPING(end_document, pdf_end_document, NULL)
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PDF_ME_MAPPING(end_dpart, pdf_end_dpart, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
    PDF_ME_MAPPING(end_font, pdf_end_font, NULL)
    PDF_ME_MAPPING(end_glyph, pdf_end_glyph, NULL)
    PDF_ME_MAPPING(end_item, pdf_end_item, NULL)
    PDF_ME_MAPPING(end_layer, pdf_end_layer, NULL)
    PDF_ME_MAPPING(end_mc, pdf_end_mc, NULL)
    PDF_ME_MAPPING(end_page_ext, pdf_end_page_ext, NULL)
    PDF_ME_MAPPING(end_pattern, pdf_end_pattern, NULL)
    PDF_ME_MAPPING(end_template, pdf_end_template, NULL)
#if PDFLIB_MAJORVERSION >= 8
    PDF_ME_MAPPING(end_template_ext, pdf_end_template_ext, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
    PDF_ME_MAPPING(endpath, pdf_endpath, NULL)
    PDF_ME_MAPPING(fill, pdf_fill, NULL)
#if PDFLIB_MAJORVERSION >= 9
    PDF_ME_MAPPING(fill_graphicsblock, pdf_fill_graphicsblock, NULL)
#endif /* PDFLIB_MAJORVERSION >= 9 */
    PDF_ME_MAPPING(fill_imageblock, pdf_fill_imageblock, NULL)
    PDF_ME_MAPPING(fill_pdfblock, pdf_fill_pdfblock, NULL)
    PDF_ME_MAPPING(fill_stroke, pdf_fill_stroke, NULL)
    PDF_ME_MAPPING(fill_textblock, pdf_fill_textblock, NULL)
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PDF_ME_MAPPING(fit_graphics, pdf_fit_graphics, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
    PDF_ME_MAPPING(fit_image, pdf_fit_image, NULL)
    PDF_ME_MAPPING(fit_pdi_page, pdf_fit_pdi_page, NULL)
    PDF_ME_MAPPING(fit_table, pdf_fit_table, NULL)
    PDF_ME_MAPPING(fit_textflow, pdf_fit_textflow, NULL)
    PDF_ME_MAPPING(fit_textline, pdf_fit_textline, NULL)
    PDF_ME_MAPPING(get_apiname, pdf_get_apiname, NULL)
    PDF_ME_MAPPING(get_buffer, pdf_get_buffer, NULL)
    PDF_ME_MAPPING(get_errmsg, pdf_get_errmsg, NULL)
    PDF_ME_MAPPING(get_errnum, pdf_get_errnum, NULL)
#if PDFLIB_MAJORVERSION >= 9
    PDF_ME_MAPPING(get_option, pdf_get_option, NULL)
#endif /* PDFLIB_MAJORVERSION >= 9 */
    PDF_ME_MAPPING(get_parameter, pdf_get_parameter, NULL)
    PDF_ME_MAPPING(get_pdi_value, pdf_get_pdi_value, NULL)
#if PDFLIB_MAJORVERSION >= 9
    PDF_ME_MAPPING(get_string, pdf_get_string, NULL)
#endif /* PDFLIB_MAJORVERSION >= 9 */
    PDF_ME_MAPPING(get_value, pdf_get_value, NULL)
    PDF_ME_MAPPING(info_font, pdf_info_font, NULL)
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PDF_ME_MAPPING(info_graphics, pdf_info_graphics, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
#if PDFLIB_MAJORVERSION >= 8
    PDF_ME_MAPPING(info_image, pdf_info_image, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
    PDF_ME_MAPPING(info_matchbox, pdf_info_matchbox, NULL)
#if PDFLIB_MAJORVERSION >= 8
    PDF_ME_MAPPING(info_path, pdf_info_path, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if PDFLIB_MAJORVERSION >= 8
    PDF_ME_MAPPING(info_pdi_page, pdf_info_pdi_page, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PDF_ME_MAPPING(info_pvf, pdf_info_pvf, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
    PDF_ME_MAPPING(info_table, pdf_info_table, NULL)
    PDF_ME_MAPPING(info_textflow, pdf_info_textflow, NULL)
    PDF_ME_MAPPING(info_textline, pdf_info_textline, NULL)
    PDF_ME_MAPPING(initgraphics, pdf_initgraphics, NULL)
    PDF_ME_MAPPING(lineto, pdf_lineto, NULL)
    PDF_ME_MAPPING(load_3ddata, pdf_load_3ddata, NULL)
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PDF_ME_MAPPING(load_asset, pdf_load_asset, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
    PDF_ME_MAPPING(load_font, pdf_load_font, NULL)
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PDF_ME_MAPPING(load_graphics, pdf_load_graphics, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
    PDF_ME_MAPPING(load_iccprofile, pdf_load_iccprofile, NULL)
    PDF_ME_MAPPING(load_image, pdf_load_image, NULL)
    PDF_ME_MAPPING(makespotcolor, pdf_makespotcolor, NULL)
    PDF_ME_MAPPING(mc_point, pdf_mc_point, NULL)
    PDF_ME_MAPPING(moveto, pdf_moveto, NULL)
    PDF_ME_MAPPING(open_pdi_document, pdf_open_pdi_document, NULL)
    PDF_ME_MAPPING(open_pdi_page, pdf_open_pdi_page, NULL)
    PDF_ME_MAPPING(pcos_get_number, pdf_pcos_get_number, NULL)
    PDF_ME_MAPPING(pcos_get_string, pdf_pcos_get_string, NULL)
    PDF_ME_MAPPING(pcos_get_stream, pdf_pcos_get_stream, NULL)
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PDF_ME_MAPPING(poca_delete, pdf_poca_delete, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PDF_ME_MAPPING(poca_insert, pdf_poca_insert, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PDF_ME_MAPPING(poca_new, pdf_poca_new, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
    PDF_ME_MAPPING(poca_remove, pdf_poca_remove, NULL)
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
    PDF_ME_MAPPING(process_pdi, pdf_process_pdi, NULL)
    PDF_ME_MAPPING(rect, pdf_rect, NULL)
    PDF_ME_MAPPING(restore, pdf_restore, NULL)
    PDF_ME_MAPPING(resume_page, pdf_resume_page, NULL)
    PDF_ME_MAPPING(rotate, pdf_rotate, NULL)
    PDF_ME_MAPPING(save, pdf_save, NULL)
    PDF_ME_MAPPING(scale, pdf_scale, NULL)
#if PDFLIB_MAJORVERSION >= 9
    PDF_ME_MAPPING(set_graphics_option, pdf_set_graphics_option, NULL)
#endif /* PDFLIB_MAJORVERSION >= 9 */
    PDF_ME_MAPPING(set_gstate, pdf_set_gstate, NULL)
    PDF_ME_MAPPING(set_info, pdf_set_info, NULL)
    PDF_ME_MAPPING(set_layer_dependency, pdf_set_layer_dependency, NULL)
#if PDFLIB_MAJORVERSION >= 8
    PDF_ME_MAPPING(set_option, pdf_set_option, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
    PDF_ME_MAPPING(set_parameter, pdf_set_parameter, NULL)
#if PDFLIB_MAJORVERSION >= 9
    PDF_ME_MAPPING(set_text_option, pdf_set_text_option, NULL)
#endif /* PDFLIB_MAJORVERSION >= 9 */
    PDF_ME_MAPPING(set_text_pos, pdf_set_text_pos, NULL)
    PDF_ME_MAPPING(set_value, pdf_set_value, NULL)
    PDF_ME_MAPPING(setcolor, pdf_setcolor, NULL)
    PDF_ME_MAPPING(setdash, pdf_setdash, NULL)
    PDF_ME_MAPPING(setdashpattern, pdf_setdashpattern, NULL)
    PDF_ME_MAPPING(setflat, pdf_setflat, NULL)
    PDF_ME_MAPPING(setfont, pdf_setfont, NULL)
    PDF_ME_MAPPING(setlinecap, pdf_setlinecap, NULL)
    PDF_ME_MAPPING(setlinejoin, pdf_setlinejoin, NULL)
    PDF_ME_MAPPING(setlinewidth, pdf_setlinewidth, NULL)
    PDF_ME_MAPPING(setmatrix, pdf_setmatrix, NULL)
    PDF_ME_MAPPING(setmiterlimit, pdf_setmiterlimit, NULL)
    PDF_ME_MAPPING(shading, pdf_shading, NULL)
    PDF_ME_MAPPING(shading_pattern, pdf_shading_pattern, NULL)
    PDF_ME_MAPPING(shfill, pdf_shfill, NULL)
    PDF_ME_MAPPING(show, pdf_show, NULL)
    PDF_ME_MAPPING(show_xy, pdf_show_xy, NULL)
    PDF_ME_MAPPING(skew, pdf_skew, NULL)
    PDF_ME_MAPPING(stringwidth, pdf_stringwidth, NULL)
    PDF_ME_MAPPING(stroke, pdf_stroke, NULL)
    PDF_ME_MAPPING(suspend_page, pdf_suspend_page, NULL)
    PDF_ME_MAPPING(translate, pdf_translate, NULL)
    PDF_ME_MAPPING(utf16_to_utf8, pdf_utf16_to_utf8, NULL)
#if PDFLIB_MAJORVERSION >= 8
    PDF_ME_MAPPING(utf8_to_utf16, pdf_utf8_to_utf16, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if PDFLIB_MAJORVERSION >= 8
    PDF_ME_MAPPING(utf32_to_utf8, pdf_utf32_to_utf8, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if PDFLIB_MAJORVERSION >= 8
    PDF_ME_MAPPING(utf8_to_utf32, pdf_utf8_to_utf32, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if PDFLIB_MAJORVERSION >= 8
    PDF_ME_MAPPING(utf16_to_utf32, pdf_utf16_to_utf32, NULL)
#endif /* PDFLIB_MAJORVERSION >= 8 */
    PDF_ME_MAPPING(utf32_to_utf16, pdf_utf32_to_utf16, NULL)
#endif /* defined(_WRAP_FUNCTION_ENTRY2)*/
#if defined(_WRAP_FUNCTION_ENTRY3)
PHP_FUNCTION(pdf_activate_item);
PHP_FUNCTION(pdf_add_bookmark);
PHP_FUNCTION(pdf_add_launchlink);
PHP_FUNCTION(pdf_add_locallink);
PHP_FUNCTION(pdf_add_nameddest);
PHP_FUNCTION(pdf_add_note);
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_add_path_point);
#endif /* PDFLIB_MAJORVERSION >= 8 */
PHP_FUNCTION(pdf_add_pdflink);
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_add_portfolio_file);
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_add_portfolio_folder);
#endif /* PDFLIB_MAJORVERSION >= 8 */
PHP_FUNCTION(pdf_add_table_cell);
PHP_FUNCTION(pdf_add_textflow);
PHP_FUNCTION(pdf_add_thumbnail);
PHP_FUNCTION(pdf_add_weblink);
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_align);
#endif /* PDFLIB_MAJORVERSION >= 8 */
PHP_FUNCTION(pdf_arc);
PHP_FUNCTION(pdf_arcn);
PHP_FUNCTION(pdf_attach_file);
PHP_FUNCTION(pdf_begin_document);
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_begin_dpart);
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
PHP_FUNCTION(pdf_begin_font);
PHP_FUNCTION(pdf_begin_glyph);
#if PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_begin_glyph_ext);
#endif /* PDFLIB_MAJORVERSION >= 9 */
PHP_FUNCTION(pdf_begin_item);
PHP_FUNCTION(pdf_begin_layer);
PHP_FUNCTION(pdf_begin_mc);
PHP_FUNCTION(pdf_begin_page);
PHP_FUNCTION(pdf_begin_page_ext);
PHP_FUNCTION(pdf_begin_pattern);
#if PDFLIB_MAJORVERSION >= 9 && (PDFLIB_MINORVERSION >= 1 || PDFLIB_REVISION >= 2)
PHP_FUNCTION(pdf_begin_pattern_ext);
#endif /* PDFLIB_MAJORVERSION >= 9 && (PDFLIB_MINORVERSION >= 1 || PDFLIB_REVISION >= 2) */
PHP_FUNCTION(pdf_begin_template);
PHP_FUNCTION(pdf_begin_template_ext);
PHP_FUNCTION(pdf_circle);
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_circular_arc);
#endif /* PDFLIB_MAJORVERSION >= 8 */
PHP_FUNCTION(pdf_clip);
PHP_FUNCTION(pdf_close);
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_close_font);
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_close_graphics);
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
PHP_FUNCTION(pdf_close_image);
PHP_FUNCTION(pdf_close_pdi);
PHP_FUNCTION(pdf_close_pdi_document);
PHP_FUNCTION(pdf_close_pdi_page);
PHP_FUNCTION(pdf_closepath);
PHP_FUNCTION(pdf_closepath_fill_stroke);
PHP_FUNCTION(pdf_closepath_stroke);
PHP_FUNCTION(pdf_concat);
PHP_FUNCTION(pdf_continue_text);
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_convert_to_unicode);
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
PHP_FUNCTION(pdf_create_3dview);
PHP_FUNCTION(pdf_create_action);
PHP_FUNCTION(pdf_create_annotation);
#if PDFLIB_MAJORVERSION >= 9 && PDFLIB_MINORVERSION >= 1
PHP_FUNCTION(pdf_create_devicen);
#endif /* PDFLIB_MAJORVERSION >= 9 && PDFLIB_MINORVERSION >= 1 */
PHP_FUNCTION(pdf_create_bookmark);
PHP_FUNCTION(pdf_create_field);
PHP_FUNCTION(pdf_create_fieldgroup);
PHP_FUNCTION(pdf_create_gstate);
PHP_FUNCTION(pdf_create_pvf);
PHP_FUNCTION(pdf_create_textflow);
PHP_FUNCTION(pdf_curveto);
PHP_FUNCTION(pdf_define_layer);
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_delete_path);
#endif /* PDFLIB_MAJORVERSION >= 8 */
PHP_FUNCTION(pdf_delete_pvf);
PHP_FUNCTION(pdf_delete_table);
PHP_FUNCTION(pdf_delete_textflow);
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_draw_path);
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_ellipse);
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_elliptical_arc);
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
PHP_FUNCTION(pdf_encoding_set_char);
PHP_FUNCTION(pdf_end_document);
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_end_dpart);
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
PHP_FUNCTION(pdf_end_font);
PHP_FUNCTION(pdf_end_glyph);
PHP_FUNCTION(pdf_end_item);
PHP_FUNCTION(pdf_end_layer);
PHP_FUNCTION(pdf_end_mc);
PHP_FUNCTION(pdf_end_page);
PHP_FUNCTION(pdf_end_page_ext);
PHP_FUNCTION(pdf_end_pattern);
PHP_FUNCTION(pdf_end_template);
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_end_template_ext);
#endif /* PDFLIB_MAJORVERSION >= 8 */
PHP_FUNCTION(pdf_endpath);
PHP_FUNCTION(pdf_fill);
#if PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_fill_graphicsblock);
#endif /* PDFLIB_MAJORVERSION >= 9 */
PHP_FUNCTION(pdf_fill_imageblock);
PHP_FUNCTION(pdf_fill_pdfblock);
PHP_FUNCTION(pdf_fill_stroke);
PHP_FUNCTION(pdf_fill_textblock);
PHP_FUNCTION(pdf_findfont);
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_fit_graphics);
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
PHP_FUNCTION(pdf_fit_image);
PHP_FUNCTION(pdf_fit_pdi_page);
PHP_FUNCTION(pdf_fit_table);
PHP_FUNCTION(pdf_fit_textflow);
PHP_FUNCTION(pdf_fit_textline);
PHP_FUNCTION(pdf_get_apiname);
PHP_FUNCTION(pdf_get_buffer);
PHP_FUNCTION(pdf_get_errmsg);
PHP_FUNCTION(pdf_get_errnum);
#if PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_get_option);
#endif /* PDFLIB_MAJORVERSION >= 9 */
PHP_FUNCTION(pdf_get_parameter);
PHP_FUNCTION(pdf_get_pdi_value);
#if PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_get_string);
#endif /* PDFLIB_MAJORVERSION >= 9 */
PHP_FUNCTION(pdf_get_value);
PHP_FUNCTION(pdf_info_font);
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_info_graphics);
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_info_image);
#endif /* PDFLIB_MAJORVERSION >= 8 */
PHP_FUNCTION(pdf_info_matchbox);
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_info_path);
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_info_pdi_page);
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_info_pvf);
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
PHP_FUNCTION(pdf_info_table);
PHP_FUNCTION(pdf_info_textflow);
PHP_FUNCTION(pdf_info_textline);
PHP_FUNCTION(pdf_initgraphics);
PHP_FUNCTION(pdf_lineto);
PHP_FUNCTION(pdf_load_3ddata);
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_load_asset);
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
PHP_FUNCTION(pdf_load_font);
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_load_graphics);
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
PHP_FUNCTION(pdf_load_iccprofile);
PHP_FUNCTION(pdf_load_image);
PHP_FUNCTION(pdf_makespotcolor);
PHP_FUNCTION(pdf_mc_point);
PHP_FUNCTION(pdf_moveto);
PHP_FUNCTION(pdf_open_ccitt);
PHP_FUNCTION(pdf_open_file);
PHP_FUNCTION(pdf_open_image_file);
PHP_FUNCTION(pdf_open_pdi_document);
PHP_FUNCTION(pdf_open_pdi_page);
PHP_FUNCTION(pdf_pcos_get_number);
PHP_FUNCTION(pdf_pcos_get_string);
PHP_FUNCTION(pdf_pcos_get_stream);
PHP_FUNCTION(pdf_place_image);
PHP_FUNCTION(pdf_place_pdi_page);
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_poca_delete);
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_poca_insert);
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_poca_new);
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
#if (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_poca_remove);
#endif /* (PDFLIB_MAJORVERSION >= 8 && PDFLIB_MINORVERSION >= 1) || PDFLIB_MAJORVERSION >= 9 */
PHP_FUNCTION(pdf_process_pdi);
PHP_FUNCTION(pdf_rect);
PHP_FUNCTION(pdf_restore);
PHP_FUNCTION(pdf_resume_page);
PHP_FUNCTION(pdf_rotate);
PHP_FUNCTION(pdf_save);
PHP_FUNCTION(pdf_scale);
PHP_FUNCTION(pdf_set_border_color);
PHP_FUNCTION(pdf_set_border_dash);
PHP_FUNCTION(pdf_set_border_style);
#if PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_set_graphics_option);
#endif /* PDFLIB_MAJORVERSION >= 9 */
PHP_FUNCTION(pdf_set_gstate);
PHP_FUNCTION(pdf_set_info);
PHP_FUNCTION(pdf_set_layer_dependency);
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_set_option);
#endif /* PDFLIB_MAJORVERSION >= 8 */
PHP_FUNCTION(pdf_set_parameter);
#if PDFLIB_MAJORVERSION >= 9
PHP_FUNCTION(pdf_set_text_option);
#endif /* PDFLIB_MAJORVERSION >= 9 */
PHP_FUNCTION(pdf_set_text_pos);
PHP_FUNCTION(pdf_set_value);
PHP_FUNCTION(pdf_setcolor);
PHP_FUNCTION(pdf_setdash);
PHP_FUNCTION(pdf_setdashpattern);
PHP_FUNCTION(pdf_setflat);
PHP_FUNCTION(pdf_setfont);
PHP_FUNCTION(pdf_setgray);
PHP_FUNCTION(pdf_setgray_fill);
PHP_FUNCTION(pdf_setgray_stroke);
PHP_FUNCTION(pdf_setlinecap);
PHP_FUNCTION(pdf_setlinejoin);
PHP_FUNCTION(pdf_setlinewidth);
PHP_FUNCTION(pdf_setmatrix);
PHP_FUNCTION(pdf_setmiterlimit);
PHP_FUNCTION(pdf_setrgbcolor);
PHP_FUNCTION(pdf_setrgbcolor_fill);
PHP_FUNCTION(pdf_setrgbcolor_stroke);
PHP_FUNCTION(pdf_shading);
PHP_FUNCTION(pdf_shading_pattern);
PHP_FUNCTION(pdf_shfill);
PHP_FUNCTION(pdf_show);
PHP_FUNCTION(pdf_show_xy);
PHP_FUNCTION(pdf_skew);
PHP_FUNCTION(pdf_stringwidth);
PHP_FUNCTION(pdf_stroke);
PHP_FUNCTION(pdf_suspend_page);
PHP_FUNCTION(pdf_translate);
PHP_FUNCTION(pdf_utf16_to_utf8);
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_utf8_to_utf16);
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_utf32_to_utf8);
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_utf8_to_utf32);
#endif /* PDFLIB_MAJORVERSION >= 8 */
#if PDFLIB_MAJORVERSION >= 8
PHP_FUNCTION(pdf_utf16_to_utf32);
#endif /* PDFLIB_MAJORVERSION >= 8 */
PHP_FUNCTION(pdf_utf32_to_utf16);
#endif /* defined(_WRAP_FUNCTION_ENTRY3)*/
