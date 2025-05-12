- Submission by Yash Jain (220101115)

## Lexer Files Description

### a6it_220101115.l (Iterative Version)
This is the iterative implementation of the lexical analyzer. Key features:
- Uses a while loop in main() to repeatedly call yylex()
- Processes tokens one at a time
- Maintains token count
- Returns control to main after each token
- Suitable for interactive processing
- File named according to format: a6(it)_rollnumber.l where:

### a6nit_220101115.l (Non-Iterative Version)
This is the non-iterative implementation of the lexical analyzer. Key features:
- Single call to yylex() processes entire input
- Processes all tokens in one pass
- More efficient for batch processing
- No explicit loop in main()
- File named according to format: a6(nit)_rollnumber.l where:


## Compilation Instructions
### Iterative Version
```bash
flex a6it_220101115.l
gcc lex.yy.c -o lexer_it -ll
./lexer_iterative < input.txt > output_it.txt


flex a6nit_220101115.l
gcc lex.yy.c -o lexer_nit -ll
./lexer_non_iterative < input.txt > output_nit.txt
```

## Files Created :-

1. lex.yy.c
2. symtab_it.txt and symtab_nit.txt
3. lexer_it and lexer_nit (Executable files)
4. output_it.txt and output_nit.txt (Corresponding output files)
