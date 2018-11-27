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
#include "hashtbl.h"
#define MAX_ERRORS       0
#define MAX_STR_CONST  256

extern int yylex();
extern char *yytext;
extern FILE *yyin;

extern void yyterminate();


extern int lineno;
extern int line_init;
extern int error_count; 
extern char str_buf[MAX_STR_CONST];    
extern char* str_buf_ptr;

void yyerror(char* str);
%}

%union{
	int intval;
	double doubleval; 
    char *strval;
}

%token<intval> T_INT T_ENUM T_LENGTH T_ICONST 
%token<doubleval> T_FCONST
%token<strval> T_TYPEDEF T_CHAR T_STRING T_SCONST 
%token<strval> T_CLASS T_PRIVATE T_PROTECTED T_PUBLIC T_STATIC T_UNION T_LIST T_CONTINUE T_BREAK T_IF T_ELSE T_WHILE T_FOR
%token<strval> T_SWITCH T_DEFAULT T_RETURN T_NEW T_CIN T_COUT T_MAIN T_THIS T_ID T_OROP T_ANDOP T_EQUIOP T_ADDOP T_MULOP T_INCDEC
%token<strval> T_SIZEOP T_LISTFUNC T_LPAREN T_RPAREN T_SEMI T_DOT T_COMMA T_ASSING T_COLON T_LBRACK T_RBRACK T_REFER T_LBRACE 
%token<strval> T_RBRACE T_METH T_INP T_OUT T_EOF 
%token<strval> T_ASSIGN T_CASE T_CCONST T_EQUOP T_FLOAT T_NOTOP T_RELOP T_VOID

%left T_OROP T_ANDOP
%left T_ADDOP T

%start program 

%%
program:                  global_declarations main_function
                        ;
global_declarations:      global_declarations global_declaration
                        |/* ε */
                        ;
global_declaration:       typedef_declaration
                        | enum_declaration
                        | class_declaration
                        | union_declaration
                        | global_var_declaration
                        | func_declaration
                        ;
typedef_declaration:      T_TYPEDEF typename listspec T_ID dims T_SEMI
                        ;
typename:                 standard_type
                        | T_ID
                        ;
standard_type:            T_CHAR 
                        | T_INT 
                        | T_FLOAT 
                        | T_STRING 
                        | T_VOID
                        ;
listspec:                 T_LIST 
                        |/* ε */
                        ;
dims:                     dims dim
                        |/* ε */
                        ;
dim:                      T_LBRACK T_ICONST T_RBRACK 
                        | T_LBRACK T_RBRACK
                        ;
enum_declaration:         T_ENUM T_ID enum_body T_SEMI
                        ;
enum_body:                T_LBRACE id_list T_RBRACE
                        ;
id_list:                  id_list T_COMMA T_ID initializer
                        | T_ID initializer
                        ;
initializer:              T_ASSIGN init_value
                        |/* ε */
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
                        | T_ADDOP expression
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
                        | variable T_DOT T_ID
                        | T_LISTFUNC T_LPAREN general_expression T_RPAREN
                        | decltype T_ID
                        | T_THIS
                        ;
general_expression:       general_expression T_COMMA general_expression
                        | assignment
                        ;
assignment:               variable T_ASSIGN assignment
                        | expression
                        ;
expression_list:          general_expression
                        |/* ε */
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
class_declaration:        T_CLASS T_ID class_body T_SEMI
                        ;
class_body:               parent T_LBRACE members_methods T_RBRACE
                        ;
parent:                   T_COLON T_ID 
                        |/* ε */
                        ;
members_methods:          members_methods access member_or_method
                        | access member_or_method
                        ;
access:                   T_PRIVATE T_COLON 
                        | T_PROTECTED T_COLON 
                        | T_PUBLIC T_COLON 
                        |/* ε */
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
variabledef:              listspec T_ID dims
                        ;
anonymous_union:          T_UNION union_body T_SEMI
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
short_func_declaration:   short_par_func_header T_SEMI
                        | nopar_func_header T_SEMI
                        ;
short_par_func_header:    func_header_start T_LPAREN parameter_types T_RPAREN
                        ;
func_header_start:        typename listspec T_ID
                        ;
parameter_types:          parameter_types T_COMMA typename pass_list_dims
                        | typename pass_list_dims
                        ;
pass_list_dims:           T_REFER
                        | listspec dims
                        ;
nopar_func_header:        func_header_start T_LPAREN T_RPAREN
                        ;
union_declaration:        T_UNION T_ID union_body T_SEMI
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
full_func_declaration:    full_par_func_header T_LBRACE decl_statements T_RBRACE
                        | nopar_class_func_header T_LBRACE decl_statements T_RBRACE
                        | nopar_func_header T_LBRACE decl_statements T_RBRACE
                        ;
full_par_func_header:     class_func_header_start T_LPAREN parameter_list T_RPAREN
                        | func_header_start T_LPAREN parameter_list T_RPAREN
                        ;
class_func_header_start:  typename listspec func_class T_ID
                        ;
func_class:               T_ID T_METH
                        ;
parameter_list:           parameter_list T_COMMA typename pass_variabledef
                        | typename pass_variabledef
                        ;
pass_variabledef:         variabledef
                        | T_REFER T_ID
                        ;
nopar_class_func_header:  class_func_header_start T_LPAREN T_RPAREN
                        ;
decl_statements:          declarations statements
                        | declarations
                        | statements
                        |/* ε */
                        ;
declarations:             declarations decltype typename variabledefs T_SEMI
                        | decltype typename variabledefs T_SEMI
                        ;
decltype:                 T_STATIC 
                        |/* ε */
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
                        |/* ε */
                        ;
while_statement:          T_WHILE T_LPAREN general_expression T_RPAREN statement
                        ;
for_statement:            T_FOR T_LPAREN optexpr T_SEMI optexpr T_SEMI optexpr T_RPAREN statement
                        ;
optexpr:                  general_expression
                        |/* ε */
                        ;
switch_statement:         T_SWITCH T_LPAREN general_expression T_RPAREN switch_tail
                        ;
switch_tail:              T_LBRACE decl_cases T_RBRACE
                        | single_casestatement
                        ;
decl_cases:               declarations casestatements
                        | declarations
                        | casestatements
                        |/* ε */
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
main_function:            main_header T_LBRACE decl_statements T_RBRACE
                        ;
main_header:              T_INT T_MAIN T_LPAREN T_RPAREN
                        ;
%%

