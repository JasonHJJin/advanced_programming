CC = gcc
CFLAGS = -Wall -g

isort: allocate_Int.o

allocate_Int.o: allocate_Int.c

.PHONY: clean
clean:
	rm -f *.o isort

.PHONY: all
all: clean isort
