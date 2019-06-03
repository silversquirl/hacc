cc=gcc -std=c99
cflags=-Wall -pedantic -Werror -g

except.o: except.c except.h
	$cc $cflags -c except.c

examples:V: examples/except examples/iter

examples/except: examples/except.c except.o
	$cc $cflags -I. -o examples/except examples/except.c except.o

examples/iter: examples/iter.c iter.h
	$cc $cflags -I. -o examples/iter examples/iter.c
