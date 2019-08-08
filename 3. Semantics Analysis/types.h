#ifndef __TYPES_H__
#define __TYPES_H__

/*
    TYPEDEF, PRIVATE, PROTECTED, PUBLIC, VOID,
    STATIC,
    ~CONTINUE, BREAK
    NEW, MAIN??
 */

typedef enum type_enum {
    NOTHING, INTEGER, REAL, // REAL == Float
    CHARACTER, STRING, VOID, ARRAY, ENUMERATION, UNION, LIST, CLASS_NAME, FUNCTION_NAME} Type;
typedef enum param_enum {VARIABLE, VALUE} Param;
typedef enum static_enum {NO_STATIC, STATIC} Static;
typedef enum operation_enum {
    CONTINUE, BREAK, IF, ELSE, WHILE, FOR, SWITCH, CASE, DEFAULT, RETURN, LENGTH, NEW, CIN, COUT,
    THIS, SIZEOF, OROP, ANDOP, EQUOP, RELOP, INCDEC, ADDOP, MULOP, NOTOP, PARENS, SEMI, DOT, COMMA,
    ASSIGN, METH, COLON, BRACKS, REFER, BRACES, INP, OUT
} Operation; 

typedef union Data{
    int intdata;
    float floatdata;
    char chardata;
    char *strdata;
}Data;

typedef struct T_Data{
	Type type;
	Data data;
}T_Data;

typedef struct Type_Struct{
	Type type;
	int size;						//megethos typou
	// int offset;
	
}Type_Struct;

// typedef struct Type_tag *Type;
// struct Type_tag {
//     enum {
//         TYPE_int,
//         TYPE_float,
//         TYPE_char,
//         TYPE_string, /* Is this required? string => array[char] */
//         TYPE_void,
//         TYPE_enum, /* Is this required? enum => array[int]*/
//         TYPE_array,
//         TYPE_list, /* Can we unify them? c++600.pdf | 9 */
//         TYPE_class,
//         TYPE_func,
//         TYPE_union,                     
//         TYPE_unknown, /* Should i remove this? */
//     } kind;
//     union {
//         struct {
//             int dim;
//             Type type;
//         } t_array;  /* Type will either be an array.. */
//         struct {
//             Type type;
//         } t_ref;   /* A simple type... */
//         struct {
//             Type type1; /* .. */
//             Type type2; /* .. */
//         } t_func;  /* Or a function */
//     } u;
// };

#endif
