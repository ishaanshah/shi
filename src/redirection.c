#include "../include/common.h"
#include "../include/constants.h"
#include "../include/redirection.h"
#include "../include/types.h"
#include "../include/utils.h"

int stdin_cpy = -1;
int stdout_cpy = -1;

void redirect(char *input, char *output, int append) {
    stdin_cpy = -1;
    stdout_cpy = -1;

    if (input) {
        stdin_cpy = dup(STDIN_FILENO);
        char inp_file_path[MAX_PATH_LEN];
        strcpy(inp_file_path, input);
        replace_tilde(inp_file_path);

        // Open file to read input
        int inp_file = open(inp_file_path, O_RDONLY, 0644);
        if (inp_file < 0 ) {
            perror("Error while opening input file");
        }

        // Alias STDIN_FILENO to inp_file
        if (dup2(inp_file, STDIN_FILENO) < 0) {
            perror("Error while redirecting STDIN");
        }

        close(inp_file);
    }

    if (output) {
        stdout_cpy = dup(STDOUT_FILENO);
        char out_file_path[MAX_PATH_LEN];
        strcpy(out_file_path, output);
        replace_tilde(out_file_path);

        // Open file to read outut
        int out_file = -1;
        if (append) {
            out_file = open(out_file_path, O_CREAT | O_WRONLY | O_APPEND, 0644);
        } else {
            out_file = open(out_file_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        }
        if (out_file < 0 ) {
            perror("Error while opening output file");
        }

        // Alias STDOUT_FILENO to out_file
        if (dup2(out_file, STDOUT_FILENO) < 0) {
            perror("Error while redirecting STDOUT");
        }

        close(out_file);
    }
}

void restore_redirect() {
    // Restore STDIN to normal fd after redirection
    if (stdin_cpy > 0) {
        // If restoring fails, try to print error message and exit
        // the shell as the error is fatal
        if (dup2(stdin_cpy, STDIN_FILENO) < 0) {
            perror("Error while restoring STDIN");
            close(stdin_cpy);
            exit(errno);
        }
        stdin_cpy = -1;
    }

    // Restore STDOUT to normal fd after redirection
    if (stdout_cpy > 0) {
        // If restoring fails, try to print error message and exit
        // the shell as the error is fatal
        if (dup2(stdout_cpy, STDOUT_FILENO) < 0) {
            perror("Error while restoring STDOUT");
            close(stdout_cpy);
            exit(errno);
        }
        stdout_cpy = -1;
    }
}
