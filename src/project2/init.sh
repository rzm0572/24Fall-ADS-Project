#!/bin/bash

mkdir -p data
mkdir -p result
mkdir -p log

cd data
mkdir -p processed
mkdir -p queries
mkdir -p raw
mkdir -p results
cd ..

cmake -B build
