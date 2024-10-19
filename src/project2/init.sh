#!/bin/bash

cmake -B build
mkdir -p data

cd data
mkdir -p processed
mkdir -p queries
mkdir -p raw
mkdir -p results
cd ..

mkdir -p log
