CC=gcc
CFLAGS=-I.
DEPS=table.h file.h helpers.h hash.h controller.h
OBJ=table.o file.o hash.o controller.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

prog: $(OBJ)
	gcc -Wall -ansi -pedantic -o $@ $^ $(CFLAGS)
debug: $(OBJ)
	gcc -g -o $@ $^ $(CFLAGS)
analyse: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) -pg