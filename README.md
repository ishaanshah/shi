# Shi
A shell by Ishaan...

## Features
- [x] Semicolon sperated command, not affected by whitespaces.
- [x] Shell Builtins
    - [x] cd `[dirname]`
    - [x] echo `[statement]`
    - [x] exit `[exitcode]`
    - [x] history `[count]`
    - [x] ls `[-al]` `[dirnames]`
    - [x] nightswatch `[-n]` `[interrupts | newborn]`
    - [x] pinfo `[pid]`
    - [x] pwd
- [x] Any external program with options.
- [x] Ability to send a program to background using a trailing `&`
- [x] Notification when background process ends.

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
    - **cd.c** - Contains the source code for the `cd` command.
    - **echo.c** - Contains the source code for the `echo` command.
    - **execute.c** - Contains the source code for executing external commands
    - **exit.c** - Contains the source code for `exit` command.
    - **handlers.c** - Contains the code which maps commands to their appropriate handlers.
    - **history.c** - Contains the source code for the `history` command.
    - **ls.c** - Contains the source code for `ls` command.
    - **nightswatch.c** - Contains the source code for `nightswatch` command.
    - **pcwd.c** - Contains the source code for `pwd` command. It has been named differently to avoid
               collisions with *pwd.h*.
    - **pinfo.c** - Contains the source code for `pinfo` command.
    - **shi.c** - Contains the main loop where input is taken and parsed.
    - **signal_handlers.c** - Contains functions related signals and the `SIGCHLD` handler.
    - **utils.c** - Contains some generic utility functions which have been used throughout the shell.
- **include/** - Contains all the corresponding header files for the above `C` files and some additional files.
    - **common.h** - Contains all the system header files needed for the program to run.
    - **constants.h** - Contains macros for some constants used throughout the code.
    - **types.h** - Contains the structs for some custom types used in the code.
- **Makefile** - Contains the intructions for building the shell using `make`.
