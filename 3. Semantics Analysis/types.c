#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#include "c600.h"
#include "types.h"

char *reverse_types[] = {
    "NOTHING", "INT", "FLOAT", "CHAR", "STR", "VOID", 
    "ARRAY", "ENUM", "UNION", "LIST", "CLASS", "FUNC"
};

Type_Struct *ts_create_standard_type(Type type){
	
	Type_Struct *result;
	
	if(!(result=malloc(sizeof(Type_Struct)))) exit(-1);
	
	result->type = type;
	
	switch (result->type){
		case INT: 
			result->size = INT_SIZE;
			break;
		case CHAR:
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


List *list_create_node(char *name){
	List *result = emalloc(sizeof(List));

	result->key = name;
	result->value = -1;
	result->next = NULL;
	
	return result;
}

List *list_add_node(List *rl, List *node){
	List *curr;
	
	curr = rl;
	while(curr->next != NULL){
		curr = curr->next;
	}
	curr->next = node;
	
	return rl;
}


List *list_addType(List *rl, Type_Struct *ts){
	List *curr;
	Type_Struct *temp;
	
	curr = rl;
	while(curr != NULL){
		temp = emalloc(sizeof(Type_Struct));
		*temp = *ts;
		curr->field = temp;
		
		curr = curr->next;
	}

	free(ts);
	return rl;
}