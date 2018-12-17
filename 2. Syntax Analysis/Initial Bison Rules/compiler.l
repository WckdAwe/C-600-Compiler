/*
  Dimitriadis Vasileios || 2116104
  Kouskouras Taxiarchis || 2116162
  Papageorgiou Grigoris || 2116025
 */
 
/* ====[STATEMENTS BLOCK]==== */

%{
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include "settings.h"
#include "bison.tab.h"

/** Extern from Bison **/
extern int flag_err_type;
extern void yyerror(char *message);

/** Flex specific variables **/
int lineno=1; // Program's line number
int line_init=-1; // For multiline comments & strings
char str_buf[MAX_STR_CONST];    
char* str_buf_ptr;

/** Flex specific functions **/
void TPRINT(int token_id);
void NPRINT(int token_id, int base);
void FPRINT(int token_id, int base);
void CPRINT();
int HexToInt(char* str);
int OctToInt(char* str);
int BinToInt(char* str);
float BinToFloat(char* str);
float HexToFloat(char* str);
float OctToFloat(char* str);
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
WHITESPACE          [ \t]*
NEWLINE             [\n]
ID                  \_*{LETTER}{ALPHANUM}*(_{ALPHANUM}+)*_?

/* ====[END STATEMENTS BLOCK]==== */

%%

 /* ====[RULES BLOCK]==== */

 /* Keywords */
"TYPEDEF"                                               {TPRINT(T_TYPEDEF); yylval.strval = strdup(yytext);
                                                            return T_TYPEDEF;}
"CHAR"                                                  {TPRINT(T_CHAR); yylval.strval = strdup(yytext);
                                                            return T_CHAR;}
"INT"                                                   {TPRINT(T_INT); yylval.strval = strdup(yytext);
                                                            return T_INT;}
"FLOAT"                                                 {TPRINT(T_FLOAT); yylval.strval = strdup(yytext);
                                                            return T_FLOAT;}
"STRING"                                                {TPRINT(T_STRING); yylval.strval = strdup(yytext);
                                                            return T_STRING;}
"CLASS"                                                 {TPRINT(T_CLASS); yylval.strval = strdup(yytext);
                                                            return T_CLASS;}
"PRIVATE"                                               {TPRINT(T_PRIVATE); yylval.strval = strdup(yytext);
                                                            return T_PRIVATE;}
"PROTECTED"                                             {TPRINT(T_PROTECTED); yylval.strval = strdup(yytext);
                                                            return T_PROTECTED;}
"PUBLIC"                                                {TPRINT(T_PUBLIC); yylval.strval = strdup(yytext);
                                                            return T_PUBLIC;}
"VOID"                                                  {TPRINT(T_VOID); yylval.strval = strdup(yytext);
                                                            return T_VOID;}
"STATIC"                                                {TPRINT(T_STATIC); yylval.strval = strdup(yytext);
                                                            return T_STATIC;}
"UNION"                                                 {TPRINT(T_UNION); yylval.strval = strdup(yytext);
                                                            return T_UNION;}
"ENUM"                                                  {TPRINT(T_ENUM); yylval.strval = strdup(yytext);
                                                            return T_ENUM;}
"LIST"                                                  {TPRINT(T_LIST); yylval.strval = strdup(yytext);
                                                            return T_LIST;}
"CONTINUE"                                              {TPRINT(T_CONTINUE); yylval.strval = strdup(yytext);
                                                            return T_CONTINUE;}
"BREAK"                                                 {TPRINT(T_BREAK); yylval.strval = strdup(yytext);
                                                            return T_BREAK;}
"IF"                                                    {TPRINT(T_IF); yylval.strval = strdup(yytext);
                                                            return T_IF;}
"ELSE"                                                  {TPRINT(T_ELSE); yylval.strval = strdup(yytext);
                                                            return T_ELSE;}
"WHILE"                                                 {TPRINT(T_WHILE); yylval.strval = strdup(yytext);
                                                            return T_WHILE;}
"FOR"                                                   {TPRINT(T_FOR); yylval.strval = strdup(yytext);
                                                            return T_FOR;}
"SWITCH"                                                {TPRINT(T_SWITCH); yylval.strval = strdup(yytext);
                                                            return T_SWITCH;}
"CASE"                                                  {TPRINT(T_CASE); yylval.strval = strdup(yytext);
                                                            return T_CASE;}
"DEFAULT"                                               {TPRINT(T_DEFAULT); yylval.strval = strdup(yytext);
                                                            return T_DEFAULT;}
"RETURN"                                                {TPRINT(T_RETURN); yylval.strval = strdup(yytext);
                                                            return T_RETURN;}
"LENGTH"                                                {TPRINT(T_LENGTH); yylval.strval = strdup(yytext);
                                                            return T_LENGTH;}
"NEW"                                                   {TPRINT(T_NEW); yylval.strval = strdup(yytext);
                                                            return T_NEW;}
"CIN"                                                   {TPRINT(T_CIN); yylval.strval = strdup(yytext);
                                                            return T_CIN;}
"COUT"                                                  {TPRINT(T_COUT); yylval.strval = strdup(yytext);
                                                            return T_COUT;}
"MAIN"                                                  {TPRINT(T_MAIN); yylval.strval = strdup(yytext);
                                                            return T_MAIN;}
"THIS"                                                  {TPRINT(T_THIS); yylval.strval = strdup(yytext);
                                                            return T_THIS;}
"SIZEOF"                                                {TPRINT(T_SIZEOP); yylval.strval = strdup(yytext);
                                                            return T_SIZEOP;}  

 /* List Items TODO: Check for \b with Dimitriou/Floro */
C(AD*|D+)R                                              {TPRINT(T_LISTFUNC); yylval.strval = strdup(yytext);
                                                            return T_LISTFUNC;}  
                                                            
                                                            
 /* ID */
{ID}                                                    {TPRINT(T_ID); yylval.strval = strdup(yytext);
                                                            return T_ID;}                                                       
 /* FLOAT HEX CONSTANT */
(0X)([1-9A-F]{HEXDIGIT}*)?\.(0*[1-9A-F]+{HEXDIGIT}*|0)  {FPRINT(T_FCONST, 16); yylval.doubleval = HexToFloat(yytext);
                                                            return T_FCONST;}
 /* FLOAT OCT CONSTANT */
(0O)([1-7]{OCTDIGIT}*)?\.(0*[1-7]+{OCTDIGIT}*|0)        {FPRINT(T_FCONST, 8); yylval.doubleval = OctToFloat(yytext);
                                                            return T_FCONST;}   
 /* FLOAT BIN CONSTANT */
(0B)(1{BINDIGIT}*)?\.(0*1+{BINDIGIT}*|0)                {FPRINT(T_FCONST, 2); yylval.doubleval = BinToFloat(yytext);
                                                            return T_FCONST;}
                                                            
 /* FLOAT DECIMAL CONSTANT */
(0|{NZDIGIT})?(\.)(0*[1-9]+{DIGIT}*|0){EXPONENT}        {FPRINT(T_FCONST, 10); yylval.doubleval = atof(yytext);
                                                            return T_FCONST;}
(0|{NZDIGIT})?(\.)(0*[1-9]+{DIGIT}*|0)                  {FPRINT(T_FCONST, 10); yylval.doubleval = atof(yytext);
                                                            return T_FCONST;}
(0|{NZDIGIT}){EXPONENT}                                 {FPRINT(T_FCONST, 10); yylval.doubleval = atof(yytext);
                                                            return T_FCONST;}
                                                            
 /* HEX CONSTANT */
0X[1-9A-F]{HEXDIGIT}*                                   {NPRINT(T_ICONST, 16); yylval.intval = HexToInt(yytext);
                                                            return T_ICONST;}
 /* OCT CONSTANT */
0O[1-7]{OCTDIGIT}*                                      {NPRINT(T_ICONST, 8);  yylval.intval = OctToInt(yytext);
                                                            return T_ICONST;}
 /* BIN CONSTANT */
0B1{BINDIGIT}*                                          {NPRINT(T_ICONST, 2);  yylval.intval = BinToInt(yytext);
                                                            return T_ICONST;}
 /* DECIMAL CONSTANT */
0|{NZDIGIT}                                             {NPRINT(T_ICONST, 10); yylval.intval = atoi(yytext);
                                                            return T_ICONST;}
                                                            
                                                            
                                                            
 /* Character Constants */
\'\\n\'                                                 {TPRINT(T_CCONST); yylval.strval = strdup(yytext);
                                                            return T_CCONST;}
\'\\f\'                                                 {TPRINT(T_CCONST); yylval.strval = strdup(yytext);
                                                            return T_CCONST;}
\'\\t\'                                                 {TPRINT(T_CCONST); yylval.strval = strdup(yytext);
                                                            return T_CCONST;}
\'\\r\'                                                 {TPRINT(T_CCONST); yylval.strval = strdup(yytext);
                                                            return T_CCONST;}
\'\\b\'                                                 {TPRINT(T_CCONST); yylval.strval = strdup(yytext);
                                                            return T_CCONST;}
\'\\v\'                                                 {TPRINT(T_CCONST); yylval.strval = strdup(yytext);
                                                            return T_CCONST;}   
    
    
    
    
    
\'{ASCII}\'                                             {TPRINT(T_CCONST); yylval.strval = strdup(yytext);
                                                            return T_CCONST;}
\'{ALPHANUM}\'                                          {TPRINT(T_CCONST); yylval.strval = strdup(yytext);
                                                            return T_CCONST;}

                        

                        
                                                            
 /* Operators */    
"||"                                                    {TPRINT(T_OROP); yylval.strval = strdup(yytext);
                                                            return T_OROP;}  
"&&"                                                    {TPRINT(T_ANDOP); yylval.strval = strdup(yytext);
                                                            return T_ANDOP;}  
"=="|"!="                                               {TPRINT(T_EQUOP); yylval.strval = strdup(yytext);
                                                            return T_EQUOP;}  
">="|"<="|">"|"<"                                       {TPRINT(T_RELOP); yylval.strval = strdup(yytext);
                                                            return T_RELOP;}
"++"|"--"                                               {TPRINT(T_INCDEC); yylval.strval = strdup(yytext);
                                                            return T_INCDEC;}                                                           
"+"|"-"                                                 {TPRINT(T_ADDOP); yylval.strval = strdup(yytext);
                                                            return T_ADDOP;}  
"*"|"/"|"%"                                             {TPRINT(T_MULOP); yylval.strval = strdup(yytext);
                                                            return T_MULOP;}  
"!"                                                     {TPRINT(T_NOTOP); yylval.strval = strdup(yytext);
                                                            return T_NOTOP;}  
                                                            

                                                            
 /* Other Lexical Tokens */
"("                                                     {TPRINT(T_LPAREN); yylval.strval = strdup(yytext);
                                                            return T_LPAREN;} 
")"                                                     {TPRINT(T_RPAREN); yylval.strval = strdup(yytext);
                                                            return T_RPAREN;} 
";"                                                     {TPRINT(T_SEMI); yylval.strval = strdup(yytext);
                                                            return T_SEMI;} 
"."                                                     {TPRINT(T_DOT); yylval.strval = strdup(yytext);
                                                            return T_DOT;} 
","                                                     {TPRINT(T_COMMA); yylval.strval = strdup(yytext);
                                                            return T_COMMA;} 
"="                                                     {TPRINT(T_ASSIGN); yylval.strval = strdup(yytext);
                                                            return T_ASSIGN;}
"::"                                                    {TPRINT(T_METH); yylval.strval = strdup(yytext);
                                                            return T_METH;}                                                             
":"                                                     {TPRINT(T_COLON); yylval.strval = strdup(yytext);
                                                            return T_COLON;} 
"["                                                     {TPRINT(T_LBRACK); yylval.strval = strdup(yytext);
                                                            return T_LBRACK;} 
"]"                                                     {TPRINT(T_RBRACK); yylval.strval = strdup(yytext);
                                                            return T_RBRACK;} 
"&"                                                     {TPRINT(T_REFER); yylval.strval = strdup(yytext);
                                                            return T_REFER;} 
"{"                                                     {TPRINT(T_LBRACE); yylval.strval = strdup(yytext);
                                                            return T_LBRACE;} 
"}"                                                     {TPRINT(T_RBRACE); yylval.strval = strdup(yytext);
                                                            return T_RBRACE;} 
">>"                                                    {TPRINT(T_INP); yylval.strval = strdup(yytext);
                                                            return T_INP;} 
"<<"                                                    {TPRINT(T_OUT); yylval.strval = strdup(yytext);
                                                            return T_OUT;} 
<INITIAL><<EOF>>                                        {TPRINT(T_EOF); yylval.strval = strdup(yytext);
                                                            return T_EOF;}
                                                            
                                                            
 /* Comments */
"/*"                                                    {BEGIN(STATE_COMMENT); str_buf_ptr = str_buf;line_init=0;}
<STATE_COMMENT>"*"+"/"                                  {BEGIN(INITIAL); *str_buf_ptr = '\0';
                                                            CPRINT();
                                                            line_init=-1;}
<STATE_COMMENT>"\n"                                     {lineno++;line_init++;}
<STATE_COMMENT>[^*\n]*                                  {char *yptr = yytext; 
                                                            while ( *yptr ) *str_buf_ptr++ = *yptr++;}
<STATE_COMMENT>[*]*                                     {}
<STATE_COMMENT><<EOF>>                                  {flag_err_type=1;yyerror("Unterminated comment"); return 0;}


"//"                                                    {BEGIN(STATE_INLINE_COMMENT); str_buf_ptr = str_buf;}
<STATE_INLINE_COMMENT>.                                 {}
<STATE_INLINE_COMMENT>[^\\\n\"]+                        {char *yptr = yytext; 
                                                            while ( *yptr ) *str_buf_ptr++ = *yptr++;}
<STATE_INLINE_COMMENT>"\n"                              {BEGIN(INITIAL);
                                                            *str_buf_ptr = '\0';
                                                            CPRINT();
                                                            lineno++;}

                                                            
 /* Strings */
\"                                                      {BEGIN(STATE_STRING); str_buf_ptr = str_buf;}
<STATE_STRING>\"                                        {BEGIN(INITIAL); *str_buf_ptr = '\0';
                                                            if(FLEX_DEBUG && FLEX_SHOW_STRINGS)
                                                                printf("STRING FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", str_buf, T_SCONST, lineno);
                                                            return T_SCONST;}
<STATE_STRING>\n                                        {flag_err_type=1;yyerror("Illegal input in string"); return 0;}
<STATE_STRING>\\n                                       {*str_buf_ptr++ = '\n';}
<STATE_STRING>\\f                                       {*str_buf_ptr++ = '\f';}
<STATE_STRING>\\t                                       {*str_buf_ptr++ = '\t';}
<STATE_STRING>\\r                                       {*str_buf_ptr++ = '\r';}
<STATE_STRING>\\b                                       {*str_buf_ptr++ = '\b';}
<STATE_STRING>\\v                                       {*str_buf_ptr++ = '\v';}
<STATE_STRING>\\\\                                      {*str_buf_ptr++ = '\\';}
<STATE_STRING>\\\"                                      {*str_buf_ptr++ = '"';}
<STATE_STRING>\\\n                                      {lineno++;}
<STATE_STRING>\\{ALPHANUM_}?                            {*str_buf_ptr++ = yytext[1];}
<STATE_STRING>[^\\\n\"]+                                {char *yptr = yytext; 
                                                            while ( *yptr ) *str_buf_ptr++ = *yptr++;}
<STATE_STRING><<EOF>>                                   {flag_err_type=1;yyerror("Unterminated string"); return 0;}

{WHITESPACE}                                            {}
{NEWLINE}                                               {lineno++;}

 /* Catch the rest */
.                                                       {yyerror("Illegal character");/**yyless(1);**/}
 /* ====[END RULES BLOCK]==== */ 

%%

/* ====[USER FUNCTIONS BLOCK]==== */


/* ====[END USER FUNCTIONS BLOCK]==== */

void TPRINT(int token_id){
    if(FLEX_DEBUG && FLEX_SHOW_TOKENS){
        printf("TOKEN FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", yytext, token_id, lineno);
    }    
}

void NPRINT(int token_id, int base){
    if(FLEX_DEBUG && FLEX_SHOW_NUMERIC){
        int number;
        if(base == 2) number = BinToInt(yytext);
        else if(base == 8) number = OctToInt(yytext);
        else if(base == 16) number = HexToInt(yytext);
        else number = atoi(yytext);
        printf("NUMBER FOUND: %d (%s) | FROM BASE: %d | TOKEN NUMBER: %d | LINE: %d\n", number, yytext, base, token_id, lineno);
    }
}

void FPRINT(int token_id, int base){
    if(FLEX_DEBUG && FLEX_SHOW_NUMERIC){
        float number;
        if(base == 2) number = BinToFloat(yytext);
        else if(base == 8) number = OctToFloat(yytext);
        else if(base == 16) number = HexToFloat(yytext);
        else number = atof(yytext);
        printf("FLOAT FOUND: %lf (%s) | FROM BASE: %d | TOKEN NUMBER: %d | LINE: %d\n", number, yytext, base, token_id, lineno);
    }
}

void CPRINT(){
    if(FLEX_DEBUG && FLEX_SHOW_COMMENTS){
        int line = line_init > 0 ? lineno-line_init : lineno;
        printf("COMMENT FOUND: %s | TOKEN NUMBER: %d | LINE: %d\n", str_buf, T_STRING, line);
    }
}

int HexToInt(char *str){
    return (int) strtol(&str[2], NULL, 16);
}

int OctToInt(char *str){
    return (int) strtol(&str[2], NULL, 8);
}

int BinToInt(char *str){
    return (int) strtol(&str[2], NULL, 2);
}

float BinToFloat(char* str){
    float number = 0.0;
    int i,length_real;
    char *character;
    character = strchr(str,'.');
    length_real = strlen(character)-1;
    number = (int)strtol(&str[2],&character,2);
    for(i=1;i<length_real;i++){
        number += (character[i] - '0') * (1/pow(2,i));
    }
    return number;
}

float OctToFloat(char* str){
    float number = 0.0;
    int i,length_real;
    char *character;
    character = strchr(str,'.');
    length_real = strlen(character)-1;
    number = (int)strtol(&str[2],&character,8);
    for(i=1;i<=length_real;i++){
        number += (character[i] - '0') * (1/pow(8,i));
    }
    return number;
}

float HexToFloat(char*str){
    float number = 0.0;
    int i,length_real;
    char *character;
    character = strchr(str,'.');
    length_real = strlen(character)-1;
    number = (int)strtol(&str[2],&character,16);
    for(i=1;i<=length_real;i++){
        if(character[i] <= '9')
			number += (character[i] - '0') * (1/pow(16,i));
		else
			number += (character[i] + 10 - 'A') * (1/pow(16,i)); /** TODO: CASE SENSITIVE **/
	}
    return number;
}
