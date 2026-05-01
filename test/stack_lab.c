#include "../ternary_os/isa/opcodes.h"
#include "../ternary_os/isa/ternary.h"
#include "../ternary_os/alu/operations.h"
#include "stack.h"
#include "stdout.h"

int ternary_to_int(Ternary t); // TODO: Move to ternary.c and implement in ternary.c before all ALU basic operations; TODO Writer: Watashi00 
    //OP_CODE, [trits...]
int program[] = {              // TODO: Remove this test program and replace with valid assembly code (ternary assembler) before all ALU basic operations; TODO Writer: Watashi00
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
                    out_str("Reading trit ");
                    out_int(t.trits[i]);
                    out_str("\n");
                }
                push(stack, t);   
                out_str("Executing PUSH\n");
                break;
            }

            case ADD: {
                Ternary a, b;
                pop(stack, &b);
                pop(stack, &a);
                Ternary result = ternary_add(a, b);
                ternary_print(a);
                ternary_print(b);
                ternary_print(result);
                out_str("Executing ADD\n");
                int result_int = ternary_to_int(result);
                out_str("Result of ADD in integer: ");
                out_int(result_int);
                out_char('\n');
                push(stack, result);
                break;
            }

            case POP: {
                Ternary value;
                pop(stack, &value);
                out_str("Executing POP\n");
                ternary_print(value);
                break;
            }
            case HALT:
                out_str("Halting program execution.\n");
                return;
            default:
                out_str("Unknown opcode: ");
                out_int(opcode);
                out_char('\n');
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



void ternary_print(Ternary t) {
    out_str("(trit= ");
    for (int i = t.size - 1; i >= 0; --i) {
        out_int(t.trits[i]);
        out_char(' ');
    }
    out_str(")\n");
}
