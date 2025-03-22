#ifndef IHEAP_H
#define IHEAP_H

/// @brief Comparison function used in heap operations,
/// @param i the first index
/// @param j the second index
/// @return <0 if arr[i] priors to arr[j], =0 if they are of
/// @return the same priority, >0 if arr[j] priors to arr[i]
/// @return where arr is the array on which index heap is built
typedef int(*cmp_)(int, int);
typedef struct iheap_ iheap;

struct iheap_ {
    int* head;  // pointer to 0th element in heap
    int cnt;    // element counter of heap
    int* hash;  // from element to index in heap
    cmp_ cmp;   // comparison function used in heap operations
};

/// @brief Create an index heap
/// @param heap heap to be created
/// @param size size of the heap
/// @param cmp comparison funnction used in heap operations
void create_iheap(iheap* heap, int size, cmp_ cmp);
/// @brief Push an index into the heap
/// @param heap heap to be operated
/// @param tar index to be pushed
void iheap_push(iheap* heap, int tar);
/// @brief Pop an index out of the heap
/// @param heap heap to be operated
/// @return the popped index
int iheap_pop(iheap* heap);
/// @brief Update the heap after change on an index
/// @param heap heap to be updated
/// @param tar the index on which the array element is changed
void iheap_update(iheap* heap, int tar);
/// @brief Destroy an index heap
/// @param heap heap to be destroied
void destroy_iheap(iheap* heap);

#endif//IHEAP_H