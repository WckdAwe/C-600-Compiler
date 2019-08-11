/******************************************************************************
 *  CVS version:
 *     $Id: quad.h,v 1.2 2005/06/24 12:47:30 nickie Exp $
 ******************************************************************************
 *
 *  C header file : quad.h
 *  Project       : Llama Compiler
 *  Version       : 1.0 alpha
 *  Description   : Syntax for quadruples
 *
 *  Comments: (in Greek iso-8859-7)
 *  ---------
 *  Εθνικό Μετσόβιο Πολυτεχνείο.
 *  Σχολή Ηλεκτρολόγων Μηχανικών και Μηχανικών Υπολογιστών.
 *  Τομέας Τεχνολογίας Πληροφορικής και Υπολογιστών.
 *  Εργαστήριο Τεχνολογίας Λογισμικού
 */


#ifndef __QUAD_H__
#define __QUAD_H__


/* ---------------------------------------------------------------------
   ---------------------------- Header files ---------------------------
   --------------------------------------------------------------------- */

#include <stdio.h>

#include "general.h"
#include "types.h"


/* ---------------------------------------------------------------------
   ------------------------- Ορισμός τύπων -----------------------------
   --------------------------------------------------------------------- */

/* Δηλώσεις */

typedef struct Quad_tag * Quad;
typedef struct Quad_operand_tag * Quad_operand;
typedef struct Quad_simple_tag * Quad_simple;

typedef struct Quad_list_tag * Quad_list;


/* Απαριθμήσεις */

typedef enum {
   quad_opcode_array,
   quad_opcode_assign,
   quad_opcode_call,
   quad_opcode_dim,
   quad_opcode_div,
   quad_opcode_endu,
   quad_opcode_eq,
   quad_opcode_eqeq,
   quad_opcode_ge,
   quad_opcode_gt,
   quad_opcode_ifb,
   quad_opcode_jump,
   quad_opcode_jumpl,
   quad_opcode_label,
   quad_opcode_le,
   quad_opcode_lt,
   quad_opcode_minus,
   quad_opcode_mod,
   quad_opcode_ne,
   quad_opcode_nxeq,
   quad_opcode_par,
   quad_opcode_plus,
   quad_opcode_ret,
   quad_opcode_retv,
   quad_opcode_times,
   quad_opcode_unit,
   quad_opcode_exp,
   quad_opcode_and,
   quad_opcode_or,
   quad_opcode_not
} Quad_opname;

typedef enum {
   pass_byval,
   pass_byref,
   pass_ret
} PassMode;


/* Ορισμοί δομών */

typedef struct {
   Identifier id;
   Type typ;
   int offset;
   int nesting;
   bool byref;
} Object;

typedef struct {
   Identifier id;
   int unique;
   int paramBytes;
   int localBytes;
   int counter;
   bool hasResult;
} Function;

typedef struct {
   int num;
   Type typ;
   int offset;
} Temporary;

struct Quad_tag {
   int label;
   Quad_opname opname;
   Quad_operand op1, op2, op3;
};

struct Quad_operand_tag {
   enum {
      QUAD_simple,
      QUAD_deref,
      QUAD_addressof,
      QUAD_passmode,
      QUAD_quadnumber,
      QUAD_empty
   } kind;
   union {
      Quad_simple simple;
      PassMode passmode;
      int number;
  } u;
};

struct Quad_simple_tag {
   enum {
      SIMPLE_iconst,
      SIMPLE_true,
      SIMPLE_false,
      SIMPLE_cconst,
      SIMPLE_fconst,
      SIMPLE_strlit,
      SIMPLE_object,
      SIMPLE_function,
      SIMPLE_temporary,
      SIMPLE_result
   } kind;
   union {
      RepInt n;
      RepFloat f;
      RepChar c;
      RepString s;
      Object obj;
      Function fun;
      Temporary temp;
   } u;
};


/* Ορισμοί δομών για λίστες */

struct Quad_list_tag {
   Quad head;
   Quad_list tail;
};


/* ---------------------------------------------------------------------
   --------------------- Πρωτότυπα συναρτήσεων -------------------------
   --------------------------------------------------------------------- */

Quad quad (int label, Quad_opname opname,
           Quad_operand op1, Quad_operand op2, Quad_operand op3);

Quad_operand quad_operand_simple     (Quad_simple qs);
Quad_operand quad_operand_deref      (Quad_simple qs);
Quad_operand quad_operand_addressof  (Quad_simple qs);
Quad_operand quad_operand_passmode   (PassMode m);
Quad_operand quad_operand_quadnumber (int number);
Quad_operand quad_operand_empty      ();

Quad_simple quad_iconst    (RepInt n);
Quad_simple quad_true      ();
Quad_simple quad_false     ();
Quad_simple quad_cconst    (RepChar c);
Quad_simple quad_fconst    (RepFloat f);
Quad_simple quad_strlit    (RepString s);
Quad_simple quad_object    (Object obj);
Quad_simple quad_function  (Function fun);
Quad_simple quad_temporary (Temporary temp);
Quad_simple quad_result    ();

Quad_list quad_list (Quad q, Quad_list l);

extern bool printSimple;

void quad_print (FILE * f, Quad q);
void quad_list_print (FILE * f, Quad_list l);


#endif
