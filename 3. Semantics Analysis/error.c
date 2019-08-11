/******************************************************************************
 *  CVS version:
 *     $Id: error.c,v 1.2 2005/04/07 11:22:47 nickie Exp $
 ******************************************************************************
 *
 *  C code file : error.c
 *  Project     : Llama Compiler
 *  Version     : 1.0 alpha
 *  Description : Simple error handler
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
#include <stdlib.h>
#include <stdarg.h>

#include "general.h"
#include "error.h"


/* ---------------------------------------------------------------------
   ---------------------- Πλήθος σφαλμάτων, κ.λπ. ----------------------
   --------------------------------------------------------------------- */

int  numErrors = 0;
int  maxErrors = 0;               /* χωρίς ανάνηψη από σφάλματα */
bool flagWarnings = true;
int  numWarnings = 0;
int  maxWarnings = 200;


/* ---------------------------------------------------------------------
   --------- Υλοποίηση των συναρτήσεων του χειριστή σφαλμάτων ----------
   --------------------------------------------------------------------- */

void internal_raw (const char * fn, int lc, const char * fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    if (fmt[0] == '\r')
        fmt++;
    else
        fprintf(stderr, "%s:%d: ", filename, lineno);
    fprintf(stderr, "Internal error occurred at %s:%d, ", fn, lc);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    numErrors++;
    exit(1);
}

void fatal (const char * fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    if (fmt[0] == '\r')
        fmt++;
    else
        fprintf(stderr, "%s:%d: ", filename, lineno);
    fprintf(stderr, "Fatal error, ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    numErrors++;
    exit(1);
}

void error (const char * fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    if (fmt[0] == '\r')
        fmt++;
    else
        fprintf(stderr, "%s:%d: ", filename, lineno-1);
    fprintf(stderr, "Error, ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    if (numErrors++ >= maxErrors) {
        message("\rToo many errors, aborting...");
        exit(1);
    }
}

void warning (const char * fmt, ...)
{
    if (flagWarnings) {
        va_list ap;

        va_start(ap, fmt);
        /* if (fmt[0] == '\r') */
        /*    fmt++; */
        /* else */
        /*    fprintf(stderr, "%s:%d: ", filename, lineno); */
        fprintf(stderr, "Warning, ");
        vfprintf(stderr, fmt, ap);
        fprintf(stderr, "\n");
        va_end(ap);
        if (numWarnings++ >= maxWarnings) {
            message("\rToo many warnings, no more will be shown...");
            flagWarnings = false;
        }
    }
}

void message (const char * fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    if (fmt[0] == '\r')
        fmt++;
    else
        fprintf(stderr, "%s:%d: ", filename, lineno);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
}
