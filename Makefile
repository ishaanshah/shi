# Compiler options
CC = gcc
CFLAGS = -Wall -Werror

# Directorie paths
IDIR = include
SDIR = src
BDIR = _build

# List of dependancies for compiling
ALL_OBJECTS =  $(BDIR)/echo.o $(BDIR)/handlers.o $(BDIR)/shi.o $(BDIR)/utils.o

build: $(ALL_OBJECTS)
	$(CC) $(CFLAGS) -I$(IDIR) -o shi $(ALL_OBJECTS)

debug: CFLAGS += -g -DDEBUG
debug: shi

$(BDIR)/echo.o: $(SDIR)/echo.c $(IDIR)/echo.h $(IDIR)/echo.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/echo.c -o $(BDIR)/echo.o

$(BDIR)/handlers.o: $(SDIR)/handlers.c $(IDIR)/echo.h $(IDIR)/handlers.h $(IDIR)/common.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/handlers.c -o $(BDIR)/handlers.o

$(BDIR)/shi.o: $(SDIR)/shi.c $(IDIR)/shi.h $(IDIR)/common.h $(IDIR)/constants.h $(IDIR)/handlers.h $(IDIR)/types.h $(IDIR)/utils.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/shi.c -o $(BDIR)/shi.o

$(BDIR)/utils.o: $(SDIR)/utils.c $(IDIR)/utils.h $(IDIR)/common.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/utils.c -o $(BDIR)/utils.o

clean:
	rm _build/*.o shi
