#ifndef __HANDLERS_H
#define __HANDLERS_H

#include "./types.h"

#define NUM_OF_BUILTINS 14

extern const char *builtin_cmds[];

extern void (*handlers[]) (command c);

const int string_to_handler_id(const char *cmd);

#endif
