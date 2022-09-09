CC = gcc
CFLAGS = -Wall -g

convert: convert.o

convert.o: convert.c

.PHONY: clean
clean:
	rm -f *.o convert

.PHONY: all
all: clean convert
