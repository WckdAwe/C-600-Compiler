
#ifndef __TYPES_H__
#define __TYPES_H__

/*
    TYPEDEF, 
    ~PRIVATE, PROTECTED, PUBLIC, VOID,
    STATIC,
    ~CONTINUE, BREAK
    NEW, MAIN??
 */

typedef enum type_enum {
    NOTHING, INT, FLOAT, CHAR, STR, VOID, 
    ARRAY, ENUM, UNION, LIST, CLASS, FUNC,
} Type;
typedef enum param_enum {VARIABLE, VALUE} Param;
typedef enum static_enum {NO_STATIC, STATIC} Static;
typedef enum operation_enum {
    CONTINUE, BREAK, IF, ELSE, WHILE, FOR, SWITCH, CASE, DEFAULT, RETURN, LENGTH, NEW, CIN, COUT,
    THIS, SIZEOF, OROP, ANDOP, EQUOP, RELOP, INCDEC, ADDOP, MULOP, NOTOP, PARENS, SEMI, DOT, COMMA,
    ASSIGN, METH, COLON, BRACKS, REFER, BRACES, INP, OUT, LEAF
} Operation; 

typedef union Data{
    int intdata;
    float floatdata;
    char chardata;
    char *strdata;
}Data;

typedef struct Type_Struct{
	Type type;
	int size;						//megethos typou
	// int offset;

    union {
        /** CONSTANT (e.x Int/Float/Char/String) **/
        Data data;

        // struct {
        //     int dim;
        //     Type type;
        // } t_array;  /* Type will either be an array.. */
        // struct {
        //     Type type;
        // } t_ref;   /* A simple type... */
        // struct {
        //     Type type1; /* .. */
        //     Type type2; /* .. */
        // } t_func;  /* Or a function */
    } u;
	
    // Type_Struct *next;           // Shouldn't this be part of an array?
}Type_Struct;

typedef struct list{
	char *key;
	// Param param;
	int value;
	// int offset;
	struct Type_Struct *field;
	struct list *next;
}List;

/*
ALTERNATIVE LIST : CHECK THIS LATER
typedef struct enum{
    Operation op;
    char *name;

    struct list values;
}Enum;
*/



typedef struct TS_Array{
	int dimensions;
	Type_Struct *dims;
}TS_Array;

typedef union TS_Union{
	struct ast_node *ast_node;
	Type_Struct *type_struct;
}AST_TS_Union;

typedef struct For_List{
	char *key;
	struct ast_node *cond;
	struct For_List *next;
}For_List;


Type_Struct *ts_create_standard_type(Type type);



List *list_create_node(char *name);
List *list_add_node(List *rl, List *node);
List *list_addType(List *rl, Type_Struct *ts);
#endif
