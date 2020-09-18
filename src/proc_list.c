#include "../include/common.h"
#include "../include/proc_list.h"
#include "../include/types.h"

process *proc_list = NULL;

int job_no = 0;

void insert_process(pid_t pid) {
    // Allocate space for new process
    process *proc = malloc(sizeof(proc_list));
    proc->next = NULL;
    proc->job_id = ++job_no;
    proc->pid = pid;

    // If list hasn't been initialised, initialise it
    if (proc_list == NULL) {
        proc_list = proc;
        return;
    }

    // Find end of process list and insert process
    process *proc_next = proc_list;
    while (proc_next->next != NULL) {
        proc_next = get_next_process(proc_next);
    }
    proc_next->next = proc;
}

void delete_process(pid_t pid) {
    // If process list is empty, return
    if (!proc_list) {
        return;
    }

    // Check if first item in list is the required process itself
    if (proc_list->pid == pid) {
        process *to_free = proc_list;
        proc_list = proc_list->next;
        free(to_free);
        return;
    }

    // Search the process with given pid from 2nd item
    process *proc = proc_list;
    while (proc->next != NULL && proc->next->pid != pid) {
        proc = get_next_process(proc);
    }

    // Delete the entry
    if (proc->next->pid == pid) {
        process *to_free = proc->next;
        proc->next = proc->next->next;
        free(to_free);
    }
}

void free_proc_list() {
    while (proc_list) {
        delete_process(proc_list->pid);
    }
}

process *get_next_process(process *p) {
    return p ? p->next : NULL;
}
