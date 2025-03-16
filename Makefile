all: avltree.o test.out

avltree.o: avltree.c
	gcc -c avltree.c

test.out: test.c avltree.o
	gcc test.c avltree.o -o test.out -Wall
