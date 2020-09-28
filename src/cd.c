#include "../include/cd.h"
#include "../include/common.h"
#include "../include/constants.h"
#include "../include/types.h"
#include "../include/utils.h"

char last_dir[MAX_PATH_LEN] = "~";

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

    // Store current working directory
    char *cwd = getcwd(NULL, 0);

    // If no argument is passed, navigate to home
    if (c.argc == 1) {
        get_homedir(path);
    } else {
        if (strcmp(c.argv[1], "-") == 0) {
            // If "-" is passed, navigate to last directory
            strcpy(path, last_dir);
        } else {
            // Replace inital tilde with home if needed
            strcpy(path, c.argv[1]);
        }

        replace_tilde(path);
    }

    if (chdir(path) < 0) {
        perror("");
    } else {
        // Store last directory if path provided was valid
        strcpy(last_dir, cwd);
    }

    free(cwd);
}
