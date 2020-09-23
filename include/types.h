#ifndef __TYPES_H
#define __TYPES_H

#include "./common.h"
#include "./constants.h"

typedef struct command {
    int argc;
    char **argv;
    char input[MAX_PATH_LEN];
    char output[MAX_PATH_LEN];
    int append;
} command;

typedef struct history {
    int index;
    char history [20][MAX_CMD_LEN];
} history;

typedef struct process {
    struct process *next;
    int job_id;
    pid_t pid;
} process;

typedef struct pipeline {
    int cmdc;
    command *cmdv;
} pipeline;

#endif
