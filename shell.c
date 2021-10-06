#include "shell.h"

#include "gaps.h" // for gaps array
#include "sorting.h"

#include <inttypes.h>
#include <stdio.h>

/* CREDITS: Based on pseudocode given by the professor in the documentation */
void shell_sort(uint32_t *A, uint32_t n) {

    uint32_t temp, j, gap_val; // temp variables used in shell sort

    /* shell sort implementation */
    for (uint32_t gap = 0; gap < GAPS; gap++) {
        gap_val = gaps[gap];

        for (uint32_t i = gap_val; i < n; i++) {
            j = i;
            temp = A[i];
            compares++; // next condition would atleast compare once since j = i = gap_val

            while (j >= gap_val && temp < A[j - gap_val]) {
                A[j] = A[j - gap_val];
                moves++;
                j -= gap_val;
                if (j >= gap_val)
                    compares++; // if j>= gap_val, the while will compare next time
            }

            A[j] = temp;
            moves += 2; // for temp = A[i] and A[j] = temp
        }
    }
}
