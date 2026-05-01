#ifndef OPCODES_H
#define OPCODES_H

#define OP_CODES(x) \
    x(ADD, 0x01) \
    x(SUB, 0x02) \
    x(MUL, 0x03) \
    x(DIV, 0x04) \
    x(MOD, 0x05) \
    x(AND, 0x06) \
    x(OR, 0x07) \
    x(XOR, 0x08) \
    x(NOT, 0x09) \
    x(SHL, 0x0A) \
    x(SHR, 0x0B) \
    x(LOAD, 0x0C) \
    x(STORE, 0x0D) \
    x(JUMP, 0x0E) \
    x(JUMP_IF_ZERO, 0x0F) \
    x(JUMP_IF_NOT_ZERO, 0x10) \
    x(HALT, 0x11) \
    x(NO_OP, 0x12) \
    x(PUSH, 0x13) \
    x(POP, 0x14) \
    x(CALL, 0x15) \
    x(RET, 0x16) \
    x(IN, 0x17) \
    x(OUT, 0x18) \

typedef enum {
#define X(name, code) name,
    OP_CODES(X)
#undef X
} OpCode;


#endif // OPCODES_H