/**
 * \file
 * \brief List module source
*/

#include <stdio.h>
#include <stdlib.h>
#include "list.hpp"



/// Returns error and prints message on condition fail
#define ASSERT(condition, message, error, ...)                                                      \
if (!(condition)) {                                                                                 \
    printf("%s(%i) in %s\n[%i] %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, error, message);     \
    dump(list, stdout);                                                                             \
    __VA_ARGS__;                                                                                    \
    return error;                                                                                   \
}


/// Returns error on condition fail
#define SIMPLE_ASSERT(condition, message, error, ...)                                               \
if (!(condition)) {                                                                                 \
    return error;                                                                                   \
}


/// Dumps information about list
#define DUMP(list, ...)                                                             \
printf("%s(%i) in %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);                  \
dump(list, stdout);                                                                 \
__VA_ARGS__;


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

    ASSERT(!verifier(list), "Second verification return error", SECOND_CHECK);

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

    ASSERT(!verifier(list), "Second verification return error", SECOND_CHECK);

    return 0;
}


int insert(List *list, int index, int value) {
    ASSERT(!verifier(list), "Can't insert element due to verification fail", -INVALID_ARG);
    ASSERT(index > -1 && index < list -> size, "Wrong index given!", -INVALID_ARG);
    ASSERT(list -> buffer[index].prev != -1, "Insert after not existing element!", -INVALID_ARG);

    int real_index = list -> free;

    list -> free = list -> buffer[list -> free].next;

    list -> buffer[real_index] = {value, list -> buffer[index].next, index};
    list -> buffer[list -> buffer[index].next].prev = real_index;
    list -> buffer[index].next = real_index;

    list -> linear = 0;

    ASSERT(!verifier(list), "Second verification return error", -SECOND_CHECK);

    return real_index;
}


int push_front(List *list, int value) {
    return insert(list, 0, value);
}


int push_back(List *list, int value) {
    return insert(list, list -> buffer[0].prev, value);
}


int remove(List *list, int index) {
    ASSERT(!verifier(list), "Can't remove element due to verification fail", INVALID_ARG);
    ASSERT(index > 0 && index < list -> size, "Wrong index given!", INVALID_ARG);
    ASSERT(list -> buffer[index].prev != -1, "Remove already free element!", INVALID_ARG);

    int next = list -> buffer[index].next, prev = list -> buffer[index].prev;
    list -> buffer[prev].next = next;
    list -> buffer[next].prev = prev;
    list -> buffer[index] = {0xBEEF, list -> free, -1};

    list -> linear = 0;

    list -> free = index;

    ASSERT(!verifier(list), "Second verification return error", SECOND_CHECK);

    return 0;
}


int pop_front(List *list) {
    return remove(list, 0);
}


int pop_back(List *list, int value) {
    return remove(list, list -> buffer[0].prev);
}


int destruct(List *list) {
    ASSERT(!verifier(list), "Can't destruct list due to verification fail", INVALID_ARG);

    free(list -> buffer);
    list -> buffer = nullptr;

    list -> free = 0;

    return 0;
}


int dump(List *list, FILE *output) {
    int error = verifier(list);

    if (error == INVALID_ARG) return INVALID_ARG;

    fprintf(output, "List [%p]\n", list);

    fprintf(output, "%4s%-8s = %i\n", "", "size", list -> size);
    fprintf(output, "%4sbuffer [%p]:\n\n", "", list -> buffer);
    /*
    if (error) return INVALID_ARG;

    fprintf(output, "%4s%-8s = %i\n", "", "head", list -> buffer[0].next);
    fprintf(output, "%4s%-8s = %i\n", "", "tail", list -> buffer[0].prev);
    fprintf(output, "%4s%-8s = %i\n", "", "free", list -> free);

    fprintf(output, "\n%4s%-4s%4s", "", "id", "");
    for(int i = 0; i < list -> size; i++)
        fprintf(output, "%-8i ", i);
    
    fprintf(output, "\n%4s%-4s%4s", "", "data", "");
    for(int i = 0; i < list -> size; i++)
        fprintf(output, "%-8i ", list -> buffer[i].data);
    
    fprintf(output, "\n%4s%-4s%4s", "", "next", "");
    for(int i = 0; i < list -> size; i++)
        fprintf(output, "%-8i ", list -> buffer[i].next);
    
    fprintf(output, "\n%4s%-4s%4s", "", "prev", "");
    for(int i = 0; i < list -> size; i++)
        fprintf(output, "%-8i ", list -> buffer[i].prev);
    fputc('\n', output);
    */

    return 0;
}


int verifier(List *list) {
    SIMPLE_ASSERT(list, "Invalid list pointer!", INVALID_ARG);

    SIMPLE_ASSERT(list -> buffer, "List has invalid buffer!", NULL_BUFFER);

    int id = 0, count = 0;

    for(int i = list -> buffer[0].next; i != 0 && count <= list -> size; i = list -> buffer[i].next, count++) {
        SIMPLE_ASSERT(list -> buffer[list -> buffer[i].prev].next == i, "Wrong prev index!", INV_NEXT_ID);
        SIMPLE_ASSERT(list -> buffer[list -> buffer[i].next].prev == i, "Wrong next index!", INV_PREV_ID);
        
        id = i;
    }

    SIMPLE_ASSERT(id == list -> buffer[0].prev, "Iteration ended before head was reached!", ITER_FAIL);

    SIMPLE_ASSERT(count <= list -> size, "List iterates more than its size! Possible recursion!", RECURSIVE_ID);

    count = 0;

    for(int i = list -> free; i != list -> size && count <= list -> size; i = list -> buffer[i].next, count++) {
        SIMPLE_ASSERT(list -> buffer[i].prev == -1, "Free element prev index is not -1!", INV_FREE);
    }

    SIMPLE_ASSERT(count <= list -> size, "List iterates more than its size! Possible recursion!", RECURSIVE_ID);

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

    ASSERT(!verifier(list), "Second verification return error", SECOND_CHECK);

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
