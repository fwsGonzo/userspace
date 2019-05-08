#!/bin/bash
set -e
#export CC=gcc-7
#export CXX=g++-7
AS_ROOT=ON ../../lxp-run

if [ $? == 0 ]; then
  echo ">>> Userspace TCP benchmark success!"
else
  exit 1
fi
