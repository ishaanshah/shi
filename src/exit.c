#include "../include/common.h"
#include "../include/exit.h"
#include "../include/types.h"

void sh_exit(command c) {
    /* Exits the shell with an code if provided.
     *
     * Arg -
     *  c: The command struct containing information about the command.
     */
    if (c.argc > 1) {
        exit(strtol(c.argv[1], NULL, 10));
    }
    exit(0);
}
