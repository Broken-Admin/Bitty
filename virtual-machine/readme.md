## C-Sim, a C implementation of the Bitty virtual machine

- Originally implemented in NodeJs, Bitty has been refactored to C
- Designed to handle binary files produced by the included assembler, it's basic function has been attemptedly well documented
- `str #03` or `str %11` effectively changes to the bank specified by the current value stored in the accumulator 

## Possible modifications to Bitty
    - Design a 2-bit ALU, adding RAM[1] and RAM[2] together, and effectively making RAM[3] a ROM address
    - Other RAM memory locations could be used for various ALU functions or as memory-mapped input/output ports