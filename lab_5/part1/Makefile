#
# Makefile for lab 5, part 1
#

CC  = gcc
CXX = g++

##INCLUDES = -I../../lab3/solutions/part1
CFLAGS   = -g -Wall
CXXFLAGS = -g -Wall

##LDFLAGS = -g -L../../lab3/solutions/part1
##LDLIBS = -lmylist

mdb-lookup-server-nc-2: mdb-lookup-server-nc-2.o
mdb-lookup-server-nc-1: mdb-lookup-server-nc-1.o

.PHONY: clean
clean:
	rm -f *.o *~ mdb-lookup-server-nc-1
	rm -f *.o *~ mdb-lookup-server-nc-2
	rm -f mypipe-*

.PHONY: all
all: clean mdb-lookup-server-nc-1 mdb-lookup-server-nc-2
