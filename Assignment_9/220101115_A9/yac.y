%{
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
%}

// Union for different types of values
%union {
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
%error-verbose
%verbose

%token WHILE DO CONST
%token CHAR ELSE FOR FLOAT IF INTEGER RETURN VOID BOOL

            
%token <char_value> IDENTIFIER                            
%token <char_value> STRING_LITERAL         

%token SQUARE_BRACKET_OPEN SQUARE_BRACKET_CLOSE
%token ROUND_BRACKET_OPEN ROUND_BRACKET_CLOSE
%token BEGIN_TOK END          
%token BITWISE_AND MUL ADD SUB EXCLAIM DIV MOD BIT_SL BIT_SR ARROW BITWISE_XOR  BITWISE_OR 
%token LTE GTE EQ NEQ AND OR LT GT
%token QUESTION COLON SEMICOLON ASSIGN 
%token COMMA THEN

%token <floatval> FLOAT_CONSTANT
%token <intval> INTEGER_CONSTANT                       
%token <char_value> CHARACTER_CONSTANT 
   

%start translation_unit
%right THEN ELSE

%type <unaryOp> unary_operator
%type <num_params> argument_expression_list argument_expression_list_opt

// Expression types
%type <expr>
    expression
    primary_expression 
    multiplicative_expression
    additive_expression
    shift_expression
    and_expression
    exclusive_or_expression
    inclusive_or_expression
    relational_expression
    equality_expression
    logical_and_expression
    logical_or_expression
    conditional_expression
    assignment_expression
    expression_statement
    condition
    and_helper
    or_helper
    if_helper

// Statement types
%type <stat>  statement
    compound_statement
    selection_statement
    iteration_statement
    jump_statement
    block_item
    block_item_list
    block_item_list_opt

%type <sym_type> pointer
%type <symp> initializer
%type <symp_list> init_declarator_list
%type <symp> direct_declarator init_declarator declarator declarator_helper
%type <A> postfix_expression
    unary_expression

// Markers for backpatching
%type <instr_number> M
%type <stat> N

%%

M:  
    {
        // Store next instruction index for backpatching
        $$ = nextinstr();
    }   
    ;

N: 
    {
        // Create a guard against fall-through for backpatching
        $$ = new Statement();
        $$->nextlist = makelist(nextinstr());
        emit("goto", "");
    }
    ;

// Switch to appropriate symbol table
changetable:  
    {    
        parST = ST;
        // Create new table if needed or use existing nested table
        if (currSymbolPtr->nested == NULL) {
            changeTable(new SymbolTable(""));    
        } else {
            changeTable(currSymbolPtr->nested);                        
            emit("Label", ST->name);
        }
    }
    ;

primary_expression: IDENTIFIER
    {
        // Generate expression with symbol table entry
        $$ = new Expression();
        $$->loc = ST->lookupIdentifier(id);
    }
    | INTEGER_CONSTANT
    { 
        // Handle integer constant
        $$ = new Expression();    
        string converted_value = convertIntToString($1);
        $$->loc = gentemp(new SymbolType("integer"), converted_value);
        emit("=", $$->loc->name, converted_value);
    }
    | CHARACTER_CONSTANT                         
    {
        // Handle character constant
        $$ = new Expression();
        $$->loc = gentemp(new SymbolType("char"), $1);
        emit("=", $$->loc->name, string($1));
    }
    | FLOAT_CONSTANT {
        // Handle float constant
        $$ = new Expression();
        $$->loc = gentemp(new SymbolType("float"), convertFloatToString($1));
        emit("=", $$->loc->name, convertFloatToString($1));
    }
    | STRING_LITERAL                                
    {
        // Handle string literal
        $$ = new Expression();
        $$->loc = gentemp(new SymbolType("ptr"), $1);
        $$->loc->type->arrtype = new SymbolType("char");
        emit("=", $$->loc->name, $1);
    }
    | ROUND_BRACKET_OPEN expression ROUND_BRACKET_CLOSE
    {
        // Handle parenthesized expression
        $$ = $2;

        // Store boolean expression for later use
        if ($2->type == "bool") {
            temp_rel = $2;
        }
    }
    ;

postfix_expression: primary_expression                      
    {
        // Create array from primary expression
        $$ = new Array();   

        if ($1->type != "bool") {
            // Normal expression
            $$->Array = $1->loc;    
            $$->type = $1->loc->type;    
            $$->loc = $$->Array;
        } else {
            // Boolean expression needs special handling
            $$->atype = "bool_pass";
        }
    }
    | postfix_expression SQUARE_BRACKET_OPEN expression SQUARE_BRACKET_CLOSE 
    {     
        // Array indexing
        $$ = new Array();
        $$->type = $1->type->arrtype;
        $$->Array = $1->Array;
        $$->loc = gentemp(new SymbolType("integer"));
        $$->atype = "arr";
        
        // Calculate offset
        int element_size = computeSize($$->type);    
        string size_str = convertIntToString(element_size);
        emit("*", $$->loc->name, $3->loc->name, size_str);
    }
    | postfix_expression ROUND_BRACKET_OPEN argument_expression_list_opt ROUND_BRACKET_CLOSE       
    {
        // Function call
        $$ = new Array();    
        $$->Array = gentemp($1->type);
        string param_count = convertIntToString($3);
        emit("call", $$->Array->name, $1->Array->name, param_count);
    }
    | postfix_expression ARROW IDENTIFIER
    {
        // Pointer member access
        $$ = new Array();
        $$->Array = $1->Array;
        $$->loc = gentemp($1->type->arrtype);
        emit("->", $$->loc->name, $$->Array->name, $3);
    }
    ;

argument_expression_list_opt: argument_expression_list 
    { 
        $$ = $1;
    }
    |  
    { 
        $$ = 0;
    } 
    ;

argument_expression_list: assignment_expression    
    {
        // First argument in list
        $$ = 1;
        emit("param", $1->loc->name);    
    }
    | argument_expression_list COMMA assignment_expression     
    {
        // Additional argument in list
        $$ = $1 + 1;
        emit("param", $3->loc->name);
    }
    ;

unary_expression: postfix_expression { $$ = $1; }                       
    | unary_operator unary_expression                       
    {
        $$ = new Array();
        
        // Handle various unary operators
        switch ($1) {      
            case '&': // Address operator
                $$->Array = gentemp(new SymbolType("ptr"));
                $$->Array->type->arrtype = $2->Array->type; 
                emit("=&", $$->Array->name, $2->Array->name);
                break;
                
            case '*': // Dereference operator
                $$->atype = "ptr";
                $$->Array = $2->Array;
                break;
                
            case '+': // Unary plus - no operation needed
                $$ = $2;
                break;
                
            case '-': // Unary minus
                $$->Array = gentemp(new SymbolType($2->Array->type->type));
                emit("uminus", $$->Array->name, $2->Array->name);
                break;
                
            case '~': // Bitwise NOT
                $$->Array = gentemp(new SymbolType($2->Array->type->type));
                emit("~", $$->Array->name, $2->Array->name);
                break;
                
            case '!': // Logical NOT
                if ($2->atype == "bool_pass") {
                    // Flip truelist and falselist for boolean expression
                    list<int> temp_list = temp_rel->truelist;
                    temp_rel->truelist = temp_rel->falselist;
                    temp_rel->falselist = temp_list;
                    $$->atype = "bool_pass";
                } else {
                    // Standard logical NOT
                    $$->Array = gentemp(new SymbolType($2->Array->type->type));
                    emit("!", $$->Array->name, $2->Array->name);
                }
                break;
        }
    };

// Unary operator handlers
unary_operator: BITWISE_AND     
    { $$ = '&'; }       
    | MUL          
    { $$ = '*'; }
    | ADD          
    { $$ = '+'; }
    | SUB          
    { $$ = '-'; }
    | EXCLAIM  
    { $$ = '!'; }
    ;

multiplicative_expression: unary_expression  
    {
        // Process array and pointer expressions
        $$ = new Expression();
        if ($1->atype == "arr") {
            // Handle array dereference
            $$->loc = gentemp($1->Array->type->arrtype);    
            emit("=[]", $$->loc->name, $1->Array->name, $1->loc->name);
        } else if ($1->atype == "ptr") { 
            // Handle pointer dereference
            Symbol* temp_var = gentemp($1->Array->type->arrtype);
            emit("=*", temp_var->name, $1->Array->name);
            $$->loc = temp_var;
        } else if ($1->atype == "bool_pass") {
            // Handle boolean expression
            $$ = temp_rel;
        } else {
            // Handle simple variable
            $$->loc = $1->Array;
        }
    }
    | multiplicative_expression MUL unary_expression           
    { 
        // Multiplication operation
        $$ = new Expression(); 
        Symbol* right_operand; 

        // Prepare right operand
        if ($3->atype == "arr") {
            right_operand = gentemp($3->Array->type->arrtype);    
            emit("=[]", right_operand->name, $3->Array->name, $3->loc->name);
        } else if ($3->atype == "ptr") {
            right_operand = gentemp($3->Array->type->arrtype);
            emit("=*", right_operand->name, $3->Array->name);
        } else {
            right_operand = $3->Array;
        }
        
        // Perform multiplication
        $$->loc = gentemp(new SymbolType($1->loc->type->type));
        emit("*", $$->loc->name, $1->loc->name, right_operand->name);
    }
    | multiplicative_expression DIV unary_expression      
    {       
        // Division operation
        $$ = new Expression(); 
        Symbol* right_operand;  

        // Prepare right operand
        if ($3->atype == "arr") {
            right_operand = gentemp($3->Array->type->arrtype);    
            emit("=[]", right_operand->name, $3->Array->name, $3->loc->name);
        } else if ($3->atype == "ptr") {
            right_operand = gentemp($3->Array->type->arrtype);
            emit("=*", right_operand->name, $3->Array->name);
        } else {
            right_operand = $3->Array;
        }
        
        // Perform division
        $$->loc = gentemp(new SymbolType($1->loc->type->type));
        emit("/", $$->loc->name, $1->loc->name, right_operand->name);
    }
    | multiplicative_expression MOD unary_expression
    {
        // Modulo operation
        $$ = new Expression(); 
        Symbol* right_operand;
        
        // Prepare right operand
        if ($3->atype == "arr") {
            right_operand = gentemp($3->Array->type->arrtype);    
            emit("=[]", right_operand->name, $3->Array->name, $3->loc->name);
        } else if ($3->atype == "ptr") {
            right_operand = gentemp($3->Array->type->arrtype);
            emit("=*", right_operand->name, $3->Array->name);
        } else {
            right_operand = $3->Array;
        }
        
        // Perform modulo
        $$->loc = gentemp(new SymbolType($1->loc->type->type));
        emit("%", $$->loc->name, $1->loc->name, right_operand->name);  
    }
    ;

additive_expression: multiplicative_expression   { $$ = $1; } 
    | additive_expression ADD multiplicative_expression {
        // Addition with type conversion
        Symbol* left_operand = convertTypeIfNeeded($1->loc, $3->loc->type);
        Symbol* right_operand = convertTypeIfNeeded($3->loc, $1->loc->type);
        $$ = new Expression();
        $$->loc = gentemp(getDominantType(left_operand->type, right_operand->type));
        emit("+", $$->loc->name, left_operand->name, right_operand->name);
    }
    | additive_expression SUB multiplicative_expression {
        // Subtraction with type conversion
        Symbol* left_operand = convertTypeIfNeeded($1->loc, $3->loc->type);
        Symbol* right_operand = convertTypeIfNeeded($3->loc, $1->loc->type);
        $$ = new Expression();
        $$->loc = gentemp(getDominantType(left_operand->type, right_operand->type));
        emit("-", $$->loc->name, left_operand->name, right_operand->name);
    }
    ;

shift_expression: additive_expression { $$ = $1; }
    | shift_expression BIT_SL additive_expression {
        $$ = new Expression();
        $$->loc = gentemp(new SymbolType("integer"));
        emit("<<", $$->loc->name, $1->loc->name, $3->loc->name);
    }
    | shift_expression BIT_SR additive_expression {
        $$ = new Expression();
        $$->loc = gentemp(new SymbolType("integer"));
        emit(">>", $$->loc->name, $1->loc->name, $3->loc->name);
    }
    ;

and_expression: shift_expression { $$ = $1; }
    | and_expression BITWISE_AND shift_expression {
        $$ = new Expression();
        $$->loc = gentemp(new SymbolType("integer"));
        emit("&", $$->loc->name, $1->loc->name, $3->loc->name);
    }
    ;

exclusive_or_expression: and_expression { $$ = $1; }
    | exclusive_or_expression BITWISE_XOR and_expression {
        $$ = new Expression();
        $$->loc = gentemp(new SymbolType("integer"));
        emit("^", $$->loc->name, $1->loc->name, $3->loc->name);
    }
    ;

inclusive_or_expression: exclusive_or_expression { $$ = $1; }
    | inclusive_or_expression BITWISE_OR exclusive_or_expression {
        $$ = new Expression();
        $$->loc = gentemp(new SymbolType("integer"));
        emit("|", $$->loc->name, $1->loc->name, $3->loc->name);
    }
    ;

relational_expression: inclusive_or_expression   { $$ = $1; }
    | relational_expression LT inclusive_or_expression
    {
        // Less than comparison
        $$ = new Expression();
        $$->type = "bool";
        $$->truelist = makelist(nextinstr());
        $$->falselist = makelist(nextinstr() + 1);
        emit("<", "", $1->loc->name, $3->loc->name);
        emit("goto", "");    
    }
    | relational_expression GT inclusive_or_expression         
    {   
        // Greater than comparison
        $$ = new Expression();        
        $$->type = "bool";
        $$->truelist = makelist(nextinstr());
        $$->falselist = makelist(nextinstr() + 1);
        emit(">", "", $1->loc->name, $3->loc->name);
        emit("goto", "");
    }
    | relational_expression LTE inclusive_or_expression           
    {   
        // Less than or equal comparison
        $$ = new Expression();        
        $$->type = "bool";
        $$->truelist = makelist(nextinstr());
        $$->falselist = makelist(nextinstr() + 1);
        emit("<=", "", $1->loc->name, $3->loc->name);
        emit("goto", "");
    }
    | relational_expression GTE inclusive_or_expression

    
                
    {  
        // Greater than or equal comparison
        $$ = new Expression();    
        $$->type = "bool";
        $$->truelist = makelist(nextinstr());
        $$->falselist = makelist(nextinstr() + 1);
        emit(">=", "", $1->loc->name, $3->loc->name);
        emit("goto", "");
    }
    ;

equality_expression: relational_expression  { $$ = $1; }
    | equality_expression EQ M relational_expression 
    {
        // Equal to comparison
        // Convert operands to int if they're bool
        if (convertBoolToInt($1) == 1) {
            backpatch($1->nextlist, $3);
        }
        if (convertBoolToInt($4) == 1) {
            backpatch($4->nextlist, nextinstr());
        }
        
        $$ = new Expression();
        $$->type = "bool";
        $$->truelist = makelist(nextinstr());
        $$->falselist = makelist(nextinstr() + 1); 
        emit("==", "", $1->loc->name, $4->loc->name);
        emit("goto", "");                
    }
    | equality_expression NEQ M relational_expression
    {       
        // Not equal comparison
        if (convertBoolToInt($1) == 1) {
            backpatch($1->nextlist, $3);
        }
        if (convertBoolToInt($4) == 1) {
            backpatch($4->nextlist, nextinstr());
        }
        
        $$ = new Expression();
        $$->type = "bool";
        $$->truelist = makelist(nextinstr());
        $$->falselist = makelist(nextinstr() + 1); 
        emit("!=", "", $1->loc->name, $4->loc->name);
        emit("goto", "");
    }
    ;

// Helper for logical AND
and_helper: logical_and_expression AND
    {
        convertIntToBool($1);
        $$ = $1;
    }


logical_and_expression: equality_expression  { $$ = $1; }
    | and_helper M equality_expression
    { 
        // Logical AND operation
        convertIntToBool($3);
        $$ = new Expression();
        $$->type = "bool";
        backpatch($1->truelist, $2);
        $$->truelist = $3->truelist;
        $$->falselist = merge($1->falselist, $3->falselist);
    }
    ;

// Helper for logical OR
or_helper: logical_or_expression OR
    {
        convertIntToBool($1);
        $$ = $1;
    }

logical_or_expression: logical_and_expression   { $$ = $1; }
    | or_helper M logical_and_expression
    { 
        // Logical OR operation
        convertIntToBool($3);            
        $$ = new Expression();            
        $$->type = "bool";
        backpatch($1->falselist, $2);
        $$->truelist = merge($1->truelist, $3->truelist);
        $$->falselist = $3->falselist;
    }
    ;

// Helper for conditional expressions
condition: logical_or_expression QUESTION 
    {
        convertIntToBool($1);
        $$ = $1;
    }

conditional_expression: logical_or_expression {$$ = $1;}
    | condition M expression N COLON M conditional_expression 
    {
        // Ternary conditional operator
        $$->loc = gentemp($3->loc->type);
        $$->loc->update($3->loc->type);
        
        // Handle the conditional branching
        emit("=", $$->loc->name, $7->loc->name);
        list<int> temp_list = makelist(nextinstr());
        emit("goto", "");
        
        backpatch($4->nextlist, nextinstr());
        emit("=", $$->loc->name, $3->loc->name);
        
        list<int> merge_list = makelist(nextinstr());
        temp_list = merge(temp_list, merge_list);                        
        emit("goto", "");
        
        // Patch all jumps
        backpatch($1->truelist, $2);
        backpatch($1->falselist, $6);
        backpatch(temp_list, nextinstr());
    }
    ;

assignment_expression: conditional_expression {$$ = $1;}
    | unary_expression ASSIGN assignment_expression 
     {
        // Handle different assignment types
        if ($1->atype == "arr") {
            // Array element assignment
            $3->loc = convertType($3->loc, $1->type->type);
            emit("[]=", $1->Array->name, $1->loc->name, $3->loc->name);        
        } else if ($1->atype == "ptr") {
            // Pointer assignment
            emit("*=", $1->Array->name, $3->loc->name);    
        } else {
            // Direct variable assignment
            $3->loc = convertType($3->loc, $1->Array->type->type);
            emit("=", $1->Array->name, $3->loc->name);
        }
        $$ = $3;
    }
    ;

expression: assignment_expression {  $$ = $1;  }
    ;

declaration: type_specifier init_declarator_list SEMICOLON { }
    ;

init_declarator_list: init_declarator
    {
        $$ = new vector<Symbol*>();
        $$->push_back($1);
    }
    | init_declarator_list COMMA init_declarator
    {
        $$ = $1;
        $$->push_back($3);
    }
    ;

init_declarator: declarator {$$ = $1;}
    | declarator ASSIGN initializer 
    {
        // Initialize with value if available
        if ($3->val != "") $1->val = $3->val;
        emit("=", $1->name, $3->name);    
    }
    ;

// Type specification
type_specifier: VOID   { var_type = "void"; }
    | CHAR   { var_type = "char"; }
    | INTEGER   { var_type = "integer"; }
    | FLOAT { var_type = "float"; }
    | BOOL { var_type = "bool"; } 
    ;

declarator: pointer direct_declarator 
    {
        // Handle pointer type
        SymbolType *base_type = $1;
        while (base_type->arrtype != NULL) base_type = base_type->arrtype;
        base_type->arrtype = $2->type;
        $$ = $2->update($1);
    }
    | direct_declarator {   }
    ;

// Helper for function declarations
declarator_helper: IDENTIFIER ROUND_BRACKET_OPEN
{   
    Symbol* symbol = ST->lookupIdentifier(id);
    if (symbol == nullptr) {
        symbol = ST->lookupDeclarator(id);
    }
    $$ = symbol->update(new SymbolType(var_type));
    currSymbolPtr = $$; 
}

direct_declarator: IDENTIFIER
    {
        // Simple variable declarator
        Symbol* symbol = ST->lookupDeclarator(id);
        $$ = symbol->update(new SymbolType(var_type));
        currSymbolPtr = $$;    
    }
    | IDENTIFIER SQUARE_BRACKET_OPEN INTEGER_CONSTANT SQUARE_BRACKET_CLOSE 
    {
        // Array declarator
        Symbol *symbol = ST->lookupDeclarator(id);
        $$ = symbol->update(new SymbolType(var_type));
        currSymbolPtr = $$;
        
        // Create array type with size
        SymbolType* array_type = new SymbolType("arr", symbol->type, $3);
        $$ = symbol->update(array_type);
    }
    | declarator_helper changetable parameter_list_opt ROUND_BRACKET_CLOSE 
    {
        // Function declarator
        ST->name = $1->name;
        
        // Set up return value
        if ($1->type->type != "void") {
            Symbol *ret_symbol = ST->lookupIdentifier("return");
            if (ret_symbol == nullptr) {
                ret_symbol = ST->lookupDeclarator("return");
            }
            ret_symbol->update($1->type);        
        }
        
        $1->nested = ST;
        ST->parent = globalST;
        changeTable(globalST);                
        currSymbolPtr = $$;
    }
    ;

pointer: MUL
    { 
        $$ = new SymbolType("ptr");
    }
    ;

parameter_list_opt: parameter_list { }
    |   
    ;

parameter_list: parameter_declaration   {  }
    | parameter_list COMMA parameter_declaration    {  }
    ;

parameter_declaration: type_specifier declarator   {  }
    ;

initializer: assignment_expression   { $$ = $1->loc; }
    ;

statement: compound_statement   { $$ = $1; }
    | expression_statement   
    { 
        $$ = new Statement();
        $$->nextlist = $1->nextlist; 
    }
    | selection_statement   { $$ = $1; }
    | iteration_statement   { $$ = $1; }
    | jump_statement   { $$ = $1; }
    ;

compound_statement: BEGIN_TOK block_item_list_opt END  
    { 
        $$ = $2; 
    }
    ;

block_item_list_opt:   { $$ = new Statement(); }
    | block_item_list   { $$ = $1; }
    ;

block_item_list: block_item   { $$ = $1; }
    | block_item_list M block_item    
    { 
        $$ = $3;
        backpatch($1->nextlist, $2);
    }
    ;

block_item: declaration   { $$ = new Statement(); }
    | statement   { $$ = $1; }
    ;

expression_statement: expression SEMICOLON {$$ = $1;}
    | SEMICOLON {$$ = new Expression();}
    ;

// Helper for if statements
if_helper: IF ROUND_BRACKET_OPEN expression
    {
        convertIntToBool($3);
        $$ = $3;   
    }

selection_statement: if_helper ROUND_BRACKET_CLOSE M statement %prec THEN
    {
        // Simple if statement
        $$ = new Statement();
        backpatch($1->truelist, $3);
        $$->nextlist = merge($1->falselist, $4->nextlist);
    }
    | if_helper ROUND_BRACKET_CLOSE M statement ELSE M statement
    {   
        // If-else statement
        $$ = new Statement();
        backpatch($1->truelist, $3);
        backpatch($1->falselist, $6);
        
        // Merge nextlists from both branches
        list<int> merged_nextlist = $4->nextlist;
        $$->nextlist = merge($7->nextlist, merged_nextlist);
    }
    ;

iteration_statement:  FOR ROUND_BRACKET_OPEN expression_statement M expression_statement M expression N ROUND_BRACKET_CLOSE M statement
    {
        // For loop
        $$ = new Statement();
        
        // Handle conditional expression
        convertIntToBool($5);
        
        // Backpatching for loop structure
        backpatch($5->truelist, $10);    // If condition true, execute body
        backpatch($8->nextlist, $4);     // After increment, check condition again
        backpatch($11->nextlist, $6);    // After body, do increment
        
        // Jump back to condition check
        string jump_target = convertIntToString($6);
        emit("goto", jump_target);
        
        // Exit loop if condition is false
        $$->nextlist = $5->falselist;
    }
    ;

jump_statement:  RETURN expression SEMICOLON               
    {
        $$ = new Statement();    
        emit("return", $2->loc->name);
    }
    | RETURN SEMICOLON 
    {
        $$ = new Statement();    
        emit("return", "");                         
    }
    ;

translation_unit: external_declaration { }
    | translation_unit external_declaration { } 
    ;

external_declaration: function_definition {  }
    | declaration   {  }
    ;
                          
function_definition: type_specifier declarator changetable BEGIN_TOK block_item_list_opt END  
    {
        // Complete function definition
        ST->parent = globalST;
        table_count = 0;
        label_table.clear();
        changeTable(globalST);
    }
    ;

%%

void yyerror(string s) {
    cout << s << endl;
}