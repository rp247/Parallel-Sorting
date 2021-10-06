#include "bubble.h"

#include "sorting.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

/* CREDITS: Based on pseudocode given by the professor in the documentation */
void bubble_sort(uint32_t *A, uint32_t n) {

    bool swapped = true;

    while (swapped) {
        swapped = false;
        for (uint32_t i = 1; i < n; i++) {
            compares++; // next line would always execute if we reach here
            if (A[i] < A[i - 1]) {
                swap_elem(A + i, A + i - 1); // swap A[i] and A[i-1]
                swapped = true;
                moves += 3; // swapping takes 3 moves
            }
        }
        n -= 1; // decrement n (since last element is going to be largest already)
    }
}
