#include "sorting.h" // declaration of extern vars and fucntion

#include "bubble.h"
#include "quick.h"
#include "set.h"
#include "shell.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* to avoid passing as argument again and again to and from helper functions */
static uint32_t print_size = 100;
static uint32_t rand_val = 13371453;

/* extern global vars for statistics */
uint64_t moves = 0;
uint64_t compares = 0;

/* helper (extern) function to swap two elements */
void swap_elem(uint32_t *e1, uint32_t *e2) {
    uint32_t temp = *e1;
    *e1 = *e2;
    *e2 = temp;
}

/* helper function to print an array */
static void print_arr(uint32_t *arr) {
    if (print_size == 0)
        return;
    for (uint32_t i = 0; i < print_size - 1; i++) {
        printf("%13" PRIu32 "%s", arr[i], (i + 1) % 5 ? "" : "\n");
    }
    printf("%13" PRIu32 "\n", arr[print_size - 1]);
}

/* helper function that initializes an array with random() */
static void initialize_array(uint32_t *arr, uint32_t size) {
    srandom(rand_val);
    for (uint32_t i = 0; i < size; i++) {
        arr[i] = (uint32_t) random();
    }
}

/* helper function to run bubblesort */
static void run_bubble(uint32_t *arr, uint32_t arr_size) {

    moves = 0;
    compares = 0; // for statistics
    initialize_array(arr, arr_size);
    bubble_sort(arr, arr_size);

    printf("Bubble Sort\n");
    printf("%" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", arr_size, moves,
        compares);
    print_arr(arr);
}

/* helper function to run bubblesort */
static void run_shell(uint32_t *arr, uint32_t arr_size) {

    moves = 0;
    compares = 0; // for statistics
    initialize_array(arr, arr_size);
    shell_sort(arr, arr_size);

    printf("Shell Sort\n");
    printf("%" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", arr_size, moves,
        compares);
    print_arr(arr);
}

/* helper function to run bubblesort */
static void run_quick_stack(uint32_t *arr, uint32_t arr_size) {

    moves = 0;
    compares = 0;
    initialize_array(arr, arr_size);
    quick_sort_stack(arr, arr_size);

    printf("Quick Sort (Stack)\n");
    printf("%" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", arr_size, moves,
        compares);
    printf("Max stack size: %" PRIu32 "\n", max_stack_size);
    print_arr(arr);
}

/* helper function to run bubblesort */
static void run_quick_queue(uint32_t *arr, uint32_t arr_size) {

    moves = 0;
    compares = 0;
    initialize_array(arr, arr_size); // initialize array
    quick_sort_queue(arr, arr_size);

    printf("Quick Sort (Queue)\n");
    printf("%" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", arr_size, moves,
        compares);
    printf("Max queue size: %" PRIu32 "\n", max_queue_size);
    print_arr(arr);
}

int main(int argc, char **argv) {

    /* usage message (based on the resource executable) */
    char *usage = "Select at least one sort to perform.\n\
SYNOPSIS\n\
    A collection of comparison-based sorting algorithms.\n\n\
USAGE\n\
    ./sorting [-habsqQo] [-n length] [-p elements] [-r seed]\n\n\
OPTIONS\n\
 -h              Display program help and usage.\n\
 -a              Enable all sorts.\n\
 -b              Enable Bubble Sort.\n\
 -s              Enable Shell Sort.\n\
 -q              Enable Quick Sort (Stack).\n\
 -Q              Enable Quick Sort (Queue).\n\
 -n length       Specify number of array elements.\n\
 -p elements     Specify number of elements to print.\n\
 -r seed         Specify random seed.\n\
 -o              Use sorted arrays.\n";

    /* not enough arguments */
    if (argc < 2) {
        fprintf(stderr, "%s", usage);
        return -1;
    }

    uint32_t arr_size = 100; // size of array. default = 100.

    /* for setting flags for the arguments */
    enum flags { All = 0, Bubble, Shell, Qstack, Qqueue };
    Set set = set_empty();

    /* for getopt/arg parsing */
    int c;
    char *optlist = "habsqQn:p:r:";

    /* parsing arguments and adding flags */
    while ((c = getopt(argc, argv, optlist)) != -1) {
        switch (c) {
        case 'h': // print help message and quit
            fprintf(stdout, "%s", usage);
            return 0;
        case 'a': set = set_insert(set, All); break;
        case 'b': set = set_insert(set, Bubble); break;
        case 's': set = set_insert(set, Shell); break;
        case 'q': set = set_insert(set, Qstack); break;
        case 'Q': set = set_insert(set, Qqueue); break;
        case 'n':
            arr_size = atoi(optarg); // get the size
            break;
        case 'p':
            print_size = atoi(optarg); // get the print size
            break;
        case 'r':
            rand_val = atoi(optarg); // get the random value
            break;
        default: fprintf(stderr, "%s", usage); return -1;
        }
    }

    /* no operations selected (we only insert operations so if set != 0 no ops selected)*/
    if (!set) {
        fprintf(stderr, "%s", usage);
        return -1;
    }

    /* array size <= 0 */
    if ((int32_t) arr_size < 1) {
        fprintf(stderr, "Invalid array length.\n");
        return -1;
    }

    print_size = arr_size < print_size ? arr_size : print_size; // array size < print size

    /* decalring array */
    uint32_t *arr = (uint32_t *) calloc(arr_size, sizeof(uint32_t));

    /* failed to allocate memory */
    if (!arr) {
        fprintf(stderr, "Failed to allocate array to sort.\n");
        return -1;
    }

    /* run all sorts */
    if (set_member(set, All)) {
        run_bubble(arr, arr_size);
        run_shell(arr, arr_size);
        run_quick_stack(arr, arr_size);
        run_quick_queue(arr, arr_size);
        if (arr) {
            free(arr); // free memory
            arr = NULL;
        }
        return 0;
    }

    /* bubblesort */
    if (set_member(set, Bubble)) {
        run_bubble(arr, arr_size);
    }

    /* shellsort */
    if (set_member(set, Shell)) {
        run_shell(arr, arr_size);
    }

    /* quicksort (with stack) */
    if (set_member(set, Qstack)) {
        run_quick_stack(arr, arr_size);
    }

    /* quicksort (with queue) */
    if (set_member(set, Qqueue)) {
        run_quick_queue(arr, arr_size);
    }

    /* free array mem */
    if (arr) {
        free(arr);
        arr = NULL;
    }

    return 0; // success :)
}
