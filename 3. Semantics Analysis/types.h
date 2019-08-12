#ifndef __TYPES_H__
#define __TYPES_H__


/* ---------------------------------------------------------------------
   ---------------------------- Header files ---------------------------
   --------------------------------------------------------------------- */

#include <stdbool.h>

#include "general.h"


/* ---------------------------------------------------------------------
   ------------------------- Ορισμός τύπων -----------------------------
   --------------------------------------------------------------------- */

/* Δήλωση */

typedef struct Type_tag * Type;

typedef struct TypeList_tag * TypeList;
struct TypeList_tag {
    Type type;                     /* Type of List                   */
    TypeList next;                 /* Pointer to next Type           */
};


/* Ορισμός δομής */
extern char* reverse_type_kind[];         /* Type kind as String       */
struct Type_tag {
    enum {                                /***** Το είδος του τύπου ****/
        TYPE_unknown,                     /* unknown type              */
        TYPE_int,                         /* int                       */
        TYPE_float,                       /* float                     */
        TYPE_char,                        /* char                      */
        TYPE_str,                         /* string                    */
        TYPE_void,                        /* void                      */
        TYPE_array,                       /* array type                */
        TYPE_enum,                        /* enum type                 */
        TYPE_union,                       /* union type                */
        TYPE_list,                        /* list type                 */
        TYPE_class,                       /* class type                */
        TYPE_func,                        /* function (arrow)          */
        TYPE_id,                          /* user defined type (id)    */
        // TYPE_ref,                      /* reference type (ref) &    */
    } kind; // IMPORTANT: Updating this requires updating reverse_type_kind[] in types.c
    union {
        struct {
            int dim;
            Type type;
        } t_array;
        struct {
            Type type; 
        } t_ref;
        struct {
            Type type1;
            Type type2;
        } t_func;
        struct {
            Identifier id;
        } t_id;
    } u;
};



/* ---------------------------------------------------------------------
   --------------------- Πρωτότυπα συναρτήσεων -------------------------
   --------------------------------------------------------------------- */

Type type_basic (int kind); // TODO: Typedef kind?
Type type_func  (Type t1, Type t2);
// Type type_ref   (Type t);
Type type_array (int dim, Type t);
Type type_enum (); // TODO: Verify if needed later. Currently using basic
Type type_union (); // TODO: Verify if needed later. Currently using basic
Type type_id    (Identifier id);

TypeList   type_list_add(TypeList list, Type type);

#endif


// #ifndef __TYPES_H__
// #define __TYPES_H__

// /*
//     TYPEDEF, 
//     ~PRIVATE, PROTECTED, PUBLIC, VOID,
//     STATIC,
//     ~CONTINUE, BREAK
//     NEW, MAIN??
//  */

// typedef enum type_enum {
//     NOTHING, INT, FLOAT, CHAR, STR, VOID, 
//     ARRAY, ENUM, UNION, LIST, CLASS, FUNC,
// } Type;
// typedef enum param_enum {VARIABLE, VALUE} Param;
// typedef enum static_enum {NO_STATIC, STATIC} Static;
// typedef enum operation_enum {
//     CONTINUE, BREAK, IF, ELSE, WHILE, FOR, SWITCH, CASE, DEFAULT, RETURN, LENGTH, NEW, CIN, COUT,
//     THIS, SIZEOF, OROP, ANDOP, EQUOP, RELOP, INCDEC, ADDOP, MULOP, NOTOP, PARENS, SEMI, DOT, COMMA,
//     ASSIGN, METH, COLON, BRACKS, REFER, BRACES, INP, OUT, LEAF
// } Operation; 

// typedef union Data{
//     int intdata;
//     float floatdata;
//     char chardata;
//     char *strdata;
// }Data;

// typedef struct Type_Struct{
// 	Type type;
// 	int size;						//megethos typou
// 	// int offset;

//     union {
//         /** CONSTANT (e.x Int/Float/Char/String) **/
//         Data data;

//         // struct {
//         //     int dim;
//         //     Type type;
//         // } t_array;  /* Type will either be an array.. */
//         // struct {
//         //     Type type;
//         // } t_ref;   /* A simple type... */
//         // struct {
//         //     Type type1; /* .. */
//         //     Type type2; /* .. */
//         // } t_func;  /* Or a function */
//     } u;
	
//     // Type_Struct *next;           // Shouldn't this be part of an array?
// }Type_Struct;

// typedef struct list{
// 	char *key;
// 	// Param param;
// 	int value;
// 	// int offset;
// 	struct Type_Struct *field;
// 	struct list *next;
// }List;

/*
ALTERNATIVE LIST : CHECK THIS LATER
typedef struct enum{
    Operation op;
    char *name;

    struct list values;
}Enum;
*/



// typedef struct TS_Array{
// 	int dimensions;
// 	Type_Struct *dims;
// }TS_Array;

// typedef union TS_Union{
// 	struct ast_node *ast_node;
// 	Type_Struct *type_struct;
// }AST_TS_Union;

// typedef struct For_List{
// 	char *key;
// 	struct ast_node *cond;
// 	struct For_List *next;
// }For_List;


// Type_Struct *ts_create_standard_type(Type type);



// List *list_create_node(char *name);
// List *list_add_node(List *rl, List *node);
// List *list_addType(List *rl, Type_Struct *ts);
// #endif
