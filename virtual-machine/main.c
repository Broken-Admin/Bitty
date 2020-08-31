#include "main.h"
#include "instructions.h"

// Accumulator
int accumulator = 0b00;
// Memory / RAM
// Banks are selected by RAM[3] in every bank
int RAM[4][4] = {0};
// Current RAM bank (0, 3)
int RAMBank = 0;
// Swap Bit
int swapbit = 0;
// 2-bit Binary
char *binarycodes[4] = {
    "00",
    "01",
    "10",
    "11"
};

int
main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./bitty.elf input.bin\n");
        printf("Note, input.bin shoud be an input file produced by the provided assembler in project-root-dir/assembler.\n");
        return (-1);
    }

    // Open the "ROM" input file for the virtual machine
    FILE *ROM = fopen(argv[1], "r");

    // Used by the while-loop, any non-zero value is true
    int isRunning = 1;
    for (int lineNumber; isRunning; lineNumber++)
    {
        // Fetch instruction
        int *buffer = malloc(1);
        isRunning = fread(buffer, 1, 1, ROM);
        if (!isRunning)
        {
            printf("End of ROM.\n");
            break;
        }

        // Handle opcode and operand

        // The opcode is stored in bits 2 and 3, zero-indexed
        // So they must be decoded from the code, which is done by
        // right-shifting all the bits twice - *buffer >> 2
        // moving the instruction to the lowest 2 bits of the
        // binary and performing a bitwise AND with 0b00000000001
        // or 0b11, isolating the instruction

        // The operand is stored in the lowest 2 bits, a bitwise AND
        // with 0b11 effectively isolates the operand
        int opcode = *buffer >> 2 & 0b11;
        int operand = *buffer & 0b11;
        // Free the memory used by the buffer
        free(buffer);
        // The instruction mnemonic
        char *mnemonic = "";
        switch (opcode)
        {
        case enum_nnd:
            // Perform a NAND of the accumulator and operand
            if (~swapbit & 0b01) // If the swapbit is 0, then the operand should be treated as an immediate
            {
                ins_mov(&accumulator, &operand);
            }
            else // Otherwise, swapbit is 1 and the operand should be used as a reference to a RAM location
            {
                ins_nnd(&accumulator, &RAM[RAMBank][operand]);
            }
            mnemonic = "nnd";
            break;
        case enum_mov:
            // Perform a movement of an immediate or memory location
            // to the accumulator
            if (~swapbit & 0b01) // If the swapbit is 0, then the operand should be treated as an immedate
            {
                ins_mov(&accumulator, &operand);
            }
            else // Otherwise, swapbit is 1 and the operand should be used as a reference to a RAM location
            {
                ins_mov(&accumulator, &RAM[RAMBank][operand]);
            }
            mnemonic = "mov";
            break;
        case enum_swp:
            // Flip the swapbit variable
            ins_swp(&swapbit);
            mnemonic = "swp";
            break;
        case enum_str:
            ins_str(&accumulator, &operand, RAM, &RAMBank);
            mnemonic = "str";
            break;
        default:
            printf("There was an unexpected error parsing the opcode %s with operand %s.\n", binarycodes[opcode], binarycodes[operand]);
            break;
        }

        // Output the executed instruction and the current state of the various memory
        printf("Executed instruction - \"%s #0%i\"\n", mnemonic, operand);
        printf("Accumulator - %i, Swap Bit - %i, RAM Bank  - %i\n", accumulator, swapbit, RAMBank);
        // This is ineffecient
        // TODO: Simplify printing RAM
        printf("RAM - [ \n\
        [%i, %i, %i, %i], \n\
        [%i, %i, %i, %i], \n\
        [%i, %i, %i, %i], \n\
        [%i, %i, %i, %i]  \n\
    ]\n",
        RAM[0][0], RAM[0][1], RAM[0][2], RAM[0][3],
        RAM[1][0], RAM[1][1], RAM[1][2], RAM[1][3],
        RAM[2][0], RAM[2][1], RAM[2][2], RAM[2][3],
        RAM[3][0], RAM[3][1], RAM[3][2], RAM[3][3]
        );
    }
    // Close the opened file
    fclose(ROM);
    return (0);
}