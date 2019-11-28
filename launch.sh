#!/bin/bash

dpcpp -std=c++17 $1 -o builds/$1.exe
echo Build Passed
python run.py data/data.txt builds/$1.exe 20