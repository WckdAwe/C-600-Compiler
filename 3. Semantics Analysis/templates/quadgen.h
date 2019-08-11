/******************************************************************************
 *  CVS version:
 *     $Id: pretty.h,v 1.2 2005/04/07 11:22:47 nickie Exp $
 ******************************************************************************
 *
 *  C header file : pretty.h
 *  Project       : Llama Compiler
 *  Version       : 1.0 alpha
 *  Description   : Pretty printer for abstract syntax
 *
 *  Comments: (in Greek iso-8859-7)
 *  ---------
 *  Εθνικό Μετσόβιο Πολυτεχνείο.
 *  Σχολή Ηλεκτρολόγων Μηχανικών και Μηχανικών Υπολογιστών.
 *  Τομέας Τεχνολογίας Πληροφορικής και Υπολογιστών.
 *  Εργαστήριο Τεχνολογίας Λογισμικού
 */


#ifndef __SEMANTIC_H__
#define __SEMANTIC_H__


/* ---------------------------------------------------------------------
   ---------------------------- Header files ---------------------------
   --------------------------------------------------------------------- */

#include <stdio.h>

#include "ast.h"
#include "symbol.h"
#include "quad.h"


/* ---------------------------------------------------------------------
   ------------------------ Function prototypes ------------------------
   --------------------------------------------------------------------- */

void          AST_program_quad_generate       (AST_program);
void          AST_letdef_quad_generate        (AST_letdef);
void          AST_def_quad_generate           (AST_def);
Type          AST_par_quad_generate           (AST_par);
Quad_operand  AST_expr_quad_generate          (AST_expr);
void          AST_clause_quad_generate        (AST_clause, Type);
void          AST_pattern_quad_generate       (AST_pattern, Type);

Quad_operand  AST_unop_quad_generate          (AST_unop, Quad_operand);
Quad_operand  AST_binop_quad_generate         (Quad_operand, AST_expr, Quad_operand);

void          AST_ltdef_list_quad_generate    (AST_ltdef_list);
void          AST_def_list_quad_generate      (AST_def_list);
Type          AST_par_list_quad_generate      (AST_par_list);
void          AST_expr_list_quad_generate     (AST_expr_list);
void          AST_clause_list_quad_generate   (AST_clause_list, Type);
void          AST_pattern_list_quad_generate  (AST_pattern_list, Type);

int           AST_expr_list_count             (AST_expr_list);

Type          Type_list_quad_generate         (Type_list);


#endif
