#include <stdio.h>
#include "char_utils.h"

#define ALFABETH_SIZE 26

int is_valid_char(char character){
	return ((character >= 'a') && (character <= 'z')) || ((character >= 'A') && (character <= 'Z'));
}


char char_to_lower(char character){ 
	if((character >= 'A') && (character <= 'Z'))
		return character - 'A' + 'a';

	return character;
}

char char_to_upper(char character){ 
	if((character >= 'a') && (character <= 'z'))
		return character + 'A' - 'a';

	return character;
}

char int_to_char(int num_to_convert){
	if((num_to_convert >= 0) && (num_to_convert < ALFABETH_SIZE))
		return num_to_convert + 'a';
	return 'A';
}

int char_to_num(char carac){
	if((carac >= 'a') && (carac <= 'z'))
		return carac - 'a';
	return '0';
}
