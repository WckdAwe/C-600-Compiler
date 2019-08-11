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


#ifndef __PRETTY_H__
#define __PRETTY_H__


/* ---------------------------------------------------------------------
   ---------------------------- Header files ---------------------------
   --------------------------------------------------------------------- */

#include <stdio.h>

#include "ast.h"


/* ---------------------------------------------------------------------
   ------------------------ Function prototypes ------------------------
   --------------------------------------------------------------------- */

void Identifier_print       (FILE *, int, Identifier);
void Type_print             (FILE *, int, Type);

void RepInt_print           (FILE *, int, RepInt);
void RepFloat_print         (FILE *, int, RepFloat);
void RepChar_print          (FILE *, int, RepChar);
void RepString_print        (FILE *, int, RepString);

void AST_program_print      (FILE *, int, AST_program);
void AST_letdef_print       (FILE *, int, AST_letdef);
void AST_typedef_print      (FILE *, int, AST_typedef);
void AST_def_print          (FILE *, int, AST_def);
void AST_tdef_print         (FILE *, int, AST_tdef);
void AST_constr_print       (FILE *, int, AST_constr);
void AST_par_print          (FILE *, int, AST_par);
void AST_expr_print         (FILE *, int, AST_expr);
void AST_clause_print       (FILE *, int, AST_clause);
void AST_pattern_print      (FILE *, int, AST_pattern);

void AST_unop_print         (FILE *, int, AST_unop);
void AST_binop_print        (FILE *, int, AST_binop);

void AST_ltdef_list_print   (FILE *, int, AST_ltdef_list);
void AST_def_list_print     (FILE *, int, AST_def_list);
void AST_tdef_list_print    (FILE *, int, AST_tdef_list);
void AST_constr_list_print  (FILE *, int, AST_constr_list);
void AST_par_list_print     (FILE *, int, AST_par_list);
void AST_expr_list_print    (FILE *, int, AST_expr_list);
void AST_clause_list_print  (FILE *, int, AST_clause_list);
void AST_pattern_list_print (FILE *, int, AST_pattern_list);

void Type_list_print        (FILE *, int, Type_list);


#endif
