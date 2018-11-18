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
//TODO: we will probably need a hashing library or a hashing function
%}

%union{
	int val;
	double dval; 
}

%token<ival> T_INT T_ENUM T_LENGTH T_ICONST 
%token<fval> T_FCONST
%token T_TYPEDEF T_CHAR T_STRING T_SCONST 
%token T_CLASS T_PRIVATE T_PROTECTED T_PUBLIC T_STATIC T_UNION T_LIST T_CONTINUE T_BREAK T_IF T_ELSE T_WHILE T_FOR
%token T_SWITCH T_DEFAULT T_RETURN T_NEW T_CIN T_COUT T_MAIN T_THIS T_ID T_OROP T_ANDOP T_EQUIOP T_ADDOP T_MULOP T_INCDEC
%token T_SIZEOP T_LISTFUNC T_LPAREN T_RPAREN T_SEMI T_DOT T_COMMA T_ASSING T_COLON T_LBRACK T_RBRACK T_REFER T_LBRACE 
%token T_RBRACE T_METH T_INP T_OUT T_EOF

%left T_OROP T_ANDOP
%left T_ADDOP T

%%
	
%%

