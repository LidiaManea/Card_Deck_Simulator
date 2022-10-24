CC=gcc
CFLAGS=-g -Wall -Wextra -std=c99

TARGETS=tema1
build: $(TARGETS)

tema1: main.c source1b.c source2.c meh.h
	$(CC) $(CFLAGS) main.c source1b.c source2.c -o tema1

clean:
	rm -f $(TARGETS)
