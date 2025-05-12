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
using namespace std;  
#define ALIGN(offset, alignment) ((offset + (alignment - 1)) & ~(alignment - 1))                                                   

// Initialize a SymbolType with given parameters
SymbolType::SymbolType(string type, SymbolType* arrtype, int width)                                 
{
    this->type = type;
    this->width = width;
    this->arrtype = arrtype;
}

// Initialize a Symbol with name, type, array type and width
Symbol::Symbol(string name, string t, SymbolType* arrtype, int width) 
{
    this->name = name;
    // Set up the symbol type
    type = new SymbolType(t, arrtype, width);         
    // Calculate size based on type                                               
    size = computeSize(type);                                                                      
    offset = 0;                                                                                    
    val = "-";                                                                                     
    nested = NULL;                                                                                 
}

// Initialize a quad with standard parameters
quad::quad(string res, string arg1, string op, string arg2)
{
    this->op = op;
    this->arg1 = arg1;
    this->arg2 = arg2;
    this->res = res;
}

// Initialize a quad with integer first argument
quad::quad(string res, int arg1, string op, string arg2)
{   
    this->op = op;
    // Convert integer to string
    this->arg1 = convertIntToString(arg1);
    this->arg2 = arg2;
    this->res = res;    
}

// Initialize a quad with float first argument
quad::quad(string res, float arg1, string op, string arg2)
{
    this->op = op;
    // Convert float to string
    this->arg1 = convertFloatToString(arg1);
    this->arg2 = arg2;
    this->res = res;
}

// Display the three-address code for this quad
void quad::print() 
{
    int next_instr = 0;   
    // Handle different operation types
    if(op == "+" || op == "-" || op == "*" || op == "/" || 
       op == "%" || op == "|" || op == "^" || op == "&" ||
       op == ">>" || op == "<<") {
        this->print_generic_tac();
    }
    else if(op == "==" || op == "!=" || op == "<=" || op == "<" || 
            op == ">" || op == ">=") {
        this->print_if_jump_tac();
    }
    else if(op == "goto") {
        std::cout << "goto " << res;
    }
    else if(op == "=") {
        std::cout << res << " = " << arg1;
    }
    else if(op == "=&") {
        std::cout << res << " = &" << arg1;
    }
    else if(op == "=*") {
        std::cout << res << " = *" << arg1;
    }
    else if(op == "*=") {
        std::cout << "*" << res << " = " << arg1;
    }
    else if(op == "uminus") {
        std::cout << res << " = -" << arg1;
    }
    else if(op == "~") {
        std::cout << res << " = ~" << arg1;
    }
    else if(op == "!") {
        std::cout << res << " = !" << arg1;
    }
    else if(op == "=[]") {
        std::cout << res << " = " << arg1 << "[" << arg2 << "]";
    }
    else if(op == "[]=") {
        std::cout << res << "[" << arg1 << "]" << " = " << arg2;
    }
    else if(op == "return") {
        std::cout << "return " << res;
    }
    else if(op == "param") {
        std::cout << "param " << res;
    }
    else if(op == "call") {
        std::cout << res << " = " << "call " << arg1 << ", " << arg2;
    }
    else if(op == "Label") {
        std::cout << res << ": ";
    }
    else {
        std::cout << "Unknown operator: " << op;
    }      
    std::cout << std::endl;
}

// Helper method for binary operation formatting
void quad::print_generic_tac()                                                                           
{
    std::cout << res << " = " << arg1 << " " << op << " " << arg2;    
}

// Helper method for conditional jump formatting
void quad::print_if_jump_tac()                                                                               
{
    std::cout << "if " << arg1 << " " << op << " " << arg2 << " goto " << res; 
}

// Storage for generated quads
quadArray Q;   

// Reference to current symbol table                                                                                 
SymbolTable* ST;  

bool debug_on;                                                                                     
string var_type;                                                                                   
SymbolTable* globalST;                                                                                
SymbolTable* parST;                                                                                   
Symbol* currSymbolPtr;                                                                                
long long int table_count;                                                                         
string loop_name;                                                                                  
vector<Label> label_table;
string id; 

// Modify symbol with new type
Symbol* Symbol::update(SymbolType* t) 
{
    type = t; 
    // Update size according to new type                                                                                       
    this->size = computeSize(t);                                                                   
    return this;                                                                                   
}

// Create a new label with name and address
Label::Label(string _name, int _addr) : name(_name), addr(_addr) {}

// Create a new symbol table with specified name
SymbolTable::SymbolTable(string name)                                                                   
{
    this->name = name;                                                                             
    count = 0;                                                                                      
}

// Check if a symbol already exists in current scope (not parent scopes)
bool SymbolTable::checkSymbolInCurrentScope(string name) {
    for (list<Symbol>::iterator it = table.begin(); it != table.end(); it++) {
        if (it->name == name) {
            return true;  // Symbol found in current scope
        }
    }
    return false;  // Symbol not found in current scope
}

// Search for a symbol with given name
Symbol* SymbolTable::lookupIdentifier(string name)                                                
{
    // Traverse through table entries
    for(auto it = table.begin(); it != table.end(); ++it) {
        if(it->name == name) {
            return &(*it);
        }
    }

    // Check parent table if not found
    Symbol *ptr = nullptr;
    if(this->parent) ptr = this->parent->lookupIdentifier(name);
    return ptr;
}

// Add a new symbol to the table
Symbol* SymbolTable::lookupDeclarator(string name)
{
    // Check if symbol already exists in current scope
    if (checkSymbolInCurrentScope(name)) {
        cerr << "Error: Redeclaration of variable '" << name << "' in the same scope" << endl;
        // Return existing symbol instead of creating a duplicate
        for (list<Symbol>::iterator it = table.begin(); it != table.end(); it++) {
            if (it->name == name) {
                return &(*it);
            }
        }
    }
    
    // If not found, create new symbol
    Symbol *symbol = new Symbol(name);
    table.push_back(*symbol);                                                                  
    return &table.back(); 
}

// Update the lookup method to check for redeclarations
Symbol* SymbolTable::lookup(string name) {
    // If the symbol exists in current scope, throw an error for redeclaration
    if (checkSymbolInCurrentScope(name)) {
        cerr << "Error: Redeclaration of variable '" << name << "' in the same scope" << endl;
        // Return existing symbol instead of creating a duplicate
        for (list<Symbol>::iterator it = table.begin(); it != table.end(); it++) {
            if (it->name == name) {
                return &(*it);
            }
        }
    }
    
    // Original lookup code continues...
    Symbol s(name);
    table.push_back(s);
    list<Symbol>::iterator it = table.end();
    it--;
    return &(*it);
}

// Update offsets in the symbol table
void SymbolTable::update()                                                                           
{
    list<SymbolTable*> nested_tables;                                                                           
    int off = 0;
    
    // Process all symbols
    for(auto it = table.begin(); it != table.end(); ++it) {
        // Handle float alignment
        if(it->type->type == "float") {
            off = ALIGN(off, 8);  // 8-byte alignment
        }
        
        // Set offset for current symbol
        if(it == table.begin()) {
            it->offset = 0;                                                                           
            off = it->size;
        }
        else {
            it->offset = off;
            off = it->offset + it->size;                                                                
        }
        
        // Track nested tables
        if(it->nested != NULL) {
            nested_tables.push_back(it->nested);
        }
    }

    // Update nested tables recursively
    for(auto nested : nested_tables) {
        nested->update();
    }
}

// Display all quads in the array
// Display both tabular and three-address code formats
void quadArray::print()                                                                               
{
    // Print header for tabular format
    std::cout << "QUAD ARRAY REPRESENTATION:" << std::endl;
    for(int i = 0; i < 60; i++) std::cout << "**";
    std::cout << std::endl;
    
    // Print column headers
    std::cout << std::left << std::setw(8) << "Index" 
              << std::setw(12) << "op" 
              << std::setw(12) << "arg1" 
              << std::setw(12) << "arg2" 
              << std::setw(12) << "result" << std::endl;
    
    for(int i = 0; i < 50; i++) std::cout << "--";
    std::cout << std::endl;
    
    // Print each quad in tabular format
    int j = 0;
    for(auto it = Array.begin(); it != Array.end(); ++it, ++j) {
        std::cout << std::left << std::setw(8) << j 
                  << std::setw(12) << it->op 
                  << std::setw(12) << it->arg1 
                  << std::setw(12) << it->arg2 
                  << std::setw(12) << it->res << std::endl;
    }
    
    std::cout << std::endl;
    
    // Print header for three-address code
    std::cout << "THREE ADDRESS CODE : " << std::endl;                                                       
    for(int i = 0; i < 60; i++) std::cout << "**";
    std::cout << std::endl;
    
    // Print function header
    std::cout << "void main()" << std::endl;
    std::cout << "{" << std::endl;
    
    // Print variable declarations (from symbol table)
    std::set<string> printedVars;  // To avoid duplicate declarations
    
    // First print user variables
    for(auto it = globalST->table.begin(); it != globalST->table.end(); ++it) {
        if(it->name[0] != 't' && it->type->type != "func") {  // Skip temporaries and functions
            printVariable(*it);
            printedVars.insert(it->name);
        }
    }
    
    // Then identify and print temporary variables used in the quads
    for(auto it = Array.begin(); it != Array.end(); ++it) {
        // Check result
        if(it->res[0] == 't' && printedVars.find(it->res) == printedVars.end()) {
            Symbol* temp = globalST->lookupIdentifier(it->res);
            if(temp) {
                printVariable(*temp);
                printedVars.insert(it->res);
            } else {
                // If the temp isn't in the table for some reason, make an assumption
                std::cout << "    int " << it->res << ";" << std::endl;
                printedVars.insert(it->res);
            }
        }
        
        // Also check arguments for any temps we might need
        if(it->arg1[0] == 't' && printedVars.find(it->arg1) == printedVars.end()) {
            Symbol* temp = globalST->lookupIdentifier(it->arg1);
            if(temp) {
                printVariable(*temp);
                printedVars.insert(it->arg1);
            }
        }
        
        if(it->arg2[0] == 't' && printedVars.find(it->arg2) == printedVars.end()) {
            Symbol* temp = globalST->lookupIdentifier(it->arg2);
            if(temp) {
                printVariable(*temp);
                printedVars.insert(it->arg2);
            }
        }
    }
    
    std::cout << std::endl;  // Add a blank line after declarations
    
    // Print quads with labels
    j = 0;
    for(auto it = Array.begin(); it != Array.end(); ++it, ++j) {
        std::cout << "L" << j << ": ";
        printQuadFormatted(*it);
    }
    
    std::cout << "}" << std::endl;  // Close function
    
    for(int i = 0; i < 65; i++) std::cout << "**";                                                             
    std::cout << std::endl;
}


// Helper method to print a variable declaration
void quadArray::printVariable(const Symbol& symbol)
{
    std::cout << "    ";
    
    // Print the type
    if(symbol.type->type == "integer") {
        std::cout << "integer ";
    } else if(symbol.type->type == "float") {
        std::cout << "float ";
    } else if(symbol.type->type == "char") {
        std::cout << "char ";
    } else if(symbol.type->type == "void") {
        std::cout << "void ";
    } else if(symbol.type->type == "arr") {
        // Print array type
        if(symbol.type->arrtype->type == "integer") {
            std::cout << "integer";
        } else if(symbol.type->arrtype->type == "float") {
            std::cout << "float ";
        } else if(symbol.type->arrtype->type == "char") {
            std::cout << "char ";
        } else {
            std::cout << symbol.type->arrtype->type << " ";
        }
    } else if(symbol.type->type == "ptr") {
        // Print pointer type
        if(symbol.type->arrtype->type == "integer") {
            std::cout << "integer ";
        } else if(symbol.type->arrtype->type == "float") {
            std::cout << "float ";
        } else if(symbol.type->arrtype->type == "char") {
            std::cout << "char ";
        } else {
            std::cout << symbol.type->arrtype->type << " ";
        }
    } else {
        std::cout << symbol.type->type << " ";
    }
    
    // Print the name
    std::cout << symbol.name;
    
    // Handle arrays
    if(symbol.type->type == "arr") {
        std::cout << "[" << symbol.type->width << "]";
    }
    
    // Handle pointers
    if(symbol.type->type == "ptr") {
        std::cout << "*";
    }
    
    // Handle initialization if there's a value
    if(symbol.val != "-") {
        std::cout << " = " << symbol.val;
    }
    
    std::cout << ";" << std::endl;
}

// Helper method to print a quad in formatted style
void quadArray::printQuadFormatted(const quad& q)
{
    std::cout << "    ";
    
    if(q.op == "+" || q.op == "-" || q.op == "*" || q.op == "/" || 
       q.op == "%" || q.op == "|" || q.op == "^" || q.op == "&" ||
       q.op == ">>" || q.op == "<<") {
        std::cout << q.res << " = " << q.arg1 << " " << q.op << " " << q.arg2 << ";" << std::endl;
    }
    else if(q.op == "==" || q.op == "!=" || q.op == "<=" || q.op == "<" || 
            q.op == ">" || q.op == ">=") {
        std::cout << "if (" << q.arg1 << " " << q.op << " " << q.arg2 << ") goto L" << q.res << ";" << std::endl;
    }
    else if(q.op == "goto") {
        std::cout << "goto L" << q.res << ";" << std::endl;
    }
    else if(q.op == "=") {
        std::cout << q.res << " = " << q.arg1 << ";" << std::endl;
    }
    else if(q.op == "=&") {
        std::cout << q.res << " = &" << q.arg1 << ";" << std::endl;
    }
    else if(q.op == "=*") {
        std::cout << q.res << " = *" << q.arg1 << ";" << std::endl;
    }
    else if(q.op == "*=") {
        std::cout << "*" << q.res << " = " << q.arg1 << ";" << std::endl;
    }
    else if(q.op == "uminus") {
        std::cout << q.res << " = -" << q.arg1 << ";" << std::endl;
    }
    else if(q.op == "~") {
        std::cout << q.res << " = ~" << q.arg1 << ";" << std::endl;
    }
    else if(q.op == "!") {
        std::cout << q.res << " = !" << q.arg1 << ";" << std::endl;
    }
    else if(q.op == "=[]") {
        std::cout << q.res << " = " << q.arg1 << "[" << q.arg2 << "];" << std::endl;
    }
    else if(q.op == "[]=") {
        std::cout << q.res << "[" << q.arg1 << "] = " << q.arg2 << ";" << std::endl;
    }
    else if(q.op == "return") {
        std::cout << "return " << q.res << ";" << std::endl;
    }
    else if(q.op == "param") {
        std::cout << "param " << q.res << ";" << std::endl;
    }
    else if(q.op == "call") {
        std::cout << q.res << " = " << "call " << q.arg1 << ", " << q.arg2 << ";" << std::endl;
    }
    else if(q.op == "Label") {
        std::cout << q.res << ": " << std::endl;
    }
    else {
        std::cout << "Unknown operator: " << q.op << std::endl;
    }
}

// Create and add a quad with string arguments
void emit(string op, string res, string arg1, string arg2) 
{
    quad *q1 = new quad(res, arg1, op, arg2);
    Q.Array.push_back(*q1);
}

// Create and add a quad with int argument
void emit(string op, string res, int arg1, string arg2) 
{
    quad *q2 = new quad(res, arg1, op, arg2);
    Q.Array.push_back(*q2);
}

// Create and add a quad with float argument
void emit(string op, string res, float arg1, string arg2) 
{
    quad *q3 = new quad(res, arg1, op, arg2);
    Q.Array.push_back(*q3);
}

// Create a temporary variable with given type
Symbol* gentemp(SymbolType* t, string str_new) 
{                                                                                                      
    string tmp_name = "t" + convertIntToString(ST->count++);                                              
    Symbol* s = new Symbol(tmp_name);
    s->type = t;
    s->size = computeSize(t);                                                                          
    s->val = str_new;
    ST->table.push_back(*s);                                                                            
    return &ST->table.back();
}

// Locate a label by name
Label* find_label(string _name){
    for(auto it = label_table.begin(); it != label_table.end(); ++it){
        if(it->name == _name) return &(*it);
    }
    return nullptr;
}

// Update jump addresses in the quad list
void backpatch(list<int> list1, int addr)                                                               
{
    string str = convertIntToString(addr);                                                                
    
    for(auto it = list1.begin(); it != list1.end(); ++it) {
        Q.Array[*it].res = str;                                                                          
    }
}

// Create a new list with single entry
list<int> makelist(int init) 
{
    list<int> newlist(1, init);                                                                          
    return newlist;                                                                                     
}

// Combine two lists
list<int> merge(list<int> &a, list<int> &b)
{
    a.merge(b);                                                                                        
    return a;                                                                                           
}

// Convert integer to string
string convertIntToString(int a)     
{
    return to_string(a);
}

// Convert float to string
string convertFloatToString(float x)                                                                    
{
    std::ostringstream buff;
    buff << x;
    return buff.str();
}

// Convert boolean expression to integer
int convertBoolToInt(Expression* e)                                                           
{    
    int res = 0;
    if(e->type == "bool") 
    {
        e->loc = gentemp(new SymbolType("integer"));                                                        
        backpatch(e->truelist, nextinstr());
        emit("=", e->loc->name, 1);
        e->nextlist = makelist(nextinstr());
        emit("goto", "");
        backpatch(e->falselist, nextinstr());
        emit("=", e->loc->name, 0);
        list<int> temp = makelist(nextinstr());
        e->nextlist = merge(e->nextlist, temp);
        emit("goto", "");
        res = 1;
    }
    return res;
}

// Convert integer expression to boolean
Expression* convertIntToBool(Expression* e)                                                          
{
    if(e->type != "bool")                
    {
        e->falselist = makelist(nextinstr());                                                             
        emit("==", "", e->loc->name, "0");                                                                 
        e->truelist = makelist(nextinstr());                                                              
        emit("goto", "");
    }
    return e;
}

// Convert symbol to target type if needed
Symbol* convertTypeIfNeeded(Symbol* src, SymbolType* target_type) {
    if (src->type->type == target_type->type) return src; // No conversion needed
    return convertType(src, target_type->type); // Use existing convertType
}

// Determine dominant type between two types
SymbolType* getDominantType(SymbolType* t1, SymbolType* t2) {
    if (t1->type == "float" || t2->type == "float") 
        return new SymbolType("float");
    else 
        return new SymbolType("integer");
}

// Convert symbol to specified type
Symbol* convertType(Symbol* s, string rettype)                                                                
{
    Symbol* temp = gentemp(new SymbolType(rettype));    
    
    // Handle float conversions
    if(s->type->type == "float")                                                                        
    {
        if(rettype == "integer")                                                                              
        {
            emit("=", temp->name, "float2int(" + s->name + ")");
            return temp;
        }
        else if(rettype == "char")                                                                       
        {
            emit("=", temp->name, "float2char(" + s->name + ")");
            return temp;
        }
        return s;
    }
    // Handle integer conversions
    else if(s->type->type == "integer")                                                                    
    {
        if(rettype == "float")                                                                          
        {
            emit("=", temp->name, "int2float(" + s->name + ")");
            return temp;
        }
        else if(rettype == "char")                                                                        
        {
            emit("=", temp->name, "int2char(" + s->name + ")");
            return temp;
        }
        return s;
    }
    // Handle char conversions
    else if(s->type->type == "char")                                                                   
    {
        if(rettype == "integer")                                                                             
        {
            emit("=", temp->name, "char2int(" + s->name + ")");
            return temp;
        }
        if(rettype == "double")                                                                           
        {
            emit("=", temp->name, "char2double(" + s->name + ")");
            return temp;
        }
        return s;
    }
    return s;
}

// Switch current symbol table
void changeTable(SymbolTable* newtable)                                                                   
{
    ST = newtable;
} 

// Output specified number of spaces
void generateSpaces(int n)                                                                              
{
    while(n--) std::cout << " ";
}

// Get next instruction index
int nextinstr() 
{
    return Q.Array.size();                                                                              
}

// Calculate size of a symbol type
int computeSize(SymbolType* t)                                                                          
{
    if(t->type.compare("void") == 0) return _VOID_SIZE;
    else if(t->type.compare("char") == 0) return _CHAR_SIZE;
    else if(t->type.compare("integer") == 0) return _INT_SIZE;
    else if(t->type.compare("float") == 0) return _FLOAT_SIZE;
    else if(t->type.compare("ptr") == 0) return _POINT_SIZE;
    else if(t->type.compare("func") == 0) return _FUNC_SIZE;
    else if(t->type.compare("arr") == 0) return t->width * computeSize(t->arrtype);                         
    else return -1;
}

// Generate string representation of type
string printType(SymbolType* t)                                                                         
{
    if(t == NULL) return "null";
    if(t->type.compare("void") == 0)    return "void";
    else if(t->type.compare("char") == 0) return "char";
    else if(t->type.compare("integer") == 0) return "integer";
    else if(t->type.compare("float") == 0) return "float";
    else if(t->type.compare("ptr") == 0) return "ptr(" + printType(t->arrtype) + ")";                
    else if(t->type.compare("arr") == 0) 
    {
        string str = convertIntToString(t->width);                                                        
        return "arr(" + str + "," + printType(t->arrtype) + ")";
    }
    else if(t->type.compare("func") == 0) return "func";
    else if(t->type.compare("block") == 0) return "block";
    else return "NA";
}

// Display symbol table contents
void SymbolTable::print()                                                                               
{
    int next_instr = 0;
    list<SymbolTable*> nested_tables;                                                                               
    
    // Header
    for(int t1 = 0; t1 < 60; t1++) std::cout << "**";                                                        
    std::cout << std::endl;

    std::cout << "Name: " << this->name;
    generateSpaces(53 - this->name.length());
    std::cout << " Parent Table: ";                                                                    
    if((this->parent == NULL)) std::cout << "NULL" << std::endl;                                           
    else std::cout << this->parent->name << std::endl;                                                  
    
    for(int x = 0; x < 60; x++) std::cout << "__";                                                          
    std::cout << std::endl;
    
    // Column headers
    std::cout << "Name";                                                                               
    generateSpaces(36);

    std::cout << "Type";                                                                                
    generateSpaces(16);

    std::cout << "Init Value";                                                                     
    generateSpaces(7);

    std::cout << "Size";                                                                                
    generateSpaces(11);

    std::cout << "Offset";                                                                              
    generateSpaces(9);

    std::cout << "Nested" << std::endl;                                                                   
    generateSpaces(100);
    std::cout << std::endl;

    // Table content
    for(auto it = table.begin(); it != table.end(); ++it) {                               
        // Name column
        std::cout << it->name;                                                                      
        generateSpaces(40 - it->name.length());

        // Type column
        string rec_type = printType(it->type);                                                          
        std::cout << rec_type;
        generateSpaces(20 - rec_type.length());

        // Init value column
        std::cout << it->val;                                                                         
        generateSpaces(20 - it->val.length());

        // Size column
        std::cout << it->size;                                                                         
        generateSpaces(15 - to_string(it->size).length());

        // Offset column
        std::cout << it->offset;                                                                       
        generateSpaces(15 - to_string(it->offset).length());

        // Nested column
        if(it->nested == NULL) {                                                                       
            std::cout << "NULL" << std::endl;
        }
        else {
            std::cout << it->nested->name << std::endl; 
            nested_tables.push_back(it->nested);                                                                 
        }
    }
 
    // Footer
    for(int i = 0; i < 60; i++) std::cout << "--";
    std::cout << "\n\n";
    
    // Print nested tables
    for(auto nested : nested_tables) {
        nested->print();
    }
}

// Main program
int main()
{
    // Initialize data structures
    label_table.clear();
    table_count = 0;                                                                                    
    debug_on = 0;      

    // Set up global symbol table                                                                                  
    globalST = new SymbolTable("Global");                                                                    
    ST = globalST;
    parST = nullptr;
    loop_name = "";

    // Parse input
    yyparse();                                                                                         
    globalST->update();                                                                                
    std::cout << "\n";

    // Display results
    Q.print();                                                                                         
    globalST->print();                                                                                 
}