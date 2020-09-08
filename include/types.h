#ifndef __TYPES_H
#define __TYPES_H

#include "./constants.h"

typedef struct command {
    int argc;
    char **argv;
} command;

typedef struct history {
    int index;
    char history [20][MAX_CMD_LEN];
} history;

#endif
