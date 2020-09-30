#include "../include/common.h"
#include "../include/kjob.h"
#include "../include/proc_list.h"
#include "../include/types.h"

void kjob(command c) {
    /* Send a signal to a particular process
     *
     * Args -
     *  c: The command struct containing information about the command.
     */

    // Check if correct number of arguments are provided
    if(c.argc > 3) {
        fprintf(stderr, "Too many arguments\n");
        exit_status = 1;
        return;
    } else if(c.argc < 3) {
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

    // Send appropriate signal
    pid_t pid_to_kill = proc->pid;
    int signal_to_send = strtol(c.argv[2], NULL, 10);
    if (kill(pid_to_kill, signal_to_send) < 0) {
        perror("kjob");
        exit_status = 1;
    }
}
