%{
	#include <stdio.h>
    #include <stdlib.h>
	#include <string.h>
	#include "translator.h"
	#include "yac.tab.h"
	extern "C" int yylex();
    extern YYSTYPE yylval;
    extern int line = 1;
     
%}

%option noyywrap

/* Regular Expressions*/
digit           [0-9]
nonzero        [1-9]
letter          [a-zA-Z_]


digit_seq       {digit}{digit}*

ESCAPE_SEQ      "\\b"|"\\v"|"\\\'"|"\\\""|"\\\?"|"\\\\"|"\\a"|"\\f"|"\\n"|"\\r"|"\\t"
C_CHAR          [^\'\\\n]|{ESCAPE_SEQ}
S_CHAR          [^\"\\\n]|{ESCAPE_SEQ}

CHAR_SEQ        {C_CHAR}{C_CHAR}*
STRING_SEQ      {S_CHAR}{S_CHAR}*

IDENTIFIER      {letter}({letter}|{digit})*

FLOAT_CONST     ({digit}+\.{digit}*)|({digit}*\.{digit}+)
INT_CONST       0|{nonzero}{digit}*  
CHAR_CONST      \'{CHAR_SEQ}\'


STRING          \"{STRING_SEQ}\"|\"\"
COMMENT_LINE    "//".*
COMMENT_MULTI   "/*"([^*]|\*+[^/*])*\**(\*"/")? 

WS              [ \t]
NEWLINE         [\n]

%%

{COMMENT_LINE}          { /*printf("single line comment(ignored)\n");*/ }
{COMMENT_MULTI}         { /*printf("multi line comment(ignored)\n");*/  }




"while"         { return WHILE; }    /* New token */
"float"         { return FLOAT; }  /* Add float keyword */
"integer"                   { return INTEGER;      }
"char"                  { return CHAR;     }
"void"                  { return VOID;     }

"begin"         { return BEGIN_TOK; }    /* New token */
"end"           { return END; }      /* New token */
"bool"          { return BOOL; }     /* New token */
"const"         { return CONST; }    /* New token */
"do"            { return DO; }       /* New token */

"for"                   { return FOR;      }
"if"                    { return IF;       }
"else"                  { return ELSE;     }


"return"                { return RETURN;   }

"<"                     { return LT;         } /* Less than */
">"                     { return GT;         } /* Greater than */
"<="                    { return LTE;        } /* Already defined */
">="                    { return GTE;        } /* Already defined */
"=="                    { return EQ;         } /* Already defined */
"!="                    { return NEQ;        } /* Already defined */


"<<"                    { return BIT_SL;     } /* Bitwise shift left */
">>"                    { return BIT_SR;     } /* Bitwise shift right */
"&"                     { return BITWISE_AND;} /* Already correct */
"|"                     { return BITWISE_OR; } /* Add bitwise OR */
"^"                     { return BITWISE_XOR;} /* Add bitwise XOR */

"||"                    { return OR;                   }
"->"            { return ARROW; }  /* New token */
"&&"                    { return AND;                  }

";"                     { return SEMICOLON;  }




"*"                     { return MUL;        }
"-"                     { return SUB;        }
"/"                     { return DIV;        }
"+"                     { return ADD;        }
"%"                     { return MOD;        }

"("                     { return ROUND_BRACKET_OPEN;   }
")"                     { return ROUND_BRACKET_CLOSE;  }
"["                     { return SQUARE_BRACKET_OPEN;  }
"]"                     { return SQUARE_BRACKET_CLOSE; }


"!"                     { return EXCLAIM;    }

","                     { return COMMA;      }
"="                     { return ASSIGN;     }
"?"                     { return QUESTION;   }
":"                     { return COLON;      }


{FLOAT_CONST}   { 
                    yylval.floatval = atof(yytext); 
                    return FLOAT_CONSTANT; 
                }

{INT_CONST}             { 
	                        yylval.intval = atoi(yytext);
							return INTEGER_CONSTANT; 
                        }
{CHAR_CONST}            { 
	                        yylval.char_value = yytext;
							return CHARACTER_CONSTANT; 
						}



{IDENTIFIER}            { 
							id = yytext;
							return IDENTIFIER;
						}

{STRING}                { 
	                        yylval.char_value = yytext;
							return STRING_LITERAL; 
						}

{WS}                    { /*White-space Rule*/ }

{NEWLINE}               { /* ++line; */ }

%%