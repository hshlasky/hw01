#!/bin/bash

read args
if ([[ ${#args} -ne 6 ]]); then
	echo "Wrong number of arguments" >&2
	exit 1
fi

if (test ! -f $args.txt); then
       	echo "Course not found" >&2
	exit 1
fi

[ -d ""$args"_stat" ] && rm -r ""$args"_stat"
mkdir ""$args"_stat"
