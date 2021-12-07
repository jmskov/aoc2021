#!/bin/bash

day=$1
prev=$(( $1-1 ))
# Create new files for specific day
cp include/solutions/aoc_day_$prev.h include/solutions/aoc_day_$day.h
cp src/solutions/aoc_day_$prev.cpp src/solutions/aoc_day_$day.cpp

# TODO: Modify the new files
# TODO: Modify aoc_days.cpp
# TODO: Modify the Makefile
