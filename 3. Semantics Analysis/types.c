#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#include "c600.h"
#include "types.h"


Type_Struct *ts_create_standard_type(Type type){
	
	Type_Struct *result;
	
	if(!(result=malloc(sizeof(Type_Struct)))) exit(-1);
	
	result->type = type;
	
	switch (result->type){
		case INTEGER: 
			result->size = INT_SIZE;
			break;
		case CHARACTER:
			result->size = CHAR_SIZE;
			break;
		case FLOAT:
			result->size = FLOAT_SIZE;
			break;
		default:
            result->size = 0; // VOID: Does it have size? | STRING: Possibly allocate it later!
			break;
	}
	
	return result;
}