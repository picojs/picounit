CC     = gcc
CFLAGS = -std=c99 -Wall -I ..
DEPS   = ../picounit.h

all: ex1 ex2

picounit.o: ../picounit.c $(DEPS)
	$(CC) -c -o picounit.o $< $(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ex1: ex1.o picounit.o $(DEPS)
	$(CC) -o ex1 ex1.o picounit.o

ex2: ex2.o picounit.o $(DEPS)
	$(CC) -o ex2 ex1.o picounit.o

.PHONY: clean

clean:
	rm ex1 ex2 *.o
