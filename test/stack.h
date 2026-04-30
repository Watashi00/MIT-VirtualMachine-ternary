#ifndef STACK_H
#define STACK_H

#include "ternary.h"

typedef struct {
    Ternary data[100];
    int top;
} Stack;

int push(Stack* stack, Ternary value);
int pop(Stack* stack, Ternary* out);

#endif // STACK_H