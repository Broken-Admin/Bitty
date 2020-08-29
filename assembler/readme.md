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

- An C interpreter could possibly be used to convert said assembled file into output suitable for programming into an EEPROM

## TODO
- Possibly add support for 3 letter macros and variables
    - E.g. `&nop nnd %00` could allow `nop` to effectively become `nnd %00` during assembly
    - Would require a rewrite of how opcodes are handled, reading only a single character at first to check if line contains opcode or definition of a macro or variable
    - E.g. `$zro %00` could allow `str zro` to be assembled as `str %00`
    - Possibly requiring an link-list hash-table of variable definitions

- Confirm input file is a bty extension file