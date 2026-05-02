#ifndef STACK_H
#define STACK_H

#include "../isa/ternary.h"

#define STACK_MAX_SIZE 100

typedef struct {
    Ternary data[STACK_MAX_SIZE];
    int top;
} Stack;

void stack_init(Stack* stack);
int stack_push(Stack* stack, Ternary value);
int stack_pop(Stack* stack, Ternary* out);

#endif // STACK_H