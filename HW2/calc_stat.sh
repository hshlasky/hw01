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

gcc -g -Wall hist.c -o hist.exe
./hist.exe $args.txt > "$args"_stat/histogram.txt

gcc -g -Wall min.c -o min.exe
gcc -g -Wall max.c -o max.exe
gcc -g -Wall mean.c -o mean.exe
gcc -g -Wall median.c -o median.exe

min=$(./min.exe $args.txt)
max=$(./max.exe $args.txt)
mean=$(./mean.exe $args.txt)
median=$(./median.exe $args.txt)

echo -e "$mean\t$median\t$min\t$max" > statistics.txt

hist=$(./hist.exe $args.txt -n_bins 100)
pass_percent=100 //need to change
echo "$pass_percent" >> statistics.txt
