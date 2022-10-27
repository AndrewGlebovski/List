#include <stdio.h>
#include "list.hpp"
#include "graph.hpp"


#define DUMP_DIR "dump/"


int main() {
    List list = {};

    construct(&list, 16);

    verifier(&list);

    FILE *file = fopen(DUMP_DIR"graph.txt", "w");

    generate_file(&list, file);

    dump(&list);

    destruct(&list);

    printf("List!\n");

    return 0;
}
