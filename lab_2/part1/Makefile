CC = gcc
CFLAGS = -Wall -g

isort: isort.o sorter.o

isort.o: isort.c sorter.h

sorter.o: sorter.c sorter.h

.PHONY: clean
clean:
	rm -f *.o isort

.PHONY: all
all: clean isort
