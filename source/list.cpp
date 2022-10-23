#include <stdio.h>
#include <stdlib.h>
#include "list.hpp"


#define ASSERT(condition, message)      \
if (!(condition)) {                     \
    printf("%s\n", message);            \
    return 1;                           \
}


int construct(List *list, size_t size) {
    ASSERT(list, "Invalid list pointer!");
    ASSERT(size > 0, "Invalid list size!");

    list -> buffer = (Node *) calloc(size, sizeof(Node));

    ASSERT(list -> buffer, "Failed to allocate list buffer!");

    list -> size = size;

    list -> buffer[0] = {0xC0FFEE, 0, 0};

    for(size_t i = 1; i < size; i++)
        list -> buffer[i] = {0xBEEF, -1, -1};

    list -> head = 1;
    list -> tail = 1;

    return 0;
}


int resize(List *list, size_t new_size) {
    ASSERT(list, "Invalid list pointer!");
    ASSERT(new_size > 0, "Invalid list size!");
    ASSERT(list -> buffer, "Invalid list buffer!");

    list -> buffer = (Node *) realloc(list -> buffer, new_size * sizeof(Node));

    ASSERT(list -> buffer, "Failed to reallocate list buffer!");

    for(size_t i = list -> size; i < new_size; i++)
        list -> buffer[i] = {0xBEEF, -1, -1};

    list -> size = new_size;

    return 0;
}


int insert(List *list, int index, int value);


int remove(List *list, int index);


int destruct(List *list) {
    ASSERT(list, "Invalid list pointer!");
    ASSERT(list -> buffer, "Invalid list buffer pointer!");

    free(list -> buffer);
    list -> buffer = nullptr;

    list -> head = 0;
    list -> tail = 0;

    return 0;
}


int dump(List *list) {
    ASSERT(list, "Invalid list pointer!");
    ASSERT(list -> buffer, "Invalid list buffer pointer!");

    printf("id    ");
    for(size_t i = 0; i < list -> size; i++)
        printf("%-8lli ", i);
    
    printf("\ndata  ");
    for(size_t i = 0; i < list -> size; i++)
        printf("%-8i ", list -> buffer[i].data);
    
    printf("\nnext  ");
    for(size_t i = 0; i < list -> size; i++)
        printf("%-8i ", list -> buffer[i].next);
    
    printf("\nprev  ");
    for(size_t i = 0; i < list -> size; i++)
        printf("%-8i ", list -> buffer[i].prev);
    putchar('\n');

    return 0;
}
