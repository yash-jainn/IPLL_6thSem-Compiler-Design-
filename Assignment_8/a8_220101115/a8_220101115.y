%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int yylex(void);
void yyerror(const char *s);

// Conversion functions
int binary_to_decimal(const char *binary);
char* binary_to_hex(const char *binary);
char* hex_to_binary(const char *hex);
int hex_to_decimal(const char *hex);
int dividee(double a,double b);
%}

%union {
    int ival;
    char *sval;
    double dval;
}

%token <sval> NUMBER
%token EXPR BINTODEC BINTOHEX HEXTOBIN HEXTODEC
%token PLUS MINUS MULTIPLY DIVIDE POWER
%token LPAREN RPAREN
%token NEWLINE

%type <dval> expression


%left PLUS MINUS
%left MULTIPLY DIVIDE
%right POWER

%%
multiline:
    | multiline program
;


program:
    EXPR LPAREN expression RPAREN   { printf("%.0f\n", $3); }
    | BINTODEC LPAREN NUMBER RPAREN { 
        int result = binary_to_decimal($3);
        printf("%d\n", result);
        free($3);
        
    }
    | BINTOHEX LPAREN NUMBER RPAREN {
        char *result = binary_to_hex($3);
        printf("%s\n", result);
        free($3);
        free(result);
    }
    | HEXTOBIN LPAREN NUMBER RPAREN {
        char *result = hex_to_binary($3);
        printf("%s\n", result);
        free($3);
        free(result);
    }
    | HEXTODEC LPAREN NUMBER RPAREN {
        int result = hex_to_decimal($3);
        printf("%d\n", result);
        free($3);
        
    }
    ;

expression:
    NUMBER                      { $$ = atoi($1); }
    | expression PLUS expression    { $$ = $1 + $3; }
    | expression MINUS expression   { $$ = $1 - $3; }
    | expression MULTIPLY expression { $$ = $1 * $3; }
    | expression DIVIDE expression  { 
        if ($3 == 0) {
            yyerror("Division by zero");
            $$ = 0;
        } else {
            $$ = dividee($1,$3);
        }
    }
    | expression POWER expression   { $$ = pow($1, $3); }
    | LPAREN expression RPAREN      { $$ = $2; }
    ;



%%

int dividee(double a, double b){
    int x = (int) a,y = (int) b;
    return (x/y);
}

// Binary to Decimal conversion
int binary_to_decimal(const char *binary) {
    int decimal = 0;
    int power = 0;
    
    // Start from the rightmost digit
    for (int i = strlen(binary) - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            decimal += (1 << power);
        }
        power++;
    }
    
    return decimal;
}

// Binary to Hexadecimal conversion
char* binary_to_hex(const char *binary) {
    // Pad binary to multiple of 4
    int len = strlen(binary);
    int padded_len = ((len + 3) / 4) * 4;
    char *padded_binary = (char*)malloc((padded_len + 1) * sizeof(char));
    memset(padded_binary, '0', padded_len);
    padded_binary[padded_len] = '\0';
    strcpy(padded_binary + (padded_len - len), binary);

    // Convert to hex
    char *hex = (char*)malloc(((padded_len / 4) + 1) * sizeof(char));
    hex[padded_len / 4] = '\0';
    
    for (int i = 0; i < padded_len; i += 4) {
        int decimal = 0;
        for (int j = 0; j < 4; j++) {
            decimal = decimal * 2 + (padded_binary[i+j] - '0');
        }
        
        // Convert decimal to hex digit
        if (decimal < 10) {
            hex[i/4] = decimal + '0';
        } else {
            hex[i/4] = decimal - 10 + 'A';
        }
    }
    
    free(padded_binary);
    return hex;
}

// Hexadecimal to Binary conversion
char* hex_to_binary(const char *hex) {
    static const char* hex_to_bin[] = {
        "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
        "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"
    };
    
    int len = strlen(hex);
    char *binary = (char*)malloc((len * 4 + 1) * sizeof(char));
    binary[len * 4] = '\0';
    
    for (int i = 0; i < len; i++) {
        int decimal;
        if (hex[i] >= '0' && hex[i] <= '9') {
            decimal = hex[i] - '0';
        } else if (hex[i] >= 'A' && hex[i] <= 'F') {
            decimal = hex[i] - 'A' + 10;
        } else if (hex[i] >= 'a' && hex[i] <= 'f') {
            decimal = hex[i] - 'a' + 10;
        } else {
            yyerror("Invalid hexadecimal character");
            free(binary);
            return NULL;
        }
        
        strcpy(binary + (i * 4), hex_to_bin[decimal]);
    }
    
    return binary;
}

// Hexadecimal to Decimal conversion
int hex_to_decimal(const char *hex) {
    int decimal = 0;
    int power = 0;
    
    // Start from the rightmost digit
    for (int i = strlen(hex) - 1; i >= 0; i--) {
        int digit;
        if (hex[i] >= '0' && hex[i] <= '9') {
            digit = hex[i] - '0';
        } else if (hex[i] >= 'A' && hex[i] <= 'F') {
            digit = hex[i] - 'A' + 10;
        } else if (hex[i] >= 'a' && hex[i] <= 'f') {
            digit = hex[i] - 'a' + 10;
        } else {
            yyerror("Invalid hexadecimal character");
            return 0;
        }
        
        decimal += digit * (1 << (4 * power));
        power++;
    }
    
    return decimal;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    yyparse();
    return 0;
}