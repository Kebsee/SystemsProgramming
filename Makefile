# Makefile for shell assignment
# Supports building smsh1, smsh2, smsh3, and smsh4

CC = gcc
CFLAGS = -Wall -g
OBJECTS = splitline.o execute.o

# Default target
all: smsh1 smsh2 smsh3 smsh4

# Original shell (provided)
smsh1: smsh1.o $(OBJECTS)
	$(CC) $(CFLAGS) -o smsh1 smsh1.o $(OBJECTS)

# Part 1: Shell with piping
part1: smsh2

smsh2: smsh2.o $(OBJECTS)
	$(CC) $(CFLAGS) -o smsh2 smsh2.o $(OBJECTS)

# Part 2: Shell with piping and redirection
part2: smsh3

smsh3: smsh3.o $(OBJECTS)
	$(CC) $(CFLAGS) -o smsh3 smsh3.o $(OBJECTS)

# Part 3: Shell with piping, redirection, and globbing
part3: smsh4

smsh4: smsh4.o $(OBJECTS)
	$(CC) $(CFLAGS) -o smsh4 smsh4.o $(OBJECTS)

# Object file rules
smsh1.o: smsh1.c smsh.h
	$(CC) $(CFLAGS) -c smsh1.c

smsh2.o: smsh2.c smsh.h
	$(CC) $(CFLAGS) -c smsh2.c

smsh3.o: smsh3.c smsh.h
	$(CC) $(CFLAGS) -c smsh3.c

smsh4.o: smsh4.c smsh.h
	$(CC) $(CFLAGS) -c smsh4.c

splitline.o: splitline.c smsh.h
	$(CC) $(CFLAGS) -c splitline.c

execute.o: execute.c smsh.h
	$(CC) $(CFLAGS) -c execute.c

# Clean up
clean:
	rm -f *.o smsh1 smsh2 smsh3 smsh4

# Test targets
test1: smsh1
	@echo "Testing smsh1 (basic shell)..."
	@echo "Run ./smsh1 to test"

test2: smsh2
	@echo "Testing smsh2 (with piping)..."
	@echo "Run ./smsh2 and try: ls | wc"

test3: smsh3
	@echo "Testing smsh3 (with piping and redirection)..."
	@echo "Run ./smsh3 and try: ls > output.txt, cat < input.txt"

test4: smsh4
	@echo "Testing smsh4 (with piping, redirection, and globbing)..."
	@echo "Run ./smsh4 and try: ls *.c, cat *.h"

.PHONY: all part1 part2 part3 clean test1 test2 test3 test4