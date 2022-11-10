#!/bin/bash

site="https://ynetnews.com/category/3082"

data=$(wget --no-check-certificate -O - $site 2>/dev/null)

articles=$(echo "$data" | \
	grep -oP "https://(www.)?ynetnews.com/article/[0-9a-zA-Z]+" |\
	sort -u)
(echo "$(echo "$articles" | wc -l)"


for article in $articles; do
	art=$(wget --no-check-certificate -O - $article 2>/dev/null)
	BB_freq=$(echo "$art" | grep -oP "Netanyahu" | wc -w)
	GZ_freq=$(echo "$art" | grep -oP "Gantz" | wc -w)
	LD_freq=$(echo "$art" | grep -oP "Lapid" | wc -w)
	BG_freq=$(echo "$art" | grep -oP "Ben-Gvir" | wc -w)

	if [[ $BB_freq+$GZ_freq+$LD_freq+$BG_freq -eq 0  ]] ; then 
		echo "$article, -"
	else
		echo "$article, Netanyahu, $BB_freq, Gantz,\
$GZ_freq, Lapid, $LD_freq, Ben-gvir, $BG_freq" 
	fi
done) > results.csv



