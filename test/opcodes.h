#ifndef OPCODES_H
#define OPCODES_H

#define OP_CODE_lIST(x) \
    x(ADD, 0x01) \
    x(SUB, 0x02) \
    x(MUL, 0x03) \
    x(DIV, 0x04) \
    x(PUSH, 0x05) \
    x(POP, 0x06) \
    x(PRINT_STACK, 0x07) \
    x(HALT, 0xFF)

typedef enum {
#define X(name, code) name = code,
    OP_CODE_lIST(X)
#undef X
} Opcode;

#endif // OPCODES_H