dnl
dnl    ettercap -- configure script
dnl
dnl    Copyright (C) ALoR & NaGA
dnl
dnl    This program is free software; you can redistribute it and/or modify
dnl    it under the terms of the GNU General Public License as published by
dnl    the Free Software Foundation; either version 2 of the License, or
dnl    (at your option) any later version.
dnl
dnl    This program is distributed in the hope that it will be useful,
dnl    but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl    GNU General Public License for more details.
dnl
dnl    You should have received a copy of the GNU General Public License
dnl    along with this program; if not, write to the Free Software
dnl    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
dnl

AC_INIT
AC_CONFIG_SRCDIR([src/ec_main.c])
AC_CONFIG_MACRO_DIR([libltdl/m4])
AC_CONFIG_AUX_DIR([libltdl/config])

AC_PREREQ([2.68])

VERSION=$(grep EC_VERSION\  ./include/ec_version.h | cut -f2 -d"\"")
SB=$(./shtool echo -n -e %B)
EB=$(./shtool echo -n -e %b)
AC_SUBST(SB)
AC_SUBST(EB)
AC_SUBST(VERSION)
EC_MESSAGE([Configuring ettercap $VERSION])

AM_INIT_AUTOMAKE([ettercap], [$VERSION])

AC_CONFIG_HEADERS([include/config.h])

AC_CONFIG_LIBOBJ_DIR([src/missing])

dnl use pretty build output with automake >= 1.11
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])],
[AM_DEFAULT_VERBOSITY=1
 AC_SUBST(AM_DEFAULT_VERBOSITY)])

dnl ================
dnl   Check the OS
dnl ================

AC_CANONICAL_HOST

AH_TEMPLATE(OS_LINUX, [compiling under linux])    

AH_TEMPLATE(OS_BSD, [compiling under bsd])
dnl the subtype for BSD only used if there are significant differences
AH_TEMPLATE(OS_BSD_FREE, [compiling under free bsd])
AH_TEMPLATE(OS_BSD_OPEN, [compiling under open bsd])
AH_TEMPLATE(OS_BSD_NET, [compiling under net bsd])

AH_TEMPLATE(OS_DARWIN, [compiling under macosx])

AH_TEMPLATE(OS_SOLARIS, [compiling under solaris])

AH_TEMPLATE(OS_WINDOWS, [compiling under windows])
dnl the subtype does matter
AH_TEMPLATE(OS_CYGWIN, [compiling under cygwin])
AH_TEMPLATE(OS_MINGW, [compiling under mingw])

dnl initialize the conditionals
AM_CONDITIONAL(LINUX, false)
AM_CONDITIONAL(BSD, false)
AM_CONDITIONAL(DARWIN, false)
AM_CONDITIONAL(SOLARIS, false)
AM_CONDITIONAL(CYGWIN, false)
AM_CONDITIONAL(MINGW, false)
AM_CONDITIONAL(SFU, false)
   
case "$host_os" in
*linux*)
   AC_DEFINE(OS_LINUX)
   AM_CONDITIONAL(LINUX, true)
   OS="LINUX"
   ;;
*freebsd*)
   AC_DEFINE(OS_BSD)
   AC_DEFINE(OS_BSD_FREE)
   AM_CONDITIONAL(BSD, true)
   OS="FREEBSD"
   ;;
*openbsd*)
   AC_DEFINE(OS_BSD)
   AC_DEFINE(OS_BSD_OPEN)
   AM_CONDITIONAL(BSD, true)
   OS="OPENBSD"
   ;;
*netbsd*)
   AC_DEFINE(OS_BSD)
   AC_DEFINE(OS_BSD_NET)
   AM_CONDITIONAL(BSD, true)
   OS="NETBSD"
   ;;
*darwin*)
   AC_DEFINE(OS_DARWIN)
   AM_CONDITIONAL(DARWIN, true)
   OS="DARWIN"
   ;;
*solaris*)
   AC_DEFINE(OS_SOLARIS)
   AM_CONDITIONAL(SOLARIS, true)
   OS="SOLARIS"
   ;;
*cygwin*)
   EC_WINDOWS_KERNEL()
   EC_CYGWIN_KERNEL()
   AC_DEFINE(OS_CYGWIN)
   AM_CONDITIONAL(CYGWIN, true)
   OS="WINDOWS"
   OS_SUB="CYGWIN $ac_ec_windows_version"
   PL_LDFLAGS="-no-undefined"
   ;;
*mingw*)
   EC_WINDOWS_KERNEL()
   EC_MINGW_KERNEL()
   AC_DEFINE(OS_WINDOWS)
   AC_DEFINE(OS_MINGW)
   AM_CONDITIONAL(MINGW, true)
   OS="WINDWOS"
   OS_SUB="MINGW"
   EC_MINGW_SPECIAL_MAKEFILE()
   exit
   ;;
*)
   echo
   echo "NOT A SUPPORTED SYSTEM / OR SYSTEM NOT RECOGNIZED"
   echo
   ;;
esac

AC_SUBST(PL_LDFLAGS)

dnl ========================
dnl   Check the C compiler
dnl ========================

AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_GCC_TRADITIONAL
EC_GCC_MACRO
AH_TEMPLATE(GCC_VERSION, [gcc version])
gcc_ver=$($CC -dumpversion)
AC_DEFINE_UNQUOTED(GCC_VERSION, "$gcc_ver")

dnl ========================
dnl   Bison/Flex related...
dnl ========================

AC_PROG_YACC
AC_PROG_LEX

dnl ========================
dnl   Libtool related...
dnl ========================

AC_DISABLE_STATIC
LT_INIT([dlopen win32-dll])
AC_SEARCH_LIBS(dlopen,c dl,,)
LT_CONFIG_LTDL_DIR([libltdl])
LTDL_INIT
ac_ec_lt_dlopen=yes
AC_SEARCH_LIBS([lt_dlopen],[c dl ltdl],,[ac_ec_lt_dlopen=no])
AC_CHECK_HEADERS([dlfcn.h ltdl.h])

dnl ======================
dnl   Machine Endianness
dnl ======================

AC_C_BIGENDIAN

dnl =====================
dnl   Check for headers
dnl =====================

AC_HEADER_TIME
AC_HEADER_DIRENT

dnl These are required !!
AC_CHECK_HEADERS(unistd.h stdlib.h signal.h stdarg.h sys/ioctl.h sys/types.h dirent.h errno.h,,
   AC_MSG_WARN(****************************************************);
   AC_MSG_WARN(* REQUIRED !! I cant believe you don't have this !!*);
   AC_MSG_WARN(****************************************************);
   exit 1)

AC_CHECK_HEADERS(fcntl.h ctype.h libgen.h)
AC_CHECK_HEADERS(sys/types.h stdint.h)
AC_CHECK_HEADERS(sys/time.h sys/utsname.h)
AC_CHECK_HEADERS(termios.h)
AC_CHECK_HEADERS(sys/poll.h poll.h sys/select.h)
AC_CHECK_HEADERS(sys/cdefs.h)
dnl nameser NS_GET32 and so on...
EC_NS_GET()

dnl ==================================================================
dnl   Checks for typedefs, structures, and compiler characteristics.
dnl ==================================================================

AC_STRUCT_TM
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_C_CONST

dnl =====================
dnl   Check for programs
dnl =====================

ACLTX_PROG_PS2PDF(AC_MSG_WARN([Cannot find ps2pdf]))
AM_CONDITIONAL([PS2PDF], [test x$ps2pdf != xno])


dnl =====================
dnl   Check for libs
dnl =====================


AC_FUNC_VPRINTF
EC_PTHREAD_CHECK()
AC_CHECK_FUNCS(getifaddrs)
AC_CHECK_FUNCS(gettimeofday)
AC_CHECK_FUNCS(vsnprintf)
AC_CHECK_FUNCS(select poll strdup strerror strstr strsignal strtok_r)
AC_CHECK_FUNCS(uname)
AC_CHECK_FUNCS(daemon)

EC_MESSAGE(Checking for required libraries)

AC_SEARCH_LIBS(gethostbyname, c nsl socket,, AC_MSG_ERROR(not found.))
AC_SEARCH_LIBS(socket, c socket,, AC_MSG_ERROR(not found.))
AC_SEARCH_LIBS(poll, c poll) 
AC_SEARCH_LIBS(gzopen,c z,,AC_MSG_ERROR(not found.))

dnl
dnl  Do we have dn_expand ?
dnl
EC_RESOLVE_CHECK()

dnl ===============================
dnl   Check for non standard libs
dnl ===============================

EC_MESSAGE(Checking for missing functions)

AC_CONFIG_LIBOBJ_DIR(src/missing)

AM_CONDITIONAL(MISSING_STRLCPY, false)
AM_CONDITIONAL(MISSING_STRLCAT, false)
AM_CONDITIONAL(MISSING_STRSEP, false)
AM_CONDITIONAL(MISSING_MEMMEM, false)
AM_CONDITIONAL(MISSING_MEMCMP, false)
AM_CONDITIONAL(MISSING_BASENAME, false)
AM_CONDITIONAL(MISSING_GETOPT_LONG, false)
AM_CONDITIONAL(MISSING_STRCASESTR, false)
AM_CONDITIONAL(MISSING_INET_ATON, false)
AM_CONDITIONAL(MISSING_SCANDIR, false)

dnl AC_REPLACE_FUNCS(strlcpy)


AC_CHECK_FUNCS([strlcpy], , [AC_LIBOBJ(strlcpy) AM_CONDITIONAL(MISSING_STRLCPY, true)])
AC_CHECK_FUNCS([strlcat], , [AC_LIBOBJ(strlcat) AM_CONDITIONAL(MISSING_STRLCAT, true)])
AC_CHECK_FUNCS([strsep], , [AC_LIBOBJ(strsep) AM_CONDITIONAL(MISSING_STRSEP, true)])
AC_CHECK_FUNCS([memmem], , [AC_LIBOBJ(memmem) AM_CONDITIONAL(MISSING_MEMMEM, true)])
AC_CHECK_FUNCS([memcmp], , [AC_LIBOBJ(memcmp) AM_CONDITIONAL(MISSING_MEMCMP, true)])
AC_CHECK_FUNCS([basename], , [AC_LIBOBJ(basename) AM_CONDITIONAL(MISSING_BASENAME, true)])
AC_CHECK_FUNCS([getopt_long], , [AC_LIBOBJ(getopt) AM_CONDITIONAL(MISSING_GETOPT_LONG, true)])
AC_CHECK_FUNCS([strcasestr], , [AC_LIBOBJ(strcasestr) AM_CONDITIONAL(MISSING_STRCASESTR, true)])
AC_CHECK_FUNCS([scandir], , [AC_LIBOBJ(scandir) AM_CONDITIONAL(MISSING_SCANDIR, true)])
AC_CHECK_FUNCS([inet_aton], , [AC_LIBOBJ(inet_aton) AM_CONDITIONAL(MISSING_INET_ATON, true)])

AC_CHECK_LIB(resolv, inet_aton,
   AM_CONDITIONAL(INET_ATON_WANTS_RESOLV, true), 
   AM_CONDITIONAL(INET_ATON_WANTS_RESOLV, false))

dnl =======================================
dnl   Check user defined --enable-FEATURE
dnl =======================================

EC_MESSAGE(Checking user defined options)

dnl -----------
dnl -- DEBUG --
dnl -----------

AH_TEMPLATE(DEBUG, [debug support])

ac_ec_debug=no
AC_MSG_CHECKING([if --enable-debug option was specified])
AC_ARG_ENABLE(debug, AS_HELP_STRING([--enable-debug],[create a file for debugging messages]),
[ case "$enableval" in
   yes)
      AC_DEFINE(DEBUG, 1)
      DEBUG_FLAGS="-g -ggdb -Wmissing-prototypes -Wno-uninitialized -Wformat-security -Wsign-compare -Wall -Wno-pointer-sign"
      AC_MSG_RESULT(yes)
      ac_ec_debug=yes
      ;;
   no)  AC_MSG_RESULT(no)
      DEBUG_FLAGS="-O2 -funroll-loops -fomit-frame-pointer -Wall"
      ac_ec_debug=no
      ;;
esac ],
   AC_MSG_RESULT(no)
   DEBUG_FLAGS="-O2 -funroll-loops -fomit-frame-pointer -Wall"
   ac_ec_debug=no
)

dnl -------------
dnl -- PLUGINS --
dnl -------------

AM_CONDITIONAL(PLUGINS, false)
AH_TEMPLATE(HAVE_PLUGINS, [plugins support])

check_plugins=0
ac_ec_plugin=no
AC_MSG_CHECKING([if --enable-plugins option was specified])
if test $ac_ec_lt_dlopen = yes; then
AC_ARG_ENABLE(plugins, AS_HELP_STRING([--enable-plugins],[enable the use of plugins in ettercap]),
[ case "$enableval" in
   yes)
      AC_MSG_RESULT(yes)
      AM_CONDITIONAL(PLUGINS, true)
      AC_DEFINE(HAVE_PLUGINS, 1)
      ac_ec_plugin=yes
      ;;
   no)  AC_MSG_RESULT(no)
      ac_ec_plugin=no
      ;;
esac ],
   AC_MSG_RESULT(yes by default)
   AM_CONDITIONAL(PLUGINS, true)
   AC_DEFINE(HAVE_PLUGINS, 1)
   ac_ec_plugin=yes
)
else
   AC_MSG_RESULT(not supported)
fi

dnl ==================
dnl   Check for libs
dnl ==================


dnl ---------
dnl  libpcap
dnl ---------
ac_ec_libpcap=default

AC_MSG_CHECKING(for libpcap)
AC_ARG_WITH(libpcap, AS_HELP_STRING([--with-libpcap=DIR],[use libpcap in DIR]),
[ case "$withval" in
  no)
     AC_MSG_RESULT(no)
     AC_MSG_ERROR(["*** ettercap cannot operate without libpcap. ***"])
     ;;
  *)
     if test -f $withval/pcap.h; then
        owd=$(pwd)
        if cd $withval; then withval=$(pwd); cd $owd; fi
        PCAPINC="-I$withval"
        if test "$OS" = "WINDOWS"; then
           PCAPLIB="-L$withval -lwpcap -lpacket"
        else
           PCAPLIB="-L$withval -lpcap"
        fi
        ac_ec_libpcap=$withval
        AC_MSG_RESULT($withval)
     elif test -f $withval/include/pcap.h; then
        owd=$(pwd)
        if cd $withval; then withval=$(pwd); cd $owd; fi
        PCAPINC="-I$withval/include"
        if test "$OS" = "WINDOWS"; then
           PCAPLIB="-L$withval/lib -lwpcap -lpacket"
        else
           PCAPLIB="-L$withval/lib -lpcap"
        fi
        ac_ec_libpcap=$withval
        AC_MSG_RESULT($withval)
     else
        AC_MSG_RESULT(no)
        AC_MSG_ERROR([pcap.h not found in $withval])
     fi
     ;;
  esac ],
[ if test -f /usr/include/pcap/pcap.h; then
     PCAPINC="-I/usr/include/pcap"
     if test "$OS" = "WINDOWS"; then
        PCAPLIB="-lwpcap -lpacket"
     else
        PCAPLIB="-lpcap"
     fi
  elif test -f /usr/include/pcap.h; then
     if test "$OS" = "WINDOWS"; then
        PCAPLIB="-lwpcap -lpacket"
     else
        PCAPLIB="-lpcap"
     fi
  elif test -f /usr/local/include/pcap.h; then
     PCAPINC="-I/usr/local/include"
     if test "$OS" = "WINDOWS"; then
        PCAPLIB="-lwpcap -lpacket"
     else
        PCAPLIB="-lpcap"
     fi
  else
     AC_MSG_RESULT(no)
     AC_MSG_ERROR([libpcap not found])
  fi
  AC_MSG_RESULT(yes) ]
)

if test "$OS" = "WINDOWS"; then
   EC_CHECK_FUNC(wpcap, pcap_datalink_val_to_description, $PCAPLIB, $LIBS,, AC_MSG_ERROR([Incorrect libpcap version. libpcap >= 0.8.1 required]))
   EC_CHECK_FUNC(packet, PacketInitPacket, $PCAPLIB, $LIBS,, AC_MSG_ERROR([Incorrect libpcap version. libpcap >= 0.8.1 required]))
   AC_CHECK_LIB(ws2_32, ntohs,, AC_MSG_ERROR([Incorrect ws2_32 version.]))
   AC_CHECK_LIB(iphlpapi, main)
else
   EC_CHECK_FUNC(pcap, pcap_datalink_val_to_description, $PCAPLIB, $LIBS,, AC_MSG_ERROR([Incorrect libpcap version. libpcap >= 0.8.1 required]))
fi

dnl ---------
dnl  libnet
dnl ---------
ac_ec_libnet=default

AC_ARG_WITH(libnet-config, AS_HELP_STRING([--with-libnet-config=DIR],[use libnet-config in DIR]),
  [LIBNET_CONFIG="$withval"],
  [AC_PATH_PROG(LIBNET_CONFIG,libnet-config,no)])

AC_MSG_CHECKING(for libnet libraries)
if test "$LIBNET_CONFIG" != "no"; then
  if ! $LIBNET_CONFIG --help > /dev/null 2>&1; then
     AC_MSG_RESULT(no)
     AC_MSG_ERROR(Could not find libnet-config anywhere (see config.log for details).)
  fi

  LNETINC="$($LIBNET_CONFIG --cflags)"
  LNETLIB="$($LIBNET_CONFIG --libs)"

  AC_MSG_RESULT($LIBNET_CONFIG)
  ac_ec_libnet=$LIBNET_CONFIG
else
  AC_MSG_ERROR(No libnet-config was specified (see config.log for details).)
fi

EC_CHECK_FUNC(net, libnet_adv_free_packet, $LNETLIB, $LIBS,, AC_MSG_ERROR([Incorrect libnet version. libnet >= 1.1.2.1 required]))

dnl ------------------
dnl Checks for openssl
dnl ------------------

AH_TEMPLATE(HAVE_OPENSSL, [openssl executable path])
AM_CONDITIONAL(OPENSSL, false)
ac_ec_libssl="NO"

AC_MSG_CHECKING(for openssl)
AC_ARG_WITH(openssl, AS_HELP_STRING([--with-openssl=DIR],[use openssl in DIR]),
[ case "$withval" in
  yes|no)
     AC_MSG_RESULT(no)
     ;;
  *)
     if test -f $withval/include/openssl/ssl.h; then
        owd=$(pwd)
        if cd $withval; then withval=$(pwd); cd $owd; fi
        SSLINC="-I$withval/include"
        SSLLIB="-L$withval/lib -lssl -lcrypto"
        AC_DEFINE(HAVE_OPENSSL, 1)
        AM_CONDITIONAL(OPENSSL, true)
        ac_ec_libssl=$withval
        AC_MSG_RESULT($withval)
     elif test -f $withval/ssl/include/openssl/ssl.h; then
        owd=$(pwd)
        if cd $withval; then withval=$(pwd); cd $owd; fi
        SSLINC="-I$withval/ssl/include"
        SSLLIB="-L$withval/ssl/lib -lssl -lcrypto"
        AC_DEFINE(HAVE_OPENSSL, 1)
        AM_CONDITIONAL(OPENSSL, true)
        ac_ec_libssl=$withval
        AC_MSG_RESULT($withval)
     else
        AC_MSG_RESULT(no)
        AC_MSG_ERROR([ssl.h not found in $withval])
     fi
     ;;
  esac ],
[ if test -f /usr/include/openssl/ssl.h; then
     SSLLIB="-lssl -lcrypto"
     AC_DEFINE(HAVE_OPENSSL, 1)
     AM_CONDITIONAL(OPENSSL, true)
     AC_MSG_RESULT(yes)
     ac_ec_libssl=default
  else
     AC_MSG_RESULT(no)
  fi]
)


dnl ---------
dnl  libpcre
dnl ---------

AH_TEMPLATE(HAVE_PCRE, [perl compatible regex])

ac_ec_pcre=no

AC_MSG_CHECKING(for libpcre)
AC_ARG_WITH(libpcre, AS_HELP_STRING([--with-libpcre=DIR],[use libpcre in DIR]),
[ case "$withval" in
  no)
     AC_MSG_RESULT(no)
     ;;
  *)
     if test -f $withval/pcre.h; then 
        owd=$(pwd)
        if cd $withval; then withval=$(pwd); cd $owd; fi
        PCREINC="-I$withval/"
        PCRELIB="-L$withval/ -lpcre"
        AM_CONDITIONAL(HAVE_PCRE, true) 
        AC_DEFINE(HAVE_PCRE, 1)
        ac_ec_pcre=yes
        AC_MSG_RESULT($withval)
     elif test -f $withval/include/pcre.h; then
        owd=$(pwd)
        if cd $withval; then withval=$(pwd); cd $owd; fi
        PCREINC="-I$withval/include"
        PCRELIB="-L$withval/lib -lpcre"
        AM_CONDITIONAL(HAVE_PCRE, true) 
        AC_DEFINE(HAVE_PCRE, 1)
        ac_ec_pcre=yes
        AC_MSG_RESULT($withval)
     else
        AC_MSG_RESULT(no)
        AC_MSG_ERROR([pcre.h not found in $withval])
     fi
     ;;
  esac ],
[ if test -f /usr/include/pcre.h; then
     AM_CONDITIONAL(HAVE_PCRE, true) 
     AC_DEFINE(HAVE_PCRE, 1)
     ac_ec_pcre=yes
     PCREINC=""
     PCRELIB="-lpcre"
     AC_MSG_RESULT(yes)
  else
     AC_MSG_RESULT(no)
     AM_CONDITIONAL(HAVE_PCRE, false) 
  fi
]
)

dnl ------------------
dnl  iconv / libiconv
dnl ------------------

AH_TEMPLATE(HAVE_UTF8, [support for UTF-8])

ac_ec_utf8=no

AC_MSG_CHECKING(for iconv)
AC_ARG_WITH(iconv, AS_HELP_STRING([--with-iconv=DIR],[use iconv in DIR]),
[ case "$withval" in
  no)
     AC_MSG_RESULT(no)
     ;;
  *)
     if test -f $withval/iconv.h; then 
        owd=$(pwd)
        if cd $withval; then withval=$(pwd); cd $owd; fi
        ICONVINC="-I$withval/"
        ICONVLIB="-L$withval/ -liconv"
        AC_MSG_RESULT($withval)
     elif test -f $withval/include/iconv.h; then
        owd=$(pwd)
        if cd $withval; then withval=$(pwd); cd $owd; fi
        ICONVINC="-I$withval/include"
        ICONVLIB="-L$withval/lib -liconv"
        AC_MSG_RESULT($withval)
     else
        AC_MSG_RESULT(no)
        AC_MSG_ERROR([iconv.h not found in $withval])
     fi
     ;;
  esac ],
[ if test -f /usr/include/iconv.h; then
     AC_MSG_RESULT(yes)
     ICONVINC=""
     ICONVLIB=""
     AC_SEARCH_LIBS(iconv, c, , ICONVLIB="-liconv")
  else
     AC_MSG_RESULT(no)
  fi
]
)

EC_CHECK_FUNC(c, iconv, $ICONVLIB,, [AC_DEFINE(HAVE_UTF8,1) ac_ec_utf8=yes])
EC_CHECK_FUNC(iconv, iconv, $ICONVLIB,, [AC_DEFINE(HAVE_UTF8,1) ac_ec_utf8=yes ICONVLIB="-liconv"])
EC_CHECK_FUNC(iconv, libiconv, $ICONVLIB,, [AC_DEFINE(HAVE_UTF8,1) ac_ec_utf8=yes ICONVLIB="-liconv"])

dnl ---------
dnl  ncurses
dnl ---------
AH_TEMPLATE(HAVE_NCURSES, [ncurses support])
AM_CONDITIONAL(NCURSES, false)

ac_ec_libncurses="NO"

AC_MSG_CHECKING(for libncurses)
AC_ARG_WITH(libncurses, AS_HELP_STRING([--with-libncurses=DIR],[use libncurses in DIR]),
[ case "$withval" in
  yes|no)
     AC_MSG_RESULT(no)
     ;;
  *)
     if test -f $withval/ncurses.h \
             -a -f $withval/panel.h \
             -a -f $withval/form.h \
             -a -f $withval/menu.h; then
        owd=$(pwd)
        if cd $withval; then withval=$(pwd); cd $owd; fi
        NCURSINC="-I$withval"
        NCURSLIB="-L$withval -lpanel -lmenu -lform -lncurses"
        AC_DEFINE(HAVE_NCURSES, 1)
        AM_CONDITIONAL(NCURSES, true)
        ac_ec_libncurses=$withval
        AC_MSG_RESULT($withval)
     elif test -f $withval/include/ncurses.h \
               -a -f $withval/include/panel.h \
               -a -f $withval/include/menu.h \
               -a -f $withval/include/form.h; then
        owd=$(pwd)
        if cd $withval; then withval=$(pwd); cd $owd; fi
        NCURSINC="-I$withval/include"
        NCURSLIB="-L$withval/lib -lpanel -lmenu -lform -lncurses"
        AC_DEFINE(HAVE_NCURSES, 1)
        AM_CONDITIONAL(NCURSES, true)
        ac_ec_libncurses=$withval
        AC_MSG_RESULT($withval)
     elif test -f $withval/include/ncurses/ncurses.h \
               -a -f $withval/include/ncurses/panel.h \
               -a -f $withval/include/ncurses/menu.h \
               -a -f $withval/include/ncurses/form.h; then
        owd=$(pwd)
        if cd $withval; then withval=$(pwd); cd $owd; fi
        NCURSINC="-I$withval/include/ncurses"
        NCURSLIB="-L$withval/lib -lpanel -lmenu -lform -lncurses"
        AC_DEFINE(HAVE_NCURSES, 1)
        AM_CONDITIONAL(NCURSES, true)
        ac_ec_libncurses=$withval
        AC_MSG_RESULT($withval)
     else
        AC_MSG_RESULT(no)
        AC_MSG_ERROR([ncurses.h menu.h panel.h form.h not found in $withval])
     fi
     ;;
  esac ],
[ if test -f /usr/include/ncurses/ncurses.h; then
     if test ! -f /usr/include/ncurses/form.h \
               -a -f /usr/include/ncurses/menu.h \
               -a -f /usr/include/ncurses/panel.h; then
         AC_MSG_RESULT(no)
     else 
         NCURSINC="-I/usr/include/ncurses"
         NCURSLIB="-lpanel -lmenu -lform -lncurses"
         AC_DEFINE(HAVE_NCURSES, 1)
         AM_CONDITIONAL(NCURSES, true)
         ac_ec_libncurses=default
         AC_MSG_RESULT(yes)
     fi
  elif test -f /usr/include/ncurses.h; then
     if test ! -f /usr/include/form.h \
               -a -f /usr/include/menu.h \
               -a -f /usr/include/panel.h; then
         AC_MSG_RESULT(no)
     else 
         NCURSLIB="-lpanel -lmenu -lform -lncurses"
         AC_DEFINE(HAVE_NCURSES, 1)
         AM_CONDITIONAL(NCURSES, true)
         ac_ec_libncurses=default
         AC_MSG_RESULT(yes)
     fi
  else
     AC_MSG_RESULT(no)
  fi]
)

dnl ---------
dnl  GTK
dnl ---------

AH_TEMPLATE(HAVE_GTK, [gtk+ support])
AM_CONDITIONAL(GTK, false)

ac_ec_gtk="NO"

AC_MSG_CHECKING(if --enable-gtk option was specified)
AC_ARG_ENABLE(gtk, AS_HELP_STRING([--enable-gtk],[enable the gtk interface]),
[ case "$enableval" in
  no)
     AC_MSG_RESULT(no)
     ;;
  yes)
      AC_MSG_RESULT(yes)
      AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
      if test "$PKG_CONFIG" = "no" ; then
         AC_MSG_RESULT(pkg-config not found)
      else
         AC_MSG_CHECKING(for gtk+)
         PKG_CHECK_MODULES(GTK, gtk+-2.0 >= 2.0.0 pango >= 1.0 atk >= 1.0,
            [ AC_DEFINE(HAVE_GTK, 1)
              AM_CONDITIONAL(GTK, true)
              AC_MSG_RESULT(yes)
              GTK_LIBS="$GTK_LIBS -lgthread-2.0"
              ac_ec_gtk=yes ],
            [ AC_MSG_RESULT(no) ]
         )
      fi
     ;;
  esac ],
[ 
     AC_MSG_RESULT(yes)
     AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
     if test "$PKG_CONFIG" = "no" ; then
        AC_MSG_RESULT(pkg-config not found)
     else
        PKG_CHECK_MODULES(GTK, gtk+-2.0 >= 2.0.0 pango >= 1.0 atk >= 1.0,
           [ AC_DEFINE(HAVE_GTK, 1)
             AM_CONDITIONAL(GTK, true)
             GTK_LIBS="$GTK_LIBS -lgthread-2.0"
             ac_ec_gtk=yes ]
        )
     fi
])


dnl -----------------------
dnl  set up the final vars
dnl -----------------------
EC_CFLAGS="$DEBUG_FLAGS $PCAPINC $LNETINC $SSLINC $PCREINC $ICONVINC"
EC_LIBS="$LIBS $PCAPLIB $LNETLIB $SSLLIB $PCRELIB $NCURSLIB $GTK_LIBS $ICONVLIB"

AC_SUBST(EC_CFLAGS)
AC_SUBST(EC_LIBS)

AC_SUBST(PCAPINC)
AC_SUBST(LNETINC)
AC_SUBST(SSLINC)
AC_SUBST(PCREINC)
AC_SUBST(NCURSINC)
AC_SUBST(GTK_CFLAGS)

AC_SUBST(PCAPLIB)
AC_SUBST(LNETLIB)
AC_SUBST(SSLLIB)
AC_SUBST(PCRELIB)
AC_SUBST(NCURSLIB)
AC_SUBST(GTK_LIBS)

AC_SUBST(ICONVLIB)

dnl  for the plugins
PL_CFLAGS="$DEBUG_FLAGS $PCREINC"
AC_SUBST(PL_CFLAGS)

dnl ===============
dnl   FINISHED !!
dnl ===============

EC_MESSAGE(Writing output files)

AC_CONFIG_FILES(  Makefile
                  Makefile.mingw
                  man/Makefile 
                  man/ettercap.8 
                  man/ettercap_curses.8 
                  man/ettercap_plugins.8 
                  man/etterlog.8 
                  man/etterfilter.8 
                  man/etter.conf.5
                  share/Makefile 
                  src/Makefile 
                  src/os/Makefile 
                  src/interfaces/Makefile 
                  src/interfaces/daemon/Makefile 
                  src/interfaces/text/Makefile 
                  src/interfaces/curses/Makefile 
                  src/interfaces/curses/widgets/Makefile 
                  src/interfaces/gtk/Makefile 
                  include/Makefile
                  utils/Makefile
                  utils/etterlog/Makefile
                  utils/etterfilter/Makefile
                  desktop/Makefile
                  plug-ins/Makefile
                  plug-ins/arp_cop/Makefile
                  plug-ins/autoadd/Makefile
                  plug-ins/chk_poison/Makefile
                  plug-ins/dos_attack/Makefile
                  plug-ins/dns_spoof/Makefile
                  plug-ins/dummy/Makefile
                  plug-ins/find_conn/Makefile
                  plug-ins/find_ettercap/Makefile
                  plug-ins/find_ip/Makefile
                  plug-ins/finger/Makefile
                  plug-ins/finger_submit/Makefile
                  plug-ins/gre_relay/Makefile
                  plug-ins/gw_discover/Makefile
                  plug-ins/isolate/Makefile
                  plug-ins/link_type/Makefile
                  plug-ins/pptp_chapms1/Makefile
                  plug-ins/pptp_clear/Makefile
                  plug-ins/pptp_pap/Makefile
                  plug-ins/pptp_reneg/Makefile
                  plug-ins/rand_flood/Makefile
                  plug-ins/remote_browser/Makefile
                  plug-ins/reply_arp/Makefile
                  plug-ins/repoison_arp/Makefile
                  plug-ins/scan_poisoner/Makefile
                  plug-ins/search_promisc/Makefile
                  plug-ins/smb_clear/Makefile
                  plug-ins/smb_down/Makefile
                  plug-ins/stp_mangler/Makefile)

AC_OUTPUT

dnl ===============
dnl   THE SUMMARY
dnl ===============

EC_MESSAGE(ettercap has been configured as follow)

echo "=================================================="
echo
   EC_CHECK_OPTION(" Install directory: ",${prefix})
echo
echo
   EC_CHECK_OPTION("Libraries :", "")
echo
   EC_CHECK_OPTION(" LIBPCAP ................ ",${ac_ec_libpcap})
   EC_CHECK_OPTION(" LIBNET ................. ",${ac_ec_libnet})
   EC_CHECK_OPTION(" LIBSSL ................. ",${ac_ec_libssl})
   EC_CHECK_OPTION(" NCURSES ................ ",${ac_ec_libncurses})
   EC_CHECK_OPTION(" GTK+ ................... ",${ac_ec_gtk})
echo
   EC_CHECK_OPTION("Functionalities :", "")
echo
   EC_CHECK_OPTION(" Debug mode ............. ",${ac_ec_debug})
   EC_CHECK_OPTION(" Plugin support ......... ",${ac_ec_plugin})
   EC_CHECK_OPTION(" Passive DNS ............ ",${ac_ec_dns})
   EC_CHECK_OPTION(" Perl regex in filters .. ",${ac_ec_pcre})
   EC_CHECK_OPTION(" Iconv UTF-8 support .... ",${ac_ec_utf8})
echo
echo "=================================================="
echo

dnl ================


dnl vim:ts=3:expandtab

