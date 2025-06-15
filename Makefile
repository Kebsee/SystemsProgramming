CC = gcc
CFLAGS = -Wall -g

all: part1 part2 part3

part1: smsh2
part2: smsh3
part3: smsh4

smsh2: smsh2.c splitline.c execute.c
	$(CC) $(CFLAGS) -o smsh2 smsh2.c splitline.c execute.c

smsh3: smsh3.c splitline.c execute.c
	$(CC) $(CFLAGS) -o smsh3 smsh3.c splitline.c execute.c

smsh4: smsh4.c splitline.c execute.c
	$(CC) $(CFLAGS) -o smsh4 smsh4.c splitline.c execute.c

clean:
	rm -f smsh2 smsh3 smsh4