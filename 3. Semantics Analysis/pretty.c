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
            Type_print(f, prec+1, e->type);
            AST_unop_print(f, prec+1, e->u.e_unop.op);
            AST_expr_print(f, prec+1, e->u.e_unop.expr);
            indent(f, prec); fprintf(f, ")\n");
            break;
        case EXPR_binop:
            fprintf(f, "ast_expr: binop(\n");
            Type_print(f, prec+1, e->type);
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
    AST_variabledef_list(f, prec+1, g->init_variabledefs);
    indent(f, prec); fprintf(f, ")\n");
}

void AST_init_variabledef_print(FILE* f, int prec, AST_init_variabledef v){
    indent(f, prec);
    if (v == NULL) {
        fprintf(f, "<<NULL>>\n");
        return;
    }
    fprintf(f, "Type: init variabledef");
    AST_variabledef_print(f, prec+1, v->variabledef);
    AST_init_value_print(f, prec+1, v->init_value);
    indent(f, prec); fprintf(f, ")\n");
}