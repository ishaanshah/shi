#include "../include/common.h"
#include "../include/execute.h"
#include "../include/types.h"

void execute(command c) {
    pid_t pid = fork();

    // Error while creating a fork, show error message and exit
    if (pid < 0) {
        perror("Error while forking");
        return;
    }

    if (pid == 0) {
        // Child process
        char **argv = malloc((c.argc + 1) * sizeof(char *));

        // Copy command line arguments
        for (int i = 0; i < c.argc; i++) {
            argv[i] = c.argv[i];
        }
        argv[c.argc] = NULL;

        // Report if error is encounterd while spawning new process
        if (execvp(argv[0], argv) < 0) {
            perror("");
            return;
        }
    } else {
        // Parent process
        waitpid(pid, NULL, 0);
    }
}
