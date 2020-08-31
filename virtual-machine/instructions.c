#include "instructions.h"
// *a, a pointer to the accumulator
// *b, a pointer to the operand
// *a should be the modified variable which persists in most cases

void ins_nnd(int *a, int *b)
{
    int c = *a & *b;
    *a = ~c & 0b11;
}

void ins_mov(int *a, int *b)
{
    *a = *b;
}

// *swpBit, a pointer to the swap bit which is used to decode instructions
void ins_swp(int *swapbit)
{
    *swapbit = !*swapbit;
}

// *ram[], a pointer to the RAM array
// *bank, a pointer to currently selected RAM bank number (0, 3)
void ins_str(int *a, int *b, int (*RAM)[4], int *bank)
{
    // Banks are selected by RAM[3] in every bank

    // If the current operand is storing to RAM[3],
    // select the bank specified by the accumulator
    if (*b == 3)
    {
        *bank = *a;
    }
    // Otherwise store the accumulator
    else 
    {
        RAM[*bank][*b] = *a;
    }
}