#!/bin/bash
set -e
../../lxp-run #| grep 'Server received'

if [ $? == 0 ]; then
  echo ">>> Userspace TCP benchmark success!"
else
  exit 1
fi
