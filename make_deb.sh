#!/bin/sh
tar -xvf opcuaclient-${VERSION}.tar.gz
cd opcuaclient-${VERSION}
dh_make -y -l -c lgpl3 -e rykovanov.as@gmail.com -f ../opcuaclient-${VERSION}.tar.gz
dpkg-buildpackage -rfakeroot -nc -F

