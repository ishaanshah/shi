#include "../include/common.h"
#include "../include/overkill.h"
#include "../include/proc_list.h"
#include "../include/types.h"

void overkill(command c) {
    /* Kill all background process by sending the SIGKILL signal
     *
     * Args -
     *  c: The command struct containing information about the command.
     */
    if (c.argc > 1) {
        fprintf(stderr, "Too many arguments\n");
    }

    while (proc_list) {
        if(kill(proc_list->pid, SIGKILL) < 0) {
            perror("overkill");
        }
    }
}
