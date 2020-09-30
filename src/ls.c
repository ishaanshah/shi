#include "../include/common.h"
#include "../include/constants.h"
#include "../include/ls.h"
#include "../include/types.h"
#include "../include/utils.h"

int filter_hidden(const struct dirent *entry) {
    /* Filter function to filter hidden files */
    return !(entry->d_name[0] == '.');
}

void list_directory(const char *path, const int aflag, const int lflag) {
    /* Print the contents of directory.
     *
     * Args -
     *  path: The path to list the contents of.
     *  aflag: Wether "-a" flag is passed.
     *  lflag: Wether "-l" flag is passed.
     */

    // Retrieve contents of directory
    struct dirent **namelist;
    int num_of_entries;
    if (aflag) {
        num_of_entries = scandir(path, &namelist, NULL, alphasort);
    } else {
        num_of_entries = scandir(path, &namelist, filter_hidden, alphasort);
    }

    if (num_of_entries < 0) {
        perror("");
        exit_status = 1;
        return;
    }

    for (int idx = 0; idx < num_of_entries; idx++) {
        // If "-l" is passed list with details
        if (lflag) {
            char buf[MAX_PATH_LEN];
            strcpy(buf, path);
            strcat(buf, namelist[idx] -> d_name);

            // Get information about the directory
            struct stat st = {0};
            // If stat is unsuccesful, skip the entry
            if (stat(buf, &st) < 0) {
                perror("");
                exit_status = 1;
                continue;
            }

            // Get permissions
            char perm_string[11];
            perm_string[0] = S_ISDIR(st.st_mode) ? 'd' : '-';
            perm_string[1] = st.st_mode & S_IRUSR ? 'r' : '-';
            perm_string[2] = st.st_mode & S_IWUSR ? 'w' : '-';
            perm_string[3] = st.st_mode & S_IXUSR ? 'x' : '-';
            perm_string[4] = st.st_mode & S_IRGRP ? 'r' : '-';
            perm_string[5] = st.st_mode & S_IWGRP ? 'w' : '-';
            perm_string[6] = st.st_mode & S_IXGRP ? 'x' : '-';
            perm_string[7] = st.st_mode & S_IROTH ? 'r' : '-';
            perm_string[8] = st.st_mode & S_IWOTH ? 'w' : '-';
            perm_string[9] = st.st_mode & S_IXOTH ? 'x' : '-';
            perm_string[10] = '\0';
            printf("%s ", perm_string);

            // Get number of hardlinks
            printf("%*lu ", 3, st.st_nlink);

            // Get the owner of file
            printf("%*s ", 15, getpwuid(st.st_uid) -> pw_name);

            // Get the group of the file
            printf("%*s ", 15, getgrgid(st.st_gid) -> gr_name);

            // Get size of the file
            printf("%*ld ", 10, st.st_size);

            // Buffer to store the formatted time
            char time_str[100];
            struct tm *timeptr = localtime(&st.st_mtim.tv_sec);
            strftime(time_str, 100, "%a %b %d %H:%M", timeptr);

            printf("%s ", time_str);
        }
        printf("%s\n", namelist[idx] -> d_name);
        free(namelist[idx]);
    }
    free(namelist);
}

void ls(command c) {
    char path[MAX_PATH_LEN];

    // Fetch and parse the options
    extern int optind;
    extern char *optarg;
    optind = 0;
    int option;
    int aflag = 0;
    int lflag = 0;
    while ((option = getopt(c.argc, c.argv, "al")) != -1) {
        switch (option) {
            case 'a':
               aflag += 1;
               break;
            case 'l':
               lflag += 1;
               break;
            default:
               return;
        }
    }

    // If no argument is provide print contents of current directory
    int diff = c.argc - optind;
    if (diff == 0) {
        list_directory("./", aflag, lflag);
    }

    int arg_idx = optind;
    while (arg_idx < c.argc) {
        // Replace tilde in path if needed
        strcpy(path, c.argv[arg_idx]);
        replace_tilde(path);
        if (diff > 1) {
            printf("%s:\n", path);
        }
        list_directory(path, aflag, lflag);
        if (diff > 1) {
            printf("\n");
        }
        arg_idx += 1;
    }
}
