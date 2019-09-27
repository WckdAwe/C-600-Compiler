#ifndef __SEMANTIC_H__
#define __SEMANTIC_H__


/* ---------------------------------------------------------------------
   ---------------------------- Header files ---------------------------
   --------------------------------------------------------------------- */

#include <stdio.h>

#include "ast.h"
#include "symbol.h"


/* ---------------------------------------------------------------------
   ------------------------ Function prototypes ------------------------
   --------------------------------------------------------------------- */

#include <string.h>
#include <stdbool.h>
#include "error.h"
#include "ast.h"
#include "semantic.h"
#include "symbol.h"

bool type_check(Type input, int check, bool can_be_null);
bool type_eq(Type a, Type b);
void AST_program_traverse(AST_program p);
void AST_gdcl_traverse(List gdcl_list);
void AST_typedef_traverse(AST_typedef typedef_dcl);
void AST_enum_traverse(AST_enum_dcl enum_dcl);
void AST_id_traverse(AST_id id, int *max);
void AST_class_traverse(AST_class_dcl class_dcl);
void AST_class_body_traverse(AST_class_body class_body);
void AST_members_methods_traverse(AST_members_method members_method);
void AST_member_or_method_traverse(AST_member_or_method mom);
void AST_member_traverse(AST_member member);
void AST_var_declaration_traverse(AST_var_declaration var_declaration);
void AST_union_fields_traverse(List union_fields);
void AST_short_func_dcl_traverse(AST_short_func_dcl short_func_dcl);
void AST_union_traverse(AST_union_dcl union_dcl);
void AST_global_var_traverse(AST_global_var_declaration global_var_dcl);
void AST_init_variabledef_traverse(AST_init_variabledef init_variabledef, Type typename);
SymbolEntry AST_variabledef_traverse(AST_variabledef variabledef, Type typename);
void AST_func_traverse(AST_func_dcl func_dcl);
void AST_full_func_dcl_traverse(AST_full_func_dcl full_func);
SymbolEntry AST_func_header_start_traverse(AST_func_header_start func_header_start, List parameters);
SymbolEntry AST_full_par_func_header_traverse(AST_full_par_func_header full_par_func_header);
SymbolEntry AST_class_func_header_start_traverse(AST_class_func_header_start class_func_header_start, List parameters);
List full_func_params_parse(List parameters);
void check_function_parameters(List func_dcl_params, List func_params);
void AST_dcl_stmt_traverse(AST_dcl_stmt dcl_stmt);
void AST_declarations_traverse(List dcls);
void AST_declaration_traverse(AST_declaration dcl);
void AST_statements_traverse(List stmts);
void AST_statement_traverse(AST_stmt stmt);
void AST_init_value_traverse(SymbolEntry entry, AST_init_value init_value);
void AST_multi_expr_traverse(List exprlist);
AST_constant AST_expr_traverse(AST_expr expr);
void io_traverse(List io);
void AST_general_expr_traverse(AST_general_expr gexpr);
void AST_assignment_traverse(AST_assignment assign);
void AST_exprlist_traverse(AST_exprlist exprlist);
void AST_constant_traverse(AST_constant constant);
void AST_variable_traverse(AST_variable var);
#endif
