#include <stddef.h>
#include <iostream>
#include <cstring>
#include "string.h"



    /**
     * @brief Initiates an empty string
     */
    String::String(){
		this->data = new char[0];
		this->length=0;
	}

    /**
     * @brief Initiates string from other string
     */
    String::String(const String &str) {
		
		//Copy string data
		this->data = new char[(str.length)+1];		
		strcpy(this->data,str.data);
		
		//Copy string length
		this->length=str.length;
	}

    /**
     * @brief Initiates a string from char array
     */
     String::String(const char *str) {
			
		//Copy Chars data
		this->data = new char[(strlen(str))+1]; //???faster
		strcpy(this->data,str);
	
		//Copy string length
		this->length=strlen(str);
	}


     String::~String(){
		delete[] this->data;
	}

    /**
     * @brief Changes this from String
     */
    String& String:: operator=(const String &rhs) {
		
		//check if the argument is the current object
		if(&rhs==this) {
			return *this;
		}
		delete[] this->data;
		
		//Copy string data
		this->data = new char[(rhs.length)+1];		
		strcpy(this->data,rhs.data);
		
		//Copy string length
		this->length=rhs.length;
		return *this;	
	}

    /**
     * @brief Changes this from char array
     */
     String& String:: operator=(const char *str){
		delete this;
		*this = String (str);
		return *this;	
	}

    /**
     * @brief Returns true if the contents of this equals to the
     * contents of rhs
     */
    bool String:: equals(const String &rhs) const {
		if(rhs.length!=this->length){
			return false;
		}
		
		return (!strcmp(this->data, rhs.data));
	}

    /**
     * @brief Returns true iff the contents of this equals to rhs
     */
    bool String:: equals(const char *rhs) const{
		if(strlen(rhs)!=this->length){
			return false;
		}
		
		return (!strcmp(this->data, rhs));
	}

    /**
     * @brief Splits this to several sub-strings according to delimiters.
     * Allocates memory for output that the user must delete (using delete[]).
     * @note Does not affect this.
     * @note If "output" is set to NULL, do not allocated memory, only
     * compute "size".
     */
    void String:: split(const char *delimiters, String **output, size_t *size) const{
		
		//count the number of tokens in data
		int counter=0;
		
		/* "On a first call, the function expects a C string as argument for
		str, whose first character is used as the starting location to scan
		for tokens. In subsequent calls, the function expects a null pointer
		and uses the position right after the end of the last token as the
		new starting location for scanning." (cplusplus.com)*/
		char* tok = strtok(this->data,delimiters);
		while (tok) {
			counter++;
			tok = strtok(NULL,delimiters);
		}
		*size = counter;
		
		//check if output is set to NULL
		if(!output){
			  return;
		}
		
		//build string array of tokens
		*output = new String [*size];
		tok = strtok(this->data,delimiters);
		for (int i=0;i<*size;i++) {
			*output[i] = tok;
			tok = strtok(NULL,delimiters);
		}
								
	}
	

    /**
     * @brief Try to convert this to an integer. We can assume that the input
     * is valid.
     */
    int String:: to_integer() const {
		return atoi(this->data);
	}

    /**
     * @brief Remove any leading or trailing white-spaces.
     * Does not change this.
     */
    String String:: trim() const {
		int first_char = -1;
		int last_char = (this->length);
		
		for (int i=0;i<this->length;i++){
			if (first_char==-1 && this->data[i] != ' '){
				first_char = i;
			}
			
			if (last_char==this->length &&
					this->data[(this->length)-(i+1)] != ' '){
				last_char = (this->length)-(i+1);
			}
			
			if (last_char != this->length && first_char != -1){
				break;
			}
		}
		
		if (first_char == -1){
			return NULL;
		}
		
		char tmp [(last_char-first_char)+2];
		strncpy(tmp, (this->data) + first_char, (last_char-first_char)+1);
		tmp[(last_char-first_char)+1]='\0';
		
		return String(tmp);
		
	}

}