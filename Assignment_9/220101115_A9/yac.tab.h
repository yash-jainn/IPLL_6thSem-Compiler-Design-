/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     WHILE = 258,
     DO = 259,
     CONST = 260,
     CHAR = 261,
     ELSE = 262,
     FOR = 263,
     FLOAT = 264,
     IF = 265,
     INTEGER = 266,
     RETURN = 267,
     VOID = 268,
     BOOL = 269,
     IDENTIFIER = 270,
     STRING_LITERAL = 271,
     SQUARE_BRACKET_OPEN = 272,
     SQUARE_BRACKET_CLOSE = 273,
     ROUND_BRACKET_OPEN = 274,
     ROUND_BRACKET_CLOSE = 275,
     BEGIN_TOK = 276,
     END = 277,
     BITWISE_AND = 278,
     MUL = 279,
     ADD = 280,
     SUB = 281,
     EXCLAIM = 282,
     DIV = 283,
     MOD = 284,
     BIT_SL = 285,
     BIT_SR = 286,
     ARROW = 287,
     BITWISE_XOR = 288,
     BITWISE_OR = 289,
     LTE = 290,
     GTE = 291,
     EQ = 292,
     NEQ = 293,
     AND = 294,
     OR = 295,
     LT = 296,
     GT = 297,
     QUESTION = 298,
     COLON = 299,
     SEMICOLON = 300,
     ASSIGN = 301,
     COMMA = 302,
     THEN = 303,
     FLOAT_CONSTANT = 304,
     INTEGER_CONSTANT = 305,
     CHARACTER_CONSTANT = 306
   };
#endif
/* Tokens.  */
#define WHILE 258
#define DO 259
#define CONST 260
#define CHAR 261
#define ELSE 262
#define FOR 263
#define FLOAT 264
#define IF 265
#define INTEGER 266
#define RETURN 267
#define VOID 268
#define BOOL 269
#define IDENTIFIER 270
#define STRING_LITERAL 271
#define SQUARE_BRACKET_OPEN 272
#define SQUARE_BRACKET_CLOSE 273
#define ROUND_BRACKET_OPEN 274
#define ROUND_BRACKET_CLOSE 275
#define BEGIN_TOK 276
#define END 277
#define BITWISE_AND 278
#define MUL 279
#define ADD 280
#define SUB 281
#define EXCLAIM 282
#define DIV 283
#define MOD 284
#define BIT_SL 285
#define BIT_SR 286
#define ARROW 287
#define BITWISE_XOR 288
#define BITWISE_OR 289
#define LTE 290
#define GTE 291
#define EQ 292
#define NEQ 293
#define AND 294
#define OR 295
#define LT 296
#define GT 297
#define QUESTION 298
#define COLON 299
#define SEMICOLON 300
#define ASSIGN 301
#define COMMA 302
#define THEN 303
#define FLOAT_CONSTANT 304
#define INTEGER_CONSTANT 305
#define CHARACTER_CONSTANT 306




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 43 "yac.y"
{
    // Terminal types
    char unaryOp;
    char* char_value;
    int intval;
    int instr_number;
    int num_params;
    double floatval;
    
    // Non-terminal types
    Expression* expr;
    Statement* stat;
    SymbolType* sym_type;
    Symbol* symp;
    vector<Symbol*>* symp_list;
    Array* A;
}
/* Line 1529 of yacc.c.  */
#line 169 "yac.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

