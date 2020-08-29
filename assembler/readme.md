## Attiy, a 4-bit assembler
- A makefile which supports both GCC and Clang compilation
    - gcc compilation is default, to compile with clang run `make clang`
    - To clean the directory of output files, run `make clean`

- Compiles a bty extension file into a binary file

- See ./example.bty for a simple example and the corresponding binary

- Supports single-on-line comments

- Comments inline with code are not supported

- Supports 2 operand bases
    - Base-2 / Binary starting with `%`, e.g. `nnd` could have operands `%00`, `%01`, `%10`, or `%11`
    - Base-10 / Decimal starting with `#`, e.g. `nnd` could have operands `#00`, `#01`, `#02`, or `#03`
    - All instructions must have operands, including those which do not make use of said operands 

- Binary is compiled into 8-bit binary codes with a with 4 always-zero leading bits before opcode and operand

- Instructions are assembled to a leading 4 bits which are all zeroes, a 2 bit opcode and a 2 bit operand, the opcode coming before the operand.
    - e.g. `mov #03` assembled to `[0000][01][11]` or `00000111`. The first bracket block (`[0000]`) being the leading 4 bits, the second bracket block (`[01]`) being the opcode for `mov`, the third bracket block (`[11]`) being the binary of the operand 3.

- An C interpreter could possibly be used to convert said assembled file into output suitable for programming into an EEPROM
    - See Caveats section for specification

## Caveats
- Due to the limitations of C, file produced by this assembler would not be compatible with an interpretation of the machine which fetched instructions and opcodes 4 bits at a time from 4-bit word ROM
    - It could also be possible to have a specialized PC, which reads 2 4-bit instructions from the same 8-bit memory location of an 8-bit word ROM, and then increments

- A machine interpretation which fetched a byte / 8 bits from an 8-bit word ROM - discarding the high 4 bits of the bit - would be compatible with the output of this assembler

## TODO
- Possibly add support for 3 letter macros and variables
    - E.g. `&nop nnd %00` could allow `nop` to effectively become `nnd %00` during assembly
    - Would require a rewrite of how opcodes are handled, reading only a single character at first to check if line contains opcode or definition of a macro or variable
    - E.g. `$zro %00` could allow `str zro` to be assembled as `str %00`
    - Possibly requiring an link-list hash-table of variable definitions

- Confirm input file is a bty extension file