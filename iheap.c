// Copyright (C) 2025 Jarry Yang - All rights reserved
//
// You may use, distribute and modify this code under the
// terms of the MIT license, for details, see LICENCE.md
#include <iheap.h>

struct iheap* new_iheap(int size, float(*cmp)(int, int)) {
    struct iheap* heap = malloc(sizeof(struct iheap));
    heap->head = malloc(sizeof(int) * (size + 1));
    heap->hash = malloc(sizeof(int) * size);
    heap->cnt = 0;
    heap->cmp = cmp;
    return heap;
}

void iheap_update(struct iheap* heap, int tar) {
    int i = heap->hash[tar];
    while (i != 1 && heap->cmp(tar, heap->head[i >> 1]) < 0) {
        heap->head[i] = heap->head[i >> 1];
        heap->hash[heap->head[i]] = i;
        i >>= 1;
    }
    heap->head[i] = tar;
    heap->hash[tar] = i;
}

void iheap_push(struct iheap* heap, int tar) {
    int i = ++heap->cnt;
    while (i >> 1 && heap->cmp(tar, heap->head[i >> 1]) < 0) {
        heap->head[i] = heap->head[i >> 1];
        heap->hash[heap->head[i]] = i;
        i >>= 1;
    }
    heap->head[i] = tar;
    heap->hash[tar] = i;
}

int iheap_pop(struct iheap* heap) {
    int popped = heap->head[1];    // popped element
    int last = heap->head[heap->cnt--];
    int i = 1, j = heap->cnt >> 1;
    while (i <= j) {
        int min = i << 1;
        if ((min | 1) <= heap->cnt && heap->cmp(heap->head[min | 1], heap->head[min]) < 0) {
            min |= 1;
        }
        if (heap->cmp(heap->head[min], last) < 0) {
            heap->head[i] = heap->head[min];
            heap->hash[heap->head[i]] = i;
        }
        else  break;
        i = min;
    }
    heap->head[i] = last;
    heap->hash[last] = i;
    return popped;
}

void delete_iheap(struct iheap* heap) {
    if (heap->head) { free(heap->head); heap->head = 0; }
    if (heap->hash) { free(heap->hash); heap->hash = 0; }
}