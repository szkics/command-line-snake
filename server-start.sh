#!/bin/bash
echo "stty -g $(stty -g)" > restore-sanity
stty cbreak
g++ -Wall -g -std=c++1z -pthread communication/server.cpp snake/snake.cpp entities/entities.cpp gamelogic/gamelogic.cpp dependencies/kbhit.cpp -o server
./server
rm server
/bin/stty cooked
rm restore-sanity
