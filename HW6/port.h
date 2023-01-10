#ifndef PORT_H
#define PORT_H

#include "string.h"
#include <stddef.h>
#include <iostream>
#include "generic-field.h"


class Port: public GenericField {
	short min_port;
	short max_port;
public:
	/**
     * @brief Initiates an empty Port
     */
	Port();
	
	/**
     * @brief Initiates Port from other Port
     */
	Port (const Port &portC);
	
	//???
	~Port();
	

	/**
	 * @return true if succeeded
     * @brief set value to mask according to the rules
     */
	bool set_value(String value);

	/**
	 * @return true if packet follows the rules
     * @brief check if packet follows the rules
     */
	bool match(String packet) const;

};
#endif