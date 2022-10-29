#include <stdio.h>
#include "log.hpp"
#include "list.hpp"
#include "graph.hpp"


#define DUMP_DIR "dump/"


int main() {
    open_log("dump/log.html");

    List list = {};

    construct(&list, 16);

    FILE *file = nullptr;

    // DUMPING 1

    file = fopen(DUMP_DIR"graph1.txt", "w");

    generate_file(&list, file);

    fclose(file);

    generate_image("dump/graph1.txt", "dump/graph1.png");

    DUMP(&list, "graph1.png", fprintf(LOG_FILE, "Dumping 1"));


    for(int i = 0; i < 12; i++)
        push_back(&list, i + 2);

    insert(&list, 0, 50);
    insert(&list, 12, 150);
    insert(&list, 5, 100);
    remove(&list, 5);
    remove(&list, 8);
    remove(&list, 9);

    linearization(&list);

    // DUMPING 2

    file = fopen(DUMP_DIR"graph2.txt", "w");

    generate_file(&list, file);

    fclose(file);

    generate_image("dump/graph2.txt", "dump/graph2.png");

    DUMP(&list, "graph2.png", fprintf(LOG_FILE, "Dumping 2"));


    close_log();

    destruct(&list);

    printf("List!\n");

    return 0;
}
