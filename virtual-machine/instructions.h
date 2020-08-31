#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef instructionsh
#define instructionsh
enum readTypeEnum
{
    imm = 0,
    ram = 1
};

enum instructionEnum
{
    enum_nnd = 0b00,
    enum_mov = 0b01,
    enum_swp = 0b10,
    enum_str = 0b11,
};

// *a, a pointer to the accumulator
// *b, a pointer to the operand
// *a should be the modified variable which persists in most cases
void ins_nnd(int *a, int *b);
void ins_mov(int *a, int *b);
void ins_swp(int *swapbit);
void ins_str(int *a, int *b, int (*RAM)[4], int *bank);
#endif