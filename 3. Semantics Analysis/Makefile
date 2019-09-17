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
CFILES   = error.c general.c symbol.c ast.c sizes.c types.c semantic.c
HFILES   = error.c general.h symbol.h ast.h sizes.h types.h semantic.h
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

lexer.o      : symbol.h types.h lexer.c bison.h c600.h general.h
bison.o      : symbol.h types.h bison.c bison.h c600.h

general.o    : general.c general.h
error.o      : error.c general.h error.h
symbol.o     : symbol.c symbol.h general.h error.h types.h
pretty.o 	 : pretty.c pretty.h error.h ast.h
semantic.o   : semantic.c general.h error.h symbol.h
sizes.o		 : sizes.c general.h
ast.o		 : ast.h types.h symbol.h general.h
types.o		 : types.c general.h
main.o       : main.c c600.h bison.h

clean:
	$(RM) $(OBJFILES) $(TMPFILES) *~

distclean: clean
	$(RM) $(EXEFILES)

count:
	wc -l -c Makefile $(SRCFILES)