#ifndef __UTILS_H
#define __UTILS_H

const char *get_homedir();

void replace_tilde(char *path);

const char *get_username();

void trim_whitespaces(char *str);

#endif
