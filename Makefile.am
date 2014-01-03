# Author: Alexander Rykovanov 2012
#
# Distributed under the GNU LGPL License
# (See accompanying file LICENSE or copy at 
# http://www.gnu.org/copyleft/gpl.html)
#
# $Id:  $
# $Date: $
# $Revision: $


AM_CPPFLAGS= $(CLIENT_CONFIG_PATH) -I$(top_srcdir) -Iinclude $(URI_INCLUDES) $(UA_MAPPING_INCLUDES) $(OPC_CORE_INCLUDES) $(GTEST_INCLUDES) $(GMOCK_INCLUDES) -I$(top_srcdir)/tests -I/usr/include/libxml2

configdir=$(sysconfdir)/opcua
config_DATA = configs/client.modules

opcincludedir = $(includedir)/opc
opcuaincludedir = $(opcincludedir)/ua
protocolincludedir = $(opcuaincludedir)/protocol
binaryincludedir = $(protocolincludedir)/binary
uaclientincludedir = $(opcuaincludedir)/client

uaclientinclude_HEADERS = \
  include/opc/ua/client/addon.h \
  include/opc/ua/client/binary_computer.h \
  include/opc/ua/client/remote_computer.h \
  include/opc/ua/client/remote_connection.h

binaryinclude_HEADERS = \
  include/opc/ua/protocol/binary/secure_connection.h

lib_LTLIBRARIES = libopcua_client.la
libopcua_client_la_SOURCES = \
  src/computer.cpp \
  src/binary_computer_addon.cpp \
  src/binary_computer.cpp \
  src/binary_connection.cpp \
  src/binary_secure_channel.cpp \
  src/endpoints.h \
  src/stream_attribute.h \
  src/stream_computer.h \
  src/stream_subscription.h \
  src/stream_view.h

libopcua_client_la_LDFLAGS =  $(UA_MAPPING_LIBS) $(OPC_CORE_LIBS) -ldl -lpthread -lxml2

bin_PROGRAMS = opcua

opcua_SOURCES = \
  src/opcua_main.cpp \
  src/opcua_options.cpp \
  src/opcua_options.h

opcua_LDFLAGS =  $(UA_MAPPING_LIBS) $(OPC_CORE_LIBS) -ldl -lboost_program_options -lpthread -lxml2

#TESTS = libuaclient_test

#check_PROGRAMS = $(TESTS)

#libuaclient_test_SOURCES =  \
#  src/computer.cpp \
#  src/binary_connection.cpp \
#  tests/common.h \
#  tests/computer_attribute.cpp \
#  tests/computer_connect.cpp \
#  tests/computer_endpoints.cpp \
#  tests/computer_session.cpp \
#  tests/computer_view.cpp

#libuaclient_test_CPPFLAGS = $(INCLUDES) $(TESTINCLUDES)
#libuaclient_test_LDFLAGS = -lpthread -Wl,-z,defs $(UA_MAPPING_LIBS)  $(GTEST_LIB) $(GTEST_MAIN_LIB) $(GMOCK_LIBS) $(URI_LIBS) -no-undefined

EXTRA_DIST = \
  configs/client.modules \
  debian make_deb.sh

pkgsharedir = $(libdir)/pkgconfig
pkgshare_DATA = opcuaclient.pc

pkgconfigdir = $(datarootdir)/pkgconfig
pkgconfig_DATA = opcuaclient.pc

clean-local:
	rm -rvf opcuaclient*$(VERSION)*

dist-deb:
	$(top_srcdir)/make_deb.sh

