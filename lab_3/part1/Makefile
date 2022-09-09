CC = gcc
CFLAGS = -Wall -g

libmylist.a: mylist.o mylist-test
	ar rcs libmylist.a mylist.o

mylist-test: mylist-test.o mylist.o

mylist-test.o: mylist-test.c  mylist.h

mylist.o: mylist.c mylist.h

.PHONY: clean
clean:
	rm -rf *.o *.a mylist-test

.PHONY: all
all: clean mylist-test libmylist.a
