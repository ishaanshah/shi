#include "../include/cd.h"
#include "../include/common.h"
#include "../include/echo.h"
#include "../include/handlers.h"
#include "../include/ls.h"
#include "../include/pinfo.h"
#include "../include/pcwd.h"
#include "../include/types.h"

const char *builtin_cmds[] = {
    "cd",
    "echo",
    "ls",
    "pinfo",
    "pwd",
};

void (*handlers[]) (command c) = {
    cd,
    echo,
    ls,
    pinfo,
    pcwd,
};

const int string_to_handler_id(const char *cmd) {
    /* Returns the handler ID for the passed cmd
     *
     * Args -
     *  cmd: The cmd to get the ID for, it should be stripped of any leading or trailing
     *       whitespaces.
     *
     * Returns -
     *  id: The index of string in the builtin_cmds array if found, else -1
     */
    for (int id = 0; id < NUM_OF_BUILTINS; id++) {
        if (strcmp(builtin_cmds[id], cmd) == 0) {
            return id;
        }
    }
    return -1;
}
