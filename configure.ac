# Author: Alexander Rykovanov 2009
#
#
# Distributed under the GNU LGPL License
# (See accompanying file LICENSE or copy at 
# http://www.gnu.org/licenses/lgpl.html)
#

AC_INIT([opcuaclient], [0.1.3], [rykovanov.as@gmail.com])
AC_CONFIG_AUX_DIR([.])
AC_CONFIG_SRCDIR([src/opcua_main.cpp])
AM_INIT_AUTOMAKE([-Wall -Werror])

CXXFLAGS="-O0 -g -std=c++0x"

AC_PROG_CXX
AM_PROG_AR
AC_PROG_LIBTOOL

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADER([config.h])


AC_ARG_WITH([gtest], 
            [AS_HELP_STRING([--with-gtest=DIR], [defines path to gtest root directory])],
            [ 
              AC_SUBST([GTEST_LIB], [-Wl,--whole-archive,$with_gtest/lib/.libs/libgtest.a,--no-whole-archive])
              AC_SUBST([GTEST_MAIN_LIB], [-Wl,--whole-archive,$with_gtest/lib/.libs/libgtest_main.a,--no-whole-archive])
              AC_SUBST([GTEST_INCLUDES], [-I$with_gtest/include])
              AC_MSG_NOTICE([Gtest path: $with_gtest]) 
            ], 
            [ 
              AC_SUBST([GTEST_LIB], [-lgtest])
              AC_SUBST([GTEST_MAIN_LIB], [-lgtest_main])
            ])

AC_ARG_WITH([gmock], 
            [AS_HELP_STRING([--with-gmock=DIR], [defines path to gmock root directory])],
            [ 
              AC_SUBST([GMOCK_LIBS], [-Wl,--whole-archive,$with_gmock/lib/.libs/libgmock.a,--no-whole-archive ])
              AC_SUBST([GMOCK_INCLUDES], [-I$with_gmock/include])
              AC_MSG_NOTICE([Gmock path: $with_gmock]) 
            ], 
            [ 
              AC_SUBST([GMOCK_LIBS], [-lgmock])
            ])


AC_ARG_WITH([uamappings], 
            [AS_HELP_STRING([--with-uamappings=DIR], [defines path to uamappings root directory])],
            [ 
              AC_SUBST([UAMAPPINGS_LIBS], ["-L$with_uamappings/.libs -lopcuabinary"])
              AC_SUBST([UAMAPPINGS_INCLUDES], [-I$with_uamappings/include])
              AC_MSG_NOTICE([ua mappings path: $with_uamappings]) 
            ], 
            [ 
              AC_SUBST([UAMAPPING_LIBS], [-lopcuabinary])
            ])

AC_ARG_WITH([opccore],
            [AS_HELP_STRING([--with-opccore=DIR], [defines path to the root directory of libopccore library.])],
            [ 
              AC_SUBST([OPC_CORE_LIBS], ["-L$with_opccore/.libs -lopcuacore -lxml2"])
              AC_SUBST([OPC_CORE_INCLUDES], ["-I$with_opccore/include -I/usr/include/libxml2"])
              AC_MSG_NOTICE([opccore path: $with_opccore]) 
            ], 
            [ 
              AC_SUBST([OPC_CORE_INCLUDES], ["-I/usr/include/libxml2"])
              AC_SUBST([OPC_CORE_LIBS], [-lopcuacore])
            ])

AC_ARG_WITH([testserver-uri], 
            [AS_HELP_STRING([--with-testserver-uri=uri], [defines uri of the server for performing testing of client.])],
            [ 
              AC_SUBST([TEST_SERVER_URI], [$with_testserver_uri])
              AC_MSG_NOTICE([Test server uri: $TEST_SERVER_URI]) 
            ], 
            [ 
            ])

AC_ARG_WITH([config-path], 
            [AS_HELP_STRING([--with-config-path], [path to the modules configuration file. By default $sysconfdir/opcua/client.modules])],
            [ 
              AC_SUBST(CLIENT_CONFIG_PATH)
              AC_SUBST([CLIENT_CONFIG_PATH], ["-DCLIENT_CONFIG_PATH=\"\\\"$with_config_path]\\\"\"")
              AC_MSG_NOTICE([Modules configuration file: $CLIENT_CONFIG_PATH]) 
            ], 
            [ 
              AC_SUBST([CLIENT_CONFIG_PATH], ["-DCLIENT_CONFIG_PATH=\"\\\"$sysconfdir/opcua/client.modules\\\"\""])
            ])

AC_SUBST([RELEASE_DATE], [$(date -R)])

#check headers
AC_CHECK_HEADERS([unistd.h])

#################################################################
AC_CONFIG_FILES([Makefile opcuaclient.pc debian/changelog])
AC_OUTPUT

