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
        case TYPE_list:
            return type_eq(a->u.t_list.type, b->u.t_list.type);
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
    entry->e.function_declaration.function = NULL;
    entry->e.function_declaration.parameters_as_types = NULL;
    if(short_func_dcl->kind == SHORT_FUNC_WITH_PARAMS) entry->e.function_declaration.parameters_as_types = short_func_dcl->parameters;
}

void AST_union_traverse(AST_union_dcl union_dcl){
    if(!union_dcl) return;
    ASSERT(union_dcl->id != NULL);
    ASSERT(union_dcl->union_fields != NULL);
    
    SymbolEntry entry = symbol_enter(symbol_table, union_dcl->id, true);
    entry->entry_type = ENTRY_TYPE; // TODO: Might require custom entry to do Union functions?
    entry->e.type.scope = scope_open(symbol_table); 
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
        init_variabledef = item->data;
     
        AST_init_variabledef_traverse(init_variabledef, global_var_dcl->typename);

        item = item->next;
    }     
}

void AST_init_variabledef_traverse(AST_init_variabledef init_variabledef, Type typename){ // TODO: Good luck with this
    if(!init_variabledef) return;
    ASSERT(init_variabledef->variabledef != NULL);
    ASSERT(init_variabledef->init_value != NULL); // Can it be null?>

    SymbolEntry entry = AST_variabledef_traverse(init_variabledef->variabledef, typename);
    ASSERT(entry != NULL);
    AST_init_value_traverse(entry, init_variabledef->init_value); // TODO
}

// TODO: Merge this wherever needed
SymbolEntry AST_variabledef_traverse(AST_variabledef variabledef, Type typename){
    if(!variabledef || !typename) return NULL;
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
    ASSERT(typename != NULL);
    return entry;
}

void AST_func_traverse(AST_func_dcl func_dcl){
    if(!func_dcl) return;
    
    switch(func_dcl->kind){
        case FD_SHORT:
            AST_short_func_dcl_traverse(func_dcl->u.fd_short.func);
            break;
        case FD_FULL:
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
    AST_dcl_stmt_traverse(full_func->statements); // TODO
    scope_close(symbol_table);
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
                      "Class Func Header Start | Function \"%s\" redefinition. %s", 
                       class_func_header_start->id->name);    
    }
    func_dcl->e.function_declaration.function = entry;

    entry->e.function.class = class;
    entry->e.function.scope = scope_open(symbol_table);
    entry->e.function.parameters = full_func_params_parse(parameters);
    
    // check_function_parameters(func_dcl->e.function_declaration.parameters_as_types, entry->e.function.parameters);
    check_function(func_dcl, entry);

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

    return entry;
}

List full_func_params_parse(List parameters){ // Doesn't create new list. It justs modifies the parameters
    List item = parameters;
    AST_parameter param;
    SymbolEntry entry;
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
                entry = AST_variabledef_traverse(param->passvar->u.variabledef, param->typename);
                param->typename = entry->e.parameter.type;
                break;
            default:
                SEMANTIC_ERROR(param, "Parameter | Kind undefined.");
        }
        item = item->next;
    }
    return parameters;
}

bool check_function(SymbolEntry func_dcl, SymbolEntry func){
    List item_func_dcl = func_dcl->e.function_declaration.parameters_as_types,
         item_func = func->e.function.parameters;
    Type func_dcl_type;
    AST_parameter func_param;

    if(!type_eq(func_dcl->e.function_declaration.result_type, func->e.function.result_type)){
        error("Function | Function's \"%s\" return type do not match.", func->id->name);
    }

    if(item_func_dcl == NULL && item_func == NULL) return true;

    while(true){
        if(item_func_dcl == NULL || item_func == NULL) break;

        func_dcl_type = item_func_dcl->data;
        func_param = item_func->data;

        if(!type_eq(func_dcl_type, func_param->typename)){
            SEMANTIC_ERROR(item_func, "Function Parameters | Function parameters do not match function declaration parameters.");
        }

        item_func_dcl = item_func_dcl->next;
        item_func = item_func->next;
    }

    if(item_func_dcl != NULL){
        SEMANTIC_ERROR(item_func_dcl, "Function Declaration Parameters | Function parameters do not match function declaration parameters.");
    }

    if(item_func != NULL){
        func_param = item_func->data;
        SEMANTIC_ERROR(item_func, "Function Parameters | Function parameters do not match function declaration parameters.");
    }
    return true;
}

void AST_dcl_stmt_traverse(AST_dcl_stmt dcl_stmt){
    if(!dcl_stmt) return;

    switch(dcl_stmt->kind){
        case DCL_STMT_STMTS_DCLS: // TODO
            AST_statements_traverse(dcl_stmt->u.dcl_stmt_stmts.statements);
            AST_declarations_traverse(dcl_stmt->u.dcl_stmt_stmts_dcls.declares);
            break;
        case DCL_STMT_STMTS: // TODO
            AST_statements_traverse(dcl_stmt->u.dcl_stmt_stmts.statements);
            break;
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

void AST_statements_traverse(List stmts){
    if(!stmts) return;
    List item = stmts;
    AST_stmt stmt;
    while(item != NULL){
        stmt = item->data;
        AST_statement_traverse(stmt);
        item = item->next;
    }
}

void AST_statement_traverse(AST_stmt stmt){
    if(!stmt) return;
    
    switch (stmt->kind){
        case STMT_EXPR: //TODO
            break;
        case STMT_IF:   //TODO
            break;
        case STMT_WHILE: //TODO
            break;
        case STMT_FOR: //TODO
            break;
        case STMT_SWITCH: //TODO
            break;
        case STMT_RETURN: //TODO
            AST_general_expr_traverse(stmt->u.return_stmt.optexpr);
            break;
        case STMT_INPUT: //TODO
            io_traverse(stmt->u.io_stmt.io_list);
            break;
        case STMT_OUTPUT: //TODO
            io_traverse(stmt->u.io_stmt.io_list);          // is this right?
            break;
        case STMT_COMP: //TODO
            AST_dcl_stmt_traverse(stmt->u.comp_stmt.dcl_stmt);
            break;
        case STMT_CONTINUE: //TODO
            // do we need code here?
            printf("STMT_CONTINUE Found. \n");
            break;
        case STMT_BREAK: //TODO
            // do we need code here?
            printf("STMT_BREAK Found. \n");
            break;
        case STMT_SEMI: //TODO
            // do we need code here?
            printf("STMT_SEMI Found. \n");
            break;
        default:
            SEMANTIC_ERROR(stmt, "statement | Kind undefined.");
    }
}
void AST_init_value_traverse(SymbolEntry entry, AST_init_value init_value){
    if(!init_value || !entry) return;
    ASSERT(entry->entry_type == ENTRY_CONSTANT || entry->entry_type == ENTRY_VARIABLE);

    AST_constant constant;
    if(entry->entry_type == ENTRY_CONSTANT){ // TODO

    }else if(entry->entry_type == ENTRY_VARIABLE){ // TODO
        switch(init_value->kind){
            case INIT_SINGLE: // TODO
                    AST_expr_traverse(init_value->u.single.expr);
                    // if(type->kind == TYPE_int) printf("Simple constant %d\n", constant->u.c_iconst);
                break;
            case INIT_MULTI: // TODO
                AST_multi_expr_traverse(init_value->u.multi.list_of_exprs);
                break;
            case INIT_DEFAULT: // TODO
                switch(entry->e.variable.type->kind){
                    case TYPE_int:
                        printf("ASSIGN to %s default value of %d\n", entry->id->name, 0);
                        break;
                    case TYPE_float:
                        printf("ASSIGN to %s default value of %.1f\n", entry->id->name, 0.0f);
                        break;
                    case TYPE_char:
                        printf("ASSIGN to %s default value of '%c'\n", entry->id->name, '0');
                        break;
                    default:
                        printf("ASSIGN to %s default value of NULL\n", entry->id->name);
                        break;
                }
                break;
            default:
                SEMANTIC_ERROR(init_value, "Init value | Kind undefined.");
        }
    }
}

void AST_multi_expr_traverse(List exprlist){
    List item = exprlist;
    AST_expr expr;
    while(item != NULL){
        expr = item->data;
        
        AST_expr_traverse(expr); // TODO | Calculations
        // if(constant->kind == CONSTANT_iconst) printf("Simple constant %d", constant->u.c_iconst);
        // printf("constant kind %d\n", constant->kind);
        item = item->next;
    }
}

Type AST_expr_traverse(AST_expr expr){
    ASSERT(expr != NULL);
    Type res = type_basic(TYPE_unknown);
    Type expr1_type, expr2_type;
    // AST_constant constant = new(malloc(sizeof(*constant)));
    switch(expr->kind){
        case EXPR_unop:
            expr1_type = AST_expr_traverse(expr->u.e_unop.expr);
            res = AST_expr_unop_traverse(expr, expr1_type);
            break;
        case EXPR_binop:
            expr1_type = AST_expr_traverse(expr->u.e_binop.expr1);
            expr2_type = AST_expr_traverse(expr->u.e_binop.expr2);
            res = AST_expr_binop_traverse(expr1_type, expr, expr2_type);
            break;
        case EXPR_call: // TODO - func & length - AST needs patching... & Maybe custom function for length?
            res = AST_expr_function_call_traverse(expr->u.e_call.variable, expr->u.e_call.list);
            break;
        case EXPR_incdec: // TODO - AST needs patching
            expr1_type = AST_variable_traverse(expr->u.e_incdec.variable);
            res = AST_expr_incdec_traverse(expr1_type, expr->u.e_incdec.variable);
            break;
        case EXPR_variable: // TODO ---
            res = AST_variable_traverse(expr->u.e_variable.variable);
            break;
        case EXPR_constant:
            switch(expr->u.e_constant.constant->kind){
                case CONSTANT_iconst:
                    res = type_basic(TYPE_int);
                    break;
                case CONSTANT_fconst:
                    res = type_basic(TYPE_float);
                    break;
                case CONSTANT_cconst:
                    res = type_basic(TYPE_char);
                    break;
                case CONSTANT_sconst:
                    res = type_basic(TYPE_str); // TODO: NEED TO ALLOCATE CORRECT SPACE!!
                    break;
                default:
                    SEMANTIC_ERROR(expr->u.e_constant.constant, "Constant | Kind undefined.");
            }
            break;
        case EXPR_type:
            res = expr->u.e_type.type;
            break;
        case EXPR_new: // TODO 
        case EXPR_general_expr: // TODO
        case EXPR_list_expr: // TODO
        default:
            SEMANTIC_ERROR(expr, "Expr | Kind undefined.");
    }
    expr->typename = res;
    return res;
}

Type AST_expr_unop_traverse(AST_expr expr, Type type){
    switch (expr->u.e_unop.op) {
        case ast_unop_plus:
        case ast_unop_minus:
            if(!type_eq(type, type_basic(TYPE_int)) || !type_eq(type, type_basic(TYPE_float)))
                SEMANTIC_ERROR(expr, "Unop Expr | Type mismatch: Argument is not of type int or float.");
            return type;

        case ast_unop_not:
            if (!type_check(type, TYPE_ref, true))
                SEMANTIC_ERROR(expr, "Unop Expr | Type mismatch: Argument is not of type ref.");
            return (expr == NULL ? NULL : type->u.t_ref.type);

        default:
            SEMANTIC_ERROR(expr, "Unop Expr | Kind undefined.");
    }
}

Type AST_expr_binop_traverse(Type type1, AST_expr expr, Type type2) {
    switch (expr->u.e_binop.op) {
        case ast_binop_plus:
        case ast_binop_minus:
        case ast_binop_times:
        case ast_binop_div: // TODO: div only for int? mod only for int?
        case ast_binop_mod: // TODO: Implement different types (ex float + int, float / int)
            if(!type_eq(type1, type2) || 
               (type_eq(type1, type2) && !(type_eq(type1, type_basic(TYPE_int)) || type_eq(type1, type_basic(TYPE_float)))))
                SEMANTIC_ERROR(expr, "Binop Expr | Type mismatch in the left & right operand.");
            return type1;

        case ast_binop_lt:
        case ast_binop_gt:
        case ast_binop_le:
        case ast_binop_ge:
            if(!type_eq(type1, type2) )
                SEMANTIC_ERROR(expr, "Binop Expr | Type mismatch: Arguments must be of the same type.");
            if(!type_eq(type1, type_basic(TYPE_char)) && !type_eq(type1, type_basic(TYPE_float)) &&
               !type_eq(type1, type_basic(TYPE_int)))
                SEMANTIC_ERROR(expr, "Binop Expr | Type mismatch: Arguments must be of type char, float or int.");
            return type_basic(TYPE_int);

        // TODO: case on assignment? No?
        case ast_binop_eq:
        case ast_binop_ne:
            if(!type_eq(type1, type2))
                SEMANTIC_ERROR(expr, "Binop Expr | Type mismatch: Arguments must be of the same type.");
            if(type_check(type1, TYPE_array, false) || type_check(type2, TYPE_array, false))
                SEMANTIC_ERROR(expr, "Binop Expr | Type mismatch: Arguments can't be of type array.");
            if(type_check(type1, TYPE_ref, false) || type_check(type2, TYPE_ref, false))
                SEMANTIC_ERROR(expr, "Binop Expr | Type mismatch: Arguments can't be of type function.");
            return type_basic(TYPE_int);

        case ast_binop_and:
        case ast_binop_or:
            if(!type_eq(type1, type_basic(TYPE_int)))
                SEMANTIC_ERROR(expr, "Binop Expr | Type mismatch in the left argument.");
            if(!type_eq(type2, type_basic(TYPE_int)))
                SEMANTIC_ERROR(expr, "Binop Expr | Type mismatch in the right argument.");
            return type_basic(TYPE_int);


        // TODO: Check about these
        // case ast_binop_semicolon:
        //     return expr2;

        // case ast_binop_assign:
        //     if ( !type_check_ref(expr1,true) ) 
        //         SEMANTIC_ERROR(e, "Type mismatch: First argument must be of type ref\n");
        //     else if ( expr1 != NULL && !type_eq(expr1->u.t_ref.type, expr2) )
        //         SEMANTIC_ERROR(e, "Type mismatch: The arguments of the assignment operator do not match\n");
        //     return type_unit();

        default:
            SEMANTIC_ERROR(expr, "Binop Expr | Kind undefined.");
    }

    return NULL;
}

Type AST_expr_incdec_traverse(Type typename, AST_variable variable){
    if(!type_eq(typename, type_basic(TYPE_int))){ // ++, -- allowed only on integer values.
        SEMANTIC_ERROR(variable, "Variable | Type mismatch in the incdec argument.");
    }

    return typename;
}


Type AST_expr_function_call_traverse(AST_variable variable, AST_exprlist exprlist_parameters){ // TODO - ALL
    // SymbolEntry entry = symbol_lookup(symbol_table, e->u.e_call.id, LOOKUP_ALL_SCOPES, 1);

    // if  ( entry->entry_type != ENTRY_FUNCTION )
    //     SEMANTIC_ERROR(e, "'%s' is not a function\n", e->u.e_call.id->name);

    // expr1_type = AST_expr_list_traverse(e->u.e_call.list);

    // if ( !type_eq(expr1_type, entry->e.function.type->u.t_func.type1) )
    //     SEMANTIC_ERROR(e, "The types of the arguments of function '%s' do "
    //             "not match the definition\n", e->u.e_call.id->name);

    // e->entry = entry; /* προσθήκη στον κόμβο ενός δείκτη στο symbol
    //                         entry της συνάρτησης που καλούμε */
    // res = entry->e.function.result_type;
    return type_basic(TYPE_unknown);
}

void io_traverse(List io){
    //?
}

Type AST_general_expr_traverse(AST_general_expr gexpr){
    switch(gexpr->kind){
        case GEXPR_GEXPR:   
            AST_general_expr_traverse(gexpr->u.gexpr.general_expr1);
            AST_general_expr_traverse(gexpr->u.gexpr.general_expr2);    // is this ok?
            break;
        case GEXPR_ASSIGNMENT:
            AST_assignment_traverse(gexpr->u.assignment.assignment);
            break;
        default:
            SEMANTIC_ERROR(gexpr, "General expr | Kind undefined.");
    }
}

Type AST_assignment_traverse(AST_assignment assign){
    switch(assign->kind){
        case ASSIGNMENT_EXPR:
            AST_expr_traverse(assign->u.expr.expr);
            break;
        case ASSIGNMENT_VAR: //TODO
            break;
        default:
            SEMANTIC_ERROR(assign, "Assignment | Kind undefined.");
    }
}

void AST_exprlist_traverse(AST_exprlist exprlist){
    switch(exprlist->kind){
        case EXPRLIST_general:
            AST_general_expr_traverse(exprlist->u.e_general.general_expr);
        case EXPRLIST_empty:
            printf("Exprlist empty\n");
        default:
            SEMANTIC_ERROR(exprlist, "exprlist | Kind undefined.");  
    }
}

void AST_constant_traverse(AST_constant constant){
    switch(constant->kind){
        case CONSTANT_iconst:
            printf("Constant value: %d\n", constant->u.c_iconst.rep);
            break;
        case CONSTANT_fconst:
            printf("Constant value: %f\n", constant->u.c_fconst.rep);
            break;
        case CONSTANT_cconst:
            printf("Constant value: %c\n", constant->u.c_cconst.rep);
            break;
        case CONSTANT_sconst:
            printf("Constant value: %s\n", constant->u.c_sconst.rep);
            break;
        default:
            SEMANTIC_ERROR(constant, "Constant | Kind undefined.");  
    }
}

Type AST_variable_traverse(AST_variable var){
    SymbolEntry entry = NULL;
    Type res = NULL;
    switch(var->kind){
        case VARIABLE_LIST: // TODO: Not sure what to expect here...
            AST_variable_traverse(var->u.list.variable);
            AST_general_expr_traverse(var->u.list.general_expr);
            break;
        case VARIABLE_NESTED:       //TODO
            // probably needs scope_open
            AST_variable_traverse(var->u.nested.variable);
            entry = symbol_lookup(symbol_table, var->u.nested.id, LOOKUP_ALL_SCOPES, 1);
            if(entry->entry_type != ENTRY_VARIABLE){ // TODO: Or (and) maybe function?
                SEMANTIC_ERROR(var, "Variable | Nested variable expected VAR. Instead got %s.", reverse_entry_type[ENTRY_VARIABLE]); 
            }
            res = entry->e.variable.type;
            break;
        case VARIABLE_LISTFUNC:     //TODO - IDK what to do here yet.
            break;
        case VARIABLE_DEFINITION: //TODO - Find usecase to understand actual use.
            entry = symbol_enter(symbol_table, var->u.definition.id, true); // TODO: Verify
            entry->entry_type = ENTRY_VARIABLE;
            entry->e.variable.type = type_basic(TYPE_unknown);
            res = entry->e.variable.type;
            break;
        case VARIABLE_THIS: //TODO - Scope remains the same, but after that i expect a scope-open
            break;
        default:
            SEMANTIC_ERROR(var, "Variable | Kind undefined.");  
    }
    ASSERT(res != NULL);
    return res;
}