# Shi
A shell by Ishaan...

## Features
- [x] Semicolon sperated command, not affected by whitespaces.
- [x] Shell Builtins
    - [x] bg `[job_id]`
    - [x] cd `[dirname]`
    - [x] echo `[statement]`
    - [x] exit `[exitcode]`
    - [x] fg `[job_id]`
    - [x] history `[count]`
    - [x] jobs
    - [x] kjob `[job_id]` `[signal]`
    - [x] ls `[-al]` `[dirnames]`
    - [x] nightswatch `[-n]` `[interrupts | newborn]`
    - [x] overkill
    - [x] pinfo `[pid]`
    - [x] pwd
    - [x] quit
    - [x] setenv `[var]` `[value]`
    - [x] unsetenv `[var]`
- [x] Any external program with options.
- [x] Ability to send a program to background using a trailing `&`.
- [x] Notification when background process ends.
- [x] Input/Output redirection.
- [x] Piping.
- [x] I/O redirection with pipelines.
- [x] CTRL-Z and CTRL-C signal handling.

## Build Instructions
The shell is built using the `make` command. To build and run the project run -
```bash
cd shi
make
./shi
```

The intermediate build files are stored in the `_build` directory, to remove them run
```bash
make clean
```
## File Structure
The project has been organised into two directories - `include` and `src`. The `src` directory
contains the source code for all the commands and `include` directory contains the corresponding
header files.

- **src/** - Contains the source code of the shell.
    - **bg.c** - Contains the source code for the `bg` command.
    - **cd.c** - Contains the source code for the `cd` command.
    - **echo.c** - Contains the source code for the `echo` command.
    - **execute.c** - Contains the source code for executing external commands
    - **exit.c** - Contains the source code for `exit` command.
    - **fg.c** - Contains the source code for the `fg` command.
    - **handlers.c** - Contains the code which maps commands to their appropriate handlers.
    - **history.c** - Contains the source code for the `history` command.
    - **jobs.c** - Contains the source code for `jobs` command.
    - **kjob.c** - Contains the source code for `kjob` command.
    - **ls.c** - Contains the source code for `ls` command.
    - **nightswatch.c** - Contains the source code for `nightswatch` command.
    - **pcwd.c** - Contains the source code for `pwd` command. It has been named differently to avoid
               collisions with *pwd.h*.
    - **pinfo.c** - Contains the source code for `pinfo` command.
    - **pipeline.c** - Contains the code related to piping of multiple commands.
    - **proc_list.c** - Contains code related to the background process list.
    - **redirection.c** - Contains code for implementation of I/O redirection.
    - **setenv.c** - Contains the source code for `setenv` command.
    - **shi.c** - Contains the main loop where input is taken and parsed.
    - **signal_handlers.c** - Contains functions related signals and the `SIGCHLD` handler.
    - **unsetenv.c** - Contains the source code for `unsetenv` command.
    - **utils.c** - Contains some generic utility functions which have been used throughout the shell.
- **include/** - Contains all the corresponding header files for the above `C` files and some additional files.
    - **common.h** - Contains all the system header files needed for the program to run.
    - **constants.h** - Contains macros for some constants used throughout the code.
    - **types.h** - Contains the structs for some custom types used in the code.
- **Makefile** - Contains the intructions for building the shell using `make`.
