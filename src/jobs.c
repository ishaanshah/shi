#include "../include/common.h"
#include "../include/constants.h"
#include "../include/jobs.h"
#include "../include/proc_list.h"
#include "../include/types.h"

void jobs(command c) {
    process *proc = proc_list;
    while (proc) {
        char proc_stat_path[MAX_PATH_LEN];
        char status_code;
        char *status = NULL;
        char comm[16];

        // Read status code of the process
        sprintf(proc_stat_path, "/proc/%d/stat", proc->pid);
        FILE *stat = fopen(proc_stat_path, "r");
        fscanf(stat, "%*d %s %c", comm, &status_code);
        comm[strlen(comm)-1] = '\0';

        switch(status_code) {
            case 'R':
               status = strdup("Running");
               break;
            case 'S':
               status = strdup("Sleeping");
               break;
            case 'D':
               status = strdup("Waiting");
               break;
            case 'T':
               status = strdup("Stopped");
               break;
            case 'Z':
               status = strdup("Zombie");
               break;
            default:
               status = strdup("Status Unknown");
               break;
        }

        printf("[%d] %s %s [%d]\n", proc->job_id, status, &comm[1], proc->pid);
        proc = get_next_process(proc);

        // Cleanup
        fclose(stat);
        free(status);
    };
}
