#!/bin/bash
set -e
# need sudo for creating TAP node
../../lxp-run --build --pgo-use --def FINAL=1 --create-tap --flush
# send 40MB file
SIZE=40960
echo ">> dd if=/dev/zero bs=1024 count=$SIZE > /dev/tcp/10.0.0.42/1338"
# need root for bridge
../../lxp-run --run --root
BINARY=build/"`cat build/binary.txt`"
cp $BINARY build/final_binary
echo "Success - stored $BINARY as build/final_binary"
