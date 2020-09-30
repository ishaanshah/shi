# Compiler options
CC = gcc
CFLAGS = -Wall -Werror

# Directory paths
IDIR = include
SDIR = src
BDIR = _build

# List of dependancies for compiling
ALL_OBJECTS = $(BDIR)/bg.o $(BDIR)/cd.o $(BDIR)/common.o $(BDIR)/echo.o $(BDIR)/execute.o $(BDIR)/exit.o $(BDIR)/fg.o $(BDIR)/handlers.o $(BDIR)/history.o $(BDIR)/jobs.o $(BDIR)/kjob.o $(BDIR)/ls.o $(BDIR)/nightswatch.o $(BDIR)/overkill.o $(BDIR)/pcwd.o $(BDIR)/pinfo.o $(BDIR)/pipeline.o $(BDIR)/proc_list.o $(BDIR)/redirection.o $(BDIR)/shi.o $(BDIR)/signal_handlers.o $(BDIR)/setenv.o $(BDIR)/unsetenv.o $(BDIR)/utils.o

build: $(ALL_OBJECTS)
	$(CC) $(CFLAGS) -I$(IDIR) -o shi $(ALL_OBJECTS)

$(BDIR)/bg.o: $(SDIR)/bg.c $(IDIR)/bg.h $(IDIR)/common.h $(IDIR)/proc_list.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/bg.c -o $(BDIR)/bg.o

$(BDIR)/cd.o: $(SDIR)/cd.c $(IDIR)/cd.h $(IDIR)/common.h $(IDIR)/constants.h $(IDIR)/types.h $(IDIR)/utils.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/cd.c -o $(BDIR)/cd.o

$(BDIR)/common.o: $(SDIR)/common.c $(IDIR)/common.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/common.c -o $(BDIR)/common.o

$(BDIR)/echo.o: $(SDIR)/echo.c $(IDIR)/echo.h $(IDIR)/common.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/echo.c -o $(BDIR)/echo.o

$(BDIR)/execute.o: $(SDIR)/execute.c $(IDIR)/execute.h $(IDIR)/common.h $(IDIR)/proc_list.h $(IDIR)/signal_handlers.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/execute.c -o $(BDIR)/execute.o

$(BDIR)/exit.o: $(SDIR)/exit.c $(IDIR)/exit.h $(IDIR)/common.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/exit.c -o $(BDIR)/exit.o

$(BDIR)/fg.o: $(SDIR)/fg.c $(IDIR)/fg.h $(IDIR)/common.h $(IDIR)/proc_list.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/fg.c -o $(BDIR)/fg.o

$(BDIR)/handlers.o: $(SDIR)/handlers.c $(IDIR)/handlers.h $(IDIR)/bg.h $(IDIR)/cd.h $(IDIR)/common.h $(IDIR)/echo.h $(IDIR)/exit.h $(IDIR)/fg.h $(IDIR)/history.h $(IDIR)/jobs.h $(IDIR)/kjob.h $(IDIR)/ls.h $(IDIR)/nightswatch.h $(IDIR)/overkill.h $(IDIR)/pcwd.h $(IDIR)/pinfo.h $(IDIR)/setenv.h $(IDIR)/types.h $(IDIR)/unsetenv.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/handlers.c -o $(BDIR)/handlers.o

$(BDIR)/history.o: $(SDIR)/history.c $(IDIR)/history.h $(IDIR)/common.h $(IDIR)/constants.h $(IDIR)/types.h $(IDIR)/utils.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/history.c -o $(BDIR)/history.o

$(BDIR)/jobs.o: $(SDIR)/jobs.c $(IDIR)/jobs.h $(IDIR)/common.h $(IDIR)/proc_list.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/jobs.c -o $(BDIR)/jobs.o

$(BDIR)/kjob.o: $(SDIR)/kjob.c $(IDIR)/kjob.h $(IDIR)/common.h $(IDIR)/proc_list.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/kjob.c -o $(BDIR)/kjob.o

$(BDIR)/ls.o: $(SDIR)/ls.c $(IDIR)/ls.h $(IDIR)/common.h $(IDIR)/constants.h $(IDIR)/types.h $(IDIR)/utils.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/ls.c -o $(BDIR)/ls.o

$(BDIR)/nightswatch.o: $(SDIR)/nightswatch.c $(IDIR)/nightswatch.h $(IDIR)/common.h $(IDIR)/constants.h $(IDIR)/types.h $(IDIR)/utils.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/nightswatch.c -o $(BDIR)/nightswatch.o

$(BDIR)/overkill.o: $(SDIR)/overkill.c $(IDIR)/overkill.h $(IDIR)/common.h $(IDIR)/proc_list.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/overkill.c -o $(BDIR)/overkill.o

$(BDIR)/pcwd.o: $(SDIR)/pcwd.c $(IDIR)/pcwd.h $(IDIR)/common.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/pcwd.c -o $(BDIR)/pcwd.o

$(BDIR)/pinfo.o: $(SDIR)/pinfo.c $(IDIR)/pinfo.h $(IDIR)/common.h $(IDIR)/constants.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/pinfo.c -o $(BDIR)/pinfo.o

$(BDIR)/pipeline.o: $(SDIR)/pipeline.c $(IDIR)/pinfo.h $(IDIR)/common.h $(IDIR)/constants.h $(IDIR)/execute.h $(IDIR)/handlers.h $(IDIR)/redirection.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/pipeline.c -o $(BDIR)/pipeline.o

$(BDIR)/proc_list.o: $(SDIR)/proc_list.c $(IDIR)/proc_list.h $(IDIR)/common.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/proc_list.c -o $(BDIR)/proc_list.o

$(BDIR)/redirection.o: $(SDIR)/redirection.c $(IDIR)/redirection.h $(IDIR)/common.h $(IDIR)/constants.h $(IDIR)/types.h $(IDIR)/utils.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/redirection.c -o $(BDIR)/redirection.o

$(BDIR)/setenv.o: $(SDIR)/setenv.c $(IDIR)/setenv.h $(IDIR)/common.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/setenv.c -o $(BDIR)/setenv.o

$(BDIR)/shi.o: $(SDIR)/shi.c $(IDIR)/shi.h $(IDIR)/common.h $(IDIR)/constants.h $(IDIR)/history.h $(IDIR)/pipeline.h $(IDIR)/signal_handlers.h $(IDIR)/types.h $(IDIR)/utils.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/shi.c -o $(BDIR)/shi.o

$(BDIR)/signal_handlers.o: $(SDIR)/signal_handlers.c $(IDIR)/signal_handlers.h $(IDIR)/common.h $(IDIR)/constants.h $(IDIR)/proc_list.h $(IDIR)/utils.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/signal_handlers.c -o $(BDIR)/signal_handlers.o

$(BDIR)/unsetenv.o: $(SDIR)/unsetenv.c $(IDIR)/unsetenv.h $(IDIR)/common.h $(IDIR)/types.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/unsetenv.c -o $(BDIR)/unsetenv.o

$(BDIR)/utils.o: $(SDIR)/utils.c $(IDIR)/utils.h $(IDIR)/common.h $(IDIR)/constants.h $(IDIR)/history.h $(IDIR)/proc_list.h
	$(CC) $(CFLAGS) -I$(IDIR) -c $(SDIR)/utils.c -o $(BDIR)/utils.o

clean:
	rm _build/*.o shi
