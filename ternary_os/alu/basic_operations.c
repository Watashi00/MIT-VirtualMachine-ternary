#include "operations.h"

int get_max(Ternary a, Ternary b);
int get_t(int i, Ternary v);

Ternary ternary_add(Ternary a, Ternary b) {
    Ternary result;
    int carry = 0;

    int max = get_max(a, b);

    for (int i = 0; i < max; i++) {
        int ta = get_t(i, a);
        int tb = get_t(i, b);

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

    result.size = max;
    return result;
}

int get_max(Ternary a, Ternary b) {
    return (a.size > b.size) ? a.size : b.size;
}

int get_t(int i, Ternary v) {
   return (i < v.size) ? v.trits[i] : 0;
}