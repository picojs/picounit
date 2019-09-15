CC     =gcc
CFLAGS=-I.
DEPS  = picounit.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

example: example.o picounit.o 
	$(CC) -o example example.o picounit.o
