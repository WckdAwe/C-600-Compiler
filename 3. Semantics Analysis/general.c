/* ---------------------------------------------------------------------
   ---------------------------- Header files ---------------------------
   --------------------------------------------------------------------- */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error.h"
#include "general.h"

char *filename;
int lineno;

/* ---------------------------------------------------------------------
   --------------------------- Generic flags ---------------------------
   --------------------------------------------------------------------- */

bool flagVerbose = true;

/* ---------------------------------------------------------------------
   ------------------- Hash function for ids ---------------------------
   --------------------------------------------------------------------- */

typedef unsigned long int HashType;

static HashType PJW_hash (const char * key)
{
    /*
     *  P.J. Weinberger's hashing function. See also:
     *  Aho A.V., Sethi R. & Ullman J.D, "Compilers: Principles,
     *  Techniques and Tools", Addison Wesley, 1986, pp. 433-437.
     */

    const HashType PJW_OVERFLOW =
        (((HashType) 0xf) << (8 * sizeof(HashType) - 4));
    const int PJW_SHIFT = (8 * (sizeof(HashType) - 1));

    HashType h, g;

    for (h = 0; *key != '\0'; key++) {
        h = (h << 4) + (*key);
        if ((g = h & PJW_OVERFLOW) != 0) {
            h ^= g >> PJW_SHIFT;
            h ^= g;
        }
    }
    return h;
}


/* ---------------------------------------------------------------------
   --------------------------- Ids -------------------------------------
   --------------------------------------------------------------------- */

static Identifier id_make_new (const char * name, Identifier next)
{
    Identifier result = new (sizeof (struct Identifier_tag));

    result->name = new(strlen(name) + 1);
    strcpy(result->name, name);
    result->next = next;
    return result;
}

/* Hash table size must be a prime number*/

#define SIZE 193


/* We use the fact that (static) global variables must be initialized:
   first we have hashtable[i] == NULL for every i. To re-initialize them
   we can use the id_reset function 
 */

static Identifier hashtable [SIZE];

Identifier id_make (const char * name)
{
    HashType index = PJW_hash(name) % SIZE;

    Identifier ids = hashtable[index];
    Identifier id;

    for (id=ids; id != NULL; id=id->next)
        if (strcmp(id->name, name) == 0)
            return id;
    id = id_make_new(name, ids);
    hashtable[index] = id;
    return id;
}

const char * id_name (Identifier id)
{
    return id->name;
}


/* WARNING: by calling the next function while ids are in use will cause 
   unpredictable concequenses
 */

void id_reset ()
{
    int i;

    for (i=0; i<SIZE; i++)
        hashtable[i] = NULL;
}

/* ---------------------------------------------------------------------
   ------------- Controlled termination of the compiler ----------------
   --------------------------------------------------------------------- */

// void terminate(int code)
// {
//     if (flagVerbose)
//         message("\r\nErrors:   %d\nWarnings: %d", numErrors, numWarnings);
//     exit(code);
// }


void *new(size_t size){
    void *pointer = malloc(size);
    if (!pointer)
        fatal("\rOut of memory");
    return pointer;
}