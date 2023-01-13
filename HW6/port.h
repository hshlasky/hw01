#ifndef PORT_H
#define PORT_H

#include "string.h"
#include <stddef.h>
#include <iostream>
#include "generic-field.h"


class Port: public GenericField {
	unsigned short min_port;
	unsigned short max_port;
	bool is_src = false;
public:
	/**
     * @brief Initiates an empty Port
     */
	Port();
	
	/**
     * @brief Initiates an Port of type src/dst
     */
	Port(bool src);
	
	/**
     * @brief Initiates Port from other Port
     */
	Port (const Port &portC);
	
	/**
     * @brief Destroys a Port.
     */	
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
	bool match(String packet);

};
#endif
