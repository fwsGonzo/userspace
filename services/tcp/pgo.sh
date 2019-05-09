#!/bin/bash
set -e
#export CC=clang-6
#export CXX=clang++-6
$INCLUDEOS_PREFIX/bin/lxp-pgo | grep 'Server received'

if [ $? == 0 ]; then
  echo ">>> Linux Userspace TCP test success!"
else
  exit 1
fi
