#!/usr/bin/env bash

echo $1
cookie=$(cat cookie.txt)
mkdir -p $1/day_$2
curl -b session=$cookie "https://adventofcode.com/$1/day/$2/input" > $1/day_$2/input.txt
