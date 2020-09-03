#ifndef __UTILS_H
#define __UTILS_H

void get_homedir(char *buf);

void replace_with_tilde(char *path);

void replace_tilde(char *path);

const char *get_username();

void trim_whitespaces(char *str);

#endif
