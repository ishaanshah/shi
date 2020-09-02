#include "../include/common.h"
#include "../include/constants.h"
#include "../include/pinfo.h"
#include "../include/types.h"

void pinfo(command c) {
    // Check for excess args
    if (c.argc > 2) {
        fprintf(stderr, "Too many arguments\n");
        return;
    }

    // Path for information regarding the process
    char proc_path[MAX_PATH_LEN];

    if (c.argc == 1) {
        // Find information about current process if PID is not provided
        sprintf(proc_path, "/proc/%d", getpid());
    } else {
        sprintf(proc_path, "/proc/%s", c.argv[1]);
    }


    // Check if given PID is valid
    DIR *dir = opendir(proc_path);
    if (dir) {
        closedir(dir);
    } else if (ENOENT == errno) {
        fprintf(stderr, "Invalid PID\n");
        return;
    }

    char proc_stat_path[MAX_PATH_LEN + 6];
    sprintf(proc_stat_path, "%s/stat", proc_path);
    FILE *p_stat = fopen(proc_stat_path, "r");
    if (p_stat) {
        // Retrieve data
        int pid;
        char state;
        fscanf(p_stat, "%d %*s %c", &pid, &state);

        // Print retrieved data
        printf("PID -- %d\n", pid);
        printf("Process Status -- %c\n", state);
    } else {
        perror("Error while reading process info");
        return;
    }
    fclose(p_stat);

    char proc_statm_path[MAX_PATH_LEN + 7];
    sprintf(proc_statm_path, "%s/statm", proc_path);
    FILE *p_statm = fopen(proc_statm_path, "r");
    if (p_statm) {
        // Retrieve data
        int proc_size;
        fscanf(p_statm, "%d", &proc_size);

        // Print retrieved data
        printf("Memory -- %d\n", proc_size);
    } else {
        perror("Error while reading process info");
        return;
    }
    fclose(p_statm);

    char proc_exe_path[MAX_PATH_LEN + 4];
    sprintf(proc_exe_path, "%s/exe", proc_path);
    char exe_path[MAX_PATH_LEN];
    ssize_t bytes_written = readlink(proc_exe_path, exe_path, MAX_PATH_LEN);
    if (bytes_written < 0) {
        perror("Error while reading process info");
        return;
    }
    exe_path[bytes_written] = '\0';
    printf("Executable Path -- %s\n", exe_path);
}
