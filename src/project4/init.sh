#!/bin/bash

mkdir -p data
mkdir -p log
mkdir -p out
mkdir -p result

cmake -B build
make all -C build
