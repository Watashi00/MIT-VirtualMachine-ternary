CC = gcc
CFLAGS = -I. -Iisa -Imm -Idrivers -Ialu -Isimulator -Icpu
LDFLAGS =

RM = cmd /C del /F /Q

# Object files
OBJ = simulator/stack_lab.o cpu/cpu.o isa/ternary.o isa/assembler.o mm/stack_functions.o drivers/stdout.o alu/basic_operations.o

# Executable name
TARGET = ternary_os

ASSEMBLER_TARGET = assembler.exe
ASSEMBLER_OBJ = tools/assembler/assembler.o isa/assembler.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJ)

simulator/stack_lab.o: simulator/stack_lab.c
	$(CC) $(CFLAGS) -c simulator/stack_lab.c -o simulator/stack_lab.o

cpu/cpu.o: cpu/cpu.c
	$(CC) $(CFLAGS) -c cpu/cpu.c -o cpu/cpu.o

isa/ternary.o: isa/ternary.c
	$(CC) $(CFLAGS) -c isa/ternary.c -o isa/ternary.o

isa/assembler.o: isa/assembler.c
	$(CC) $(CFLAGS) -c isa/assembler.c -o isa/assembler.o

tools/assembler/assembler.o: tools/assembler/assembler.c
	$(CC) $(CFLAGS) -c tools/assembler/assembler.c -o tools/assembler/assembler.o

mm/stack_functions.o: mm/stack_functions.c
	$(CC) $(CFLAGS) -c mm/stack_functions.c -o mm/stack_functions.o

drivers/stdout.o: drivers/stdout.c
	$(CC) $(CFLAGS) -c drivers/stdout.c -o drivers/stdout.o

alu/basic_operations.o: alu/basic_operations.c
	$(CC) $(CFLAGS) -c alu/basic_operations.c -o alu/basic_operations.o

clean:
	-$(RM) $(subst /,\\,$(OBJ) $(TARGET) $(ASSEMBLER_OBJ) $(ASSEMBLER_TARGET))

run: $(TARGET)
	./$(TARGET)

assembler: $(ASSEMBLER_TARGET)

$(ASSEMBLER_TARGET): $(ASSEMBLER_OBJ)
	$(CC) $(ASSEMBLER_OBJ) -o $(ASSEMBLER_TARGET)

.PHONY: all clean run