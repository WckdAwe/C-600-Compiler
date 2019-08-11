/******************************************************************************
 *  CVS version:
 *     $Id: pretty.c,v 1.3 2005/04/25 12:35:11 nickie Exp $
 ******************************************************************************
 *
 *  C code file : pretty.c
 *  Project     : Llama Compiler
 *  Version     : 1.0 alpha
 *  Description : Pretty printer for abstract syntax
 *
 *  Comments: (in Greek iso-8859-7)
 *  ---------
 *  Εθνικό Μετσόβιο Πολυτεχνείο.
 *  Σχολή Ηλεκτρολόγων Μηχανικών και Μηχανικών Υπολογιστών.
 *  Τομέας Τεχνολογίας Πληροφορικής και Υπολογιστών.
 *  Εργαστήριο Τεχνολογίας Λογισμικού
 */


/* ---------------------------------------------------------------------
   ---------------------------- Header files ---------------------------
   --------------------------------------------------------------------- */

#include "error.h"
#include "ast.h"
#include "pretty.h"


/* ---------------------------------------------------------------------
   ---- Implementation of functions required by the abstract syntax ----
   --------------------------------------------------------------------- */

/* Auxiliary */

static void indent (FILE * f, int n)
{
   int i;

   for (i = 0; i < n; i++)
      fprintf(f, "  ");
}


/* Printing functions */

void Identifier_print (FILE * f, int prec, Identifier id)
{
   indent(f, prec);
   if (id == NULL) {
      fprintf(f, "<<NULL>>\n");
      return;
   }
   fprintf(f, "Identifier: \"%s\"\n", id_name(id));
}

void Type_print (FILE * f, int prec, Type type)
{
   indent(f, prec);
   if (type == NULL) {
      fprintf(f, "<<NULL>>\n");
      return;
   }
   switch (type->kind) {
      case TYPE_unit:
         fprintf(f, "Type: unit");
         break;
      case TYPE_bool:
         fprintf(f, "Type: bool");
         break;
      case TYPE_char:
         fprintf(f, "Type: char");
         break;
      case TYPE_int:
         fprintf(f, "Type: int");
         break;
      case TYPE_float:
         fprintf(f, "Type: float");
         break;
      case TYPE_array:
         fprintf(f, "Type: array (");
         indent(f, prec+1);
         fprintf(f, "dim = %d\n", type->u.t_array.dim);
         Type_print(f, prec+1, type->u.t_array.type);
         indent(f, prec); fprintf(f, ")");
         break;
      case TYPE_ref:
         fprintf(f, "Type: ref (\n");
         Type_print(f, prec+1, type->u.t_ref.type);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case TYPE_func:
         fprintf(f, "Type: func (\n");
         Type_print(f, prec+1, type->u.t_func.type1);
         Type_print(f, prec+1, type->u.t_func.type2);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case TYPE_id:
         fprintf(f, "Type: id (\n");
         Identifier_print(f, prec+1, type->u.t_id.id);
         indent(f, prec); fprintf(f, ")\n");
         break;
      default:
         internal("invalid AST");
   }
}

void RepInt_print (FILE * f, int prec, RepInt r)
{
   indent(f, prec);
   fprintf(f, "%d\n", r);
}

void RepFloat_print (FILE * f, int prec, RepFloat r)
{
   indent(f, prec);
   fprintf(f, "%f\n", r);
}

void RepChar_print (FILE * f, int prec, RepChar r)
{
   indent(f, prec);
   fprintf(f, "%s\n", r);
}

void RepString_print (FILE * f, int prec, RepString r)
{
   indent(f, prec);
   fprintf(f, "%s\n", r);
}

void AST_program_print (FILE * f, int prec, AST_program p)
{
   indent(f, prec);
   if (p == NULL) {
      fprintf(f, "<<NULL>>\n");
      return;
   }
   fprintf(f, "ast_program (\n");
   AST_ltdef_list_print(f, prec+1, p->list);
   indent(f, prec); fprintf(f, ")\n");
}

void AST_letdef_print (FILE * f, int prec, AST_letdef ld)
{
   indent(f, prec);
   if (ld == NULL) {
      fprintf(f, "<<NULL>>\n");
      return;
   }
   fprintf(f, "ast_letdef (\n");
   indent(f, prec+1);
   fprintf(f, "rec = %s\n", ld->recFlag ? "true" : "false");
   AST_def_list_print(f, prec+1, ld->list);
   indent(f, prec); fprintf(f, ")\n");
}

void AST_typedef_print (FILE * f, int prec, AST_typedef td)
{
   indent(f, prec);
   if (td == NULL) {
      fprintf(f, "<<NULL>>\n");
      return;
   }
   fprintf(f, "ast_typedef (\n");
   AST_tdef_list_print(f, prec+1, td->list);
   indent(f, prec); fprintf(f, ")\n");
}

void AST_def_print (FILE * f, int prec, AST_def d)
{
   indent(f, prec);
   if (d == NULL) {
      fprintf(f, "<<NULL>>\n");
      return;
   }
   switch (d->kind) {
      case DEF_normal:
         fprintf(f, "ast_def: normal (\n");
         Identifier_print(f, prec+1, d->u.d_normal.id);
         AST_par_list_print(f, prec+1, d->u.d_normal.list);
         Type_print(f, prec+1, d->u.d_normal.type);
         AST_expr_print(f, prec+1, d->u.d_normal.expr);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case DEF_mutable:
         fprintf(f, "ast_def: mutable (\n");
         Identifier_print(f, prec+1, d->u.d_mutable.id);
         AST_expr_list_print(f, prec+1, d->u.d_mutable.list);
         Type_print(f, prec+1, d->u.d_mutable.type);
         indent(f, prec); fprintf(f, ")\n");
         break;
      default:
         internal("invalid AST");
   }
}

void AST_tdef_print (FILE * f, int prec, AST_tdef td)
{
   indent(f, prec);
   if (td == NULL) {
      fprintf(f, "<<NULL>>\n");
      return;
   }
   fprintf(f, "ast_tdef (\n");
   Identifier_print(f, prec+1, td->id);
   AST_constr_list_print(f, prec+1, td->list);
   indent(f, prec); fprintf(f, ")\n");
}

void AST_constr_print (FILE * f, int prec, AST_constr c)
{
   indent(f, prec);
   if (c == NULL) {
      fprintf(f, "<<NULL>>\n");
      return;
   }
   fprintf(f, "ast_constr (\n");
   Identifier_print(f, prec+1, c->id);
   Type_list_print(f, prec+1, c->list);
   indent(f, prec); fprintf(f, ")\n");
}

void AST_par_print (FILE * f, int prec, AST_par p)
{
   indent(f, prec);
   if (p == NULL) {
      fprintf(f, "<<NULL>>\n");
      return;
   }
   fprintf(f, "ast_par (\n");
   Identifier_print(f, prec+1, p->id);
   Type_print(f, prec+1, p->type);
   indent(f, prec); fprintf(f, ")\n");
}

void AST_expr_print (FILE * f, int prec, AST_expr e)
{
   indent(f, prec);
   if (e == NULL) {
      fprintf(f, "<<NULL>>\n");
      return;
   }
   switch (e->kind) {
      case EXPR_iconst:
         fprintf(f, "ast_expr: iconst (\n");
         RepInt_print(f, prec+1, e->u.e_iconst.rep);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case EXPR_fconst:
         fprintf(f, "ast_expr: fconst (\n");
         RepFloat_print(f, prec+1, e->u.e_fconst.rep);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case EXPR_cconst:
         fprintf(f, "ast_expr: cconst (\n");
         RepChar_print(f, prec+1, e->u.e_cconst.rep);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case EXPR_strlit:
         fprintf(f, "ast_expr: strlit (\n");
         RepString_print(f, prec+1, e->u.e_strlit.rep);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case EXPR_true:
         fprintf(f, "ast_expr: true\n");
         break;
      case EXPR_false:
         fprintf(f, "ast_expr: false\n");
         break;
      case EXPR_unit:
         fprintf(f, "ast_expr: unit\n");
         break;
      case EXPR_unop:
         fprintf(f, "ast_expr: unop (\n");
         AST_unop_print(f, prec+1, e->u.e_unop.op);
         AST_expr_print(f, prec+1, e->u.e_unop.expr);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case EXPR_binop:
         fprintf(f, "ast_expr: binop (\n");
         AST_binop_print(f, prec+1, e->u.e_binop.op);
         AST_expr_print(f, prec+1, e->u.e_binop.expr1);
         AST_expr_print(f, prec+1, e->u.e_binop.expr2);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case EXPR_id:
         fprintf(f, "ast_expr: id (\n");
         Identifier_print(f, prec+1, e->u.e_id.id);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case EXPR_Id:
         fprintf(f, "ast_expr: Id (\n");
         Identifier_print(f, prec+1, e->u.e_Id.id);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case EXPR_call:
         fprintf(f, "ast_expr: call (\n");
         Identifier_print(f, prec+1, e->u.e_call.id);
         AST_expr_list_print(f, prec+1, e->u.e_call.list);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case EXPR_Call:
         fprintf(f, "ast_expr: Call (\n");
         Identifier_print(f, prec+1, e->u.e_Call.id);
         AST_expr_list_print(f, prec+1, e->u.e_Call.list);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case EXPR_arrel:
         fprintf(f, "ast_expr: arrel (\n");
         Identifier_print(f, prec+1, e->u.e_arrel.id);
         AST_expr_list_print(f, prec+1, e->u.e_arrel.list);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case EXPR_dim:
         fprintf(f, "ast_expr: dim (\n");
         indent(f, prec+1);
         fprintf(f, "dim = %d\n", e->u.e_dim.dim);
         Identifier_print(f, prec+1, e->u.e_dim.id);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case EXPR_new:
         fprintf(f, "ast_expr: new (\n");
         Type_print(f, prec+1, e->u.e_new.type);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case EXPR_delete:
         fprintf(f, "ast_expr: delete (\n");
         AST_expr_print(f, prec+1, e->u.e_delete.expr);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case EXPR_let:
         fprintf(f, "ast_expr: let (\n");
         AST_letdef_print(f, prec+1, e->u.e_let.def);
         AST_expr_print(f, prec+1, e->u.e_let.expr);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case EXPR_if:
         fprintf(f, "ast_expr: if (\n");
         AST_expr_print(f, prec+1, e->u.e_if.econd);
         AST_expr_print(f, prec+1, e->u.e_if.ethen);
         AST_expr_print(f, prec+1, e->u.e_if.eelse);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case EXPR_while:
         fprintf(f, "ast_expr: while (\n");
         AST_expr_print(f, prec+1, e->u.e_while.econd);
         AST_expr_print(f, prec+1, e->u.e_while.ebody);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case EXPR_for:
         fprintf(f, "ast_expr: for (\n");
         Identifier_print(f, prec+1, e->u.e_for.id);
         AST_expr_print(f, prec+1, e->u.e_for.expr1);
         indent(f, prec+1);
         fprintf(f, "downFlag = %s\n", e->u.e_for.downFlag ? "true" : "false");
         AST_expr_print(f, prec+1, e->u.e_for.expr2);
         AST_expr_print(f, prec+1, e->u.e_for.ebody);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case EXPR_match:
         fprintf(f, "ast_expr: match (\n");
         AST_expr_print(f, prec+1, e->u.e_match.expr);
         AST_clause_list_print(f, prec+1, e->u.e_match.list);
         indent(f, prec); fprintf(f, ")\n");
         break;
      default:
         internal("invalid AST");
   }
}

void AST_clause_print (FILE * f, int prec, AST_clause c)
{
   indent(f, prec);
   if (c == NULL) {
      fprintf(f, "<<NULL>>\n");
      return;
   }
   fprintf(f, "ast_clause (\n");
   AST_pattern_print(f, prec+1, c->pattern);
   AST_expr_print(f, prec+1, c->expr);
   indent(f, prec); fprintf(f, ")\n");
}

void AST_pattern_print (FILE * f, int prec, AST_pattern p)
{
   indent(f, prec);
   if (p == NULL) {
      fprintf(f, "<<NULL>>\n");
      return;
   }
   switch (p->kind) {
      case PATTERN_iconst:
         fprintf(f, "ast_pattern: iconst (\n");
         RepInt_print(f, prec+1, p->u.p_iconst.rep);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case PATTERN_fconst:
         fprintf(f, "ast_pattern: fconst (\n");
         RepFloat_print(f, prec+1, p->u.p_fconst.rep);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case PATTERN_cconst:
         fprintf(f, "ast_pattern: cconst (\n");
         RepChar_print(f, prec+1, p->u.p_cconst.rep);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case PATTERN_true:
         fprintf(f, "ast_pattern: true\n");
         break;
      case PATTERN_false:
         fprintf(f, "ast_pattern: false\n");
         break;
      case PATTERN_id:
         fprintf(f, "ast_pattern: id (\n");
         Identifier_print(f, prec+1, p->u.p_id.id);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case PATTERN_Id:
         fprintf(f, "ast_pattern: Id (\n");
         Identifier_print(f, prec+1, p->u.p_Id.id);
         AST_pattern_list_print(f, prec+1, p->u.p_Id.list);
         indent(f, prec); fprintf(f, ")\n");
         break;
      default:
         internal("invalid AST");
   }
}

void AST_unop_print (FILE * f, int prec, AST_unop op)
{
   indent(f, prec);
   switch (op) {
      case ast_unop_plus:
         fprintf(f, "ast_unop_plus\n");
         break;
      case ast_unop_minus:
         fprintf(f, "ast_unop_minus\n");
         break;
      case ast_unop_fplus:
         fprintf(f, "ast_unop_fplus\n");
         break;
      case ast_unop_fminus:
         fprintf(f, "ast_unop_fminus\n");
         break;
      case ast_unop_exclam:
         fprintf(f, "ast_unop_exclam\n");
         break;
      case ast_unop_not:
         fprintf(f, "ast_unop_not\n");
         break;
      default:
         internal("invalid AST");
   }
}

void AST_binop_print (FILE * f, int prec, AST_binop op)
{
   indent(f, prec);
   switch (op) {
      case ast_binop_plus:
         fprintf(f, "ast_binop_plus\n");
         break;
      case ast_binop_minus:
         fprintf(f, "ast_binop_minus\n");
         break;
      case ast_binop_times:
         fprintf(f, "ast_binop_times\n");
         break;
      case ast_binop_div:
         fprintf(f, "ast_binop_div\n");
         break;
      case ast_binop_fplus:
         fprintf(f, "ast_binop_fplus\n");
         break;
      case ast_binop_fminus:
         fprintf(f, "ast_binop_fminus\n");
         break;
      case ast_binop_ftimes:
         fprintf(f, "ast_binop_ftimes\n");
         break;
      case ast_binop_fdiv:
         fprintf(f, "ast_binop_fdiv\n");
         break;
      case ast_binop_mod:
         fprintf(f, "ast_binop_mod\n");
         break;
      case ast_binop_exp:
         fprintf(f, "ast_binop_exp\n");
         break;
      case ast_binop_eq:
         fprintf(f, "ast_binop_eq\n");
         break;
      case ast_binop_ne:
         fprintf(f, "ast_binop_ne\n");
         break;
      case ast_binop_lt:
         fprintf(f, "ast_binop_lt\n");
         break;
      case ast_binop_gt:
         fprintf(f, "ast_binop_gt\n");
         break;
      case ast_binop_le:
         fprintf(f, "ast_binop_le\n");
         break;
      case ast_binop_ge:
         fprintf(f, "ast_binop_ge\n");
         break;
      case ast_binop_pheq:
         fprintf(f, "ast_binop_pheq\n");
         break;
      case ast_binop_phne:
         fprintf(f, "ast_binop_phne\n");
         break;
      case ast_binop_and:
         fprintf(f, "ast_binop_and\n");
         break;
      case ast_binop_or:
         fprintf(f, "ast_binop_or\n");
         break;
      case ast_binop_semicolon:
         fprintf(f, "ast_binop_semicolon\n");
         break;
      case ast_binop_assign:
         fprintf(f, "ast_binop_assign\n");
         break;
      default:
         internal("invalid AST");
   }
}

void AST_ltdef_list_print (FILE * f, int prec, AST_ltdef_list l)
{
   indent(f, prec);
   if (l == NULL) {
      fprintf(f, "<<NULL>>\n");
      return;
   }
   switch (l->kind) {
      case LTDEF_let:
         fprintf(f, "ast_ltdef_list: let (\n");
         AST_letdef_print(f, prec+1, l->head.letdef);
         AST_ltdef_list_print(f, prec+1, l->tail);
         indent(f, prec); fprintf(f, ")\n");
         break;
      case LTDEF_type:
         fprintf(f, "ast_ltdef_list: type (\n");
         AST_typedef_print(f, prec+1, l->head.typdef);
         AST_ltdef_list_print(f, prec+1, l->tail);
         indent(f, prec); fprintf(f, ")\n");
         break;
      default:
         internal("invalid AST");
   }
}

void AST_def_list_print (FILE * f, int prec, AST_def_list l)
{
   indent(f, prec);
   if (l == NULL) {
      fprintf(f, "<<NULL>>\n");
      return;
   }
   fprintf(f, "ast_def_list (\n");
   AST_def_print(f, prec+1, l->head);
   AST_def_list_print(f, prec+1, l->tail);
   indent(f, prec); fprintf(f, ")\n");
}

void AST_tdef_list_print (FILE * f, int prec, AST_tdef_list l)
{
   indent(f, prec);
   if (l == NULL) {
      fprintf(f, "<<NULL>>\n");
      return;
   }
   fprintf(f, "ast_tdef_list (\n");
   AST_tdef_print(f, prec+1, l->head);
   AST_tdef_list_print(f, prec+1, l->tail);
   indent(f, prec); fprintf(f, ")\n");
}

void AST_constr_list_print (FILE * f, int prec, AST_constr_list l)
{
   indent(f, prec);
   if (l == NULL) {
      fprintf(f, "<<NULL>>\n");
      return;
   }
   fprintf(f, "ast_constr_list (\n");
   AST_constr_print(f, prec+1, l->head);
   AST_constr_list_print(f, prec+1, l->tail);
   indent(f, prec); fprintf(f, ")\n");
}

void AST_par_list_print (FILE * f, int prec, AST_par_list l)
{
   indent(f, prec);
   if (l == NULL) {
      fprintf(f, "<<NULL>>\n");
      return;
   }
   fprintf(f, "ast_par_list (\n");
   AST_par_print(f, prec+1, l->head);
   AST_par_list_print(f, prec+1, l->tail);
   indent(f, prec); fprintf(f, ")\n");
}

void AST_expr_list_print (FILE * f, int prec, AST_expr_list l)
{
   indent(f, prec);
   if (l == NULL) {
      fprintf(f, "<<NULL>>\n");
      return;
   }
   fprintf(f, "ast_expr_list (\n");
   AST_expr_print(f, prec+1, l->head);
   AST_expr_list_print(f, prec+1, l->tail);
   indent(f, prec); fprintf(f, ")\n");
}

void AST_clause_list_print (FILE * f, int prec, AST_clause_list l)
{
   indent(f, prec);
   if (l == NULL) {
      fprintf(f, "<<NULL>>\n");
      return;
   }
   fprintf(f, "ast_clause_list (\n");
   AST_clause_print(f, prec+1, l->head);
   AST_clause_list_print(f, prec+1, l->tail);
   indent(f, prec); fprintf(f, ")\n");
}

void AST_pattern_list_print (FILE * f, int prec, AST_pattern_list l)
{
   indent(f, prec);
   if (l == NULL) {
      fprintf(f, "<<NULL>>\n");
      return;
   }
   fprintf(f, "ast_par_list (\n");
   AST_pattern_print(f, prec+1, l->head);
   AST_pattern_list_print(f, prec+1, l->tail);
   indent(f, prec); fprintf(f, ")\n");
}

void Type_list_print (FILE * f, int prec, Type_list l)
{
   indent(f, prec);
   if (l == NULL) {
      fprintf(f, "<<NULL>>\n");
      return;
   }
   fprintf(f, "ast_type_list (\n");
   Type_print(f, prec+1, l->head);
   Type_list_print(f, prec+1, l->tail);
   indent(f, prec); fprintf(f, ")\n");
}
