#include <cstring>
#include <cstdlib>
#include <iostream>
#include "string.h"
#include "generic-field.h"
#include "ip.h"
#define IP_NUM_BYTES 4



	/**
     * @brief Initiates an empty Ip
     */
	Ip::Ip() {	
		this->mask=0;
	}
	
	/**
     * @brief Initiates Ip from other Ip
     */
	Ip :: Ip (const Ip &ipC){
		for(int i=0;i<IP_NUM_BYTES;i++){
			this->addressByte[i]=ipC.addressByte[i];
		}
		this->mask=ipC.mask;
	}
	
	//???
	~Ip(){}
	
	/**
	 * @return unsigned int ip address 
     * @brief creat an ip address from four chars (bytes of ip)
     */
	unsigned int Ip :: ip_to_int(char a, char b, char c, char d) const{
		unsigned int out=0;
		out=((int)a<<24)|((int)b<<16)|((int)c<<8)|((int)d);
		return out;
	}

	/**
	 * @return true if succeeded
     * @brief set value to mask according to the rules
     */
	bool Ip :: set_value(String value){
		String* splitted_val;
		size_t val_parts;
		value.split("./", &splitted_val, &val_parts) ;
		
		if (val_parts != IP_NUM_BYTES+1) {
			return false;
		}	
		
		for(int i=0;i<IP_NUM_BYTES;i++){
			this->addressByte[i]=splitted_val[i];
		}
		this->mask = splitted_val[IP_NUM_BYTES+1];
		return true;
	}

	/**
	 * @return the mask at 32'b
     * @brief convert the mask to 32'b
     */
	private: unsigned int get_mask(char m) const{
		unsigned int out = 0;
		out=-1;
		out << (32-(int)m);
		return out;
	}
	
	/**
	 * @return true if packet follows the rules
     * @brief check if packet follows the rules
     */
	bool Ip :: match(String packet) const{
		//convert the mask to 32'b
		unsigned int use_mask = get_mask(this->mask);
		//convert the rule ip to 32'b
		unsigned int rule_ip = ip_to_int(this->addressByte[0],
										this->addressByte[1],
										this->addressByte[2],
										this->addressByte[3]);
		String* splitted_pac;
		size_t pac_parts;
		packet.split(".", &splitted_pac, &pac_parts);
		
		//convert the packet ip to 32'b
		unsigned int packet_ip = ip_to_int(splitted_pac[0],
										splitted_pac[1],
										splitted_pac[2],
										splitted_pac[3]);
		
		//check the rule		
		return (rule_ip&use_mask)==(packet_ip&use_mask);
	}
	
	
