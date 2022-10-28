/**
 * \file
 * \brief List module header
*/


typedef enum {
    INVALID_ARG  =  1,       ///< Function get invalid argument
    INVALID_PTR  =  2,       ///< Function get invalid pointer
    NULL_BUFFER  =  3,       ///< List has null buffer
    INV_NEXT_ID  =  4,       ///< Element next index is wrong
    INV_PREV_ID  =  5,       ///< Element previous index is wrong
    ITER_FAIL    =  6,       ///< Logical list iteration end before tail
    RECURSIVE_ID =  7,       ///< Infinite iteration
    ALLOC_FAIL   =  8,       ///< Failed to allocate memory
    REALLOC_FAIL =  9,       ///< Failed to reallocate memory
    INV_FREE     = 10,       ///< Free element has prev = -1
    SECOND_CHECK = 11,       ///< Function second returns error
} ERROR_CODES;


/// Contains all information about element
typedef struct {
    int data = 0;           ///< element value
    int next = 0;           ///< next element index
    int prev = 0;           ///< previous element index
} Node;


/// Ultimate data structure
typedef struct {
    Node *buffer = nullptr;         ///< Array of nodes
    int free = 0;                   ///< First empty node index
    int size = 0;                   ///< List size
    int linear = 1;                 ///< Non zero value means that list is sorted (linearized)
} List;


/**
 * \brief List constructor
 * \param [out] list Not allocated or free list
 * \param [in]  size Specifies buffer size
 * \return Non zero value means error
*/
int construct(List *list, int size);


/**
 * \brief Resizes already allocated list  
 * \param [out] list This list buffer will be reallocated and filled with poison value
 * \param [in]  new_size Specifies buffer new size
 * \return Non zero value means error
*/
int resize(List *list, int new_size);


/**
 * \brief Inserts element in list
 * \param [out] list Allocated list
 * \param [in]  index Element will be inserted after this index
 * \param [in]  value New element will store this value
 * \return Real index of new element in buffer. Please, store it to improve perfomance of your program
*/
[[nodiscard]] int insert(List *list, int index, int value);


/**
 * \brief Removes element from list
 * \param [out] list Allocated list
 * \param [in]  index Actual index in buffer
 * \warning Index must be real, not logical (if you don't have real index, use real_index())
 * \return Non zero value means error
*/
int remove(List *list, int index);


/**
 * \brief List descructor
 * \param [out] list Allocated list
 * \return Non zero value means error
*/
int destruct(List *list);


/**
 * \brief Prints list info
 * \param [in] list Allocated list
 * \param [in] output Output file 
 * \return Non zero value means error
*/
int dump(List *list, FILE * output);


/**
 * \brief Checks list for mistakes
 * \param [in] list Allocated list
 * \return Non zero value means error
*/
int verifier(List *list);


/**
 * \brief Sorts list in logical order
 * \param [out] list Allocated list
 * \return Non zero value means error
*/
int linearization(List *list);


/**
 * \brief Gets element real index in buffer
 * \param [out] list Allocated list
 * \param [in]  logical_index Element index in logical order
 * \return Real index in buffer
*/
int real_index(List *list, int logical_index);


/**
 * \brief Pushes value to list front
 * \param [out] list Allocated list
 * \param [in]  value New element will store this value
 * \return Real index of new element in buffer. Please, store it to improve perfomance of your program
*/
[[nodiscard]] int push_front(List *list, int value);


/**
 * \brief Pushes value to list back
 * \param [out] list Allocated list
 * \param [in]  value New element will store this value
 * \return Real index of new element in buffer. Please, store it to improve perfomance of your program
*/
[[nodiscard]] int push_back(List *list, int value);


/**
 * \brief Removes front element from list
 * \param [out] list Allocated list
 * \return Non zero value means error
*/
int pop_front(List *list);


/**
 * \brief Removes back element from list
 * \param [out] list Allocated list
 * \return Non zero value means error
*/
int pop_back(List *list, int value);
