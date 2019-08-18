#include "error.h"
#include "ast.h" 

extern int lineno;

/* ---------------------------------------------------------------------
   --------------------- Υλοποίηση συναρτήσεων -------------------------
   --------------------------------------------------------------------- */
// AST_general_expr ast_general_expr(List list){
//     AST_general_expr result = new(sizeof(*result));
//     result->assignments = result->assignments; 
//     result->lineno = lineno;
//     return result;
// }

AST_general_expr ast_gexpr_gexpr(AST_general_expr general_expr1, AST_general_expr general_expr2){
    AST_general_expr result = new(sizeof(*result));
    result->kind = GEXPR_GEXPR;
    result->u.gexpr.general_expr1 = general_expr1;
    result->u.gexpr.general_expr2 = general_expr2;
    result->lineno = lineno;
    return result;
}

AST_general_expr ast_gexpr_assignment(AST_assignment assignment){
    AST_general_expr result = new(sizeof(*result));
    result->kind = GEXPR_ASSIGNMENT;
    result->u.assignment.assignment = assignment;
    result->lineno = lineno;
    return result;
}

AST_variable ast_variable_list(AST_variable variable, AST_general_expr general_expr){
    AST_variable result = new(sizeof(*result));
    result->kind = VARIABLE_LIST;
    result->u.list.variable = variable;
    result->u.list.general_expr = general_expr;
    result->lineno = lineno;
    return result;
}

AST_variable ast_variable_nested(AST_variable variable, Identifier id){
    AST_variable result = new(sizeof(*result));
    result->kind = VARIABLE_NESTED;
    result->u.nested.id = id;
    result->u.nested.variable = variable;
    result->lineno = lineno;
    return result;
}

AST_variable ast_variable_listfunc(AST_general_expr general_expr){
    AST_variable result = new(sizeof(*result));
    result->kind = VARIABLE_LISTFUNC;
    result->u.listfunc.general_expr = general_expr;
    result->lineno = lineno;
    return result;
}

AST_variable ast_variable_definition(int is_static, Identifier id){
    AST_variable result = new(sizeof(*result));
    result->kind = VARIABLE_DEFINITION;
    result->u.definition.is_static = is_static;
    result->u.definition.id = id;
    result->lineno = lineno;
    return result;
}

AST_variable ast_variable_this(){
    AST_variable result = new(sizeof(*result));
    result->kind = VARIABLE_THIS;
    result->lineno = lineno;
    return result;
}

AST_assignment ast_assignment_var(AST_variable variable, AST_assignment assignment){
    AST_assignment result = new(sizeof(*result));
    result->kind = ASSIGNMENT_VAR;
    result->u.var.variable = variable;
    result->u.var.assignment = assignment;
    result->lineno = lineno;
    return result;
}

AST_assignment ast_assignment_expr(AST_expr expr){
    AST_assignment result = new(sizeof(*result));
    result->kind = ASSIGNMENT_EXPR;
    result->u.expr.expr = expr;
    result->lineno = lineno;
    return result;
}

AST_global_var_declaration ast_global_var_declaration(Type typename, List init_variabledefs){
    AST_global_var_declaration result = new(sizeof(*result));
    result->typename = typename;
    result->init_variabledefs = init_variabledefs;
    result->lineno;
    return result;
}

AST_init_variabledef ast_init_variabledef(AST_variabledef variabledef, AST_init_value init_value){
    AST_init_variabledef result = new(sizeof(*result));
    result->variabledef = variabledef;
    result->init_value = init_value;
    result->lineno = lineno;
    return result;
}

AST_enum_dcl ast_enum_dcl(Identifier id, List id_list){
    AST_enum_dcl result = new(sizeof(*result));
    result->id = id;
    result->id_list = id_list;
    result->lineno = lineno;
    return result;
}

AST_id ast_id(Identifier id, AST_init_value init_value){
    AST_id result = new(sizeof(*result));
    result->id = id;
    result->init_value = init_value;
    result->lineno = lineno;
    return result;
}

AST_init_value ast_init_value_default(){
    AST_init_value result = new(sizeof(*result));
    result->kind = INIT_DEFAULT;
    result->lineno = lineno;
    return result;
}

AST_init_value ast_init_value_multi(List list_of_exprs){
    AST_init_value result = new(sizeof(*result));
    result->kind = INIT_MULTI;
    result->u.multi.list_of_exprs = list_of_exprs;
    result->lineno = lineno;
    return result;
}

AST_init_value ast_init_value_single(AST_expr expr){
    AST_init_value result = new(sizeof(*result));
    result->kind = INIT_SINGLE;
    result->u.single.expr = expr;
    result->lineno = lineno;
    return result;
}

AST_stmt ast_comp_stmt(AST_dcl_stmt dcl_stmt){
    AST_stmt result = new(sizeof(*result));
    result->kind = STMT_COMP;
    result->u.comp_stmt.dcl_stmt = dcl_stmt;
    result->lineno = lineno;
    return result;
}

AST_stmt ast_switch_stmt(AST_general_expr general_expr, AST_switch_tail switch_tail){
    AST_stmt result = new(sizeof(*result));
    result->kind = STMT_SWITCH;
    result->u.switch_stmt.general_expr = general_expr;
    result->u.switch_stmt.switch_tail = switch_tail;
    result->lineno = lineno;
    return result;
}

AST_switch_tail ast_switch_tail_decl(AST_decl_cases decl_case){
    AST_switch_tail result = new(sizeof(*result));
    result->kind = SWITCH_DECL_CASES;
    result->u.decl_cases.decl_cases = decl_case;
    return result;
}

AST_switch_tail ast_switch_tail_single(AST_casestmt casestmt){
    AST_switch_tail result = new(sizeof(*result));
    result->kind = SWITCH_SINGLE_CASE;
    result->u.single_case.casestmt = casestmt; 
    return result;
}

AST_decl_cases ast_decl_cases_empty(){
    AST_decl_cases result = new(sizeof(*result));
    result->kind = DC_EMPTY;
    result->lineno = lineno;
    return result;
}

AST_decl_cases ast_decl_cases_single(int type, List list){
    ASSERT(type == DC_CASE_ONLY || type == DC_DECLARATION_ONLY);
    AST_decl_cases result = new(sizeof(*result));
    result->kind = type;
    result->u.single.dcls_or_stmts = list;
    result->lineno = lineno;
    return result;
}

AST_decl_cases ast_decl_cases_both(List declarations, List casestmts){
    AST_decl_cases result = new(sizeof(*result));
    result->kind = DC_BOTH;
    result->u.both.declarations = declarations;
    result->u.both.casestmts = casestmts;
    result->lineno = lineno;
    return result;
}

AST_casestmt ast_casestmt_multi(AST_constant constant, List stmts){
    AST_casestmt result = new(sizeof(*result));
    result->kind = CASE_MULTI_STMT;
    result->u.c_multi_stmt.constant = constant;
    result->u.c_multi_stmt.stmts = stmts;
    return result;
}

AST_casestmt ast_casestmt_single(AST_constant constant, AST_stmt stmt){
    AST_casestmt result = new(sizeof(*result));
    result->kind = CASE_SINGLE_STMT;
    result->u.c_single_stmt.constant = constant;
    result->u.c_single_stmt.stmt = stmt;
    result->lineno = lineno;
    return result;
}

AST_casestmt ast_casestmt_nextcase(AST_constant constant, AST_casestmt casestmt){
    AST_casestmt result = new(sizeof(*result));
    result->kind = CASE_NEXTCASE;
    result->u.c_nextcase.constant = constant;
    result->u.c_nextcase.casestmt = casestmt;
    result->lineno = lineno;
    return result;
}

AST_casestmt ast_casestmt_default(List stmts){
    AST_casestmt result = new(sizeof(*result));
    result->kind = CASE_DEFAULT;
    result->u.c_default.stmts = stmts;
    result->lineno = lineno;
    return result;
}

AST_stmt ast_io_stmt(int in_or_out, List list){
    ASSERT(in_or_out == STMT_INPUT || in_or_out == STMT_OUTPUT);
    AST_stmt result = new(sizeof(*result));
    result->kind = in_or_out;
    result->u.io_stmt.io_list = list;
    result->lineno = lineno;
    return result;
}

AST_stmt ast_expr_stmt(AST_general_expr general_expr){
    AST_stmt result = new(sizeof(*result));
    result->kind = STMT_EXPR;
    result->u.general_expr.general_expr = general_expr;
    result->lineno = lineno;
    return result;
}

AST_stmt ast_return_stmt(AST_general_expr optexpr){
    AST_stmt result = new(sizeof(*result));
    result->kind = STMT_RETURN;
    result->u.return_stmt.optexpr = optexpr;
    result->lineno = lineno;
    return result;
}

AST_stmt ast_stmt_basic(int stmt_kind){
    ASSERT(stmt_kind == STMT_CONTINUE || stmt_kind == STMT_BREAK || stmt_kind == STMT_SEMI);
    AST_stmt result = new(sizeof(*result));
    result->kind = stmt_kind;
    result->lineno;
    return result;
}

AST_stmt ast_for_stmt(AST_general_expr optexpr1, AST_general_expr optexpr2, AST_general_expr optexpr3, AST_stmt stmt){
    AST_stmt result = new(sizeof(*result));
    result->kind = STMT_FOR;
    result->u.for_stmt.optexpr1 = optexpr1;
    result->u.for_stmt.optexpr2 = optexpr2;
    result->u.for_stmt.optexpr3 = optexpr3;
    result->u.for_stmt.stmt = stmt;
    result->lineno = lineno;
    return result;
}

AST_stmt ast_while_stmt(AST_general_expr general_expr, AST_stmt stmt){
    AST_stmt result = new(sizeof(*result));
    result->kind = STMT_WHILE;
    result->u.while_stmt.general_expr = general_expr;
    result->u.while_stmt.stmt = stmt;
    result->lineno = lineno;
    return result;
}

AST_stmt ast_if_stmt(AST_general_expr general_expr, AST_stmt stmt, AST_stmt if_tail){
    AST_stmt result = new(sizeof(*result));
    result->kind = STMT_IF;
    result->u.if_stmt.general_expr = general_expr;
    result->u.if_stmt.stmt = stmt;
    result->u.if_stmt.if_tail = if_tail;
    result->lineno = lineno;
    return result;
}

AST_class_dcl ast_class_dcl(Identifier id, AST_class_body class_body){
    AST_class_dcl result = new(sizeof(*result));
    result->id = id;
    result->class_body = class_body;
    result->lineno = lineno;
    return result;
}

AST_class_body ast_class_body(Identifier parent, List members_methods){
    AST_class_body result = new(sizeof(*result));
    result->parent = parent;
    result->members_methods = members_methods;
    result->lineno = lineno;
    return result;
}

AST_members_method ast_members_method(Access access, AST_member_or_method mom){
    AST_members_method result = new(sizeof(*result));
    result->access = access;
    result->mom = mom;
    result->lineno = lineno;
    return result;
}

AST_member_or_method ast_mom_method(AST_short_func_dcl method){
    AST_member_or_method result = new(sizeof(*result));
    result->kind = MOM_METHOD;
    result->u.method = method;
    result->lineno = lineno;
    return result;
}

AST_member_or_method ast_mom_member(AST_member member){
    AST_member_or_method result = new(sizeof(*result));
    result->kind = MOM_MEMBER;
    result->u.member = member;
    result->lineno = lineno;
    return result;
}

AST_short_func_dcl ast_short_func_dcl(AST_func_header_start func_header_start, List parameters){
    AST_short_func_dcl result = new(sizeof(*result));
    result->kind = parameters ? SHORT_FUNC_WITH_PARAMS : SHORT_FUNC_NO_PARAMS;
    result->func_header_start = func_header_start;
    result->parameters = parameters;
    result->lineno = lineno;
    return result;
}

AST_union_dcl ast_union_dcl(Identifier id, List union_fields){
    AST_union_dcl result = new(sizeof(*result));
    result->id = id;
    result->union_fields = union_fields;
    result->lineno = lineno;
    return result;
}

AST_member ast_member_anon_union(List union_fields){
    AST_member result = new(sizeof(*result));
    result->kind = MEMBER_ANON_UNION;
    result->u.union_fields = union_fields;
    result->lineno = lineno;
    return result;
}

AST_member ast_member_variable(AST_var_declaration var_declaration){
    AST_member result = new(sizeof(*result));
    result->kind = MEMBER_VARIABLE;
    result->u.var_declaration = var_declaration;
    result->lineno = lineno;
    return result;
}

AST_declaration ast_declaration(Type typename, int is_static, List list){
    AST_declaration result = new(sizeof(*result));
    result->typename = typename;
    result->is_static = is_static;
    result->list = list;
    result->lineno = lineno;
    return result;
}

AST_var_declaration ast_var_declaration(Type typename, List list){
    AST_var_declaration result = new(sizeof(*result));
    result->typename = typename;
    result->list = list;
    result->lineno = lineno;
    return result;
}

AST_parameter ast_parameter(Type typename, AST_passvar passvar){
    AST_parameter result = new(sizeof(*result));
    result->typename = typename;
    result->passvar = passvar;
    result->lineno = lineno;
    return result;    
}

AST_passvar ast_passvar_variable(AST_variabledef variable){
    AST_passvar result = new(sizeof(*result));
    result->kind = PASSVAR_variable;
    result->u.variabledef = variable;
    result->lineno = lineno;
    return result;
}

AST_passvar ast_passvar_ref(Identifier id){
    AST_passvar result = new(sizeof(*result));
    result->kind = PASSVAR_ref;
    result->u.ref = type_ref(type_id(id));
    result->lineno = lineno;
    return result;
}

AST_typedef ast_typedef(Identifier id, Type typename, Type list, Type array){
    AST_typedef result = new(sizeof(*result));
    result->id = id;
    result->typename = set_list_or_array_or_typename(list, array, typename);
    result->lineno = lineno;
    return result;
}

AST_class_func_header_start ast_class_func_header_start(Identifier id, Identifier class, Type typename, Type list){
    AST_class_func_header_start result = new(sizeof(*result));
    result->id = id;
    result->class = class;
    result->typename = set_list_or_typename(list, typename);
    result->lineno = lineno;
    return result;
}


AST_func_header_start ast_func_header_start(Identifier id, Type typename, Type list){
    AST_func_header_start result = new(sizeof(*result));
    result->id = id;
    result->typename = set_list_or_typename(list, typename);
    result->lineno = lineno;
    return result;
}

AST_variabledef ast_variabledef(Identifier id, Type list, Type array){
    ASSERT(!(list && array)); // Can't be list & array at the same time!
    AST_variabledef result = new(sizeof(*result));
    result->id = id;
    result->type = list ? list : array; // Can return null if both list & array == NULL;
    result->lineno = lineno;
    return result;
}
                  
Type ast_dims(Type outer_array, Type inner_array){ //  Good for semantic... Maybe need different for ast?
    if(outer_array){
        outer_array->u.t_array.type = inner_array;
        return outer_array;
    }else{
        return inner_array;
    }
}

AST_constant ast_constant_iconst(int r) {
    AST_constant result = new(sizeof(*result));
    result->kind = CONSTANT_iconst;
    result->u.c_iconst.rep = r;
    result->lineno = lineno;
    return result;
}

AST_constant ast_constant_fconst(float r) {
    AST_constant result = new(sizeof(*result));
    result->kind = CONSTANT_fconst;
    result->u.c_fconst.rep = r;
    result->lineno = lineno;
    return result;
}

AST_constant ast_constant_cconst(char r) {
    AST_constant result = new(sizeof(*result));
    result->kind = CONSTANT_cconst;
    result->u.c_cconst.rep = r;
    result->lineno = lineno;
    return result;
}

AST_constant ast_constant_sconst(char* r) {
    AST_constant result = new(sizeof(*result));
    result->kind = CONSTANT_sconst;
    result->u.c_sconst.rep = r;
    result->lineno = lineno;
    return result;
}

AST_full_par_func_header ast_full_par_func_header_class(AST_class_func_header_start h, List p){
    AST_full_par_func_header result = new(sizeof(*result));
    result->kind = FPF_CLASS;
    result->u.fpf_class.header = h;
    result->parameters = p;
    result->lineno = lineno;
    return result;
}

AST_full_par_func_header ast_full_par_func_header_noclass(AST_func_header_start h, List p){
     AST_full_par_func_header result = new(sizeof(*result));
     result->kind = FPF_NOCLASS;
     result->u.fpf_noclass.header = h;
     result->parameters = p;
     result->lineno = lineno;
     return result;
}

AST_full_func_dcl ast_full_func_dcl_full_par(AST_full_par_func_header h, AST_dcl_stmt s){
    AST_full_func_dcl result = new(sizeof(*result));
    result->kind = FFD_FULL_PAR;
    result->u.full_par.header = h;
    result->statements = s;
    result->lineno = lineno;
    return result;
}

AST_full_func_dcl ast_full_func_dcl_nopar_class(AST_class_func_header_start h, AST_dcl_stmt s){
    AST_full_func_dcl result = new(sizeof(*result));
    result->kind = FFD_NOPAR_CLASS;
    result->u.nopar_class.header = h;
    result->statements = s;
    result->lineno = lineno;
    return result;
}

AST_full_func_dcl ast_full_func_dcl_nopar(AST_func_header_start h, AST_dcl_stmt s){
    AST_full_func_dcl result = new(sizeof(*result));
    result->kind = FFD_NOPAR;
    result->u.nopar.header = h;
    result->statements = s;
    result->lineno = lineno;
    return result;
}

AST_dcl_stmt ast_dcl_stmt_dcls_stmts(List s, List d){
    AST_dcl_stmt result = new(sizeof(*result));
    result->kind = DCL_STMT_STMTS_DCLS;
    result->u.dcl_stmt_stmts_dcls.statements = s;
    result->u.dcl_stmt_stmts_dcls.declares = d;
    result->lineno = lineno;
    return result;
}

AST_dcl_stmt ast_dcl_stmt_dcls(List d){
    AST_dcl_stmt result = new(sizeof(*result));
    result->kind = DCL_STMT_DCLS;
    result->u.dcl_stmt_dcls.declares = d;
    result->lineno = lineno;
    return result;
}

AST_dcl_stmt ast_dcl_stmt_empty(){
    AST_dcl_stmt result = new(sizeof(*result));
    result->kind = DCL_STMT_EMPTY;
    result->lineno = lineno;
    return result;
}

AST_dcl_stmt ast_dcl_stmt_stmts(List s){
    AST_dcl_stmt result = new(sizeof(*result));
    result->kind = DCL_STMT_STMTS;
    result->u.dcl_stmt_stmts.statements = s;
    result->lineno = lineno;
    return result;
}

AST_func_dcl ast_func_dcl_short(AST_short_func_dcl s){
    AST_func_dcl result = new(sizeof(*result));
    result->kind = FD_SHORT;
    result->u.fd_short.func = s;
    result->lineno = lineno;
    return result;
}
AST_func_dcl ast_func_dcl_full(AST_full_func_dcl f){
    AST_func_dcl result = new(sizeof(*result));
    result->kind = FD_FULL;
    result->u.fd_full.func = f;
    result->lineno = lineno;
    return result;
}

List list_add(List list, void *data){
    List node = new(sizeof(struct List_tag));
    node->data = data;
    node->next = NULL;

    if(list == NULL)
        return node;
    
    List tmp = list;
	while(tmp->next != NULL){
		tmp = tmp->next;
	}
    tmp->next = node;
	
	return list;
}

void list_reverse(List *head){
    List prev = NULL;
    List current = *head;
    List next = NULL;

    while(current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

Type set_list_or_typename(Type list, Type typename){
    if(list){
        ASSERT(list->kind == TYPE_list);
        list->u.t_list.type = typename;
        return list;
    }else{
        return typename;
    }
}

Type set_list_or_array_or_typename(Type list, Type array, Type typename){
    ASSERT(!(list && array)); // Can't be both a list and array!
    if(list){
        ASSERT(list->kind == TYPE_list);
        list->u.t_list.type = typename;
        return list;
    }else if(array){
        set_array_type(array, typename);
        return array;
    }else{
        return typename;
    }
}

void set_array_type(Type array, Type type){
    ASSERT(array && type);
    ASSERT(array->kind == TYPE_array);
    Type tmp = array;
    while(tmp->u.t_array.type->kind == TYPE_array)
        tmp = tmp->u.t_array.type;
    tmp->u.t_array.type = type;
}

Type get_parameter_type(Type typename, Type pass_list_dims){
    if(!pass_list_dims){ // If not ref or list/array
        return typename;
    }else{
        switch(pass_list_dims->kind){
            case TYPE_ref:
                pass_list_dims->u.t_ref.type = typename;
                break;
            case TYPE_list:
                pass_list_dims->u.t_list.type = typename;
                break;
            case TYPE_array:
                set_array_type(pass_list_dims, typename);
                break;
            default:
                fatal("Unexpected input on get_parameter_type()\n");
                break;
        }
        return pass_list_dims;
    }
}





AST_expr ast_new_binop_AND_expr(AST_expr exp1 ,AST_expr exp2)
{   AST_expr result = new(sizeof(result));

    result->kind = EXPR_binop;
    result->u.e_binop.expr1 = exp1;
    result->u.e_binop.expr2 =exp2;
    result->u.e_binop.op = ast_binop_and;
    
    result->lineno = lineno;
    return result;
}



AST_expr ast_new_binop_OR_expr(AST_expr exp1 ,AST_expr exp2)
{   AST_expr result = new(sizeof(result));

    result->kind = EXPR_binop;
    result->u.e_binop.expr1 = exp1;
    result->u.e_binop.expr2 =exp2;
    result->u.e_binop.op = ast_binop_or;
    
    result->lineno = lineno;
    return result;
}

AST_expr ast_new_binop_EQ_expr(AST_expr exp1 ,AST_expr exp2)
{   AST_expr result = new(sizeof(result));

    result->kind = EXPR_binop;
    result->u.e_binop.expr1 = exp1;
    result->u.e_binop.expr2 =exp2;
    result->u.e_binop.op = ast_binop_eq;
   
    result->lineno = lineno;
    return result;
}

AST_expr ast_new_binop_REL_expr(AST_expr exp1 ,char *op ,AST_expr exp2)
{   AST_expr result = new(sizeof(result));

    result->kind = EXPR_binop;
    result->u.e_binop.expr1 = exp1;
    result->u.e_binop.expr2 =exp2;

    if(strcmp("<",op))
        result->u.e_binop.op = ast_binop_lt;
    else if(strcmp("<=",op))
        result->u.e_binop.op = ast_binop_le;
    else if(strcmp(">=",op))
        result->u.e_binop.op = ast_binop_ge;
    else
        result->u.e_binop.op = ast_binop_gt;

    result->lineno = lineno;
    return result;
}


AST_expr ast_new_binop_ADD_expr(AST_expr exp1 ,char *op ,AST_expr exp2)
{   AST_expr result = new(sizeof(result));

    result->kind = EXPR_binop;
    result->u.e_binop.expr1 = exp1;
    result->u.e_binop.expr2 =exp2;

    if(strcmp("+",op))
        result->u.e_binop.op = ast_binop_plus;
    else
        result->u.e_binop.op = ast_binop_minus;

    result->lineno = lineno;
    return result;
}

AST_expr ast_new_binop_MUL_expr(AST_expr exp1 ,char *op ,AST_expr exp2)
{   AST_expr result = new(sizeof(result));

    result->kind = EXPR_binop;
    result->u.e_binop.expr1 = exp1;
    result->u.e_binop.expr2 =exp2;

    if(strcmp("*",op))
        result->u.e_binop.op = ast_binop_times;
    else if(strcmp("/",op))
        result->u.e_binop.op = ast_binop_div;
    else
        result->u.e_binop.op = ast_binop_mod;

    result->lineno = lineno;
    return result;
}

AST_expr ast_unop_expr(char *op ,AST_expr expr)
{
    AST_expr result = new(sizeof(result));
    
    result->kind = EXPR_unop;
    result->u.e_unop.expr= expr;


    if(strcmp("!",op))
        result->u.e_unop.op = ast_unop_not;
    else if(strcmp("+",op))
        result->u.e_unop.op = ast_unop_plus;
    else if(strcmp("-",op))
        result->u.e_unop.op = ast_unop_minus;
    else if(strcmp("sizeof",op))
        result->u.e_binop.op = ast_unop_sizeop;
    else if (strcmp("++",op))
        result->u.e_unop.op = ast_unop_inc;
    else
        result->u.e_unop.op = ast_unop_dec;

    result->lineno = lineno;
    return result;
    
}

AST_expr ast_func_expr(AST_variable variable ,AST_expr_list expression_list)
{   AST_expr result = new(sizeof(result));

    result->kind = EXPR_call;
    result->u.e_call.id = variable->u.definition.id;
    result->u.e_call.list = expression_list;
    
    result->lineno = lineno;
    return result;
}

AST_expr ast_length_expr(AST_general_expr general_expression)
{   AST_expr result = new(sizeof(result));

    result->kind = EXPR_call;
    result->u.e_call_length.expr = general_expression;
    
    result->lineno = lineno;
    return result;  
}








