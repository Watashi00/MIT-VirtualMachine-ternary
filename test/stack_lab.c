#include <stdio.h>

void sum(int* a, int* b, int* result);
typedef struct {
    int data[100];
    int top;
} Stack;

int main() {
    Stack stack;
    stack.top = 0;
    for(int i = 0; i < 10; i++) {
        int j = i * 2;
        printf("i: %d, j: %d\n", i, j);
        
    }
    return 0;
}

void sum(int* a, int* b, int* result) {
    *result = *a + *b;
};

void stack_push(Stack* stack, int value) {
    if (stack->top < 100) {
        stack->data[stack->top] = value;
        stack->top++;
    } else {
        printf("Stack overflow\n");
    }
};

