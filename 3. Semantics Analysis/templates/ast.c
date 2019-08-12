/******************************************************************************
 *  CVS version:
 *     $Id: ast.c,v 1.2 2005/04/07 11:22:47 nickie Exp $
 ******************************************************************************
 *
 *  C code file : ast.c
 *  Project     : Llama Compiler
 *  Version     : 1.0 alpha
 *  Description : Abstract syntax
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

#include "ast.h"

extern int lineno;

/* ---------------------------------------------------------------------
   --------------------- Υλοποίηση συναρτήσεων -------------------------
   --------------------------------------------------------------------- */

AST_program ast_program(AST_ltdef_list l) {
    AST_program result = new(sizeof(*result));
    result->list = l;
    result->lineno = lineno;
    return result;
}

AST_letdef ast_letdef(bool recFlag, AST_def_list l) {
    AST_letdef result = new(sizeof(*result));
    result->recFlag = recFlag;
    result->list = l;
    result->lineno = lineno;
    return result;
}

AST_def ast_def_normal(Identifier id, AST_par_list l, Type t, AST_expr e) {
    AST_def result = new(sizeof(*result));
    result->kind = DEF_normal;
    result->u.d_normal.id = id;
    result->u.d_normal.list = l;
    result->u.d_normal.type = t;
    result->u.d_normal.expr = e;
    result->lineno = lineno;
    return result;
}

AST_def ast_def_mutable(Identifier id, AST_expr_list l, Type t) {
    AST_def result = new(sizeof(*result));
    result->kind = DEF_mutable;
    result->u.d_mutable.id = id;
    result->u.d_mutable.list = l;
    result->u.d_mutable.type = t;
    result->lineno = lineno;
    return result;
}

AST_typedef ast_typedef(AST_tdef_list l) {
    AST_typedef result = new(sizeof(*result));
    result->list = l;
    result->lineno = lineno;
    return result;
}

AST_tdef ast_tdef(Identifier id, AST_constr_list l) {
    AST_tdef result = new(sizeof(*result));
    result->id = id;
    result->list = l;
    result->lineno = lineno;
    return result;
}

AST_constr ast_constr(Identifier id, Type_list l) {
    AST_constr result = new(sizeof(*result));
    result->id = id;
    result->list = l;
    result->lineno = lineno;
    return result;
}

AST_par ast_par(Identifier id, Type t) {
    AST_par result = new(sizeof(*result));
    result->id = id;
    result->type = t;
    result->lineno = lineno;
    return result;
}

AST_clause ast_clause(AST_pattern p, AST_expr e) {
    AST_clause result = new(sizeof(*result));
    result->pattern = p;
    result->expr = e;
    result->lineno = lineno;
    return result;
}

AST_expr ast_expr_iconst(int r) {
    AST_expr result = new(sizeof(*result));
    result->kind = EXPR_iconst;
    result->u.e_iconst.rep = r;
    result->lineno = lineno;
    result->type = type_int();
    return result;
}

AST_expr ast_expr_fconst(float r) {
    AST_expr result = new(sizeof(*result));
    result->kind = EXPR_fconst;
    result->u.e_fconst.rep = r;
    result->lineno = lineno;
    result->type = type_float();
    return result;
}

AST_expr ast_expr_cconst(char r) {
    AST_expr result = new(sizeof(*result));
    result->kind = EXPR_cconst;
    result->u.e_cconst.rep = r;
    result->lineno = lineno;
    result->type = type_char();
    return result;
}

AST_expr ast_expr_strlit(char* r) {
    AST_expr result = new(sizeof(*result));
    result->kind = EXPR_strlit;
    result->u.e_strlit.rep = r;
    result->lineno = lineno;
    result->type = type_array(1, type_char());
    return result;
}

AST_expr ast_expr_true(void) {
    AST_expr result = new(sizeof(*result));
    result->kind = EXPR_true;
    result->lineno = lineno;
    result->type = type_bool();
    return result;
}

AST_expr ast_expr_false(void) {
    AST_expr result = new(sizeof(*result));
    result->kind = EXPR_false;
    result->lineno = lineno;
    result->type = type_bool();
    return result;
}

AST_expr ast_expr_unit(void) {
    AST_expr result = new(sizeof(*result));
    result->kind = EXPR_unit;
    result->lineno = lineno;
    result->type = type_unit();
    return result;
}

AST_expr ast_expr_unop(AST_unop op, AST_expr e) {
    AST_expr result = new(sizeof(*result));
    result->kind = EXPR_unop;
    result->u.e_unop.op = op;
    result->u.e_unop.expr = e;
    result->lineno = lineno;
    return result;
}

AST_expr ast_expr_binop(AST_expr e1, AST_binop op, AST_expr e2) {
    AST_expr result = new(sizeof(*result));
    result->kind = EXPR_binop;
    result->u.e_binop.op = op;
    result->u.e_binop.expr1 = e1;
    result->u.e_binop.expr2 = e2;
    result->lineno = lineno;
    return result;
}

AST_expr ast_expr_id(Identifier id) {
    AST_expr result = new(sizeof(*result));
    result->kind = EXPR_id;
    result->u.e_id.id = id;
    result->lineno = lineno;
    return result;
}

AST_expr ast_expr_Id(Identifier id) {
    AST_expr result = new(sizeof(*result));
    result->kind = EXPR_Id;
    result->u.e_Id.id = id;
    result->lineno = lineno;
    return result;
}

AST_expr ast_expr_call(Identifier id, AST_expr_list l) {
    AST_expr result = new(sizeof(*result));
    result->kind = EXPR_call;
    result->u.e_call.id = id;
    result->u.e_call.list = l;
    result->lineno = lineno;
    return result;
}

AST_expr ast_expr_Call(Identifier id, AST_expr_list l) {
    AST_expr result = new(sizeof(*result));
    result->kind = EXPR_Call;
    result->u.e_Call.id = id;
    result->u.e_Call.list = l;
    result->lineno = lineno;
    return result;
}

AST_expr ast_expr_arrel(Identifier id, AST_expr_list l) {
    AST_expr result = new(sizeof(*result));
    result->kind = EXPR_arrel;
    result->u.e_arrel.id = id;
    result->u.e_arrel.list = l;
    result->lineno = lineno;
    return result;
}

AST_expr ast_expr_dim(int dim, Identifier id) {
    AST_expr result = new(sizeof(*result));
    result->kind = EXPR_dim;
    result->u.e_dim.dim = dim;
    result->u.e_dim.id = id;
    result->lineno = lineno;
    return result;
}

AST_expr ast_expr_new(Type t) {
    AST_expr result = new(sizeof(*result));
    result->kind = EXPR_new;
    result->u.e_new.type = t;
    result->lineno = lineno;
    return result;
}

AST_expr ast_expr_delete(AST_expr e) {
    AST_expr result = new(sizeof(*result));
    result->kind = EXPR_delete;
    result->u.e_delete.expr = e;
    result->lineno = lineno;
    return result;
}

AST_expr ast_expr_let(AST_letdef ld, AST_expr e) {
    AST_expr result = new(sizeof(*result));
    result->kind = EXPR_let;
    result->u.e_let.def = ld;
    result->u.e_let.expr = e;
    result->lineno = lineno;
    return result;
}

AST_expr ast_expr_if(AST_expr ec, AST_expr e1, AST_expr e2) {
    AST_expr result = new(sizeof(*result));
    result->kind = EXPR_if;
    result->u.e_if.econd = ec;
    result->u.e_if.ethen = e1;
    result->u.e_if.eelse = e2;
    result->lineno = lineno;
    return result;
}

AST_expr ast_expr_while(AST_expr ec, AST_expr eb) {
    AST_expr result = new(sizeof(*result));
    result->kind = EXPR_while;
    result->u.e_while.econd = ec;
    result->u.e_while.ebody = eb;
    result->lineno = lineno;
    return result;
}

AST_expr ast_expr_for(Identifier id, AST_expr e1, bool down,
        AST_expr e2, AST_expr eb) {
    AST_expr result = new(sizeof(*result));
    result->kind = EXPR_for;
    result->u.e_for.id = id;
    result->u.e_for.expr1 = e1;
    result->u.e_for.downFlag = down;
    result->u.e_for.expr2 = e2;
    result->u.e_for.ebody = eb;
    result->lineno = lineno;
    return result;
}

AST_expr ast_expr_match(AST_expr e, AST_clause_list l) {
    AST_expr result = new(sizeof(*result));
    result->kind = EXPR_match;
    result->u.e_match.expr = e;
    result->u.e_match.list = l;
    result->lineno = lineno;
    return result;
}



AST_pattern ast_pattern_iconst(int r) {
    AST_pattern result = new(sizeof(*result));
    result->kind = PATTERN_iconst;
    result->u.p_iconst.rep = r;
    result->lineno = lineno;
    return result;
}

AST_pattern ast_pattern_fconst(float r) {
    AST_pattern result = new(sizeof(*result));
    result->kind = PATTERN_fconst;
    result->u.p_fconst.rep = r;
    result->lineno = lineno;
    return result;
}

AST_pattern ast_pattern_cconst(char r) {
    AST_pattern result = new(sizeof(*result));
    result->kind = PATTERN_cconst;
    result->u.p_cconst.rep = r;
    result->lineno = lineno;
    return result;
}

AST_pattern ast_pattern_true(void) {
    AST_pattern result = new(sizeof(*result));
    result->kind = PATTERN_true;
    result->lineno = lineno;
    return result;
}

AST_pattern ast_pattern_false(void) {
    AST_pattern result = new(sizeof(*result));
    result->kind = PATTERN_false;
    result->lineno = lineno;
    return result;
}

AST_pattern ast_pattern_id(Identifier id) {
    AST_pattern result = new(sizeof(*result));
    result->kind = PATTERN_id;
    result->u.p_id.id = id;
    result->lineno = lineno;
    return result;
}

AST_pattern ast_pattern_Id(Identifier id, AST_pattern_list l) {
    AST_pattern result = new(sizeof(*result));
    result->kind = PATTERN_Id;
    result->u.p_Id.id = id;
    result->u.p_Id.list = l;
    result->lineno = lineno;
    return result;
}



AST_ltdef_list ast_ltdef_list_let(AST_letdef ld, AST_ltdef_list l) {
    AST_ltdef_list result = new(sizeof(*result));
    result->kind = LTDEF_let;
    result->head.letdef = ld;
    result->tail = l;
    result->lineno = lineno;
    return result;
}

AST_ltdef_list ast_ltdef_list_type(AST_typedef td, AST_ltdef_list l) {
    AST_ltdef_list result = new(sizeof(*result));
    result->kind = LTDEF_type;
    result->head.typdef = td;
    result->tail = l;
    result->lineno = lineno;
    return result;
}

AST_def_list ast_def_list(AST_def d, AST_def_list l) {
    AST_def_list result = new(sizeof(*result));
    result->head = d;
    result->tail = l;
    result->lineno = lineno;
    return result;
}

AST_tdef_list ast_tdef_list(AST_tdef td, AST_tdef_list l) {
    AST_tdef_list result = new(sizeof(*result));
    result->head = td;
    result->tail = l;
    result->lineno = lineno;
    return result;
}

AST_constr_list ast_constr_list(AST_constr c, AST_constr_list l) {
    AST_constr_list result = new(sizeof(*result));
    result->head = c;
    result->tail = l;
    result->lineno = lineno;
    return result;
}

AST_par_list ast_par_list(AST_par p, AST_par_list l) {
    AST_par_list result = new(sizeof(*result));
    result->head = p;
    result->tail = l;
    result->lineno = lineno;
    return result;
}

AST_expr_list ast_expr_list(AST_expr e, AST_expr_list l) {
    AST_expr_list result = new(sizeof(*result));
    result->head = e;
    result->tail = l;
    result->lineno = lineno;
    return result;
}

AST_clause_list ast_clause_list(AST_clause c, AST_clause_list l) {
    AST_clause_list result = new(sizeof(*result));
    result->head = c;
    result->tail = l;
    result->lineno = lineno;
    return result;
}

AST_pattern_list ast_pattern_list(AST_pattern p, AST_pattern_list l) {
    AST_pattern_list result = new(sizeof(*result));
    result->head = p;
    result->tail = l;
    result->lineno = lineno;
    return result;
}

Type_list type_list(Type t, Type_list l) {
    Type_list result = new(sizeof(*result));
    result->head = t;
    result->tail = l;
    result->lineno = lineno;
    return result;
}
