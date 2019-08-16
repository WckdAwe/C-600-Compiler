#include "error.h"
#include "ast.h" 

extern int lineno;

/* ---------------------------------------------------------------------
   --------------------- Υλοποίηση συναρτήσεων -------------------------
   --------------------------------------------------------------------- */

AST_parameter ast_parameter(Type typename, AST_passvar passvar){
    AST_parameter result = new(sizeof(*result));
    result->typename = typename;
    result->passvar = passvar;
    result->lineno = lineno;
    return result;    
}

AST_passvar ast_passvar_variable(AST_variabledef variable){
    AST_passvar result = new(sizeof(*result));
    result->kind = PASSVAR_variable;
    result->u.variabledef = variable;
    result->lineno = lineno;
    return result;
}

AST_passvar ast_passvar_ref(Identifier id){
    AST_passvar result = new(sizeof(*result));
    result->kind = PASSVAR_ref;
    result->u.ref = type_ref(type_id(id));
    result->lineno = lineno;
    return result;
}

AST_typedef ast_typedef(Identifier id, Type typename, Type list, Type array){
    AST_typedef result = new(sizeof(*result));
    result->id = id;
    result->typename = set_list_or_array_or_typename(list, array, typename);
    result->lineno = lineno;
    return result;
}

AST_class_func_header_start ast_class_func_header_start(Identifier id, Identifier class, Type typename, Type list){
    AST_class_func_header_start result = new(sizeof(*result));
    result->id = id;
    result->class = class;
    result->typename = set_list_or_typename(list, typename);
    result->lineno = lineno;
    return result;
}

AST_func_header_start ast_func_header_start(Identifier id, Type typename, Type list){
    AST_func_header_start result = new(sizeof(*result));
    result->id = id;
    result->typename = set_list_or_typename(list, typename);
    result->lineno = lineno;
    return result;
}

AST_variabledef ast_variabledef(Identifier id, Type list, Type array){
    ASSERT(!(list && array)); // Can't be list & array at the same time!
    AST_variabledef result = new(sizeof(*result));
    result->id = id;
    result->type = list ? list : array; // Can return null if both list & array == NULL;
    result->lineno = lineno;
    return result;
}

Type ast_dims(Type outer_array, Type inner_array){ //  Good for semantic... Maybe need different for ast?
    if(outer_array){
        outer_array->u.t_array.type = inner_array;
        return outer_array;
    }else{
        return inner_array;
    }
}

AST_casestatement ast_casestatement(AST_constant constant){
    AST_casestatement result = new(sizeof(*result));
    result->constant = constant;
    result->lineno = lineno;
    return result;
}

AST_constant ast_constant_iconst(int r) {
    AST_constant result = new(sizeof(*result));
    result->kind = CONSTANT_iconst;
    result->u.c_iconst.rep = r;
    result->lineno = lineno;
    return result;
}

AST_constant ast_constant_fconst(float r) {
    AST_constant result = new(sizeof(*result));
    result->kind = CONSTANT_fconst;
    result->u.c_fconst.rep = r;
    result->lineno = lineno;
    return result;
}

AST_constant ast_constant_cconst(char r) {
    AST_constant result = new(sizeof(*result));
    result->kind = CONSTANT_cconst;
    result->u.c_cconst.rep = r;
    result->lineno = lineno;
    return result;
}

AST_constant ast_constant_sconst(char* r) {
    AST_constant result = new(sizeof(*result));
    result->kind = CONSTANT_sconst;
    result->u.c_sconst.rep = r;
    result->lineno = lineno;
    return result;
}





List list_add(List list, void *data){
    List node = new(sizeof(struct List_tag));
    node->data = data;
    node->next = NULL;

    if(list == NULL)
        return node;
    
    List tmp = list;
	while(tmp->next != NULL){
		tmp = tmp->next;
	}
    tmp->next = node;
	
	return list;
}

void list_reverse(List *head){
    List prev = NULL;
    List current = *head;
    List next = NULL;

    while(current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

Type set_list_or_typename(Type list, Type typename){
    if(list){
        ASSERT(list->kind == TYPE_list);
        list->u.t_list.type = typename;
        return list;
    }else{
        return typename;
    }
}

Type set_list_or_array_or_typename(Type list, Type array, Type typename){
    ASSERT(!(list && array)); // Can't be both a list and array!
    if(list){
        ASSERT(list->kind == TYPE_list);
        list->u.t_list.type = typename;
        return list;
    }else if(array){
        set_array_type(array, typename);
        return array;
    }else{
        return typename;
    }
}

void set_array_type(Type array, Type type){
    ASSERT(array && type);
    ASSERT(array->kind == TYPE_array);
    Type tmp = array;
    while(tmp->u.t_array.type->kind == TYPE_array)
        tmp = tmp->u.t_array.type;
    tmp->u.t_array.type = type;
}

// AST_Node *create_ast_node(Operation op, Type type, AST_Node *left, AST_Node *right){
// 	AST_Node *ast_node = emalloc(sizeof(AST_Node));
	
// 	ast_node->op = op;
// 	ast_node->type = type;
	
// 	ast_node->left = left;
// 	ast_node->right = right;

// 	return ast_node;
// }


// AST_Node *create_ast_if_node(AST_Node *condition, AST_Node *if_branch, AST_Node *else_branch){
	
// 	AST_IF_Node *ast_node = emalloc(sizeof(AST_IF_Node));

// 	ast_node->op = IF;

// 	ast_node->condition = condition;
// 	ast_node->if_branch = if_branch;
// 	ast_node->else_brach = else_branch;
  
// 	return (AST_Node *) ast_node;
// }

// AST_Node *create_ast_while_node(AST_Node *condition, AST_Node *while_branch){
	
// 	AST_WHILE_Node *ast_node = emalloc(sizeof(AST_WHILE_Node));

// 	ast_node->op = WHILE;

// 	ast_node->condition = condition;
// 	ast_node->while_branch = while_branch;
  
// 	return (AST_Node *) ast_node;
// }


// AST_Node *create_ast_for_node(AST_Node *start_condition, AST_Node *end_condition, int increment, AST_Node *for_branch){
// 	AST_FOR_Node *ast_node = emalloc(sizeof(AST_FOR_Node));

// 	ast_node->op = FOR;

// 	ast_node->start_condition = start_condition;
// 	ast_node->end_condition = end_condition;
// 	ast_node->increment = increment;
// 	ast_node->for_branch = for_branch;

// 	return (AST_Node *) ast_node;
// }

// AST_Node *create_leaf_node(Type_Struct *value, char *name){
// 	struct ast_leaf_node *ast_node = emalloc(sizeof(struct ast_leaf_node));

// 	ast_node->op = LEAF;
// 	ast_node->name = name;

// 	ast_node->value = value;

// 	return (struct ast_node*) ast_node;
// }

// AST_Node *new_ast_enum_leaf_node(Type_Struct *ts_value, char *name, Type_Struct *enumeration){
// 	struct ast_enum_leaf_node *ast_node = emalloc(sizeof(struct ast_enum_leaf_node));

// 	ast_node->op = ENUM;
// 	ast_node->values = ts_value;
// 	ast_node->name = name;
// 	ast_node->enumeration = enumeration;

// 	return (struct AST_Node*) ast_node;
	
// }

// AST_expr ast_expr_call(Identifier id, AST_expr_list l) {
//     AST_expr result = new(sizeof(*result));
//     result->kind = EXPR_call;
//     result->u.e_call.id = id;
//     result->u.e_call.list = l;
//     result->lineno = lineno;
//     return result;
// }

// AST_expr ast_expr_Call(Identifier id, AST_expr_list l) {
//     AST_expr result = new(sizeof(*result));
//     result->kind = EXPR_Call;
//     result->u.e_Call.id = id;
//     result->u.e_Call.list = l;
//     result->lineno = lineno;
//     return result;
// }

// AST_DECL_Node* new_single_decl_node(Type variable_type, char* id)
// {   	AST_DECL_Node* new_node;
//    	new_node = (AST_DECL_Node*)malloc(sizeof(AST_DECL_Node));
	
//     	new_node->variable_type=variable_type;
//     	new_node->id=id;
//     	new_node->dim=0;
// 		//initial value? there could be none.	
//     	return new_node;
// }

// AST_Node* new_exp_node(Operation op_type , AST_Node* left_exp , AST_Node* right_exp) 
// //exp 'OP' exp : (op,exp,exp)
// {
//     	AST_Node* new_node ; 
//     	new_node = (AST_Node*)malloc(sizeof(AST_Node)); 

//     	new_node->left=left_exp;
//     	new_node->right=right_exp;
//     	new_node->op_type=op_type;

//     	return new_node;
// } 

// AST_Node* new_asgn_node(AST_Node* variable,AST_Node* value)
// {
// 	AST_ASGN_Node = new_node;
// 	new_node = (AST_ASGN_Node*)malloc(sizeof(ASGN_Node));

// 	new_node->op_type=ASSIGN;
// 	new_node->left=variable;
// 	new_node->right=value; //or expression

// 	return new_node;
	
// }

// AST_Node* new_condition_node(Operation op_type,AST_Node* expr1,AST_Node* expr2)
// {
// 	AST_Node* new_node;
// 	new_node = (AST_Node*)malloc(sizeof(AST_Node));
	
// 	new_node->left = expr1;
// 	new_node->right = expr2;
// 	new_node->op_type = op_type; //EQUOP , OROP ,ANDOP , RELOP
	
// 	return new_node;	
// }

// //const data nodes
// AST_Node* new_iconst_node(int data)
// {
// 	AST_Node *new_node;
// 	new_node = (AST_Node*)malloc(sizeof(AST_Node));
	
// 	new_node->op_type=LEAF;
// 	new_node->node_data->intdata=data;
// 	new_node->left=NULL;
// 	new_node->right=NULL;

// 	return new_node;
// }

// AST_Node* new_fconst_data(float data)
// {
// 	AST_Node *new_node;
// 	new_node = (AST_Node*)malloc(sizeof(AST_Node));
	
// 	new_node->op_type=LEAF;
// 	new_node->node_data->float=data;
// 	new_node->left=NULL;
// 	new_node->right=NULL;

// 	return new_node;

// }
// AST_Node* new_cconst_node(char data)
// {
// 	AST_Node *new_node;
// 	new_node = (AST_Node*)malloc(sizeof(AST_Node));
	
// 	new_node->op_type=LEAF;
// 	new_node->node_data->chardata=data;
// 	new_node->left=NULL;
// 	new_node->right=NULL;

// 	return new_node;

// }

// AST_Node* new_sconst_node(char* data)
// {
// 	AST_Node *new_Node;
// 	new_node = (AST_Node*)malloc(sizeof(AST_Node));
	
// 	new_node->op_type=LEAF;
// 	new_node->node_data->strdata=data;
// 	new_node->left=NULL;
// 	new_node->right=NULL;

// 	return new_node;

// }

// AST_Node *create_function_node(char *name, AST_Node *arguments, AST_Node *statements, Type_Struct *return_type){
// 	Function *ast_node = emalloc(sizeof(Function));

// 	ast_node->op = FUNC;
// 	ast_node->name = name;
// 	ast_node->arguments = arguments;
// 	ast_node->statements = statements;
// 	ast_node->return_type = return_type;

// 	return (struct AST_Node*) ast_node;
// }
