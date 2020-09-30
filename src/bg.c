#include "../include/bg.h"
#include "../include/common.h"
#include "../include/proc_list.h"
#include "../include/types.h"

void bg(command c) {
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

    // Send SIGCONT to process group
    if (kill(proc->pid, SIGCONT) < 0) {
        perror("fg");
        exit_status = 1;
    }
}
