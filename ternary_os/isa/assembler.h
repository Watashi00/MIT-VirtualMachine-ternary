#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stddef.h>

int parse_assembly_file(const char* path, int** out_program, size_t* out_length);
int read_program_binary(const char* path, int** out_program, size_t* out_length);
void free_program(int* program);
int write_program_binary(const char* path, const int* program, size_t length);

#endif // ASSEMBLER_H
