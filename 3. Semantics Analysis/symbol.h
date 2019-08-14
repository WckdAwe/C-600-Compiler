/******************************************************************************
 *  CVS version:
 *     $Id: symbol.h,v 1.2 2005/04/07 11:22:47 nickie Exp $
 ******************************************************************************
 *
 *  C header file : symbol.h
 *  Project       : Llama Compiler
 *  Version       : 1.0 alpha
 *  Description   : Generic symbol table
 *
 *  Comments: (in Greek iso-8859-7)
 *  ---------
 *  Εθνικό Μετσόβιο Πολυτεχνείο.
 *  Σχολή Ηλεκτρολόγων Μηχανικών και Μηχανικών Υπολογιστών.
 *  Τομέας Τεχνολογίας Πληροφορικής και Υπολογιστών.
 *  Εργαστήριο Τεχνολογίας Λογισμικού
 */


#ifndef __SYMBOL_H__
#define __SYMBOL_H__


/* ---------------------------------------------------------------------
   ---------------------------- Header files ---------------------------
   --------------------------------------------------------------------- */

#include <stdbool.h>
#include "types.h"


/* ---------------------------------------------------------------------
   -------------------------- Τύποι δεδομένων --------------------------
   --------------------------------------------------------------------- */

/* Πίνακας συμβόλων */

typedef struct SymbolTable_tag * SymbolTable;

/* Εγγραφή στον πίνακα συμβόλων */

typedef struct SymbolEntry_tag * SymbolEntry;
typedef union const_data ConstantData;
typedef struct Constant_tag Constant;

/* Λίστα απο εγγραφές του πίνακα συμβόλων */

typedef struct EntryList_tag * EntryList;

/* Σύνολο εγγραφών που βρίσκονται στην ίδια εμβέλεια */

typedef struct Scope_tag * Scope;

/* Τρόπος αναζήτησης στον πίνακα συμβόλων */

typedef enum {              /* Ψάξε:                             */
    LOOKUP_CURRENT_SCOPE,   /* - μόνο στην τρέχουσα εμβέλεια,
                                 ακόμα και αν είναι κρυφή        */
    LOOKUP_ALL_SCOPES       /* - σε όλες τις μη κρυφές εμβέλειες */
} LookupType;

struct SymbolTable_tag {
   /* Η διαχείριση αυτών των πεδίων γίνεται αυτόματα */
   unsigned int  hashTableSize;      /* Μέγεθος πίνακα κατακερματισμού */
   SymbolEntry * hashTable;          /* Πίνακας κατακερματισμού        */
   Scope         currentScope;       /* Τρέχουσα εμβέλεια              */

   /* Συμπληρώστε ό,τι άλλο θέλετε */
};

extern char *reverse_entry_type[];

struct SymbolEntry_tag {
   /* Η διαχείριση αυτών των πεδίων γίνεται αυτόματα */
   Identifier   id;                 /* Ονομα αναγνωριστικού            */
   Scope        scope;              /* Εμβέλεια όπου βρίσκεται         */
   SymbolEntry  nextInHash;         /* Επόμενη εγγραφή στον Π.Κ.       */
   SymbolEntry  nextInScope;        /* Επόμενη εγγραφή στην εμβέλεια   */

   enum {
       ENTRY_CONSTANT,
       ENTRY_FUNCTION,
       ENTRY_FUNCTION_DECLARATION,
       ENTRY_PARAMETER,
       ENTRY_VARIABLE,
       ENTRY_TYPE,
       ENTRY_IDENTIFIER,
       ENTRY_CLASS,
   } entry_type;

   union {
       struct Constant_tag{
           Type type;
           union const_data{
               int v_int;
               char v_char;
               float v_float;
               char *v_str;
           } value;
       } constant;

      struct {
        //   SymbolEntry *first_argument;
        //   SymbolEntry *last_argument;
        SymbolEntry parent;
        EntryList arguments;
        //   Type type;
          Type result_type;
        //   int counter; /* Μοναδικός για κάθε συνάρτηση, για να ξεχωρίζουμε
                        //   αυτές που έχουν το ίδιο όνομα */
      } function;

      struct {
          TypeList parameters;
          Type result_type;
      } function_declaration;

      struct {
          Type type;
      } parameter;

      struct {
          Type type;
      } variable;

      struct {
          Scope scope; /* Εμβέλεια όπου βρίσκεται ο τύπος και οι κατασκευαστές του */
          Type type;
      } type;

    //   struct {
    //       Type type;
    //   } identifier;

    //   struct {
    //       Type type;
    //       Type argument_type;
    //   } constructor;
      struct{
        Type type;
        SymbolEntry *first_member;
        SymbolEntry *first_method;
        SymbolEntry *last_member;
        SymbolEntry *last_method;
      } class;
        int counter;
   } e;
};

struct EntryList_tag {
    SymbolEntry entry;              /* Entry of List                   */
    EntryList next;                 /* Pointer to next Entry           */
};

struct Scope_tag {
    /* Η διαχείριση αυτών των πεδίων γίνεται αυτόματα */
    Scope        parent;                       /* Περιβάλλουσα εμβέλεια */
    SymbolEntry  entries;                      /* Σύμβολα της εμβέλειας */
    unsigned int nesting;                      /* Βάθος φωλιάσματος     */
    bool         hidden;                       /* Κρυφή εμβέλεια ή όχι  */

    /* Συμπληρώστε ό,τι άλλο θέλετε */
};

/* ---------------------------------------------------------------------
   ------ Πρωτότυπα των συναρτήσεων χειρισμού του πίνακα συμβολών ------
   --------------------------------------------------------------------- */

SymbolTable symbol_make   (unsigned int size);
Scope       scope_open    (SymbolTable table);
Scope       scope_close   (SymbolTable table);
void        scope_hide    (Scope scope, bool flag);
void        scope_insert  (SymbolTable table, Scope scope);
SymbolEntry symbol_enter  (SymbolTable table, Identifier id, bool err);
SymbolEntry symbol_lookup (SymbolTable table, Identifier id, LookupType type,
        bool err);
void        scope_print   (Scope scope, int go_deeper);

EntryList   entry_list_add(EntryList list, SymbolEntry entry);
#endif
