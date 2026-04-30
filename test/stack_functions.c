#include <stdio.h>
#include "stack.h"

int push(Stack* stack, int value) {
    if (stack->top >= 100) {
        printf("Stack overflow\n");
        return -1;
    }

    stack->data[stack->top++] = value;
    return 0;
}

int pop(Stack* stack, int* out) {
    if (stack->top <= 0) {
        printf("Stack underflow\n");
        return -1;
    }

    *out = stack->data[--stack->top];
    return 0;
}

void print_stack(Stack* stack) {
    printf("Stack (top=%d): ", stack->top);
    for (int i = 0; i < stack->top; i++) {
        printf("%d ", stack->data[i]);
    }
    printf("\n");
}