#!/bin/bash

#get all the rules without the comments
grep -o '^[^#]*' $1 > out

while read rule; do
	rule_one=$rule|awk -F, '{print $1}'
	rule_two=$rule|awk -F, '{print $2}'
	rule_three=$rule|awk -F, '{print $3}'
	rule_four=$rule|awk -F, '{print $4}'
	echo $rule_one
	echo $rule_two
	echo $rule_three
	echo $rule_four
done <out
