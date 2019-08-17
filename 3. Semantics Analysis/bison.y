%{
#include <string.h>
#include <stdio.h>
#include "c600.h"
#include "types.h"
#include "symbol.h"
#include "ast.h"
#include "error.h"


/* ---------------------------------------------------------------------
   ------------- External variables & functions from main.c ------------
   --------------------------------------------------------------------- */

extern void yyerror(const char *message);


/* ---------------------------------------------------------------------
   ------------- External variables & functions from lexer.l -----------
   --------------------------------------------------------------------- */

extern int yylex();
extern int lineno;
extern char *yytext;
%}


%error-verbose

%union{
    int intval;
    float floatval; 
    char charval;
    char *strval;

    Identifier identifier;

    Access access;
    Type type;
    List list;

    AST_constant constant;
    AST_variabledef variabledef;
    AST_func_header_start func_header_start;
    AST_class_func_header_start class_func_header_start;
    AST_typedef typedef_dcl;
    AST_passvar passvar;
    AST_var_declaration var_declaration;
    AST_member member;
    AST_union_dcl union_dcl;
    AST_short_func_dcl short_func_dcl;
    AST_member_or_method member_or_method;
    AST_class_body class_body;
    AST_class_dcl class_dcl;
    AST_general_expr general_expr;
    AST_stmt stmt;
    AST_casestmt casestmt;
    AST_decl_cases decl_cases;
    AST_full_par_func_header full_par_func_header;
    AST_full_func_dcl full_func_dcl;
    AST_dcl_stmt dcl_stmt;
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
    
%type <strval> program global_declaration global_declarations enum_declaration
%type <strval> enum_body id_list variable assignment expression_list listexpression
%type <strval> init_values
%type <strval> global_var_declaration func_declaration full_func_declaration 
%type <strval> full_par_func_header decl_statements
%type <strval> switch_tail
%type <strval> in_item main_function main_header

%type <access> access
%type <intval> decltype // As booleans

%type <class_dcl> class_declaration 
%type <class_body> class_body
%type <passvar> pass_variabledef
%type <typedef_dcl> typedef_declaration
%type <class_func_header_start> class_func_header_start nopar_class_func_header
%type <func_header_start> func_header_start nopar_func_header
%type <variabledef> variabledef
%type <constant> constant 
%type <type> typename standard_type dim dims listspec pass_list_dims
%type <identifier> func_class parent
%type <list> init_variabledefs variabledefs parameter_list parameter_types
%type <list> declarations fields union_body anonymous_union members_methods 
%type <list> statements in_list out_list casestatements 
%type <var_declaration> var_declaration field
%type <member> member
%type <union_dcl> union_declaration
%type <short_func_dcl> short_func_declaration short_par_func_header method
%type <member_or_method> member_or_method
%type <general_expr> general_expression optexpr out_item
%type <stmt> statement if_tail expression_statement if_statement while_statement 
%type <stmt> for_statement switch_statement return_statement io_statement 
%type <stmt> comp_statement
%type <casestmt> casestatement single_casestatement
%type <decl_cases> decl_cases


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
program:                                                                                    
                          global_declarations main_function                                 {}
                        ;
global_declarations:      global_declarations global_declaration                            {}
                        | %empty                                                            {}
                        ;
global_declaration:       typedef_declaration                                               {} // Completed
                        | enum_declaration                                                  {}
                        | class_declaration                                                 {} // Completed
                        | union_declaration                                                 {}
                        | global_var_declaration                                            {}
                        | func_declaration                                                  {}
                        ;
typedef_declaration:      T_TYPEDEF typename listspec T_ID dims T_SEMI                      {$$ = ast_typedef(id_make($4), $2, $3, $5);}
                        ;
typename:                 standard_type                                                     {$$ = $1;}
                        | T_ID                                                              {$$ = type_id(id_make($1));}
                        ;
standard_type:            T_CHAR                                                            {$$ = type_basic(TYPE_char);}         
                        | T_INT                                                             {$$ = type_basic(TYPE_int);}
                        | T_FLOAT                                                           {$$ = type_basic(TYPE_float);}
                        | T_STRING                                                          {$$ = type_basic(TYPE_str);}
                        | T_VOID                                                            {$$ = type_basic(TYPE_void);}
                        ;
listspec:                 T_LIST                                                            {$$ = type_list(NULL);} // Item is list
                        | %empty                                                            {$$ = NULL;} // Item is not list                               
                        ;
dims:                     dims dim                                                          {$$ = ast_dims($1, $2);}
                        | %empty                                                            {$$ = NULL;}
                        ;
dim:                      T_LBRACK T_ICONST T_RBRACK                                        {$$ = type_array($2, NULL);}                                        
                        | T_LBRACK T_RBRACK                                                 {$$ = type_array(-1, NULL);} // -1 stands for "Dynamically Find/Allocate memory"
                        ;
enum_declaration:         T_ENUM T_ID enum_body T_SEMI                                      {}
                        ;
enum_body:                T_LBRACE id_list T_RBRACE                                         {}
                        ;
id_list:                  id_list T_COMMA T_ID initializer                                  {} 
                        | T_ID initializer                                                  {}
                        ;
initializer:              T_ASSIGN init_value                                               {}
                        | %empty                                                            {}
                        ;
init_value:               expression                                                        {}
                        | T_LBRACE init_values T_RBRACE                                     {}
                        ;
expression:               expression T_OROP expression                                      {}
                        | expression T_ANDOP expression                                     {}
                        | expression T_EQUOP expression                                     {}
                        | expression T_RELOP expression                                     {}
                        | expression T_ADDOP expression                                     {}
                        | expression T_MULOP expression                                     {}
                        | T_NOTOP expression                                                {}
                        | T_ADDOP expression %prec UMINUS                                   {}
                        | T_SIZEOP expression                                               {} // ^ 
                        | T_INCDEC variable                                                 {}
                        | variable T_INCDEC                                                 {}
                        | variable                                                          {} // ^ Variable Required
                        | variable T_LPAREN expression_list T_RPAREN                        {} 
                        | T_LENGTH T_LPAREN general_expression T_RPAREN                     {}
                        | T_NEW T_LPAREN general_expression T_RPAREN                        {}
                        | constant                                                          {} // Complete                                                          
                        | T_LPAREN general_expression T_RPAREN                              {}
                        | T_LPAREN standard_type T_RPAREN                                   {} // Complete
                        | listexpression                                                    {}
                        ;
variable:                 variable T_LBRACK general_expression T_RBRACK                     {} 
                        | variable T_DOT T_ID                                               {}                 
                        | T_LISTFUNC T_LPAREN general_expression T_RPAREN                   {} 
                        | decltype T_ID                                                     {}                 
                        | T_THIS                                                            {}
                        ;
general_expression:       general_expression T_COMMA general_expression                     {}
                        | assignment                                                        {}
                        ;
assignment:               variable T_ASSIGN assignment                                      {}
                        | expression                                                        {}
                        ;
expression_list:          general_expression                                                {} // Abstract
                        | %empty                                                            {$$ = NULL;}
                        ;
constant:                 T_CCONST                                                          {$$ = ast_constant_cconst($1);}
                        | T_ICONST                                                          {$$ = ast_constant_iconst($1);}
                        | T_FCONST                                                          {$$ = ast_constant_fconst($1);}
                        | T_SCONST                                                          {$$ = ast_constant_sconst($1);}
                        ;
listexpression:           T_LBRACK expression_list T_RBRACK                                 {}
                        ;
init_values:              init_values T_COMMA init_value                                    {}
                        | init_value                                                        {}
                        ;
class_declaration:        T_CLASS T_ID class_body T_SEMI                                    {$$ = ast_class_dcl(id_make($2), $3);}     
                        ;
class_body:               parent T_LBRACE members_methods T_RBRACE                          {$$ = ast_class_body($1, $3);}
                        ;
parent:                   T_COLON T_ID                                                      {$$ = id_make($2);}  
                        | %empty                                                            {$$ = NULL;} 
                        ;
members_methods:          members_methods access member_or_method                           {$$ = list_add($1, (void *) ast_members_method($2, $3));}
                        | access member_or_method                                           {$$ = list_add(NULL, (void *) ast_members_method($1, $2));}
                        ;
access:                   T_PRIVATE T_COLON                                                 {$$=ACCESS_PRIVATE;}
                        | T_PROTECTED T_COLON                                               {$$=ACCESS_PROTECTED;}
                        | T_PUBLIC T_COLON                                                  {$$=ACCESS_PUBLIC;}
                        | %empty                                                            {$$=ACCESS_DEFAULT;}
                        ;
member_or_method:         member                                                            {$$ = ast_mom_member($1);}
                        | method                                                            {$$ = ast_mom_method($1);}
                        ;
member:                   var_declaration                                                   {$$ = ast_member_variable($1);}
                        | anonymous_union                                                   {$$ = ast_member_anon_union($1);}
                        ;
var_declaration:          typename variabledefs T_SEMI                                      {$$ = ast_var_declaration($1, $2);}                         
                        ;
variabledefs:             variabledefs T_COMMA variabledef                                  {$$ = list_add($1, (void *) $3);}
                        | variabledef                                                       {$$ = list_add(NULL, (void *) $1);}
                        ;
variabledef:              listspec T_ID dims                                                {$$ = ast_variabledef(id_make($2), $1, $3);}
                        ;
anonymous_union:          T_UNION union_body T_SEMI                                         {$$ = $2;}
                        ;
union_body:               T_LBRACE fields T_RBRACE                                          {$$ = $2;}
                        ;
fields:                   fields field                                                      {$$ = list_add($1, (void *) $2);}
                        | field                                                             {$$ = list_add(NULL, (void *) $1);}
                        ;
field:                    var_declaration                                                   {$$ = $1;}
                        ;
method:                   short_func_declaration                                            {$$ = $1;}
                        ;
short_func_declaration:   short_par_func_header T_SEMI                                      {$$ = $1;}
                        | nopar_func_header T_SEMI                                          {$$ = ast_short_func_dcl($1, NULL);}
                        ;
short_par_func_header:    func_header_start T_LPAREN parameter_types T_RPAREN               {$$ = ast_short_func_dcl($1, $3);}
                        ;
func_header_start:        typename listspec T_ID                                            {$$ = ast_func_header_start(id_make($3), $1, $2);}
                        ;
parameter_types:          parameter_types T_COMMA typename pass_list_dims                   {$$ = list_add($1, (void *) get_parameter_type($3, $4));}
                        | typename pass_list_dims                                           {$$ = list_add(NULL, (void *) get_parameter_type($1, $2));}
                        ;
pass_list_dims:           T_REFER                                                           {$$ = type_ref(NULL);}
                        | listspec dims                                                     {$$ = $1 ? $1 : $2;}
                        ;
nopar_func_header:        func_header_start T_LPAREN T_RPAREN                               {$$ = $1;}
                        ;
union_declaration:        T_UNION T_ID union_body T_SEMI                                    {$$ = ast_union_dcl(id_make($2), $3);}                     
                        ;
                                                                                            // Should we handle globals differently? Probably.. but yeah..
global_var_declaration:   typename init_variabledefs T_SEMI                                 {}
                        ;
init_variabledefs:        init_variabledefs T_COMMA init_variabledef                        {} // {$$ = list_add($1, (void *) $3);}
                        | init_variabledef                                                  {} // {$$ = list_add(NULL, (void *) $1);}
                        ;
init_variabledef:         variabledef initializer                                           {} // TODO: Update this to include initializer
                        ;
func_declaration:         short_func_declaration                                              {$$ = $1;}
                        | full_func_declaration                                               {$$ = $1;}   
                        ;
full_func_declaration:    full_par_func_header T_LBRACE decl_statements T_RBRACE              {$$ = ast_full_func_dcl_full_par($1, $3);}    
                        | nopar_class_func_header T_LBRACE decl_statements T_RBRACE           {$$ = ast_full_func_dcl_nopar_class($1, $3);}
                        | nopar_func_header T_LBRACE decl_statements T_RBRACE                 {$$ = ast_full_func_dcl_nopar($1, $3);}
                        ;
full_par_func_header:     class_func_header_start T_LPAREN parameter_list T_RPAREN            {$$ = ast_full_par_func_header_class($1, $3);}
                        | func_header_start T_LPAREN parameter_list T_RPAREN                  {$$ = ast_full_par_func_header_noclass($1, $3);}
                        ;
class_func_header_start:  typename listspec func_class T_ID                                 {$$ = ast_class_func_header_start(id_make($4), $3, $1, $2);} 
                        ;
func_class:               T_ID T_METH                                                       {$$ = id_make($1);}
                        ;
parameter_list:           parameter_list T_COMMA typename pass_variabledef                  {$$ = list_add($1, (void *) ast_parameter($3, $4));}
                        | typename pass_variabledef                                         {$$ = list_add(NULL, (void *) ast_parameter($1, $2));}
                        ;
pass_variabledef:         variabledef                                                       {$$ = ast_passvar_variable($1);}
                        | T_REFER T_ID                                                      {$$ = ast_passvar_ref(id_make($2));}
                        ;
nopar_class_func_header:  class_func_header_start T_LPAREN T_RPAREN                         {$$ = $1;}
                        ;
decl_statements:          declarations statements                                           {$$ = ast_dcl_stmt_dcls_stmts($1, $2);}
                        | declarations                                                      {$$ = ast_dcl_stmt_dcls($1);}
                        | statements                                                        {$$ = ast_dcl_stmt_stmts($1);}
                        | %empty                                                            {}
                        ;
declarations:             declarations decltype typename variabledefs T_SEMI                {$$ = list_add($1, (void *) ast_declaration($3, $2, $4));}
                        | decltype typename variabledefs T_SEMI                             {$$ = list_add(NULL, (void *) ast_declaration($2, $1, $3));}
                        ;
decltype:                 T_STATIC                                                          {$$=1;} // Is static
                        | %empty                                                            {$$=0;} // Is not static
                        ;
statements:               statements statement                                              {$$ = list_add($1, (void *)$2);}
                        | statement                                                         {$$ = list_add(NULL, (void *)$1);}
                        ;
statement:                expression_statement                                              {$$ = $1;}
                        | if_statement                                                      {$$ = $1;}
                        | while_statement                                                   {$$ = $1;}
                        | for_statement                                                     {$$ = $1;}
                        | switch_statement                                                  // {$$ = $1;}
                        | return_statement                                                  {$$ = $1;}
                        | io_statement                                                      {$$ = $1;}
                        | comp_statement                                                    {$$ = $1;}
                        | T_CONTINUE T_SEMI                                                 {$$ = ast_stmt_basic(STMT_CONTINUE);}
                        | T_BREAK T_SEMI                                                    {$$ = ast_stmt_basic(STMT_BREAK);}
                        | T_SEMI                                                            {$$ = ast_stmt_basic(STMT_SEMI);}
                        ;
expression_statement:     general_expression T_SEMI                                         {$$ = ast_expr_stmt($1);}
                        ;
if_statement:             T_IF T_LPAREN                                                     
                            general_expression T_RPAREN statement                           
                          if_tail                                                           {$$ = ast_if_stmt($3, $5, $6);}
                        ;
if_tail:                  T_ELSE                                                            
                            statement                                                       {$$ = $2;}
                        | %empty %prec LOWER_THAN_ELSE                                      {$$ = NULL;} // Careful with this null. ASSERT LATER?
                        ;
while_statement:          T_WHILE T_LPAREN                                                   
                            general_expression T_RPAREN statement                           {$$ = ast_while_stmt($3, $5);}
                        ;
for_statement:            T_FOR T_LPAREN                                                     
                            optexpr T_SEMI optexpr T_SEMI optexpr T_RPAREN statement        {$$ = ast_for_stmt($3, $5, $7, $9);}
                        ;
optexpr:                  general_expression                                                {$$ = $1;}
                        | %empty                                                            {$$ = NULL;} 
                        ;
switch_statement:         T_SWITCH T_LPAREN                                                 
                            general_expression T_RPAREN switch_tail                         {} // {$$ = ast_switch_stmt($3, $5);}
                        ;
switch_tail:              T_LBRACE decl_cases T_RBRACE                                      {}
                        | single_casestatement                                              {}
                        ;
decl_cases:               declarations casestatements                                       {$$ = ast_decl_cases_both($1, $2);}
                        | declarations                                                      {$$ = ast_decl_cases_single(DC_DECLARATION_ONLY, $1);}    
                        | casestatements                                                    {$$ = ast_decl_cases_single(DC_CASE_ONLY, $1);}     
                        | %empty                                                            {$$ = ast_decl_cases_empty();}
                        ;
casestatements:           casestatements casestatement                                      {$$ = list_add($1, (void *) $2);}
                        | casestatement                                                     {$$ = list_add(NULL, (void *) $1);}
                        ;                                                                       
casestatement:            T_CASE constant T_COLON casestatement                             {$$ = ast_casestmt_nextcase($2, $4);}
                        | T_CASE constant T_COLON statements                                {$$ = ast_casestmt_multi($2, $4);}                  
                        | T_DEFAULT T_COLON statements                                      {$$ = ast_casestmt_default($3);}            
                        ;                                                                       
single_casestatement:     T_CASE constant T_COLON single_casestatement                      {$$ = ast_casestmt_nextcase($2, $4);}
                        | T_CASE constant T_COLON statement                                 {$$ = ast_casestmt_single($2, $4);}           
                        ;
return_statement:         T_RETURN optexpr T_SEMI                                           {$$ = ast_return_stmt($2);}
                        ;
io_statement:             T_CIN T_INP in_list T_SEMI                                        {$$ = ast_io_stmt(STMT_INPUT, $3);}
                        | T_COUT T_OUT out_list T_SEMI                                      {$$ = ast_io_stmt(STMT_OUTPUT, $3);}
                        ;
in_list:                  in_list T_INP in_item                                             {$$ = list_add($1, (void *) $3);}  
                        | in_item                                                           {$$ = list_add(NULL, (void *) $1);}
                        ;
in_item:                  variable                                                          {}
                        ;
out_list:                 out_list T_OUT out_item                                           {$$ = list_add($1, (void *) $3);}  
                        | out_item                                                          {$$ = list_add(NULL, (void *) $1);}
                        ;
out_item:                 general_expression                                                {$$ = $1;}
                        ;
comp_statement:           T_LBRACE decl_statements T_RBRACE                                 {$$ = $2;}
                        ;
main_function:            main_header T_LBRACE decl_statements T_RBRACE                     {}                               
                        ;
main_header:              T_INT T_MAIN T_LPAREN T_RPAREN                                    {}
                        ;
%%