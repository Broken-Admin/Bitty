#include "main.h"
#include "instructions.h"

// Accumulator
int accumulator = 0b00;
// Memory / RAM
int RAM[4] = {0, 0, 0, 0};
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
            ins_nnd(&accumulator, &operand);
            mnemonic = "nnd";
            break;
        case enum_mov:
            // Perform a movement of an immediate or memory location
            // to the accumulator
            if (~swapbit & 0b01) // If the swapbit is 0, then the operand should be treated as an immedate
            {
                ins_mov(&accumulator, &operand);
            }
            else // Otherwise, swapbit is 1 and the operand should be reference a RAM location
            {
                ins_mov(&accumulator, &RAM[operand]);
            }
            mnemonic = "mov";
            break;
        case enum_swp:
            // Flip the swapbit variable
            ins_swp(&swapbit);
            mnemonic = "swp";
            break;
        case enum_str:
            ins_str(&accumulator, &operand, RAM);
            mnemonic = "str";
            break;
        default:
            printf("There was an unexpected error parsing the opcode %s with operand %s.\n", binarycodes[opcode], binarycodes[operand]);
            break;
        }

        // Output the executed instruction and the current state of the various memory
        printf("Executed instruction - \"%s #0%i\"\n", mnemonic, operand);
        printf("Accumulator - %i, RAM - [%i, %i, %i, %i], Swap Bit - %i\n\n", accumulator, RAM[0], RAM[1], RAM[2], RAM[3], swapbit);
    }
    // Close the opened file
    fclose(ROM);
    return (0);
}