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

#ifndef YY_YY_BISON_H_INCLUDED
# define YY_YY_BISON_H_INCLUDED
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
    T_EOF = 0,
    T_ICONST = 258,
    T_FCONST = 259,
    T_TYPEDEF = 260,
    T_CHAR = 261,
    T_STRING = 262,
    T_SCONST = 263,
    T_CLASS = 264,
    T_PRIVATE = 265,
    T_PROTECTED = 266,
    T_PUBLIC = 267,
    T_STATIC = 268,
    T_UNION = 269,
    T_LIST = 270,
    T_CONTINUE = 271,
    T_BREAK = 272,
    T_IF = 273,
    T_ELSE = 274,
    T_WHILE = 275,
    T_FOR = 276,
    T_SWITCH = 277,
    T_DEFAULT = 278,
    T_RETURN = 279,
    T_NEW = 280,
    T_CIN = 281,
    T_COUT = 282,
    T_MAIN = 283,
    T_THIS = 284,
    T_ID = 285,
    T_OROP = 286,
    T_ANDOP = 287,
    T_EQUOP = 288,
    T_ADDOP = 289,
    T_MULOP = 290,
    T_INCDEC = 291,
    T_SIZEOP = 292,
    T_LISTFUNC = 293,
    T_LPAREN = 294,
    T_RPAREN = 295,
    T_SEMI = 296,
    T_DOT = 297,
    T_COMMA = 298,
    T_COLON = 299,
    T_LBRACK = 300,
    T_RBRACK = 301,
    T_REFER = 302,
    T_LBRACE = 303,
    T_RBRACE = 304,
    T_METH = 305,
    T_INP = 306,
    T_OUT = 307,
    T_ASSIGN = 308,
    T_CASE = 309,
    T_CCONST = 310,
    T_FLOAT = 311,
    T_NOTOP = 312,
    T_RELOP = 313,
    T_VOID = 314,
    T_ENUM = 315,
    T_INT = 316,
    T_LENGTH = 317,
    UMINUS = 318,
    LOWER_THAN_ELSE = 319
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 38 "bison.y" /* yacc.c:1909  */

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
    AST_switch_tail switch_tail;
    AST_init_value init_value;
    AST_expr expr;
    AST_enum_dcl enum_dcl;
    AST_func_dcl func_dcl;
    AST_init_variabledef init_variabledef;
    AST_global_var_declaration global_var_declaration;
    AST_assignment assignment;
    AST_variable variable;
    AST_exprlist exprlist;
    AST_global_decl global_decl;
    AST_program program;

#line 166 "bison.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_BISON_H_INCLUDED  */
