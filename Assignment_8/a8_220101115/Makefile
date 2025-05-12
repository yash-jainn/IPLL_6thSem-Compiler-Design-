# Makefile for a8_220101115 Implementation

# Compiler and tools
CC = gcc
YACC = bison
LEX = flex

# Compiler flags
CFLAGS = -Wall -g
LIBS = -lm

# Target executable
TARGET = a8_220101115

# Source files
LEX_FILE = a8_220101115.l
YACC_FILE = a8_220101115.y

# Object files
YACC_OUTPUT = a8_220101115.tab.c
LEX_OUTPUT = lex.yy.c

# Default rule
all: $(TARGET)

# Compile Bison file
$(YACC_OUTPUT): $(YACC_FILE)
	$(YACC) -d $(YACC_FILE)

# Compile Lex file
$(LEX_OUTPUT): $(LEX_FILE) $(YACC_OUTPUT)
	$(LEX) $(LEX_FILE)

# Link and compile
$(TARGET): $(YACC_OUTPUT) $(LEX_OUTPUT)
	$(CC) $(CFLAGS) -o $@ $(YACC_OUTPUT) $(LEX_OUTPUT) $(LIBS)

# Clean up
clean:
	rm -f $(TARGET) $(YACC_OUTPUT) $(LEX_OUTPUT) y.tab.h

# Run the a8_220101115
run: $(TARGET)
	./$(TARGET)

test: $(TARGET)
	./$(TARGET) < a8_220101115_test.tc > output.txt
	

.PHONY: all clean run