/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "yac.y"

    #include "translator.h"
    
    #include <iostream>
    #include <iomanip>
    #include <cmath>
    #include <string>
    #include <algorithm>
    #include <map>
    #include <queue>
    #include <set>
    #include <array>
    #include <unordered_set>
    #include <unordered_map>
    #include <stack>
    #include <cassert>
    #include <vector>
    #include <numeric>
    #include <cstdlib>
    #include <bitset>
    #include <chrono>
    #include <random>
    #include <fstream>
    #include <iterator>
    #include <complex>
    #include <cstring>
    #include <list>
    #include <sstream>

    using namespace std;
    
    extern "C" int yylex();
    
    // Stores the most recently encountered type
    extern string var_type;
    extern vector<Label> label_table;

    void yyerror(string s);
    Expression* temp_rel;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 193 of yacc.c.  */
#line 257 "yac.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 270 "yac.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  19
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   236

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  109
/* YYNRULES -- Number of states.  */
#define YYNSTATES  184

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     5,     6,     8,    10,    12,    14,
      16,    20,    22,    27,    32,    36,    38,    39,    41,    45,
      47,    50,    52,    54,    56,    58,    60,    62,    66,    70,
      74,    76,    80,    84,    86,    90,    94,    96,   100,   102,
     106,   108,   112,   114,   118,   122,   126,   130,   132,   137,
     142,   145,   147,   151,   154,   156,   160,   163,   165,   173,
     175,   179,   181,   185,   187,   191,   193,   197,   199,   201,
     203,   205,   207,   210,   212,   215,   217,   222,   227,   229,
     231,   232,   234,   238,   241,   243,   245,   247,   249,   251,
     253,   257,   258,   260,   262,   266,   268,   270,   273,   275,
     279,   284,   292,   304,   308,   311,   313,   316,   318,   320
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
     100,     0,    -1,    -1,    -1,    -1,    15,    -1,    50,    -1,
      51,    -1,    49,    -1,    16,    -1,    19,    77,    20,    -1,
      56,    -1,    57,    17,    77,    18,    -1,    57,    19,    58,
      20,    -1,    57,    32,    15,    -1,    59,    -1,    -1,    76,
      -1,    59,    47,    76,    -1,    57,    -1,    61,    60,    -1,
      23,    -1,    24,    -1,    25,    -1,    26,    -1,    27,    -1,
      60,    -1,    62,    24,    60,    -1,    62,    28,    60,    -1,
      62,    29,    60,    -1,    62,    -1,    63,    25,    62,    -1,
      63,    26,    62,    -1,    63,    -1,    64,    30,    63,    -1,
      64,    31,    63,    -1,    64,    -1,    65,    23,    64,    -1,
      65,    -1,    66,    33,    65,    -1,    66,    -1,    67,    34,
      66,    -1,    67,    -1,    68,    41,    67,    -1,    68,    42,
      67,    -1,    68,    35,    67,    -1,    68,    36,    67,    -1,
      68,    -1,    69,    37,    53,    68,    -1,    69,    38,    53,
      68,    -1,    71,    39,    -1,    69,    -1,    70,    53,    69,
      -1,    73,    40,    -1,    71,    -1,    72,    53,    71,    -1,
      73,    43,    -1,    73,    -1,    74,    53,    77,    54,    44,
      53,    75,    -1,    75,    -1,    60,    46,    76,    -1,    76,
      -1,    81,    79,    45,    -1,    80,    -1,    79,    47,    80,
      -1,    82,    -1,    82,    46,    89,    -1,    13,    -1,     6,
      -1,    11,    -1,     9,    -1,    14,    -1,    85,    84,    -1,
      84,    -1,    15,    19,    -1,    15,    -1,    15,    17,    50,
      18,    -1,    83,    55,    86,    20,    -1,    24,    -1,    87,
      -1,    -1,    88,    -1,    87,    47,    88,    -1,    81,    82,
      -1,    76,    -1,    91,    -1,    95,    -1,    97,    -1,    98,
      -1,    99,    -1,    21,    92,    22,    -1,    -1,    93,    -1,
      94,    -1,    93,    53,    94,    -1,    78,    -1,    90,    -1,
      77,    45,    -1,    45,    -1,    10,    19,    77,    -1,    96,
      20,    53,    90,    -1,    96,    20,    53,    90,     7,    53,
      90,    -1,     8,    19,    95,    53,    95,    53,    77,    54,
      20,    53,    90,    -1,    12,    77,    45,    -1,    12,    45,
      -1,   101,    -1,   100,   101,    -1,   102,    -1,    78,    -1,
      81,    82,    55,    21,    92,    22,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   135,   135,   142,   152,   164,   170,   178,   185,   191,
     199,   211,   226,   240,   248,   258,   263,   268,   274,   282,
     283,   331,   333,   335,   337,   339,   343,   364,   385,   406,
     429,   430,   438,   448,   449,   454,   461,   462,   469,   470,
     477,   478,   485,   486,   496,   506,   516,   531,   532,   550,
     570,   577,   578,   591,   597,   598,   611,   617,   618,   643,
     644,   663,   666,   669,   674,   681,   682,   691,   692,   693,
     694,   695,   698,   706,   710,   720,   727,   738,   759,   765,
     766,   769,   770,   773,   776,   779,   780,   785,   786,   787,
     790,   796,   797,   800,   801,   808,   809,   812,   813,   817,
     823,   830,   843,   865,   870,   877,   878,   881,   882,   885
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WHILE", "DO", "CONST", "CHAR", "ELSE",
  "FOR", "FLOAT", "IF", "INTEGER", "RETURN", "VOID", "BOOL", "IDENTIFIER",
  "STRING_LITERAL", "SQUARE_BRACKET_OPEN", "SQUARE_BRACKET_CLOSE",
  "ROUND_BRACKET_OPEN", "ROUND_BRACKET_CLOSE", "BEGIN_TOK", "END",
  "BITWISE_AND", "MUL", "ADD", "SUB", "EXCLAIM", "DIV", "MOD", "BIT_SL",
  "BIT_SR", "ARROW", "BITWISE_XOR", "BITWISE_OR", "LTE", "GTE", "EQ",
  "NEQ", "AND", "OR", "LT", "GT", "QUESTION", "COLON", "SEMICOLON",
  "ASSIGN", "COMMA", "THEN", "FLOAT_CONSTANT", "INTEGER_CONSTANT",
  "CHARACTER_CONSTANT", "$accept", "M", "N", "changetable",
  "primary_expression", "postfix_expression",
  "argument_expression_list_opt", "argument_expression_list",
  "unary_expression", "unary_operator", "multiplicative_expression",
  "additive_expression", "shift_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "relational_expression", "equality_expression", "and_helper",
  "logical_and_expression", "or_helper", "logical_or_expression",
  "condition", "conditional_expression", "assignment_expression",
  "expression", "declaration", "init_declarator_list", "init_declarator",
  "type_specifier", "declarator", "declarator_helper", "direct_declarator",
  "pointer", "parameter_list_opt", "parameter_list",
  "parameter_declaration", "initializer", "statement",
  "compound_statement", "block_item_list_opt", "block_item_list",
  "block_item", "expression_statement", "if_helper", "selection_statement",
  "iteration_statement", "jump_statement", "translation_unit",
  "external_declaration", "function_definition", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    54,    55,    56,    56,    56,    56,    56,
      56,    57,    57,    57,    57,    58,    58,    59,    59,    60,
      60,    61,    61,    61,    61,    61,    62,    62,    62,    62,
      63,    63,    63,    64,    64,    64,    65,    65,    66,    66,
      67,    67,    68,    68,    68,    68,    68,    69,    69,    69,
      70,    71,    71,    72,    73,    73,    74,    75,    75,    76,
      76,    77,    78,    79,    79,    80,    80,    81,    81,    81,
      81,    81,    82,    82,    83,    84,    84,    84,    85,    86,
      86,    87,    87,    88,    89,    90,    90,    90,    90,    90,
      91,    92,    92,    93,    93,    94,    94,    95,    95,    96,
      97,    97,    98,    99,    99,   100,   100,   101,   101,   102
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     0,     1,     1,     1,     1,     1,
       3,     1,     4,     4,     3,     1,     0,     1,     3,     1,
       2,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     3,     3,     3,     1,     4,     4,
       2,     1,     3,     2,     1,     3,     2,     1,     7,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     1,     1,
       1,     1,     2,     1,     2,     1,     4,     4,     1,     1,
       0,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       3,     0,     1,     1,     3,     1,     1,     2,     1,     3,
       4,     7,    11,     3,     2,     1,     2,     1,     1,     6
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    68,    70,    69,    67,    71,   108,     0,     0,   105,
     107,    75,    78,     0,    63,    65,     4,    73,     0,     1,
     106,     0,    74,    62,     0,     0,     0,    80,    72,     0,
      64,    65,     5,     9,     0,    21,    22,    23,    24,    25,
       8,     6,     7,    11,    19,    26,     0,    30,    33,    36,
      38,    40,    42,    47,    51,     2,    54,     2,    57,     2,
      59,    84,    66,    91,     0,     0,    79,    81,    76,    61,
       0,     0,    16,     0,     0,    20,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     2,     0,    50,     0,    53,    56,     0,     0,     0,
       0,    91,    98,     0,    95,     0,    96,    85,     0,     2,
      93,    86,     0,    87,    88,    89,    83,    77,     0,    10,
       0,     0,    15,    17,    14,    60,    27,    28,    29,    26,
      31,    32,    34,    35,    37,    39,    41,    45,    46,    43,
      44,     0,     0,    52,    55,     3,     0,     0,   104,     0,
       0,    97,   109,     0,     2,    82,    12,    13,     0,    48,
      49,     0,     2,    99,   103,    90,    94,     0,    18,     2,
       0,   100,     0,     2,     2,    58,     0,     0,     3,   101,
       0,     2,     0,   102
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    92,   161,    26,    43,    44,   121,   122,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    69,   103,   104,    13,    14,   105,
      31,    16,    17,    18,    65,    66,    67,    62,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,     8,     9,
      10
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -144
static const yytype_int16 yypact[] =
{
      32,  -144,  -144,  -144,  -144,  -144,  -144,    18,   111,  -144,
    -144,    50,  -144,    40,  -144,   -15,  -144,  -144,    29,  -144,
    -144,    34,  -144,  -144,    18,   185,    47,    32,  -144,    80,
    -144,    60,  -144,  -144,   185,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,   -10,    64,   185,    -9,    30,    59,
      77,    79,    81,    23,    54,  -144,    98,  -144,   -27,  -144,
    -144,  -144,  -144,   135,    18,    96,    91,  -144,  -144,  -144,
     119,   185,   185,   125,   185,  -144,   185,   185,   185,   185,
     185,   185,   185,   185,   185,   185,   185,   185,   185,   185,
    -144,  -144,   185,  -144,   185,  -144,  -144,   185,   133,   134,
      78,   135,  -144,   110,  -144,    18,  -144,  -144,   143,   146,
    -144,  -144,   137,  -144,  -144,  -144,  -144,  -144,    32,  -144,
     151,   150,   129,  -144,  -144,  -144,  -144,  -144,  -144,  -144,
      -9,    -9,    30,    30,    59,    77,    79,    81,    81,    81,
      81,   185,   185,    54,    98,  -144,   148,   185,  -144,   132,
     156,  -144,  -144,   135,  -144,  -144,  -144,  -144,   185,    23,
      23,   138,  -144,  -144,  -144,  -144,  -144,     2,  -144,  -144,
     148,   172,   185,  -144,  -144,  -144,   185,     2,  -144,  -144,
     161,  -144,     2,  -144
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -144,   -55,     5,   171,  -144,  -144,  -144,  -144,    -6,  -144,
     -19,    14,   105,   106,   104,    44,   -33,    99,  -144,   100,
    -144,  -144,  -144,    20,   -24,   -34,    49,  -144,   178,     3,
      -2,  -144,   177,  -144,  -144,  -144,    85,  -144,  -143,  -144,
      95,  -144,    52,  -138,  -144,  -144,  -144,  -144,  -144,   198,
    -144
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -93
static const yytype_int16 yytable[] =
{
      70,    61,    94,     7,    97,    15,    -4,    71,   162,    72,
      98,     7,    99,    95,   100,    76,    96,    32,    33,    77,
      78,    34,    73,   101,   171,    35,    36,    37,    38,    39,
      64,    25,   173,    11,   179,   141,   142,   120,     1,   183,
      75,     2,    12,     3,    11,     4,     5,   102,   123,     6,
     125,    40,    41,    42,   153,    79,    80,     6,    86,    87,
     130,   131,   116,   145,    88,    89,   149,    21,    63,    22,
     126,   127,   128,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,    29,    23,   129,    24,   129,    81,
      82,    90,    91,    32,    33,   132,   133,    34,    68,   167,
      83,    35,    36,    37,    38,    39,    25,   170,   159,   160,
      74,    19,    84,   163,   172,    85,   117,     1,   176,   177,
       2,    64,     3,   148,     4,     5,   182,    40,    41,    42,
     137,   138,   139,   140,   168,   129,   129,    93,   118,   119,
     124,     1,   178,    98,     2,    99,     3,   100,     4,     5,
      32,    33,   146,   147,    34,   151,   101,   154,    35,    36,
      37,    38,    39,    32,    33,   152,   129,    34,   -92,   156,
     157,    35,    36,    37,    38,    39,   158,   164,   165,   174,
     102,   181,   169,   180,    40,    41,    42,    27,   134,   136,
     135,   143,   175,   102,   144,    28,   150,    40,    41,    42,
      32,    33,    30,   155,    34,   166,    20,     0,    35,    36,
      37,    38,    39,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    40,    41,    42
};

static const yytype_int16 yycheck[] =
{
      34,    25,    57,     0,    59,     7,    21,    17,   146,    19,
       8,     8,    10,    40,    12,    24,    43,    15,    16,    28,
      29,    19,    32,    21,   167,    23,    24,    25,    26,    27,
      27,    46,   170,    15,   177,    90,    91,    71,     6,   182,
      46,     9,    24,    11,    15,    13,    14,    45,    72,     0,
      74,    49,    50,    51,   109,    25,    26,     8,    35,    36,
      79,    80,    64,    97,    41,    42,   100,    17,    21,    19,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    50,    45,    92,    47,    94,    30,
      31,    37,    38,    15,    16,    81,    82,    19,    18,   154,
      23,    23,    24,    25,    26,    27,    46,   162,   141,   142,
      46,     0,    33,   147,   169,    34,    20,     6,   173,   174,
       9,   118,    11,    45,    13,    14,   181,    49,    50,    51,
      86,    87,    88,    89,   158,   141,   142,    39,    47,    20,
      15,     6,   176,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    19,    19,    19,    45,    21,    20,    23,    24,
      25,    26,    27,    15,    16,    22,   172,    19,    22,    18,
      20,    23,    24,    25,    26,    27,    47,    45,    22,     7,
      45,    20,    44,   178,    49,    50,    51,    16,    83,    85,
      84,    92,   172,    45,    94,    18,   101,    49,    50,    51,
      15,    16,    24,   118,    19,   153,     8,    -1,    23,    24,
      25,    26,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    49,    50,    51
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     9,    11,    13,    14,    78,    81,   100,   101,
     102,    15,    24,    79,    80,    82,    83,    84,    85,     0,
     101,    17,    19,    45,    47,    46,    55,    55,    84,    50,
      80,    82,    15,    16,    19,    23,    24,    25,    26,    27,
      49,    50,    51,    56,    57,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    89,    21,    81,    86,    87,    88,    18,    76,
      77,    17,    19,    32,    46,    60,    24,    28,    29,    25,
      26,    30,    31,    23,    33,    34,    35,    36,    41,    42,
      37,    38,    53,    39,    53,    40,    43,    53,     8,    10,
      12,    21,    45,    77,    78,    81,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,    82,    20,    47,    20,
      77,    58,    59,    76,    15,    76,    60,    60,    60,    60,
      62,    62,    63,    63,    64,    65,    66,    67,    67,    67,
      67,    53,    53,    69,    71,    77,    19,    19,    45,    77,
      92,    45,    22,    53,    20,    88,    18,    20,    47,    68,
      68,    54,    95,    77,    45,    22,    94,    53,    76,    44,
      53,    90,    53,    95,     7,    75,    53,    53,    77,    90,
      54,    20,    53,    90
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 135 "yac.y"
    {
        // Store next instruction index for backpatching
        (yyval.instr_number) = nextinstr();
    ;}
    break;

  case 3:
#line 142 "yac.y"
    {
        // Create a guard against fall-through for backpatching
        (yyval.stat) = new Statement();
        (yyval.stat)->nextlist = makelist(nextinstr());
        emit("goto", "");
    ;}
    break;

  case 4:
#line 152 "yac.y"
    {    
        parST = ST;
        // Create new table if needed or use existing nested table
        if (currSymbolPtr->nested == NULL) {
            changeTable(new SymbolTable(""));    
        } else {
            changeTable(currSymbolPtr->nested);                        
            emit("Label", ST->name);
        }
    ;}
    break;

  case 5:
#line 165 "yac.y"
    {
        // Generate expression with symbol table entry
        (yyval.expr) = new Expression();
        (yyval.expr)->loc = ST->lookupIdentifier(id);
    ;}
    break;

  case 6:
#line 171 "yac.y"
    { 
        // Handle integer constant
        (yyval.expr) = new Expression();    
        string converted_value = convertIntToString((yyvsp[(1) - (1)].intval));
        (yyval.expr)->loc = gentemp(new SymbolType("integer"), converted_value);
        emit("=", (yyval.expr)->loc->name, converted_value);
    ;}
    break;

  case 7:
#line 179 "yac.y"
    {
        // Handle character constant
        (yyval.expr) = new Expression();
        (yyval.expr)->loc = gentemp(new SymbolType("char"), (yyvsp[(1) - (1)].char_value));
        emit("=", (yyval.expr)->loc->name, string((yyvsp[(1) - (1)].char_value)));
    ;}
    break;

  case 8:
#line 185 "yac.y"
    {
        // Handle float constant
        (yyval.expr) = new Expression();
        (yyval.expr)->loc = gentemp(new SymbolType("float"), convertFloatToString((yyvsp[(1) - (1)].floatval)));
        emit("=", (yyval.expr)->loc->name, convertFloatToString((yyvsp[(1) - (1)].floatval)));
    ;}
    break;

  case 9:
#line 192 "yac.y"
    {
        // Handle string literal
        (yyval.expr) = new Expression();
        (yyval.expr)->loc = gentemp(new SymbolType("ptr"), (yyvsp[(1) - (1)].char_value));
        (yyval.expr)->loc->type->arrtype = new SymbolType("char");
        emit("=", (yyval.expr)->loc->name, (yyvsp[(1) - (1)].char_value));
    ;}
    break;

  case 10:
#line 200 "yac.y"
    {
        // Handle parenthesized expression
        (yyval.expr) = (yyvsp[(2) - (3)].expr);

        // Store boolean expression for later use
        if ((yyvsp[(2) - (3)].expr)->type == "bool") {
            temp_rel = (yyvsp[(2) - (3)].expr);
        }
    ;}
    break;

  case 11:
#line 212 "yac.y"
    {
        // Create array from primary expression
        (yyval.A) = new Array();   

        if ((yyvsp[(1) - (1)].expr)->type != "bool") {
            // Normal expression
            (yyval.A)->Array = (yyvsp[(1) - (1)].expr)->loc;    
            (yyval.A)->type = (yyvsp[(1) - (1)].expr)->loc->type;    
            (yyval.A)->loc = (yyval.A)->Array;
        } else {
            // Boolean expression needs special handling
            (yyval.A)->atype = "bool_pass";
        }
    ;}
    break;

  case 12:
#line 227 "yac.y"
    {     
        // Array indexing
        (yyval.A) = new Array();
        (yyval.A)->type = (yyvsp[(1) - (4)].A)->type->arrtype;
        (yyval.A)->Array = (yyvsp[(1) - (4)].A)->Array;
        (yyval.A)->loc = gentemp(new SymbolType("integer"));
        (yyval.A)->atype = "arr";
        
        // Calculate offset
        int element_size = computeSize((yyval.A)->type);    
        string size_str = convertIntToString(element_size);
        emit("*", (yyval.A)->loc->name, (yyvsp[(3) - (4)].expr)->loc->name, size_str);
    ;}
    break;

  case 13:
#line 241 "yac.y"
    {
        // Function call
        (yyval.A) = new Array();    
        (yyval.A)->Array = gentemp((yyvsp[(1) - (4)].A)->type);
        string param_count = convertIntToString((yyvsp[(3) - (4)].num_params));
        emit("call", (yyval.A)->Array->name, (yyvsp[(1) - (4)].A)->Array->name, param_count);
    ;}
    break;

  case 14:
#line 249 "yac.y"
    {
        // Pointer member access
        (yyval.A) = new Array();
        (yyval.A)->Array = (yyvsp[(1) - (3)].A)->Array;
        (yyval.A)->loc = gentemp((yyvsp[(1) - (3)].A)->type->arrtype);
        emit("->", (yyval.A)->loc->name, (yyval.A)->Array->name, (yyvsp[(3) - (3)].char_value));
    ;}
    break;

  case 15:
#line 259 "yac.y"
    { 
        (yyval.num_params) = (yyvsp[(1) - (1)].num_params);
    ;}
    break;

  case 16:
#line 263 "yac.y"
    { 
        (yyval.num_params) = 0;
    ;}
    break;

  case 17:
#line 269 "yac.y"
    {
        // First argument in list
        (yyval.num_params) = 1;
        emit("param", (yyvsp[(1) - (1)].expr)->loc->name);    
    ;}
    break;

  case 18:
#line 275 "yac.y"
    {
        // Additional argument in list
        (yyval.num_params) = (yyvsp[(1) - (3)].num_params) + 1;
        emit("param", (yyvsp[(3) - (3)].expr)->loc->name);
    ;}
    break;

  case 19:
#line 282 "yac.y"
    { (yyval.A) = (yyvsp[(1) - (1)].A); ;}
    break;

  case 20:
#line 284 "yac.y"
    {
        (yyval.A) = new Array();
        
        // Handle various unary operators
        switch ((yyvsp[(1) - (2)].unaryOp)) {      
            case '&': // Address operator
                (yyval.A)->Array = gentemp(new SymbolType("ptr"));
                (yyval.A)->Array->type->arrtype = (yyvsp[(2) - (2)].A)->Array->type; 
                emit("=&", (yyval.A)->Array->name, (yyvsp[(2) - (2)].A)->Array->name);
                break;
                
            case '*': // Dereference operator
                (yyval.A)->atype = "ptr";
                (yyval.A)->Array = (yyvsp[(2) - (2)].A)->Array;
                break;
                
            case '+': // Unary plus - no operation needed
                (yyval.A) = (yyvsp[(2) - (2)].A);
                break;
                
            case '-': // Unary minus
                (yyval.A)->Array = gentemp(new SymbolType((yyvsp[(2) - (2)].A)->Array->type->type));
                emit("uminus", (yyval.A)->Array->name, (yyvsp[(2) - (2)].A)->Array->name);
                break;
                
            case '~': // Bitwise NOT
                (yyval.A)->Array = gentemp(new SymbolType((yyvsp[(2) - (2)].A)->Array->type->type));
                emit("~", (yyval.A)->Array->name, (yyvsp[(2) - (2)].A)->Array->name);
                break;
                
            case '!': // Logical NOT
                if ((yyvsp[(2) - (2)].A)->atype == "bool_pass") {
                    // Flip truelist and falselist for boolean expression
                    list<int> temp_list = temp_rel->truelist;
                    temp_rel->truelist = temp_rel->falselist;
                    temp_rel->falselist = temp_list;
                    (yyval.A)->atype = "bool_pass";
                } else {
                    // Standard logical NOT
                    (yyval.A)->Array = gentemp(new SymbolType((yyvsp[(2) - (2)].A)->Array->type->type));
                    emit("!", (yyval.A)->Array->name, (yyvsp[(2) - (2)].A)->Array->name);
                }
                break;
        }
    ;}
    break;

  case 21:
#line 332 "yac.y"
    { (yyval.unaryOp) = '&'; ;}
    break;

  case 22:
#line 334 "yac.y"
    { (yyval.unaryOp) = '*'; ;}
    break;

  case 23:
#line 336 "yac.y"
    { (yyval.unaryOp) = '+'; ;}
    break;

  case 24:
#line 338 "yac.y"
    { (yyval.unaryOp) = '-'; ;}
    break;

  case 25:
#line 340 "yac.y"
    { (yyval.unaryOp) = '!'; ;}
    break;

  case 26:
#line 344 "yac.y"
    {
        // Process array and pointer expressions
        (yyval.expr) = new Expression();
        if ((yyvsp[(1) - (1)].A)->atype == "arr") {
            // Handle array dereference
            (yyval.expr)->loc = gentemp((yyvsp[(1) - (1)].A)->Array->type->arrtype);    
            emit("=[]", (yyval.expr)->loc->name, (yyvsp[(1) - (1)].A)->Array->name, (yyvsp[(1) - (1)].A)->loc->name);
        } else if ((yyvsp[(1) - (1)].A)->atype == "ptr") { 
            // Handle pointer dereference
            Symbol* temp_var = gentemp((yyvsp[(1) - (1)].A)->Array->type->arrtype);
            emit("=*", temp_var->name, (yyvsp[(1) - (1)].A)->Array->name);
            (yyval.expr)->loc = temp_var;
        } else if ((yyvsp[(1) - (1)].A)->atype == "bool_pass") {
            // Handle boolean expression
            (yyval.expr) = temp_rel;
        } else {
            // Handle simple variable
            (yyval.expr)->loc = (yyvsp[(1) - (1)].A)->Array;
        }
    ;}
    break;

  case 27:
#line 365 "yac.y"
    { 
        // Multiplication operation
        (yyval.expr) = new Expression(); 
        Symbol* right_operand; 

        // Prepare right operand
        if ((yyvsp[(3) - (3)].A)->atype == "arr") {
            right_operand = gentemp((yyvsp[(3) - (3)].A)->Array->type->arrtype);    
            emit("=[]", right_operand->name, (yyvsp[(3) - (3)].A)->Array->name, (yyvsp[(3) - (3)].A)->loc->name);
        } else if ((yyvsp[(3) - (3)].A)->atype == "ptr") {
            right_operand = gentemp((yyvsp[(3) - (3)].A)->Array->type->arrtype);
            emit("=*", right_operand->name, (yyvsp[(3) - (3)].A)->Array->name);
        } else {
            right_operand = (yyvsp[(3) - (3)].A)->Array;
        }
        
        // Perform multiplication
        (yyval.expr)->loc = gentemp(new SymbolType((yyvsp[(1) - (3)].expr)->loc->type->type));
        emit("*", (yyval.expr)->loc->name, (yyvsp[(1) - (3)].expr)->loc->name, right_operand->name);
    ;}
    break;

  case 28:
#line 386 "yac.y"
    {       
        // Division operation
        (yyval.expr) = new Expression(); 
        Symbol* right_operand;  

        // Prepare right operand
        if ((yyvsp[(3) - (3)].A)->atype == "arr") {
            right_operand = gentemp((yyvsp[(3) - (3)].A)->Array->type->arrtype);    
            emit("=[]", right_operand->name, (yyvsp[(3) - (3)].A)->Array->name, (yyvsp[(3) - (3)].A)->loc->name);
        } else if ((yyvsp[(3) - (3)].A)->atype == "ptr") {
            right_operand = gentemp((yyvsp[(3) - (3)].A)->Array->type->arrtype);
            emit("=*", right_operand->name, (yyvsp[(3) - (3)].A)->Array->name);
        } else {
            right_operand = (yyvsp[(3) - (3)].A)->Array;
        }
        
        // Perform division
        (yyval.expr)->loc = gentemp(new SymbolType((yyvsp[(1) - (3)].expr)->loc->type->type));
        emit("/", (yyval.expr)->loc->name, (yyvsp[(1) - (3)].expr)->loc->name, right_operand->name);
    ;}
    break;

  case 29:
#line 407 "yac.y"
    {
        // Modulo operation
        (yyval.expr) = new Expression(); 
        Symbol* right_operand;
        
        // Prepare right operand
        if ((yyvsp[(3) - (3)].A)->atype == "arr") {
            right_operand = gentemp((yyvsp[(3) - (3)].A)->Array->type->arrtype);    
            emit("=[]", right_operand->name, (yyvsp[(3) - (3)].A)->Array->name, (yyvsp[(3) - (3)].A)->loc->name);
        } else if ((yyvsp[(3) - (3)].A)->atype == "ptr") {
            right_operand = gentemp((yyvsp[(3) - (3)].A)->Array->type->arrtype);
            emit("=*", right_operand->name, (yyvsp[(3) - (3)].A)->Array->name);
        } else {
            right_operand = (yyvsp[(3) - (3)].A)->Array;
        }
        
        // Perform modulo
        (yyval.expr)->loc = gentemp(new SymbolType((yyvsp[(1) - (3)].expr)->loc->type->type));
        emit("%", (yyval.expr)->loc->name, (yyvsp[(1) - (3)].expr)->loc->name, right_operand->name);  
    ;}
    break;

  case 30:
#line 429 "yac.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 31:
#line 430 "yac.y"
    {
        // Addition with type conversion
        Symbol* left_operand = convertTypeIfNeeded((yyvsp[(1) - (3)].expr)->loc, (yyvsp[(3) - (3)].expr)->loc->type);
        Symbol* right_operand = convertTypeIfNeeded((yyvsp[(3) - (3)].expr)->loc, (yyvsp[(1) - (3)].expr)->loc->type);
        (yyval.expr) = new Expression();
        (yyval.expr)->loc = gentemp(getDominantType(left_operand->type, right_operand->type));
        emit("+", (yyval.expr)->loc->name, left_operand->name, right_operand->name);
    ;}
    break;

  case 32:
#line 438 "yac.y"
    {
        // Subtraction with type conversion
        Symbol* left_operand = convertTypeIfNeeded((yyvsp[(1) - (3)].expr)->loc, (yyvsp[(3) - (3)].expr)->loc->type);
        Symbol* right_operand = convertTypeIfNeeded((yyvsp[(3) - (3)].expr)->loc, (yyvsp[(1) - (3)].expr)->loc->type);
        (yyval.expr) = new Expression();
        (yyval.expr)->loc = gentemp(getDominantType(left_operand->type, right_operand->type));
        emit("-", (yyval.expr)->loc->name, left_operand->name, right_operand->name);
    ;}
    break;

  case 33:
#line 448 "yac.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 34:
#line 449 "yac.y"
    {
        (yyval.expr) = new Expression();
        (yyval.expr)->loc = gentemp(new SymbolType("integer"));
        emit("<<", (yyval.expr)->loc->name, (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name);
    ;}
    break;

  case 35:
#line 454 "yac.y"
    {
        (yyval.expr) = new Expression();
        (yyval.expr)->loc = gentemp(new SymbolType("integer"));
        emit(">>", (yyval.expr)->loc->name, (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name);
    ;}
    break;

  case 36:
#line 461 "yac.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 37:
#line 462 "yac.y"
    {
        (yyval.expr) = new Expression();
        (yyval.expr)->loc = gentemp(new SymbolType("integer"));
        emit("&", (yyval.expr)->loc->name, (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name);
    ;}
    break;

  case 38:
#line 469 "yac.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 39:
#line 470 "yac.y"
    {
        (yyval.expr) = new Expression();
        (yyval.expr)->loc = gentemp(new SymbolType("integer"));
        emit("^", (yyval.expr)->loc->name, (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name);
    ;}
    break;

  case 40:
#line 477 "yac.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 41:
#line 478 "yac.y"
    {
        (yyval.expr) = new Expression();
        (yyval.expr)->loc = gentemp(new SymbolType("integer"));
        emit("|", (yyval.expr)->loc->name, (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name);
    ;}
    break;

  case 42:
#line 485 "yac.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 43:
#line 487 "yac.y"
    {
        // Less than comparison
        (yyval.expr) = new Expression();
        (yyval.expr)->type = "bool";
        (yyval.expr)->truelist = makelist(nextinstr());
        (yyval.expr)->falselist = makelist(nextinstr() + 1);
        emit("<", "", (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name);
        emit("goto", "");    
    ;}
    break;

  case 44:
#line 497 "yac.y"
    {   
        // Greater than comparison
        (yyval.expr) = new Expression();        
        (yyval.expr)->type = "bool";
        (yyval.expr)->truelist = makelist(nextinstr());
        (yyval.expr)->falselist = makelist(nextinstr() + 1);
        emit(">", "", (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name);
        emit("goto", "");
    ;}
    break;

  case 45:
#line 507 "yac.y"
    {   
        // Less than or equal comparison
        (yyval.expr) = new Expression();        
        (yyval.expr)->type = "bool";
        (yyval.expr)->truelist = makelist(nextinstr());
        (yyval.expr)->falselist = makelist(nextinstr() + 1);
        emit("<=", "", (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name);
        emit("goto", "");
    ;}
    break;

  case 46:
#line 520 "yac.y"
    {  
        // Greater than or equal comparison
        (yyval.expr) = new Expression();    
        (yyval.expr)->type = "bool";
        (yyval.expr)->truelist = makelist(nextinstr());
        (yyval.expr)->falselist = makelist(nextinstr() + 1);
        emit(">=", "", (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name);
        emit("goto", "");
    ;}
    break;

  case 47:
#line 531 "yac.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 48:
#line 533 "yac.y"
    {
        // Equal to comparison
        // Convert operands to int if they're bool
        if (convertBoolToInt((yyvsp[(1) - (4)].expr)) == 1) {
            backpatch((yyvsp[(1) - (4)].expr)->nextlist, (yyvsp[(3) - (4)].instr_number));
        }
        if (convertBoolToInt((yyvsp[(4) - (4)].expr)) == 1) {
            backpatch((yyvsp[(4) - (4)].expr)->nextlist, nextinstr());
        }
        
        (yyval.expr) = new Expression();
        (yyval.expr)->type = "bool";
        (yyval.expr)->truelist = makelist(nextinstr());
        (yyval.expr)->falselist = makelist(nextinstr() + 1); 
        emit("==", "", (yyvsp[(1) - (4)].expr)->loc->name, (yyvsp[(4) - (4)].expr)->loc->name);
        emit("goto", "");                
    ;}
    break;

  case 49:
#line 551 "yac.y"
    {       
        // Not equal comparison
        if (convertBoolToInt((yyvsp[(1) - (4)].expr)) == 1) {
            backpatch((yyvsp[(1) - (4)].expr)->nextlist, (yyvsp[(3) - (4)].instr_number));
        }
        if (convertBoolToInt((yyvsp[(4) - (4)].expr)) == 1) {
            backpatch((yyvsp[(4) - (4)].expr)->nextlist, nextinstr());
        }
        
        (yyval.expr) = new Expression();
        (yyval.expr)->type = "bool";
        (yyval.expr)->truelist = makelist(nextinstr());
        (yyval.expr)->falselist = makelist(nextinstr() + 1); 
        emit("!=", "", (yyvsp[(1) - (4)].expr)->loc->name, (yyvsp[(4) - (4)].expr)->loc->name);
        emit("goto", "");
    ;}
    break;

  case 50:
#line 571 "yac.y"
    {
        convertIntToBool((yyvsp[(1) - (2)].expr));
        (yyval.expr) = (yyvsp[(1) - (2)].expr);
    ;}
    break;

  case 51:
#line 577 "yac.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 52:
#line 579 "yac.y"
    { 
        // Logical AND operation
        convertIntToBool((yyvsp[(3) - (3)].expr));
        (yyval.expr) = new Expression();
        (yyval.expr)->type = "bool";
        backpatch((yyvsp[(1) - (3)].expr)->truelist, (yyvsp[(2) - (3)].instr_number));
        (yyval.expr)->truelist = (yyvsp[(3) - (3)].expr)->truelist;
        (yyval.expr)->falselist = merge((yyvsp[(1) - (3)].expr)->falselist, (yyvsp[(3) - (3)].expr)->falselist);
    ;}
    break;

  case 53:
#line 592 "yac.y"
    {
        convertIntToBool((yyvsp[(1) - (2)].expr));
        (yyval.expr) = (yyvsp[(1) - (2)].expr);
    ;}
    break;

  case 54:
#line 597 "yac.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 55:
#line 599 "yac.y"
    { 
        // Logical OR operation
        convertIntToBool((yyvsp[(3) - (3)].expr));            
        (yyval.expr) = new Expression();            
        (yyval.expr)->type = "bool";
        backpatch((yyvsp[(1) - (3)].expr)->falselist, (yyvsp[(2) - (3)].instr_number));
        (yyval.expr)->truelist = merge((yyvsp[(1) - (3)].expr)->truelist, (yyvsp[(3) - (3)].expr)->truelist);
        (yyval.expr)->falselist = (yyvsp[(3) - (3)].expr)->falselist;
    ;}
    break;

  case 56:
#line 612 "yac.y"
    {
        convertIntToBool((yyvsp[(1) - (2)].expr));
        (yyval.expr) = (yyvsp[(1) - (2)].expr);
    ;}
    break;

  case 57:
#line 617 "yac.y"
    {(yyval.expr) = (yyvsp[(1) - (1)].expr);;}
    break;

  case 58:
#line 619 "yac.y"
    {
        // Ternary conditional operator
        (yyval.expr)->loc = gentemp((yyvsp[(3) - (7)].expr)->loc->type);
        (yyval.expr)->loc->update((yyvsp[(3) - (7)].expr)->loc->type);
        
        // Handle the conditional branching
        emit("=", (yyval.expr)->loc->name, (yyvsp[(7) - (7)].expr)->loc->name);
        list<int> temp_list = makelist(nextinstr());
        emit("goto", "");
        
        backpatch((yyvsp[(4) - (7)].stat)->nextlist, nextinstr());
        emit("=", (yyval.expr)->loc->name, (yyvsp[(3) - (7)].expr)->loc->name);
        
        list<int> merge_list = makelist(nextinstr());
        temp_list = merge(temp_list, merge_list);                        
        emit("goto", "");
        
        // Patch all jumps
        backpatch((yyvsp[(1) - (7)].expr)->truelist, (yyvsp[(2) - (7)].instr_number));
        backpatch((yyvsp[(1) - (7)].expr)->falselist, (yyvsp[(6) - (7)].instr_number));
        backpatch(temp_list, nextinstr());
    ;}
    break;

  case 59:
#line 643 "yac.y"
    {(yyval.expr) = (yyvsp[(1) - (1)].expr);;}
    break;

  case 60:
#line 645 "yac.y"
    {
        // Handle different assignment types
        if ((yyvsp[(1) - (3)].A)->atype == "arr") {
            // Array element assignment
            (yyvsp[(3) - (3)].expr)->loc = convertType((yyvsp[(3) - (3)].expr)->loc, (yyvsp[(1) - (3)].A)->type->type);
            emit("[]=", (yyvsp[(1) - (3)].A)->Array->name, (yyvsp[(1) - (3)].A)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name);        
        } else if ((yyvsp[(1) - (3)].A)->atype == "ptr") {
            // Pointer assignment
            emit("*=", (yyvsp[(1) - (3)].A)->Array->name, (yyvsp[(3) - (3)].expr)->loc->name);    
        } else {
            // Direct variable assignment
            (yyvsp[(3) - (3)].expr)->loc = convertType((yyvsp[(3) - (3)].expr)->loc, (yyvsp[(1) - (3)].A)->Array->type->type);
            emit("=", (yyvsp[(1) - (3)].A)->Array->name, (yyvsp[(3) - (3)].expr)->loc->name);
        }
        (yyval.expr) = (yyvsp[(3) - (3)].expr);
    ;}
    break;

  case 61:
#line 663 "yac.y"
    {  (yyval.expr) = (yyvsp[(1) - (1)].expr);  ;}
    break;

  case 62:
#line 666 "yac.y"
    { ;}
    break;

  case 63:
#line 670 "yac.y"
    {
        (yyval.symp_list) = new vector<Symbol*>();
        (yyval.symp_list)->push_back((yyvsp[(1) - (1)].symp));
    ;}
    break;

  case 64:
#line 675 "yac.y"
    {
        (yyval.symp_list) = (yyvsp[(1) - (3)].symp_list);
        (yyval.symp_list)->push_back((yyvsp[(3) - (3)].symp));
    ;}
    break;

  case 65:
#line 681 "yac.y"
    {(yyval.symp) = (yyvsp[(1) - (1)].symp);;}
    break;

  case 66:
#line 683 "yac.y"
    {
        // Initialize with value if available
        if ((yyvsp[(3) - (3)].symp)->val != "") (yyvsp[(1) - (3)].symp)->val = (yyvsp[(3) - (3)].symp)->val;
        emit("=", (yyvsp[(1) - (3)].symp)->name, (yyvsp[(3) - (3)].symp)->name);    
    ;}
    break;

  case 67:
#line 691 "yac.y"
    { var_type = "void"; ;}
    break;

  case 68:
#line 692 "yac.y"
    { var_type = "char"; ;}
    break;

  case 69:
#line 693 "yac.y"
    { var_type = "integer"; ;}
    break;

  case 70:
#line 694 "yac.y"
    { var_type = "float"; ;}
    break;

  case 71:
#line 695 "yac.y"
    { var_type = "bool"; ;}
    break;

  case 72:
#line 699 "yac.y"
    {
        // Handle pointer type
        SymbolType *base_type = (yyvsp[(1) - (2)].sym_type);
        while (base_type->arrtype != NULL) base_type = base_type->arrtype;
        base_type->arrtype = (yyvsp[(2) - (2)].symp)->type;
        (yyval.symp) = (yyvsp[(2) - (2)].symp)->update((yyvsp[(1) - (2)].sym_type));
    ;}
    break;

  case 73:
#line 706 "yac.y"
    {   ;}
    break;

  case 74:
#line 711 "yac.y"
    {   
    Symbol* symbol = ST->lookupIdentifier(id);
    if (symbol == nullptr) {
        symbol = ST->lookupDeclarator(id);
    }
    (yyval.symp) = symbol->update(new SymbolType(var_type));
    currSymbolPtr = (yyval.symp); 
;}
    break;

  case 75:
#line 721 "yac.y"
    {
        // Simple variable declarator
        Symbol* symbol = ST->lookupDeclarator(id);
        (yyval.symp) = symbol->update(new SymbolType(var_type));
        currSymbolPtr = (yyval.symp);    
    ;}
    break;

  case 76:
#line 728 "yac.y"
    {
        // Array declarator
        Symbol *symbol = ST->lookupDeclarator(id);
        (yyval.symp) = symbol->update(new SymbolType(var_type));
        currSymbolPtr = (yyval.symp);
        
        // Create array type with size
        SymbolType* array_type = new SymbolType("arr", symbol->type, (yyvsp[(3) - (4)].intval));
        (yyval.symp) = symbol->update(array_type);
    ;}
    break;

  case 77:
#line 739 "yac.y"
    {
        // Function declarator
        ST->name = (yyvsp[(1) - (4)].symp)->name;
        
        // Set up return value
        if ((yyvsp[(1) - (4)].symp)->type->type != "void") {
            Symbol *ret_symbol = ST->lookupIdentifier("return");
            if (ret_symbol == nullptr) {
                ret_symbol = ST->lookupDeclarator("return");
            }
            ret_symbol->update((yyvsp[(1) - (4)].symp)->type);        
        }
        
        (yyvsp[(1) - (4)].symp)->nested = ST;
        ST->parent = globalST;
        changeTable(globalST);                
        currSymbolPtr = (yyval.symp);
    ;}
    break;

  case 78:
#line 760 "yac.y"
    { 
        (yyval.sym_type) = new SymbolType("ptr");
    ;}
    break;

  case 79:
#line 765 "yac.y"
    { ;}
    break;

  case 81:
#line 769 "yac.y"
    {  ;}
    break;

  case 82:
#line 770 "yac.y"
    {  ;}
    break;

  case 83:
#line 773 "yac.y"
    {  ;}
    break;

  case 84:
#line 776 "yac.y"
    { (yyval.symp) = (yyvsp[(1) - (1)].expr)->loc; ;}
    break;

  case 85:
#line 779 "yac.y"
    { (yyval.stat) = (yyvsp[(1) - (1)].stat); ;}
    break;

  case 86:
#line 781 "yac.y"
    { 
        (yyval.stat) = new Statement();
        (yyval.stat)->nextlist = (yyvsp[(1) - (1)].expr)->nextlist; 
    ;}
    break;

  case 87:
#line 785 "yac.y"
    { (yyval.stat) = (yyvsp[(1) - (1)].stat); ;}
    break;

  case 88:
#line 786 "yac.y"
    { (yyval.stat) = (yyvsp[(1) - (1)].stat); ;}
    break;

  case 89:
#line 787 "yac.y"
    { (yyval.stat) = (yyvsp[(1) - (1)].stat); ;}
    break;

  case 90:
#line 791 "yac.y"
    { 
        (yyval.stat) = (yyvsp[(2) - (3)].stat); 
    ;}
    break;

  case 91:
#line 796 "yac.y"
    { (yyval.stat) = new Statement(); ;}
    break;

  case 92:
#line 797 "yac.y"
    { (yyval.stat) = (yyvsp[(1) - (1)].stat); ;}
    break;

  case 93:
#line 800 "yac.y"
    { (yyval.stat) = (yyvsp[(1) - (1)].stat); ;}
    break;

  case 94:
#line 802 "yac.y"
    { 
        (yyval.stat) = (yyvsp[(3) - (3)].stat);
        backpatch((yyvsp[(1) - (3)].stat)->nextlist, (yyvsp[(2) - (3)].instr_number));
    ;}
    break;

  case 95:
#line 808 "yac.y"
    { (yyval.stat) = new Statement(); ;}
    break;

  case 96:
#line 809 "yac.y"
    { (yyval.stat) = (yyvsp[(1) - (1)].stat); ;}
    break;

  case 97:
#line 812 "yac.y"
    {(yyval.expr) = (yyvsp[(1) - (2)].expr);;}
    break;

  case 98:
#line 813 "yac.y"
    {(yyval.expr) = new Expression();;}
    break;

  case 99:
#line 818 "yac.y"
    {
        convertIntToBool((yyvsp[(3) - (3)].expr));
        (yyval.expr) = (yyvsp[(3) - (3)].expr);   
    ;}
    break;

  case 100:
#line 824 "yac.y"
    {
        // Simple if statement
        (yyval.stat) = new Statement();
        backpatch((yyvsp[(1) - (4)].expr)->truelist, (yyvsp[(3) - (4)].instr_number));
        (yyval.stat)->nextlist = merge((yyvsp[(1) - (4)].expr)->falselist, (yyvsp[(4) - (4)].stat)->nextlist);
    ;}
    break;

  case 101:
#line 831 "yac.y"
    {   
        // If-else statement
        (yyval.stat) = new Statement();
        backpatch((yyvsp[(1) - (7)].expr)->truelist, (yyvsp[(3) - (7)].instr_number));
        backpatch((yyvsp[(1) - (7)].expr)->falselist, (yyvsp[(6) - (7)].instr_number));
        
        // Merge nextlists from both branches
        list<int> merged_nextlist = (yyvsp[(4) - (7)].stat)->nextlist;
        (yyval.stat)->nextlist = merge((yyvsp[(7) - (7)].stat)->nextlist, merged_nextlist);
    ;}
    break;

  case 102:
#line 844 "yac.y"
    {
        // For loop
        (yyval.stat) = new Statement();
        
        // Handle conditional expression
        convertIntToBool((yyvsp[(5) - (11)].expr));
        
        // Backpatching for loop structure
        backpatch((yyvsp[(5) - (11)].expr)->truelist, (yyvsp[(10) - (11)].instr_number));    // If condition true, execute body
        backpatch((yyvsp[(8) - (11)].stat)->nextlist, (yyvsp[(4) - (11)].instr_number));     // After increment, check condition again
        backpatch((yyvsp[(11) - (11)].stat)->nextlist, (yyvsp[(6) - (11)].instr_number));    // After body, do increment
        
        // Jump back to condition check
        string jump_target = convertIntToString((yyvsp[(6) - (11)].instr_number));
        emit("goto", jump_target);
        
        // Exit loop if condition is false
        (yyval.stat)->nextlist = (yyvsp[(5) - (11)].expr)->falselist;
    ;}
    break;

  case 103:
#line 866 "yac.y"
    {
        (yyval.stat) = new Statement();    
        emit("return", (yyvsp[(2) - (3)].expr)->loc->name);
    ;}
    break;

  case 104:
#line 871 "yac.y"
    {
        (yyval.stat) = new Statement();    
        emit("return", "");                         
    ;}
    break;

  case 105:
#line 877 "yac.y"
    { ;}
    break;

  case 106:
#line 878 "yac.y"
    { ;}
    break;

  case 107:
#line 881 "yac.y"
    {  ;}
    break;

  case 108:
#line 882 "yac.y"
    {  ;}
    break;

  case 109:
#line 886 "yac.y"
    {
        // Complete function definition
        ST->parent = globalST;
        table_count = 0;
        label_table.clear();
        changeTable(globalST);
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2688 "yac.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 895 "yac.y"


void yyerror(string s) {
    cout << s << endl;
}
