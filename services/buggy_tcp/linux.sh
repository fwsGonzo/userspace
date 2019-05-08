#!/bin/bash
set -e
#nc -w 3 10.0.0.59 666 < build/service
while :
do
  nc -l -p 1666 > out.file
  ls -la out.file
done
