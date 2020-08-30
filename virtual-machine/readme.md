## C-Sim, a C implementation of the Bitty virtual machine

- Originally implemented in NodeJs, Bitty has been refactored to C
- Designed to handle binary files produced by the included assembler, it's basic function has been attemptedly well documented

## Possible modifications to Bitty
    - Design a 2-bit ALU, adding RAM[1] and RAM[2] together, and effectively making RAM[3] a ROM address
    - RAM[0] could be used for banking, in which writing to it changes the bank currently selected
    - Other RAM memory locations could be used for various ALU functions or as memory-mapped input/output ports