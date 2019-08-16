/* ---------------------------------------------------------------------
   ---------------------------- Header files ---------------------------
   --------------------------------------------------------------------- */

#include "types.h"
#include "error.h"
#include <stdio.h>

char* reverse_type_kind[] = {
	"UNKNOWN", "INT", "FLOAT", "CHAR", "STR", "VOID", 
	"ARRAY", "ENUM", "UNION", "LIST", "CLASS", "FUNC", "ID", "REF"    
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
		//case TYPE_list:
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

Type type_ref (Type type)
{
   Type result = new(sizeof(struct Type_tag));

   result->kind = TYPE_ref;
   result->u.t_ref.type = (type ? type : type_basic(TYPE_unknown));
   return result;
}

Type type_array (int dim, Type type)
{
   	Type result = new(sizeof(struct Type_tag));

   	result->kind = TYPE_array;
   	result->u.t_array.dim = dim;
   	result->u.t_array.type = (type ? type : type_basic(TYPE_unknown));
   	return result;
}

Type type_list (Type type)
{
   Type result = new(sizeof(struct Type_tag));

   result->kind = TYPE_list;
   result->u.t_list.type = (type ? type : type_basic(TYPE_unknown));
   return result;
}

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