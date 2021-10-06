#include "stack.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* CREDITS: From lab documentation by professor */
/* stack structure */
struct Stack {
    uint32_t top; // index of next empty slot
    uint32_t capacity; // max pushes
    int64_t *items;
};

/* CREDITS: From lab documentation by professor */
/* creates a stack and returns pointer to it */
Stack *stack_create(uint32_t capacity) {

    Stack *s = (Stack *) malloc(sizeof(Stack));

    if (s) {
        s->top = 0; // top = 0
        s->capacity = capacity;
        s->items = (int64_t *) calloc(capacity, sizeof(int64_t)); // change to calloc??

        /* cant allocate memory. free stack */
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

/* CREDITS: From lab documentation by professor */
/* deletes a stack (frees the memory) */
void stack_delete(Stack **s) {
    if (*s && (*s)->items) { // if stack and items not null
        free((*s)->items); // free items
        free(*s); // free stack
        *s = NULL; // update pointer to stack (items unsusable since s null)
    }
    return;
}

/* returns true if stack empty, else false */
bool stack_empty(Stack *s) {
    if (!s)
        return true; // no stack
    return s->top == 0; // if top is 0 then no elements
}

/* returns true if stack full, else false */
bool stack_full(Stack *s) {
    if (!s)
        return true;
    return s->top == s->capacity; // all indexes filled or not
}

/* returns size of the stack */
uint32_t stack_size(Stack *s) {
    if (!s)
        return 0;
    return s->top;
}

/* pushes x on top of stack. returns true if push successful, else false */
bool stack_push(Stack *s, int64_t x) {
    if (!s || stack_full(s))
        return false;
    s->items[s->top] = x; // make top element = x
    s->top++; // increment counter
    return true; // added element
}

/* pops x off of stack. returns true if pop successful, else false. pops value in var pointed by x */
bool stack_pop(Stack *s, int64_t *x) {
    if (!x || !s || stack_empty(s))
        return false; // already empty or null pointer
    s->top--;
    *x = s->items[s->top]; // assign x top value. CREDITS: From lab documentation by professor
    return true;
}

/* prints a stack */
void stack_print(Stack *s) {
    if (!s || stack_empty(s))
        return;

    printf("Stack (Head->Tail): ");
    for (int32_t i = s->top - 1; i > -1; i--) {
        printf("%" PRId64 "->", s->items[i]);
    }
    printf("\n");
}
