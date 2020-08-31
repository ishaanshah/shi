#include "../include/common.h"
#include "../include/utils.h"
#include <stdio.h>
#include <string.h>

const char *get_homedir() {
    /* Returns the absolute path of user's home directory */
    const char *homedir = getpwuid(getuid()) -> pw_dir;
    return homedir;
}

void replace_tilde(char *path) {
    /* Replace the home directory with tilde if needed. Overwrites the absolute path
     * passed with the one with tilde if home is present.
     *
     * Args -
     *  path: The absolute path to current working directory.
     */
    const char *homedir = get_homedir();

    unsigned long path_len = strlen(path);
    unsigned long homedir_len = strlen(homedir);

    // If path_len > homedir_len then the path may contain home
    if (path_len >= homedir_len && strncmp(homedir, path, homedir_len) == 0) {
        char *result = malloc(sizeof(char) * (path_len + 1));
        result[0] = '~';
        strcpy(result + sizeof(char), path + homedir_len);
        strcpy(path, result);
        free(result);
    }
}
