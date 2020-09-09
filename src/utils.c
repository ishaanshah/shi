#include "../include/common.h"
#include "../include/constants.h"
#include "../include/history.h"
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
    dirname(buf);
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
    /* Trim leading and trailing whitespace, the passed string will be modified.
     *
     * Args -
     *  str: The string to trim whitespaces from.
     */

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

void print_prompt() {
    /* Print the promt in the shell */
    char *cwd;
    char hostname[HOST_NAME_MAX];

    // Get current directory
    cwd = getcwd(NULL, 0);
    replace_with_tilde(cwd);

    // Set hostname
    gethostname(hostname, HOST_NAME_MAX);

    printf("<%s@%s:%s> ", get_username(), hostname, cwd);
    fflush(stdout);

    free(cwd);
}

void cleanup() {
    /* Cleanup before exiting */
    char homedir[MAX_PATH_LEN];
    char history_path[MAX_PATH_LEN];
    get_homedir(homedir);
    strcpy(history_path, homedir);
    strcat(history_path, "/.shi_history");
    save_history(history_path);
}

int key_pressed() {
    /* Returns 1 if a key is pressed, otherwise returns 0 */
    struct termios old_attr, new_attr;

    // Store old properties
    tcgetattr(STDIN_FILENO, &old_attr);

    // Disable canonical mode
    new_attr = old_attr;
    new_attr.c_lflag &= ~(ICANON | ECHO);

    // Change the terminal mode
    tcsetattr(STDIN_FILENO, TCSANOW, &new_attr);

    // Check if anything should be read
    int bytes_to_read;
    ioctl(STDIN_FILENO, FIONREAD, &bytes_to_read);

    // Restore old properties
    tcsetattr(STDIN_FILENO, TCSANOW, &old_attr);

    return bytes_to_read > 0 ? 1 : 0;
}
