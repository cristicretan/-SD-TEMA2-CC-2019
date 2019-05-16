CC = gcc
CFLAGS = -Wall -c -std=c11 -g
RM = rm -f

all:
	$(CC) tree.o helpers.o tema2.o -o tema2

build: tema2.c tree.c helpers.c
	$(CC) $(CFLAGS) tree.c helpers.c tema2.c
	make all

clean:
	$(RM) tema2 helpers.o tree.o tema2.o
