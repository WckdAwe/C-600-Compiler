%{
#include <string.h>
#include <stdio.h>
#include "c600.h"
#include "types.h"
#include "symbol.h"
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

extern char str_buf[MAX_STR_CONST];    
extern char* str_buf_ptr;

extern char *yytext;


/* ---------------------------------------------------------------------
   --------------------- Local variables & functions  ------------------
   --------------------------------------------------------------------- */

// Type type;
SymbolEntry entry;
SymbolTable symbol_table;
Scope scope;
// Constant constant;
// ConstantData data;
// int function_counter = 0;

/** TODO: Write why split T_ICONST/T_FCONST **/
/** TODO: constant Union with type and val **/

/** EXTRACT THESE LATER **/
void set_array_type(Type array, Type t){
    ASSERT(array && t);
    ASSERT(array->kind == TYPE_array);
    Type tmp = array;
    while(tmp->u.t_array.type->kind == TYPE_array)
        tmp = tmp->u.t_array.type;
    tmp->u.t_array.type = t;
}
%}


%error-verbose

%union{
    int intval;
    float floatval; 
    char charval;
    char *strval;
    Type type_t;
    // ConstantData data;
    // struct Constant_tag constant;
    struct SymbolEntry_tag * symbol_entry; //SymbolEntry symbol_entry;
    struct EntryList_tag * entry_list;
    struct TypeList_tag * type_list;
    // Type typeval;
    // Type_Struct *tsval;
    // List *listval;
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
%type <strval> enum_body id_list initializer init_value expression variable general_expression assignment expression_list listexpression
%type <strval> init_values class_declaration class_body members_methods access member_or_method member var_declaration
%type <strval> anonymous_union union_body fields field method short_func_declaration short_par_func_header
%type <strval> nopar_func_header union_declaration global_var_declaration func_declaration full_func_declaration 
%type <strval> full_par_func_header nopar_class_func_header decl_statements declarations 
%type <strval> statements statement expression_statement if_statement if_tail while_statement for_statement optexpr switch_statement switch_tail decl_cases 
%type <strval> casestatements casestatement single_casestatement return_statement io_statement in_list in_item out_list out_item comp_statement main_function main_header

//%type <constant> constant
%type <intval> listspec decltype
%type <type_t> standard_type typename dim dims pass_list_dims
%type <symbol_entry> init_variabledef variabledef pass_variabledef func_class typedef_declaration func_header_start class_func_header_start
%type <symbol_entry> parent
%type <entry_list> init_variabledefs variabledefs parameter_list
%type <type_list> parameter_types

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
program:                                                                                    {symbol_table=symbol_make(28447);scope_open(symbol_table);}
                        global_declarations main_function     
                                                                                            {scope = symbol_table->currentScope; scope_close(symbol_table); printf("\n\n\n--------------------------------\n\n\n");scope_print(scope, 1);}
                        ;
global_declarations:      global_declarations global_declaration
                        | %empty {}
                        ;
global_declaration:       typedef_declaration                                               {}
                        | enum_declaration
                        | class_declaration
                        | union_declaration
                        | global_var_declaration
                        | func_declaration
                        ;
typedef_declaration:      T_TYPEDEF typename listspec T_ID dims T_SEMI                      {
                                                                                                ASSERT(!($3 == 1 && $5 != NULL));
                                                                                                ASSERT($2 != NULL);
                                                                                                $$ = entry = symbol_enter(symbol_table, id_make($4), 1);
                                                                                                entry->entry_type = ENTRY_VARIABLE;
                                                                                                if($3){ // If TypeDef is list.
                                                                                                    entry->e.variable.type = type_list($2);
                                                                                                }else if($5){ // If TypeDef is array;
                                                                                                    entry->e.variable.type = $5;
                                                                                                    set_array_type($5, $2);
                                                                                                }else{
                                                                                                    entry->e.variable.type = $2;
                                                                                                }
                                                                                            }
                        ;
typename:                 standard_type                                                     {$$ = $1;}
                        | T_ID                                                              {
                                                                                                entry = symbol_lookup(symbol_table, id_make($1), LOOKUP_ALL_SCOPES, 1); 
                                                                                                if(entry){
                                                                                                    switch(entry->entry_type){
                                                                                                        case ENTRY_TYPE:
                                                                                                            $$ = entry->e.type.type;
                                                                                                            break;
                                                                                                        case ENTRY_VARIABLE:
                                                                                                            $$ = entry->e.variable.type;
                                                                                                            break;
                                                                                                        default:
                                                                                                            printf("Add more types for %s\n", reverse_entry_type[entry->entry_type]);
                                                                                                            break;
                                                                                                    }
                                                                                                }else{
                                                                                                    printf("No entry found for %s \n", $1);
                                                                                                }
                                                                                            }
                        ;
standard_type:            T_CHAR                                                            {$$ = type_basic(TYPE_char);} 
                        | T_INT                                                             {$$ = type_basic(TYPE_int);}
                        | T_FLOAT                                                           {$$ = type_basic(TYPE_float);}
                        | T_STRING                                                          {$$ = type_basic(TYPE_str);}
                        | T_VOID                                                            {$$ = type_basic(TYPE_void);}
                        ;
listspec:                 T_LIST                                                            {$$=1;} // 1 = is list // TODO: C600++.pdf
                        | %empty                                                            {$$=0;} // 0 = isn't list                                        
                        ;
dims:                     dims dim                                                          {//Executed only if [x][y]...[z] is present
                                                                                                if($1){
                                                                                                    $1->u.t_array.type = $2;
                                                                                                    $$ = $1;
                                                                                                }else{
                                                                                                    $$ = $2;
                                                                                                }
                                                                                            }
                        | %empty                                                            {$$=NULL;} // NULL = no dims
                        ;
dim:                      T_LBRACK T_ICONST T_RBRACK                                        {$$ = type_array($2, type_basic(TYPE_unknown));}// TODO: [x] Preassign memory.
                        | T_LBRACK T_RBRACK                                                 {$$ = type_array(-1, type_basic(TYPE_unknown));}// TODO: Dynamic memory? Assign later
                        ;
enum_declaration:         T_ENUM T_ID                                                       {entry = symbol_enter(symbol_table, id_make($2), 1);entry->entry_type = ENTRY_TYPE;entry->e.type.type=type_basic(TYPE_enum);scope=scope_open(symbol_table);entry->e.type.scope=scope;}
                            enum_body                                                       {scope_close(symbol_table);}
                            T_SEMI                                                  
                        ;
enum_body:                T_LBRACE id_list T_RBRACE
                        ;
id_list:                  id_list T_COMMA T_ID initializer                                  {entry = symbol_enter(symbol_table, id_make($3), 1);entry->entry_type = ENTRY_CONSTANT;entry->e.constant.type=type_basic(TYPE_int);} 
                        | T_ID                                                              {entry = symbol_enter(symbol_table, id_make($1), 1);entry->entry_type = ENTRY_CONSTANT;entry->e.constant.type=type_basic(TYPE_int);}
                          initializer
                        ;
initializer:              T_ASSIGN init_value                                               // TODO: ASSIGN INITIAL VALUES
                        | %empty {}                                                         // TODO: Assign default values
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
                        | constant                                                          {}                                                          
                        | T_LPAREN general_expression T_RPAREN
                        | T_LPAREN standard_type T_RPAREN
                        | listexpression
                        ;
variable:                 variable T_LBRACK general_expression T_RBRACK
                        | variable T_DOT T_ID                                               // .......
                        | T_LISTFUNC T_LPAREN general_expression T_RPAREN
                        | decltype T_ID                                                     {}//TODO: UPDATE DIS. {hashtbl_insert(hashtbl, $2, NULL, scope);} // TODO: STATIC ASSIGNMENT?
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
class_declaration:        T_CLASS T_ID                                                      {entry = symbol_enter(symbol_table, id_make($2), 1);entry->entry_type = ENTRY_TYPE;entry->e.type.type=type_basic(TYPE_class); scope = scope_open(symbol_table); entry->e.type.scope = scope;}
                            class_body                                              
                            T_SEMI                                                          {scope_close(symbol_table);}
                        ;
class_body:               parent T_LBRACE members_methods T_RBRACE                          {}
                        ;
parent:                   T_COLON T_ID                                                      {
                                                                                                // Entry must exist to provide inheritance...
                                                                                                // TODO: MUST ADD IT...
                                                                                                $$ = entry = symbol_lookup(symbol_table, id_make($2), LOOKUP_ALL_SCOPES, 1); // TODO: Handle Inheritance ..........
                                                                                            }// TODO: Update this {ht_complex_insert(hashtbl, $2, ts_create_standard_type(CLASS), scope);}
                        | %empty                                                            {} // No Inheritance
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
var_declaration:          typename variabledefs T_SEMI                                      {
                                                                                                EntryList list = $2; 
                                                                                                Type type;
                                                                                                while(list != NULL){
                                                                                                    entry = list->entry;
                                                                                                    switch(entry->entry_type){
                                                                                                        case ENTRY_CONSTANT:
                                                                                                            entry->e.constant.type = $1;
                                                                                                            break;
                                                                                                        case ENTRY_VARIABLE:
                                                                                                            type = entry->e.variable.type;
                                                                                                            ASSERT(type != NULL);
                                                                                                            switch(type->kind){
                                                                                                                case TYPE_list:
                                                                                                                    type->u.t_list.type = $1;
                                                                                                                    break;
                                                                                                                case TYPE_array:
                                                                                                                    set_array_type(type, $1);
                                                                                                                    break;
                                                                                                                default:
                                                                                                                    *type = *($1);  
                                                                                                                    break;
                                                                                                            }                                                                               
                                                                                                            break;
                                                                                                        default:
                                                                                                            printf("Entry type not defined (1)\n");
                                                                                                            break;
                                                                                                    }
                                                                                                    list = list->next;
                                                                                                }
                                                                                            }                         
                        ;
variabledefs:             variabledefs T_COMMA variabledef                                  {$$ = entry_list_add($1, $3);}
                        | variabledef                                                       {$$ = entry_list_add(NULL, $1);}
                        ;
variabledef:              listspec T_ID dims                                                {
                                                                                                ASSERT(!($1 == 1 && $3 != NULL));
                                                                                                $$ = entry = symbol_enter(symbol_table, id_make($2), 1); // TODO: Possibly change this to something more dynamic
                                                                                                entry->entry_type = ENTRY_VARIABLE;
                                                                                                if($3){ // If variable is array
                                                                                                    entry->e.variable.type = $3;
                                                                                                    set_array_type($3, type_basic(TYPE_unknown));
                                                                                                }else if($1){ // If variable is list
                                                                                                    entry->e.variable.type = type_list(type_basic(TYPE_unknown));
                                                                                                }else{
                                                                                                    entry->e.variable.type = type_basic(TYPE_unknown);
                                                                                                }
                                                                                            }
                        ;
anonymous_union:          T_UNION                                                           // TODO: Read more about anonymous unions. No scope should be added {scope_open(symbol_table);} // {scope++;scope_open(symbol_table);}
                            union_body                                                      // same ^ {scope_close(symbol_table);} //{hashtbl_get(hashtbl, scope);scope--;scope_close(symbol_table);}
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
short_func_declaration:   short_par_func_header T_SEMI                                      {scope_close(symbol_table);}
                        | nopar_func_header T_SEMI                                          {scope_close(symbol_table);}
                        ;
short_par_func_header:    func_header_start T_LPAREN parameter_types T_RPAREN               {
                                                                                                Type result_type = $1->e.function.result_type;
                                                                                                $1->entry_type = ENTRY_FUNCTION_DECLARATION;
                                                                                                $1->e.function_declaration.parameters = $3;
                                                                                                $1->e.function_declaration.result_type = result_type;
                                                                                            }
                        ;
func_header_start:        typename listspec T_ID                                            {
                                                                                                $$ = entry = symbol_enter(symbol_table, id_make($3), 1);
                                                                                                entry->entry_type = ENTRY_FUNCTION;
                                                                                                entry->e.function.result_type=$1;
                                                                                                scope_open(symbol_table);
                                                                                                //Need to pass parameters here...
                                                                                            }
                        ;
parameter_types:          parameter_types T_COMMA typename pass_list_dims                   {
                                                                                                if(!$4){ // If not ref or list/array
                                                                                                    $$ = type_list_add($1, $3);
                                                                                                }else{
                                                                                                    $$ = type_list_add($1, $4);
                                                                                                    switch($4->kind){
                                                                                                        case TYPE_ref:
                                                                                                            $4->u.t_ref.type = $3;
                                                                                                            break;
                                                                                                        case TYPE_list:
                                                                                                            $4->u.t_list.type = $3;
                                                                                                            break;
                                                                                                        case TYPE_array:
                                                                                                            set_array_type($4, $3);
                                                                                                            break;
                                                                                                        default:
                                                                                                            exit(1);
                                                                                                            break;
                                                                                                    }
                                                                                                }
                                                                                            }
                        | typename pass_list_dims                                           {
                                                                                                if(!$2){ // If not ref or list/array
                                                                                                    $$ = type_list_add(NULL, $1);
                                                                                                }else{
                                                                                                    $$ = type_list_add(NULL, $2);
                                                                                                    switch($2->kind){
                                                                                                        case TYPE_ref:
                                                                                                            $2->u.t_ref.type = $1;
                                                                                                            break;
                                                                                                        case TYPE_list:
                                                                                                            $2->u.t_list.type = $1;
                                                                                                            break;
                                                                                                        case TYPE_array:
                                                                                                            set_array_type($2, $1);
                                                                                                            break;
                                                                                                        default:
                                                                                                            printf("Unexpected Input\n");
                                                                                                            exit(1);
                                                                                                            break;
                                                                                                    }
                                                                                                }
                                                                                            }
                        ;
pass_list_dims:           T_REFER                                                           {$$ = type_ref(TYPE_unknown);}
                        | listspec dims                                                     {
                                                                                                ASSERT(!($1 == 1 && $2 != NULL));
                                                                                                if($1){
                                                                                                    $$ = type_list(TYPE_unknown);
                                                                                                }else if($2){
                                                                                                    $$ = $2;
                                                                                                }else{
                                                                                                    $$ = NULL;
                                                                                                }
                                                                                            }
                        ;
nopar_func_header:        func_header_start T_LPAREN T_RPAREN                               {/** NO SCOPE due to func_header_start! **/}
                        ;
union_declaration:        T_UNION T_ID                                                      {entry = symbol_enter(symbol_table, id_make($2), 1);entry->entry_type=ENTRY_TYPE;entry->e.type.type=type_basic(TYPE_union);scope=scope_open(symbol_table);entry->e.type.scope=scope;}
                            union_body          
                            T_SEMI                                                          {scope_close(symbol_table);} // {hashtbl_get(hashtbl, scope);scope--;scope_close(symbol_table);}
                        ;
                                                                                            // Should we handle globals differently? Probably.. but yeah..
global_var_declaration:   typename init_variabledefs T_SEMI                                 {
                                                                                                EntryList list = $2; 
                                                                                                Type type;
                                                                                                while(list != NULL){
                                                                                                    entry = list->entry;
                                                                                                    switch(entry->entry_type){
                                                                                                        case ENTRY_CONSTANT:
                                                                                                            entry->e.constant.type = $1;
                                                                                                            break;
                                                                                                        case ENTRY_VARIABLE:
                                                                                                            type = entry->e.variable.type;
                                                                                                            ASSERT(type != NULL);
                                                                                                            switch(type->kind){
                                                                                                                case TYPE_list:
                                                                                                                    type->u.t_list.type = $1;
                                                                                                                    break;
                                                                                                                case TYPE_array:
                                                                                                                    set_array_type(type, $1);
                                                                                                                    break;
                                                                                                                default:
                                                                                                                    *type = *($1); 
                                                                                                                    break;     
                                                                                                            }                                                                          
                                                                                                            break;
                                                                                                        default:
                                                                                                            printf("Entry type not defined (2)\n");
                                                                                                            break;
                                                                                                    }
                                                                                                    list = list->next;
                                                                                                }
                                                                                            }
                        ;
init_variabledefs:        init_variabledefs T_COMMA init_variabledef                        {$$ = entry_list_add($1, $3);} 
                        | init_variabledef                                                  {$$ = entry_list_add(NULL, $1);} 
                        ;
init_variabledef:         variabledef initializer                                           {$$ = $1;} // TODO: Update this to include initializer
                        ;
func_declaration:         short_func_declaration
                        | full_func_declaration
                        ;
full_func_declaration:    full_par_func_header T_LBRACE decl_statements T_RBRACE            {scope_close(symbol_table);}
                        | nopar_class_func_header T_LBRACE decl_statements T_RBRACE         {scope_close(symbol_table);}
                        | nopar_func_header T_LBRACE decl_statements T_RBRACE               {scope_close(symbol_table);}
                        ;
full_par_func_header:     class_func_header_start T_LPAREN parameter_list T_RPAREN          {$1->e.function.arguments = $3;}
                        | func_header_start T_LPAREN parameter_list T_RPAREN                {$1->e.function.arguments = $3;}
                        ;
//REMEMBER TO SET PARAMETERS FOR FUNCTION
class_func_header_start:  typename listspec func_class T_ID                                 {
                                                                                                // Implement owner & inheritance?
                                                                                                // TODO: Check about listspec?
                                                                                                $$ = entry = symbol_enter(symbol_table, id_make($4), 1);
                                                                                                entry->entry_type = ENTRY_FUNCTION;
                                                                                                entry->e.function.result_type=$1;
                                                                                                entry->e.function.parent=$3;
                                                                                                scope_open(symbol_table);
                                                                                            } 
                        ;
func_class:               T_ID T_METH                                                       {$$ = symbol_lookup(symbol_table, id_make($1), LOOKUP_CURRENT_SCOPE, 1); }
                        ;
parameter_list:           parameter_list T_COMMA typename pass_variabledef                  {
                                                                                                $$ = entry_list_add($1, $4);
                                                                                                entry = $4;
                                                                                                Type type = entry->e.parameter.type;
                                                                                                switch(type->kind){
                                                                                                    case TYPE_ref:
                                                                                                        type->u.t_ref.type = $3;
                                                                                                        break;
                                                                                                    default:
                                                                                                        *type = *($3);
                                                                                                        break;
                                                                                                }
                                                                                            }
                        | typename pass_variabledef                                         {
                                                                                                $$ = entry_list_add(NULL, $2);
                                                                                                entry = $2;
                                                                                                Type type = entry->e.parameter.type;
                                                                                                switch(type->kind){
                                                                                                    case TYPE_ref:
                                                                                                        type->u.t_ref.type = $1;
                                                                                                        break;
                                                                                                    default:
                                                                                                        *type = *($1);
                                                                                                        break;
                                                                                                }
                                                                                            }
                        ;
pass_variabledef:         variabledef                                                       {$$ = $1;$1->entry_type=ENTRY_PARAMETER;} // todo: Verify no conflicts/overrides
                        | T_REFER T_ID                                                      {
                                                                                                $$ = entry = symbol_enter(symbol_table, id_make($2), 1);
                                                                                                entry->entry_type=ENTRY_PARAMETER;
                                                                                                entry->e.parameter.type=type_ref(TYPE_unknown);
                                                                                            }
                        ;
nopar_class_func_header:  class_func_header_start T_LPAREN T_RPAREN                 
                        ;
decl_statements:          declarations statements
                        | declarations
                        | statements
                        | %empty {}
                        ;
declarations:             declarations decltype typename variabledefs T_SEMI                {   // TODO: HANDLE STATIC
                                                                                                EntryList list = $4; 
                                                                                                Type type;
                                                                                                while(list != NULL){
                                                                                                    entry = list->entry;
                                                                                                    switch(entry->entry_type){
                                                                                                        case ENTRY_CONSTANT:
                                                                                                            entry->e.constant.type = $3;
                                                                                                            break;
                                                                                                        case ENTRY_VARIABLE:
                                                                                                            type = entry->e.variable.type;
                                                                                                            ASSERT(type != NULL);
                                                                                                            switch(type->kind){
                                                                                                                case TYPE_list:
                                                                                                                    type->u.t_list.type = $3;
                                                                                                                    break;
                                                                                                                case TYPE_array:
                                                                                                                    set_array_type(type, $3);
                                                                                                                    break;
                                                                                                                default:
                                                                                                                    *type = *($3);  
                                                                                                                    break;
                                                                                                            }                                                                               
                                                                                                            break;
                                                                                                        default:
                                                                                                            printf("Entry type not defined (1)\n");
                                                                                                            break;
                                                                                                    }
                                                                                                    list = list->next;
                                                                                                }
                                                                                            }
                        | decltype typename variabledefs T_SEMI                             {
                                                                                                EntryList list = $3; 
                                                                                                Type type;
                                                                                                while(list != NULL){
                                                                                                    entry = list->entry;
                                                                                                    switch(entry->entry_type){
                                                                                                        case ENTRY_CONSTANT:
                                                                                                            entry->e.constant.type = $2;
                                                                                                            break;
                                                                                                        case ENTRY_VARIABLE:
                                                                                                            type = entry->e.variable.type;
                                                                                                            ASSERT(type != NULL);
                                                                                                            switch(type->kind){
                                                                                                                case TYPE_list:
                                                                                                                    type->u.t_list.type = $2;
                                                                                                                    break;
                                                                                                                case TYPE_array:
                                                                                                                    set_array_type(type, $2);
                                                                                                                    break;
                                                                                                                default:
                                                                                                                    *type = *($2);  
                                                                                                                    break;
                                                                                                            }                                                                               
                                                                                                            break;
                                                                                                        default:
                                                                                                            printf("Entry type not defined (1)\n");
                                                                                                            break;
                                                                                                    }
                                                                                                    list = list->next;
                                                                                                }
                                                                                            }
                        ;
decltype:                 T_STATIC                                                          {$$=1;}
                        | %empty                                                            {$$=0;}
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
if_statement:             T_IF T_LPAREN                                                     {scope_open(symbol_table);} //  {scope++;scope_open(symbol_table);}
                            general_expression T_RPAREN statement                           {scope_close(symbol_table);} // {hashtbl_get(hashtbl, scope);scope--;scope_close(symbol_table);}
                            if_tail
                        ;
if_tail:                  T_ELSE                                                            {scope_open(symbol_table);} //  {scope++;scope_open(symbol_table);}
                            statement                                                       {scope_close(symbol_table);} // {hashtbl_get(hashtbl, scope);scope--;scope_close(symbol_table);}
                        | %empty %prec LOWER_THAN_ELSE                                      {}
                        ;
while_statement:          T_WHILE T_LPAREN                                                  {scope_open(symbol_table);} //  {scope++;scope_open(symbol_table);} 
                            general_expression T_RPAREN statement                           {scope_close(symbol_table);} // {hashtbl_get(hashtbl, scope);scope--;scope_close(symbol_table);}
                        ;
for_statement:            T_FOR T_LPAREN                                                    {scope_open(symbol_table);} //  {scope++;scope_open(symbol_table);} 
                            optexpr T_SEMI optexpr T_SEMI optexpr T_RPAREN statement        {scope_close(symbol_table);} // {hashtbl_get(hashtbl, scope);scope--;scope_close(symbol_table);}
                        ;
optexpr:                  general_expression
                        | %empty {}
                        ;
switch_statement:         T_SWITCH T_LPAREN                                                 {scope_open(symbol_table);} //  {scope++;scope_open(symbol_table);}
                            general_expression T_RPAREN switch_tail                         {scope_close(symbol_table);} // {hashtbl_get(hashtbl, scope);scope--;scope_close(symbol_table);}
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
                        | T_CASE constant T_COLON                                           {scope_open(symbol_table);} //  {scope++;scope_open(symbol_table);}
                            statements                                                      {scope_close(symbol_table);} // {hashtbl_get(hashtbl, scope);scope--;scope_close(symbol_table);}
                        | T_DEFAULT T_COLON                                                 {scope_open(symbol_table);} //  {scope++;scope_open(symbol_table);} 
                            statements                                                      {scope_close(symbol_table);} // {hashtbl_get(hashtbl, scope);scope--;scope_close(symbol_table);}
                        ;
single_casestatement:     T_CASE constant T_COLON single_casestatement
                        | T_CASE constant T_COLON                                           {scope_open(symbol_table);} //  {scope++;scope_open(symbol_table);} 
                            statement                                                       {scope_close(symbol_table);} // {hashtbl_get(hashtbl, scope);scope--;scope_close(symbol_table);}
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
                            T_LBRACE decl_statements T_RBRACE                               {scope_close(symbol_table);} // {hashtbl_get(hashtbl, scope);scope--;scope_close(symbol_table);}
                        ;
main_header:              T_INT T_MAIN T_LPAREN T_RPAREN                                    {scope_open(symbol_table);} //  {scope++;scope_open(symbol_table);}
                        ;
%%