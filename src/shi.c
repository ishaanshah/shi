#include "../include/common.h"
#include "../include/shi.h"
#include "../include/utils.h"

int main() {
    char hostname[HOST_NAME_MAX];
    char username[LOGIN_NAME_MAX];
    char *cwd;
    char *cmd_list = NULL;
    size_t cmd_len = 0;

    // Set hostname
    gethostname(hostname, HOST_NAME_MAX);
    // TODO: Make sure that this is correct
    getlogin_r(username, LOGIN_NAME_MAX);

    // Flag to exit when the command is passed
    int exit = 0;
    while (!exit) {
        // Get current directory
        cwd = getcwd(NULL, 0);
        replace_tilde(cwd);

        // Print prompt
        printf("<%s@%s:%s>", username, hostname, cwd);
        getline(&cmd_list, &cmd_len, stdin);

        // Parse commands
        char *cmd = strtok(cmd_list, ";") ;
        while (cmd != NULL) {
            printf("%s", cmd);
            cmd = strtok(NULL, ";");
            // TODO: implement exit
            // if (strncmp("exit", cmd, 4) == 0) {
            //     exit = 1;
            //     break;
            // }
        }

    }

    free(cwd);
    free(cmd_list);

    return 0;
}
