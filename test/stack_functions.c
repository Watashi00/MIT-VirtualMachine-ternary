#include <stdio.h>
#include "stack.h"

int push(Stack* stack, Ternary value) {
    if (stack->top >= 100) {
        printf("Stack overflow\n");
        return -1;
    }

    stack->data[stack->top++] = value;
    return 0;
}

int pop(Stack* stack, Ternary* out) {
    if (stack->top <= 0) {
        printf("Stack underflow\n");
        return -1;
    }

    *out = stack->data[--stack->top];
    return 0;
}