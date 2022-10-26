#include <stdio.h>
#include "list.hpp"
#include "graph.hpp"


int main() {
    List list = {};

    construct(&list, 16);

    for(int i = 0; i < 12; i++)
        insert(&list, i, 0);

    insert(&list, 5, 10);
    insert(&list, 2, 3);

    remove(&list, 4);
    remove(&list, 10);
    remove(&list, 7);

    verifier(&list);

    FILE *file = fopen("graph.txt", "w");

    generate_file(&list, file);

    // printf("%i\n", generate_image());

    dump(&list);

    destruct(&list);

    printf("List!\n");

    return 0;
}
