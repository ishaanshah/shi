#include "../include/common.h"
#include "../include/execute.h"
#include "../include/proc_list.h"
#include "../include/signal_handlers.h"
#include "../include/types.h"

int check_trailing_amp(command c) {
    /* Check if the command has trailing &amp */
    return c.argv[c.argc-1][0] == '&' ? 1 : 0;
}

void execute(command c) {
    /* Execute non inbuilt programs
     *
     * Args -
     *  c: The command struct containing information about the command.
     */
    pid_t pid = fork();

    // Error while creating a fork, show error message and exit
    if (pid < 0) {
        perror("Error while forking");
        return;
    }

    const int bg = check_trailing_amp(c);

    if (pid == 0) {
        // Child process
        // Change process group of child process
        setpgid(0, 0);

        deregister_child_signal_handlers();

        // If it is a foreground process, change the foreground group
        if (!bg) {
            tcsetpgrp(STDIN_FILENO, getpgid(0));
        }

        char **argv = NULL;
        argv = malloc((c.argc + 1) * sizeof(char *));

        // Copy command line arguments
        for (int arg = 0; arg < c.argc; arg++) {
            argv[arg] = strdup(c.argv[arg]);
        }
        if (bg) {
            argv[c.argc - 1] = NULL;
        }
        argv[c.argc] = NULL;

        // Report if error is encounterd while spawning new process
        // and clean up malloced memory.
        if (execvp(argv[0], argv) < 0) {
            // Cleanup
            for (int arg = 0; arg < c.argc; arg++) {
                free(argv[arg]);
            }
            free(argv[c.argc]);
            free(argv);

            // Print error
            fprintf(stderr, "Error: command \"%s\" not found\n", c.argv[0]);
            exit(1);
        }
    } else {
        // Parent process
        // Change process group of child process
        setpgid(pid, pid);
        if (bg) {
            insert_process(pid);
        } else {
            // Change foreground group
            tcsetpgrp(STDIN_FILENO, getpgid(pid));

            // Wait for process to complete
            int status;
            waitpid(pid, &status, WUNTRACED);

            // Restore foreground group
            tcsetpgrp(STDIN_FILENO, getpgid(0));

            // Insert in bg process list if process is stopped
            if (WIFSTOPPED(status)) {
                insert_process(pid);
                exit_status = 1;
            }
        }
    }
}
