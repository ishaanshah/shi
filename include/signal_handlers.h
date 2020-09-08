#ifndef __SIGNAL_HANDLERS_H
#define __SIGNAL_HANDLERS_H

#include "common.h"

void register_signal_handlers();

void deregister_child_signal_handlers();

void zombie_killer(int signal, siginfo_t *info, void *context);

#endif
