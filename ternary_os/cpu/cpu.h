#ifndef CPU_H
#define CPU_H

#include <stddef.h>
#include "../isa/opcodes.h"
#include "../isa/ternary.h"
#include "../mm/stack.h"

typedef struct {
    const int* program;
    size_t program_length;
    size_t pc;
    Stack stack;
} CPU;

void cpu_init(CPU* cpu, const int* program, size_t length);
int cpu_step(CPU* cpu);
int cpu_run(CPU* cpu);

#endif // CPU_H
