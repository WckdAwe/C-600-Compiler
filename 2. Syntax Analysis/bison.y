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

extern int yylex();
extern char *yytext;
extern FILE *yyin;

extern void yyterminate();


extern int lineno=1;
extern int line_init=-1;
extern int error_count = 0; 
extern char str_buf[MAX_STR_CONST];    
extern char* str_buf_ptr;

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
typedef_declaration:      TYPEDEF typename listspec ID dims SEMI
                        ;
typename:                 standard_type
                        | ID
                        ;
standard_type:            CHAR 
                        | INT 
                        | FLOAT 
                        | STRING 
                        | VOID
                        ;
listspec:                 LIST 
                        |/* ε */
                        ;
dims:                     dims dim
                        |/* ε */
                        ;
dim:                      LBRACK ICONST RBRACK 
                        | LBRACK RBRACK
                        ;
enum_declaration:         ENUM ID enum_body SEMI
                        ;
enum_body:                LBRACE id_list RBRACE
                        ;
id_list:                  id_list COMMA ID initializer
                        | ID initializer
                        ;
initializer:              ASSIGN init_value
                        |/* ε */
init_value:               expression
                        | LBRACE init_values RBRACE
                        ;
expression:               expression OROP expression
                        | expression ANDOP expression
                        | expression EQUOP expression
                        | expression RELOP expression
                        | expression ADDOP expression
                        | expression MULOP expression
                        | NOTOP expression
                        | ADDOP expression
                        | SIZEOP expression
                        | INCDEC variable
                        | variable INCDEC
                        | variable
                        | variable LPAREN expression_list RPAREN
                        | LENGTH LPAREN general_expression RPAREN
                        | NEW LPAREN general_expression RPAREN
                        | constant
                        | LPAREN general_expression RPAREN
                        | LPAREN standard_type RPAREN
                        | listexpression
                        ;
variable:                 variable LBRACK general_expression RBRACK
                        | variable DOT ID
                        | LISTFUNC LPAREN general_expression RPAREN
                        | decltype ID
                        | THIS
                        ;
general_expression:       general_expression COMMA general_expression
                        | assignment
                        ;
assignment:               variable ASSIGN assignment
                        | expression
                        ;
expression_list:          general_expression
                        |/* ε */
                        ;
constant:                 CCONST 
                        | ICONST 
                        | FCONST 
                        | SCONST
                        ;
listexpression:           LBRACK expression_list RBRACK
                        ;
init_values:              init_values COMMA init_value
                        | init_value
                        ;
class_declaration:        CLASS ID class_body SEMI
                        ;
class_body:               parent LBRACE members_methods RBRACE
                        ;
parent:                   COLON ID 
                        |/* ε */
                        ;
members_methods:          members_methods access member_or_method
                        | access member_or_method
                        ;
access:                   PRIVATE COLON 
                        | PROTECTED COLON 
                        | PUBLIC COLON 
                        |/* ε */
                        ;
member_or_method:         member
                        | method
                        ;
member:                   var_declaration
                        | anonymous_union
                        ;
var_declaration:          typename variabledefs SEMI
                        ;
variabledefs:             variabledefs COMMA variabledef
                        | variabledef
                        ;
variabledef:              listspec ID dims
                        ;
anonymous_union:          UNION union_body SEMI
                        ;
union_body:               LBRACE fields RBRACE
                        ;
fields:                   fields field
                        | field
                        ;
field:                    var_declaration
                        ;
method:                   short_func_declaration
                        ;
short_func_declaration:   short_par_func_header SEMI
                        | nopar_func_header SEMI
                        ;
short_par_func_header:    func_header_start LPAREN parameter_types RPAREN
                        ;
func_header_start:        typename listspec ID
                        ;
parameter_types:          parameter_types COMMA typename pass_list_dims
                        | typename pass_list_dims
                        ;
pass_list_dims:           REFER
                        | listspec dims
                        ;
nopar_func_header:        func_header_start LPAREN RPAREN
                        ;
union_declaration:        UNION ID union_body SEMI
                        ;
global_var_declaration:   typename init_variabledefs SEMI
                        ;
init_variabledefs:        init_variabledefs COMMA init_variabledef
                        | init_variabledef
                        ;
init_variabledef:         variabledef initializer
                        ;
func_declaration:         short_func_declaration
                        | full_func_declaration
                        ;
full_func_declaration:    full_par_func_header LBRACE decl_statements RBRACE
                        | nopar_class_func_header LBRACE decl_statements RBRACE
                        | nopar_func_header LBRACE decl_statements RBRACE
                        ;
full_par_func_header:     class_func_header_start LPAREN parameter_list RPAREN
                        | func_header_start LPAREN parameter_list RPAREN
                        ;
class_func_header_start:  typename listspec func_class ID
                        ;
func_class:               ID METH
                        ;
parameter_list:           parameter_list COMMA typename pass_variabledef
                        | typename pass_variabledef
                        ;
pass_variabledef:         variabledef
                        | REFER ID
                        ;
nopar_class_func_header:  class_func_header_start LPAREN RPAREN
                        ;
decl_statements:          declarations statements
                        | declarations
                        | statements
                        |/* ε */
                        ;
declarations:             declarations decltype typename variabledefs SEMI
                        | decltype typename variabledefs SEMI
                        ;
decltype:                 STATIC 
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
                        | CONTINUE SEMI
                        | BREAK SEMI
                        | SEMI
                        ;
expression_statement:     general_expression SEMI
                        ;
if_statement:             IF LPAREN general_expression RPAREN statement if_tail
                        ;
if_tail:                  ELSE statement
                        |/* ε */
                        ;
while_statement:          WHILE LPAREN general_expression RPAREN statement
                        ;
for_statement:            FOR LPAREN optexpr SEMI optexpr SEMI optexpr RPAREN statement
                        ;
optexpr:                  general_expression
                        |/* ε */
                        ;
switch_statement:         SWITCH LPAREN general_expression RPAREN switch_tail
                        ;
switch_tail:              LBRACE decl_cases RBRACE
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
casestatement:            CASE constant COLON casestatement
                        | CASE constant COLON statements
                        | DEFAULT COLON statements
                        ;
single_casestatement:     CASE constant COLON single_casestatement
                        | CASE constant COLON statement
                        ;
return_statement:         RETURN optexpr SEMI
                        ;
io_statement:             CIN INP in_list SEMI
                        | COUT OUT out_list SEMI
                        ;
in_list:                  in_list INP in_item
                        | in_item
                        ;
in_item:                  variable
                        ;
out_list:                 out_list OUT out_item
                        | out_item
                        ;
out_item:                 general_expression
                        ;
comp_statement:           LBRACE decl_statements RBRACE
                        ;
main_function:            main_header LBRACE decl_statements RBRACE
                        ;
main_header:              INT MAIN LPAREN RPAREN
                        ;
%%

