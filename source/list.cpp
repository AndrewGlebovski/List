/**
 * \file
 * \brief List module source
*/

#include <stdio.h>
#include <stdlib.h>
#include "list.hpp"



/// Returns 1 and prints message on condition fail
#define ASSERT(condition, message, error)                                                           \
if (!(condition)) {                                                                                 \
    printf("%s(%i) in %s\n[%i] %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, error, message);     \
    return error;                                                                                   \
}


int construct(List *list, int size) {
    ASSERT(list, "Invalid list pointer!", INVALID_ARG);
    ASSERT(size > 0, "Invalid list size!", INVALID_ARG);

    list -> buffer = (Node *) calloc(size, sizeof(Node));

    ASSERT(list -> buffer, "Failed to allocate list buffer!", ALLOC_FAIL);

    list -> size = size;

    list -> buffer[0] = {0xC0FFEE, 0, 0};

    for(int i = 1; i < size; i++)
        list -> buffer[i] = {0xBEEF, i + 1, -1};

    list -> free = 1;

    return 0;
}


int resize(List *list, int new_size) {
    ASSERT(list, "Invalid list pointer!", INVALID_ARG);
    ASSERT(new_size > 0, "Invalid list size!", INVALID_ARG);
    ASSERT(list -> buffer, "Invalid list buffer!", NULL_BUFFER);

    list -> buffer = (Node *) realloc(list -> buffer, new_size * sizeof(Node));

    ASSERT(list -> buffer, "Failed to reallocate list buffer!", REALLOC_FAIL);

    for(int i = list -> size; i < new_size; i++)
        list -> buffer[i] = {0xBEEF, i + 1, -1};

    list -> size = new_size;

    return 0;
}


int insert(List *list, int index, int value) {
    ASSERT(!verifier(list), "Can't insert element to verification fail", INVALID_ARG);
    ASSERT(index > -1 && index < list -> size, "Wrong index given!", INVALID_ARG);
    ASSERT(list -> buffer[index].prev != -1, "Insert after not existing element!", INVALID_ARG);

    int real_index = list -> free;

    list -> free = list -> buffer[list -> free].next;

    list -> buffer[real_index] = {value, list -> buffer[index].next, index};
    list -> buffer[list -> buffer[index].next].prev = real_index;
    list -> buffer[index].next = real_index;

    list -> linear = 0;

    return real_index;
}


int remove(List *list, int index) {
    ASSERT(!verifier(list), "Can't remove element due to verification fail", INVALID_ARG);
    ASSERT(index > -1 && index < list -> size, "Wrong index given!", INVALID_ARG);
    ASSERT(list -> buffer[index].prev != -1, "Remove already free element!", INVALID_ARG);

    int next = list -> buffer[index].next, prev = list -> buffer[index].prev;
    list -> buffer[prev].next = next;
    list -> buffer[next].prev = prev;
    list -> buffer[index] = {0xBEEF, list -> free, -1};

    list -> linear = 0;

    list -> free = index;

    return 0;
}


int destruct(List *list) {
    ASSERT(!verifier(list), "Can't destruct list due to verification fail", INVALID_ARG);

    free(list -> buffer);
    list -> buffer = nullptr;

    list -> free = 0;

    return 0;
}


int dump(List *list) {
    ASSERT(!verifier(list), "Can't dump list due to verification fail", INVALID_ARG);

    printf("free - %i\n", list -> free);

    printf("id    ");
    for(int i = 0; i < list -> size; i++)
        printf("%-8i ", i);
    
    printf("\ndata  ");
    for(int i = 0; i < list -> size; i++)
        printf("%-8i ", list -> buffer[i].data);
    
    printf("\nnext  ");
    for(int i = 0; i < list -> size; i++)
        printf("%-8i ", list -> buffer[i].next);
    
    printf("\nprev  ");
    for(int i = 0; i < list -> size; i++)
        printf("%-8i ", list -> buffer[i].prev);
    putchar('\n');

    return 0;
}


int verifier(List *list) {
    ASSERT(list, "Invalid list pointer!", INVALID_ARG);

    ASSERT(list -> buffer, "List has invalid buffer!", NULL_BUFFER);

    int id = 0, count = 0;

    for(int i = list -> buffer[0].next; i != 0 && count <= list -> size; i = list -> buffer[i].next, count++) {
        ASSERT(list -> buffer[list -> buffer[i].prev].next == i, "Wrong prev index!", INV_NEXT_ID);
        ASSERT(list -> buffer[list -> buffer[i].next].prev == i, "Wrong next index!", INV_PREV_ID);
        
        id = i;
    }

    ASSERT(id == list -> buffer[0].prev, "Iteration ended before head was reached!", ITER_FAIL);

    ASSERT(count <= list -> size, "List iterates more than its size! Possible recursion!", RECURSIVE_ID);

    count = 0;

    for(int i = list -> free; i != list -> size && count <= list -> size; i = list -> buffer[i].next, count++) {
        ASSERT(list -> buffer[i].prev == -1, "Free element prev index is not -1!", INV_FREE);
    }

    ASSERT(count <= list -> size, "List iterates more than its size! Possible recursion!", RECURSIVE_ID);

    return 0;
}


int linearization(List *list) {
    ASSERT(!verifier(list), "Can't linearize list due to verification fail", INVALID_ARG);

    Node *linear_buffer = (Node *) calloc(list -> size, sizeof(Node));

    int linear_index = 1;

    for(int i = list -> buffer[0].next; i != 0; i = list -> buffer[i].next, linear_index++)
        linear_buffer[linear_index] = {list -> buffer[i].data, linear_index + 1, linear_index - 1};
    
    for(int i = linear_index; i < list -> size; i++)
        linear_buffer[i] = {0xBEEF, i + 1, -1};
    
    free(list -> buffer);

    list -> buffer = linear_buffer;

    list -> buffer[0].next = 1;
    list -> buffer[0].prev = linear_index - 1;
    list -> free = linear_index;

    list -> buffer[linear_index - 1].next = 0;

    list -> linear = 1;

    return 0;
}


int real_index(List *list, int logical_index) {
    ASSERT(!verifier, "Can't get real index due to verification fail", INVALID_ARG);

    if (logical_index == 0) {
        return 0;
    }
    else if (list -> linear) {
        return logical_index;
    }
    else {
        int real_id = list -> buffer[0].next;

        for(int j = 1; j < logical_index; j++)
            real_id = list -> buffer[real_id].next;

        return real_id;
    }
}
