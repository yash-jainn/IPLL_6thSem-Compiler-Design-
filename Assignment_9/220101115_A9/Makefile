
CC = g++
CFLAGS = -std=c++11 -Wall
LEX = flex
YACC = bison -d -v

all: microc

microc: lex.yy.o yac.tab.o translator.o
	$(CC) $(CFLAGS) -o $@ $^  # Line 10 - likely using spaces instead of tab

lex.yy.c: lexer.l yac.tab.h
	$(LEX) $<

yac.tab.c yac.tab.h: yac.y
	$(YACC) $<

translator.o: translator.cpp translator.h yac.tab.h
	$(CC) $(CFLAGS) -c $<

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c $<

yac.tab.o: yac.tab.c
	$(CC) $(CFLAGS) -c $<

test: microc
	./microc test.mc

clean:
	rm -f *.o lex.yy.c yac.tab.c yac.tab.h yac.output microc

.PHONY: all clean test