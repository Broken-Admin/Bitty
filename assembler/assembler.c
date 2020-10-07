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

    // input holds the file descriptor for the input file
    input = fopen(argv[1], "r");

    // output hold the file descriptor for the output file
    output = fopen(argv[2], "wb");

    char *c_line = NULL;
    size_t linesize = 0;
    size_t bufferSize = 45;

    int linenumber = 0;
    for (;; linenumber++)
    {
        c_line = malloc(bufferSize);
        linesize = bufferSize;

        // getline returns -1 upon end-of-file or error
        // getline will resize provided buffer accordingly
        if (getline(&c_line, &linesize, input) < 0)
        {
            free(c_line);
            break;
        }

        if (c_line == NULL)
        {
            free(c_line);
            break;
        }

        // Handle opcode
        uint8_t opcode = 0xFF;

        char *mnemonic = strtok(c_line, " ");

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
            free(c_line);
            continue;
        }
        else
        {
            // An invalid opcode has been reached
            printf("Reached invalid opcode on line %i - \"%s\", skipping line.\n", linenumber, mnemonic);
            // Move to next line
            free(c_line);
            continue;
        }

        // Operand value
        uint8_t operand;

        // Buffer for handling of number
        // The max size for the number string is 3 bytes
        // which could include the type, and 2 binary numbers
        char *unparsed = strtok(NULL, " ");
        if (unparsed == NULL || strlen(unparsed) < 1)
        {
            printf("There was an error when attempting to parse the opcode of line %i. Skipping line and attempting to continue assembly.\n", linenumber);
            free(c_line);
            continue;
        }

        // Handle of number type
        // #dec, %bin

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
                printf("Invalid opcode \"%i\" encountered on line %i, defaulting to zero.\n", number[2], linenumber);
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
                printf("Invalid opcode \"%i\" encountered on line %i, defaulting to zero.\n", number[2], linenumber);
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
            printf("Skipping line and attempting to continue assembly.\n");
            free(c_line);
            continue;
        }

        // Clear the buffer resized by getline
        free(c_line);

        // Write opcode and operand to file as half-byte value
        // E.g. "swp %01" would be written to the file as binary 00001001
        // which consists of 0000, the unused top 4 bits,
        // 0b10, the opcode, and the following 2 bit value
        // 0b01 which the operation should be performed using
        int *byte = malloc(1);
        *byte = (opcode << 2) + operand;
        fwrite(byte, 1, 1, output);
        free(byte);
    }
    printf("End of file reached or error encountered.\n");
    printf("%i lines parsed.\n", linenumber);
    fclose(input);
    fclose(output);
    return (0);
}