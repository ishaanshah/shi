#include "../include/common.h"
#include "../include/constants.h"
#include "../include/execute.h"
#include "../include/handlers.h"
#include "../include/history.h"
#include "../include/redirection.h"
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

            // Initialise argc to 0 and input, output filepaths to NULL
            c.argc = 0;
            char *input = NULL;
            char *output = NULL;
            int append = 0;
            while (cmd_arg != NULL) {
                // Check if redirection operators are present
                if (strcmp(cmd_arg, ">") == 0) {
                    // Get file name
                    cmd_arg = strtok_r(NULL, " \t", &save_ptr[1]);
                    if (cmd_arg == NULL) {
                        fprintf(stderr, "Error: Output file path not provided, defaulting to STDOUT\n");
                        break;
                    }
                    output = malloc(sizeof(char *) * (strlen(cmd_arg) + 1));
                    strcpy(output, cmd_arg);
                } else if(strcmp(cmd_arg, ">>") == 0) {
                    // Get file name
                    cmd_arg = strtok_r(NULL, " \t", &save_ptr[1]);
                    if (cmd_arg == NULL) {
                        fprintf(stderr, "Error: Output file path not provided, defaulting to STDOUT\n");
                        break;
                    }
                    output = malloc(sizeof(char *) * (strlen(cmd_arg) + 1));
                    strcpy(output, cmd_arg);
                    append = 1;
                } else if (!output && strcmp(cmd_arg, "<") == 0) {
                    // Get file name
                    cmd_arg = strtok_r(NULL, " \t", &save_ptr[1]);
                    if (cmd_arg == NULL) {
                        fprintf(stderr, "Error: Input file path not provided, defaulting to STDIN\n");
                        break;
                    }
                    input = malloc(sizeof(char *) * (strlen(cmd_arg) + 1));
                    strcpy(input, cmd_arg);
                } else {
                    // Acquire necessary memory to store the argument
                    c.argv[c.argc] = malloc(sizeof(char) * (strlen(cmd_arg) + 1));
                    strcpy(c.argv[c.argc], cmd_arg);
                    c.argc += 1;
                }

                // Fetch next argument
                cmd_arg = strtok_r(NULL, " \t", &save_ptr[1]);
            }

            redirect(input, output, append);

            if (c.argc > 0) {
                int handler_id = string_to_handler_id(c.argv[0]);
                if (handler_id < 0) {
                    execute(c);
                } else {
                    handlers[handler_id](c);
                }
            }

            restore_redirect();

            // Free up memory to avoid memory leaks
            for (int arg = 0; arg < c.argc; arg++) {
                free(c.argv[arg]);
            }
            if (input) {
                free(input);
            }
            if (output) {
                free(output);
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
