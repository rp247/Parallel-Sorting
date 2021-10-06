#include "quick.h"

#include "queue.h"
#include "sorting.h"
#include "stack.h"

#include <inttypes.h>
#include <stdio.h>

#define MAX(a, b) (a > b ? a : b) // used for max stack and queue size

uint32_t max_stack_size; // extern var for statistics
uint32_t max_queue_size;

/* CREDITS: Based on pseudocode given by the professor in the documentation */
static int64_t partition(uint32_t *arr, int64_t low, int64_t high) {
    uint32_t pivot = arr[low + ((high - low) / 2)];
    int64_t i = low - 1;
    int64_t j = high + 1;

    while (i < j) {

        do {
            i++;
            compares++;
        } while (arr[i] < pivot); // until finds a elements bigger than pivot

        do {
            j--;
            compares++;
        } while (arr[j] > pivot); // find one less than pivot

        /* swap only if low < high */
        if (i < j) {
            swap_elem(arr + i, arr + j); // swap arr[i] and arr[j]
            moves += 3;
        }
    }

    return j; // return new pivot
}

/* CREDITS: Based on pseudocode given by the professor in the documentation */
void quick_sort_stack(uint32_t *A, uint32_t n) {

    int64_t pivot;
    int64_t low = 0;
    int64_t high = n - 1;

    Stack *st = stack_create(n); // create a stack (won't need more mem than no. of elements)

    /* mem cannot be allocated */
    if (!st) {
        fprintf(stderr, "Failed to allocate memory for stack.\n");
        return;
    }

    stack_push(st, low);
    max_stack_size++; // update max stack size. (atleast one since 0 is invalid length)

    if (stack_push(st, high)) { // push high to stack.
        max_stack_size++; // update if it can be pushed
    }

    while (stack_size(st) != 0) {
        /* popping empty stack returns false and is ignored (partition loop won't continue) */
        stack_pop(st, &high);
        stack_pop(st, &low);

        pivot = partition(A, low, high);

        if (low < pivot) { // low < pivot then low = low, high = pivot
            stack_push(st, low);
            stack_push(st, pivot);
        }

        if (high > pivot + 1) { // high > pivot then low = pivot+1, high = high
            stack_push(st, pivot + 1);
            stack_push(st, high);
        }
        max_stack_size
            = MAX(max_stack_size, stack_size(st)); // update max stack size (only after pushing)
    }

    stack_delete(&st); // free memory
}

/* CREDITS: Based on pseudocode given by the professor in the documentation */
void quick_sort_queue(uint32_t *A, uint32_t n) {

    int64_t pivot; // to store pivot after partition
    int64_t low = 0;
    int64_t high = (int64_t) n - 1;

    Queue *q = queue_create(n); // won't need more mem

    /* malloc failed */
    if (!q) {
        fprintf(stderr, "Failed to allocate memory for queue.\n");
        return;
    }

    enqueue(q, low);
    max_queue_size++;

    if (enqueue(q, high)) {
        max_queue_size++; // only update if it can be pushed (not possible if arr size == 1)
    }

    while (queue_size(q) != 0) {
        /* dequeing empty queue returns false and is ignored (partition loop won't continue) */
        dequeue(q, &low);
        dequeue(q, &high);

        pivot = partition(A, low, high);

        if (low < pivot) { // low < pivot then low = low, high = pivot
            enqueue(q, low);
            enqueue(q, pivot);
        }

        if (high > pivot + 1) { // high > pivot then low = pivot+1, high = high
            enqueue(q, pivot + 1);
            enqueue(q, high);
        }
        max_queue_size
            = MAX(max_queue_size, queue_size(q)); // update max size (no need to update after deque)
    }

    queue_delete(&q); // free mem
}
