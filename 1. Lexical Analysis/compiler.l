/*
  Dimitriadis Vasileios || 2116104
  Kouskouras Taxiarchis || 2116162
  Papageorgiou Grigoris || 2116025
 */
 
/* ====[STATEMENTS BLOCK]==== */

%{
#include "compiler.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#ifndef FLEX_DEBUG
#define FLEX_DEBUG 1
#define FPRINT(x, y) printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_TYPEDEF, lineno);
#endif

int lineno=1; // Program's line number
int error_count = 0; // Program's total errors
                     // TODO: + on the ID? Probably wrong REGEX!
char str_buf[MAX_STR_CONST];    
char* str_buf_ptr;

void yyerror(char *message);    

/* TODO: Fix IDENTIFIER REGEX => (\_)?[a-zA-Z]([a-zA-Z0-9_](?!\_)*[a-zA-Z0-9])*   (\_)*[a-zA-Z]([a-zA-Z0-9_](?!(\_)*(\_)\1+))*  ==== ? */
%}

/* Read only 1 File */
%option noyywrap

/* Case insensitive tokens (e.x ClaSS == class) */
%option case-insensitive

/* Initial States */
%x STATE_COMMENT
%x STATE_INLINE_COMMENT
%x STATE_STRING

LETTER              [a-zA-Z]
DIGIT               [0-9]
BINDIGIT            [01]
OCTDIGIT            [0-7]
HEXDIGIT            [0-9A-F]
NZDIGIT             [1-9]{DIGIT}*
EXPONENT            E[+-]?(0|{NZDIGIT})
ALPHANUM            ({LETTER}|{DIGIT})
ALPHANUM_           ({ALPHANUM}|_)
ASCII               [ !"#$%&'()*+,-./:;<=>?@\[\\\]^_`{|}~]
WHITESPACE          [ \t]
ID                  \_*{LETTER}{ALPHANUM}*(_{ALPHANUM}+)*_?

/* ====[END STATEMENTS BLOCK]==== */

%%

 /* ====[RULES BLOCK]==== */

 /* Keywords */
"TYPEDEF"                                               {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_TYPEDEF, lineno); 
                                                            return T_TYPEDEF;}
"CHAR"                                                  {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_CHAR, lineno); 
                                                            return T_CHAR;}
"INT"                                                   {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_INT, lineno); 
                                                            return T_INT;}
"FLOAT"                                                 {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_FLOAT, lineno); 
                                                            return T_FLOAT;}
"STRING"                                                {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_STRING, lineno); 
                                                            return T_STRING;}
"CLASS"                                                 {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_CLASS, lineno); 
                                                            return T_CLASS;}
"PRIVATE"                                               {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_PRIVATE, lineno); 
                                                            return T_PRIVATE;}
"PROTECTED"                                             {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_PROTECTED, lineno); 
                                                            return T_PROTECTED;}
"PUBLIC"                                                {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_PUBLIC, lineno); 
                                                            return T_PUBLIC;}
"STATIC"                                                {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_STATIC, lineno); 
                                                            return T_STATIC;}
"UNION"                                                 {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_UNION, lineno); 
                                                            return T_UNION;}
"ENUM"                                                  {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_ENUM, lineno); 
                                                            return T_ENUM;}
"LIST"                                                  {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_LIST, lineno); 
                                                            return T_LIST;}
"CONTINUE"                                              {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_CONTINUE, lineno); 
                                                            return T_CONTINUE;}
"BREAK"                                                 {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_BREAK, lineno); 
                                                            return T_BREAK;}
"IF"                                                    {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_IF, lineno); 
                                                            return T_IF;}
"ELSE"                                                  {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_ELSE, lineno); 
                                                            return T_ELSE;}
"WHILE"                                                 {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_WHILE, lineno); 
                                                            return T_WHILE;}
"FOR"                                                   {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_FOR, lineno); 
                                                            return T_FOR;}
"SWITCH"                                                {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_SWITCH, lineno); 
                                                            return T_SWITCH;}
"DEFAULT"                                               {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_DEFAULT, lineno); 
                                                            return T_DEFAULT;}
"RETURN"                                                {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_RETURN, lineno); 
                                                            return T_RETURN;}
"LENGTH"                                                {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_LENGTH, lineno); 
                                                            return T_LENGTH;}
"NEW"                                                   {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_NEW, lineno); 
                                                            return T_NEW;}
"CIN"                                                   {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_CIN, lineno); 
                                                            return T_CIN;}
"COUT"                                                  {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_COUT, lineno); 
                                                            return T_COUT;}
"MAIN"                                                  {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_MAIN, lineno); 
                                                            return T_MAIN;}
"THIS"                                                  {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_THIS, lineno); 
                                                            return T_THIS;}
"SIZEOF"                                                {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_SIZEOP, lineno); 
                                                            return T_SIZEOP;}  

 /* List Items TODO: Check for \b with Dimitriou/Floro */
C(AD*|D+)R                                              {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_LISTFUNC, lineno); 
                                                            return T_LISTFUNC;}  
                                                            
                                                            
 /* ID */
{ID}                                                    {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_ID, lineno); 
                                                            return T_ID;}                                                       
 /* FLOAT HEX CONSTANT */
(0X)([1-9A-F]{HEXDIGIT}*)?\.(0*[1-9A-F]+{HEXDIGIT}*|0)  {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_FCONST, lineno); 
                                                            return T_FCONST;}
 /* FLOAT OCT CONSTANT */
(0O)([1-7]{OCTDIGIT}*)?\.(0*[1-7]+{OCTDIGIT}*|0)        {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_FCONST, lineno); 
                                                            return T_FCONST;}   
 /* FLOAT BIN CONSTANT */
(0B)(1{BINDIGIT}*)?\.(0*1+{BINDIGIT}*|0)                {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_FCONST, lineno); 
                                                            return T_FCONST;}
                                                            
 /* FLOAT DECIMAL CONSTANT */
(0|{NZDIGIT})?(\.)(0*[1-9]+{DIGIT}*|0){EXPONENT}        {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_FCONST, lineno); 
                                                            return T_FCONST;}
(0|{NZDIGIT})?(\.)(0*[1-9]+{DIGIT}*|0)                  {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_FCONST, lineno); 
                                                            return T_FCONST;}
(0|{NZDIGIT}){EXPONENT}                                 {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_FCONST, lineno); 
                                                            return T_FCONST;}
                                                            
 /* HEX CONSTANT */
0X[1-9A-F]{HEXDIGIT}*                                       {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_ICONST, lineno); 
                                                            return T_ICONST;}
 /* OCT CONSTANT */
0O[1-7]{OCTDIGIT}*                                      {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_ICONST, lineno); 
                                                            return T_ICONST;}
 /* BIN CONSTANT */
0B1{BINDIGIT}*                                          {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_ICONST, lineno); 
                                                            return T_ICONST;}
 /* DECIMAL CONSTANT */
0|{NZDIGIT}                                             {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_ICONST, lineno); 
                                                            return T_ICONST;}
                                                            
                                                            
                                                            
 /* Character Constants */
\'\\n\'                                                 {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_CCONST, lineno); 
                                                            return T_CCONST;}
\'\\f\'                                                 {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_CCONST, lineno); 
                                                            return T_CCONST;}
\'\\t\'                                                 {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_CCONST, lineno); 
                                                            return T_CCONST;}
\'\\r\'                                                 {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_CCONST, lineno); 
                                                            return T_CCONST;}
\'\\b\'                                                 {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_CCONST, lineno); 
                                                            return T_CCONST;}
\'\\v\'                                                 {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_CCONST, lineno); 
                                                            return T_CCONST;}   
    
    
    
    
    
\'{ASCII}\'                                             {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_CCONST, lineno); 
                                                            return T_CCONST;}
\'{ALPHANUM}\'                                          {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_CCONST, lineno); 
                                                            return T_CCONST;}

                        

                        
                                                            
 /* Operators */    
"||"                                                    {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_OROP, lineno); 
                                                            return T_OROP;}  
"&&"                                                    {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_ANDOP, lineno); 
                                                            return T_ANDOP;}  
"=="|"!="                                               {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_EQUOP, lineno); 
                                                            return T_EQUOP;}  
">="|"<="|">"|"<"                                       {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_RELOP, lineno); 
                                                            return T_RELOP;}
"++"|"--"                                               {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_INCDEC, lineno); 
                                                            return T_INCDEC;}                                                           
"+"|"-"                                                 {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_ADDOP, lineno); 
                                                            return T_ADDOP;}  
"*"|"/"|"%"                                             {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_MULOP, lineno); 
                                                            return T_MULOP;}  
"!"                                                     {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_NOTOP, lineno); 
                                                            return T_NOTOP;}  
                                                            

                                                            
 /* Other Lexical Tokens */
"("                                                     {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_LPAREN, lineno); 
                                                            return T_LPAREN;} 
")"                                                     {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_RPAREN, lineno); 
                                                            return T_RPAREN;} 
";"                                                     {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_SEMI, lineno); 
                                                            return T_SEMI;} 
"."                                                     {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_DOT, lineno); 
                                                            return T_DOT;} 
","                                                     {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_COMMA, lineno); 
                                                            return T_COMMA;} 
"="                                                     {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_ASSIGN, lineno); 
                                                            return T_ASSIGN;}
"::"                                                    {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_METH, lineno); 
                                                            return T_METH;}                                                             
":"                                                     {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_COLON, lineno); 
                                                            return T_COLON;} 
"["                                                     {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_LBRACK, lineno); 
                                                            return T_LBRACK;} 
"]"                                                     {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_RBRACK, lineno); 
                                                            return T_RBRACK;} 
"&"                                                     {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_REFER, lineno); 
                                                            return T_REFER;} 
"{"                                                     {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_LBRACE, lineno); 
                                                            return T_LBRACE;} 
"}"                                                     {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_RBRACE, lineno); 
                                                            return T_RBRACE;} 
">>"                                                    {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_INP, lineno); 
                                                            return T_INP;} 
"<<"                                                    {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_OUT, lineno); 
                                                            return T_OUT;} 
<INITIAL><<EOF>>                                        {printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, T_EOF, lineno); 
                                                            return T_EOF;}
                                                            
                                                            
 /* Comments */
"/*"                                                    {BEGIN(STATE_COMMENT);}
<STATE_COMMENT>"*/"                                     {BEGIN(INITIAL);}
<STATE_COMMENT>"\n"                                     {lineno++;}
<STATE_COMMENT>.                                        {}
<STATE_COMMENT><<EOF>>                                  {yyerror("Unterminated comment"); return 0;}

"//"                                                    {BEGIN(STATE_INLINE_COMMENT);}
<STATE_INLINE_COMMENT>"\n"                              {BEGIN(INITIAL);lineno++;}

 /* Strings */
\"                                                      {str_buf_ptr = str_buf; BEGIN(STATE_STRING);}
<STATE_STRING>\"                                        {*str_buf_ptr = '\0'; BEGIN(INITIAL);
                                                            printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", str_buf, T_STRING, lineno);
                                                            return T_STRING;}
<STATE_STRING>\n                                        {yyerror("Illegal input in string");}
<STATE_STRING>\\n                                       {*str_buf_ptr++ = '\n';}
<STATE_STRING>\\f                                       {*str_buf_ptr++ = '\f';}
<STATE_STRING>\\t                                       {*str_buf_ptr++ = '\t';}
<STATE_STRING>\\r                                       {*str_buf_ptr++ = '\r';}
<STATE_STRING>\\b                                       {*str_buf_ptr++ = '\b';}
<STATE_STRING>\\v                                       {*str_buf_ptr++ = '\v';}
<STATE_STRING>\\\n                                      {lineno++;}
<STATE_STRING>\\										{*str_buf_ptr--;lineno++;}
<STATE_STRING><<EOF>>                                   {yyerror("Unterminated comment"); return 0;}


{WHITESPACE}                                            {}
\n                                                      {lineno++;}

 /* Catch the rest */
.                                                       {yyerror("Illegal character");}
 /* ====[END RULES BLOCK]==== */

%%

/* ====[USER FUNCTIONS BLOCK]==== */


/* ====[END USER FUNCTIONS BLOCK]==== */

int main(int argc, char *argv[]){
    int token;
    
    ++argv; --argc; // ?
    if(argc > 0){
        yyin = fopen(argv[0], "r");
        if (yyin == NULL){
            perror ("Error opening file"); return -1;
        }
    }
    
    token = yylex();
    while(token != T_EOF){
        token = yylex();
    }
    
    if(error_count > 0){
        printf("Failed to analyze the program due to %d errors\n", error_count);
    }else{
        printf("Program analyzed successfully\n");
    }
    fclose(yyin);
    yyterminate();
}

void yyerror(char *message)
{
    error_count++;
    
    printf("ERROR at line %d caused by %s: %s\n", lineno, yytext, message);
    if(error_count == MAX_ERRORS){
        printf("Max errors detected\n");
        exit(-1);
    }
}
