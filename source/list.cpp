#include "list.hpp"


#define ASSERT(condition, message)      \
if (!(condition)) {                     \
    printf("%s", msg);                  \
    return 1;                           \
}


int construct(List *list, size_t size);


int resize(List *list, size_t new_size);


int insert(List *list, int index, int value);


int remove(List *list, int index);


int destruct(List *list);
