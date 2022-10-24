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
        list -> buffer[i] = {0xBEEF, (int) i + 1, -1};

    list -> head = 0;
    list -> tail = 0;
    list -> free = 1;

    return 0;
}


int resize(List *list, size_t new_size) {
    ASSERT(list, "Invalid list pointer!");
    ASSERT(new_size > 0, "Invalid list size!");
    ASSERT(list -> buffer, "Invalid list buffer!");

    list -> buffer = (Node *) realloc(list -> buffer, new_size * sizeof(Node));

    ASSERT(list -> buffer, "Failed to reallocate list buffer!");

    for(size_t i = list -> size; i < new_size; i++)
        list -> buffer[i] = {0xBEEF, (int) i + 1, -1};

    list -> size = new_size;

    return 0;
}


int insert(List *list, int index, int value) {
    /*
    ASSERT(list, "Invalid list pointer!");
    ASSERT(list -> buffer, "Invalid list buffer!");
    ASSERT(index > 0, "Invalid index!");
    */

    int real_index = list -> free;

    list -> free = list -> buffer[list -> free].next;

    if (list -> free == (int) list -> size)
        resize(list, list -> size * 2);

    if (list -> tail == 0 && list -> head == 0) {
        list -> buffer[real_index] = {value, 0, 0};
        list -> head = real_index;
        list -> tail = real_index;
    }
    
    else if (index >= list -> tail) {
        list -> buffer[list -> tail].next = real_index;
        list -> buffer[real_index] = {value, 0, list -> tail};
        list -> tail = real_index;
    }

    else if (index < list -> head) {
        list -> buffer[list -> head].prev = real_index;
        list -> buffer[real_index] = {value, list -> head, 0};
        list -> head = real_index;
    }

    else {
        list -> buffer[real_index] = {value, list -> buffer[index].next, index};
        list -> buffer[list -> buffer[index].next].prev = real_index;
        list -> buffer[index].next = real_index;
    }

    return real_index;
}


int remove(List *list, int index) {
    /*
    ASSERT(list, "Invalid list pointer!");
    ASSERT(list -> buffer, "Invalid list buffer!");
    ASSERT(index > 0, "Invalid index!");
    */

    if (list -> tail == 0 && list -> head == 0) {
        return 1;
    }

    else if (index == 0 || list -> buffer[index].prev == -1) {
        return 1;
    }

    else if (index == list -> head) {
        list -> head = list -> buffer[index].next;
        list -> buffer[list -> buffer[index].next].prev = 0;
        list -> buffer[index] = {0xBEEF, list -> free, -1};
    }

    else if (index == list -> tail) {
        list -> tail = list -> buffer[index].prev;
        list -> buffer[list -> buffer[index].prev].next = 0;
        list -> buffer[index] = {0xBEEF, list -> free, -1};
    }

    else {
        int next = list -> buffer[index].next, prev = list -> buffer[index].prev;
        list -> buffer[prev].next = next;
        list -> buffer[next].prev = prev;
        list -> buffer[index] = {0xBEEF, list -> free, -1};
    }

    list -> free = index;

    return 0;
}


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

    printf("head - %i\ntail - %i\nfree - %i\n", list -> head, list -> tail, list -> free);

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
