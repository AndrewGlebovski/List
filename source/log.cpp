#include <stdio.h>
#include "log.hpp"
#include "list.hpp"


FILE *LOG_FILE = nullptr;


int open_log(const char *filepath) {
    LOG_FILE = fopen(filepath, "w");

    if (!LOG_FILE) {
        printf("Couldn't open file %s as log!\n", filepath);
        return 1;
    }

    return 0;
}


int close_log(void) {
    if (!LOG_FILE) {
        printf("Couldn't close log!\n");
        return 1;
    }

    return 0;
}
