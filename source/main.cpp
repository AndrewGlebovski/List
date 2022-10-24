#include <stdio.h>
#include "list.hpp"


int main() {
    List list = {};

    construct(&list, 16);

    dump(&list);

    destruct(&list);

    printf("List!\n");

    return 0;
}
