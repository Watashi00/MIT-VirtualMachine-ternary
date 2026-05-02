#include "stack.h"

void stack_init(Stack* stack) {
    stack->top = 0;
}

int stack_push(Stack* stack, Ternary value) {
    if (stack->top >= STACK_MAX_SIZE) {
        return -1;
    }

    stack->data[stack->top++] = value;
    return 0;
}

int stack_pop(Stack* stack, Ternary* out) {
    if (stack->top <= 0) {
        return -1;
    }

    *out = stack->data[--stack->top];
    return 0;
}