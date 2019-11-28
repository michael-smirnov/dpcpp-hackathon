# Intel(R) Hackathon as part of ITMM Day
![](images/oneAPI-logo.png)

## Repository
This repository contains an example of possible solution for the final task of the Intel(R) Haskaton 2019 in Nizhny Novgorod.

Files in the repository:
- data.txt - public set of data for final task
- example.cpp - simple sequential solution based on exaustive search (written on C++)
- launch.sh - script for building & launching solution
- run.py - an implementation of a script, which will be used for rating of the participants

## Task description
The program receives the following input:

1. The number of points to be received, *N*
2. *2\*N* floating point numbers: *x1*, *y1*, *x2*, *y2*, ..., *xN*, *yN*; where each pair represent a 2D Point *p0*, *p1*, ... , *pN*

Participant should write a program, which finds the shortest way from *p0* to *p1* through all other points. Each point must participate in the path only once. Distance between points is considered as Euclidean.

Participants should send their paths to *stdout*. Each path must contain the indices of the points, except first and last one. Point indices must be separated by comma. For example, if *N=4*:
2, 3
3, 2

where first line represents the path p0-p2-p3-p1, and the second is p0-p3-p2-p1

## Conditions of the competition
Execution time of a program is limited by 60 seconds and the program will be killed after this time.

The scoring script analyses last three lines sent to *stdout* starting from the last and accepts the first appropriate solution

The participant who finds the shortest path wins
