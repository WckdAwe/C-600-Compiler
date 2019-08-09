#include "hashtbl.h"

#ifndef types
#define types

struct astNode;
struct hashtbl;

typedef enum type_enum {VOID, INT, FLOAT, CHAR, ENUM, STRING, LIST, ARRAY, CLASS, UNION, FUNCTION} Type;
typedef enum boolean {FALSE, TRUE} Boolean;		//Maybe delete this after
typedef enum param_enum {VALUE, VAR} Param;
typedef enum operation_enum {CONTINUE, BREAK, IF, ELSE, WHILE, FOR, SWITCH, DEFAULT, RETURN, LENGTHM NEW, CIN, COUT, THIS, OROP, ANDOP, EQUOP, ADDOP, MULOP, INCDEC, SIZEOF, PARENS, BRACKS, SEMI, DOT, COMMA, REFER, METH, INP, OUT, ASSING} Operation;
typedef enum const_enum {NOTCONST, CONST} Const;	//Maybe delete this after


typedef struct Data_union{
	int ival;
	double dval;
	char cval;
	char *strval;
	Boolean bval;	//Maybe delete this after

}Data;

typedef struct T_data{
	Type type;
	Data data;
}T_Data;

struct Type_Struct;



//TODO: write code for list

typedef struct list{
	char *key // maybe change that to an int ? 
	Param param;
	int value;
	int offset;
	struct Type_Struct *field;
	struct list *next;
}


typedef struct Type_Struct{
	Type type;
	int size;
	int offset;
	
	union{
		Data data;
		
		//Array
		struct{
			type stype;
			struct Type_Struct *subts;
			int dimensions;
			struct Type_Struct *dims
		}array;
		
		//List
		List *list;
		
		//Function
		struct{
			int numberOfArgs;
			type returnType;
			List *list;	//list of args
			List *local //list of local var
			struct ast_node *ast_tree;
			
		}func;
	}T_union;
	
	struct Type_Struct *next;
}Type_Struct;

typedef struct TS_Array{
	int dimensions;
	Type_Struct *dims;
}TS_Array;

typedef union{
	struct ast_node *ast_node;
	struct Type_Struct *type_struct;
}AST_TS_Union;

//TODO: write signatures


#endif





