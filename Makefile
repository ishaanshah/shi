# Compiler options
CC = gcc
CFLAGS = -Wall -Werror

# Directorie paths
IDIR = include
SDIR = src
BDIR = _build

# List of dependancies for compiling
ALL_OBJECTS = $(BDIR)/shi.o

build: $(ALL_OBJECTS)
	$(CC) $(CFLAGS) -I$(IDIR) -o shi $(ALL_OBJECTS)

debug: CFLAGS += -g -DDEBUG
debug: ysh

$(BDIR)/shi.o: $(SDIR)/shi.c $(IDIR)/shi.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/shi.c -o $(BDIR)/shi.o

clean:
	rm -r _build shi
