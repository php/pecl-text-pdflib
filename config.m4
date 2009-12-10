dnl
dnl $Id$
dnl

PHP_ARG_WITH(pdflib,for PDFlib support,
[  --with-pdflib[=DIR]     Include PDFlib support.])

if test "$PHP_PDFLIB" != "no"; then

  dnl #
  dnl # The main PDFlib configure
  dnl #

  PHP_REQUIRE_CXX()  # needed to link with g++ to include ICU library
  PHP_NEW_EXTENSION(pdf, pdf.c, $ext_shared)
  dnl # MacOSX requires this
  case `(uname -s) 2>/dev/null || echo unknown` in
    *arwin*)
      PHP_ADD_FRAMEWORK(ApplicationServices)
      PDF_SHARED_LIBADD="$PDF_SHARED_LIBADD $PHP_FRAMEWORKS"
      ;;
  esac
  PHP_SUBST(PDF_SHARED_LIBADD)

  case $PHP_PDFLIB in
    yes)
        AC_DEFINE(HAVE_PDFLIB,1,[ ])
        PHP_ADD_LIBRARY(pdf,, PDF_SHARED_LIBADD)
    ;;
    *)
      if test -f "$PHP_PDFLIB/include/pdflib.h" ; then

          AC_DEFINE(HAVE_PDFLIB,1,[ ]) 
          PHP_ADD_LIBRARY_WITH_PATH(pdf, $PHP_PDFLIB/lib, PDF_SHARED_LIBADD)
          PHP_ADD_INCLUDE($PHP_PDFLIB/include)
      else
        AC_MSG_ERROR([pdflib.h not found! Check the path passed to --with-pdflib=<PATH>. PATH should be the install prefix directory.])
      fi
    ;;
  esac
fi
