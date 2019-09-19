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
        case TYPE_func:
            return type_eq(a->u.t_func.type1, b->u.t_func.type1) &&
                type_eq(a->u.t_func.type2, b->u.t_func.type2);
        case TYPE_id:
            return strcmp(a->u.t_id.id->name, b->u.t_id.id->name) == 0;
        case TYPE_ref:
            return type_eq(a->u.t_ref.type, b->u.t_ref.type);
        case TYPE_array:
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
            case GDCL_CLASS: // TODO
                AST_class_traverse(gdcl->u.g_class.class_dcl);
                break;
            case GDCL_UNION: // TODO
            case GDCL_GLOBAL_VAR: // TODO
            case GDCL_FUNC: // TODO
            default:
                SEMANTIC_ERROR(gdcl_list, "GDCL | Invalid kind");
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
        case MOM_MEMBER: // TODO
            AST_member_traverse(mom->u.member);
            break;
        case MOM_METHOD: // TODO
            printf("MOM\n");
            break;
        default:
            SEMANTIC_ERROR(mom, "MOM | Member or Method kind undefined.");
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
            SEMANTIC_ERROR(member, "Member | Member kind undefined.");
    }
}

void AST_var_declaration_traverse(AST_var_declaration var_declaration){
    if(!var_declaration) return;
    ASSERT(var_declaration->typename != NULL);
    ASSERT(var_declaration->list != NULL);

    // Assign typename to all variables inside the list
    List item = var_declaration->list;
    AST_variabledef variabledef;

    while(item){
        variabledef = (AST_variabledef) item->data;
        ASSERT(variabledef->id != NULL);
        SymbolEntry entry = symbol_enter(symbol_table, variabledef->id, true);
        entry->entry_type = ENTRY_VARIABLE;

        // TODO: Possibly export this? Most likely will be required by other funcs here & outside of this file.
        if(variabledef->type == NULL){ // Simple variable, neither List nor Array.
            entry->e.variable.type = var_declaration->typename;
        }else{
            switch(variabledef->type->kind){
                case TYPE_list:  // TODO: Verify that this works
                    variabledef->type->u.t_list.type = var_declaration->typename;
                    entry->e.variable.type = variabledef->type;
                    break;
                case TYPE_array: // TODO: Verify that this works
                    set_array_type(variabledef->type, var_declaration->typename);
                    entry->e.variable.type = variabledef->type;
                    break;
                default:
                    SEMANTIC_ERROR(variabledef, "Variabledef | Unexpected variable inner type (NULL, List or Array expected but got %d)", variabledef->type->kind);
            }
        }

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