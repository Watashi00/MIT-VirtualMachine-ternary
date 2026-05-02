#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../cpu/cpu.h"
#include "../isa/assembler.h"

static int has_suffix(const char* path, const char* suffix) {
    size_t path_len = strlen(path);
    size_t suffix_len = strlen(suffix);
    if (path_len < suffix_len) {
        return 0;
    }
    return strcasecmp(path + path_len - suffix_len, suffix) == 0;
}

static void print_usage(const char* program_name) {
    fprintf(stderr, "Usage: %s <program.bin>\n", program_name);
    fprintf(stderr, "Run the ternary VM using a compiled binary program file.\n");
    fprintf(stderr, "Use assembler.exe to convert .w sources into .bin files first.\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        print_usage(argv[0]);
        return 1;
    }

    if (!has_suffix(argv[1], ".bin")) {
        fprintf(stderr, "Error: only .bin compiled program files are supported.\n");
        return 1;
    }

    int* program_data = NULL;
    size_t program_length = 0;
    if (read_program_binary(argv[1], &program_data, &program_length) != 0) {
        free_program(program_data);
        fprintf(stderr, "Error: failed to read binary program file '%s'.\n", argv[1]);
        return 1;
    }

    CPU cpu;
    cpu_init(&cpu, program_data, program_length);
    cpu_run(&cpu);

    free_program(program_data);
    return 0;
}

