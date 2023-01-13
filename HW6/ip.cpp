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
	Ip :: Ip() {	
		this->mask=0;
	}
	
	/**
     * @brief Initiates an Ip of type src/dst
     */
	Ip :: Ip(bool src) {
		this->mask=0;
		this->is_src=src;
	}
	
	/**
     * @brief Initiates Ip from other Ip
     */
	Ip :: Ip (const Ip &ipC){
		for(int i=0;i<IP_NUM_BYTES;i++){
			this->addressByte[i]=ipC.addressByte[i];
		}
		this->mask=ipC.mask;
		this->is_src=ipC.is_src;
	}
	
	/**
     * @brief Destroys an Ip.
     */	
	Ip :: ~Ip(){}

	
	/**
	 * @return unsigned int ip address 
     * @brief creat an ip address from four chars (bytes of ip)
     */
	unsigned int Ip :: ip_to_int(char a, char b, char c, char d) const{
		unsigned int out=0;
		out=(((a&0xFF)<<24)|((b&0xFF)<<16)|((c&0xFF)<<8)|(d&0xFF));
		return out;
	}

	/**
	 * @return true if succeeded
     * @brief set value to mask according to the rules
     */
	bool Ip :: set_value(String value){
		String* splitted_val;
		size_t val_parts;
		
		//Split String value to get Ip chars and mask.
		value.split("./", &splitted_val, &val_parts) ;
		
		//Check if the input is valid ("XXX.XXX.XXX.XXX/XX")
		if (val_parts != IP_NUM_BYTES+1) {
			delete[] splitted_val;
			return false;
		}	
		
		//Set each char in its place.
		for(int i=0;i<IP_NUM_BYTES;i++){
			this->addressByte[i]=((char)(splitted_val[i].to_integer()));
		}
		
		//Set mask according to the last field.
		this->mask = ((char)(splitted_val[IP_NUM_BYTES].to_integer()));
		
		delete[] splitted_val;
		return true;
	}

	/**
	 * @return the mask at 32 bits.
     * @brief convert the mask to 32 bits.
     */
	unsigned int get_mask(char m) {
		unsigned int out = 0;
		out=-1;
		out <<= (32-(int)m);
		return out;
	}
	
	/**
	 * @return true if packet follows the rules
     * @brief check if packet follows the rules
     */
	bool Ip :: match(String packet) {
		
		//If mask is 0, every Ip follows it.
		if(!this->mask){
		 	return true;
		}
		
		//convert the mask to 32 bits
		unsigned int use_mask = get_mask(this->mask);
		
		//convert the rule ip to 32 bits
		unsigned int rule_ip = ip_to_int(this->addressByte[0],
										 this->addressByte[1],
										 this->addressByte[2],
										 this->addressByte[3]);
										 
		String* splitted_pac;
		size_t pac_parts;
		
		//Split packet into fields ("src/dst-port/ip" or numbers)
		packet.split("=.,", &splitted_pac, &pac_parts);
		
		//Check if packet is empty
		if(pac_parts==0){
			delete[] splitted_pac;
			return false;
		}
		
		unsigned int packet_ip =0;
		

		//Go over splitted String and check find the relevant field.
		//Then assign packet ip it's rellevant field.
		for (size_t i=0;i<pac_parts;i++) {
			if(is_src) {
				if (splitted_pac[i].equals("src-ip")) {
					packet_ip =
						ip_to_int((splitted_pac[i+1].to_integer()),
						    	  (splitted_pac[i+2].to_integer()),
								  (splitted_pac[i+3].to_integer()),
								  (splitted_pac[i+4].to_integer()));
					break;
				}
			}
			else if (splitted_pac[i].equals("dst-ip")) {
				packet_ip =
					ip_to_int((splitted_pac[i+1].to_integer()),
					    	  (splitted_pac[i+2].to_integer()),
							  (splitted_pac[i+3].to_integer()),
							  (splitted_pac[i+4].to_integer()));
				break;
			}
		}
		
		
		delete[] splitted_pac;
		
		//check if the packet follows the rule		
		return (rule_ip&use_mask)==(packet_ip&use_mask);
	}
	
	
