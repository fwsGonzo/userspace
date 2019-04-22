#!/bin/bash
set -e
export CC=clang-6.0
export CXX=clang++-6.0
RUN=OFF ../../lxp-run

if [ $? == 0 ]; then
  echo ">>> Building fuzzer success!"
else
  exit 1
fi
