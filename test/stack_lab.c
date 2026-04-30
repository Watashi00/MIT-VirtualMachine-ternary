#include <stdio.h>
#include "stack.h"
#include "opcodes.h"

void sum(int* a, int* b, int* result);
void stack_complete_test();

int main() {
    program_flux_test();
    return 0;
}

void program_flux_test() {
    int program[] = {
        PUSH, 5,
        PUSH, 10,
        ADD,
        POP,
        HALT
    };
}

void stack_complete_test() {
    Stack stack = { .top = 0 };
    for(int i = 0; i < 100; i++) {
        int j = i * 2;
        printf("i: %d, j: %d\n", i, j);
        push(&stack, j);
    }

    print_stack(&stack);

    int has_prev = 0;
    int prev;
    for(int i = 0; i < 100; i++) {
        int value;
        if (pop(&stack, &value) == -1) {
            printf("Error: Stack underflow\n");
            break;
        }
        if (has_prev) {
            int result;
            sum(&prev, &value, &result);
            printf("Sum of %d and %d is %d\n", prev, value, result);
        }
        prev = value;
        has_prev = 1;
        printf("Popped value: %d\n", value);
    }

    print_stack(&stack);
}

void sum(int* a, int* b, int* result) {
    printf("Summing %d and %d\n", *a, *b);
    *result = *a + *b;
};