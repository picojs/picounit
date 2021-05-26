#CC     = gcc
#CFLAGS = -std=c99 -Wall -pedantic -I ..

CC     = clang
CFLAGS = -std=c99 -Wall -Wextra -Weverything -Wpedantic -I ..

DEPS   = ../picounit.h

all: example1 example2

picounit.o: ../picounit.c $(DEPS)
	$(CC) -c -o picounit.o $< $(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

example1: example1.o picounit.o $(DEPS)
	$(CC) -o example1 example1.o picounit.o

example2: example2.o picounit.o $(DEPS)
	$(CC) -o example2 example2.o picounit.o

.PHONY: clean

clean:
	rm example1 example2 *.o
