#!/bin/bash
set -e
#export CC=clang-6
#export CXX=clang++-6
../../lxp-pgo

if [ $? == 0 ]; then
  echo ">>> Linux Userspace TCP test success!"
else
  exit 1
fi
