#!/bin/bash

cmake -B build
make $1 -C build

./build/$1 $2 $3
