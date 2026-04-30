#include <stdio.h>
#include "stack.h"
#include "opcodes.h"
#include "ternary.h"

void sum(int* a, int* b, int* result);
void stack_complete_test();
int ternary_to_int(Ternary t);
    //OP_CODE, [trits...]
int program[] = {
    PUSH, 3, 1, 0, 1,
    PUSH, 2, 1, -1,
    ADD,
    POP,
    HALT
};
void program_flux_test(int* program, Stack* stack);


Stack stack = { .top = 0 };

int main() {
    program_flux_test(program, &stack);
    return 0;
}

void program_flux_test(int* program, Stack* stack) {
    int pc = 0;

    while (1) {
        int opcode = program[pc++];
        switch (opcode) {
            case PUSH: {
                int size = program[pc++];

                Ternary t;
                t.size = size;
                for (int i = 0; i < size; i++) {
                    t.trits[i] = program[pc++];
                    printf("Reading trit %d\n", t.trits[i]);
                }
                push(stack, t);   
                printf("Executing PUSH %d\n", size);
                break;
            }

            case ADD: {
                Ternary a, b;
                pop(stack, &b);
                pop(stack, &a);
                Ternary result = ternary_add(a, b);
                printf("Executing ADD\n");
                int result_int = ternary_to_int(result);
                printf("Result of addition: %d\n", result_int);
                push(stack, result);
                break;
            }

            case POP: {
                Ternary value;
                pop(stack, &value);
                printf("Executing POP\n");
                ternary_print(value);
                break;
            }
            case HALT:
                printf("Halting program execution.\n");
                return;
            default:
                printf("Unknown opcode: 0x%02X\n", opcode);
                return;
        }
    }
}

Ternary ternary_from_int(int value) {
    Ternary t;
    t.size = 0;

    while (value != 0 && t.size < MAX_TRITS) {
        int rem = value % 3;
        value /= 3;
        if (rem == 2) {
            rem = -1;
            value += 1;
        }
        t.trits[t.size++] = rem;
    }

    return t;
}

int ternary_to_int(Ternary t) {
    int result = 0;
    int power = 1;
    for (int i = 0; i < t.size; i++) {
        result += t.trits[i] * power;
        power *= 3;
    }
    return result;
}

Ternary ternary_add(Ternary a, Ternary b) {
    Ternary result;
    int carry = 0;

    int max = (a.size > b.size) ? a.size : b.size;

    for (int i = 0; i < max; i++) {
        int ta = (i < a.size) ? a.trits[i] : 0;
        int tb = (i < b.size) ? b.trits[i] : 0;

        int sum = ta + tb + carry;

        if (sum > 1) {
            result.trits[i] = sum - 3;
            carry = 1;
        } else if (sum < -1) {
            result.trits[i] = sum + 3;
            carry = -1;
        } else {
            result.trits[i] = sum;
            carry = 0;
        }
    }

    if (carry != 0) {
        result.trits[max++] = carry;
    }

    result.size = max;
    return result;
}

void ternary_print(Ternary t) {
    printf("(trit= ");
    for (int i = t.size - 1; i >= 0; --i) {
        printf("%d ", t.trits[i]);
    }
    printf(")\n");
}


void sum(int* a, int* b, int* result) {
    printf("Summing %d and %d\n", *a, *b);
    *result = *a + *b;
};