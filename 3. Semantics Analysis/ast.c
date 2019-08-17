#include "error.h"
#include "ast.h" 

extern int lineno;

/* ---------------------------------------------------------------------
   --------------------- Υλοποίηση συναρτήσεων -------------------------
   --------------------------------------------------------------------- */
AST_class_dcl ast_class_dcl(Identifier id, AST_class_body class_body){
    AST_class_dcl result = new(sizeof(*result));
    result->id = id;
    result->class_body = class_body;
    result->lineno = lineno;
    return result;
}

AST_class_body ast_class_body(Identifier parent, List members_methods){
    AST_class_body result = new(sizeof(*result));
    result->parent = parent;
    result->members_methods = members_methods;
    result->lineno = lineno;
    return result;
}

AST_members_method ast_members_method(Access access, AST_member_or_method mom){
    AST_members_method result = new(sizeof(*result));
    result->access = access;
    result->mom = mom;
    result->lineno = lineno;
    return result;
}

AST_member_or_method ast_mom_method(AST_short_func_dcl method){
    AST_member_or_method result = new(sizeof(*result));
    result->kind = MOM_METHOD;
    result->u.method = method;
    result->lineno = lineno;
    return result;
}

AST_member_or_method ast_mom_member(AST_member member){
    AST_member_or_method result = new(sizeof(*result));
    result->kind = MOM_MEMBER;
    result->u.member = member;
    result->lineno = lineno;
    return result;
}

AST_short_func_dcl ast_short_func_dcl(AST_func_header_start func_header_start, List parameters){
    AST_short_func_dcl result = new(sizeof(*result));
    result->kind = parameters ? SHORT_FUNC_WITH_PARAMS : SHORT_FUNC_NO_PARAMS;
    result->func_header_start = func_header_start;
    result->parameters = parameters;
    result->lineno = lineno;
    return result;
}

AST_union_dcl ast_union_dcl(Identifier id, List union_fields){
    AST_union_dcl result = new(sizeof(*result));
    result->id = id;
    result->union_fields = union_fields;
    result->lineno = lineno;
    return result;
}

AST_member ast_member_anon_union(List union_fields){
    AST_member result = new(sizeof(*result));
    result->kind = MEMBER_ANON_UNION;
    result->u.union_fields = union_fields;
    result->lineno = lineno;
    return result;
}

AST_member ast_member_variable(AST_var_declaration var_declaration){
    AST_member result = new(sizeof(*result));
    result->kind = MEMBER_VARIABLE;
    result->u.var_declaration = var_declaration;
    result->lineno = lineno;
    return result;
}

AST_declaration ast_declaration(Type typename, int is_static, List list){
    AST_declaration result = new(sizeof(*result));
    result->typename = typename;
    result->is_static = is_static;
    result->list = list;
    result->lineno = lineno;
    return result;
}

AST_var_declaration ast_var_declaration(Type typename, List list){
    AST_var_declaration result = new(sizeof(*result));
    result->typename = typename;
    result->list = list;
    result->lineno = lineno;
    return result;
}

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

Type get_parameter_type(Type typename, Type pass_list_dims){
    if(!pass_list_dims){ // If not ref or list/array
        return typename;
    }else{
        switch(pass_list_dims->kind){
            case TYPE_ref:
                pass_list_dims->u.t_ref.type = typename;
                break;
            case TYPE_list:
                pass_list_dims->u.t_list.type = typename;
                break;
            case TYPE_array:
                set_array_type(pass_list_dims, typename);
                break;
            default:
                fatal("Unexpected input on get_parameter_type()\n");
                break;
        }
        return pass_list_dims;
    }
}

