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
    char buffer[256];
    switch(entry->e.variable.type->kind){
        case TYPE_array: 
            printf("Typedef %s of %s \n", entry->id->name, _print_array_type(entry->e.variable.type));
            break;
        default:
            printf("Typedef %s of %s \n", entry->id->name, reverse_type_kind[entry->e.variable.type->kind]);
    }
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