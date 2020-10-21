#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

// Mnemonics and opcodes
const char *mnemonics[] = {"nnd", "mov", "swp", "str"};
enum Opcode
{
    nnd = 0b00,
    mov = 0b01,
    swp = 0b10,
    str = 0b11
};

// Binary codes for operands
const char *binary[] = {
    "00",
    "01",
    "10",
    "11"
};