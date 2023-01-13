#include <cstring>
#include <cstdlib>
#include <iostream>
#include "string.h"
#include "generic-field.h"
#include "port.h"



	/**
     * @brief Initiates an empty Ip
     */
	Port :: Port() {	
		this->min_port=0;
		this->max_port=0;
	}
	
	/**
     * @brief Initiates an Port of type src/dst
     */
	Port :: Port(bool src) {
		this->min_port=0;
		this->max_port=0;
		this->is_src=src;
	}
	
	/**
     * @brief Initiates Port from other Ip
     */
	Port :: Port (const Port &portC){
		this->min_port=portC.min_port;
		this->max_port=portC.max_port;
		this->is_src=portC.is_src;
	}

	/**
     * @brief Destroys a Port.
     */	
	Port :: ~Port(){}
	

	/**
	 * @return true if succeeded
     * @brief set value to min_port and max_port according to the rules
     */
	bool Port :: set_value(String value){
		String* splitted_val;
		size_t val_parts;
		
		//Split String value according to dellimeter '-' to get max and min.
		value.split("-", &splitted_val, &val_parts);
		
		//Check if the input is valid ("MIN-MAX")
		if (val_parts != 2) {
			delete[] splitted_val;
			return false;
		}

		//First field is min, second is max.
		this->min_port=(unsigned short)(splitted_val[0].to_integer());
		this->max_port=(unsigned short)(splitted_val[1].to_integer());
		
		delete[] splitted_val;
		return true;
	}

	
	/**
	 * @return true if packet follows the rules
     * @brief check if packet follows the rules
     */
	bool Port :: match(String packet){
		String* splitted_val;
		size_t val_parts;
		
		//Split packet into fields ("src/dst-port/ip" or numbers)
		packet.split("=,", &splitted_val, &val_parts);
		
		//Check if packet is empty
		if (val_parts == 0) {
			delete[] splitted_val;
			return true;
		}	
		
		bool out_b = false;
		
		
		//Go over splitted String and check find the relevant field.
		//Then check if it follows the given rule.
		for (size_t i=0;i<val_parts;i++) {
			
			//If the relevant field is "src-port"
			if(is_src){
				if (splitted_val[i].equals("src-port")) {
					out_b=(((unsigned short)(splitted_val[i+1].to_integer()))
						>= this->min_port)&&
					(((unsigned short)(splitted_val[i+1].to_integer()))
						<= this->max_port);
					break;
				}
			}
			
			//If the relevant field is "dst-port"
			else if (splitted_val[i].equals("dst-port")) {
				out_b=(((unsigned short)(splitted_val[i+1].to_integer()))
					>= this->min_port)&&
				(((unsigned short)(splitted_val[i+1].to_integer()))
					<= this->max_port);
				break;
			}
		}
				
		delete[] splitted_val;

		return out_b; 
	}
		
