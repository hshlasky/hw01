#!/bin/bash

#get course number and check if it is valid.
read args
if ([[ ${#args} -ne 6 ]]); then
	echo "Wrong number of arguments" >&2
	exit 1
fi

if (test ! -f $args.txt); then
       	echo "Course not found" >&2
	exit 1
fi

#create a directory "(course num)_stat" (delete the previous one, if exists)
[ -d ""$args"_stat" ] && rm -r ""$args"_stat"
mkdir ""$args"_stat"

#compile all coding files
gcc -g -Wall hist.c -o hist.exe
gcc -g -Wall min.c -o min.exe
gcc -g -Wall max.c -o max.exe
gcc -g -Wall mean.c -o mean.exe
gcc -g -Wall median.c -o median.exe

#output the course's histogram (using 10 bins) to "histogram.txt".
./hist.exe $args.txt > "$args"_stat/histogram.txt

#run the codes and calculate all course's stats.
min=$(./min.exe $args.txt)
max=$(./max.exe $args.txt)
mean=$(./mean.exe $args.txt)
median=$(./median.exe $args.txt)

#output stats to the file "statistics.txt"
echo -e "$mean\t$median\t$min\t$max" > "$args"_stat/statistics.txt

#calculate the passing percentage using hist.exe with 100 bins.
hist=$(./hist.exe $args.txt -n_bins 100)
students=$(wc -l < $args.txt)
passed=0
grade=0

#count the number of students which passed the course.
while read line; do
	arr=($line)
	[[ $grade -gt 54 ]] && (( passed=$passed+${arr[1]} ))
	(( grade=$grade+1 ))
done < <(echo "$hist")

#append percentage to "statistics.txt".
(( pass_percent=100*$passed/$students ))
echo "$pass_percent" >> "$args"_stat/statistics.txt
