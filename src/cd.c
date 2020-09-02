#include "../include/cd.h"
#include "../include/common.h"
#include "../include/types.h"
#include "../include/utils.h"

void cd(command c) {
    /* Change directory to the specified path
     *
     * Args -
     *  c: The command struct containing information about the command
     */

    // Check for excess args
    if (c.argc > 2) {
        fprintf(stderr, "Too many arguments\n");
        return;
    }

    // Path to navigate to
    const char *path = NULL;

    // Buffer to store temporary results
    char *buf = malloc(sizeof(char));

    // If no argument is passed, navigate to home
    if (c.argc == 1) {
        path = get_homedir();
    } else {
        // Replace inital tilde with home if needed
        if (c.argv[1][0] == '~') {
            // Remove the leading tilde
            strcpy(c.argv[1], c.argv[1] + sizeof(c.argv[1][0]));

            // Get homedir
            const char *homedir = get_homedir();

            // Create needed space for concating
            buf = realloc(buf, sizeof(char) * (1 + strlen(homedir) + strlen(c.argv[1])));

            // Concat homedir and the apth
            strcpy(buf, homedir);
            strcat(buf, c.argv[1]);
            path = buf;
        } else {
            path = c.argv[1];
        }
    }


    if (chdir(path) < 0) {
        perror("");
    }

    free(buf);
}
