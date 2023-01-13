#include <stddef.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "generic-field.h"
#include "input.h"
#include "string.h"
#include "ip.h"
#include "port.h"

int main(int argc, char *argv[]) {
  

  	//check the arguments
	if(check_args(argc, argv)){
		return 1;
	}
	
	GenericField* one_rule;
	
	//get the rule part one - type. part 2 - rule
	String rule_get=argv[1];
	String *splitted_rule;
    size_t output_parts;


    rule_get.split("=,", &splitted_rule, &output_parts);
	bool is_src;
	//clean spaces from beginning and ending
	splitted_rule[0]=splitted_rule[0].trim();
	splitted_rule[1]=splitted_rule[1].trim();
	
	if(splitted_rule[0].equals("src-port")||
		splitted_rule[0].equals("dst-port")){
		is_src = splitted_rule[0].equals("src-port");
		one_rule = new Port(is_src);
		if(!one_rule->set_value(splitted_rule[1])){
			delete[] splitted_rule;
			delete one_rule;
			return 1;
		}
	}
	
	if(splitted_rule[0].equals("src-ip")||
		splitted_rule[0].equals("dst-ip")){
		is_src = splitted_rule[0].equals("src-ip");
		one_rule = new Ip(is_src);
		
		if(!one_rule->set_value(splitted_rule[1])){
			delete[] splitted_rule;
			delete one_rule;
			return 1;
		}		
	}
	


	parse_input(*one_rule);
	delete one_rule;
	delete[] splitted_rule;
	return 0;
		
}
