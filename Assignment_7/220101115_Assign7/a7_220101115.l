%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
#include <stdlib.h>

extern void yyerror(const char *);
int line_num = 1;
%}

/* Regular definitions */
digit       [0-9]
nonzero     [1-9]
letter      [a-zA-Z]
id_nondigit [a-zA-Z_]
whitespace  [ \t\r\f\v]

%%

"return"    { return RETURN; }
"void"      { return VOID; }
"float"     { return FLOAT; }
"integer"   { return INTEGER; }
"char"      { return CHAR; }
"for"       { return FOR; }
"const"     { return CONST; }
"while"     { return WHILE; }
"bool"      { return BOOL; }
"if"        { return IF; }
"do"        { return DO; }
"else"      { return ELSE; }
"begin"     { return BEGIN_TOKEN; }
"end"       { return END_TOKEN; }

{id_nondigit}({id_nondigit}|{digit})* {
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}

{nonzero}{digit}* {
    yylval.num = atoi(yytext);
    return INT_CONST;
}

0 {
    yylval.num = 0;
    return INT_CONST;
}

{digit}+\.{digit}+([eE][+-]?{digit}+)? {
    yylval.fnum = atof(yytext);
    return FLOAT_CONST;
}

{digit}+[eE][+-]?{digit}+ {
    yylval.fnum = atof(yytext);
    return FLOAT_CONST;
}

\'[^\'\\\n]\'|\'\\[abfnrtv\\\'\"]\'  {
    yylval.ch = yytext[1] == '\\' ? 
                (yytext[2] == 'n' ? '\n' : 
                 yytext[2] == 't' ? '\t' : 
                 yytext[2] == 'r' ? '\r' : 
                 yytext[2] == 'b' ? '\b' : 
                 yytext[2] == 'f' ? '\f' : 
                 yytext[2] == 'v' ? '\v' : 
                 yytext[2] == 'a' ? '\a' : 
                 yytext[2] == '\\' ? '\\' : 
                 yytext[2] == '\'' ? '\'' : 
                 yytext[2] == '\"' ? '\"' : yytext[2]) : yytext[1];
    return CHAR_CONST;
}

\"[^\"\\\n]*\"  {
    yylval.str = strdup(yytext);
    return STRING_LITERAL;
}

"["         { return '['; }
"]"         { return ']'; }
"("         { return '('; }
")"         { return ')'; }
"->"        { return ARROW; }
"++"        { return INC; }
"--"        { return DEC; }
"&"         { return '&'; }
"*"         { return '*'; }
"+"         { return '+'; }
"-"         { return '-'; }
"!"         { return '!'; }
"/"         { return '/'; }
"%"         { return '%'; }
"<<"        { return LEFT_SHIFT; }
">>"        { return RIGHT_SHIFT; }
"<"         { return '<'; }
">"         { return '>'; }
"<="        { return LESS_EQUAL; }
">="        { return GREATER_EQUAL; }
"=="        { return EQUAL; }
"!="        { return NOT_EQUAL; }
"~"         { return '~'; }
"|"         { return '|'; }
"&&"        { return AND; }
"||"        { return OR; }
"?"         { return '?'; }
":"         { return ':'; }
";"         { return ';'; }
"="         { return '='; }
","         { return ','; }

"/*"        { 
    char c, prev = 0;
    while ((c = input()) != 0) {
        if (c == '/' && prev == '*')
            break;
        if (c == '\n')
            line_num++;
        prev = c;
    }
}

"//"        { 
    char c;
    while ((c = input()) != '\n' && c != 0);
    line_num++;
}

\n          { line_num++; }
{whitespace}+ { /* ignore whitespace */ }

.           { yyerror("Invalid character"); }

%%

int yywrap() {
    return 1;
}
