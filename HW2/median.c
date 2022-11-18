#!/bin/bash

# Get data from stdin
data=$(cat -)

# How many students?
n=$(echo "$data" | wc -l)

# Start "hist" with 100 buckets
hist=$(echo "$data" | ./hist.exe -nbins 100)

# Desierd median index:
(( m=(n+1)/2 ))

# Go over all lines in "hist", count until reaching "m"
counter=0
while read line; do
	arr=($line)
	(( counter=$counter+${arr[1]} ))
	if (( $counter>=$m )); then
		echo -n "Median "
		echo $line | cut -d"-" -f1
		exit 0
	fi
done < <(echo "$hist")
