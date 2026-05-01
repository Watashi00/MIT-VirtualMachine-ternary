#include "operations.h"

Ternary ternary_add(Ternary a, Ternary b) {
    Ternary result;
    int carry = 0;

    int max = (a.size > b.size) ? a.size : b.size;

    for (int i = 0; i < max; i++) {
        int ta = (i < a.size) ? a.trits[i] : 0;
        int tb = (i < b.size) ? b.trits[i] : 0;

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