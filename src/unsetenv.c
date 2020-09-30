#include "../include/common.h"
#include "../include/types.h"
#include "../include/unsetenv.h"

void sh_unsetenv(command c) {
    /* Unset environment variables.
     *
     * Args -
     *  c: The command struct containing information about the command.
     */

    // Check if valid number of arguments are provided
    if (c.argc > 2) {
        fprintf(stderr, "Too many arguments\n");
        exit_status = 1;
        return;
    }
    if (c.argc < 2) {
        fprintf(stderr, "Too few arguments\n");
        exit_status = 1;
        return;
    }

    // Check if unsetenv was successfull
    if (unsetenv(c.argv[1]) < 0) {
        perror("setenv");
        exit_status = 1;
    }
}
