#!/bin/bash
  
#get all the rules without the comments
#echo -e $(cat /dev/stdin)
packets=$(cat /dev/stdin)

#Go over each rule argument and add all packets that follow it to oout.
while read line; do
    one_rule=$(echo $line | grep -o '^[^#]*')
	
	#Get the four parts of the rule.
    if ([ ! -z "$one_rule" ]) then
        rule_one=$(echo $one_rule|awk -F, '{print $1}')
        rule_two=$(echo $one_rule|awk -F, '{print $2}')
        rule_three=$(echo $one_rule|awk -F, '{print $3}')
        rule_four=$(echo $one_rule|awk -F, '{print $4}')

		#Add packets that follow this rule to oout.
		oout+=$(echo $packets | sed 's/src-ip/\n&/g'| sort |
		uniq  | ./firewall.exe $rule_one |
		./firewall.exe $rule_two | ./firewall.exe $rule_three |
		./firewall.exe $rule_four)
		fi
done <$1

#Print all unique packets that passed the firewall in a sorted order.
echo $oout | sed 's/src-ip/\n&/g'| sort |sed '/^[[:space:]]*$/d'|
uniq| sed 's/ //g'
