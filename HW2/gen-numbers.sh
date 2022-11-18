#!/bin/bash

for (( i=0; i<1000; i++ )); do
	echo $(( $RANDOM % 100 ))
done
