#include "../include/common.h"
#include "../include/constants.h"
#include "../include/handlers.h"
#include "../include/shi.h"
#include "../include/types.h"
#include "../include/utils.h"

int main() {
    char hostname[HOST_NAME_MAX];
    char *cwd;
    char *cmd_list = NULL;
    size_t cmd_len = 0;

    // Set hostname
    gethostname(hostname, HOST_NAME_MAX);

    // Struct to store information regarding the command
    struct command c = {0};
    c.argv = malloc(sizeof(char *) * MAX_ARG_COUNT);
    while (1) {
        // Get current directory
        cwd = getcwd(NULL, 0);
        replace_tilde(cwd);

        // Print prompt
        printf("<%s@%s:%s>", get_username(), hostname, cwd);
        getline(&cmd_list, &cmd_len, stdin);

        // Parse commands
        char *save_ptr[2];
        char *cmd = strtok_r(cmd_list, ";", &save_ptr[0]);
        while (cmd != NULL) {
            trim_whitespaces(cmd);

            // Tokenise arguments
            char *cmd_arg = strtok_r(cmd, " \t", &save_ptr[1]);

            // Initialise argc to 0
            c.argc = 0;
            while (cmd_arg != NULL) {
                // Acquire necessary memory to store the argument
                c.argv[c.argc] = malloc(sizeof(char) * strlen(cmd_arg));
                strcpy(c.argv[c.argc], cmd_arg);
                c.argc += 1;

                // Fetch next argument
                cmd_arg = strtok_r(NULL, " \t", &save_ptr[1]);
            }

            if (c.argc > 0) {
                int handler_id = string_to_handler_id(c.argv[0]);
                if (handler_id < 0) {
                    fprintf(stderr, "Command not found: %s\n", c.argv[0]);
                } else {
                    handlers[handler_id](c);
                }
            }

            // Free up memory to avoid memory leaks
            for (int arg = 0; arg < c.argc; arg++) {
                free(c.argv[arg]);
            }

            // Fetch next command
            cmd = strtok_r(NULL, ";", &save_ptr[0]);
        }

    }

    // Cleanup
    free(c.argv);
    free(cwd);
    free(cmd_list);

    return 0;
}
