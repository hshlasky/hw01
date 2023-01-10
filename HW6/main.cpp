#include <stddef.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "generic-field.h"
#include "input.h"
#include "string.h"
#include "ip.h"
#include "port.h"

int main (int argc, char** argv) {

	//check the arguments
	if(check_args(argc, argv)){
		return 1;
	}
	
	Generic-field* one_rule;
	
	//get the rule part one - type. part 2 - rule
	String rule(argv[1]);
	String *splitted_rule;
    size_t output_parts;
    rule.split("=", &splitted_rule, &output_parts);
	
	//clean spaces from beginning and ending
	splitted_rule[0]=splitted_rule[0].trim();
	splitted_rule[1]=splitted_rule[1].trim();
	
	if(splitted_rule[0].equals("src-port")||
		splitted_rule[0].equals("dst-port")){
		one_rule = new Port();
		if(!one_rule.set_value(splitted_rule[1])){
			return 1;
		}
	}
	
	if(splitted_rule[0].equals("src-ip")||
		splitted_rule[0].equals("dst-ip")){
		one_rule = new Ip();
		if(!one_rule.set_value(splitted_rule[1])){
			return 1;
		}		
	}
	
	
	
}
