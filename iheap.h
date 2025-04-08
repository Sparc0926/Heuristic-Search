// Copyright (C) 2025 Jarry Yang - All rights reserved
//
// You may use, distribute and modify this code under the
// terms of the MIT license, for details, see LICENCE.md
#ifndef IHEAP_H
#define IHEAP_H

#include <stdlib.h>

struct iheap {
    int* head;               // pointer to 0th element in heap
    int cnt;                 // element counter of heap
    int* hash;               // from element to index in heap
    float(*cmp)(int, int);   // comparison function used in heap operations
};

/// @brief create an index heap
/// @param size size of the heap
/// @param cmp comparison function used in heap operations
/// @return pointer to iheap created
struct iheap* new_iheap(int size, float(*cmp)(int, int));
/// @brief push an index into the heap
/// @param heap heap to be operated
/// @param tar index to be pushed
void iheap_push(struct iheap* heap, int tar);
/// @brief pop an index out of the heap
/// @param heap heap to be operated
/// @return the popped index
int iheap_pop(struct iheap* heap);
/// @brief update the heap after change on an index
/// @param heap heap to be updated
/// @param tar the index on which the array element is changed
void iheap_update(struct iheap* heap, int tar);
/// @brief destroy an index heap
/// @param heap heap to be destroied
void delete_iheap(struct iheap* heap);

#endif//IHEAP_H