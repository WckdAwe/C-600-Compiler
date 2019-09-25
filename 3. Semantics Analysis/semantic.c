#include <string.h>
#include <stdbool.h>
#include "error.h"
#include "ast.h"
#include "semantic.h"
#include "symbol.h"

#define SEMANTIC_ERROR(object, ...) \
    do { \
        lineno = object->lineno; \
        error(__VA_ARGS__); \
    } while(0)

SymbolTable symbol_table;
// SymbolTable type_symbol_table;
// int function_counter; /* Ο μετρητής των διαφορετικών συναρτήσεων που έχουμε βρει */


// void add_function(const char *name, Type parameter_type, Type result_type ) {
//     SymbolEntry entry;

//     entry = symbol_enter(symbol_table, id_make(name), 0);
//     entry->entry_type = ENTRY_FUNCTION;
//     entry->e.function.result_type = result_type;
//     entry->e.function.type = type_func(parameter_type, result_type);
//     entry->e.function.counter = ++function_counter;
// }

bool type_check(Type input, int check, bool can_be_null) {
    if ( input == NULL ) return can_be_null;
    return  input->kind = check;
}

// TODO: Update this
bool type_eq(Type a, Type b) {
    if ( a == NULL || b == NULL ) return true;
    if ( a->kind == TYPE_unknown || b->kind == TYPE_unknown ) return true;
    if ( a->kind != b->kind ) return false;

    switch(a->kind) {
        case TYPE_func: // TODO: Verify
            return type_eq(a->u.t_func.type1, b->u.t_func.type1) &&
                   type_eq(a->u.t_func.type2, b->u.t_func.type2);
        case TYPE_id:
            return strcmp(a->u.t_id.id->name, b->u.t_id.id->name) == 0;
        case TYPE_ref: // TODO: Verify - Maybe return true immediatly?
            return type_eq(a->u.t_ref.type, b->u.t_ref.type);
        case TYPE_array: // TODO: Verify
            return type_eq(a->u.t_array.type, b->u.t_array.type) &&
                   a->u.t_array.dim == b->u.t_array.dim;
        default:
            return true;
    }
}

void AST_program_traverse(AST_program p) {
    if (p == NULL) {
        return;
    }

    symbol_table = symbol_make(28447);
    Scope scope = scope_open(symbol_table);
    AST_gdcl_traverse(p->gdcl_list);
    // AST_dcl_stmts_traverse(p->dcl_stmts); // TODO
    scope_print(scope, 1);
    scope_close(symbol_table);
}

void AST_gdcl_traverse(List gdcl_list){
    if(!gdcl_list) return;
    
    List item = gdcl_list;
    AST_global_decl gdcl = NULL;
    while(item){
        gdcl = item->data;
        switch(gdcl->kind){
            case GDCL_TYPEDEF:
                AST_typedef_traverse(gdcl->u.g_typedef.typedef_dcl);
                break;
            case GDCL_ENUM:
                AST_enum_traverse(gdcl->u.g_enum.enum_dcl);
                break;
            case GDCL_CLASS:
                AST_class_traverse(gdcl->u.g_class.class_dcl);
                break;
            case GDCL_UNION:
                AST_union_traverse(gdcl->u.g_union.union_dcl);
                break;
            case GDCL_GLOBAL_VAR:
                AST_global_var_traverse(gdcl->u.g_global_var.global_var_dcl);
                break;
            case GDCL_FUNC:
                AST_func_traverse(gdcl->u.g_func.func_dcl);
                break;
            default:
                SEMANTIC_ERROR(gdcl_list, "GDCL | Kind undefined.");
                exit(-1);
        }
        item = item->next;
    }
}

void AST_typedef_traverse(AST_typedef typedef_dcl){
    if(!typedef_dcl) return;
    ASSERT(typedef_dcl->id != NULL);
    ASSERT(typedef_dcl->typename != NULL);

    SymbolEntry entry = symbol_enter(symbol_table, typedef_dcl->id, true);
    entry->entry_type = ENTRY_VARIABLE;
    entry->e.variable.type = typedef_dcl->typename;
}

void AST_enum_traverse(AST_enum_dcl enum_dcl){
    if(!enum_dcl) return;
    ASSERT(enum_dcl->id != NULL);

    SymbolEntry entry = symbol_enter(symbol_table, enum_dcl->id, true);
    entry->entry_type = ENTRY_TYPE;
    entry->e.type.scope = scope_open(symbol_table); 
    entry->e.type.type = type_basic(TYPE_enum);
    //TODO: Export to AST_enum_contents_traverse?
    List item = enum_dcl->id_list;
    AST_id id = NULL;
    int *initial_value = new(sizeof(int));
    *initial_value = 0;

    while(item){
        id = (AST_id) item->data;
        AST_id_traverse(id, initial_value);
        item = item->next;
    }

    scope_close(symbol_table);
    free(initial_value);
}

void AST_id_traverse(AST_id id, int *max){ // Used for IDs inside Enum
    if(!id) return;
    ASSERT(id->id != NULL);
    ASSERT(id->init_value != NULL);

    SymbolEntry entry = symbol_enter(symbol_table, id->id, true);
    entry->entry_type = ENTRY_CONSTANT;
    entry->e.constant.type = type_basic(TYPE_int);

    AST_expr expr;
    AST_constant constant;
    switch(id->init_value->kind){
        case INIT_SINGLE: // Enum ID can only be an integer constant!
            expr = id->init_value->u.single.expr;
            if(expr->kind != EXPR_constant) SEMANTIC_ERROR(expr, "Expression | Must be Integer constant.");
            else{
                constant = expr->u.e_constant.constant;
                if(constant->kind != CONSTANT_iconst) SEMANTIC_ERROR(constant, "Constant | Must be Integer constant.");
                else{
                    entry->e.constant.value.v_int = constant->u.c_iconst.rep;
                }
            }
            break;
        case INIT_MULTI:
            SEMANTIC_ERROR(id, "Identifier | Multiple identifiers not allowed in this case.");
            break;
        case INIT_DEFAULT:
        default:
            entry->e.constant.value.v_int = *max;
    }
    
    // Duplicate check / Ascending order check
    if(entry->e.constant.value.v_int < *max){
        SEMANTIC_ERROR(id, "Constant | Enum constants must be in ascending order.");
    }

    if(entry->e.constant.value.v_int >= *max){
        *max = entry->e.constant.value.v_int + 1;
    }
    return;
}

void AST_class_traverse(AST_class_dcl class_dcl){
    if(!class_dcl) return;
    ASSERT(class_dcl->id != NULL);
    ASSERT(class_dcl->class_body != NULL);

    SymbolEntry entry = symbol_enter(symbol_table, class_dcl->id, true);
    entry->entry_type = ENTRY_TYPE;
    entry->e.type.scope = scope_open(symbol_table); 
    entry->e.type.type = type_basic(TYPE_class);

    AST_class_body_traverse(class_dcl->class_body);

    scope_close(symbol_table);
}

void AST_class_body_traverse(AST_class_body class_body){
    if(!class_body) return;
    ASSERT(class_body->members_methods != NULL);
    // ASSERT(class_body->parent != NULL); || PARENT CAN BE NULL

    SymbolEntry parent = NULL;
    if(class_body->parent){
        parent = symbol_lookup(symbol_table, class_body->parent, LOOKUP_ALL_SCOPES, true); // Check if parent exists!
        if(parent->entry_type != ENTRY_TYPE){ // TODO: Verify if this is really needed (I think it should.)
            SEMANTIC_ERROR(class_body, "Parent | Parent must be of another already-defined class.");
        }
    }
    // TODO: Implement parent inheritance methods?!
    // Possibly by just adding the from parent-class using the list.

    List item = class_body->members_methods;
    AST_members_method mm;

    while(item){
        mm = (AST_members_method) item->data;
        AST_members_methods_traverse(mm);

        item = item->next;
    }
}

void AST_members_methods_traverse(AST_members_method members_method){
    if(!members_method) return;
    // ASSERT(members_method->access != NULL); // Maybe hardcode NULL => DEFAULT?
    ASSERT(members_method->mom != NULL);

    // TODO: If statement depending on ACCESS?

    AST_member_or_method_traverse(members_method->mom);
}

void AST_member_or_method_traverse(AST_member_or_method mom){
    if(!mom) return;
    
    switch(mom->kind){
        case MOM_MEMBER:
            AST_member_traverse(mom->u.member.member);
            break;
        case MOM_METHOD:
            AST_short_func_dcl_traverse(mom->u.method.short_func_dcl);
            break;
        default:
            SEMANTIC_ERROR(mom, "MOM | Kind undefined.");
    }
}

void AST_member_traverse(AST_member member){
    if(!member) return;
    
    switch(member->kind){
        case MEMBER_VARIABLE: 
            AST_var_declaration_traverse(member->u.var_declaration);
            break;
        case MEMBER_ANON_UNION: // TODO - Implement Anonymous Unions logic || Scope?
            AST_union_fields_traverse(member->u.union_fields);
            break;
        default:
            SEMANTIC_ERROR(member, "Member | Kind undefined.");
    }
}

void AST_var_declaration_traverse(AST_var_declaration var_declaration){
    if(!var_declaration) return;
    ASSERT(var_declaration->typename != NULL);
    ASSERT(var_declaration->list != NULL);

    // Assign typename to all variables inside the list
    List item = var_declaration->list;
    AST_variabledef variabledef;

    while(item){ // TODO: MERGE with init_variabledef
        variabledef = (AST_variabledef) item->data;
        ASSERT(variabledef->id != NULL);
        AST_variabledef_traverse(variabledef, var_declaration->typename);

        item = item->next;
    }
}

void AST_union_fields_traverse(List union_fields){
    if(!union_fields) return;

    List item = union_fields;
    AST_var_declaration var_declaration;

    while(item){
        var_declaration = (AST_var_declaration) item->data;

        AST_var_declaration_traverse(var_declaration);

        item = item->next;
    }
}

void AST_short_func_dcl_traverse(AST_short_func_dcl short_func_dcl){
    if(!short_func_dcl) return;
    ASSERT(short_func_dcl->func_header_start != NULL);
    ASSERT(short_func_dcl->kind == SHORT_FUNC_NO_PARAMS || 
           short_func_dcl->kind == SHORT_FUNC_WITH_PARAMS);
    
    if(symbol_table->currentScope->nesting == 1){ // Function declarations should only be inside classes! TODO: Verify not nested declarations inside struct/func/smthing else 
        SEMANTIC_ERROR(short_func_dcl, "Short func dcl | Function declaration attempted in global scope. \n - This should be allowed by C++600, but we haven't implemented it yet.");
    }

    SymbolEntry entry = symbol_enter(symbol_table, short_func_dcl->func_header_start->id, true);
    entry->entry_type = ENTRY_FUNCTION_DECLARATION;
    entry->e.function_declaration.result_type = short_func_dcl->func_header_start->typename;
    
    // Add parameters to function if they are defined || TODO: Verify that there are no check that need to happen!
    if(short_func_dcl->kind == SHORT_FUNC_WITH_PARAMS) entry->e.function_declaration.parameters_as_types = short_func_dcl->parameters;
}

void AST_union_traverse(AST_union_dcl union_dcl){
    if(!union_dcl) return;
    ASSERT(union_dcl->id != NULL);
    ASSERT(union_dcl->union_fields != NULL);
    
    SymbolEntry entry = symbol_enter(symbol_table, union_dcl->id, true);
    entry->entry_type = ENTRY_TYPE; // TODO: Might require custom entry to do Union functions?
    entry->e.type.scope = scope_open(symbol_table); // TODO: Possibly doesn't need to be like that
    entry->e.type.type = type_basic(TYPE_union);

    AST_union_fields_traverse(union_dcl->union_fields);
    
    scope_close(symbol_table);
}

void AST_global_var_traverse(AST_global_var_declaration global_var_dcl){
    if(!global_var_dcl) return;
    ASSERT(global_var_dcl->typename != NULL);
    ASSERT(global_var_dcl->init_variabledefs != NULL); // TODO: Can this be null ? Can there be no Vars?

    List item = global_var_dcl->init_variabledefs;
    AST_init_variabledef init_variabledef;

    while(item){
        // TODO: Set correct type to each init variabledef.
        init_variabledef = item->data;
     
        AST_init_variabledef_traverse(init_variabledef, global_var_dcl->typename);

        item = item->next;
    }     
}

void AST_init_variabledef_traverse(AST_init_variabledef init_variabledef, Type typename){ // TODO: Good luck with this
    if(!init_variabledef) return;
    ASSERT(init_variabledef->variabledef != NULL);
    ASSERT(init_variabledef->init_value != NULL); // Can it be null?>

    AST_variabledef_traverse(init_variabledef->variabledef, typename);

    // TODO: Parse init_value!!
    // IMPORTANT!!
}

// TODO: Merge this wherever needed
void AST_variabledef_traverse(AST_variabledef variabledef, Type typename){
    SymbolEntry entry = symbol_enter(symbol_table, variabledef->id, true);
    entry->entry_type = ENTRY_VARIABLE;

    // TODO: Possibly export this? Most likely will be required by other funcs here & outside of this file.
    if(variabledef->type == NULL){ // Simple variable, neither List nor Array.
        entry->e.variable.type = typename;
    }else{
        switch(variabledef->type->kind){
            case TYPE_list:  // TODO: Verify that this works
                variabledef->type->u.t_list.type = typename;
                entry->e.variable.type = variabledef->type;
                break;
            case TYPE_array: // TODO: Verify that this works
                set_array_type(variabledef->type, typename);
                entry->e.variable.type = variabledef->type;
                break;
            default:
                SEMANTIC_ERROR(variabledef, "Variabledef | Unexpected variable inner type (NULL, List or Array expected but got %d)", variabledef->type->kind);
        }
    }
}

void AST_func_traverse(AST_func_dcl func_dcl){
    if(!func_dcl) return;
    
    switch(func_dcl->kind){
        case FD_SHORT: // TODO
            AST_short_func_dcl_traverse(func_dcl->u.fd_short.func);
            break;
        case FD_FULL: // TODO
            AST_full_func_dcl_traverse(func_dcl->u.fd_full.func);
            break;
        default:
            SEMANTIC_ERROR(func_dcl, "Function Declaration | Kind undefined.");
    }
}

// TODO: Solve the following
// 1: Do we require a declaration?
// 2: Should Declarations point to functions?
// 3: Should Declarations & functions be unified (pointing dec to func)
void AST_full_func_dcl_traverse(AST_full_func_dcl full_func){
    if(!full_func) return;
    
    SymbolEntry entry = NULL;
    switch(full_func->kind){
        case FFD_NOPAR:
            entry = AST_func_header_start_traverse(full_func->u.nopar.header, NULL);
            break;
        case FFD_NOPAR_CLASS:
            entry = AST_class_func_header_start_traverse(full_func->u.nopar_class.header, NULL);
            break;
        case FFD_FULL_PAR: 
            entry = AST_full_par_func_header_traverse(full_func->u.full_par.header);
            break;
        default:
            SEMANTIC_ERROR(full_func, "Full Function Declaration | Kind undefined.");
    }
    ASSERT(entry != NULL);
    scope_close(symbol_table);
    AST_dcl_stmt_traverse(full_func->statements); // TODO
}

SymbolEntry AST_func_header_start_traverse(AST_func_header_start func_header_start, List parameters){ 
    if(!func_header_start) return NULL;

    SymbolEntry entry = symbol_enter(symbol_table, func_header_start->id, true);
    entry->entry_type = ENTRY_FUNCTION;
    entry->e.function.result_type = func_header_start->typename;
    entry->e.function.scope = scope_open(symbol_table);
    entry->e.function.parameters = full_func_params_parse(parameters); // Function can accept NULL parameters.
    entry->e.function.class = NULL;
    
    // if(parameters != NULL) check_function_parameters(func_dcl->e.function_declaration.parameters_as_types, entry->e.function.parameters); // TODO: Implement func_declaration for global funcs without class

    return entry;
}

SymbolEntry AST_class_func_header_start_traverse(AST_class_func_header_start class_func_header_start, List parameters){
    if(!class_func_header_start) return NULL;
    ASSERT(class_func_header_start->class != NULL);
    ASSERT(class_func_header_start->typename != NULL);
    ASSERT(class_func_header_start->id != NULL);
    
    char func_name[256*2+2]; // TODO: Better
    memset(func_name,0, strlen(func_name));
    sprintf(func_name, "%s::%s", class_func_header_start->class->name, class_func_header_start->id->name);
    SymbolEntry class, func_dcl;
    SymbolEntry entry = symbol_enter(symbol_table, id_make(func_name), true);
    entry->entry_type = ENTRY_FUNCTION;
    entry->e.function.result_type = class_func_header_start->typename;

    class = symbol_lookup(symbol_table, class_func_header_start->class, LOOKUP_ALL_SCOPES, true);
    if(class->entry_type != ENTRY_TYPE || 
      (class->entry_type == ENTRY_TYPE && class->e.type.type->kind != TYPE_class)){
        SEMANTIC_ERROR(class_func_header_start, 
                      "Class Func Header Start | Function's \"%s\" class \"%s\" is not a class.", 
                       class_func_header_start->id->name, class->id->name);
    }
    

    if(!(func_dcl = symbol_lookup_scope(symbol_table, class->e.type.scope, class_func_header_start->id, false))){ // Check if function is actually part of the class?
        SEMANTIC_ERROR(class_func_header_start, 
                      "Class Func Header Start | Class \"%s\" doesn't contain function \"%s\".", 
                       class->id->name, class_func_header_start->id->name);
    }

    // Verify function name is actually a function declaration
    if(func_dcl->entry_type != ENTRY_FUNCTION_DECLARATION){
        SEMANTIC_ERROR(class_func_header_start, 
                      "Class Func Header Start | Function name \"%s\" doesn't match any function in\"%s\".", 
                       class_func_header_start->id->name, class->id->name);    
    }

    // Check if function has been redefined
    if(func_dcl->e.function_declaration.function != NULL){
        SEMANTIC_ERROR(class_func_header_start, 
                      "Class Func Header Start | Function \"%s\" redefinition.", 
                       class_func_header_start->id->name, class->id->name);    
    }
    func_dcl->e.function_declaration.function = entry;

    entry->e.function.class = class;
    entry->e.function.scope = scope_open(symbol_table);
    entry->e.function.parameters = full_func_params_parse(parameters);
    
    if(parameters != NULL) check_function_parameters(func_dcl->e.function_declaration.parameters_as_types, entry->e.function.parameters);

    return entry;
}

SymbolEntry AST_full_par_func_header_traverse(AST_full_par_func_header full_par_func_header){
    if(!full_par_func_header) return NULL;

    SymbolEntry entry;
    switch(full_par_func_header->kind){
        case FPF_NOCLASS:
            entry = AST_func_header_start_traverse(full_par_func_header->u.fpf_noclass.header, full_par_func_header->parameters);
            break;
        case FPF_CLASS:
            entry = AST_class_func_header_start_traverse(full_par_func_header->u.fpf_class.header, full_par_func_header->parameters);
            break;
        default:
            SEMANTIC_ERROR(full_par_func_header, "Full Par Func Header | Kind undefined. (%d)", full_par_func_header->kind);
    }
    // TODO: Verify parameters
    return entry;
}

List full_func_params_parse(List parameters){ // Doesn't create new list. It justs modifies the parameters
    List item = parameters;
    AST_parameter param;
    while(item != NULL){
        param = item->data;
        ASSERT(param->passvar != NULL);
        ASSERT(param->typename != NULL);
        switch(param->passvar->kind){
            case PASSVAR_ref:
                param->typename = type_ref(param->typename);

                // TODO: Update this -- Risky & Complicated / buggy structure
                AST_variabledef vardef = ast_variabledef(param->passvar->u.ref_id, NULL, NULL);
                AST_variabledef_traverse(vardef, param->typename);
                break;
            case PASSVAR_variable:
                AST_variabledef_traverse(param->passvar->u.variabledef, param->typename);
                break;
            default:
                SEMANTIC_ERROR(param, "Parameter | Kind undefined.");
        }
        item = item->next;
    }
    return parameters;
}

void check_function_parameters(List func_dcl_params, List func_params){
    List item_func_dcl = func_dcl_params,
         item_func = func_params;
    Type func_dcl_type;
    AST_parameter func_param;
    while(true){
        if(item_func_dcl == NULL || item_func == NULL) break;

        func_dcl_type = item_func_dcl->data;
        func_param = item_func->data;

        if(!type_eq(func_dcl_type, func_param->typename)){
            SEMANTIC_ERROR(func_params, "Function Parameters | Function parameters do not match function declaration parameters.");
        }

        item_func_dcl = item_func_dcl->next;
        item_func = item_func->next;
    }

    if(item_func_dcl != NULL || item_func != NULL){
        SEMANTIC_ERROR(func_params, "Function Parameters | Function parameters do not match function declaration parameters.");
    }
}

void AST_dcl_stmt_traverse(AST_dcl_stmt dcl_stmt){
    if(!dcl_stmt) return;

    switch(dcl_stmt->kind){
        case DCL_STMT_STMTS_DCLS: // TODO
        case DCL_STMT_STMTS: // TODO
        case DCL_STMT_DCLS: // TODO
            AST_declarations_traverse(dcl_stmt->u.dcl_stmt_dcls.declares);
            break;
        case DCL_STMT_EMPTY:
            return;
        default:
            SEMANTIC_ERROR(dcl_stmt, "Dcl stmt | Kind undefined.");
    }
}

void AST_declarations_traverse(List dcls){
    if(!dcls) return;
    List item = dcls;
    AST_declaration dcl;
    while(item != NULL){
        dcl = item->data;
        AST_declaration_traverse(dcl);
        item = item->next;
    }
}

void AST_declaration_traverse(AST_declaration dcl){
    if(!dcl) return;

    if(dcl->is_static){
        printf("TODO: Handle STATIC for %d\n", dcl->lineno); // TODO!! Requires stack.........
    }

    List item = dcl->list;
    AST_variabledef variabledef;

    while(item){ // TODO: MERGE with init_variabledef
        variabledef = (AST_variabledef) item->data;
        ASSERT(variabledef->id != NULL);
        AST_variabledef_traverse(variabledef, dcl->typename);

        item = item->next;
    }
}
