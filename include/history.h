#ifndef __HISTORY_H
#define __HISTORY_H

#include "./types.h"

void init_history(char *path);

void get_history(command c);

void update_history(char *entry);

void save_history(char *path);

#endif
