#!/bin/bash
set -e
export CC=gcc-7
export CXX=g++-7
$INCLUDEOS_PREFIX/bin/lxp-run

if [ $? == 0 ]; then
  echo ">>> Linux Userspace LiveUpdate test success!"
else
  exit 1
fi
