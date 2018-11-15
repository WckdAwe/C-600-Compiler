/*
  Dimitriadis Vasileios || 2116104
  Kouskouras Taxiarchis || 2116162
  Papageorgiou Grigoris || 2116025
 */
 
// Keywords
#define T_TYPEDEF        1
#define T_CHAR           2
#define T_INT            3
#define T_FLOAT          4
#define T_STRING         5
#define T_CLASS          6
#define T_PRIVATE        7
#define T_PROTECTED      8
#define T_PUBLIC         9
#define T_STATIC        10
#define T_UNION         11
#define T_ENUM          12
#define T_LIST          13
#define T_CONTINUE      14
#define T_BREAK         15
#define T_IF            16
#define T_ELSE          17
#define T_WHILE         18
#define T_FOR           19
#define T_SWITCH        20
#define T_DEFAULT       21
#define T_RETURN        22
#define T_LENGTH        23
#define T_NEW           24
#define T_CIN           25
#define T_COUT          26
#define T_MAIN          27
#define T_THIS          28

// Identifier
#define T_ID            29

// Basic Constants
#define T_ICONST        30
#define T_FCONST        31
#define T_CCONST        32
#define T_SCONST        33

// Operators
#define T_OROP          34
#define T_ANDOP         35
#define T_EQUOP         36
#define T_RELOP         37
#define T_ADDOP         38
#define T_MULOP         39
#define T_NOTOP         40
#define T_INCDEC        41   // ++ -- ?
#define T_SIZEOP        42

// List Items
#define T_LISTFUNC      43

// Other Lexical Tokens
#define T_LPAREN        44
#define T_RPAREN        45
#define T_SEMI          46
#define T_DOT           47
#define T_COMMA         48
#define T_ASSIGN        49
#define T_COLON         50
#define T_LBRACK        51
#define T_RBRACK        52
#define T_REFER         53
#define T_LBRACE        54
#define T_RBRACE        55
#define T_METH          56
#define T_INP           57
#define T_OUT           58
#define T_EOF            0



#define MAX_ERRORS       0
#define MAX_STR_CONST  256

#ifndef FLEX_DEBUG
#define FLEX_DEBUG      1
#define SHOW_TOKENS     1
#define SHOW_COMMENTS   1
#define SHOW_NUMERIC    1
#define SHOW_STRINGS    1
#endif