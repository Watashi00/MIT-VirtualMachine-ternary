#include <stdio.h>
#include "stdout.h"

void out_char(char c) {
    putchar(c);
}

void out_int(int value) {
    char buf[16];
    int i = 0;

    if (value == 0) {
        out_char('0');
        return;
    }

    if (value < 0) {
        out_char('-');
        value = -value;
    }

    while (value > 0) {
        buf[i++] = '0' + (value % 10);
        value /= 10;
    }

    while (i--) {
        out_char(buf[i]);
    }
}

void out_str(const char *s) {
    while (*s) {
        out_char(*s++);
    }
}