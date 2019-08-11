#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <errno.h>

#include "c600.h"


/* ---------------------------------------------------------------------
   ------------- External variables & functions from lexer.l -----------
   --------------------------------------------------------------------- */

extern int lineno;
extern char *filename;

extern char str_buf[MAX_STR_CONST];
extern char *str_buf_ptr;

extern char *yytext;
extern FILE *yyin;

/* ---------------------------------------------------------------------
   --------------------- Local variables & functions  ------------------
   --------------------------------------------------------------------- */


int error_count = 0;
int flag_err_type = 0; // 0: Token Error (YYTEXT) || 1: String Error (STRBUF)

void yyerror(const char *message)
{
    error_count++;

    if (flag_err_type == 0)
    {
        printf("-> ERROR at line %d caused by %s : %s\n", lineno, yytext, message);
    }
    else if (flag_err_type == 1)
    {
        *str_buf_ptr = '\0'; // String or Comment Error. Cleanup old chars stored in buffer.
        printf("-> ERROR at line %d near \"%s\": %s\n", lineno, str_buf, message);
    }
    flag_err_type = 0; // Reset flag_err_type to default.
    if (MAX_ERRORS <= 0)
        return;
    if (error_count == MAX_ERRORS)
    {
        printf("Max errors (%d) detected. ABORTING...\n", MAX_ERRORS);
        exit(-1);
    }
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        yyin = fopen(argv[1], "r");
        filename = argv[1];
        if (yyin == NULL)
        {
            perror("Error opening file");
            return -1;
        }
    }

    yyparse();
    fclose(yyin);

    if (error_count > 0)
    {
        printf("Syntax Analysis failed due to %d errors\n", error_count);
    }
    else
    {
        printf("Syntax Analysis completed successfully.\n");
    }
    return 0;
}