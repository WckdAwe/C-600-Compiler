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

#endif
