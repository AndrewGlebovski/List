#include <stdio.h>
#include "list.hpp"
#include "graph.hpp"


#define DUMP_DIR "dump/"


int main() {
    List list = {};

    construct(&list, 16);

    FILE *file = fopen(DUMP_DIR"graph.txt", "w");

    for(int i = 0; i < 12; i++)
        insert(&list, i, i + 2);

    insert(&list, 0, 50);
    insert(&list, 12, 150);
    insert(&list, 5, 100);
    remove(&list, 5);
    remove(&list, 8);
    remove(&list, 9);

    verifier(&list);

    generate_file(&list, file);

    fclose(file);

    generate_image("dump/graph.txt", "dump/graph.png");

    dump(&list);

    destruct(&list);

    printf("List!\n");

    return 0;
}
