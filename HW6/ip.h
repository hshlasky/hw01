#ifndef IP_H
#define IP_H

#include "string.h"
#include <stddef.h>
#include <iostream>
#include "generic-field.h"
#define IP_NUM_BYTES 4

class Ip: public GenericField {
	char mask;
	char addressByte [IP_NUM_BYTES]={0};
	bool is_src = false;
public:
	/**
     * @brief Initiates an empty Ip
     */
	Ip();
	
	/**
     * @brief Initiates an Ip of type src/dst
     */
	Ip(bool src);
	
	/**
     * @brief Initiates Ip from other Ip
     */
	Ip (const Ip &ipC);
	
	/**
     * @brief Destroys an Ip.
     */	
	~Ip();
	
	/**
	 * @return unsigned int ip address 
     * @brief creat an ip address from four chars (bytes of ip)
     */
	unsigned int ip_to_int(char a, char b, char c, char d) const;

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
