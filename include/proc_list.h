#ifndef __PROC_LIST_H
#define __PROC_LIST_H

#include "./common.h"
#include "./types.h"

extern process *proc_list;

void insert_process(pid_t pid);

void delete_process(pid_t pid);

process *get_next_process(process *p);

#endif
