#!/bin/bash
set -e
BINARY=`cat build/binary.txt`
sudo gdb build/$BINARY
