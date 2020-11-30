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
    "11"};

void getBinaryRepresentation(int reg, char *dest)
{
    int twoBit = reg & 0b10;
    char *twoColor = twoBit ? CWHT : CBLK;
    int oneBit = reg & 0b01;
    char *oneColor = oneBit ? CWHT : CBLK;
    char *output = malloc(32);
    sprintf(output, "%s\u2586%s%s\u2586%s", twoColor, SPT, oneColor, CRST);
    // Copy point the destination to the output pointer
    strcpy(dest, output);
    // Free output buffer
    free(output);
}

int main(int argc, char *argv[])
{
    if (argc != 2 && argc != 3 && argc != 4)
    {
        printf("Usage: ./bitty.elf input.bin [binary=0] [slow=0]\n");
        printf("Note, input.bin shoud be an input file produced by the provided assembler in project-root-dir/assembler.\n");
        printf("Note, to enable binary or slow modes, provide 1. E.g. \"./bitty.elf input.bin 1 1\" to enable both binary and slow modes.\n");
        printf("Any number other than 0 will result in mode being enabled, any character will result in modes not being enabled.");
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
            // Free the prepared buffer
            free(buffer);
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
                ins_nnd(&accumulator, &RAM[operand]);
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

        // Binary mode
        if (argc >= 3 && strtol(argv[2], NULL, 10))
        {
            // Note on coloring, a white (on) block conveys a 1
            // a black (off) block conveys a 0, seperators are there
            // for better viewing

            char *binaryString = malloc(32);
            getBinaryRepresentation(accumulator, binaryString);
            // Accumulator displaying
            printf("Accumulator - %s\n", binaryString);
            // RAM displaying
            printf("Ram - [");
            for (int i = 0; i < 4; i++)
            {
                getBinaryRepresentation(RAM[i], binaryString);
                if (i + 1 != 4)
                    printf("%s, ", binaryString);
                else
                    printf("%s", binaryString);
            }
            printf("]\n");
            // Free up the binaryString buffer
            free(binaryString);
        }
        else
        {
            printf("Accumulator - %i, RAM - [%i, %i, %i, %i], Swap Bit - %i\n", accumulator, RAM[0], RAM[1], RAM[2], RAM[3], swapbit);
        }
        // Slow mode
        if (argc == 4 && strtol(argv[3], NULL, 10))
        {
            printf("Press enter to proceed to next execution step.\n");
            // Wait for user key
            getchar();
        }
        // Trailing newline
        printf("\n");
    }
    // Close the opened file
    fclose(ROM);
    return (0);
}