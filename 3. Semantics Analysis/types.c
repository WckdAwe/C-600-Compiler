/* ---------------------------------------------------------------------
   ---------------------------- Header files ---------------------------
   --------------------------------------------------------------------- */

#include "types.h"
#include "error.h"
#include <stdio.h>

char* reverse_type_kind[] = {
	"UNKNOWN", "INT", "FLOAT", "CHAR", "STR", "VOID", 
	"ARRAY", "ENUM", "UNION", "LIST", "CLASS", "FUNC", "ID",     
};

/* ---------------------------------------------------------------------
   --------------------- Υλοποίηση συναρτήσεων -------------------------
   --------------------------------------------------------------------- */


Type type_basic (int kind_id)
{
   	Type result = new(sizeof(struct Type_tag));
	switch(kind_id){
		case TYPE_int:
		case TYPE_float:
		case TYPE_char:
		case TYPE_str:
		case TYPE_void:
		case TYPE_enum: // TODO: Verify this?
		case TYPE_union:
		case TYPE_class: // TODO: and this
		case TYPE_list:
			result->kind = kind_id;
			break;
		default:
			ASSERT(result->kind == TYPE_unknown);
			result->kind = TYPE_unknown;
	};
   	return result;
}

Type type_id (Identifier id)
{
   	Type result = new(sizeof(struct Type_tag));

   	result->kind = TYPE_id;
   	result->u.t_id.id = id;
   	return result;
}

Type type_array (int dim, Type type)
{
   	Type result = new(sizeof(struct Type_tag));

   	result->kind = TYPE_array;
   	result->u.t_array.dim = dim;
   	result->u.t_array.type = type;
   	return result;
}

// Type type_ref (Type type)
// {
//    Type result = new(sizeof(struct Type_tag));

//    result->kind = TYPE_ref;
//    result->u.t_ref.type = type;
//    return result;
// }

Type type_func (Type type1, Type type2)
{
   	Type result = new(sizeof(struct Type_tag));

   	result->kind = TYPE_func;
   	result->u.t_func.type1 = type1;
  	result->u.t_func.type2 = type2;
  	return result;
}

TypeList type_list_add(TypeList list, Type type){
    TypeList node = new(sizeof(struct TypeList_tag));
    node->type = type;
    node->next = NULL;

    if(list == NULL)
        return node;
    
    TypeList tmp = list;
	while(tmp->next != NULL){
		tmp = tmp->next;
	}
    tmp->next = node;
	
	return list;
}

// #include<string.h>
// #include<stdio.h>
// #include<stdlib.h>

// #include "c600.h"
// #include "types.h"

// char *reverse_types[] = {
//     "NOTHING", "INT", "FLOAT", "CHAR", "STR", "VOID", 
//     "ARRAY", "ENUM", "UNION", "LIST", "CLASS", "FUNC"
// };

// Type_Struct *ts_create_standard_type(Type type){
	
// 	Type_Struct *result;
	
// 	if(!(result=malloc(sizeof(Type_Struct)))) exit(-1);
	
// 	result->type = type;
	
// 	switch (result->type){
// 		case INT: 
// 			result->size = INT_SIZE;
// 			break;
// 		case CHAR:
// 			result->size = CHAR_SIZE;
// 			break;
// 		case FLOAT:
// 			result->size = FLOAT_SIZE;
// 			break;
// 		default:
//             result->size = 0; // VOID: Does it have size? | STRING: Possibly allocate it later!
// 			break;
// 	}
	
// 	return result;
// }


// List *list_create_node(char *name){
// 	List *result = new(sizeof(List));

// 	result->key = name;
// 	result->value = -1;
// 	result->next = NULL;
	
// 	return result;
// }

// List *list_add_node(List *rl, List *node){
// 	List *curr;
	
// 	curr = rl;
// 	while(curr->next != NULL){
// 		curr = curr->next;
// 	}
// 	curr->next = node;
	
// 	return rl;
// }


// List *list_addType(List *rl, Type_Struct *ts){
// 	List *curr;
// 	Type_Struct *temp;
	
// 	curr = rl;
// 	while(curr != NULL){
// 		temp = new(sizeof(Type_Struct));
// 		*temp = *ts;
// 		curr->field = temp;
		
// 		curr = curr->next;
// 	}

// 	free(ts);
// 	return rl;
// }