#include "../include/common.h"
#include "../include/constants.h"
#include "../include/signal_handlers.h"
#include "../include/utils.h"

void register_signal_handlers() {
    /* Register the appropriate signal handlers while initialising the shell */

    // Register SIGCHLD handler
    struct sigaction sig_chld_action;
    memset(&sig_chld_action, 0, sizeof(sig_chld_action));
    sig_chld_action.sa_sigaction = zombie_killer;
    sig_chld_action.sa_flags = SA_RESTART | SA_SIGINFO;
    sigaction(SIGCHLD, &sig_chld_action, 0);

    // Ignore interactive and job-control signals
    signal (SIGINT, SIG_IGN);
    signal (SIGQUIT, SIG_IGN);
    signal (SIGTSTP, SIG_IGN);
    signal (SIGTTIN, SIG_IGN);
    signal (SIGTTOU, SIG_IGN);
}

void deregister_child_signal_handlers() {
    /* Deregister the ignored signal handlers for child process */

    // Ignore interactive and job-control signals
    signal (SIGINT, SIG_DFL);
    signal (SIGQUIT, SIG_DFL);
    signal (SIGTSTP, SIG_DFL);
    signal (SIGTTIN, SIG_DFL);
    signal (SIGTTOU, SIG_DFL);
    signal (SIGCHLD, SIG_DFL);
}

void zombie_killer(int signal, siginfo_t *info, void *context) {
    // Get process name
    char proc_name[MAX_PATH_LEN];
    char proc_path[MAX_PATH_LEN];
    sprintf(proc_path, "/proc/%d/comm", info->si_pid);
    int stat_file = open(proc_path, O_RDONLY, 0);
    read(stat_file, proc_name, MAX_PATH_LEN);
    basename(proc_name);
    proc_name[strlen(proc_name) - 1] = '\0';
    close(stat_file);

    // Reap the process
    int status;
    pid_t pid = waitpid(info->si_pid, &status, WNOHANG);
    if (pid <= 0) {
        return;
    } else {
        char buf[5000];
        sprintf(buf, "\r%s with pid %d exited %s\n",
                proc_name, pid,
                !info->si_status ? "normally" : "abnormally");
        write(STDERR_FILENO, buf, strlen(buf));
        print_prompt();
    }
}

