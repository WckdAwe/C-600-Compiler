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

// typedef struct TypeList_tag * TypeList;
// struct TypeList_tag {
//     Type type;                     /* Type of List                   */
//     TypeList next;                 /* Pointer to next Type           */
// };


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
        TYPE_ref,                         /* reference type (ref) &    */
    } kind; // IMPORTANT: Updating this requires updating reverse_type_kind[] in types.c
    union {
        struct {
            int dim;
            Type type;
        } t_array;
        struct {
            Type type;
        } t_list;
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
        struct {
            Identifier parent; // Here?
        } t_class;
    } u;
};



/* ---------------------------------------------------------------------
   --------------------- Πρωτότυπα συναρτήσεων -------------------------
   --------------------------------------------------------------------- */

Type type_basic (int kind); // TODO: Typedef kind?
Type type_func  (Type t1, Type t2);
Type type_ref   (Type t);
Type type_array (int dim, Type t);
Type type_list  (Type t);
// Type type_enum (); // TODO: Verify if needed later. Currently using basic
// Type type_union (); // TODO: Verify if needed later. Currently using basic
Type type_id    (Identifier id);

// TypeList   type_list_add(TypeList list, Type type);

#endif