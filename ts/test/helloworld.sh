#!/bin/sh
set -e

bin/razuberi.js test/helloworld.ts -o test/helloworld.cpp
g++ -c -I ../cpp/out/include test/helloworld.cpp -o test/helloworld.o
g++ -L ../cpp/out/lib -l razuberi test/helloworld.o -o test/helloworld
test/helloworld
