/******************************************************************************
 *  CVS version:
 *     $Id: quad.c,v 1.2 2005/06/24 12:47:30 nickie Exp $
 ******************************************************************************
 *
 *  C code file : quad.c
 *  Project     : Llama Compiler
 *  Version     : 1.0 alpha
 *  Description : Syntax for quadruples
 *
 *  Comments: (in Greek iso-8859-7)
 *  ---------
 *  Εθνικό Μετσόβιο Πολυτεχνείο.
 *  Σχολή Ηλεκτρολόγων Μηχανικών και Μηχανικών Υπολογιστών.
 *  Τομέας Τεχνολογίας Πληροφορικής και Υπολογιστών.
 *  Εργαστήριο Τεχνολογίας Λογισμικού
 */


/* ---------------------------------------------------------------------
   ---------------------------- Header files ---------------------------
   --------------------------------------------------------------------- */

#include "error.h"
#include "quad.h"


/* ---------------------------------------------------------------------
   --------------------------- Μεταβλητές ------------------------------
   --------------------------------------------------------------------- */

bool printSimple = false;


/* ---------------------------------------------------------------------
   --------------------- Υλοποίηση συναρτήσεων -------------------------
   --------------------------------------------------------------------- */

Quad quad (int label, Quad_opname opname,
        Quad_operand op1, Quad_operand op2, Quad_operand op3)
{
    Quad result = new(sizeof(*result));
    result->label = label;
    result->opname = opname;
    result->op1 = op1;
    result->op2 = op2;
    result->op3 = op3;
    return result;
}

Quad_operand quad_operand_simple (Quad_simple qs)
{
    Quad_operand result = new(sizeof(*result));
    result->kind = QUAD_simple;
    result->u.simple = qs;
    return result;
}

Quad_operand quad_operand_deref (Quad_simple qs)
{
    Quad_operand result = new(sizeof(*result));
    result->kind = QUAD_deref;
    result->u.simple = qs;
    return result;
}

Quad_operand quad_operand_addressof (Quad_simple qs)
{
    Quad_operand result = new(sizeof(*result));
    result->kind = QUAD_addressof;
    result->u.simple = qs;
    return result;
}

Quad_operand quad_operand_passmode (PassMode m)
{
    Quad_operand result = new(sizeof(*result));
    result->kind = QUAD_passmode;
    result->u.passmode = m;
    return result;
}

Quad_operand quad_operand_quadnumber (int number)
{
    Quad_operand result = new(sizeof(*result));
    result->kind = QUAD_quadnumber;
    result->u.number = number;
    return result;
}

Quad_operand quad_operand_empty ()
{
    Quad_operand result = new(sizeof(*result));
    result->kind = QUAD_empty;
    return result;
}

Quad_simple quad_iconst (RepInt n)
{
    Quad_simple result = new(sizeof(*result));
    result->kind = SIMPLE_iconst;
    result->u.n = n;
    return result;
}

Quad_simple quad_true ()
{
    Quad_simple result = new(sizeof(*result));
    result->kind = SIMPLE_true;
    return result;
}

Quad_simple quad_false ()
{
    Quad_simple result = new(sizeof(*result));
    result->kind = SIMPLE_false;
    return result;
}

Quad_simple quad_cconst (RepChar c)
{
    Quad_simple result = new(sizeof(*result));
    result->kind = SIMPLE_cconst;
    result->u.c = c;
    return result;
}

Quad_simple quad_fconst (RepFloat f)
{
    Quad_simple result = new(sizeof(*result));
    result->kind = SIMPLE_fconst;
    result->u.f = f;
    return result;
}

Quad_simple quad_strlit (RepString s)
{
    Quad_simple result = new(sizeof(*result));
    result->kind = SIMPLE_strlit;
    result->u.s = s;
    return result;
}

Quad_simple quad_object (Object obj)
{
    Quad_simple result = new(sizeof(*result));
    result->kind = SIMPLE_object;
    result->u.obj = obj;
    return result;
}

Quad_simple quad_function (Function fun)
{
    Quad_simple result = new(sizeof(*result));
    result->kind = SIMPLE_function;
    result->u.fun = fun;
    return result;
}

Quad_simple quad_temporary (Temporary temp)
{
    Quad_simple result = new(sizeof(*result));
    result->kind = SIMPLE_temporary;
    result->u.temp = temp;
    return result;
}

Quad_simple quad_result ()
{
    Quad_simple result = new(sizeof(*result));
    result->kind = SIMPLE_result;
    return result;
}

Quad_list quad_list (Quad q, Quad_list l)
{
    Quad_list result = new(sizeof(*result));
    result->head = q;
    result->tail = l;
    return result;
}


static void quad_simple_print (FILE * f, Quad_simple qs)
{
    ASSERT(qs != NULL);
    switch (qs->kind) {
        case SIMPLE_iconst:
            fprintf(f, "%d", qs->u.n);
            break;
        case SIMPLE_true:
            fprintf(f, "true");
            break;
        case SIMPLE_false:
            fprintf(f, "false");
            break;
        case SIMPLE_cconst:
            fprintf(f, "%s", qs->u.c);
            break;
        case SIMPLE_fconst:
            fprintf(f, "%lf", qs->u.f);
            break;
        case SIMPLE_strlit:
            fprintf(f, "%s", qs->u.s);
            break;
        case SIMPLE_object:
            if (printSimple)
                fprintf(f, "%s", id_name(qs->u.obj.id));
            else {
                fprintf(f, "obj[%s; ", id_name(qs->u.obj.id));
                Type_print(f, 0, qs->u.obj.typ);
                fprintf(f, "; %d; %d; %d]", qs->u.obj.offset, qs->u.obj.nesting,
                        qs->u.obj.byref);
            }
            break;
        case SIMPLE_function:
            if (printSimple)
                fprintf(f, "%s", id_name(qs->u.fun.id));
            else
                fprintf(f, "fun[%s; %d; %d; %d; %d; %d]", id_name(qs->u.fun.id),
                        qs->u.fun.unique, qs->u.fun.paramBytes,
                        qs->u.fun.localBytes, qs->u.fun.counter,
                        qs->u.fun.hasResult);
            break;
        case SIMPLE_temporary:
            if (printSimple)
                fprintf(f, "$%d", qs->u.temp.num);
            else {
                fprintf(f, "temp[$%d; ", qs->u.temp.num);
                Type_print(f, 0, qs->u.temp.typ);
                fprintf(f, "; %d]", qs->u.temp.offset);
            }
            break;
        case SIMPLE_result:
            fprintf(f, "$$");
            break;
    }
}

static void passmode_print (FILE * f, PassMode m)
{
    switch (m) {
        case pass_byval:  fprintf(f, "V");   break;
        case pass_byref:  fprintf(f, "R");   break;
        case pass_ret:    fprintf(f, "RET"); break;
    }
}

static void quad_operand_print (FILE * f, Quad_operand op)
{
    ASSERT(op != NULL);
    switch (op->kind) {
        case QUAD_simple:
            quad_simple_print(f, op->u.simple);
            break;
        case QUAD_deref:
            fprintf(f, "[");
            quad_simple_print(f, op->u.simple);
            fprintf(f, "]");
            break;
        case QUAD_addressof:
            fprintf(f, "{");
            quad_simple_print(f, op->u.simple);
            fprintf(f, "}");
            break;
        case QUAD_passmode:
            passmode_print(f, op->u.passmode);
            break;
        case QUAD_quadnumber:
            fprintf(f, "%d\n", op->u.number);
            break;
        case QUAD_empty:
            fprintf(f, "-");
            break;
    }
}

void quad_print (FILE * f, Quad q)
{
    ASSERT(q != NULL);
    fprintf(f, "%d: ", q->label);
    switch (q->opname) {
        case quad_opcode_array:    fprintf(f, "array, "); break;
        case quad_opcode_assign:   fprintf(f, ":=, ");    break;
        case quad_opcode_call:     fprintf(f, "call, ");  break;
        case quad_opcode_dim:      fprintf(f, "dim, ");   break;
        case quad_opcode_div:      fprintf(f, "/, ");     break;
        case quad_opcode_endu:     fprintf(f, "endu, ");  break;
        case quad_opcode_eq:       fprintf(f, "=, ");     break;
        case quad_opcode_eqeq:     fprintf(f, "==, ");    break;
        case quad_opcode_ge:       fprintf(f, ">=, ");    break;
        case quad_opcode_gt:       fprintf(f, ">, ");     break;
        case quad_opcode_ifb:      fprintf(f, "ifb, ");   break;
        case quad_opcode_jump:     fprintf(f, "jump, ");  break;
        case quad_opcode_jumpl:    fprintf(f, "jumpl, "); break;
        case quad_opcode_label:    fprintf(f, "label, "); break;
        case quad_opcode_le:       fprintf(f, "<=, ");    break;
        case quad_opcode_lt:       fprintf(f, "<, ");     break;
        case quad_opcode_minus:    fprintf(f, "-, ");     break;
        case quad_opcode_mod:      fprintf(f, "%%, ");    break;
        case quad_opcode_ne:       fprintf(f, "<>, ");    break;
        case quad_opcode_nxeq:     fprintf(f, "!=, ");    break;
        case quad_opcode_par:      fprintf(f, "par, ");   break;
        case quad_opcode_plus:     fprintf(f, "+, ");     break;
        case quad_opcode_ret:      fprintf(f, "ret, ");   break;
        case quad_opcode_retv:     fprintf(f, "retv, ");   break;
        case quad_opcode_times:    fprintf(f, "*, ");     break;
        case quad_opcode_unit:     fprintf(f, "unit, ");  break; 
        case quad_opcode_exp:      fprintf(f, "**, ");    break;   
        case quad_opcode_and:      fprintf(f, "and, ");   break;              
        case quad_opcode_or:       fprintf(f, "or, ");    break;
        case quad_opcode_not:      fprintf(f, "not, ");   break;
    }
    quad_operand_print(f, q->op1);   fprintf(f, ", ");
    quad_operand_print(f, q->op2);   fprintf(f, ", ");
    quad_operand_print(f, q->op3);   fprintf(f, "\n");
}

void quad_list_print (FILE * f, Quad_list l)
{
    for (; l != NULL; l = l->tail)
        quad_print(f, l->head);
}
