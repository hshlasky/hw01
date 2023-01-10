#include <cstring>
#include <cstdlib>
#include <iostream>
#include "string.h"
#include "generic-field.h"
#include "port.h"



	/**
     * @brief Initiates an empty Ip
     */
	Port::Port() {	
		this->min_port=0;
		this->max_port=0;
	}
	
	/**
     * @brief Initiates Port from other Ip
     */
	Port :: Port (const Port &portC){
		this->min_port=portC.min_port;
		this->max_port=portC.max_port;
	}
	
	//???
	~Port(){}
	

	/**
	 * @return true if succeeded
     * @brief set value to mask according to the rules
     */
	bool Port :: set_value(String value){
		String* splitted_val;
		size_t val_parts;
		value.split("-", &splitted_val, &val_parts) ;
		
		if (val_parts != 2) {
			return false;
		}		
		this->min_port=(short)splitted_val[0];
		this->max_port=(short)splitted_val[1];
		return true;
	}

	
	/**
	 * @return true if packet follows the rules
     * @brief check if packet follows the rules
     */
	bool Port :: match(String packet) const{
		return ((short)packet>=this->min_port)&&
				((short)packet<=this->max_port);
	}
	
	
