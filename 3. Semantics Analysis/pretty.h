#ifndef __PRETTY_H__
#define __PRETTY_H__
 

#include <stdio.h>
#include "ast.h"



void Identifier_print(FILE *, int, Identifier);
void Access_print(FILE *, int, Access );
void Type_print(FILE *, int, Type );

void RepInt_print (FILE *, int, int);
void RepFloat_print (FILE *, int, float);
void RepChar_print (FILE *, int, char);
void RepString_print (FILE *, int, char *);

void AST_binop_print(FILE *, int, AST_binop);
void AST_unop_print(FILE *, int, AST_unop);

void AST_expr_print(FILE *, int, AST_expr);
void AST_exprlist_print(FILE *, int, AST_exprlist);
void AST_variable_print(FILE *, int, AST_variable);
void AST_assingment_print(FILE *, int, AST_assignment);
void AST_global_var_declaration_print(FILE *, int, AST_global_var_declaration);
void AST_init_variabledef_print(FILE *, int , AST_init_variabledef);
void AST_enum_dcl_print(FILE *, int, AST_enum_dcl);
void AST_id_print(FILE *, int, AST_id);
void AST_init_value_print(FILE *, int, AST_init_value);
void AST_switch_tail_print(FILE *, int, AST_switch_tail);
void AST_decl_cases_print(FILE *, int, AST_decl_cases);
void AST_casestmt_print(FILE *, int, AST_casestmt);
void AST_stmt_print(FILE *, int, AST_stmt);
void AST_general_expr_print(FILE *, int, AST_general_expr);
void AST_class_dcl_print(FILE *, int, AST_class_dcl);
void AST_class_body_print(FILE *, int, AST_class_body);
void AST_members_method_print(FILE *, int, AST_members_method);
void AST_member_or_method_print(FILE *, int, AST_member_or_method);
void AST_short_func_dcl_print(FILE *, int, AST_short_func_dcl);
void AST_union_dcl_print(FILE *, int, AST_union_dcl);
void AST_member_print(FILE *, int, AST_member);
void AST_declaration_print(FILE *, int, AST_declaration);
void AST_var_declaration_print(FILE *, int, AST_var_declaration);
void AST_parameter_print(FILE *, int, AST_parameter);
void AST_passvar_print(FILE *, int, AST_passvar);
       
void AST_typedef_print(FILE *, int, AST_typedef);
void AST_class_func_header_start_print(FILE *, int, AST_class_func_header_start);
void AST_func_header_start_print(FILE *, int, AST_func_header_start);
void AST_variabledef_print(FILE *, int, AST_variabledef);
void AST_constant_print(FILE *, int, AST_constant);
void AST_full_par_func_header_print(FILE *, int, AST_full_par_func_header);
void AST_full_func_dcl_print(FILE *, int, AST_full_func_dcl);
void AST_dcl_stmt_print(FILE *, int, AST_dcl_stmt);
void AST_func_dcl_print(FILE *, int, AST_func_dcl);

void AST_program_print(FILE *, int, AST_program);
void List_print(FILE *, int, List);

void start_program(FILE *, int);

#endif