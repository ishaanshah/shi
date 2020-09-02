# Compiler options
CC = gcc
CFLAGS = -Wall -Werror

# Directorie paths
IDIR = include
SDIR = src
BDIR = _build

# List of dependancies for compiling
ALL_OBJECTS =  $(BDIR)/cd.o $(BDIR)/echo.o $(BDIR)/handlers.o $(BDIR)/pinfo.o $(BDIR)/pwd.o $(BDIR)/shi.o $(BDIR)/utils.o

build: $(ALL_OBJECTS)
	$(CC) $(CFLAGS) -I$(IDIR) -o shi $(ALL_OBJECTS)

debug: CFLAGS += -g -DDEBUG
debug: shi

$(BDIR)/cd.o: $(SDIR)/cd.c $(IDIR)/cd.h $(IDIR)/common.h $(IDIR)/types.h $(IDIR)/utils.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/cd.c -o $(BDIR)/cd.o

$(BDIR)/echo.o: $(SDIR)/echo.c $(IDIR)/echo.h $(IDIR)/common.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/echo.c -o $(BDIR)/echo.o

$(BDIR)/handlers.o: $(SDIR)/handlers.c $(IDIR)/handlers.h $(IDIR)/cd.h $(IDIR)/common.h $(IDIR)/echo.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/handlers.c -o $(BDIR)/handlers.o

$(BDIR)/pinfo.o: $(SDIR)/pinfo.c $(IDIR)/pinfo.h $(IDIR)/common.h $(IDIR)/constants.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/pinfo.c -o $(BDIR)/pinfo.o

$(BDIR)/pwd.o: $(SDIR)/pwd.c $(IDIR)/pwd.h $(IDIR)/common.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/pwd.c -o $(BDIR)/pwd.o

$(BDIR)/shi.o: $(SDIR)/shi.c $(IDIR)/shi.h $(IDIR)/common.h $(IDIR)/constants.h $(IDIR)/handlers.h $(IDIR)/types.h $(IDIR)/utils.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/shi.c -o $(BDIR)/shi.o

$(BDIR)/utils.o: $(SDIR)/utils.c $(IDIR)/utils.h $(IDIR)/common.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/utils.c -o $(BDIR)/utils.o

clean:
	rm _build/*.o shi
