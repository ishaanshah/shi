# Compiler options
CC = gcc
CFLAGS = -Wall -Werror

# Directorie paths
IDIR = include
SDIR = src
BDIR = _build

# List of dependancies for compiling
ALL_OBJECTS =  $(BDIR)/cd.o $(BDIR)/echo.o $(BDIR)/execute.o $(BDIR)/handlers.o $(BDIR)/ls.o $(BDIR)/pcwd.o $(BDIR)/pinfo.o $(BDIR)/shi.o $(BDIR)/utils.o

build: $(ALL_OBJECTS)
	$(CC) $(CFLAGS) -I$(IDIR) -o shi $(ALL_OBJECTS)

debug: CFLAGS += -g -DDEBUG
debug: shi

$(BDIR)/cd.o: $(SDIR)/cd.c $(IDIR)/cd.h $(IDIR)/common.h $(IDIR)/constants.h $(IDIR)/types.h $(IDIR)/utils.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/cd.c -o $(BDIR)/cd.o

$(BDIR)/echo.o: $(SDIR)/echo.c $(IDIR)/echo.h $(IDIR)/common.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/echo.c -o $(BDIR)/echo.o

$(BDIR)/execute.o: $(SDIR)/execute.c $(IDIR)/execute.h $(IDIR)/common.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/execute.c -o $(BDIR)/execute.o

$(BDIR)/handlers.o: $(SDIR)/handlers.c $(IDIR)/handlers.h $(IDIR)/cd.h $(IDIR)/common.h $(IDIR)/echo.h $(IDIR)/ls.h $(IDIR)/pcwd.h $(IDIR)/pinfo.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/handlers.c -o $(BDIR)/handlers.o

$(BDIR)/ls.o: $(SDIR)/ls.c $(IDIR)/ls.h $(IDIR)/common.h $(IDIR)/constants.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/ls.c -o $(BDIR)/ls.o

$(BDIR)/pinfo.o: $(SDIR)/pinfo.c $(IDIR)/pinfo.h $(IDIR)/common.h $(IDIR)/constants.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/pinfo.c -o $(BDIR)/pinfo.o

$(BDIR)/pcwd.o: $(SDIR)/pcwd.c $(IDIR)/pcwd.h $(IDIR)/common.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/pcwd.c -o $(BDIR)/pcwd.o

$(BDIR)/shi.o: $(SDIR)/shi.c $(IDIR)/shi.h $(IDIR)/common.h $(IDIR)/constants.h $(IDIR)/execute.h $(IDIR)/handlers.h $(IDIR)/types.h $(IDIR)/utils.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/shi.c -o $(BDIR)/shi.o

$(BDIR)/utils.o: $(SDIR)/utils.c $(IDIR)/utils.h $(IDIR)/common.h $(IDIR)/constants.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/utils.c -o $(BDIR)/utils.o

clean:
	rm _build/*.o shi
