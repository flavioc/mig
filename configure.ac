dnl configure script for GNU MIG.

AC_PREREQ([2.53])

AC_INIT([GNU MIG], [1.3.1], [bug-hurd@gnu.org])
AC_CONFIG_SRCDIR([migcom.c])
AC_CONFIG_AUX_DIR([build-aux])

AC_CANONICAL_HOST
AC_CANONICAL_TARGET

AC_ARG_PROGRAM

AM_INIT_AUTOMAKE

dnl Checks for programs.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_YACC
AM_PROG_LEX
AC_PROG_AWK
AC_PROG_INSTALL

dnl Checks for header files.
AC_HEADER_STDC

dnl Checks for library functions.
AC_FUNC_ALLOCA
AC_FUNC_VPRINTF


[if [ "$target" = "$host" ]; then
  TARGET_CC='${CC}'
else]
  AC_CHECK_PROG([TARGET_CC], [$target_alias-gcc], [$target_alias-gcc], [none])
  [if [ x"$TARGET_CC" != x"$target_alias"-gcc ]; then]
    AC_MSG_ERROR([could not find a compiler for the target you requested])
  [fi
fi]
dnl These two are just for the user's convenience.
AC_SUBST([TARGET_CPPFLAGS])
AC_SUBST([TARGET_CFLAGS])

[MIGCOM=`echo migcom | sed "$program_transform_name"`]
AC_SUBST([MIGCOM])
[MIG=`echo mig | sed "$program_transform_name"`]
AC_SUBST([MIG])

AC_OUTPUT([Makefile mig])
