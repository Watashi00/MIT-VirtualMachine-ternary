#include <stdio.h>
#include "stack.h"
#include "opcodes.h"
#include "ternary.h"

void sum(int* a, int* b, int* result);
void stack_complete_test();
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
                    printf("Executing PUSH %d\n", size);
                }
                break;
            }

            case ADD: {
                trit a, b;
                printf("Executing ADD (%d + %d)\n", a, b);
                break;
            }

            case POP: {
                trit value;
                printf("Executing POP %d\n", value);
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

Ternary ternary_add(Ternary a, Ternary b) {
    Ternary result;
    int carry = 0;

    int max = (a.size > b.size) ? a.size : b.size;

    for (int i = 0; i < MAX_TRITS; i++) {
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

    return result;
}


void sum(int* a, int* b, int* result) {
    printf("Summing %d and %d\n", *a, *b);
    *result = *a + *b;
};