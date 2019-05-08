#!/bin/bash
#fallocate -l 35741088 zeroes.elf
while :
do
  echo "Sending to IncludeOS"
  #dd if=/dev/zero bs=1024 count=34903 > /dev/tcp/10.0.0.59/666
  dd if=/dev/zero bs=1024 count=34903 > /dev/tcp/10.0.0.59/666
  #echo "Sending to Linux"
  #dd if=/dev/zero bs=1024 count=34903 > /dev/tcp/10.0.0.1/1666
  #exit 0
done
