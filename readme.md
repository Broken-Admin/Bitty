## Bitty, a 2-bit computer
- This is the VM for the Bitty 2-bit Minecraft computer

- Bitty was originally an idea that struck me while idly working with redstone in Minecraft. If I could produce discrete logic gates, I considered it should be possible to build a computer.

#### A basic design

Seeing this idea started in Minecraft, it seems only fair to explain the process I began with.

Beginning with attempts to see if my idea was truly possible, I took to the internet and found that what I have read to be the earliest Minecraft computer was made in late 2010 on YouTube by [theinternetftw](https://www.youtube.com/channel/UCOiL1Gy74gUIsfQj59dDE8w).

After having confirmation my idea was possible, I took tof find a way to store values in memory, I found the piston toggle-latch. I took this idea further, finding a way to procure a rising-edge and falling-edge detector and the "schematic" for a XOR gate.

After these findings, I was able to produce basic memory. Eventually I had a need for a binary decoder for control flow and memory addressing, first finding a way to produce a NOR gate decoder, if sloppily - but eventually finding a cleaner way of doing it which only seems reasonable to do in Minecraft.

After multiple nights with a similar lack of sleep, and much time devoted to pondering possible implementation, I was lead to the point of having memory, memory addressing, control flow, user input, and basic instruction specifications - including a universal logic NAND instruction. Combining these pieces it would be possible to produce a complete Minecraft computer. Which is what I set out to do.

#### Information

- See `docs` directory for specifications
- Bitty does not currently include an assembler and all programs must be written in machine-code, directly to the binary file. A pen and paper or notepad tool is recommended for writing and debugging of programs.