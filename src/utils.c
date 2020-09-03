#include "../include/common.h"
#include "../include/constants.h"
#include "../include/utils.h"

void get_homedir(char *buf) {
    /* Get the absolute path of user's home directory.
     *
     * Args -
     *  buf: The buffer to store the homdir in.
     */
    char process_exe_path[MAX_PATH_LEN];
    sprintf(process_exe_path, "/proc/%d/exe", getpid());
    // If home directory can't be read, exit the shell
    if (readlink(process_exe_path, buf, MAX_PATH_LEN) < -1) {
        perror("");
        exit(errno);
    };
    *strrchr(buf, '/') = '\0';
}

void replace_with_tilde(char *path) {
    /* Replace the home directory with tilde if needed. Overwrites the absolute path
     * passed with the one with tilde if home is present.
     *
     * Args -
     *  path: The absolute path to current working directory.
     */
    char homedir[MAX_PATH_LEN];
    get_homedir(homedir);

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

void replace_tilde(char *path) {
    /* Replace the tilde with home directory if needed. Overwrite the path variable
     * passed.
     *
     * Args -
     *  path: The path to replace tilde if needed
     */
    if (path[0] == '~') {
        // Remove the leading tilde
        memmove(path, &path[1], strlen(path) * sizeof(char));

        // Get homedir
        char homedir[MAX_PATH_LEN];
        get_homedir(homedir);

        // Replace tilde if needed
        char buf[MAX_PATH_LEN];
        strcpy(buf, homedir);
        strcat(buf, path);
        strcpy(path, buf);
    }
}

const char *get_username() {
    /* Returns the username of the user running the program */
    const char *username = getpwuid(getuid()) -> pw_name;
    return username;
}

void trim_whitespaces(char *str) {
    // Trim leading whitespaces
    int offset = 0;
    while (isspace(str[offset])) {
        offset++;
    }
    strcpy(str, str + (offset * sizeof(char)));

    // Trim trailing whitespaces
    int len = strlen(str);
    for (int idx = len-1; idx >= 0; idx--) {
        if (isspace(str[idx])) {
            str[idx] = '\0';
        } else {
            break;
        }
    }
}
