#!/bin/bash

# Generate an input file suitable for Project 1.
# Usage:
#    ./generate_sort.sh alg_name problem_size > file_name
#
# Example:
#  ./generate_sort.sh selection 1000 > test.in
#
# Don't forget to make this file executable before running it:
#    chmod u+x ./generate_sort.sh
#

echo $1
for i in `seq 1 $2`;
do
  let "number=$RANDOM + 1"
  echo $number
done  
echo 0

