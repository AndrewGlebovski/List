#include <stdio.h>
#include "list.hpp"
#include "graph.hpp"


#define DUMP_DIR "dump/"


int main() {
    List list = {};

    construct(&list, 16);

    verifier(&list);

    FILE *file = fopen(DUMP_DIR"graph.txt", "w");

    for(int i = 0; i < 12; i++)
        insert(&list, i, i + 2);

    generate_file(&list, file);

    fclose(file);

    generate_image("dump/graph.txt", "dump/graph.png");

    dump(&list);

    destruct(&list);

    printf("List!\n");

    return 0;
}
