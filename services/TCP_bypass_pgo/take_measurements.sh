#!/bin/bash
for i in {1..30}
do
  dd if=/dev/zero bs=1024 count=81920 > /dev/tcp/10.0.10.42/1338
  #dd if=/dev/zero bs=1024 count=81920 > /dev/tcp/127.0.0.1/1338
done
echo "Done"
