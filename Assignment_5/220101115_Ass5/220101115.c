#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define KEYWORD 1
#define IDENTIFIER 2 /* Can be digit, or non-digit */
#define CHAR_CONSTANT 3
#define INT_CONSTANT 4 /* Signed integer */
#define STRING_LITERALS 5
#define PUNCTUATORS 6 /* All the braces and special symbols(except escape sequence) are qualified as punctuators */
#define SINGLE_COMMENT 7
#define MULTI_COMMENT 8

extern int yylex();
extern char *yytext;
extern FILE *yyin;

// Structure for a symbol table entry
typedef struct Symbol
{
	char name[100];		 // Name of the symbol (e.g., identifier or literal)
	char type[20];		 // Type (e.g., int, string, function, etc.)
	char value[100];	 // Value (e.g., 10 for an integer, or the string itself)
	struct Symbol *next; // Pointer to the next symbol (for linked list)
} Symbol;

Symbol *symbolTable = NULL; // Head of the symbol table

// Function to add a symbol to the symbol table
void addSymbol(char *name, char *type, char *value)
{
	Symbol *newSymbol = (Symbol *)malloc(sizeof(Symbol));
	strcpy(newSymbol->name, name);
	strcpy(newSymbol->type, type);
	strcpy(newSymbol->value, value);
	newSymbol->next = symbolTable;
	symbolTable = newSymbol;
}

// Function to check if a symbol is already in the table
int symbolExists(char *name)
{
	Symbol *current = symbolTable;
	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
		{
			return 1; // Symbol found
		}
		current = current->next;
	}
	return 0; // Symbol not found
}

// Function to print the symbol table to a file
void printSymbolTable(FILE *file)
{
	Symbol *current = symbolTable;
	while (current != NULL)
	{
		printf("%s %s %s\n", current->name, current->type, current->value);
		// cout<< current->name << " " << current->type << " " << current->value << endl;x
		// Avoid printing integer constants if they aren't needed in the table
		if (strcmp(current->type, "Integer") == 0)
		{
			// Skip integer constants (or handle them differently if needed)
			current = current->next;
			continue;
		}

		// Print function type without a value
		if (strcmp(current->type, "Identifier") == 0)
		{
			fprintf(file, "Name: %s, Type: %s\n", current->name, current->type);
		}
		else
		{
			fprintf(file, "Name: %s, Type: %s, Value: %s\n", current->name, current->type, current->value);
		}
		current = current->next;
	}
}

int main()
{
	FILE *myfile = fopen("220101115.nc", "r");
	FILE *out = fopen("out.txt", "w");
	FILE *symbolFile = fopen("symbol_table.txt", "w"); // To store symbol table

	if (!myfile)
	{
		fprintf(out, "Can't open 220101115.nc file! Check file name\n");
		return -1;
	}

	yyin = myfile;

	int token;
	while (token = yylex())
	{
		switch (token)
		{
		case KEYWORD:
		{
			fprintf(out, "<KEYWORD, %d, %s>\n", token, yytext);
			break;
		}
		case IDENTIFIER:
		{
			if (!symbolExists(yytext))
			{
				addSymbol(yytext, "Identifier", ""); // No value for identifiers
			}
			fprintf(out, "<IDENTIFIER, %d, %s>\n", token, yytext);
			break;
		}
		case INT_CONSTANT:
		{
			if (!symbolExists(yytext))
			{
				addSymbol(yytext, "Integer Constant", ""); // No value for identifiers
			}
			fprintf(out, "<INTEGER CONST, %d, %s>\n", token, yytext);
			break;
		}
		case CHAR_CONSTANT:
		{
			int p = strlen(yytext);
			char pp[p - 2]; // Remove the surrounding quotes
			for (int i = 1; i < p - 1; i++)
			{
				pp[i - 1] = yytext[i];
			}
			pp[p - 2] = '\0';

			// Add char constant to the symbol table
			if (!symbolExists(pp))
			{
				addSymbol(pp, "Char Constant", pp);
			}

			fprintf(out, "<CHAR CONST, %d, %s>\n", token, pp);
			break;
		}
		case STRING_LITERALS:
		{
			int p = strlen(yytext);
			char pp[p - 2];
			for (int i = 1; i < p - 1; i++)
			{
				pp[i - 1] = yytext[i];
			}
			pp[p - 2] = '\0';
			fprintf(out, "<STRING, %d, %s>\n", token, pp);
			break;
		}
		case PUNCTUATORS:
		{
			fprintf(out, "<PUNCTUATOR, %d, %s>\n", token, yytext);
			break;
		}
		case SINGLE_COMMENT:
		{
			fprintf(out, "<SINGLE LINE COMMENT, %d, %s>\n", token, yytext);
			break;
		}
		case MULTI_COMMENT:
		{
			fprintf(out, "<MULTILINE COMMENT, %d, %s>\n", token, yytext);
			break;
		}
		}
	}

	// Print the symbol table to a file
	printSymbolTable(symbolFile);

	fclose(symbolFile); // Close the symbol table file
	fclose(out);
	fclose(myfile);
}
int yywrap()
{
	return 1;
}
