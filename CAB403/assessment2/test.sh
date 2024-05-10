#!/bin/bash

echo "DOOR 101 127.0.0.1:4901 FAIL_SAFE#" | nc 127.0.0.1 5000

echo "DOOR 102 127.0.0.1:4902 FAIL_SAFE#" | nc 127.0.0.1 5000

echo "DOOR 103 127.0.0.1:4903 FAIL_SAFE#" | nc 127.0.0.1 5000
sleep 1

echo "" | nc 127.0.0.1 5000
echo "" | nc 127.0.0.1 5000
echo "" | nc 127.0.0.1 5000
sleep 1

echo "CARDREADER 103 HELLO#" | nc 127.0.0.1 5000
sleep 1

#echo "CARDREADER 101 SCANNED db4ed0a0bfbb00ac#" | nc 127.0.0.1 5000

