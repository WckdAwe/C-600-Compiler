# Inspired by https://github.com/ychatz/compiler
.SUFFIXES:
.SUFFIXES: .l .y .c .o
.PHONY: clean distclean

# OS type: Linux/Win DJGPP
ifdef OS
   EXE=.exe
else
   EXE=
endif

# programs
CC=gcc
#CC=gcc-3.0
LEX=flex
YACC=bison

# options
CFLAGS=-g -DCHECK_ASSERT
LDFLAGS=-lfl -lm
ifndef LFLAGS
   LFLAGS=
endif
ifndef YFLAGS
   YFLAGS=-dv
endif

# files
CFILES   = general.c hashtbl.c 
HFILES   = general.h hashtbl.h 
OBJFILES = $(patsubst %.c,%.o,$(CFILES)) bison.o lexer.o main.o
TMPFILES = bison.h bison.c bison.output lexer.c c600
EXEFILES = c600$(EXE)

SRCFILES = $(HFILES) $(CFILES)

#
# Generic rules
#

%.c %.h: %.l
	$(LEX) $(LFLAGS) -olexer.c $<

%.c %.h: %.y
	$(YACC) $(YFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $< -lm

#
# Specific rules and dependencies
#

all: $(EXEFILES)

c600$(EXE): $(OBJFILES)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) 

lexer.o      : lexer.c bison.h c600.h general.h
bison.o      : bison.c  bison.h lexer.h c600.h

general.o    : general.c general.h
hashtbl.o    : hashtbl.c general.h
main.o       : main.c c600.h bison.h

clean:
	$(RM) $(OBJFILES) $(TMPFILES) *~

distclean: clean
	$(RM) $(EXEFILES)

count:
	wc -l -c Makefile $(SRCFILES)