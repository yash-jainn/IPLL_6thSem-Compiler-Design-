# MicroC Compiler

A simple compiler implementation for a Calculator using Flex and Bison.

## Components

1. **Lexical Analyzer** ([a8_220101115.l](a8_220101115.l))
   - Tokenizes the input code
   - Recognizes keywords, identifiers, constants, operators and special symbols
   

2. **Parser** ([a8_220101115.y](a8_220101115.y))
   - Implements grammar rules for Calculator
   - Supports following functions
    - expr()
    - bintodec()
    - bintohex() 
    - hextodec()
    - hextobin()


## Building and Running

- Just use the Makefile
```bash
make clean
make all
make test 
```

- To upload testcases from a file 
```bash
make clean
make all
make test
```

# Precautions
- We are expecting correct input format, i.e. binary and hex should be in their correct form, otherwise we might get wrong answer.