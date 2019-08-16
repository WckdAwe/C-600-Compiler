#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "symbol.h"
#include "general.h"

#ifndef __AST_H__
#define __AST_H__



/* ---------------------------------------------------------------------
   ------------------------- Ορισμός τύπων -----------------------------
   --------------------------------------------------------------------- */

/* Δηλώσεις */

// typedef struct AST_program_tag * AST_program;
// typedef struct AST_letdef_tag  * AST_letdef;
// typedef struct AST_typedef_tag * AST_typedef;
// typedef struct AST_def_tag     * AST_def;
// typedef struct AST_tdef_tag    * AST_tdef;
// typedef struct AST_constr_tag  * AST_constr;
// typedef struct AST_par_tag     * AST_par;
// typedef struct AST_expr_tag    * AST_expr;
// typedef struct AST_clause_tag  * AST_clause;

typedef struct AST_var_declaration_tag          * AST_var_declaration;
typedef struct AST_parameter_tag                * AST_parameter;              
typedef struct AST_passvar_tag                  * AST_passvar;
typedef struct AST_typedef_tag                  * AST_typedef;
typedef struct AST_class_func_header_start_tag  * AST_class_func_header_start;
typedef struct AST_func_header_start_tag        * AST_func_header_start;
typedef struct AST_variabledef_tag              * AST_variabledef;
// typedef struct AST_id_type_tag               * AST_id_type;
typedef struct AST_casestatement_tag            * AST_casestatement;
typedef struct AST_constant_tag                 * AST_constant;

typedef struct List_tag                 * List;  // TODO: Extract to library?

// typedef struct AST_ltdef_list_tag   * AST_ltdef_list;
// typedef struct AST_def_list_tag     * AST_def_list;
// typedef struct AST_tdef_list_tag    * AST_tdef_list;
// typedef struct AST_constr_list_tag  * AST_constr_list;
// typedef struct AST_par_list_tag     * AST_par_list;
// typedef struct AST_expr_list_tag    * AST_expr_list;
// typedef struct AST_clause_list_tag  * AST_clause_list;
// typedef struct AST_pattern_list_tag * AST_pattern_list;

// typedef struct Type_list_tag * Type_list;


/* Απαριθμήσεις τελεστών */


// typedef enum{
// 	ast_unop_plus,
// 	ast_unop_minus,
// 	ast_unop_not,
// 	ast_unop_inc,
// 	ast_unop_dec,
// 	//might need to add more	
// }AST_unop;

// typedef enum {
//     ast_binop_plus,
//     ast_binop_minus,
//     ast_binop_times,
//     ast_binop_div,
//     ast_binop_fplus,
//     ast_binop_fminus,
//     ast_binop_ftimes,
//     ast_binop_fdiv,
//     ast_binop_mod,
//     ast_binop_exp,
//     ast_binop_eq,
//     ast_binop_ne,
//     ast_binop_lt,
//     ast_binop_gt,
//     ast_binop_le,
//     ast_binop_ge,
//     ast_binop_pheq,   //do we need this ?
//     ast_binop_phne,	  //do we need this ?
//     ast_binop_and,
//     ast_binop_or,
//     ast_binop_semicolon,
//     ast_binop_assign
// } AST_binop;

// //First symbol of c++600
// typedef struct AST_program_tag{
// 	AST_letdef_list list;
// 	int lineno;
// };

// //change name ?
// struct AST_letdef_tag{
// 	bool recFlag; //do we need this?
// 	AST_def_list list;
// 	int lineno;
// };

// struct AST_def_tag {
//     enum {
//         DEF_normal,
//         DEF_mutable,
//     } kind;
//     union {
//         struct {
//             Identifier id;
//             AST_par_list list;
//             Type type;
//             AST_expr expr;
//         } d_normal;
//         struct {
//             Identifier id;
//             AST_expr_list list;
//             Type type;
//         } d_mutable; // change name?
//     } u;
//     int lineno;
//     SymbolEntry entry;
// };

// struct AST_tdef_tag {
//     Identifier id;
//     AST_constr_list list;
//     int lineno;
// };

// struct AST_constr_tag {
//     Identifier id;
//     Type_list list;
//     int lineno;
// };

// struct AST_par_tag {
//     Identifier id;
//     Type type;
//     int lineno;
// };

// struct AST_expr_tag {
//     enum {
//         EXPR_iconst,
//         EXPR_fconst,
//         EXPR_cconst,
//         EXPR_strlit, // do we need this?
//         EXPR_true,
//         EXPR_false,
//         EXPR_unit,
//         EXPR_unop,
//         EXPR_binop,
//         EXPR_id,
//         EXPR_Id,
//         //EXPR_call,
//         //EXPR_Call,
//        // EXPR_arrel,
//         EXPR_dim,
//         EXPR_new,
//         EXPR_delete,
//         //EXPR_let,
//         EXPR_if,
//         EXPR_while,
//         EXPR_for,
//         //EXPR_match, //check what we need and what we dont
//         EXPR_class
//     } kind;
//     union {
//         struct {
//             int rep;
//         } e_iconst;
//         struct {
//             float rep;
//         } e_fconst;
//         struct {
//             char rep;
//         } e_cconst;
//         struct {
//             char* rep;
//         } e_strlit;
//         struct {
//             AST_unop op;
//             AST_expr expr;
//         } e_unop;
//         struct {
//             AST_expr expr1;
//             AST_binop op;
//             AST_expr expr2;
//         } e_binop;
//         struct {
//             Identifier id;
//         } e_id;
//         struct {
//             Identifier id;
//         } e_Id;
//         struct {
//             Identifier id;
//             AST_expr_list list;
//         } e_call;
//         struct {
//             Identifier id;
//             AST_expr_list list;
//         } e_Call;
//         struct {
//             Identifier id;
//             AST_expr_list list;
//         } e_arrel;
//         struct {
//             int dim;
//             Identifier id;
//         } e_dim;
//         struct {
//             Type type;
//         } e_new;
//         struct {
//             AST_expr expr;
//         } e_delete;
//         struct {
//             AST_letdef def;
//             AST_expr expr;
//         } e_let;
//         struct {
//             AST_expr econd;
//             AST_expr ethen;
//             AST_expr eelse;
//         } e_if;
//         struct {
//             AST_expr econd;
//             AST_expr ebody;
//         } e_while;
//         struct {
//             Identifier id;
//             AST_expr expr1;
//             bool downFlag;
//             AST_expr expr2;
//             AST_expr ebody;
//         } e_for;
//         struct {
//             AST_expr expr;
//             AST_clause_list list;
//         } e_match;
//         struct{
//             Identifier name;            //Class Name
//             AST_expr_list members;          // ex: int i , char c
//             AST_expr_list methods;      // doSomething()
//         }e_class;
//     } u;
//     int lineno;
//     Type type;
//     SymbolEntry entry;
// };

// struct AST_clause_tag {
//     AST_pattern pattern;
//     AST_expr expr;
//     int lineno;
//
// };

struct AST_var_declaration_tag{
    Type typename;
    List list;
    int lineno;
};

struct AST_parameter_tag{
    Type typename;
    AST_passvar passvar;
    int lineno;
};

struct AST_passvar_tag{
    enum{
        PASSVAR_variable,
        PASSVAR_ref
    } kind;
    union{
        AST_variabledef variabledef;
        Type ref;
    }u;
    int lineno;
};

struct AST_typedef_tag{
    Identifier id;
    Type typename;
    int lineno;
};

struct AST_class_func_header_start_tag{
    Type typename;
    Identifier id;
    Identifier class;
    int lineno;
};

struct AST_func_header_start_tag{ // Could merge with item bellow?
    Identifier id;
    Type typename;
    int lineno;
};

struct AST_variabledef_tag{
    Identifier id;
    Type type;
    int lineno;
};

// struct AST_id_type_tag{
//     Identifier id;
//     Type type;
// };

struct AST_casestatement_tag {
    AST_constant constant;
    // AST_expr expr;
    int lineno;
};

struct AST_constant_tag {
    enum {
        CONSTANT_iconst,
        CONSTANT_fconst,
        CONSTANT_cconst,
        CONSTANT_sconst,
    } kind;
    union {
        struct {
            int rep;
        } c_iconst;
        struct {
            float rep;
        } c_fconst;
        struct {
            char rep;
        } c_cconst;
        struct {
            char* rep;
        } c_sconst;
    } u;
    int lineno;
};

struct List_tag{
    void *data;
    List next;
};

AST_var_declaration ast_var_declaration(Type typename, List list);
AST_parameter ast_parameter(Type typename, AST_passvar passvar);
AST_passvar ast_passvar_variable(AST_variabledef variable);
AST_passvar ast_passvar_ref(Identifier id);
AST_typedef ast_typedef(Identifier id, Type typename, Type list, Type array);
AST_class_func_header_start ast_class_func_header_start(Identifier id, Identifier class, Type typename, Type list);
AST_func_header_start ast_func_header_start(Identifier id, Type typename, Type list);
AST_variabledef ast_variabledef(Identifier id, Type list, Type array);
Type ast_dims (Type outer_array, Type inner_array);
AST_constant ast_constant_iconst (int r);
AST_constant ast_constant_fconst (float r);
AST_constant ast_constant_cconst (char r);
AST_constant ast_constant_sconst (char* r);

List list_add(List list, void *data);
void list_reverse(List *head);

Type set_list_or_typename(Type list, Type typename);
Type set_list_or_array_or_typename(Type list, Type array, Type typename);
void set_array_type(Type array, Type type);
#endif

