#include <stddef.h>

#include "cpu.h"
#include "../alu/operations.h"
#include "../drivers/stdout.h"

static int cpu_push(CPU* cpu);
static int cpu_add(CPU* cpu);
static int cpu_pop(CPU* cpu);

void cpu_init(CPU* cpu, const int* program, size_t length) {
    cpu->program = program;
    cpu->program_length = length;
    cpu->pc = 0;
    stack_init(&cpu->stack);
}

int cpu_step(CPU* cpu) {
    if (cpu->pc >= cpu->program_length) {
        out_str("CPU error: end of program without HALT\n");
        return -1;
    }

    int opcode = cpu->program[cpu->pc++];

    switch (opcode) {
        case PUSH:
            return cpu_push(cpu);
        case ADD:
            return cpu_add(cpu);
        case POP:
            return cpu_pop(cpu);
        case HALT:
            out_str("HALT\n");
            return 1;
        default:
            out_str("Unknown opcode: ");
            out_int(opcode);
            out_char('\n');
            return -1;
    }
}

int cpu_run(CPU* cpu) {
    while (1) {
        int result = cpu_step(cpu);
        if (result != 0) {
            return result;
        }
    }
}

static int cpu_push(CPU* cpu) {
    if (cpu->pc >= cpu->program_length) {
        out_str("Program error: missing PUSH operand\n");
        return -1;
    }

    int size = cpu->program[cpu->pc++];
    if (size < 0 || size > MAX_TRITS || cpu->pc + size > cpu->program_length) {
        out_str("Program error: invalid PUSH size\n");
        return -1;
    }

    Ternary value;
    value.size = size;
    for (int i = 0; i < size; i++) {
        value.trits[i] = cpu->program[cpu->pc++];
    }

    if (stack_push(&cpu->stack, value) != 0) {
        out_str("Stack overflow\n");
        return -1;
    }

    out_str("PUSH\n");
    return 0;
}

static int cpu_add(CPU* cpu) {
    Ternary b;
    Ternary a;

    if (stack_pop(&cpu->stack, &b) != 0 || stack_pop(&cpu->stack, &a) != 0) {
        out_str("Stack underflow during ADD\n");
        return -1;
    }

    Ternary result = ternary_add(a, b);
    out_str("ADD\n");
    ternary_print(a);
    ternary_print(b);
    ternary_print(result);

    if (stack_push(&cpu->stack, result) != 0) {
        out_str("Stack overflow\n");
        return -1;
    }

    return 0;
}

static int cpu_pop(CPU* cpu) {
    Ternary value;
    if (stack_pop(&cpu->stack, &value) != 0) {
        out_str("Stack underflow\n");
        return -1;
    }

    out_str("POP\n");
    ternary_print(value);
    return 0;
}
