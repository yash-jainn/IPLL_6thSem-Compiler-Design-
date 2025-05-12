# Micro C Compiler

A compiler front-end for Micro C language that performs lexical analysis, syntax analysis, and generates three-address code (TAC) as an intermediate representation.

## Project Structure

- lexer.l: Flex lexical analyzer definition
- yac.y: Bison parser definition with semantic actions
- translator.h: Class declarations and data structures
- translator.cpp: Implementation of compiler functionality
- test.mc: Example Micro C program

## Building the Compiler

Use the included Makefile to build the project:

```bash
make
```

## Usage

1. Write your Micro C program in a `test.mc` file
2. Compile the program:

```bash
./microc < test.mc > test.output
```

3. The compiler will generate:
   - Quad Array Table 
   - Three-address code output
   - Symbol table dump


## Note 
- I have followed the grammar from assignment 6 and 7, as mentioned in the PS. So many common functionalities which are not in the microC grammar will not work. For eg:- while, do-while loop. 
- Also, you can not perform operations outside any function, which is the case with C language as well. Only declarations allowed outside functions.
- Also, Since compound assignments should be exluded (as mentioned in assignment), i have not added the functionality of ++ and -- also, as they are nothing but += 1 or -= 1 only.
- As mentioned in the assignment, the for loop variable (i) should be declared outside only, it can't be declared inside the loop initiator.
