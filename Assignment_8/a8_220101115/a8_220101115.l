%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "a8_220101115.tab.h"

int yylex(void);
void yyerror(const char *s);
%}


%%
"expr"          { return EXPR; }
"bintodec"      { return BINTODEC; }
"bintohex"      { return BINTOHEX; }
"hextobin"      { return HEXTOBIN; }
"hextodec"      { return HEXTODEC; }

[0-9A-Fa-f]+    { yylval.sval = strdup(yytext); return NUMBER; }

"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MULTIPLY; }
"/"             { return DIVIDE; }
"**"            { return POWER; }
"("             { return LPAREN; }
")"             { return RPAREN; }


[ \t\n]         ; /* Ignore whitespace */
.               { yyerror("Unexpected character"); }

%%

int yywrap() {
    return 1;
}
