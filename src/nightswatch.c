#include "../include/common.h"
#include "../include/constants.h"
#include "../include/nightswatch.h"
#include "../include/utils.h"

void newborn(int interval) {
    const char path[] = "/proc/loadavg";
    int recent_pid;
    int quit = 0;
    time_t t0;

    // Get latest created pid
    while (!quit) {
        t0 = time(0);
        FILE *load_avg = fopen(path, "r");
        if (!load_avg) {
            perror("nightswatch");
            exit_status = 1;
            break;
        }
        fscanf(load_avg, "%*s %*s %*s %*s %d", &recent_pid);
        printf("%d\n", recent_pid);
        while (1) {
            if (time(0) - t0 >= interval) {
                break;
            }
            // Exit if 'q' is pressed
            if (key_pressed() && getchar() == 'q') {
                quit = 1;
                break;
            }
        }
        fclose(load_avg);
    }
}

void interrupt(int interval) {
    const char path[] = "/proc/interrupts";
    int quit = 0;
    time_t t0;

    char cpu_line[LINE_MAX];
    char interrupt_cnt[LINE_MAX];

    // Get number of keyboard interrupts
    while (!quit) {
        t0 = time(0);
        FILE *interrupts = fopen(path, "r");
        if (!interrupts) {
            perror("nightswatch");
            exit_status = 1;
            break;
        }

        // Store information about CPUs
        fgets(cpu_line, LINE_MAX, interrupts);
        // Skip 2nd line as i8042 is the 3rd one
        fgets(interrupt_cnt, LINE_MAX, interrupts);
        fgets(interrupt_cnt, LINE_MAX, interrupts);

        // Format string correctly
        int i;
        for (i = 0; interrupt_cnt[i] != ':'; i++) {
            interrupt_cnt[i] = ' ';
        }
        interrupt_cnt[i] = ' ';
        while (interrupt_cnt[i] != 'I') {
            i++;
        }
        interrupt_cnt[i] = '\n';
        interrupt_cnt[i+1] = '\0';

        printf("%s%s", cpu_line, interrupt_cnt);
        while (1) {
            if (time(0) - t0 >= interval) {
                break;
            }
            // Exit if 'q' is pressed
            if (key_pressed() && getchar() == 'q') {
                quit = 1;
                break;
            }
        }
        fclose(interrupts);
    }
}

void nightswatch(command c) {
    // Restore Ctrl C handler
    signal(SIGINT, SIG_DFL);

    // Fetch and parse the options
    extern int optind;
    extern int optopt;
    extern char *optarg;
    optind = 0;
    int option;
    int interval = -1;
    while ((option = getopt(c.argc, c.argv, "n:")) != -1) {
        if (option == 'n') {
            interval = strtol(optarg, NULL, 10);
        } else {
            // If argument is not provided, exit
            if (optopt == 'n') {
                exit_status = 1;
                return;
            }
        }
    }

    // Check if provided interval is valid
    if (interval <= 0) {
        fprintf(stderr, "Error: Interval has to be a positive integer\n");
        exit_status = 1;
        return;
    }

    if (optind < c.argc) {
        if (strcmp("newborn", c.argv[optind]) == 0) {
            newborn(interval);
        } else if (strcmp("interrupt", c.argv[optind]) == 0) {
            interrupt(interval);
        } else {
            fprintf(stderr, "Error: Invalid subcommand, choose from \"newborn\" or \"interrupt\"\n");
            exit_status = 1;
        }
    } else {
        fprintf(stderr, "Error: Invalid subcommand, choose from \"newborn\" or \"interrupt\"\n");
        exit_status = 1;
    }

    // Ignore it again
    signal(SIGINT, SIG_IGN);
}
