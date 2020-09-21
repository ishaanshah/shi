#include "../include/common.h"
#include "../include/setenv.h"
#include "../include/types.h"

void sh_setenv(command c) {
    /* Set environment variables.
     *
     * Args - 
     *  c: The command struct containing information about the command.
     */

    // Check if valid number of arguments are provided
    if (c.argc > 3) {
        fprintf(stderr, "Too many arguments\n");
        return;
    }
    if (c.argc < 2) {
        fprintf(stderr, "Too few arguments\n");
        return;
    }

    // Set the environment variable
    int result;
    if (c.argc == 2) {
        result = setenv(c.argv[1], "", 1);
    } else {
        result = setenv(c.argv[1], c.argv[2], 1);
    }

    // Check if setenv was successfull
    if (result < 0) {
        perror("setenv");
    }
}
