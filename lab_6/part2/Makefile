#
# Makefile for lab 6, part 2
#

CC = gcc

CFLAGS = -g -Wall -C

http-client: http-client.o

http-client.o: http-client.c

.PHONY: clean
clean:
	rm -f *.o http-client

.PHONY: all
all: clean http-client
