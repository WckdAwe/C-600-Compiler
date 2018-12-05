/*
  Dimitriadis Vasileios || 2116104
  Kouskouras Taxiarchis || 2116162
  Papageorgiou Grigoris || 2116025

*/
%{
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include "settings.h"
#include "hashtbl.h"


/** Extern from Flex **/
extern int lineno, 
           line_init;

extern char str_buf[MAX_STR_CONST];    
extern char* str_buf_ptr;

extern int yylex();
extern char *yytext;
extern FILE *yyin;

extern void yyterminate();


/** Bison specific variables **/
int error_count=0; 
int flag_err_type=0; // 0: Token Error (YYTEXT) || 1: String Error (STRBUF)
int scope=0;

HASHTBL *hashtbl;

/** Bison specific functions **/
void yyerror(const char *message);


/** TODO: Order of Operations: https://en.wikipedia.org/wiki/Order_of_operations **/
/** TODO: Explain why UMINUS **/
/** TODO: Explain Order of Operations **/
/** TODO: Verify %type **/
%}


%error-verbose

%union{
	int intval;
	double doubleval; 
    char *strval;
}

%token <intval> T_ICONST 
%token <doubleval> T_FCONST
%token <strval> T_TYPEDEF T_CHAR T_STRING T_SCONST T_INT T_ENUM T_LENGTH
%token <strval> T_CLASS T_PRIVATE T_PROTECTED T_PUBLIC T_STATIC T_UNION T_LIST T_CONTINUE T_BREAK T_IF T_ELSE T_WHILE T_FOR
%token <strval> T_SWITCH T_DEFAULT T_RETURN T_NEW T_CIN T_COUT T_MAIN T_THIS T_ID T_OROP T_ANDOP T_EQUOP T_ADDOP T_MULOP T_INCDEC
%token <strval> T_SIZEOP T_LISTFUNC T_LPAREN T_RPAREN T_SEMI T_DOT T_COMMA T_COLON T_LBRACK T_REFER T_LBRACE 
%token <strval> T_RBRACE T_METH T_INP T_OUT
%token <strval> T_ASSIGN T_CASE T_CCONST T_FLOAT T_NOTOP T_RELOP T_VOID
%token <strval> T_RBRACK "]"
%token <strval> T_EOF 0 "end of file"


%type <strval> program global_declaration global_declarations typedef_declaration typename standard_type listspec dims dim enum_declaration
%type <strval> enum_body id_list initializer init_value expression variable general_expression assignment expression_list constant listexpression
%type <strval> init_values class_declaration class_body parent members_methods access member_or_method member var_declaration variabledefs variabledef 
%type <strval> anonymous_union union_body fields field method short_func_declaration short_par_func_header func_header_start parameter_types 
%type <strval> pass_list_dims nopar_func_header union_declaration global_var_declaration init_variabledefs init_variabledef func_declaration full_func_declaration 
%type <strval> full_par_func_header class_func_header_start func_class parameter_list pass_variabledef nopar_class_func_header decl_statements declarations decltype 
%type <strval> statements statement expression_statement if_statement if_tail while_statement for_statement optexpr switch_statement switch_tail decl_cases 
%type <strval> casestatements casestatement single_casestatement return_statement io_statement in_list in_item out_list out_item comp_statement main_function main_header

%left T_COMMA
%right T_ASSIGN 
%left T_OROP
%left T_ANDOP
%left T_EQUOP
%left T_RELOP
%left T_ADDOP
%left T_MULOP 
%left T_NOTOP T_REFER T_SIZEOP T_INCDEC UMINUS
%left T_LPAREN T_RPAREN T_LBRACK T_RBRACK T_DOT T_METH

%nonassoc LOWER_THAN_ELSE
%nonassoc T_ELSE


                        
%start program 

%%
program:                  global_declarations main_function                         {scope++;}
                        ;
global_declarations:      global_declarations global_declaration
                        | %empty {}
                        ;
global_declaration:       typedef_declaration
                        | enum_declaration
                        | class_declaration
                        | union_declaration
                        | global_var_declaration
                        | func_declaration
                        ;
typedef_declaration:      T_TYPEDEF typename listspec T_ID                          {hashtbl_insert(hashtbl, $4, NULL, scope);scope++;}
                            dims T_SEMI 				                            {hashtbl_get(hashtbl, scope);scope--;}
                        ;
typename:                 standard_type
                        | T_ID														{hashtbl_insert(hashtbl, $1, NULL, scope);}
                        ;
standard_type:            T_CHAR 
                        | T_INT 
                        | T_FLOAT 
                        | T_STRING 
                        | T_VOID
                        ;
listspec:                 T_LIST 
                        | %empty {}
                        ;
dims:                     dims dim
                        | %empty {}
                        ;
dim:                      T_LBRACK T_ICONST T_RBRACK 
                        | T_LBRACK T_RBRACK
                        ;
enum_declaration:         T_ENUM T_ID                                               {hashtbl_insert(hashtbl, $2, NULL, scope);scope++;}
                            enum_body       
                            T_SEMI								                    {hashtbl_get(hashtbl, scope);scope--;}
                        ;
enum_body:                T_LBRACE id_list T_RBRACE
                        ;
id_list:                  id_list T_COMMA T_ID initializer							{hashtbl_insert(hashtbl, $3, NULL, scope);}
                        | T_ID 														{hashtbl_insert(hashtbl, $1, NULL, scope);} 
                          initializer
                        ;
initializer:              T_ASSIGN init_value
                        | %empty {}
init_value:               expression
                        | T_LBRACE init_values T_RBRACE
                        ;
expression:               expression T_OROP expression
                        | expression T_ANDOP expression
                        | expression T_EQUOP expression
                        | expression T_RELOP expression
                        | expression T_ADDOP expression
                        | expression T_MULOP expression
                        | T_NOTOP expression
                        | T_ADDOP expression %prec UMINUS
                        | T_SIZEOP expression
                        | T_INCDEC variable
                        | variable T_INCDEC
                        | variable
                        | variable T_LPAREN expression_list T_RPAREN
                        | T_LENGTH T_LPAREN general_expression T_RPAREN
                        | T_NEW T_LPAREN general_expression T_RPAREN
                        | constant
                        | T_LPAREN general_expression T_RPAREN
                        | T_LPAREN standard_type T_RPAREN
                        | listexpression
                        ;
variable:                 variable T_LBRACK general_expression T_RBRACK
                        | variable T_DOT T_ID										{hashtbl_insert(hashtbl, $3, NULL, scope);}
                        | T_LISTFUNC T_LPAREN general_expression T_RPAREN
                        | decltype T_ID												{hashtbl_insert(hashtbl, $2, NULL, scope);}
                        | T_THIS
                        ;
general_expression:       general_expression T_COMMA general_expression
                        | assignment
                        ;
assignment:               variable T_ASSIGN assignment
                        | expression
                        ;
expression_list:          general_expression
                        | %empty {}
                        ;
constant:                 T_CCONST 
                        | T_ICONST 
                        | T_FCONST 
                        | T_SCONST
                        ;
listexpression:           T_LBRACK expression_list T_RBRACK
                        ;
init_values:              init_values T_COMMA init_value
                        | init_value
                        ;
class_declaration:        T_CLASS T_ID                                              {hashtbl_insert(hashtbl, $2, NULL, scope);scope++;}
                            class_body                                              
                            T_SEMI					                                {hashtbl_get(hashtbl, scope);scope--;}
                        ;
class_body:               parent T_LBRACE members_methods T_RBRACE
                        ;
parent:                   T_COLON T_ID 										        {hashtbl_insert(hashtbl, $2, NULL, scope);}
                        | %empty {}
                        ;
members_methods:          members_methods access member_or_method
                        | access member_or_method
                        ;
access:                   T_PRIVATE T_COLON 
                        | T_PROTECTED T_COLON 
                        | T_PUBLIC T_COLON 
                        | %empty {}
                        ;
member_or_method:         member
                        | method
                        ;
member:                   var_declaration
                        | anonymous_union
                        ;
var_declaration:          typename variabledefs T_SEMI
                        ;
variabledefs:             variabledefs T_COMMA variabledef
                        | variabledef
                        ;
variabledef:              listspec T_ID dims								        {hashtbl_insert(hashtbl, $2, NULL, scope);}
                        ;
anonymous_union:          T_UNION                                                   {scope++;}
                            union_body 
                            T_SEMI                                                  {hashtbl_get(hashtbl, scope);scope--;}
                        ;
union_body:               T_LBRACE fields T_RBRACE
                        ;
fields:                   fields field
                        | field
                        ;
field:                    var_declaration
                        ;
method:                   short_func_declaration                                    
                        ;
short_func_declaration:   short_par_func_header T_SEMI                              {hashtbl_get(hashtbl, scope);scope--;}
                        | nopar_func_header T_SEMI                                  {hashtbl_get(hashtbl, scope);scope--;}
                        ;
short_par_func_header:    func_header_start T_LPAREN parameter_types T_RPAREN      
                        ;
func_header_start:        typename listspec T_ID							        {hashtbl_insert(hashtbl, $3, NULL, scope);scope++;/**Scope++ for every function!!!**/}
                        ;
parameter_types:          parameter_types T_COMMA typename pass_list_dims
                        | typename pass_list_dims
                        ;
pass_list_dims:           T_REFER
                        | listspec dims
                        ;
nopar_func_header:        func_header_start T_LPAREN T_RPAREN                       {/** NO SCOPE due to func_header_start! **/}
                        ;
union_declaration:        T_UNION T_ID                                              {hashtbl_insert(hashtbl, $2, NULL, scope);scope++;}
                            union_body          
                            T_SEMI						                            {hashtbl_get(hashtbl, scope);scope--;}
                        ;
global_var_declaration:   typename init_variabledefs T_SEMI
                        ;
init_variabledefs:        init_variabledefs T_COMMA init_variabledef
                        | init_variabledef
                        ;
init_variabledef:         variabledef initializer
                        ;
func_declaration:         short_func_declaration
                        | full_func_declaration
                        ;
full_func_declaration:    full_par_func_header T_LBRACE decl_statements T_RBRACE    {hashtbl_get(hashtbl, scope);scope--;}
                        | nopar_class_func_header T_LBRACE decl_statements T_RBRACE {hashtbl_get(hashtbl, scope);scope--;}
                        | nopar_func_header T_LBRACE decl_statements T_RBRACE       {hashtbl_get(hashtbl, scope);scope--;}
                        ;
full_par_func_header:     class_func_header_start T_LPAREN parameter_list T_RPAREN
                        | func_header_start T_LPAREN parameter_list T_RPAREN
                        ;
class_func_header_start:  typename listspec func_class T_ID							{hashtbl_insert(hashtbl, $4, NULL, scope);scope++;/**Scope++ for every function!!!**/}
                        ;
func_class:               T_ID T_METH												{hashtbl_insert(hashtbl, $1, NULL, scope);}
                        ;
parameter_list:           parameter_list T_COMMA typename pass_variabledef
                        | typename pass_variabledef
                        ;
pass_variabledef:         variabledef
                        | T_REFER T_ID												{hashtbl_insert(hashtbl, $2, NULL, scope);}
                        ;
nopar_class_func_header:  class_func_header_start T_LPAREN T_RPAREN                 
                        ;
decl_statements:          declarations statements
                        | declarations
                        | statements
                        | %empty {}
                        ;
declarations:             declarations decltype typename variabledefs T_SEMI
                        | decltype typename variabledefs T_SEMI
                        ;
decltype:                 T_STATIC 
                        | %empty {}
                        ;
statements:               statements statement
                        | statement
                        ;
statement:                expression_statement
                        | if_statement
                        | while_statement
                        | for_statement
                        | switch_statement
                        | return_statement
                        | io_statement
                        | comp_statement
                        | T_CONTINUE T_SEMI
                        | T_BREAK T_SEMI
                        | T_SEMI
                        ;
expression_statement:     general_expression T_SEMI
                        ;
if_statement:             T_IF T_LPAREN general_expression T_RPAREN statement if_tail
                        ;
if_tail:                  T_ELSE statement
                        | %empty %prec LOWER_THAN_ELSE {}
                        ;
while_statement:          T_WHILE T_LPAREN general_expression T_RPAREN statement
                        ;
for_statement:            T_FOR T_LPAREN optexpr T_SEMI optexpr T_SEMI optexpr T_RPAREN statement
                        ;
optexpr:                  general_expression
                        | %empty {}
                        ;
switch_statement:         T_SWITCH T_LPAREN general_expression T_RPAREN switch_tail
                        ;
switch_tail:              T_LBRACE decl_cases T_RBRACE
                        | single_casestatement
                        ;
decl_cases:               declarations casestatements
                        | declarations
                        | casestatements
                        | %empty {}
                        ;
casestatements:           casestatements casestatement
                        | casestatement
                        ;
casestatement:            T_CASE constant T_COLON casestatement
                        | T_CASE constant T_COLON statements
                        | T_DEFAULT T_COLON statements
                        ;
single_casestatement:     T_CASE constant T_COLON single_casestatement
                        | T_CASE constant T_COLON statement
                        ;
return_statement:         T_RETURN optexpr T_SEMI
                        ;
io_statement:             T_CIN T_INP in_list T_SEMI
                        | T_COUT T_OUT out_list T_SEMI
                        ;
in_list:                  in_list T_INP in_item
                        | in_item
                        ;
in_item:                  variable
                        ;
out_list:                 out_list T_OUT out_item
                        | out_item
                        ;
out_item:                 general_expression
                        ;
comp_statement:           T_LBRACE decl_statements T_RBRACE
                        ;
main_function:            main_header T_LBRACE decl_statements T_RBRACE                         {hashtbl_get(hashtbl, scope);scope--;}
                        ;
main_header:              T_INT T_MAIN T_LPAREN T_RPAREN                                        {scope++;}
                        ;
%%

int main(int argc, char *argv[]){

    if(!(hashtbl = hashtbl_create(10, NULL))) {
		fprintf(stderr, "ERROR: hashtbl_create() failed!\n");
		exit(EXIT_FAILURE);
	}
    
    if(argc > 1){
        yyin = fopen(argv[1], "r");
        if (yyin == NULL){
            perror ("Error opening file"); return -1;
        }
    }

    yyparse();
    
    hashtbl_destroy(hashtbl);
    fclose(yyin);
    
    
    if(error_count > 0){
        printf("Syntax Analysis failed due to %d errors\n", error_count);
    }else{
        printf("Syntax Analysis completed successfully.\n");
    }
    return 0;
}


void yyerror(const char *message)
{
    error_count++;
    
    if(flag_err_type==0){
		printf("-> ERROR at line %d caused by %s : %s\n", lineno, yytext, message);
    }else if(flag_err_type==1){
		//*str_buf_ptr = '\0'; // String or Comment Error. Cleanup old chars stored in buffer.
		printf("-> ERROR at line %d near \"%s\": %s\n", lineno, str_buf, message);
    }
    flag_err_type = 0; // Reset flag_err_type to default.
    if(MAX_ERRORS <= 0) return;
    if(error_count == MAX_ERRORS){
        printf("Max errors detected\n");
        exit(-1);
    }
}
