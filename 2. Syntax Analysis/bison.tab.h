/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_BISON_TAB_H_INCLUDED
# define YY_YY_BISON_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_INT = 258,
    T_ENUM = 259,
    T_LENGTH = 260,
    T_ICONST = 261,
    T_FCONST = 262,
    T_TYPEDEF = 263,
    T_CHAR = 264,
    T_STRING = 265,
    T_SCONST = 266,
    T_CLASS = 267,
    T_PRIVATE = 268,
    T_PROTECTED = 269,
    T_PUBLIC = 270,
    T_STATIC = 271,
    T_UNION = 272,
    T_LIST = 273,
    T_CONTINUE = 274,
    T_BREAK = 275,
    T_IF = 276,
    T_ELSE = 277,
    T_WHILE = 278,
    T_FOR = 279,
    T_SWITCH = 280,
    T_DEFAULT = 281,
    T_RETURN = 282,
    T_NEW = 283,
    T_CIN = 284,
    T_COUT = 285,
    T_MAIN = 286,
    T_THIS = 287,
    T_ID = 288,
    T_OROP = 289,
    T_ANDOP = 290,
    T_EQUIOP = 291,
    T_ADDOP = 292,
    T_MULOP = 293,
    T_INCDEC = 294,
    T_SIZEOP = 295,
    T_LISTFUNC = 296,
    T_LPAREN = 297,
    T_RPAREN = 298,
    T_SEMI = 299,
    T_DOT = 300,
    T_COMMA = 301,
    T_ASSING = 302,
    T_COLON = 303,
    T_LBRACK = 304,
    T_RBRACK = 305,
    T_REFER = 306,
    T_LBRACE = 307,
    T_RBRACE = 308,
    T_METH = 309,
    T_INP = 310,
    T_OUT = 311,
    T_EOF = 312,
    T_ASSIGN = 313,
    T_CASE = 314,
    T_CCONST = 315,
    T_EQUOP = 316,
    T_FLOAT = 317,
    T_NOTOP = 318,
    T_RELOP = 319,
    T_VOID = 320,
    T = 321
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 33 "bison.y" /* yacc.c:1909  */

	int intval;
	double doubleval; 
    char *strval;

#line 127 "bison.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_BISON_TAB_H_INCLUDED  */
