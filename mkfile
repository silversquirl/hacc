cc=gcc -std=c99
cflags=-Wall -pedantic -Werror -g

except.o: except.c except.h
	$cc $cflags -c except.c

example: example.c except.o
	$cc $cflags -o example example.c except.o
