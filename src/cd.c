#include "../include/cd.h"
#include "../include/common.h"
#include "../include/constants.h"
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
    char path[MAX_PATH_LEN];

    // If no argument is passed, navigate to home
    if (c.argc == 1) {
        get_homedir(path);
    } else {
        // Replace inital tilde with home if needed
        strcpy(path, c.argv[1]);
        replace_tilde(path);
    }


    if (chdir(path) < 0) {
        perror("");
    }
}
