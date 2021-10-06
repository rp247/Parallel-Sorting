#include "queue.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* CREDITS: From lab documentation by professor */
/* stack structure */
struct Queue {
    uint32_t head; // head index
    uint32_t tail; // tail index
    uint32_t size; // size of queue
    uint32_t capacity; // capacity of queue
    int64_t *items; // pointer to array that holds items
};

/* to calculate next postion of head or tail (wrap around pos) */
/* [create a function] idea from Eugene's section */
static inline uint32_t next_pos(uint32_t elem, uint32_t capacity) {
    return (elem + 1) % capacity;
}

/* creates a stack and returns pointer to it */
Queue *queue_create(uint32_t capacity) {
    Queue *q = (Queue *) malloc(sizeof(Queue));

    if (!q)
        return NULL; // if mem can't be allocated

    q->head = 0; // initially head index = 0
    q->tail = 0; // initially tail index = 0
    q->size = 0; // initially size = 0
    q->capacity = capacity; // capacity of queue
    q->items = (int64_t *) calloc(capacity, sizeof(int64_t));

    /* if mem can't be allocated for items */
    if (!q->items) {
        free(q);
        q = NULL;
    }

    return q;
}

/* deletes a queue (frees the memory) */
void queue_delete(Queue **q) {
    if (*q && (*q)->items) {
        free((*q)->items); // free items
        free(*q); // free queue
        *q = NULL; // set queue pointer to null
    }
    return;
}

/* returns true if queue empty, else false */
bool queue_empty(Queue *q) {
    if (!q)
        return true; // no queue
    return q->size == 0; // if size = 0, then true
}

/* returns true if queue full, else false */
bool queue_full(Queue *q) {
    if (!q)
        return true; // no queue
    return q->size == q->capacity; // if size = capacity, then true
}

/* returns size of the queue */
uint32_t queue_size(Queue *q) {
    if (!q)
        return 0; // no queue
    return q->size;
}

/* enqueues an element at the end of the queue*/
bool enqueue(Queue *q, int64_t x) {
    if (queue_full(q))
        return false; // queue already full

    q->items[q->tail] = x; // add to tail
    q->tail = next_pos(q->tail, q->capacity); // move tail one step or wrap around
    q->size++; // increment size

    return true;
}

/* dequeues an element from the front of the queue*/
bool dequeue(Queue *q, int64_t *x) {
    if (queue_empty(q))
        return false; // queue already empty

    *x = q->items[q->head]; // set x to head element
    q->head = next_pos(q->head, q->capacity); // move head one step or wrap around
    q->size--; // decrement size

    return true;
}

/* prints a queue */
void queue_print(Queue *q) {
    if (!q || queue_empty(q))
        return;

    printf("Queue (Head<-Tail): ");

    uint32_t i = q->head;

    /* couldn't print head w/o do-while */
    do {
        printf("%" PRId64 "<-", q->items[i]);
        i = next_pos(i, q->capacity);
    } while (i != q->tail);

    printf("\n");
}
