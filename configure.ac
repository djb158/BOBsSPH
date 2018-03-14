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

AC_PROG_LIBTOOL
for lib in `find $PWD/libsrc/ -type d -name 'lib*'`
do
    LDFLAGS="$LDFLAGS -L$lib"
done

SPH_GIT_COMMIT_HASH=`git rev-parse HEAD`
AC_DEFINE_UNQUOTED([SPH_GIT_COMMIT_HASH],
                   ["$SPH_GIT_COMMIT_HASH"],
                   [Define sph git commit hash])


AC_PROG_RANLIB
AC_CONFIG_FILES(Makefile 
	include/Makefile
	libsrc/Makefile
	libsrc/libutil/Makefile
	libsrc/libsph/Makefile
	libsrc/libsplash/Makefile
	src/sph/Makefile
	src/pbobs/Makefile
	src/Makefile
)
AC_OUTPUT
