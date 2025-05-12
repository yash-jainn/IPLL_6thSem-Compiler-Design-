/*
%{
    include libraries
%}

Declarations here

%%
    RULES here
%%

optional main function

*/


%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define KEYWORD 1  
#define IDENTIFIER 2  
#define INT_CONSTANT 3 
#define CHAR_CONSTANT 4   
#define FLOAT_CONSTANT 5 
#define STRING_LITERALS 6
#define PUNCTUATORS 7 
#define SINGLE_COMMENT 8
#define MULTI_COMMENT 9
#define WS 10

typedef struct Symbol{
    char name[100];
    char type[100];
    char value[100];
    struct Symbol* next;
} Symbol;

Symbol* symbolTable = NULL; /* Head of the symbol table */

void addSymbol(char* name, char* type, char* value){
    Symbol * temp = (Symbol*) malloc(sizeof(Symbol));
    
    strcpy(temp->name, name);
    strcpy(temp->type, type);
    strcpy(temp->value, value);
    
    temp->next= symbolTable;
    symbolTable = temp;
}

int check(char* name){
    for(Symbol* it = symbolTable;it!=NULL;it= it->next){
        if( strcmp(it->name, name) == 0 )return 0;
    }
    return 1;
}

void printSymbolTable (){
    FILE *file = fopen("symtab_it.txt", "w"); 
    if(symbolTable == NULL)return;
    Symbol* it = symbolTable;
    while(it!=NULL){
        fprintf(file, "Name: %s, Type: %s, Value: %s\n", it->name, it->type, it->value);
        it = it->next;
    }
}
%}



/* KEYWORDS */

KEYWORD "char"|"else"|"for"|"if"|"integer"|"return"|"void"|"float"|"const"|"while"|"bool"|"do"|"begin"|"end"


/*IDENTIFIER*/
IDENTIFIER [_a-zA-Z][_a-zA-Z0-9]*  

/*--------INTEGER CONSTANT-----------*/
INT_CONSTANT  [+-]?[1-9][0-9]*


/*-------DIGIT_SEQUENCE----------*/
digit [0-9]
DIGIT_SEQUENCE [0-9]+

/*-------FRACTIONAL_CONSTANT----------*/
FRACTIONAL_CONSTANT ({DIGIT_SEQUENCE}?[.]{DIGIT_SEQUENCE})|({DIGIT_SEQUENCE}[.])

/*-------EXPONENT_PART----------*/
EXPONENT_PART [eE][+-]?{DIGIT_SEQUENCE}


/*-------FLOAT_CONSTANT----------*/
FLOAT_CONSTANT ({FRACTIONAL_CONSTANT}{EXPONENT_PART}?)|({DIGIT_SEQUENCE}{EXPONENT_PART})

/*-------CHARACTER CONSTANT----------*/
CHAR_CONSTANT	'{CHAR_SEQ}'
CHAR_SEQ	{C_CHAR}+
C_CHAR		{SRC_SET}|{ESC_SEQ}
SRC_SET		[^\\\'\\n]

/*-------ESCAPE SEQUENCE----------*/
ESC_SEQ 	\\a|\\b|\\f|\\n|\\t|\\r|\\v|\\\'|\\\"|\\\\|\\\? 


/*STRING LITERALS*/

S_CHAR_SEQUENCE	     {S_CHAR}+
S_CHAR  		     {ESC_SEQ}|[^\\\"\\n]
STRING_LITERALS    ["]({S_CHAR_SEQUENCE}?)["]


/*---------PUNCTUATIONS--------------*/
PUNCTUATORS              "["|"]"|"("|")"|"->"|"&"|"*"|"+"|"-"|"/"|"%"|"!"|"?"|"<"|">"|"<="|">="|"=="|"!="|"&&"|"||"|"="|":"|";"|","

/*---------WHITESPACE , TAB , NEW LINE CHARACTER-----------*/
WS			[ \t\n]


/*--------SINGLE COMMENT LINE---------*/
SINGLE_COMMENT	[/][/][^\\n]*
 
/*--------MULTI COMMENT LINE----------*/
MULTI_COMMENT [/][*]{STR2}*[*][/]
STR2		[^*]|{STR3}
STR3 		[*][^*/]

%% 

{KEYWORD}         return KEYWORD;
{IDENTIFIER}      return IDENTIFIER;
{INT_CONSTANT}    return INT_CONSTANT;
{CHAR_CONSTANT}   return CHAR_CONSTANT;
{FLOAT_CONSTANT}  return FLOAT_CONSTANT;
{STRING_LITERALS} return STRING_LITERALS;
{PUNCTUATORS}     return PUNCTUATORS;
{SINGLE_COMMENT}  return SINGLE_COMMENT;
{MULTI_COMMENT}   return MULTI_COMMENT;
{WS}              return WS;


%%
int main() {
    int token;
    while ((token = yylex())) {
        switch (token) {
            case KEYWORD:
                printf("<KEYWORD, %d, %s>\n", token, yytext);
                if(check(yytext) == 1){
                    addSymbol(yytext, "Keyword", "");
                }
                break;
            case IDENTIFIER:
                printf("<IDENTIFIER, %d, %s>\n", token, yytext);
                if(check(yytext) == 1){
                    addSymbol(yytext, "Identifier", "");
                }
                break;
            case CHAR_CONSTANT:
                printf("<CHAR_CONSTANT, %d, %s>\n", token, yytext);
                if(check(yytext) == 1){
                    addSymbol("", "char constant", yytext );
                }
                break;
            case INT_CONSTANT:
                printf("<INT_CONSTANT, %d, %s>\n", token, yytext);
                if(check(yytext) == 1){
                    addSymbol("", "int constant", yytext );
                }
                break;
            case FLOAT_CONSTANT:
                printf("<FLOAT_CONSTANT, %d, %s>\n", token, yytext);
                if(check(yytext) == 1){
                    addSymbol("", "float Constant", yytext );
                }
                break;
            case STRING_LITERALS:
                printf("<STRING_LITERALS, %d, %s>\n", token, yytext);
                break;
            case PUNCTUATORS:
                printf("<PUNCTUATORS, %d, %s>\n", token, yytext);
                break;
            case SINGLE_COMMENT:
                printf("<SINGLE_COMMENT, %d, %s>\n", token, yytext);
                break;
            case MULTI_COMMENT:
                printf("<MULTI_COMMENT, %d, %s>\n", token, yytext);
                break;
            case WS:
                printf("");
                break;
            default:
                printf("<INVALID_TOKEN, %s>\n", yytext);
                break;
        }
       
    }
    printSymbolTable();
    return 0;
}
