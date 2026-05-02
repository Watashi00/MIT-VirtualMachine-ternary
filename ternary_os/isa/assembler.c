#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "assembler.h"
#include "opcodes.h"
#include "ternary.h"

#define INITIAL_PROGRAM_CAPACITY 128

static const char* skip_whitespace(const char* s) {
    while (*s && isspace((unsigned char)*s)) {
        s++;
    }
    return s;
}

static int parse_int_token(const char* token, int* out_value) {
    char* end;
    long value = strtol(token, &end, 0);
    if (*token == '\0' || *end != '\0') {
        return -1;
    }
    if (value < INT32_MIN || value > INT32_MAX) {
        return -1;
    }
    *out_value = (int)value;
    return 0;
}

static int parse_opcode_token(const char* token, int* out_opcode) {
#define X(name, code) if (strcasecmp(token, #name) == 0) { *out_opcode = code; return 0; }
    OP_CODES(X)
#undef X
    return -1;
}

static char* read_line(FILE* file, size_t* length) {
    size_t cap = 256;
    size_t len = 0;
    char* buffer = malloc(cap);
    if (!buffer) {
        return NULL;
    }

    int c;
    while ((c = fgetc(file)) != EOF) {
        if (len + 1 >= cap) {
            cap *= 2;
            char* next = realloc(buffer, cap);
            if (!next) {
                free(buffer);
                return NULL;
            }
            buffer = next;
        }

        buffer[len++] = (char)c;
        if (c == '\n') {
            break;
        }
    }

    if (len == 0 && c == EOF) {
        free(buffer);
        return NULL;
    }

    buffer[len] = '\0';
    if (length) {
        *length = len;
    }
    return buffer;
}

static int ensure_capacity(int** program, size_t* capacity, size_t min_capacity) {
    if (*capacity >= min_capacity) {
        return 0;
    }
    size_t new_capacity = (*capacity == 0) ? INITIAL_PROGRAM_CAPACITY : *capacity * 2;
    while (new_capacity < min_capacity) {
        new_capacity *= 2;
    }
    int* next = realloc(*program, new_capacity * sizeof(int));
    if (!next) {
        return -1;
    }
    *program = next;
    *capacity = new_capacity;
    return 0;
}

static int append_token(int** program, size_t* length, size_t* capacity, int value) {
    if (ensure_capacity(program, capacity, *length + 1) != 0) {
        return -1;
    }
    (*program)[(*length)++] = value;
    return 0;
}

int parse_assembly_file(const char* path, int** out_program, size_t* out_length) {
    if (!path || !out_program || !out_length) {
        return -1;
    }

    FILE* file = fopen(path, "r");
    if (!file) {
        return -1;
    }

    int* program = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t line_number = 0;
    char* line = NULL;

    while ((line = read_line(file, NULL)) != NULL) {
        line_number++;
        char* text = line;
        text = (char*)skip_whitespace(text);

        if (*text == '\0' || *text == ';' || *text == '#' || (text[0] == '/' && text[1] == '/')) {
            free(line);
            continue;
        }

        char* token = strtok(text, " \t\r\n");
        if (!token) {
            free(line);
            continue;
        }

        int opcode;
        if (parse_opcode_token(token, &opcode) != 0) {
            fprintf(stderr, "Assembler error: unknown opcode '%s' on line %zu\n", token, line_number);
            free(line);
            free(program);
            fclose(file);
            return -1;
        }

        if (append_token(&program, &length, &capacity, opcode) != 0) {
            free(line);
            free(program);
            fclose(file);
            return -1;
        }

        if (opcode == PUSH) {
            char* size_token = strtok(NULL, " \t\r\n");
            if (!size_token) {
                fprintf(stderr, "Assembler error: missing PUSH size on line %zu\n", line_number);
                free(line);
                free(program);
                fclose(file);
                return -1;
            }

            int size;
            if (parse_int_token(size_token, &size) != 0 || size < 0 || size > MAX_TRITS) {
                fprintf(stderr, "Assembler error: invalid PUSH size '%s' on line %zu\n", size_token, line_number);
                free(line);
                free(program);
                fclose(file);
                return -1;
            }

            if (append_token(&program, &length, &capacity, size) != 0) {
                free(line);
                free(program);
                fclose(file);
                return -1;
            }

            for (int i = 0; i < size; i++) {
                char* trit_token = strtok(NULL, " \t\r\n");
                if (!trit_token) {
                    fprintf(stderr, "Assembler error: missing trit %d for PUSH on line %zu\n", i + 1, line_number);
                    free(line);
                    free(program);
                    fclose(file);
                    return -1;
                }

                int trit;
                if (parse_int_token(trit_token, &trit) != 0 || trit < -1 || trit > 1) {
                    fprintf(stderr, "Assembler error: invalid trit '%s' on line %zu\n", trit_token, line_number);
                    free(line);
                    free(program);
                    fclose(file);
                    return -1;
                }

                if (append_token(&program, &length, &capacity, trit) != 0) {
                    free(line);
                    free(program);
                    fclose(file);
                    return -1;
                }
            }
        }

        free(line);
    }

    fclose(file);
    *out_program = program;
    *out_length = length;
    return 0;
}

void free_program(int* program) {
    free(program);
}

int read_program_binary(const char* path, int** out_program, size_t* out_length) {
    if (!path || !out_program || !out_length) {
        return -1;
    }

    FILE* file = fopen(path, "rb");
    if (!file) {
        return -1;
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return -1;
    }

    long file_size = ftell(file);
    if (file_size < 0 || (file_size % sizeof(int32_t)) != 0) {
        fclose(file);
        return -1;
    }

    if (fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        return -1;
    }

    size_t length = (size_t)file_size / sizeof(int32_t);
    int32_t* buffer = malloc(length * sizeof(int32_t));
    if (!buffer) {
        fclose(file);
        return -1;
    }

    if (fread(buffer, sizeof(int32_t), length, file) != length) {
        free(buffer);
        fclose(file);
        return -1;
    }

    fclose(file);

    int* program = malloc(length * sizeof(int));
    if (!program) {
        free(buffer);
        return -1;
    }

    for (size_t i = 0; i < length; i++) {
        program[i] = (int)buffer[i];
    }

    free(buffer);
    *out_program = program;
    *out_length = length;
    return 0;
}

int write_program_binary(const char* path, const int* program, size_t length) {
    if (!path || !program) {
        return -1;
    }

    FILE* file = fopen(path, "wb");
    if (!file) {
        return -1;
    }

    for (size_t i = 0; i < length; i++) {
        int32_t value = (int32_t)program[i];
        if (fwrite(&value, sizeof(value), 1, file) != 1) {
            fclose(file);
            return -1;
        }
    }

    fclose(file);
    return 0;
}
