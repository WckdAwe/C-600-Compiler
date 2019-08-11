#ifndef __GENERAL_H__
#define __GENERAL_H__

/* ---------------------------------------------------------------------
   ---------------------------- Header files ---------------------------
   --------------------------------------------------------------------- */

#include <stdbool.h>
#include <stdlib.h>

/* ---------------------------------------------------------------------
   ---------------------------- Generic Flags --------------------------
   --------------------------------------------------------------------- */

extern bool flagVerbose;

/* ---------------------------------------------------------------------
   ------- Αρχείο εισόδου του μεταγλωττιστή και αριθμός γραμμής --------
   --------------------------------------------------------------------- */

extern char *filename;
extern int lineno;

typedef struct Identifier_tag * Identifier;

struct Identifier_tag {
   char * name;
   Identifier next;
};

Identifier id_make (const char *);
const char * id_name (Identifier);

void id_reset ();

void *new(size_t size);
#endif