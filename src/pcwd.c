#include "../include/common.h"
#include "../include/pcwd.h"
#include "../include/types.h"

void pcwd(command c) {
    /* Prints the current working directory
     *
     * Args -
     *  c: The command struct containing information about the command
     */

    // Check for excess args
    if (c.argc > 1) {
        fprintf(stderr, "Too many arguments\n");
        return;
    }

    // Fetch and print the current working directory
    char *cwd;
    cwd = getcwd(NULL, 0);
    printf("%s\n", cwd);

    // Cleanup to avoid memory leaks
    free(cwd);
}
