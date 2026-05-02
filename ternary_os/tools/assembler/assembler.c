#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "isa/assembler.h"

static void print_usage(const char* program_name) {
    fprintf(stderr, "Usage: %s input.w [output.bin]\n", program_name);
    fprintf(stderr, "Assemble .w source into binary program data.\n");
}

static int has_suffix(const char* path, const char* suffix) {
    size_t path_len = strlen(path);
    size_t suffix_len = strlen(suffix);
    if (path_len < suffix_len) {
        return 0;
    }
    return strcasecmp(path + path_len - suffix_len, suffix) == 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        print_usage(argv[0]);
        return 1;
    }

    if (!has_suffix(argv[1], ".w")) {
        fprintf(stderr, "Error: input file must have a .w extension.\n");
        return 1;
    }

    int* program = NULL;
    size_t length = 0;
    if (parse_assembly_file(argv[1], &program, &length) != 0) {
        free_program(program);
        return 1;
    }

    if (argc == 3) {
        if (write_program_binary(argv[2], program, length) != 0) {
            fprintf(stderr, "Error: failed to write output file '%s'.\n", argv[2]);
            free_program(program);
            return 1;
        }
    } else {
        for (size_t i = 0; i < length; i++) {
            printf("%d", program[i]);
            if (i + 1 < length) {
                printf(" ");
            }
        }
        printf("\n");
    }

    free_program(program);
    return 0;
}
