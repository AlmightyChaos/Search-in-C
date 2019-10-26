all:rbtree

CC = gcc
INCLUDE = .
CFLAGS = -g -Wall -ansi


rbtree:rbtree.o rbtree_test.o
	$(CC) -o rbtree rbtree.o rbtree_test.o
rbtree.o:rbtree.h rbtree.c
	$(CC) -I $(INCLUDE) $(CFLAGS) -c rbtree.c 
rbtree_test.o:rbtree.h rbtree.c 
	$(CC) -I $(INCLUDE) $(CFLAGS) -c rbtree_test.c

clean:
	rm -f rbtree.o rbtree_test.o rbtree

