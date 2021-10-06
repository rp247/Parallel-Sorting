#ifndef __SORTING_H__
#define __SORTING_H__

#include <inttypes.h>

/* for swapping arr[a] with arr[b] */
extern void swap_elem(uint32_t *e1, uint32_t *e2);

extern uint64_t compares; // for statistics
extern uint64_t moves;

#endif /* __SORTING_H__ */
