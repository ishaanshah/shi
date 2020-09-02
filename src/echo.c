#include "../include/common.h"
#include "../include/echo.h"
#include "../include/types.h"

void echo(command c) {
    /* Dump argv to stdout
     *
     * Args -
     *  c: The command struct containing information about the command
     */
    for (int arg = 1; arg < c.argc; arg++) {
        printf("%s ", c.argv[arg]);
    }
    printf("\n");
}
