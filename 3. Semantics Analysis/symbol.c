/******************************************************************************
 *  CVS version:
 *     $Id: symbol.c,v 1.2 2005/04/07 11:22:47 nickie Exp $
 ******************************************************************************
 *
 *  C code file : symbol.c
 *  Project     : Llama Compiler
 *  Version     : 1.0 alpha
 *  Description : Generic symbol table
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

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "general.h"
#include "error.h"
#include "symbol.h"
#include "types.h"


char* reverse_entry_type[] = {
    "CONST", "FUNC", "PARAM", "VAR", "TYPE", "CONSTR", "ID"
};

/* ---------------------------------------------------------------------
   -------------------------- Τύποι δεδομένων --------------------------
   --------------------------------------------------------------------- */


/* ---------------------------------------------------------------------
   ------ Υλοποίηση των συναρτήσεων χειρισμού του πίνακα συμβόλων ------
   --------------------------------------------------------------------- */

SymbolTable symbol_make (unsigned int size)
{
    SymbolTable result = new(sizeof(struct SymbolTable_tag));
    unsigned int i;

    result->hashTableSize = size;
    result->hashTable = new(size * sizeof(SymbolEntry));
    result->currentScope = NULL;

    for (i = 0; i < size; i++)
        result->hashTable[i] = NULL;

    return result;
}

Scope scope_open (SymbolTable table)
{
    Scope result = new(sizeof(struct Scope_tag));

    ASSERT(table != NULL);

    result->parent = table->currentScope;
    result->entries = NULL;
    result->nesting =
        table->currentScope != NULL ? table->currentScope->nesting + 1 : 1;
    result->hidden = false;
    table->currentScope = result;
    return result;
}

Scope scope_close (SymbolTable table)
{
    Scope result = table->currentScope;
    SymbolEntry e;

    ASSERT(table != NULL);
    ASSERT(result != NULL);

    for (e = result->entries; e != NULL; e = e->nextInScope) {
        unsigned int hashValue = (unsigned int) e->id % table->hashTableSize;

        ASSERT(table->hashTable[hashValue] == e);
        table->hashTable[hashValue] = e->nextInHash;
        e->nextInHash = NULL;
    }

    table->currentScope = result->parent;
    // symbol_print(table); // TODO: REMOVE THIS || DEBUG ONLY
    return result;
}

void scope_hide (Scope scope, bool flag)
{
    ASSERT(scope != NULL);
    scope->hidden = flag;
}

void scope_insert (SymbolTable table, Scope scope)
{
    SymbolEntry e;
    SymbolEntry last = NULL;

    ASSERT(table != NULL);
    ASSERT(scope != NULL);

    for (e = scope->entries; e != NULL; e = e->nextInScope) {
        unsigned int hashValue = (unsigned int) e->id % table->hashTableSize;

        e->scope = table->currentScope;
        e->nextInHash = table->hashTable[hashValue];
        table->hashTable[hashValue] = e;
        last = e;
    }
    if (table->currentScope != NULL && last != NULL) {
        last->nextInScope = table->currentScope->entries;
        table->currentScope->entries = scope->entries;
    }
}

SymbolEntry symbol_enter (SymbolTable table, Identifier id, bool err)
{
    unsigned int hashValue = (unsigned int) id % table->hashTableSize;
    SymbolEntry e;

    ASSERT(table != NULL);

    /* Έλεγχος αν υπάρχει ήδη στην τρέχουσα εμβέλεια */

    if (err) {
        unsigned int currentNesting =
            table->currentScope != NULL ? table->currentScope->nesting : 0;

        for (e = table->hashTable[hashValue]; e != NULL; e = e->nextInHash) {
            unsigned int eNesting = e->scope != NULL ? e->scope->nesting : 0;

            if (eNesting < currentNesting)
                break;

            ASSERT(eNesting == currentNesting);
            if (e->id == id) {
                error("duplicate identifier: %s", id_name(id));
                return NULL;
            }
        }
    }

    /* Προσθήκη */

    e = new(sizeof(struct SymbolEntry_tag));
    e->id = id;
    e->scope = table->currentScope;
    e->nextInHash = table->hashTable[hashValue];
    table->hashTable[hashValue] = e;
    if (table->currentScope != NULL) {
        e->nextInScope = table->currentScope->entries;
        table->currentScope->entries = e;
    }
    else
        e->nextInScope = NULL;
    return e;
}

// SymbolEntry symbol_enter_multiple (SymbolTable table, Identifier id, bool err){
// }

SymbolEntry symbol_lookup (SymbolTable table, Identifier id,
        LookupType type, bool err)
{
    unsigned int currentNesting =
        table->currentScope != NULL ? table->currentScope->nesting : 0;
    unsigned int hashValue = (unsigned int) id % table->hashTableSize;
    SymbolEntry e;

    ASSERT(table != NULL);

    switch (type) {
        case LOOKUP_CURRENT_SCOPE:
            for (e = table->hashTable[hashValue]; e != NULL; e = e->nextInHash) {
                unsigned int eNesting = e->scope != NULL ? e->scope->nesting : 0;

                if (eNesting < currentNesting)
                    break;

                ASSERT(eNesting == currentNesting);
                if (e->id == id)
                    return e;
            }
            break;
        case LOOKUP_ALL_SCOPES:
            for (e = table->hashTable[hashValue]; e != NULL; e = e->nextInHash) {
                if (e->scope != NULL && e->scope->hidden)
                    continue;
                if (e->id == id)
                    return e;
            }
            break;
    }

    /* Σφάλμα, αν δε βρέθηκε */

    if (err)
        error("unknown identifier: %s", id_name(id));
    return NULL;
}

// /** Find another place to place these: Maybe pretty.h? **/
// void print_constant(Type){

// }

void scope_print (Scope scope)
{
    SymbolEntry e;
    for (e = scope->entries; e != NULL; e = e->nextInScope) {
        // unsigned int hashValue = (unsigned int) e->id % table->hashTableSize;

        // ASSERT(table->hashTable[hashValue] == e);
        printf("(%d) ID: %s | %s ", scope->nesting, id_name(e->id), reverse_entry_type[e->entry_type]);

        switch(e->entry_type){
            case ENTRY_CONSTANT:
                ASSERT(e->e.constant.type != NULL);
                printf(" | %s | \n", reverse_type_kind[e->e.constant.type->kind]);
                break;
            case ENTRY_TYPE:
                ASSERT(e->e.type.scope != NULL);
                scope_print(e->e.type.scope);
                break;
            default:
                printf("\n");
        }
    }
}

void symbol_print (SymbolTable table)
{
    Scope result = table->currentScope;
    
    // Scope result = table->currentScope;
    // SymbolEntry e;
    // while(result != NULL){
    //     for (e = result->entries; e != NULL; e = e->nextInScope) {
    //         // unsigned int hashValue = (unsigned int) e->id % table->hashTableSize;

    //         // ASSERT(table->hashTable[hashValue] == e);
    //         printf("(%d) ID: %s | %s ", result->nesting, id_name(e->id), reverse_entry_type[e->entry_type]);

    //         switch(e->entry_type){
    //             case ENTRY_CONSTANT:
    //                 printf(" | CONSTANTTT");
    //             default:
    //                 printf("\n");
    //         }
    //     }
    //     result = result->parent;
    // }
}