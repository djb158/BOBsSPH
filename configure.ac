AC_INIT(infra_sph, 3.0.2, djb158@bigpond.com)
dnl version=3.0.2
dnl
dnl certain autotools related files are placed in the subdir config
dnl
AC_CONFIG_AUX_DIR(config)
dnl
dnl initialize automake
dnl
AM_INIT_AUTOMAKE(infra_sph,3.0.1)
dnl
dnl place the results of running this script in the file config.h
dnl
AC_CONFIG_HEADER([config.h])
dnl
dnl Checks for programs.
dnl
AC_PROG_INSTALL
AC_ARG_WITH(mpi, [AS_HELP_STRING([--with-mpi],
    [compile with MPI (parallelization) support. If none is found,
    MPI is not used. Default: auto])
],,[with_mpi=auto])

AX_PROG_CC_MPI([test x"$with_mpi" != xno],[use_mpi=yes],[
use_mpi=no
if test x"$with_mpi" = xyes; then
  AC_MSG_FAILURE([MPI compiler requested, but couldn't use MPI.])
else
  AC_MSG_WARN([No MPI compiler found, won't use MPI.])
fi
])

AX_PROG_CXX_MPI([test x"$with_mpi" != xno],[use_mpi=yes],[
  use_mpi=no
  if test x"$with_mpi" = xyes; then
    AC_MSG_FAILURE([MPI compiler requested, but couldn't use MPI.])
  else
    AC_MSG_WARN([No MPI compiler found, won't use MPI.])
  fi
])
LT_INIT
AC_PROG_LIBTOOL
for lib in `find $PWD/libsrc/ -type d -name 'lib*'`
do
    LDFLAGS="$LDFLAGS -L$lib"
done

# === Check to be used for unit tests ===
# This macro is defined in check.m4 and tests if check.h and
# libcheck.a are installed in your system. It sets CHECK_CFLAGS and
# CHECK_LIBS accordingly.  
AM_PATH_CHECK(0.9.5, [have_check="yes"],
  AC_MSG_WARN([Check not found; cannot run unit tests!])
  [have_check="no"])
AM_CONDITIONAL(HAVE_CHECK, test x"$have_check" = "xyes")
# === End check to be used for unit tests ===

# === record git commitid
SPH_GIT_COMMIT_HASH=`git rev-parse HEAD`
AC_DEFINE_UNQUOTED([SPH_GIT_COMMIT_HASH],
                   ["$SPH_GIT_COMMIT_HASH"],
                   [Define sph git commit hash])
# === end record git commitid

dnl +++++++++++++++++ start LIBS section ++++++++++++++++++++++++++++++++++++++++
dnl
dnl This section finds all of the libraries which may be added to the
dnl LIBS varible in each Makefile. If a library cannot be found, a warning message
dnl is given and it will not be added to LIBS.
dnl
dnl possible libraries are:
dnl   LIBS = -lnsl -lsocket -lresolv -lrt -lm
dnl
AC_CHECK_LIB(m, main)
dnl rt, socket, nsl are needed by libcd under solaris
AC_CHECK_LIB(rt, nanosleep)
dnl libresolv is needed by the socket library on several platforms
AC_CHECK_LIB(resolv, dn_expand)
AC_CHECK_LIB(socket, socket)
AC_CHECK_LIB(nsl, inet_addr)

dnl ++++++++++++++++++ end LIBS section +++++++++++++++++++++++++++++++++++++++++

dnl ++++++++++++++++++ start optional library section +++++++++++++++++++++++++++
dnl
# Our own libraries (libsrc), these need to be in dependency order

# lib_test_A
AC_MSG_CHECKING([whether dependencies are fulfilled for test_A libutil])
  TEST_UTIL_INCLUDES="-I\$(top_srcdir)/libsrc/libutil"
  HE_UNIQ_VAR([TEST_UTIL_INCLUDES])
  TEST_UTIL_LIBS="-L\$(top_srcdir)/libsrc/libutil -lutil"
  TEST_UTIL_DEPS=""
  LIB_TEST_UTIL="\$(top_builddir)/libsrc/libutil/libutil.la"
  TEST_A_DEPENDENCIES=""
  HE_UNIQ_VAR([TEST_UTIL_DEPENDENCIES])
  AC_DEFINE(HAVE_UTIL, [], [Do we have util library])
  AC_MSG_RESULT([yes])
AC_SUBST(TEST_UTIL_INCLUDES)
AC_SUBST(TEST_UTIL_LIBS)
AC_SUBST(TEST_UTIL_LIBADD)
AC_SUBST(LIB_TEST_UTIL)
AC_SUBST(TEST_UTIL_DEPENDENCIES)
AM_CONDITIONAL([HAVE_TEST_UTIL], [test -n "${TEST_UTIL_LIBS}"])

dnl
dnl ++++++++++++++++++ end optional library section +++++++++++++++++++++++++++++


AC_PROG_RANLIB
AC_CONFIG_FILES(Makefile 
	include/Makefile
	libsrc/Makefile
	libsrc/libutil/Makefile
	libsrc/libutil/test/Makefile
	libsrc/libsph/Makefile
	libsrc/libsplash/Makefile
	src/sph/Makefile
	src/pbobs/Makefile
	src/Makefile
)
AC_OUTPUT


