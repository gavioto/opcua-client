#!/bin/sh
make dist
tar -xvf opcuaclient-0.1.2.tar.gz
cd opcuaclient-0.1.2
dh_make -y -l -c lgpl3 -e rykovanov.as@gmail.com -f ../opcuaclient-0.1.2.tar.gz
dpkg-buildpackage -rfakeroot

