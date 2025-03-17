all: avltree.o test.out

avltree.o: avltree.c avltree.h
	gcc -c avltree.c

test.out: test.c avltree.o avltree.h
	gcc test.c avltree.o -o test.out -Wall
