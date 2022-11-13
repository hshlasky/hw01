#!/bin/bash
#Brief: this code checks the frequencies of the names Netanyahu, Gantz, Lapid and BenGvir in Ynet News articles.

site="https://ynetnews.com/category/3082"

data=$(wget --no-check-certificate -O - $site 2>/dev/null)

#Fetches the different article URLs
articles=$(echo "$data" | \
	grep -oP "https://(www.)?ynetnews.com/article/[0-9a-zA-Z]+" |\
	sort -u)

#Outputs the number of articles we found.
(echo "$(echo "$articles" | wc -l)"

#Counts the number of times each one of the four politicians' names appear in each article.
for article in $articles; do
	art=$(wget --no-check-certificate -O - $article 2>/dev/null)
	BB_freq=$(echo "$art" | grep -oP "Netanyahu" | wc -w)
	GZ_freq=$(echo "$art" | grep -oP "Gantz" | wc -w)
	LD_freq=$(echo "$art" | grep -oP "Lapid" | wc -w)
	BG_freq=$(echo "$art" | grep -oP "Ben-Gvir" | wc -w)
	#if the article doesn't include any name, prints the article's URL and -.
	if [[ $BB_freq+$GZ_freq+$LD_freq+$BG_freq -eq 0  ]] ; then 
		echo "$article, -"
	#Else, prints the articles URL and the frequency of each name.
	else
		echo "$article, Netanyahu, $BB_freq, Gantz,\
$GZ_freq, Lapid, $LD_freq, Ben-gvir, $BG_freq" 
	fi
#Output the result to a file named results.csv.
done) > results.csv



