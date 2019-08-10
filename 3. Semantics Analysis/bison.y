%{
#include <string.h>
#include "c600.h"


/* ---------------------------------------------------------------------
   ------------- External variables & functions from main.c ------------
   --------------------------------------------------------------------- */

extern HASHTBL *hashtbl;
extern void yyerror(const char *message);


/* ---------------------------------------------------------------------
   ------------- External variables & functions from lexer.l -----------
   --------------------------------------------------------------------- */

extern int yylex();
extern int lineno;

extern char str_buf[MAX_STR_CONST];    
extern char* str_buf_ptr;

extern char *yytext;


/* ---------------------------------------------------------------------
   --------------------- Local variables & functions  ------------------
   --------------------------------------------------------------------- */

int scope = 0;

Data data;

/** TODO: Write why split T_ICONST/T_FCONST **/
/** TODO: constant Union with type and val **/
%}


%error-verbose

%union{
    int intval;
    float floatval; 
    char charval;
    char *strval;
    Type typeval;
    Type_Struct *tsval;
}

%token <intval>     T_ICONST        "integer constant"
%token <floatval>   T_FCONST        "float constant"
%token <strval>     T_TYPEDEF       "typedef"
%token <strval>     T_CHAR          "char"
%token <strval>     T_STRING        "string"
%token <strval>     T_SCONST        "string const"
%token <strval>     T_CLASS         "class"
%token <strval>     T_PRIVATE       "private"
%token <strval>     T_PROTECTED     "protected"
%token <strval>     T_PUBLIC        "public"
%token <strval>     T_STATIC        "static"
%token <strval>     T_UNION         "union"
%token <strval>     T_LIST          "list"
%token <strval>     T_CONTINUE      "continue" 
%token <strval>     T_BREAK         "break"
%token <strval>     T_IF            "if"
%token <strval>     T_ELSE          "else"
%token <strval>     T_WHILE         "while"
%token <strval>     T_FOR           "for"
%token <strval>     T_SWITCH        "switch"
%token <strval>     T_DEFAULT       "default"
%token <strval>     T_RETURN        "return"
%token <strval>     T_NEW           "new"
%token <strval>     T_CIN           "cin"
%token <strval>     T_COUT          "cout"
%token <strval>     T_MAIN          "main"
%token <strval>     T_THIS          "this"
%token <strval>     T_ID            "id"
%token <strval>     T_OROP          "||"
%token <strval>     T_ANDOP         "&&"
%token <strval>     T_EQUOP         "== or !="
%token <strval>     T_ADDOP         "+ or -"
%token <strval>     T_MULOP         "* or / or %"
%token <strval>     T_INCDEC        "-- or ++"
%token <strval>     T_SIZEOP        "sizeof"
%token <strval>     T_LISTFUNC      "listfunc"
%token <strval>     T_LPAREN        "("
%token <strval>     T_RPAREN        ")"
%token <strval>     T_SEMI          ";"
%token <strval>     T_DOT           "."
%token <strval>     T_COMMA         ","
%token <strval>     T_COLON         ":"
%token <strval>     T_LBRACK        "["
%token <strval>     T_RBRACK        "]"
%token <strval>     T_REFER         "&"
%token <strval>     T_LBRACE        "{"
%token <strval>     T_RBRACE        "}"
%token <strval>     T_METH          "::"
%token <strval>     T_INP           "<<"
%token <strval>     T_OUT           ">>"
%token <strval>     T_ASSIGN        "="
%token <strval>     T_CASE          "case"
%token <charval>    T_CCONST        "char const"
%token <strval>     T_FLOAT         "float"
%token <strval>     T_NOTOP         "!"
%token <strval>     T_RELOP         "> or >= or < or <="
%token <strval>     T_VOID          "void"
%token <strval>     T_ENUM          "enum"
%token <strval>     T_INT           "int"
%token <strval>     T_LENGTH        "length"
%token <strval>     T_EOF   0       "end of file"
    
%type <strval> program global_declaration global_declarations typedef_declaration listspec dims dim enum_declaration
%type <strval> enum_body id_list initializer init_value expression variable general_expression assignment expression_list listexpression
%type <strval> init_values class_declaration class_body parent members_methods access member_or_method member var_declaration variabledefs variabledef 
%type <strval> anonymous_union union_body fields field method short_func_declaration short_par_func_header func_header_start parameter_types 
%type <strval> pass_list_dims nopar_func_header union_declaration global_var_declaration init_variabledefs init_variabledef func_declaration full_func_declaration 
%type <strval> full_par_func_header class_func_header_start func_class parameter_list pass_variabledef nopar_class_func_header decl_statements declarations decltype 
%type <strval> statements statement expression_statement if_statement if_tail while_statement for_statement optexpr switch_statement switch_tail decl_cases 
%type <strval> casestatements casestatement single_casestatement return_statement io_statement in_list in_item out_list out_item comp_statement main_function main_header
%type <strval> constant

%type <typeval> standard_type
%type <tsval> typename

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
program:                  global_declarations main_function                        
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
typedef_declaration:      T_TYPEDEF typename listspec T_ID                                  {hashtbl_insert(hashtbl, $4, NULL, scope);scope++;}
                            dims T_SEMI                                                     {hashtbl_get(hashtbl, scope);scope--;}
                        ;
typename:                 standard_type                                                     {$$ = ts_create_standard_type($1);}
                        | T_ID                                                              {hashtbl_insert(hashtbl, $1, NULL, scope);}
                        ;
standard_type:            T_CHAR                                                            {$$=CHARACTER;} 
                        | T_INT                                                             {$$=INTEGER;}
                        | T_FLOAT                                                           {$$=FLOAT;}
                        | T_STRING                                                          {$$=STRING;}
                        | T_VOID                                                            {$$=VOID;}
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
enum_declaration:         T_ENUM T_ID                                                       {hashtbl_insert(hashtbl, $2, NULL, scope);scope++;}
                            enum_body                                                       {hashtbl_get(hashtbl, scope);scope--;}
                            T_SEMI                                                  
                        ;
enum_body:                T_LBRACE id_list T_RBRACE
                        ;
id_list:                  id_list T_COMMA T_ID initializer                                  {hashtbl_insert(hashtbl, $3, NULL, scope);}
                        | T_ID                                                              {hashtbl_insert(hashtbl, $1, NULL, scope);} 
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
                        | variable T_DOT T_ID                                               {hashtbl_insert(hashtbl, $3, NULL, scope);}
                        | T_LISTFUNC T_LPAREN general_expression T_RPAREN
                        | decltype T_ID                                                     {hashtbl_insert(hashtbl, $2, NULL, scope);}
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
constant:                 T_CCONST                                                          {data.chardata=$1;} 
                        | T_ICONST                                                          {data.intdata=$1;}
                        | T_FCONST                                                          {data.floatdata=$1;}
                        | T_SCONST                                                          {data.strdata=$1;}
                        ;
listexpression:           T_LBRACK expression_list T_RBRACK
                        ;
init_values:              init_values T_COMMA init_value
                        | init_value
                        ;
class_declaration:        T_CLASS T_ID                                                      {hashtbl_insert(hashtbl, $2, NULL, scope);scope++;}
                            class_body                                              
                            T_SEMI                                                          {hashtbl_get(hashtbl, scope);scope--;}
                        ;
class_body:               parent T_LBRACE members_methods T_RBRACE
                        ;
parent:                   T_COLON T_ID                                                      {hashtbl_insert(hashtbl, $2, NULL, scope);}
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
variabledef:              listspec T_ID dims                                                {hashtbl_insert(hashtbl, $2, NULL, scope);}
                        ;
anonymous_union:          T_UNION                                                           {scope++;}
                            union_body                                                      {hashtbl_get(hashtbl, scope);scope--;}
                            T_SEMI                                                  
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
short_func_declaration:   short_par_func_header T_SEMI                                      {hashtbl_get(hashtbl, scope);scope--;}
                        | nopar_func_header T_SEMI                                          {hashtbl_get(hashtbl, scope);scope--;}
                        ;
short_par_func_header:    func_header_start T_LPAREN parameter_types T_RPAREN      
                        ;
func_header_start:        typename listspec T_ID                                            {hashtbl_insert(hashtbl, $3, NULL, scope);scope++;/**Scope++ for every function!!!**/}
                        ;
parameter_types:          parameter_types T_COMMA typename pass_list_dims
                        | typename pass_list_dims
                        ;
pass_list_dims:           T_REFER
                        | listspec dims
                        ;
nopar_func_header:        func_header_start T_LPAREN T_RPAREN                               {/** NO SCOPE due to func_header_start! **/}
                        ;
union_declaration:        T_UNION T_ID                                                      {hashtbl_insert(hashtbl, $2, NULL, scope);scope++;}
                            union_body          
                            T_SEMI                                                          {hashtbl_get(hashtbl, scope);scope--;}
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
full_func_declaration:    full_par_func_header T_LBRACE decl_statements T_RBRACE            {hashtbl_get(hashtbl, scope);scope--;}
                        | nopar_class_func_header T_LBRACE decl_statements T_RBRACE         {hashtbl_get(hashtbl, scope);scope--;}
                        | nopar_func_header T_LBRACE decl_statements T_RBRACE               {hashtbl_get(hashtbl, scope);scope--;}
                        ;
full_par_func_header:     class_func_header_start T_LPAREN parameter_list T_RPAREN
                        | func_header_start T_LPAREN parameter_list T_RPAREN
                        ;
class_func_header_start:  typename listspec func_class T_ID                                 {hashtbl_insert(hashtbl, $4, NULL, scope);scope++;/**Scope++ for every function!!!**/}
                        ;
func_class:               T_ID T_METH                                                       {hashtbl_insert(hashtbl, $1, NULL, scope);}
                        ;
parameter_list:           parameter_list T_COMMA typename pass_variabledef
                        | typename pass_variabledef
                        ;
pass_variabledef:         variabledef
                        | T_REFER T_ID                                                      {hashtbl_insert(hashtbl, $2, NULL, scope);}
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
if_statement:             T_IF T_LPAREN                                                     {scope++;}
                            general_expression T_RPAREN statement                           {hashtbl_get(hashtbl, scope);scope--;}
                            if_tail
                        ;
if_tail:                  T_ELSE                                                            {scope++;}
                            statement                                                       {hashtbl_get(hashtbl, scope);scope--;}
                        | %empty %prec LOWER_THAN_ELSE                                      {}
                        ;
while_statement:          T_WHILE T_LPAREN                                                  {scope++;} 
                            general_expression T_RPAREN statement                           {hashtbl_get(hashtbl, scope);scope--;}
                        ;
for_statement:            T_FOR T_LPAREN                                                    {scope++;} 
                            optexpr T_SEMI optexpr T_SEMI optexpr T_RPAREN statement        {hashtbl_get(hashtbl, scope);scope--;}
                        ;
optexpr:                  general_expression
                        | %empty {}
                        ;
switch_statement:         T_SWITCH T_LPAREN                                                 {scope++;}
                            general_expression T_RPAREN switch_tail                         {hashtbl_get(hashtbl, scope);scope--;}
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
                        | T_CASE constant T_COLON                                           {scope++;}
                            statements                                                      {hashtbl_get(hashtbl, scope);scope--;}
                        | T_DEFAULT T_COLON                                                 {scope++;} 
                            statements                                                      {hashtbl_get(hashtbl, scope);scope--;}
                        ;
single_casestatement:     T_CASE constant T_COLON single_casestatement
                        | T_CASE constant T_COLON                                           {scope++;} 
                            statement                                                       {hashtbl_get(hashtbl, scope);scope--;}
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
main_function:            main_header                                                  
                            T_LBRACE decl_statements T_RBRACE                               {hashtbl_get(hashtbl, scope);scope--;}
                        ;
main_header:              T_INT T_MAIN T_LPAREN T_RPAREN                                    {scope++;}
                        ;
%%