#include "../include/common.h"
#include "../include/constants.h"
#include "../include/execute.h"
#include "../include/handlers.h"
#include "../include/history.h"
#include "../include/shi.h"
#include "../include/signal_handlers.h"
#include "../include/types.h"
#include "../include/utils.h"

int main() {
    char *cmd_list = NULL;
    size_t cmd_len = 0;

    register_signal_handlers();

    // Initialise history struct
    char homedir[MAX_PATH_LEN];
    char history_path[MAX_PATH_LEN];
    get_homedir(homedir);
    strcpy(history_path, homedir);
    strcat(history_path, "/.shi_history");
    init_history(history_path);

    atexit(cleanup);

    // Struct to store information regarding the command
    struct command c = {0};
    c.argv = malloc(sizeof(char *) * MAX_ARG_COUNT);
    while (1) {
        // Print prompt
        print_prompt();

        // Read line, if response is -1, exit
        if (getline(&cmd_list, &cmd_len, stdin) < 0) {
            break;
        };

        // Add command to history
        update_history(cmd_list);

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
                c.argv[c.argc] = malloc(sizeof(char) * (strlen(cmd_arg) + 1));
                strcpy(c.argv[c.argc], cmd_arg);
                c.argc += 1;

                // Fetch next argument
                cmd_arg = strtok_r(NULL, " \t", &save_ptr[1]);
            }

            if (c.argc > 0) {
                int handler_id = string_to_handler_id(c.argv[0]);
                if (handler_id < 0) {
                    execute(c);
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
    free(cmd_list);

    return 0;
}
