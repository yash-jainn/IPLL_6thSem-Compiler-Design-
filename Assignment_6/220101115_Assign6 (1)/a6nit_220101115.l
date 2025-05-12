%{
#include<stdio.h>
#define KEYWORD 1  
#define IDENTIFIER 2  
#define INT_CONSTANT 3 
#define CHAR_CONSTANT 4   
#define FLOAT_CONSTANT 5 
#define STRING_LITERALS 6
#define PUNCTUATORS 7 
#define SINGLE_COMMENT 8
#define MULTI_COMMENT 9


typedef struct Symbol{
    char name[100];
    char type[100];
    char value[100];
    struct Symbol* next;
} Symbol;

Symbol* symbolTable = NULL; // Head of the symbol table

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
    FILE *file = fopen("symtab_nit.txt", "w"); 
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
{KEYWORD}         {printf("<KEYWORD, 1, %s>\n", yytext); if(check(yytext) == 1)addSymbol(yytext, "Keyword", "");}
            
{IDENTIFIER}      {printf("<IDENTIFIER, 2, %s>\n", yytext);if(check(yytext) == 1)addSymbol(yytext, "Identifier", "");}
{INT_CONSTANT}    {printf("<INTEGER CONST, 3, %s>\n", yytext);if(check(yytext) == 1) addSymbol("", "int constant", yytext );}
{CHAR_CONSTANT}   {printf("<CHAR CONST, 4, %s>\n", yytext);if(check(yytext) == 1)addSymbol("", "char constant", yytext );}
{FLOAT_CONSTANT}  {printf("<FLOAT CONSTANT, 5, %s>\n", yytext);if(check(yytext) == 1)addSymbol("", "float constant", yytext );}
{STRING_LITERALS} {printf("<STRING, 6, %s>\n", yytext);}
{PUNCTUATORS}     {printf("<PUNCTUATOR, 7, %s>\n", yytext);}
{SINGLE_COMMENT}  {printf("<SINGLE LINE COMMENT, 8, %s>\n", yytext);}
{MULTI_COMMENT}   {printf("<MULTILINE COMMENT, 9, %s>\n", yytext);}
{WS}              {printf("");}
%%


int main() {
  yylex();
  printSymbolTable();
  return 0;
}   
