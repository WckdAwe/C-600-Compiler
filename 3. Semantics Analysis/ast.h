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
typedef struct AST_program_tag                  * AST_program;
typedef struct AST_global_decl_tag              * AST_global_decl;
typedef struct AST_variable_tag                 * AST_variable;
typedef struct AST_assignment_tag               * AST_assignment;
typedef struct AST_global_var_declaration_tag   * AST_global_var_declaration;
typedef struct AST_init_variabledef_tag         * AST_init_variabledef;
typedef struct AST_enum_dcl_tag                 * AST_enum_dcl;
typedef struct AST_id_tag                       * AST_id;
typedef struct AST_init_value_tag               * AST_init_value;
typedef struct AST_expr_tag                     * AST_expr;
typedef struct AST_switch_tail_tag              * AST_switch_tail;
typedef struct AST_decl_cases_tag               * AST_decl_cases;
typedef struct AST_casestmt_tag                 * AST_casestmt;
typedef struct AST_stmt_tag                     * AST_stmt;
typedef struct AST_general_expr_tag             * AST_general_expr;
typedef struct AST_class_dcl_tag                * AST_class_dcl;
typedef struct AST_class_body_tag               * AST_class_body;
typedef struct AST_members_method_tag           * AST_members_method;
typedef struct AST_member_or_method_tag         * AST_member_or_method;
typedef struct AST_short_func_dcl_tag           * AST_short_func_dcl;
typedef struct AST_union_dcl_tag                * AST_union_dcl;
typedef struct AST_member_tag                   * AST_member;
typedef struct AST_declaration_tag              * AST_declaration;
typedef struct AST_var_declaration_tag          * AST_var_declaration;
typedef struct AST_parameter_tag                * AST_parameter;              
typedef struct AST_passvar_tag                  * AST_passvar;
typedef struct AST_typedef_tag                  * AST_typedef;
typedef struct AST_class_func_header_start_tag  * AST_class_func_header_start;
typedef struct AST_func_header_start_tag        * AST_func_header_start;
typedef struct AST_variabledef_tag              * AST_variabledef;
typedef struct AST_constant_tag                 * AST_constant;
typedef struct AST_full_par_func_header_tag     * AST_full_par_func_header;
typedef struct AST_full_func_dcl_tag            * AST_full_func_dcl;
typedef struct AST_dcl_stmt_tag                 * AST_dcl_stmt;
typedef struct AST_func_dcl_tag                 * AST_func_dcl; 
typedef struct AST_exprlist_tag                 * AST_exprlist;

typedef struct List_tag                 * List;  // TODO: Extract to library?


typedef enum access_enum{
    ACCESS_PRIVATE,
    ACCESS_PROTECTED,
    ACCESS_PUBLIC,
    ACCESS_DEFAULT,
} Access;


typedef enum {
    ast_unop_plus,
    ast_unop_minus,
    ast_unop_not,
    ast_unop_sizeop,
    ast_unop_inc,
    ast_unop_dec,
    
} AST_unop;

typedef enum {
    ast_binop_plus,
    ast_binop_minus,
    ast_binop_times,
    ast_binop_div,
    ast_binop_mod,
    ast_binop_eq,
    ast_binop_ne,
    ast_binop_lt,
    ast_binop_gt,
    ast_binop_le,
    ast_binop_ge,
    ast_binop_and,
    ast_binop_or,
} AST_binop;

struct AST_expr_tag {
    enum{
        EXPR_unop,
        EXPR_binop,
        EXPR_call,  
        EXPR_incdec,
        EXPR_variable,
        EXPR_constant,
        EXPR_type,
        EXPR_new,
        EXPR_general_expr,
        EXPR_list_expr,
    } kind;
    union {
        struct{
            AST_unop op;
            AST_expr expr;
        } e_unop;
        struct{
            AST_expr expr1;
            AST_binop op;
            AST_expr expr2;
        } e_binop;
        struct{
            AST_variable variable;
            AST_exprlist list;
        } e_call;
        struct{
            AST_general_expr general_expr;
        } e_call_length;
        struct{
            AST_variable variable;
            AST_unop op;
        } e_incdec;
        struct{
            AST_variable variable;
        } e_variable;
        struct{
            AST_constant constant;
        } e_constant;
        struct{
            Type type;
        } e_type;
        struct{
            AST_general_expr general_expr;
        } e_new;
        struct{
            AST_general_expr general_expr;
        } e_general_expr;
        struct{
            AST_exprlist exprlist;
        } e_listexpr;
    } u;
    int lineno;
}; 

struct AST_exprlist_tag{
    enum{
        EXPRLIST_general,
        EXPRLIST_empty
    } kind;
    union {
        struct{
            AST_general_expr general_expr;
        } e_general;
    } u;
    int lineno;
};

struct AST_global_decl_tag{
    enum{
        GDCL_TYPEDEF,
        GDCL_ENUM,
        GDCL_CLASS,
        GDCL_UNION,
        GDCL_GLOBAL_VAR,
        GDCL_FUNC,
    } kind;
    union{
        struct{
            AST_typedef typedef_dcl;
        } g_typedef;
        struct{
            AST_enum_dcl enum_dcl;
        } g_enum;
        struct{
            AST_class_dcl class_dcl;
        } g_class;
        struct{
            AST_union_dcl union_dcl;
        } g_union;
        struct{
            AST_global_var_declaration global_var_dcl;
        } g_global_var;
        struct{
            AST_func_dcl func_dcl;
        } g_func;
    } u;

    int lineno;
};


/* Απαριθμήσεις τελεστών */
struct AST_variable_tag{
    // ABSTRACT
    enum{
        VARIABLE_LIST,
        VARIABLE_NESTED,
        VARIABLE_LISTFUNC,
        VARIABLE_DEFINITION,
        VARIABLE_THIS,
    } kind;
    union{
        struct{
            AST_variable variable;
            AST_general_expr general_expr;
        } list;
        struct{
            AST_variable variable;
            Identifier id;
        } nested;
        struct{
            AST_general_expr general_expr;
        } listfunc;
        struct{
            int is_static;
            Identifier id;
        } definition;
    } u;

    int lineno;
};

struct AST_assignment_tag{
    enum{
        ASSIGNMENT_EXPR,
        ASSIGNMENT_VAR,
    } kind;
    union{
        struct{
            AST_expr expr;
        } expr;
        struct{
            AST_variable variable;
            AST_assignment assignment;
        } var;
    } u;
    int lineno;
};

struct AST_global_var_declaration_tag{
    Type typename;
    List init_variabledefs;
    int lineno;
};

struct AST_init_variabledef_tag{
    AST_variabledef variabledef;
    AST_init_value init_value;
    int lineno;
};

struct AST_enum_dcl_tag{
    Identifier id;
    List id_list;
    int lineno;
};


struct AST_id_tag{
    Identifier id;
    AST_init_value init_value;
    int lineno;
};

struct AST_init_value_tag{
    enum{
        INIT_SINGLE,
        INIT_MULTI,
        INIT_DEFAULT,
    } kind;
    union{
        struct{
            AST_expr expr;
        } single;
        struct{
            List list_of_exprs;
        } multi;
    } u;
    int lineno;
};

struct AST_switch_tail_tag{
    enum{
        SWITCH_SINGLE_CASE,
        SWITCH_DECL_CASES,
    } kind;
    union{
        struct{
            AST_casestmt casestmt;
        } single_case;
        struct{
            AST_decl_cases decl_cases;
        } decl_cases;
    } u;
};

struct AST_decl_cases_tag{
    enum{
        DC_BOTH,
        DC_DECLARATION_ONLY,
        DC_CASE_ONLY,
        DC_EMPTY,
    } kind;
    union{
        struct{
            List declarations;
            List casestmts; 
        } both;
        struct{
            List dcls_or_stmts;
        } single;
    } u;
    int lineno;
};

struct AST_casestmt_tag{
    enum{
        CASE_DEFAULT,
        CASE_NEXTCASE,
        CASE_SINGLE_STMT,
        CASE_MULTI_STMT,
    } kind;
    union{
        struct{
            List stmts;
        } c_default;
        struct{
            AST_constant constant;
            AST_casestmt casestmt;
        } c_nextcase;
        struct{
            AST_constant constant;
            AST_stmt stmt;
        } c_single_stmt;
        struct{
            AST_constant constant;
            List stmts;
        } c_multi_stmt;
    } u;
    int lineno;
};

struct AST_stmt_tag{
    enum{
        STMT_EXPR,
        STMT_IF,
        STMT_WHILE,
        STMT_FOR,
        STMT_SWITCH,
        STMT_RETURN,
        STMT_INPUT,
        STMT_OUTPUT,
        STMT_COMP,
        STMT_CONTINUE,
        STMT_BREAK,
        STMT_SEMI // ? | Nothing
    } kind;
    union{
        struct{
            AST_general_expr general_expr;
        } general_expr;
        struct{
            AST_general_expr general_expr;
            AST_stmt stmt;
            AST_stmt if_tail;
        } if_stmt;
        struct{
            AST_general_expr general_expr;
            AST_stmt stmt;
        } while_stmt;
        struct{
            AST_general_expr optexpr1; // Can be NULL
            AST_general_expr optexpr2;
            AST_general_expr optexpr3;
            AST_stmt stmt;
        } for_stmt;
        struct{
            AST_general_expr general_expr;
            AST_switch_tail switch_tail;
        } switch_stmt;
        struct{
            AST_general_expr optexpr;
        } return_stmt;
        struct{
            List io_list;
        } io_stmt;
        struct{
            AST_dcl_stmt dcl_stmt;
        } comp_stmt;
    } u;
    int lineno;
};

struct AST_general_expr_tag{
    enum{
        GEXPR_GEXPR,
        GEXPR_ASSIGNMENT,
    } kind;
    union{
        struct{
            AST_general_expr general_expr1;
            AST_general_expr general_expr2;
        } gexpr;
        struct{
            AST_assignment assignment;
        } assignment;
    } u;
    int lineno;
};

struct AST_class_dcl_tag{
    Identifier id;
    AST_class_body class_body;
    int lineno;
};

struct AST_class_body_tag{
    Identifier parent;
    List members_methods;
    int lineno;
};

struct AST_members_method_tag{
    Access access;
    AST_member_or_method mom;
    int lineno;
};

struct AST_member_or_method_tag{
    enum{
        MOM_MEMBER,
        MOM_METHOD,
    } kind;
    union{
        AST_short_func_dcl method;          // CHECH THIS!!!!!!!! probably needs structs
        AST_member member;
    } u;
    int lineno;
};

struct AST_short_func_dcl_tag{
    enum{
        SHORT_FUNC_NO_PARAMS,
        SHORT_FUNC_WITH_PARAMS,
    } kind;
    AST_func_header_start func_header_start;
    List parameters;
    int lineno;
};

struct AST_union_dcl_tag{
    Identifier id;
    List union_fields;
    int lineno;
};

struct AST_member_tag{
    enum{
        MEMBER_VARIABLE,
        MEMBER_ANON_UNION,
    } kind;
    union{
        AST_var_declaration var_declaration;
        List union_fields;
    } u;
    int lineno;
};

struct AST_declaration_tag{
    Type typename;
    int is_static;
    List list;
    int lineno;
};

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

struct AST_full_par_func_header_tag{
    enum{
        FPF_NOCLASS,
        FPF_CLASS,
    } kind;
    union{
        struct{
            AST_func_header_start header;
        } fpf_noclass;
        struct{
            AST_class_func_header_start header;
        } fpf_class;
    }u;
    List parameters;
    int lineno;
};

struct AST_full_func_dcl_tag{
    enum{
        FFD_NOPAR,
        FFD_NOPAR_CLASS,
        FFD_FULL_PAR,
    } kind;
    union{
        struct{
            AST_func_header_start header;
        } nopar;
        struct{
            AST_class_func_header_start header;
        } nopar_class;
        struct{
            AST_full_par_func_header header;
        } full_par;
    }u;
    AST_dcl_stmt statements;
    int lineno;
};

struct AST_dcl_stmt_tag{
    enum{
        DCL_STMT_STMTS,
        DCL_STMT_DCLS,
        DCL_STMT_STMTS_DCLS,
        DCL_STMT_EMPTY
    } kind;
    union{
        struct{
            List statements;
        } dcl_stmt_stmts;
        struct{
            List declares;
        } dcl_stmt_dcls;
        struct{
            List statements;
            List declares;
        } dcl_stmt_stmts_dcls;
    } u;
    int lineno;
};

struct AST_func_dcl_tag{
    enum{
        FD_SHORT,
        FD_FULL
    } kind;
    union{
        struct{
            AST_short_func_dcl func;
        } fd_short;
        struct{
            AST_full_func_dcl func;
        } fd_full;
    } u;
    int lineno;
};

struct AST_program_tag{
    List gdcl_list;
    AST_dcl_stmt dcl_stmts;
    int lineno;
};

struct List_tag{
    void *data;
    List next;
};

// struct AST_expr_list_tag {
//     AST_expr head;
//     AST_expr_list tail;
//     int lineno;
// };


AST_general_expr ast_gexpr_gexpr(AST_general_expr general_expr1, AST_general_expr general_expr2);
AST_general_expr ast_gexpr_assignment(AST_assignment assignment);
AST_variable ast_variable_list(AST_variable variable, AST_general_expr general_expr);
AST_variable ast_variable_nested(AST_variable variable, Identifier id);
AST_variable ast_variable_listfunc(AST_general_expr general_expr);
AST_variable ast_variable_definition(int is_static, Identifier id);
AST_variable ast_variable_this();
AST_assignment ast_assignment_var(AST_variable variable, AST_assignment assignment);
AST_assignment ast_assignment_expr(AST_expr expr);
AST_global_var_declaration ast_global_var_declaration(Type typename, List init_variabledefs);
AST_init_variabledef ast_init_variabledef(AST_variabledef variabledef, AST_init_value init_value);
AST_enum_dcl ast_enum_dcl(Identifier id, List id_list);
AST_id ast_id(Identifier id, AST_init_value init_value);
AST_init_value ast_init_value_default();
AST_init_value ast_init_value_multi(List list_of_exprs);
AST_init_value ast_init_value_single(AST_expr expr);
AST_stmt ast_comp_stmt(AST_dcl_stmt dcl_stmt);
AST_stmt ast_switch_stmt(AST_general_expr general_expr, AST_switch_tail switch_tail);
AST_switch_tail ast_switch_tail_decl(AST_decl_cases decl_case);
AST_switch_tail ast_switch_tail_single(AST_casestmt casestmt);
AST_decl_cases ast_decl_cases_empty();
AST_decl_cases ast_decl_cases_single(int type, List list);
AST_decl_cases ast_decl_cases_both(List declarations, List casestmts);
AST_casestmt ast_casestmt_multi(AST_constant constant, List stmts);
AST_casestmt ast_casestmt_single(AST_constant constant, AST_stmt stmt);
AST_casestmt ast_casestmt_nextcase(AST_constant constant, AST_casestmt casestmt);
AST_casestmt ast_casestmt_default(List stmts);
AST_stmt ast_io_stmt(int in_or_out, List list);
AST_stmt ast_expr_stmt(AST_general_expr general_expr);
AST_stmt ast_return_stmt(AST_general_expr optexpr);
AST_stmt ast_stmt_basic(int stmt_kind);
AST_stmt ast_for_stmt(AST_general_expr optexpr1, AST_general_expr optexpr2, AST_general_expr optexpr3, AST_stmt stmt);
AST_stmt ast_while_stmt(AST_general_expr general_expr, AST_stmt stmt);
AST_stmt ast_if_stmt(AST_general_expr general_expr, AST_stmt stmt, AST_stmt if_tail);
AST_class_dcl ast_class_dcl(Identifier id, AST_class_body class_body);
AST_class_body ast_class_body(Identifier parent, List members_methods);
AST_members_method ast_members_method(Access access, AST_member_or_method mom);
AST_member_or_method ast_mom_method(AST_short_func_dcl method);
AST_member_or_method ast_mom_member(AST_member member);
AST_short_func_dcl ast_short_func_dcl(AST_func_header_start func_header_start, List parameters);
AST_union_dcl ast_union_dcl(Identifier id, List union_fields);
AST_member ast_member_anon_union(List union_fields);
AST_member ast_member_variable(AST_var_declaration var_declaration);
AST_declaration ast_declaration(Type typename, int is_static, List list);
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
AST_full_par_func_header ast_full_par_func_header_class(AST_class_func_header_start h, List p);
AST_full_par_func_header ast_full_par_func_header_noclass(AST_func_header_start h, List p);
AST_full_func_dcl ast_full_func_dcl_full_par(AST_full_par_func_header h, AST_dcl_stmt s);
AST_full_func_dcl ast_full_func_dcl_nopar_class(AST_class_func_header_start h, AST_dcl_stmt s);
AST_full_func_dcl ast_full_func_dcl_nopar(AST_func_header_start h, AST_dcl_stmt s);
AST_dcl_stmt ast_dcl_stmt_dcls_stmts(List d, List s);
AST_dcl_stmt ast_dcl_stmt_dcls(List d);
AST_dcl_stmt ast_dcl_stmt_stmts(List s);
AST_dcl_stmt ast_dcl_stmt_empty();
AST_func_dcl ast_func_dcl_short(AST_short_func_dcl s);
AST_func_dcl ast_func_dcl_full(AST_full_func_dcl f);
AST_expr ast_expr_new_binop_AND(AST_expr exp1, AST_expr exp2);
AST_expr ast_expr_new_binop_OR(AST_expr exp1, AST_expr exp2);
AST_expr ast_expr_new_binop_EQ(AST_expr exp1, AST_expr exp2);
AST_expr ast_expr_new_binop_REL(AST_expr exp1, char *op, AST_expr exp2);
AST_expr ast_expr_new_binop_ADD(AST_expr exp1, char *op, AST_expr exp2);
AST_expr ast_expr_new_binop_MUL(AST_expr exp1, char *op, AST_expr exp2);
AST_expr ast_expr_unop(char *op, AST_expr expr);
AST_expr ast_expr_incdec(char *op, AST_variable variable);
AST_expr ast_expr_variable(AST_variable variable);
AST_expr ast_expr_func(AST_variable variable, AST_exprlist expression_list);
AST_expr ast_expr_length(AST_general_expr general_expression);
AST_expr ast_expr_constant(AST_constant constant);
AST_expr ast_expr_standardtype(Type type);
AST_expr ast_expr_new(AST_general_expr general_expr);
AST_expr ast_expr_general_expr(AST_general_expr general_expr);
AST_expr ast_expr_listexpr(AST_exprlist expr_list);
AST_exprlist ast_exprlist_general(AST_general_expr general_expr);
AST_global_decl ast_gdcl_typedef(AST_typedef typedef_dcl);
AST_global_decl ast_gdcl_enum(AST_enum_dcl enum_dcl);
AST_global_decl ast_gdcl_class(AST_class_dcl class_dcl);
AST_global_decl ast_gdcl_union(AST_union_dcl union_dcl);
AST_global_decl ast_gdcl_gvar(AST_global_var_declaration gvar);
AST_global_decl ast_gdcl_func(AST_func_dcl func_dcl);
AST_program ast_program(List gdcl_list, AST_dcl_stmt dcl_stmt);

List list_add(List list, void *data);
void list_reverse(List *head);

Type set_list_or_typename(Type list, Type typename);
Type set_list_or_array_or_typename(Type list, Type array, Type typename);
void set_array_type(Type array, Type type);
Type get_parameter_type(Type typename, Type pass_list_dims);

#endif

