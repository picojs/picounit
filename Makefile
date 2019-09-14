# Makefile to build example

tests: example.o picounit.o
    gcc -o tests example.o picounit.o

example.o: example.c picounit.h
    gcc -c example.c

picounit.o: picounit.c picounit.h
    gcc -c picounit.c

