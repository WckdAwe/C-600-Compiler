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
    Type type;
    char str_bfr[256];
    for (e = scope->entries; e != NULL; e = e->nextInScope) {
        // TODO: Anything better?
        int i;
        for(i=0;i<scope->nesting-1;i++)
            printf("  ");

        printf("(%02d) ID: %-22s | %-5s", scope->nesting, id_name(e->id), reverse_entry_type[e->entry_type]);

        switch(e->entry_type){
            case ENTRY_CONSTANT:
                ASSERT(e->e.constant.type != NULL);
                printf(" | %-5s \n", reverse_type_kind[e->e.constant.type->kind]);
                break;
            case ENTRY_TYPE:
                ASSERT(e->e.type.scope != NULL);
                printf("of %s \n", reverse_type_kind[e->e.type.type->kind]);
                scope_print(e->e.type.scope);
                break;
            case ENTRY_FUNCTION:
                printf(" of .....\n");
                break;
            case ENTRY_VARIABLE:
                type = e->e.variable.type;
                switch(type->kind){
                    case TYPE_array:
                        ASSERT(type != NULL);
                        memset(str_bfr,0,strlen(str_bfr));
                        while(type->kind == TYPE_array){
                            sprintf(str_bfr, "%s[%d]", str_bfr, type->u.t_array.dim);
                            type = type->u.t_array.type;
                            ASSERT(type != NULL);
                        }
                        printf(" %s%s\n", reverse_type_kind[type->kind], str_bfr);
                        break;
                    default:
                        printf(" Unknown type??\n");
                        break;
                }
                break;
            default:
                printf("\n");
        }
    }
}

EntryList entry_list_add(EntryList list, SymbolEntry entry){
    EntryList node = new(sizeof(struct EntryList_tag));
    node->entry = entry;
    node->next = NULL;

    if(list == NULL)
        return node;
    
    EntryList tmp = list;
	while(tmp->next != NULL){
		tmp = tmp->next;
	}
    tmp->next = node;
	
	return list;
}