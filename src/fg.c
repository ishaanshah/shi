#include "../include/common.h"
#include "../include/fg.h"
#include "../include/proc_list.h"
#include "../include/types.h"

void fg(command c) {
    /* Bring a background job to foreground.
     *
     * Args -
     *  c: The command struct containing information about the command.
     */

    // Check if correct number of arguments are provided
    if(c.argc > 2) {
        fprintf(stderr, "Too many arguments\n");
        exit_status = 1;
        return;
    } else if(c.argc < 2) {
        fprintf(stderr, "Too few arguments\n");
        exit_status = 1;
        return;
    }

    // Search for job with given job_id
    int job_id = strtol(c.argv[1], NULL, 10);
    process *proc = proc_list;
    while (proc) {
        if (proc->job_id == job_id) {
            break;
        }
        proc = get_next_process(proc);
    }
    if (!proc) {
        fprintf(stderr, "Invalid job ID\n");
        exit_status = 1;
        return;
    }
    pid_t pid = proc->pid;

    // Change foreground process group
    tcsetpgrp(STDIN_FILENO, getpgid(pid));

    // Send SIGCONT to process group
    if (kill(pid, SIGCONT) < 0) {
        perror("fg");
        exit_status = 1;
    }

    // Delete the process from bg process list
    delete_process(pid);

    // Wait for process to complete
    int status;
    waitpid(pid, &status, WUNTRACED);

    // Restore foreground process group
    tcsetpgrp(STDIN_FILENO, getpgid(0));

    // Reinsert process if it's sent to background again
    if (WIFSTOPPED(status)) {
        insert_process(pid);
    }
}
