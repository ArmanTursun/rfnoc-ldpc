#!/bin/bash

cd ../uhd-offloading/host/build
#make uninstall
make -j16
make install
ldconfig
