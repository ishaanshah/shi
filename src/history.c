#include "../include/common.h"
#include "../include/constants.h"
#include "../include/history.h"
#include "../include/types.h"
#include "../include/utils.h"

struct history hist;

void init_history(char *path) {
    /* Initialise the history struct, either by reading from the history file.
     *
     * Args -
     *  path: The path to history file.
     */
    FILE *hist_file = fopen(path, "rb");

    // If file could not be opened, initialise empty structure
    if (!hist_file) {
        hist.index = -1;
        return;
    }

    // Else read the file
    fread(&hist, sizeof(hist), 1, hist_file);

    // Close the file
    fclose(hist_file);
}

void get_history(command c) {
    /* Print the command history.
     *
     * Args -
     *  c: The command struct containing information about the command.
     */
    int cnt = MAX_HISTORY_RTR_SIZE;
    if (c.argc > 1) {
        cnt = strtol(c.argv[1], NULL, 10);
    }

    if (cnt > MAX_HISTORY_RTR_SIZE) {
        fprintf(stderr, "Error: Max number of history entries is 10\n");
        return;
    }
    if (cnt < 0) {
        fprintf(stderr, "Error: Count should be positive number\n");
        return;
    }

    int start_index = (hist.index - cnt + MAX_HISTORY_STR_SIZE) % MAX_HISTORY_STR_SIZE;
    while (hist.index != start_index) {
        printf("%s", hist.history[start_index]);
        start_index = (start_index + 1) % MAX_HISTORY_STR_SIZE;
    }
}

void update_history(char *entry) {
    /* Insert a command in the history struct.
     *
     * Args -
     *  entry: The command to insert into history struct
     */
    hist.index = (hist.index + 1) % MAX_HISTORY_STR_SIZE;
    strcpy(hist.history[hist.index], entry);
}

void save_history(char *path) {
    /* Store the history struct in a file for future reference.
     *
     * Args -
     *  path: The path to history file.
     */
    FILE *hist_file = fopen(path, "wb");

    if (!hist_file) {
        return;
    }

    // Write to the file
    fwrite(&hist, sizeof(hist), 1, hist_file);

    // Close the file
    fclose(hist_file);
}
