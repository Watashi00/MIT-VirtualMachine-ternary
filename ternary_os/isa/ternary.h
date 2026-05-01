#ifndef TERNARY_H
#define TERNARY_H

#include <stdint.h>

#define MAX_TRITS 32

typedef int8_t trit; // -1, 0, +1

typedef struct {
    trit trits[MAX_TRITS];
    int size;
} Ternary;

int ternary_to_int(Ternary t);
Ternary ternary_from_int(int value);
Ternary ternary_add(Ternary a, Ternary b);
void ternary_print(Ternary t);

#endif // TERNARY_H