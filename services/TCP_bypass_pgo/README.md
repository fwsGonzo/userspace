# TCP Benchmarking Experiments

## Howto:

Receive data from the instance:
```
./send.sh
or
ncat 10.0.0.42 1337 --recv-only > bla.txt
```

Send data to the instance:
```
./receive.sh
or
cat bla.txt | ncat 10.0.0.42 1338 --send-only
or
dd if=/dev/zero bs=1024 count=40960 > /dev/tcp/10.0.0.42/1338
```

Configure by changing the variables at the top of experiment.cpp
