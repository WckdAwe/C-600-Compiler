#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#ifndef __AST_H__
#define __AST_H__



/* ---------------------------------------------------------------------
   ------------------------- Ορισμός τύπων -----------------------------
   --------------------------------------------------------------------- */

/* Δηλώσεις */

typedef struct AST_program_tag * AST_program;
typedef struct AST_letdef_tag  * AST_letdef;
typedef struct AST_typedef_tag * AST_typedef;
typedef struct AST_def_tag     * AST_def;
typedef struct AST_tdef_tag    * AST_tdef;
typedef struct AST_constr_tag  * AST_constr;
typedef struct AST_par_tag     * AST_par;
typedef struct AST_expr_tag    * AST_expr;
typedef struct AST_clause_tag  * AST_clause;
typedef struct AST_pattern_tag * AST_pattern;

typedef struct AST_ltdef_list_tag   * AST_ltdef_list;
typedef struct AST_def_list_tag     * AST_def_list;
typedef struct AST_tdef_list_tag    * AST_tdef_list;
typedef struct AST_constr_list_tag  * AST_constr_list;
typedef struct AST_par_list_tag     * AST_par_list;
typedef struct AST_expr_list_tag    * AST_expr_list;
typedef struct AST_clause_list_tag  * AST_clause_list;
typedef struct AST_pattern_list_tag * AST_pattern_list;

typedef struct Type_list_tag * Type_list;


/* Απαριθμήσεις τελεστών */


typedef enum{
	ast_unop_plus,
	ast_unop_minus,
	ast_unop_not,
	ast_unop_inc,
	ast_unop_dec,
	//might need to add more	
}AST_unop;

typedef enum {
    ast_binop_plus,
    ast_binop_minus,
    ast_binop_times,
    ast_binop_div,
    ast_binop_fplus,
    ast_binop_fminus,
    ast_binop_ftimes,
    ast_binop_fdiv,
    ast_binop_mod,
    ast_binop_exp,
    ast_binop_eq,
    ast_binop_ne,
    ast_binop_lt,
    ast_binop_gt,
    ast_binop_le,
    ast_binop_ge,
    ast_binop_pheq,   //do we need this ?
    ast_binop_phne,	  //do we need this ?
    ast_binop_and,
    ast_binop_or,
    ast_binop_semicolon,
    ast_binop_assign
} AST_binop;

//First symbol of c++600
typedef struct AST_program_tag{
	AST_ltdef_list list;
	int lineno;
};

//change name ?
struct AST_letdef_tag{
	bool recFlag; //do we need this?
	AST_def_list list;
	int lineno;
};

struct AST_typedef_tag {
    AST_tdef_list list;
    int lineno;
};

struct AST_def_tag {
    enum {
        DEF_normal,
        DEF_mutable,
    } kind;
    union {
        struct {
            Identifier id;
            AST_par_list list;
            Type type;
            AST_expr expr;
        } d_normal;
        struct {
            Identifier id;
            AST_expr_list list;
            Type type;
        } d_mutable; // change name?
    } u;
    int lineno;
    SymbolEntry entry;
};

struct AST_tdef_tag {
    Identifier id;
    AST_constr_list list;
    int lineno;
};

struct AST_constr_tag {
    Identifier id;
    Type_list list;
    int lineno;
};

struct AST_par_tag {
    Identifier id;
    Type type;
    int lineno;
};

struct AST_expr_tag {
    enum {
        EXPR_iconst,
        EXPR_fconst,
        EXPR_cconst,
        EXPR_strlit, // do we need this?
        EXPR_true,
        EXPR_false,
        EXPR_unit,
        EXPR_unop,
        EXPR_binop,
        EXPR_id,
        EXPR_Id,
        //EXPR_call,
        //EXPR_Call,
       // EXPR_arrel,
        EXPR_dim,
        EXPR_new,
        EXPR_delete,
        //EXPR_let,
        EXPR_if,
        EXPR_while,
        EXPR_for,
        //EXPR_match, //check what we need and what we dont
        EXPR_class
    } kind;
    union {
        struct {
            int rep;
        } e_iconst;
        struct {
            float rep;
        } e_fconst;
        struct {
            char rep;
        } e_cconst;
        struct {
            char* rep;
        } e_strlit;
        struct {
            AST_unop op;
            AST_expr expr;
        } e_unop;
        struct {
            AST_expr expr1;
            AST_binop op;
            AST_expr expr2;
        } e_binop;
        struct {
            Identifier id;
        } e_id;
        struct {
            Identifier id;
        } e_Id;
        struct {
            Identifier id;
            AST_expr_list list;
        } e_call;
        struct {
            Identifier id;
            AST_expr_list list;
        } e_Call;
        struct {
            Identifier id;
            AST_expr_list list;
        } e_arrel;
        struct {
            int dim;
            Identifier id;
        } e_dim;
        struct {
            Type type;
        } e_new;
        struct {
            AST_expr expr;
        } e_delete;
        struct {
            AST_letdef def;
            AST_expr expr;
        } e_let;
        struct {
            AST_expr econd;
            AST_expr ethen;
            AST_expr eelse;
        } e_if;
        struct {
            AST_expr econd;
            AST_expr ebody;
        } e_while;
        struct {
            Identifier id;
            AST_expr expr1;
            bool downFlag;
            AST_expr expr2;
            AST_expr ebody;
        } e_for;
        struct {
            AST_expr expr;
            AST_clause_list list;
        } e_match;
        struct{
            Identifier name;            //Class Name
            TypeList members;          // ex: int i , char c   
            AST_expr_list methods;      // doSomething()
        }e_class;
    } u;
    int lineno;
    Type type;
    SymbolEntry entry;
};

struct AST_clause_tag {
    AST_pattern pattern;
    AST_expr expr;
    int lineno;
};

struct AST_pattern_tag {
    enum {
        PATTERN_iconst, //do we need all the consts?
        PATTERN_fconst,
        PATTERN_cconst, 
        PATTERN_true,
        PATTERN_false,
        PATTERN_id,
        PATTERN_Id
    } kind;
    union {
        struct {
            int rep;
        } p_iconst;
        struct {
            float rep;
        } p_fconst;
        struct {
            char rep;
        } p_cconst;
        struct {
            Identifier id;
        } p_id;
        struct {
            Identifier id;
            AST_pattern_list list;
        } p_Id;
    } u;
    int lineno;
};

struct AST_ltdef_list_tag {
    enum {
        LTDEF_let,
        LTDEF_type
    } kind;
    union {
        AST_letdef  letdef;
        AST_typedef typdef;
    } head;
    AST_ltdef_list tail;
    int lineno;
};

struct AST_def_list_tag {
    AST_def head;
    AST_def_list tail;
    int lineno;
};

struct AST_tdef_list_tag {
    AST_tdef head;
    AST_tdef_list tail;
    int lineno;
};

struct AST_constr_list_tag {
    AST_constr head;
    AST_constr_list tail;
    int lineno;
};

struct AST_par_list_tag {
    AST_par head;
    AST_par_list tail;
    int lineno;
};

struct AST_expr_list_tag {
    AST_expr head;
    AST_expr_list tail;
    int lineno;
};

struct AST_clause_list_tag {
    AST_clause head;
    AST_clause_list tail;
    int lineno;
};

struct AST_pattern_list_tag {
    AST_pattern head;
    AST_pattern_list tail;
    int lineno;
};

struct Type_list_tag {
    Type head;
    Type_list tail;
    int lineno;
};


AST_program ast_program           (AST_ltdef_list l);
AST_letdef  ast_letdef            (bool recFlag, AST_def_list l); 		  //name?
AST_def     ast_def_normal        (Identifier id, AST_par_list l,
        Type t, AST_expr e);
AST_def     ast_def_mutable       (Identifier id, AST_expr_list l, Type t); //name?
AST_typedef ast_typedef           (AST_tdef_list l);
AST_tdef    ast_tdef              (Identifier id, AST_constr_list l);
AST_constr  ast_constr            (Identifier id, Type_list l);
AST_par     ast_par               (Identifier id, Type t);
AST_clause  ast_clause            (AST_pattern p, AST_expr e);

AST_expr ast_expr_iconst (int r);
AST_expr ast_expr_fconst (float r);
AST_expr ast_expr_cconst (char r);
//AST_expr ast_expr_strlit (char* r);
AST_expr ast_expr_true   ();
AST_expr ast_expr_false  ();
AST_expr ast_expr_unit   ();
AST_expr ast_expr_unop   (AST_unop op, AST_expr e);
AST_expr ast_expr_binop  (AST_expr e1, AST_binop op, AST_expr e2);
AST_expr ast_expr_id     (Identifier id);
AST_expr ast_expr_Id     (Identifier id);
// AST_expr ast_expr_call   (Identifier id, AST_expr_list l);
// AST_expr ast_expr_Call   (Identifier id, AST_expr_list l);
// AST_expr ast_expr_arrel  (Identifier id, AST_expr_list l);
AST_expr ast_expr_dim    (int dim, Identifier id);
AST_expr ast_expr_new    (Type t);
AST_expr ast_expr_delete (AST_expr e);
AST_expr ast_expr_let    (AST_letdef ld, AST_expr e);
AST_expr ast_expr_if     (AST_expr ec, AST_expr e1, AST_expr e2);
AST_expr ast_expr_while  (AST_expr ec, AST_expr eb);
AST_expr ast_expr_for    (Identifier id, AST_expr e1, bool down,
        AST_expr e2, AST_expr eb);
// AST_expr ast_expr_match  (AST_expr e, AST_clause_list l);
AST_expr ast_expr_class(Identifier id, Type_list tl, AST_expr_list el);


AST_pattern ast_pattern_iconst (int r);
AST_pattern ast_pattern_fconst (float r);
AST_pattern ast_pattern_cconst (char r);
AST_pattern ast_pattern_true   ();
AST_pattern ast_pattern_false  ();
AST_pattern ast_pattern_id     (Identifier id);
AST_pattern ast_pattern_Id     (Identifier id, AST_pattern_list l);

AST_ltdef_list   ast_ltdef_list_let  (AST_letdef ld  , AST_ltdef_list l);
AST_ltdef_list   ast_ltdef_list_type (AST_typedef td , AST_ltdef_list l);

AST_def_list     ast_def_list        (AST_def d      , AST_def_list l);
AST_tdef_list    ast_tdef_list       (AST_tdef td    , AST_tdef_list l);
AST_constr_list  ast_constr_list     (AST_constr c   , AST_constr_list l);
AST_par_list     ast_par_list        (AST_par p      , AST_par_list l);
AST_expr_list    ast_expr_list       (AST_expr e     , AST_expr_list l);
AST_clause_list  ast_clause_list     (AST_clause c   , AST_clause_list l);
AST_pattern_list ast_pattern_list    (AST_pattern p  , AST_pattern_list l);

Type_list type_list (Type t, Type_list l);

#endif

