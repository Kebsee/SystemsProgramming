CC = gcc
CFLAGS = -Wall -pthread
SOURCES = slow_functions.c

# Build Part 1
part1: part1.c $(SOURCES)
	$(CC) $(CFLAGS) -o PART1 part1.c $(SOURCES)

# Build Part 2  
part2: part2.c $(SOURCES)
	$(CC) $(CFLAGS) -o PART2 part2.c $(SOURCES)

# Clean up
clean:
	rm -f PART1 PART2

.PHONY: clean
