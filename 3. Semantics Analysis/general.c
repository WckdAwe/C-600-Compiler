/* ---------------------------------------------------------------------
   ---------------------------- Header files ---------------------------
   --------------------------------------------------------------------- */

#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <errno.h>
#include "general.h"

/* ---------------------------------------------------------------------
   --------------------------- Generic flags ---------------------------
   --------------------------------------------------------------------- */

bool flagVerbose = true;

/* ---------------------------------------------------------------------
   ------------- Ελεγχόμενος τερματισμός του μεταγλωττιστή -------------
   --------------------------------------------------------------------- */

// void terminate(int code)
// {
//     if (flagVerbose)
//         message("\r\nErrors:   %d\nWarnings: %d", numErrors, numWarnings);
//     exit(code);
// }


void *emalloc(size_t size){
    void *pointer = malloc(size);

    if (!pointer){
        perror("malloc");
        exit(ENOMEM);
    }

    return pointer;
}