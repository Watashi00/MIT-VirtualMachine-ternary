#ifndef STACK_H
#define STACK_H

typedef struct {
    int data[100]; // 100 * 4 bytes = 400 bytes; 0.4 KB
    int top;       // top index of the stack
} Stack;

int push(Stack* stack, int value);
int pop(Stack* stack, int* out);
void print_stack(Stack* stack);

#endif // STACK_H