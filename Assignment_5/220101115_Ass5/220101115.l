%{
#define KEYWORD 1  
#define IDENTIFIER 2  /* Can be digit, or non-digit */
#define CHAR_CONSTANT 3  
#define INT_CONSTANT 4   /* Signed integer */
#define STRING_LITERALS 5 
#define PUNCTUATORS 6 /* All the braces and special symbols(except escape sequence) are qualified as punctuators */
#define SINGLE_COMMENT 7
#define MULTI_COMMENT 8
%}

/* KEYWORDS */

KEYWORD "char*"|"int*"|"char"|"else"|"for"|"if"|"int"|"return"|"void"

/*IDENTIFIER*/
IDENTIFIER [_a-zA-Z][_a-zA-Z0-9]*  

/*--------INTEGER CONSTANT-----------*/
INT_CONSTANT  ([+-]?)[0-9]+

/*-------CHARACTER CONSTANT----------*/
CHAR_CONSTANT	'{CHAR_SEQ}'
CHAR_SEQ	{C_CHAR}+
C_CHAR		{SRC_SET}|{ESC_SEQ}
SRC_SET		[^\\\'\\n]


/*STRING CONSTANT*/
ESC_SEQ 	\\a|\\b|\\f|\\n|\\t|\\r|\\v|\\\'|\\\"|\\\\|\\\? 

S_CHAR_SEQUENCE	     {S_CHAR}+
S_CHAR  		     {ESC_SEQ}|[^\\\'\\n]
STRING_LITERALS 	     "\""{S_CHAR_SEQUENCE}?"\""

/*---------PUNCTUATIONS--------------*/
PUNCTUATORS              "["|"]"|"("|")"|"{"|"}"|"->"|"&"|"*"|"+"|"-"|"/"|"%"|"!"|"?"|"<"|">"|"<="|">="|"=="|"!="|"&&"|"||"|"="|":"|";"|","

/*---------WHITESPACE , TAB , NEW LINE CHARACTER-----------*/
WS			[ \t\n]

/*--------SINGLE COMMENT LINE---------*/
SINGLE_COMMENT	[/][/].*
 
/*--------MULTI COMMENT LINE----------*/
MULTI_COMMENT [/][*]{STR2}*[*][/]
STR2		[^*]|{STR3}
STR3 		[*][^*/]

%% 
{KEYWORD}       return KEYWORD;
{IDENTIFIER}		    return IDENTIFIER;
{INT_CONSTANT}	    return INT_CONSTANT;
{CHAR_CONSTANT}    return CHAR_CONSTANT;
{STRING_LITERALS}	    return STRING_LITERALS;
{PUNCTUATORS}		    return PUNCTUATORS;
{SINGLE_COMMENT}   return SINGLE_COMMENT;
{MULTI_COMMENT}  return MULTI_COMMENT;
{WS}	
%%




