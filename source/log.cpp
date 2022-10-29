#include <stdio.h>
#include "list.hpp"
#include "graph.hpp"
#include "log.hpp"


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


void create_graph_dump(List *list) {
    static int i = 0;

    char dot[FILENAME_MAX] = "", img[FILENAME_MAX] = "";

    sprintf(dot, "dump/graph%i.txt", i);
    sprintf(img, "dump/graph%i.png", i);

    FILE *file = fopen(dot, "w");

    generate_file(list, file);

    fclose(file);

    generate_image(dot, img);

    fprintf(LOG_FILE, "<img src=\"graph%i.png\" alt=\"WTF\" style=\"width: 100%%\">\n", i);

    i++;
}
