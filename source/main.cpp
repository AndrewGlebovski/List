#include <stdio.h>
#include "list.hpp"
#include "graph.hpp"
#include "log.hpp"


int main() {
    open_log("dump/log.html");

    List list = {};

    construct(&list, 16);

    FILE *file = nullptr;

    DUMP_IT(&list, fprintf(LOG_FILE, "Constructor result"));

    for(int i = 0; i < 12; i++)
        push_back(&list, i + 2);

    insert(&list, 0, 50);
    insert(&list, 12, 150);
    insert(&list, 5, 100);
    remove(&list, 5);
    remove(&list, 8);
    remove(&list, 9);

    linearization(&list);

    DUMP_IT(&list, fprintf(LOG_FILE, "Linearization result"));

    close_log();

    destruct(&list);

    printf("List!\n");

    return 0;
}
