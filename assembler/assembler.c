#include "assembler.h"

int main(int argc, char *argv[])
{
    // argv[1] holds the filename to read from
    // argv[2] holds the filename to write to
    if (argc != 3)
    {
        printf("Usage: ./assembler.bin input.bty output.bin\n");
        return (0);
    }

    // input holds the file discriptor for the input file
    input = fopen(argv[1], "r");

    // output hold the file descriptor for the output file
    output = fopen(argv[2], "wb");

    uint8_t notendoffile = 1;
    for (int linenumber = 0; notendoffile; linenumber++)
    {
        // Handle opcode

        // 3 byte buffer
        char *mnemonic = malloc(3);

        // Assign notendoffile to the return value, as if there is an error
        // or end of file is reached, fread returns 0
        notendoffile = fread(mnemonic, 1, 3, input);
        if (!notendoffile) // Check if end of file has been reached
        {
            continue;
        }
        // Opcode
        uint8_t opcode = 0xFF;

        if (strcmp(mnemonic, mnemonics[0]) == 0) // nnd / 0b00
        {
            opcode = nnd;
        }
        else if (strcmp(mnemonic, mnemonics[1]) == 0) // mov / 0b01
        {
            opcode = mov;
        }
        else if (strcmp(mnemonic, mnemonics[2]) == 0) // swp / 0b10
        {
            opcode = swp;
        }
        else if (strcmp(mnemonic, mnemonics[3]) == 0) // str / 0b11
        {
            opcode = str;
        }
        else if (mnemonic[0] == ';') // Check if this line is a comment
        {
            // If line is a comment, skip to the next line and return to top of loop
            char *cchar = malloc(1);
            while (*cchar != '\n') // Move to the next line
            {
                notendoffile = fread(cchar, 1, 1, input);
                if(!notendoffile)
                {
                    break;
                }
            }
            free(cchar);
            continue;
        }
        else
        {
            // An invalid opcode has been reached
            printf("Reached invalid opcode on line %i - \"%s\", skipping.\n", linenumber, mnemonic);
            char *cchar = malloc(1);
            while (cchar[0] != '\n') // Move to the next line
            {
                notendoffile = fread(cchar, 1, 1, input);
                if(!notendoffile)
                {
                    break;
                }
            }
            // Free up allocated memory
            free(cchar);
            continue;
        }

        free(mnemonic);
        // By this point, assume that there is a valid opcode and mnemonic

        // TODO: HANDLE OPERAND
        // Move ahead by one, getting to the start of the operand
        fseek(input, 1, SEEK_CUR);

        // Operand value
        uint8_t operand;

        // Buffer for handling of number
        // The max size for the number string is 3 bytes
        // which could include the type, and 2 binary numbers
        char *unparsed = malloc(3);

        // Handle of number type
        // #dec, %bin
        notendoffile = fread(unparsed, 3, 1, input);

        if (unparsed[0] == '#') // Decimal
        {
            // Handle decimal operand
            int number[3];
            // Attempt to parse the digits of the operand
            // if the digit is invalid, it is assumed
            // to be zero
            // This should be documented somewhere
            number[0] = unparsed[1] - 0x30 > -1 && unparsed[1] - 0x30 < 10 ? unparsed[1] - 0x30 : 0;
            number[1] = unparsed[2] - 0x30 > -1 && unparsed[2] - 0x30 < 10 ? unparsed[2] - 0x30 : 0;
            // Compute the actual number
            number[2] = (number[0] * 10) + (number[1] * 1);
            if (number[2] > 3 || number[2] < 0) // If the number is larger than 3 or less than 0, it cannot be represented by the CPU
            {
                printf("Invalid opcode \"%i\" encountered on line %i, defaulting to zero.\n", number[3], linenumber);
                operand = 0;
            }
            else // Otherwise the operand is correct and should be assigned to operand
            {
                operand = number[2];
            }
        }
        else if (unparsed[0] == '%') // Binary
        {
            // Handle binary operand
            int number[3];

            number[0] = unparsed[1] - 0x30 > -1 && unparsed[1] - 0x30 < 2 ? unparsed[1] - 0x30 : 0;
            number[1] = unparsed[2] - 0x30 > -1 && unparsed[2] - 0x30 < 2 ? unparsed[2] - 0x30 : 0;

            // Compute the actual number
            number[2] = (number[0] * 2) + (number[1] * 1);
            if (number[2] > 3 || number[2] < 0) // If the number is larger than 3 or less than 0, it cannot be represented by the CPU
            {
                printf("binary error.\n");
                printf("Invalid opcode \"%i\" encountered on line %i, defaulting to zero.\n", number[3], linenumber);
                operand = 0;
            }
            else // Otherwise the operand is correct and should be assigned to operand
            {
                operand = number[2];
            }
        }
        else
        {
            // Otherwise, discard the value
            printf("Operand \"%s\" for opcode %i on line %i, is invalid.\n", unparsed, opcode, linenumber);
            char *cchar = malloc(1);
            while (cchar[0] != '\n') // Move to the next line
            {
                notendoffile = fread(cchar, 1, 1, input);
                if(!notendoffile)
                {
                    break;
                }
            }
            // Free up allocated memory
            free(cchar);
            continue;
        }

        // Write opcode and operand to file as half-byte value
        // E.g. "swp %01" would be written to the file as binary 00001001
        // which consists of 0000, the unused top 4 bits,
        // 0b10, the opcode, and the following 2 bit value
        // 0b01 which the operation should be performed using
        int *byte = malloc(1);
        *byte = (opcode << 2) + operand;
        fwrite(byte, 1, 1, output);
        free(byte);

        // Move to the next line, as each line should be exactly 7
        // visible characters, which would be the 3 letter mnemonic,
        // a single space, a 3 alphanumeric string for the operand
        // E.g. "mov %01", "mov" being the operand, then a single
        // space, following last is the operand
        // At the end will be a single invisible newline character
        // which this seek moves past
        fseek(input, 1, SEEK_CUR);
    }
    fclose(input);
    fclose(output);
    return (0);
}