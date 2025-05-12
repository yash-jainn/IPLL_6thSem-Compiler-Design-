# MicroC Compiler

A simple compiler implementation for MicroC (a subset of C) using Flex and Bison.

## Components

1. **Lexical Analyzer** ([a7_220101115.l](a7_220101115.l))
   - Tokenizes the input code
   - Recognizes keywords, identifiers, constants, operators and special symbols
   - Tracks line numbers

2. **Parser** ([a7_220101115.y](a7_220101115.y))
   - Implements grammar rules for MicroC
   - Maintains symbol table for variables and functions. Symbol table contains identifiers, there type and the scope where    they belong.
   - Supports basic C constructs:
     - Variables and functions
     - Control structures (if-else, for loops)
     - Expressions and operators
     - Arrays and pointers
     - Basic data types (int, float, char, bool)

- Changes made :- I removed two non_terminals from the grammar, as they were useless after the assignment was modified. Also I have incuded float and bool as type_specifiers in my code although it was not mentioned in the assignment.

## Building and Running

1. Generate the lexer and parser:
```bash
flex a7_220101115.l
yacc -d a7_220101115.y
```

2. Compile the generated files:
```bash
gcc lex.yy.c y.tab.c -o parser -ly -ll
```

3. Run the parser on a test file:
```bash
./parser a7_test_220101115.c
```

OR

- Just use the Makefile
```bash
make clean
make all
```


## Features

- Symbol table with scope management
- Error reporting with line numbers
- Support for:
  - Function declarations and definitions
  - Variable declarations with initializers
  - Arithmetic and logical expressions
  - Control flow statements
  - Arrays and pointer operations

## Output

The parser outputs:
- Reduction steps during parsing
- Symbol table contents with variable names, types and scopes
- Parse status (success/failure)