# Commands : make clean
# 			 make all OR make
# 			 ./a.out

all : 
	flex a6it_220101115.l
	gcc lex.yy.c -o lexer_it -ll
	./lexer_it < input.txt > output_it.txt

	flex a6nit_220101115.l
	gcc lex.yy.c -o lexer_nit -ll
	./lexer_nit < input.txt > output_nit.txt
	
clean :
	rm -f lex.yy.c lexer_it lexer_nit output_it.txt output_nit.txt symtab_it.txt symtab_nit.txt

	