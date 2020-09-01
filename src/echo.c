#include "../include/common.h"
#include "../include/echo.h"

void echo(command c) {
    for (int arg = 1; arg < c.argc; arg++) {
        printf("%s ", c.argv[arg]);
    }
    printf("\n");
}
