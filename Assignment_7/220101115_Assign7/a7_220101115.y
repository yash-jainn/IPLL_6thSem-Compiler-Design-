%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int line_num;
extern FILE *yyin;
void yyerror(const char *s);

// Symbol table structure
typedef struct symbol {
    char *name;
    char *type;
    int scope;
    struct symbol *next;
} Symbol;

Symbol *symbol_table = NULL;
int current_scope = 0;

// Function to add symbol to symbol table
void add_symbol(char *name, char *type) {
    Symbol *s = (Symbol *)malloc(sizeof(Symbol));
    s->name = strdup(name);
    s->type = strdup(type);
    s->scope = current_scope;
    s->next = symbol_table;
    symbol_table = s;
    printf("Added symbol: %s (type: %s, scope: %d)\n", name, type, current_scope);
}

// Function to print symbol table
void print_symbol_table() {
    printf("\n--- Symbol Table ---\n");
    printf("Name\t\tType\t\tScope\n");
    printf("-------------------------------\n");
    
    Symbol *s = symbol_table;
    while (s != NULL) {
        printf("%s\t\t%s\t\t%d\n", s->name, s->type, s->scope);
        s = s->next;
    }
    printf("-------------------------------\n");
}

// Function to print reduction
void print_reduction(const char *rule, int line_num) {
    printf("Line no. %d Reduction: %s\n", line_num, rule);
}

%}

%union {
    int num;
    float fnum;
    char ch;
    char *str;
}

%token RETURN VOID FLOAT INTEGER CHAR FOR CONST WHILE BOOL IF DO ELSE
%token BEGIN_TOKEN END_TOKEN
%token <str> IDENTIFIER
%token <num> INT_CONST
%token <fnum> FLOAT_CONST
%token <ch> CHAR_CONST
%token <str> STRING_LITERAL
%token ARROW INC DEC LEFT_SHIFT RIGHT_SHIFT LESS_EQUAL GREATER_EQUAL
%token EQUAL NOT_EQUAL AND OR

%right '='
%right '?' ':'
%left OR
%left AND
%left '|'
%left '~'
%left EQUAL NOT_EQUAL
%left '<' '>' LESS_EQUAL GREATER_EQUAL
%left LEFT_SHIFT RIGHT_SHIFT
%left '+' '-'
%left '*' '/' '%'
%right '!' UNARY
%left INC DEC
%left '[' ']' '(' ')' ARROW

%nonassoc IFX
%nonassoc ELSE


%type <str> type_specifier
%start translation_unit
%%

/* Translation_unit */

translation_unit
    : translation_unit function_definition
      { print_reduction(" translation_unit -> function_definition", line_num ); }
    | translation_unit declaration
      { print_reduction(" translation_unit -> declaration", line_num ); }
    | /* empty */
      { print_reduction(" translation_unit -> empty", line_num ); }
    ;

function_definition
    : type_specifier function_declarator compound_statement
      
      { 
        print_reduction(" function_definition -> type_specifier function_declarator compound_statement", line_num ); }
    ;

function_declarator
    : IDENTIFIER '(' parameter_list_opt ')'
      { add_symbol($1, "function");
        print_reduction(" function_declarator -> identifier ( parameter_list_opt )", line_num ); }
    ;

/* declarations */

declaration
    : type_specifier init_declarator ';'
      { print_reduction(" declaration -> type_specifier init_declarator ;", line_num ); }
    ;

init_declarator
    : declarator
      { print_reduction(" init_declarator -> declarator", line_num ); }
    | declarator '=' initializer
      { print_reduction(" init_declarator -> declarator = initializer", line_num ); }
    ;

type_specifier
    : VOID
      { $$ = "void"; print_reduction(" type_specifier -> void", line_num ); }
    | CHAR
      { $$ = "char"; print_reduction(" type_specifier -> char", line_num ); }
    | INTEGER
      { $$ = "integer"; print_reduction(" type_specifier -> integer", line_num ); }
    | FLOAT
      { $$ = "float"; print_reduction(" type_specifier -> float", line_num ); }
    | BOOL
      { $$ = "bool"; print_reduction(" type_specifier -> bool", line_num ); }
    ;

declarator
    : direct_declarator
      { print_reduction(" declarator -> direct_declarator", line_num ); }
    | pointer direct_declarator
      { print_reduction(" declarator -> pointer direct_declarator", line_num ); }
    ;

direct_declarator
    : IDENTIFIER
      { 
        add_symbol($1, "identifier");
        print_reduction(" direct_declarator -> identifier", line_num); 
      }
    | IDENTIFIER '[' INT_CONST ']'
      { 
        add_symbol($1, "array");
        print_reduction(" direct_declarator -> identifier [ integer_constant ]",line_num); 
      }
    | IDENTIFIER '(' parameter_list_opt ')'
      { 
        add_symbol($1, "function");
        print_reduction(" direct_declarator -> identifier ( parameter_list_opt )",line_num); 
      }
    ;

pointer
    : '*'
      { print_reduction(" pointer -> *", line_num ); }
    ;

parameter_list
    : parameter_declaration
      { print_reduction(" parameter_list -> parameter_declaration", line_num ); }
    | parameter_list ',' parameter_declaration
      { print_reduction(" parameter_list -> parameter_list , parameter_declaration", line_num ); }
    ;

parameter_list_opt
    : parameter_list
      { print_reduction(" parameter_list_opt -> parameter_list", line_num ); }
    | /* empty */
      { print_reduction(" parameter_list_opt -> empty", line_num ); }
    ;

parameter_declaration
    : type_specifier IDENTIFIER
      { 
        add_symbol($2, $1);
        print_reduction(" parameter_declaration -> type_specifier identifier",line_num); 
      }
    | type_specifier pointer IDENTIFIER
      { 
        char type[50];
        sprintf(type, "pointer to %s", $1);
        add_symbol($3, type);
        print_reduction(" parameter_declaration -> type_specifier pointer identifier",line_num); 
      }
    ;


initializer
    : assignment_expression
      { print_reduction(" initializer -> assignment_expression", line_num ); }
    ;

/* Statements */
statement
    : compound_statement
      { print_reduction(" statement -> compound_statement", line_num ); }
    | expression_statement
      { print_reduction(" statement -> expression_statement", line_num ); }
    | selection_statement
      { print_reduction(" statement -> selection_statement", line_num ); }
    | iteration_statement
      { print_reduction(" statement -> iteration_statement", line_num ); }
    | jump_statement
      { print_reduction(" statement -> jump_statement", line_num ); }
    ;

compound_statement
    : BEGIN_TOKEN { current_scope++; } block_item_list_opt END_TOKEN
      { 
        current_scope--; 
        print_reduction(" compound_statement -> begin block_item_list_opt end",line_num); 
      }
    ;

block_item_list
    : block_item
      { print_reduction(" block_item_list -> block_item", line_num ); }
    | block_item_list block_item
      { print_reduction(" block_item_list -> block_item_list block_item", line_num ); }
    ;

block_item
    : declaration
      { print_reduction(" block_item -> declaration", line_num ); }
    | statement
      { print_reduction(" block_item -> statement", line_num ); }
    ;

block_item_list_opt
    : block_item_list
      { print_reduction(" block_item_list_opt -> block_item_list", line_num ); }
    | /* empty */
      { print_reduction(" block_item_list_opt -> empty", line_num ); }
    ;

expression_statement
    : expression_opt ';'
      { print_reduction(" expression_statement -> expression_opt ;", line_num ); }
    ;

expression_opt
    : expression
      { print_reduction(" expression_opt -> expression", line_num ); }
    | /* empty */
      { print_reduction(" expression_opt -> empty", line_num ); }
    ;

selection_statement
    : IF '(' expression ')' statement %prec IFX
      { print_reduction(" selection_statement -> if ( expression ) statement", line_num ); }
    | IF '(' expression ')' statement ELSE statement
      { print_reduction(" selection_statement -> if ( expression ) statement else statement", line_num ); }
    ;
iteration_statement
    : FOR '(' expression_opt ';' expression_opt ';' expression_opt ')' statement
      { print_reduction(" iteration_statement -> for ( expression_opt ; expression_opt ; expression_opt ) statement", line_num ); }
    ;

jump_statement
    : RETURN expression_opt ';'
      { print_reduction(" jump_statement -> return expression_opt ;", line_num ); }
    ;

/* Expression grammar (keep this at the end) */

primary_expression
    : IDENTIFIER
      { print_reduction(" primary_expression -> identifier", line_num ); }
    | INT_CONST
      { print_reduction(" primary_expression -> integer_constant", line_num ); }
    | FLOAT_CONST
      { print_reduction(" primary_expression -> floating_constant", line_num ); }
    | CHAR_CONST
      { print_reduction(" primary_expression -> character_constant", line_num ); }
    | STRING_LITERAL
      { print_reduction(" primary_expression -> string_literal", line_num ); }
    | '(' expression ')'
      { print_reduction(" primary_expression -> ( expression )", line_num ); }
    ;

postfix_expression
    : primary_expression
      { print_reduction(" postfix_expression -> primary_expression", line_num ); }
    | postfix_expression '[' expression ']'
      { print_reduction(" postfix_expression -> postfix_expression [ expression ]", line_num ); }
    | postfix_expression '(' argument_expression_list_opt ')'
      { print_reduction(" postfix_expression -> postfix_expression ( argument_expression_list_opt )", line_num ); }
    | postfix_expression ARROW IDENTIFIER
      { print_reduction(" postfix_expression -> postfix_expression -> identifier", line_num ); }
    ;

argument_expression_list
    : assignment_expression
      { print_reduction(" argument_expression_list -> assignment_expression", line_num ); }
    | argument_expression_list ',' assignment_expression
      { print_reduction(" argument_expression_list -> argument_expression_list , assignment_expression", line_num ); }
    ;

argument_expression_list_opt
    : argument_expression_list
      { print_reduction(" argument_expression_list_opt -> argument_expression_list", line_num ); }
    | /* empty */
      { print_reduction(" argument_expression_list_opt -> empty", line_num ); }
    ;

unary_expression
    : postfix_expression
      { print_reduction(" unary_expression -> postfix_expression", line_num ); }
    | unary_operator unary_expression %prec UNARY
      { print_reduction(" unary_expression -> unary_operator unary_expression", line_num ); }
    ;

unary_operator
    : '&'
      { print_reduction(" unary_operator -> &", line_num ); }
    | '*'
      { print_reduction(" unary_operator -> *", line_num ); }
    | '+'
      { print_reduction(" unary_operator -> +", line_num ); }
    | '-'
      { print_reduction(" unary_operator -> -", line_num ); }
    | '!'
      { print_reduction(" unary_operator -> !", line_num ); }
    ;

multiplicative_expression
    : unary_expression
      { print_reduction(" multiplicative_expression -> unary_expression", line_num ); }
    | multiplicative_expression '*' unary_expression
      { print_reduction(" multiplicative_expression -> multiplicative_expression * unary_expression", line_num ); }
    | multiplicative_expression '/' unary_expression
      { print_reduction(" multiplicative_expression -> multiplicative_expression / unary_expression", line_num ); }
    | multiplicative_expression '%' unary_expression
      { print_reduction(" multiplicative_expression -> multiplicative_expression % unary_expression", line_num ); }
    ;

additive_expression
    : multiplicative_expression
      { print_reduction(" additive_expression -> multiplicative_expression", line_num ); }
    | additive_expression '+' multiplicative_expression
      { print_reduction(" additive_expression -> additive_expression + multiplicative_expression", line_num ); }
    | additive_expression '-' multiplicative_expression
      { print_reduction(" additive_expression -> additive_expression - multiplicative_expression", line_num ); }
    ;

relational_expression
    : additive_expression
      { print_reduction(" relational_expression -> additive_expression", line_num ); }
    | relational_expression '<' additive_expression
      { print_reduction(" relational_expression -> relational_expression < additive_expression", line_num ); }
    | relational_expression '>' additive_expression
      { print_reduction(" relational_expression -> relational_expression > additive_expression", line_num ); }
    | relational_expression LESS_EQUAL additive_expression
      { print_reduction(" relational_expression -> relational_expression <= additive_expression", line_num ); }
    | relational_expression GREATER_EQUAL additive_expression
      { print_reduction(" relational_expression -> relational_expression >= additive_expression", line_num ); }
    ;

equality_expression
    : relational_expression
      { print_reduction(" equality_expression -> relational_expression", line_num ); }
    | equality_expression EQUAL relational_expression
      { print_reduction(" equality_expression -> equality_expression == relational_expression", line_num ); }
    | equality_expression NOT_EQUAL relational_expression
      { print_reduction(" equality_expression -> equality_expression != relational_expression", line_num ); }
    ;

logical_AND_expression
    : equality_expression
      { print_reduction(" logical_AND_expression -> equality_expression", line_num ); }
    | logical_AND_expression AND equality_expression
      { print_reduction(" logical_AND_expression -> logical_AND_expression && equality_expression", line_num ); }
    ;

logical_OR_expression
    : logical_AND_expression
      { print_reduction(" logical_OR_expression -> logical_AND_expression", line_num ); }
    | logical_OR_expression OR logical_AND_expression
      { print_reduction(" logical_OR_expression -> logical_OR_expression || logical_AND_expression", line_num ); }
    ;

conditional_expression
    : logical_OR_expression
      { print_reduction(" conditional_expression -> logical_OR_expression", line_num ); }
    | logical_OR_expression '?' expression ':' conditional_expression
      { print_reduction(" conditional_expression -> logical_OR_expression ? expression : conditional_expression", line_num ); }
    ;

assignment_expression
    : conditional_expression
      { print_reduction(" assignment_expression -> conditional_expression", line_num ); }
    | unary_expression '=' assignment_expression
      { print_reduction(" assignment_expression -> unary_expression = assignment_expression", line_num ); }
    ;

expression
    : assignment_expression
      { print_reduction(" expression -> assignment_expression", line_num ); }
    ;


%%

void yyerror(const char *s) {
    fprintf(stderr, "Error at line %d: %s\n", line_num, s);
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
            return 1;
        }
    }
    
    printf("Starting parser for microC language...\n");
    
    int result = yyparse();
    
    print_symbol_table();
    
    if (result == 0)
        printf("Parsing completed successfully.\n");
    else
        printf("Parsing failed.\n");
    
    if (argc > 1)
        fclose(yyin);
    
    return result;
}
