CC     = gcc
CFLAGS = -std=c99 -Wall -I.
DEPS   = picounit.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

example: example.o picounit.o
	$(CC) -o example example.o picounit.o

all: clean example

.PHONY: clean

clean:
	rm example *.o
