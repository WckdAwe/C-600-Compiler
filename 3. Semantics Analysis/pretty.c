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

void Access_print(FILE *f, int prec, Access a){
    indent(f, prec);
    switch(a){
        case ACCESS_PRIVATE:
            fprintf(f, "Access private");
            break;
        case ACCESS_PROTECTED:
            fprintf(f, "Access protected");
            break;
        case ACCESS_PUBLIC:
            fprintf(f, "Access public");
            break;
        case ACCESS_DEFAULT:
            fprintf(f, "Access default");
            break;
        default:
            internal("invalid AST");
    }
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
        case EXPR_call:
            fprint(f, "ast_expr:(\n");
            Identifier_print(f, prec+1, e->u.e_call.id);
            AST_expr_list_print(f, prec+1, e->u.e_call.list);
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
            fprintf(f, "ast_variable: variable list(\n");
            AST_variable_print(f, prec+1, v->u.list.variable);
            AST_general_expr_print(f, prec+1, v->u.list.general_expr);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case VARIABLE_NESTED:
            fprintf(f, "ast_variable: variable nested(\n");
            AST_variable_print(f, prec+1, v->u.nested.variable);
            Identifier_print(f, prec+1, v->u.nested.id);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case VARIABLE_LISTFUNC:
            fprintf(f, "ast_variable: variable listfunc(\n");
            AST_general_expr_print(f, prec+1, v->u.listfunc.general_expr);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case VARIABLE_DEFINITION:
            fprintf(f, "ast_variable: variable definition(\n");
            RepInt_print(f, prec+1, v->u.definition.is_static);
            Identifier_print(f, prec+1, v->u.definition.id);
            indent(f, prec); fprintf(f, ")\n");
            break;
        //case VARIABLE_THIS
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
            fprintf(f, "ast_assingment: assingment expr(\n");
            AST_expr_print(f, prec+1, a->u.expr.expr);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case ASSIGNMENT_VAR:
            fprintf(f, "ast_assingment: assingment var(\n");
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
    //AST_init_variabledef_print_list(f, prec+1, g->init_variabledefs);
    List_print(f, prec+1, g->init_variabledefs);
    indent(f, prec); fprintf(f, ")\n");
}

void AST_init_variabledef_print(FILE* f, int prec, AST_init_variabledef v){
    indent(f, prec);
    if (v == NULL) {
        fprintf(f, "<<NULL>>\n");
        return;
    }
    fprintf(f, "Type: ast_init_variabledef(\n");
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
    fprintf(f, "Type: ast_enum_dcl(\n");
    Identifier_print(f, prec+1, e->id);
    //Identifier_list_print(f, prec+1, e->id_list);
    List_print(f, prec+1, e->id_list);
    indent(f, prec); fprintf(f, ")\n");
}

void AST_id_print(FILE *f, int prec, AST_id i){
    indent(f, prec);
    if (i == NULL) {
        fprintf(f, "<<NULL>>\n");
        return;
    }
    fprintf(f, "Type: ast_id(\n");
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
            fprintf(f, "ast_init_value: init single(\n");
            AST_expr_print(f, prec+1, i->u.single.expr);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case INIT_MULTI:
            fprintf(f, "ast_init_value: init multi(\n");
            //AST_expr_list_print(f, prec+1, i->u.multi.list_of_exprs);
            List_print(f, prec+1, i->u.multi.list_of_exprs);
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
            fprintf(f, "ast_switch_tail: single case(\n");
            AST_casestmt_print(f, prec+1, s->u.single_case.casestmt);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case SWITCH_DECL_CASES:
            fprintf(f, "ast_switch_tail: decl case(\n");
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
            fprintf(f, "AST_decl_cases: both(\n");
            //AST_declaration_list_print(f, prec+1, d->u.both.declarations);
            List_print(f, prec+1, d->u.both.declarations);
            //AST_casestmt_list_print(f, prec+1, d->u.both.casestmts);
            List_print(f, prec+1, d->u.both.casestmts);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case DC_DECLARATION_ONLY:
            fprintf(f, "AST_decl_cases: declarations only(\n");
            //AST_declaration_list_print(f, prec+1, d->u.single.dcls_or_stmts);
            List_print(f, prec+1, d->u.single.dcls_or_stmts);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case DC_CASE_ONLY:
            fprintf(f, "AST_decl_cases: case only(\n");
            //AST_casestmt_list_print(f, prec+1, d->u.single.dcls_or_stmts);
            List_print(f, prec+1, d->u.single.dcls_or_stmts);
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
            fprintf(f, "AST_casestmt: case defaulft(\n");
            //AST_stmt_list_print(f, prec+1, c->u.c_default.stmts);
            List_print(f, prec+1, c->u.c_default.stmts);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case CASE_NEXTCASE:
            fprintf(f, "AST_casestmt: case nextcase(\n");
            AST_constant_print(f, prec+1, c->u.c_nextcase.constant);
            AST_casestmt_print(f, prec+1, c->u.c_nextcase.casestmt);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case CASE_SINGLE_STMT:
            fprintf(f, "AST_casestmt: case single stmt(\n");
            AST_constant_print(f, prec+1, c->u.c_single_stmt.constant);
            AST_stmt_print(f, prec+1, c->u.c_single_stmt.stmt);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case CASE_MULTI_STMT:
            fprintf(f, "AST_casestmt: case multi stmt(\n");
            AST_constant_print(f, prec+1, c->u.c_multi_stmt.constant);
            //AST_stmt_list_print(f, prec+1, c->u.c_multi_stmt.stmts);
            List_print(f, prec+1, c->u.c_multi_stmt.stmts);
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
            fprintf(f, "AST_stmt: stmt expr(\n");
            AST_general_expr_print(f, prec+1, s->u.general_expr.general_expr);
            indent(f, prec); fprintf(f, ")\n");
            break; 
        case STMT_IF:
            fprintf(f, "AST_stmt: stmt if(\n");
            AST_general_expr_print(f, prec+1, s->u.if_stmt.general_expr);
            AST_stmt_print(f, prec+1, s->u.if_stmt.stmt);
            AST_stmt_print(f, prec+1, s->u.if_stmt.if_tail);
            indent(f, prec); fprintf(f, ")\n");
            break; 
        case STMT_WHILE:
            fprintf(f, "AST_stmt: stmt while(\n");
            AST_general_expr_print(f, prec+1, s->u.while_stmt.general_expr);
            AST_stmt_print(f, prec+1, s->u.if_stmt.stmt);
            indent(f, prec); fprintf(f, ")\n");
            break; 
        case STMT_FOR:
            fprintf(f, "AST_stmt: stmt for(\n");
            AST_general_expr_print(f, prec+1, s->u.for_stmt.optexpr1);
            AST_general_expr_print(f, prec+1, s->u.for_stmt.optexpr2);
            AST_general_expr_print(f, prec+1, s->u.for_stmt.optexpr3);
            AST_stmt_print(f, prec+1, s->u.for_stmt.stmt);
            indent(f, prec); fprintf(f, ")\n");
            break; 
        case STMT_SWITCH:
            fprintf(f, "AST_stmt: stmt switch(\n");
            AST_general_expr_print(f, prec+1, s->u.switch_stmt.general_expr);
            AST_switch_tail_print(f, prec+1, s->u.switch_stmt.switch_tail);
            indent(f, prec); fprintf(f, ")\n");
            break; 
        case STMT_RETURN:
            fprintf(f, "AST_stmt: stmt return(\n");
            AST_general_expr_print(f, prec+1, s->u.return_stmt.optexpr);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case STMT_OUTPUT:
            fprintf(f, "AST_stmt: stmt output(\n");
            //AST_stmt_list_print(f, prec+1, s->u.io_stmt);
            List_print(f, prec+1,s->u.io_stmt.io_list);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case STMT_COMP:
            fprintf(f, "AST_stmt: stmt comp(\n");
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
            fprintf(f, "AST_general_expr: gexpr gexpr(\n");
            AST_general_expr_print(f, prec+1, g->u.gexpr.general_expr1);
            AST_general_expr_print(f, prec+1, g->u.gexpr.general_expr2);
            indent(f, prec); fprintf(f, ")\n");
            break; 
        case GEXPR_ASSIGNMENT: 
            fprintf(f, "AST_general_expr: gexpr assingment(\n");
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
    fprintf(f, "Type: AST_class_dcl(\n");
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
    fprintf(f, "Type: AST_class_body(\n");
    Identifier_print(f, prec+1, c->parent);
    //AST_members_method_list_print(f, prec+1, c->members_methods);
    List_print(f, prec+1, c->members_methods);
    indent(f, prec); fprintf(f, ")\n");
}

void AST_members_method_print(FILE *f, int prec, AST_members_method m){
    indent(f, prec);
    if(m == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    fprint(f, "Type: AST_members_method(\n");
    Access_print(f, prec+1, m->access);
    AST_member_or_method_print(f, prec+1, m->mom);
    indent(f, prec); fprintf(f, ")\n");
}

void AST_member_or_method_print(FILE *f, int prec, AST_member_or_method m){
    indent(f, prec);
    if(m == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    switch(m->kind){
        case MOM_MEMBER:
            fprintf(f, "AST_member_or_method: mom mebmer(\n");
            AST_short_func_dcl_print(f, prec+1, m->u.method);
            AST_member_print(f, prec+1, m->u.member);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case MOM_METHOD:
            fprintf(f, "AST_member_or_method: mom method(\n");
            AST_short_func_dcl_print(f, prec+1, m->u.method);
            AST_member_print(f, prec+1, m->u.member);
            indent(f, prec); fprintf(f, ")\n");
            break;
        default:
            internal("Invalid AST");
    }

}

void AST_short_func_dcl_print(FILE *f, int prec, AST_short_func_dcl s){
    indent(f, prec);
    if(s == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    switch(s->kind){
        case SHORT_FUNC_NO_PARAMS:
            fprintf(f, "short_func_dcl: short func no params(\n");
            AST_func_header_start_print(f, prec+1, s->func_header_start);
            AST_parameter_list(f, prec+1, s->parameters);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case SHORT_FUNC_WITH_PARAMS:
            fprintf(f, "short_func_dcl: short func with params(\n");
            AST_func_header_start_print(f, prec+1, s->func_header_start);
            //AST_parameter_list(f, prec+1, s->parameters);
            List_print(f, prec+1, s->parameters);
            indent(f, prec); fprintf(f, ")\n");
            break;
        default:
            internal("Invalid AST");
    }
}

void AST_union_dcl_print(FILE *f, int prec, AST_union_dcl u){
    fprintf(f, "Type: AST_union_dcl(\n");
    Identifier_print(f, prec+1, u->id);
    //AST_var_declaration_list_print(f, prec+1, u->union_fields);
    List_print(f, prec+1, u->union_fields);
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
            fprintf(f, "AST_member: member variable(\n");
            AST_var_declaration_print(f, prec+1, m->u.var_declaration);
            //AST_var_declaration_list_print(f, prec+1, m->u.union_fields);
            List_print(f, prec+1, m->u.union_fields);
            indent(f, prec); fprintf(f, ")\n");
            break;  
        case MEMBER_ANON_UNION:
            fprintf(f, "AST_member: member anon union(\n");
            AST_var_declaration_print(f, prec+1, m->u.var_declaration);
            //AST_var_declaration_list_print(f, prec+1, m->u.union_fields);
            List_print(f, prec+1, m->u.union_fields);
            indent(f, prec); fprintf(f, ")\n");
            break;
        default:
            internal("Invalid AST");
    }
}

void AST_declaration_print(FILE *f, int prec, AST_declaration d){
    indent(f, prec);
    if(d == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }

    fprintf(f, "Type: AST_declaration(\n");
    Type_print(f, prec+1, d->typename);
    RepInt_print(f, prec+1, d->is_static);
    //AST_declaration_list_print(f, prec+1, d->list);
    List_print(f, prec+1, d->list);
    indent(f, prec); fprintf(f, ")\n");
}

void AST_var_declaration_print(FILE *f, int prec, AST_var_declaration v){
    indent(f, prec);
    if(v == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }

    fprintf(f, "Type: AST var declaration");
    Type_print(f, prec+1, v->typename);
    //AST_var_declaration_list_print(f, prec+1, v->list);
    List_print(f, prec+1, v->list);
    indent(f, prec); fprintf(f, ")\n");
}

void AST_parameter_print(FILE *f, int prec, AST_parameter p){
    indent(f, prec);
    if(p == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }

    fprintf(f, "Type: AST parameter(\n");
    Type_print(f, prec+1, p->typename);
    AST_passvar_print(f, prec+1, p->passvar);
    indent(f, prec); fprintf(f, ")\n");
}

void AST_passvar_print(FILE *f, int prec, AST_passvar p){
    indent(f, prec);
    if(p == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    switch(p->kind){
        case PASSVAR_variable:
            fprintf(f, "passvar: passvar variable(\n");
            AST_variabledef_print(f, prec+1, p->u.variabledef);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case PASSVAR_ref:
            fprintf(f, "passvar: passvar ref(\n");
            Type_print(f, prec+1, p->u.ref);
            indent(f, prec); fprintf(f, ")\n");
            break;
        default:
            interval("Invalid AST");
    }   
       
}

void AST_typedef_print(FILE *f, int prec, AST_typedef t ){
    indent(f, prec);
    if(t == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    fprintf(f, "Type: AST_typedef(\n");
    Identifier_print(f, prec+1, t->id);
    Type_print(f, prec+1, t->typename);
    indent(f, prec); fprintf(f, ")\n");
}

void AST_class_func_header_start_print(FILE *f, int prec, AST_class_func_header_start c){
    indent(f, prec);
    if(c == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    fprintf(f, "Type: class_func_header_start(\n");
    Type_print(f, prec+1, c->typename);
    Identifier_print(f, prec+1, c->id);
    Identifier_print(f, prec+1, c->class);
    indent(f, prec); fprintf(f, ")\n");
}

void AST_func_header_start_print(FILE *f, int prec, AST_func_header_start h){
    indent(f, prec);
    if(h == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    fprintf(f, "Type: AST_class_func_header_start(\n");
    Identifier_print(f, prec+1, h->id);
    Type_print(f, prec+1, h->typename);
    indent(f, prec); fprintf(f, ")\n");
}

void AST_variabledef_print(FILE *f, int prec, AST_variabledef v){
    indent(f, prec);
    if(v == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    fprintf(f, "Type: AST_variabledef(\n");
    Identifier_print(f, prec+1, v->id);
    Type_print(f, prec+1, v->type);
    indent(f, prec); fprintf(f, ")\n");
}

void AST_constant_print(FILE *f, int prec, AST_constant c){
    indent(f, prec);
    if(c == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    switch(c->kind){
        case CONSTANT_iconst:
            fprintf(f, "constant: iconst(\n");
            RepInt_print(f, prec+1, c->u.c_iconst.rep);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case CONSTANT_fconst:
            fprintf(f, "constant: fconst(\n");
            RepFloat_print(f, prec+1, c->u.c_fconst.rep);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case CONSTANT_cconst:
            fprintf(f, "constant: cconst(\n");
            RepChar_print(f, prec+1, c->u.c_cconst.rep);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case CONSTANT_sconst:
            fprintf(f, "constant: sconst(\n");
            RepString_print(f, prec+1, c->u.c_sconst.rep);
            indent(f, prec); fprintf(f, ")\n");
            break;
        default:
            interval("Invalid AST");
    }

}

void AST_full_par_func_header_print(FILE *f, int prec, AST_full_par_func_header h){
    indent(f, prec);
    if(h == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    switch(h->kind){
        case FPF_NOCLASS:
            fprintf(f, "AST_full_par_func_header: fpf noclass(\n");
            AST_func_header_start_print(f, prec+1, h->u.fpf_noclass.header);
            //AST_parameter_list_print(f, prec+1, h->parameters);
            List_print(f, prec+1, h->parameters);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case FPF_CLASS:
            fprintf(f, "AST_full_par_func_header: fpf class(\n");
            AST_class_func_header_start_print(f, prec+1, h->u.fpf_class.header);
            //AST_parameter_list_print(f, prec+1, h->parameters);
            List_print(f, prec+1, h->parameters);
            indent(f, prec); fprintf(f, ")\n");
            break;
        default:
            interval("Invalid AST");
    }
}

void AST_full_func_dcl_print(FILE *f, int prec, AST_full_func_dcl d){
    indent(f, prec);
    if(d == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    switch(d->kind){
        case FFD_NOPAR:
            fprintf(f, "AST_full_func_dcl: ffd nopar(\n");
            AST_func_header_start_print(f, prec+1, d->u.nopar.header);
            AST_dcl_stmt_print(f, prec+1, d->statements);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case FFD_NOPAR_CLASS:
            fprintf(f, "AST_full_func_dcl: ffd nopar class(\n");
            AST_class_func_header_start_print(f, prec+1, d->u.nopar_class.header);
            AST_dcl_stmt_print(f, prec+1, d->statements);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case FFD_FULL_PAR:
            fprintf(f, "AST_full_func_dcl: ffd full par(\n");
            AST_full_par_func_header_print(f, prec+1, d->u.full_par.header);
            AST_dcl_stmt_print(f, prec+1, d->statements);
            indent(f, prec); fprintf(f, ")\n");
            break;
        default:
            interval("Invalid AST");
    }
}

void AST_dcl_stmt_print(FILE *f, int prec, AST_dcl_stmt s){
    indent(f, prec);
    if(s == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    switch(s->kind){
        case DCL_STMT_STMTS:
            fprintf(f, "AST_dcl_stmt: dcl stmt stmts(\n");
            //AST_stmt_list_print(f, prec+1, s->u.dcl_stmt_stmts.statements);
            List_print(f, prec+1, s->u.dcl_stmt_stmts.statements);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case DCL_STMT_DCLS:
            fprintf(f, "AST_dcl_stmt: dcl stmt dcls(\n");
            //AST_declaration_list_print(f, prec+1,s->u.dcl_stmt_dcls.declares);
            List_print(f, prec+1,s->u.dcl_stmt_dcls.declares);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case DCL_STMT_STMTS_DCLS:
            fprintf(f, "AST_dcl_stmt: dcl stmt stmts dcls(\n");
            //AST_stmt_list_print(f, prec+1, s->u.dcl_stmt_stmts_dcls.statements);
            List_print(f, prec+1, s->u.dcl_stmt_stmts_dcls.statements);
            //AST_declaration_list_print(f, prec+1, s->u.dcl_stmt_stmts_dcls.declares);
            List_print(f, prec+1, s->u.dcl_stmt_stmts_dcls.declares);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case DCL_STMT_EMPTY:
            break;
        default: 
            interval("Invalid AST");
    }
}

void AST_func_dcl_print(FILE *f, int prec, AST_func_dcl d){
    indent(f, prec);
    if(d == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    switch(d->kind){
        case FD_SHORT:
            fprintf(f, "AST_func_dcl: dcl fd short(\n");
            AST_short_func_dcl_print(f, prec+1, d->u.fd_short.func);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case FD_FULL:
            fprintf(f, "AST_func_dcl: dcl fd full(\n");
            AST_full_func_dcl_print(f, prec+1, d->u.fd_short.func);
            indent(f, prec); fprintf(f, ")\n");
            break;           
        default: 
            interval("Invalid AST");
    }
}

void List_print(FILE *f, int prec, List l){
    indent(f, prec);
    if(l == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    fprintf(f, "list(\n");
    //RepString_print(f, prec+1, l->data); 
    Type_print(f, prec+1, l->data);         //TODO: check this !
    List_print(f, prec+1, l->next);
    indent(f, prec); fprintf(f, ")\n");
}

void AST_expr_list_print(FILE *f, int prec, AST_expr_list l){
   indent(f, prec);
    if(l == NULL){
        fprintf(f, "<<NULL>>\n");
        return;
    }
    fprintf(f, "AST_expr_list(\n");
    AST_expr_head_print(f, prec+1, l->head);
    AST_expr_list_print(f, prec+1, l->tail);
    indent(f, prec); fprintf(f, ")\n");
}