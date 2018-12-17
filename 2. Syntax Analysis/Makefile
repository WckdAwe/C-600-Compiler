all: cpp600

bison.tab.c bison.tab.h: bison.y
	bison -v -d bison.y

lex.yy.c: compiler.l bison.tab.h
	flex compiler.l

cpp600: lex.yy.c bison.tab.c bison.tab.h hashtbl.o
	gcc -o bison bison.tab.c lex.yy.c hashtbl.o -lm

hashtbl.o: hashtbl.c hashtbl.h
	gcc -o hashtbl.o -c hashtbl.c
clean:
	rm bison bison.tab.c lex.yy.c bison.tab.h hashtbl.o 
	rm bison.output
