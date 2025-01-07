#!/bin/bash
echo "stty -g $(stty -g)" > restore-sanity
stty cbreak
g++ -Wall -g -std=c++17 -pthread communication/client.cpp -o client
./client
/bin/stty cooked
rm -f client
rm -f restore-sanity