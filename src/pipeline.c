#include "../include/common.h"
#include "../include/constants.h"
#include "../include/execute.h"
#include "../include/handlers.h"
#include "../include/pipeline.h"
#include "../include/redirection.h"
#include "../include/types.h"
#include <unistd.h>

void exec_cmd(command c) {
    // Redirect the I/O if needed
    redirect(c.input, c.output, c.append);

    // Call the actual command
    if (c.argc > 0) {
        int handler_id = string_to_handler_id(c.argv[0]);
        if (handler_id < 0) {
            execute(c);
        } else {
            handlers[handler_id](c);
        }
    }

    // Restore STDIN and STDOUT if needed
    restore_redirect();
}

void exec_pipeline(pipeline p) {
    // Make copies of STDIN and STDOUT to restore them later
    int stdin_cpy = dup(STDIN_FILENO);
    int stdout_cpy = dup(STDOUT_FILENO);

    // Create an array to store all the pipes created
    int pipes[MAX_PIPE_COUNT][2];
    for (int cmd = 0; cmd < p.cmdc; cmd++) {
        if (cmd < p.cmdc - 1) {
            pipe(pipes[cmd]);
        }

        command c = p.cmdv[cmd];
        if (cmd == 0) {
            dup2(pipes[0][1], STDOUT_FILENO);
            exec_cmd(c);
            close(pipes[0][1]);
        } else if (cmd == p.cmdc - 1) {
            dup2(stdout_cpy, STDOUT_FILENO);
            dup2(pipes[cmd-1][0], STDIN_FILENO);
            exec_cmd(c);
            close(pipes[cmd-1][0]);
        } else {
            dup2(pipes[cmd][1], STDOUT_FILENO);
            dup2(pipes[cmd-1][0], STDIN_FILENO);
            exec_cmd(c);
            close(pipes[cmd][1]);
            close(pipes[cmd-1][0]);
        }
    }

    // Restore STDIN and STDOUT
    dup2(stdin_cpy, STDIN_FILENO);
    dup2(stdout_cpy, STDOUT_FILENO);
}
