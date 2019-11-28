#!/bin/bash

mkdir -p builds
dpcpp -std=c++17 -O2 $1 -o builds/$1.exe
echo Build Passed
python run.py data.txt builds/$1.exe 60
