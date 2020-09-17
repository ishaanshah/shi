#ifndef __REDIRECTION_H
#define __REDIRECTION_H

#include "types.h"

extern int stdin_cpy;
extern int stdout_cpy;

void redirect(char *input, char *output, int append);

void restore_redirect();

#endif
