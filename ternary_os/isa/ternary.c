#include "ternary.h"
#include "../drivers/stdout.h"

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
