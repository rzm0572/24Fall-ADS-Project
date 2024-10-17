#!/bin/bash

TEST_CASE=3

if [[ -n "$3" ]]; then
    TEST_CASE=$3
fi

cmake -B build
make $1 -C build
./build/$1 $2 ${TEST_CASE}
