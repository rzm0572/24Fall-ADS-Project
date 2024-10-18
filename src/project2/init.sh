#!/bin/bash

cmake -B build
mkdir data

cd data
mkdir processed
mkdir queries
mkdir raw
mkdir results
cd ..

mkdir log
