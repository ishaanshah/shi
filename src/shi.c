#include "../include/common.h"
#include "../include/constants.h"
#include "../include/history.h"
#include "../include/pipeline.h"
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

    // Struct to store information regarding the pipe
    struct pipeline p = {0};
    p.cmdv = malloc(sizeof(command) * MAX_PIPE_COUNT);

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

        // Parse pipeline of commands
        char *save_ptr[3];
        char *pipeline = strtok_r(cmd_list, ";", &save_ptr[0]);
        while (pipeline != NULL) {
            trim_whitespaces(pipeline);

            // Initialise cmdc to 0
            p.cmdc = 0;

            // Tokenise commands
            char *cmd = strtok_r(pipeline, "|", &save_ptr[1]);
            while (cmd != NULL) {
                trim_whitespaces(cmd);

                // Tokenise arguments
                char *cmd_arg = strtok_r(cmd, " \t", &save_ptr[2]);

                // Initialise argc to 0 and input/output to empty strings
                c.argc = 0;
                c.append = 0;
                c.input[0] = '\0';
                c.output[0] = '\0';
                while (cmd_arg != NULL) {
                    // Check if redirection operators are present
                    if (strcmp(cmd_arg, ">") == 0) {
                        // Get file name
                        cmd_arg = strtok_r(NULL, " \t", &save_ptr[2]);
                        if (cmd_arg == NULL) {
                            fprintf(stderr, "Error: Output file path not provided, defaulting to STDOUT\n");
                            break;
                        }
                        strcpy(c.output, cmd_arg);
                    } else if(strcmp(cmd_arg, ">>") == 0) {
                        // Get file name
                        cmd_arg = strtok_r(NULL, " \t", &save_ptr[2]);
                        if (cmd_arg == NULL) {
                            fprintf(stderr, "Error: Output file path not provided, defaulting to STDOUT\n");
                            break;
                        }
                        strcpy(c.output, cmd_arg);
                        c.append = 1;
                    } else if (strcmp(cmd_arg, "<") == 0) {
                        // Get file name
                        cmd_arg = strtok_r(NULL, " \t", &save_ptr[2]);
                        if (cmd_arg == NULL) {
                            fprintf(stderr, "Error: Input file path not provided, defaulting to STDIN\n");
                            break;
                        }
                        strcpy(c.input, cmd_arg);
                    } else {
                        // Acquire necessary memory to store the argument
                        c.argv[c.argc] = strdup(cmd_arg);
                        c.argc += 1;
                    }

                    // Fetch next argument
                    cmd_arg = strtok_r(NULL, " \t", &save_ptr[2]);
                }

                // Copy data command data topipeline pipeline
                p.cmdv[p.cmdc].argc = c.argc;
                p.cmdv[p.cmdc].argv = malloc(sizeof(char *) * c.argc);
                p.cmdv[p.cmdc].append = c.append;
                strcpy(p.cmdv[p.cmdc].input, c.input);
                strcpy(p.cmdv[p.cmdc].output, c.output);

                // Free up memory to avoid memory leaks
                for (int arg = 0; arg < c.argc; arg++) {
                    p.cmdv[p.cmdc].argv[arg] = strdup(c.argv[arg]);
                    free(c.argv[arg]);
                }
                p.cmdc += 1;

                // Fetch next command
                cmd = strtok_r(NULL, "|", &save_ptr[1]);
            }
            exec_pipeline(p);

            // Free up memory to avoid memory leaks
            for (int cmd_idx = 0; cmd_idx < p.cmdc; cmd_idx++) {
                for (int arg = 0; arg < p.cmdv[cmd_idx].argc; arg++) {
                    free(p.cmdv[cmd_idx].argv[arg]);
                }
                free(p.cmdv[cmd_idx].argv);
            }

            // Fetch next pipeline of commands
            pipeline = strtok_r(NULL, ";", &save_ptr[0]);
        }
    }

    // Cleanup
    free(c.argv);
    free(p.cmdv);
    free(cmd_list);

    return 0;
}
