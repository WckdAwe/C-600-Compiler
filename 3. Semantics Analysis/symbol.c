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
    "CONST", "FUNC", "FDCL", "PARAM", "VAR", "TYPE", "ID", "CLASS",
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
    // scope_print(table->currentScope, 0); // DEBUG ONLY;
    // printf("---End Scope---\n");
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

char* _print_array_type(Type array){
    ASSERT(array->kind == TYPE_array);
    char* out_bfr = malloc(sizeof(char)*256);
    char bfr[256];
    memset(out_bfr,0, strlen(out_bfr));
    memset(bfr,0, strlen(bfr));
    Type tmp = array;
    while(tmp->kind == TYPE_array){
        sprintf(bfr, "%s[%d]", bfr, tmp->u.t_array.dim);
        tmp = tmp->u.t_array.type;
        ASSERT(tmp != NULL);
    }
    sprintf(out_bfr, "%s%s", reverse_type_kind[tmp->kind], bfr);
    return out_bfr;
    // TODO: Implement cleanup? MemLeaks otherwise...
}

void scope_print (Scope scope, int go_deeper)
{
    SymbolEntry e;
    Type type;
    char str_bfr[256];
    for (e = scope->entries; e != NULL; e = e->nextInScope) {
        // TODO: Anything better?
        int i;
        for(i=0;i<scope->nesting-1;i++)
            printf("  ");

        ASSERT(e != NULL);
        printf("(%02d) ID: %-22s | %-5s", scope->nesting, id_name(e->id), reverse_entry_type[e->entry_type]);

        switch(e->entry_type){
            case ENTRY_CONSTANT:
                type = e->e.constant.type;
                ASSERT(type != NULL);
                printf(" | %-5s ", reverse_type_kind[type->kind]);
                switch(type->kind){
                    case TYPE_char:
                        printf("| Value: %c\n", e->e.constant.value.v_char);
                        break;
                    case TYPE_int:
                        printf("| Value: %d\n", e->e.constant.value.v_int);
                        break;
                    case TYPE_float:
                        printf("| Value: %f\n", e->e.constant.value.v_float);
                        break;
                    case TYPE_str:
                        printf("| Value: %s\n", e->e.constant.value.v_str);
                        break;
                    default:
                        printf("| Unknown?\n");
                }
                break;
            case ENTRY_TYPE:
                ASSERT(e->e.type.scope != NULL);
                printf("of %s \n", reverse_type_kind[e->e.type.type->kind]);
                if(go_deeper)
                    scope_print(e->e.type.scope, go_deeper);
                break;
            case ENTRY_FUNCTION:
                ASSERT(e->e.function.result_type != NULL);
                EntryList arguments = e->e.function.arguments;
                memset(str_bfr,0, strlen(str_bfr));
                while(arguments != NULL){
                    ASSERT(arguments->entry->entry_type == ENTRY_PARAMETER);
                    type = arguments->entry->e.parameter.type;
                    switch(type->kind){
                        case TYPE_array:
                            sprintf(str_bfr, "%s, %s", str_bfr, _print_array_type(type));
                            break;
                        default:
                            sprintf(str_bfr, "%s, %s", str_bfr, reverse_type_kind[type->kind]);
                            break;
                    }
                    arguments = arguments->next;
                }
                // ASSERT(e->e.function.parent != NULL);
                // ASSERT(e->e.function.parent->id != NULL);
                if(str_bfr != '\0'){
                    printf(" [%s] of %s that returns %s\n", str_bfr+2, e->e.function.parent ? id_name(e->e.function.parent->id) : "N/A", reverse_type_kind[e->e.function.result_type->kind]);
                }else{
                    printf(" [%s] of %s that returns %s\n", str_bfr, e->e.function.parent ? id_name(e->e.function.parent->id) : "N/A", reverse_type_kind[e->e.function.result_type->kind]);
                }
                break;
            case ENTRY_FUNCTION_DECLARATION:
                ASSERT(e->e.function_declaration.result_type != NULL);
                memset(str_bfr,0,strlen(str_bfr));
                TypeList parameters = e->e.function_declaration.parameters;
                while(parameters != NULL){
                    switch(parameters->type->kind){
                        case TYPE_array:
                            sprintf(str_bfr, "%s, %s", str_bfr, _print_array_type(parameters->type));
                            break;
                        default:
                            sprintf(str_bfr, "%s, %s", str_bfr, reverse_type_kind[parameters->type->kind]);
                            break;
                    }
                    parameters = parameters->next;
                }
                if(str_bfr != '\0'){
                    printf(" [%s] of ..... that returns %s\n", str_bfr+2, reverse_type_kind[e->e.function_declaration.result_type->kind]);
                }else{
                    printf(" [%s] of ..... that returns %s\n", str_bfr, reverse_type_kind[e->e.function_declaration.result_type->kind]);
                }
                break;
            case ENTRY_VARIABLE:
                type = e->e.variable.type;
                ASSERT(type != NULL);
                switch(type->kind){
                    case TYPE_array:
                        printf("%s\n", _print_array_type(type));
                        break;
                    case TYPE_ref:
                        ASSERT(type->u.t_ref.type != NULL);
                        printf("reference to: %s \n", reverse_type_kind[type->u.t_ref.type->kind]);
                        break;
                    default:
                        printf("%s\n", reverse_type_kind[type->kind]);
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

void entry_list_reverse(EntryList *head){
    EntryList prev = NULL;
    EntryList current = *head;
    EntryList next = NULL;

    while(current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}