#include "ast.h"
#include "error.h"
#include "pretty.h"


static void indent(FILE *f, int n){
    int i;
    for(i=0;i<n;i++)fprintf(f, " ");
}

/* printing functions */

void Identifier_print(FILE *f, int prec, Identifier id){
    indent(f, prec);
    if( id == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    fprintf(f, "Identifier: \%s\"\n", id_name(id));
}

void Type_print(FILE *f, int prec, Type type){
    indent(f, prec);
    if(type == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    switch(type->kind){
        case TYPE_unknown:
            fprintf(f, "Type: unknown");
            break;
        case TYPE_int:
            fprintf(f, "Type: int");
            break;
        case TYPE_float:
            fprintf(f, "Type: float");
            break;
        case TYPE_char:
            fprintf(f, "Type: char");
            break;
        case TYPE_str:
            fprintf(f, "Type: str");
            break;
        case TYPE_void:
            fprintf(f, "Type: void");
            break;
        case TYPE_array:
            fprintf(f, "Type: array (");
            indent(f, prec+1);
            fprintf(f, "dim = %d\n", type->u.t_array.dim);
            Type_print(f, prec+1, type->u.t_array.type);
            indent(f, prec); fprintf(f, ")");
            break;
        case TYPE_enum:
            fprintf(f, "Type: enum");
            break;
        case TYPE_union:
            fprintf(f, "Type: union");
            break;
        case TYPE_list:
            fprintf(f, "Type: list (");
            Type_print(f, prec+1, type->u.t_list.type);
            indent(f, prec); fprintf(f, ")");
            break;
        case TYPE_class:
            fprintf(f, "Type: class (\n");
            Type_print(f, prec+1, type->u.t_class.parent);
            indent(f, prec); fprintf(f, ")");
            break;
        case TYPE_func:
            fprintf(f, "Type: func (\n");
            Type_print(f, prec+1, type->u.t_func.type1);
            Type_print(f, prec+1, type->u.t_func.type2);
            indent(f, prec); fprintf(f, ")");
            break;
        case TYPE_id:
            fprintf(f, "Type: id (\n");
            Identifier_print(f, prec+1, type->u.t_id.id);
            indent(f, prec); fprintf(f, ")\n");
        case TYPE_ref:
            fprintf(f, "Type: ref (\n");
            Type_print(f, prec+1, type->u.t_ref.type);
            indent(f, prec); fprintf(f, ")\n");
        default:
            internal("Invalid AST");
    } 
}

void RepInt_print (FILE * f, int prec, int r)
{
   indent(f, prec);
   fprintf(f, "%d\n", r);
}

void RepFloat_print (FILE * f, int prec, float r)
{
   indent(f, prec);
   fprintf(f, "%f\n", r);
}

void RepChar_print (FILE * f, int prec, char r)
{
   indent(f, prec);
   fprintf(f, "%s\n", r);
}

void RepString_print (FILE * f, int prec, char *r)
{
   indent(f, prec);
   fprintf(f, "%s\n", r);
}

void AST_expr_print(FILE *f, int prec, AST_expr e){
    indent(f, prec);
    if (e == NULL) {
        fprintf(f, "<<NULL>>\n");
        return;
   }
   switch(e->kind){
       case EXPR_unop:
            fprintf(f, "ast_expr: unop(\n");
            AST_unop_print(f, prec+1, e->u.e_unop.op);
            AST_expr_print(f, prec+1, e->u.e_unop.expr);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case EXPR_binop:
            fprintf(f, "ast_expr: binop(\n");
            AST_expr_print(f, prec+1, e->u.e_binop.expr1);
            AST_binop_print(f, prec+1, e->u.e_binop.op);
            AST_expr_print(f, prec+1, e->u.e_binop.expr2);
            indent(f, prec); fprintf(f, ")\n");
            break;
        default:
            internal("invalid AST");
   }

}

void AST_variable_print(FILE *f, int prec, AST_variable v){
    indent(f, prec);
    if (v == NULL) {
        fprintf(f, "<<NULL>>\n");
        return;
    }
    switch(v->kind){
        case VARIABLE_LIST:
            fprintf(f, "ast_variable: variable list");
            AST_variable_print(f, prec+1, v->u.list.variable);
            AST_general_expr_print(f, prec+1, v->u.list.general_expr);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case VARIABLE_NESTED:
            fprintf(f, "ast_variable: variable nested");
            AST_variable_print(f, prec+1, v->u.nested.variable);
            Identifier_print(f, prec+1, v->u.nested.id);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case VARIABLE_LISTFUNC:
            fprintf(f, "ast_variable: variable listfunc");
            AST_general_expr_print(f, prec+1, v->u.listfunc.general_expr);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case VARIABLE_DEFINITION:
            fprintf(f, "ast_variable: variable definition");
            RepInt_print(f, prec+1, v->u.definition.is_static);
            Identifier_print(f, prec+1, v->u.definition.id);
            indent(f, prec); fprintf(f, ")\n");
            break;
        //CASE VARIABLE_THIS
        default:
            internal("invalid AST");
    }

}

void AST_assingment_print(FILE *f, int prec, AST_assignment a){
    indent(f, prec);
    if (a == NULL) {
        fprintf(f, "<<NULL>>\n");
        return;
    }
    switch(a->kind){
        case ASSIGNMENT_EXPR:
            fprintf(f, "ast_assingment: assingment expr");
            AST_expr_print(f, prec+1, a->u.expr.expr);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case ASSIGNMENT_VAR:
            fprintf(f, "ast_assingment: assingment var");
            AST_variable_print(f, prec+1, a->u.var.variable);
            AST_assignment_print(f, prec+1, a->u.var.assignment);
            indent(f, prec); fprintf(f, ")\n");
            break;
        default:
            internal("invalid AST");
    }
    
}


void AST_global_var_declaration_print(FILE *f, int prec, AST_global_var_declaration g){
    indent(f, prec);
    if (g == NULL) {
        fprintf(f, "<<NULL>>\n");
        return;
    }
    fprintf(f, "Type: ast_global_var_declaration");
    AST_type_print(f, prec+1, g->typename);
    ast_init_value_default_print(f, prec+1, g->init_variabledefs);
    indent(f, prec); fprintf(f, ")\n");
}

void AST_init_variabledef_print(FILE* f, int prec, AST_init_variabledef v){
    indent(f, prec);
    if (v == NULL) {
        fprintf(f, "<<NULL>>\n");
        return;
    }
    fprintf(f, "Type: ast_init_variabledef");
    AST_variabledef_print(f, prec+1, v->variabledef);
    AST_init_value_print(f, prec+1, v->init_value);
    indent(f, prec); fprintf(f, ")\n");
}

void AST_enum_dcl_print(FILE *f, int prec, AST_enum_dcl e){
    indent(f, prec);
    if (e == NULL) {
        fprintf(f, "<<NULL>>\n");
        return;
    }
    fprintf(f, "Type: ast_enum_dcl");
    Identifier_print(f, prec+1, e->id);
    Identifier_list_print(f, prec+1, e->id_list);
    indent(f, prec); fprintf(f, ")\n");
}

void AST_id_print(FILE *f, int prec, AST_id i){
    indent(f, prec);
    if (i == NULL) {
        fprintf(f, "<<NULL>>\n");
        return;
    }
    fprintf(f, "Type: ast_id");
    Identifier_print(f, prec+1, i->id);
    AST_init_value_print(f, prec+1, i->init_value);
    indent(f, prec); fprintf(f, ")\n");
}

void AST_init_value_print(FILE *f, int prec, AST_init_value i){
    indent(f, prec);
    if(i == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    switch(i->kind){
        case INIT_SINGLE:
            fprintf(f, "ast_init_value: init single");
            AST_expr_print(f, prec+1, i->u.single.expr);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case INIT_MULTI:
            fprintf(f, "ast_init_value: init multi");
            AST_expr_list_print(f, prec+1, i->u.multi.list_of_exprs);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case INIT_DEFAULT:
            // ?
            break;
        default:
            internal("invalid AST");
    }

}

void AST_switch_tail_print(FILE *f, int prec, AST_switch_tail s){
    indent(f, prec);
    if(s == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    switch (s->kind){
        case SWITCH_SINGLE_CASE:
            fprintf(f, "ast_switch_tail: single case");
            AST_casestmt_print(f, prec+1, s->u.single_case.casestmt);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case SWITCH_DECL_CASES:
            fprintf(f, "ast_switch_tail: decl case");
            AST_decl_cases_print(f, prec+1, s->u.decl_cases.decl_cases);
            indent(f, prec); fprintf(f, ")\n");
            break;
        default:
            internal("Invalid AST");
    }
}

void AST_decl_cases_print(FILE *f, int prec, AST_decl_cases d){
    indent(f, prec);
    if(d == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    switch(d->kind){
        case DC_BOTH:
            fprintf(f, "AST_decl_cases: both");
            AST_decl_cases_list_print(f, prec+1, d->u.both.declarations);
            AST_casestmt_list_print(f, prec+1, d->u.both.casestmts);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case DC_DECLARATION_ONLY:
            fprintf(f, "AST_decl_cases: declarations only");
            AST_decl_cases_list_print(f, prec+1, d->u.single.dcls_or_stmts);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case DC_CASE_ONLY:
            fprintf(f, "AST_decl_cases: declarations only");
            AST_casestmt_list_print(f, prec+1, d->u.single.dcls_or_stmts);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case DC_EMPTY:
            break;
        default:
            internal("Invalid AST");
    }
}

void AST_casestmt_print(FILE *f, int prec, AST_casestmt c){
    indent(f, prec);
    if(c == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    switch(c->kind){
        case CASE_DEFAULT:
            fprintf(f, "AST_casestmt: case defaulft");
            AST_stmt_list_print(f, prec+1, c->u.c_default.stmts);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case CASE_NEXTCASE:
            fprintf(f, "AST_casestmt: case nextcase");
            AST_constant_print(f, prec+1, c->u.c_nextcase.constant);
            AST_casestmt_print(f, prec+1, c->u.c_nextcase.casestmt);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case CASE_SINGLE_STMT:
            fprintf(f, "AST_casestmt: case single stmt");
            indent(f, prec); fprintf(f, ")\n");
            break;
        case CASE_MULTI_STMT:
            fprintf(f, "AST_casestmt: case multi stmt");
            AST_constant_print(f, prec+1, c->u.c_multi_stmt.constant);
            AST_stmt_list_print(f, prec+1, c->u.c_multi_stmt.stmts);
            indent(f, prec); fprintf(f, ")\n");
            break;
        default:
            internal("Invalid AST");
    }
}

void AST_stmt_print(FILE *f, int prec, AST_stmt s){
    indent(f, prec);
    if(s == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    switch(s->kind){
        case STMT_EXPR:
            fprintf(f, "AST_stmt: stmt expr");
            AST_general_expr_print(f, prec+1, s->u.general_expr.general_expr);
            indent(f, prec); fprintf(f, ")\n");
            break; 
        case STMT_IF:
            fprintf(f, "AST_stmt: stmt if");
            AST_general_expr_print(f, prec+1, s->u.if_stmt.general_expr);
            AST_stmt_print(f, prec+1, s->u.if_stmt.stmt);
            AST_stmt_print(f, prec+1, s->u.if_stmt.if_tail);
            indent(f, prec); fprintf(f, ")\n");
            break; 
        case STMT_WHILE:
            fprintf(f, "AST_stmt: stmt while");
            AST_general_expr_print(f, prec+1, s->u.if_stmt.general_expr);
            AST_stmt_print(f, prec+1, s->u.if_stmt.stmt);
            indent(f, prec); fprintf(f, ")\n");
            break; 
        case STMT_FOR:
            fprintf(f, "AST_stmt: stmt for");
            AST_general_expr_print(f, prec+1, s->u.for_stmt.optexpr1);
            AST_general_expr_print(f, prec+1, s->u.for_stmt.optexpr2);
            AST_general_expr_print(f, prec+1, s->u.for_stmt.optexpr3);
            AST_stmt_print(f, prec+1, s->u.for_stmt.stmt);
            indent(f, prec); fprintf(f, ")\n");
            break; 
        case STMT_SWITCH:
            fprintf(f, "AST_stmt: stmt switch");
            AST_general_expr_print(f, prec+1, s->u.switch_stmt.general_expr);
            AST_switch_tail_print(f, prec+1, s->u.switch_stmt.switch_tail);
            indent(f, prec); fprintf(f, ")\n");
            break; 
        case STMT_RETURN:
            fprintf(f, "AST_stmt: stmt switch");
            AST_general_expr_print(f, prec+1, s->u.return_stmt.optexpr);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case STMT_OUTPUT:
            fprintf(f, "AST_stmt: stmt switch");
            AST_io_stmt_list_print(f, prec+1, s->u.io_stmt);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case STMT_COMP:
            fprintf(f, "AST_stmt: stmt switch");
            AST_dcl_stmt_print(f, prec+1, s->u.comp_stmt.dcl_stmt);
            indent(f, prec); fprintf(f, ")\n");
            break;
        //MORE CASES:
        default:
            internal("Invalid AST");
    }   
}


void AST_general_expr_print(FILE *f, int prec, AST_general_expr g){
    indent(f, prec);
    if(g == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    switch(g->kind){
        case GEXPR_GEXPR:
            fprintf(f, "AST_general_expr: gexpr gexpr");
            AST_general_expr_print(f, prec+1, g->u.gexpr.general_expr1);
            AST_assignment_print(f, prec+1, g->u.gexpr.general_expr2);
            indent(f, prec); fprintf(f, ")\n");
            break; 
        case GEXPR_ASSIGNMENT: 
            fprintf(f, "AST_general_expr: gexpr gexpr");
            AST_assignment_print(f, prec+1, g->u.assignment.assignment);
            indent(f, prec); fprintf(f, ")\n");
            break; 
        default:
            internal("Invalid AST");
    }
}

void AST_class_dcl_print(FILE *f, int prec, AST_class_dcl c){
    indent(f, prec);
    if(c == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    fprintf(f, "Type: AST_class_dcl");
    Identifier_print(f, prec+1, c->id);
    AST_class_body_print(f, prec+1, c->class_body);
    indent(f, prec); fprintf(f, ")\n");
}

void AST_class_body_print(FILE *f, int prec, AST_class_body c){
    indent(f, prec);
    if(c == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    fprintf(f, "Type: AST_class_body");
    Identifier_print(f, prec+1, c->parent);
    AST_members_method_list_print(f, prec+1, c->members_methods);
    indent(f, prec); fprintf(f, ")\n");
}

//check this
// void AST_member_or_method_print(FILE *f, int prec, AST_member_or_method m){
//     indent(f, prec);
//     if(m == NULL){
//         fprintf(f, "<<NULL>>\n");
//         return;
//     }
//     switch(m->kind){
//         case MOM_MEMBER:
//             fprintf(f, "AST_mebmer_or_method: mom member");
            
//             indent(f, prec); fprintf(f, ")\n");
//             break;
//     }
// }

void AST_short_func_dcl_print(FILE *f, int prec, AST_short_func_dcl s){
    indent(f, prec);
    if(s == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    switch(s->kind){
        case SHORT_FUNC_NO_PARAMS:
            fprintf(f, "short_func_dcl: short func no params");
            AST_func_header_start_print(f, prec+1, s->func_header_start);
            AST_parameter_list(f, prec+1, s->parameters);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case SHORT_FUNC_WITH_PARAMS:
            fprintf(f, "short_func_dcl: short func with params");
            AST_func_header_start_print(f, prec+1, s->func_header_start);
            AST_parameter_list(f, prec+1, s->parameters);
            indent(f, prec); fprintf(f, ")\n");
            break;
        default:
            internal("Invalid AST");
    }
}

void AST_union_dcl_print(FILE *f, int prec, AST_union_dcl u){
    fprintf(f, "Type: AST_union_dcl");
    Identifier_print(f, prec+1, u->id);
    AST_var_declaration_list_print(f, prec+1, u->union_fields);
    indent(f, prec); fprintf(f, ")\n");    
}

void AST_member_print(FILE *f, int prec, AST_member m){
    indent(f, prec);
    if(m == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    switch(m->kind){
        case MEMBER_VARIABLE:
            fprintf(f, "AST_member: member variable");
            AST_var_declaration_print(f, prec+1, m->u.var_declaration);
            AST_var_declaration_list_print(f, prec+1, m->u.union_fields);
            indent(f, prec); fprintf(f, ")\n");
            break;  
        case MEMBER_ANON_UNION:
            fprintf(f, "AST_member: member anon union");
            AST_var_declaration_print(f, prec+1, m->u.var_declaration);
            AST_var_declaration_list_print(f, prec+1, m->u.union_fields);
            indent(f, prec); fprintf(f, ")\n");
            break;
        default:
            internal("Invalid AST");
    }
}

