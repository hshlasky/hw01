#include <stddef.h>
#include <iostream>
#include <cstring>
#include "string.h"



    /**
     * @brief Initiates an empty string
     */
    String :: String(){
		this->data = new char[0+1];
		this->length=0;
	}

    /**
     * @brief Initiates string from other string
     */
    String :: String(const String &str) {
		
		//Copy string length
		this->length=str.length;
		
		//Copy string data
		this->data = new char[str.length+1];		
		strcpy(this->data,str.data);	
	}

    /**
     * @brief Initiates a string from char array
     */
     String :: String(const char *str) {
		
		//Copy string length
		this->length=strlen(str);		
		//Copy Chars data
		this->data = new char[strlen(str)+1];
		strcpy(this->data,str);
	}

    /**
     * @brief deletes a String and deallocate it's data field
     */
     String::~String(){
		delete[] this->data;
	}

    /**
     * @brief Changes this from String
     */
    String& String :: operator=(const String &rhs) {
		
		//check if the argument is the current object
		if(&rhs==this) {
			return *this;
		}
		delete[] this->data;
		
		//Copy string length
		this->length=rhs.length;
		
		//Copy string data
		this->data = new char[rhs.length+1];		
		strcpy(this->data,rhs.data);
		
		return *this;	
	}

    /**
     * @brief Changes this from char array
     */
     String& String :: operator=(const char *str){
		if (this->data == str){
			return *this;
		}
	   	delete[] this->data;
		
		//Copy string length
		this->length=strlen(str);
		
		//Copy Chars data
		this->data = new char[strlen(str)+1];
		strcpy(this->data,str);

		return *this;	
	}

    /**
     * @brief Returns true if the contents of this equals to the
     * contents of rhs
     */
    bool String :: equals(const String &rhs) const {
			
		return (!strcmp(this->data, rhs.data));
	}

    /**
     * @brief Returns true iff the contents of this equals to rhs
     */
    bool String :: equals(const char *rhs) const{	
		return (!strcmp(this->data, rhs));
	}

    /**
     * @brief Splits this to several sub-strings according to delimiters.
     * Allocates memory for output that the user must delete (using delete[]).
     * @note Does not affect this.
     * @note If "output" is set to NULL, do not allocated memory, only
     * compute "size".
     */
    void String :: split(const char *delimiters, String **output, size_t *size) const{
		
		//count the number of tokens in data
		size_t counter=0;
		
		//Copy Chars data
		char* data_copy1 = new char[this->length+1];
		strcpy(data_copy1,this->data);
		char* data_copy2 = new char[this->length+1];
		strcpy(data_copy2,this->data);	
		
		/* "On a first call, the function expects a C string as argument for
		str, whose first character is used as the starting location to scan
		for tokens. In subsequent calls, the function expects a null pointer
		and uses the position right after the end of the last token as the
		new starting location for scanning." (cplusplus.com)*/
		char* tok = strtok(data_copy1,delimiters);
		while (tok) {
			counter++;
			tok = strtok(NULL,delimiters);
		}
		*size = counter;
		
		//check if output is set to NULL
		if(!output){
			delete data_copy1;
			delete data_copy2;
			return;
		}
		//!!!
		
		//build string array of tokens
		String* out_arr = new String [*size+1];
		
		tok = strtok(data_copy2,delimiters);
		for (size_t i=0;i<*size;i++) {
			out_arr[i] = String(tok).trim();
			tok = strtok(NULL,delimiters);
		}
		
		*output = out_arr;
		
		delete data_copy1;
		delete data_copy2;
								
	}
	

    /**
     * @brief Try to convert this to an integer. We can assume that the input
     * is valid.
     */
    int String :: to_integer() const {
		return atoi(this->data);
	}

    /**
     * @brief Remove any leading or trailing white-spaces.
     * Does not change this.
     */
    String String :: trim() const {
		int first_char = -1;
		size_t last_char = (this->length);
		
		
		for (size_t i=0;i<this->length;i++){
			//find the first char that isn't a whitespace.
			if (first_char==-1 && this->data[i] != ' '){
				first_char = i;
			}
			
			//find the last char that isn't a whitespace.
			if (last_char==this->length &&
					this->data[(this->length)-(i+1)] != ' '){
				last_char = (this->length)-(i+1);
			}
			
			//check if found found both ends.
			if (last_char != this->length && first_char != -1){
				break;
			}
		}
		
		//check if the whole String is whitespaces.
		if (first_char == -1){
			return NULL;
		}
		
		//copy the string without the ends and add '\0'
		char tmp [(last_char-first_char)+2];
		strncpy(tmp, (this->data) + first_char, (last_char-first_char)+1);
		tmp[(last_char-first_char)+1]='\0';
		
		return String(tmp);
		
	}
	
