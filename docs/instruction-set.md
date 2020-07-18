## Caveats
- With a logical NAND, all possible digital logic is possible to replicate, if with extra steps.
- The `swp` bit determines whether the first two instructions - i.e. `nnd` and `mov` - interpret an immediate or address memory
- When the `swp` bit is set, `value` is interpreted as an address to data in RAM
- When the `swp` bit is reset, value is interpreted as an immedaite

## Instructions
- nnd `value` or `0x0v` - Perform a logical NAND with the accumulator and an immediate `value` or RAM data. See caveats.
- mov `value` or `0x1v` - Copy an immediate `value` or data from RAM to the accumulator. See caveats.
- swp or `0x20` - Flip the `swp` bit.
- str value or `0x3v` - Store the accumulator in the RAM memory addressed by `value`.