#!/bin/sh
set -e

cd "$(dirname "$0")"

set -x
../bin/razuberi $1.ts -o $1.cpp
indent $1.cpp
g++ -c -I ../../cpp/out/include $1.cpp -o $1.o
g++ -L ../../cpp/out/lib -l razuberi $1.o -o $1
set +x
echo
$1
