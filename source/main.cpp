#include <stdio.h>
#include "list.hpp"
#include "graph.hpp"


int main() {
    List list = {};

    construct(&list, 16);

    verifier(&list);

    dump(&list);

    destruct(&list);

    printf("List!\n");

    return 0;
}
