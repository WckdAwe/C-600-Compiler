#include "hashtbl.h>

#ifndef types
#define types

struct astNode;
struct hashtbl;

typedef enum type_enum {VOID, INT, FLOAT, CHAR, ENUM, STRING, LIST, ARRAY, CLASS, UNION, FUNCTION} Type;
typedef enum boolean {FALSE, TRUE} Boolean;
typedef enum param_enum {VALUE, VAR} Param;
typedef enum operation_enum {CONTINUE, BREAK, IF, ELSE, WHILE, FOR, SWITCH, DEFAULT, RETURN, LENGTHM NEW, CIN, COUT, THIS, OROP, ANDOP, EQUOP, ADDOP, MULOP, INCDEC, SIZEOF, PARENS, BRACKS, SEMI, DOT, COMMA, REFER, METH, INP, OUT, ASSING} Operation;
typedef enum const_enum {NOTCONST, CONST} Const;


typedef struct Data_union{
	int ival;
	double dval;
	char cval;
	char *strval;
	Boolean bval;

}Data;

typedef struct T_data{
	Type type;
	Data data;
}T_Data;

struct Type_struct;

//TODO: write code for list



#endif





