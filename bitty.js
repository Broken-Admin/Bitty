const fs = require("fs");

// Accumulator

class accu {
    val = 0b00;
};

accumulator = new accu;

// RAM

class ram {
    memory = Array(4); // Only 4 addresses are possible with 2 bits
};

RAM = new ram;
RAM.memory = [0,0,0,0];

// Instructions

class opcodes {
    nnd = 0b00; // Logical NAND
    mov = 0b01; // For moving of values into the accumulator
    swp = 0b10; // For changing the way input values are handled for the above instructions
    str = 0b11; // For storing values into RAM
};

instructions_codes = new opcodes;

class operation_functions {
    nnd(val) {
        let c;
        // If the bit is set
        if(swp_bit && 0b1) {
            // Perform a logical AND of the accumulator and the address of the value pointed to
            // by the first 2 bits of val
            c = accumulator.val & RAM.memory[val & 0b11];
        }
        // If the bit is not set
        else {
            // Perform a logical AND of the accumulator and the value of the first 2 bits
            // of val
            c = accumulator.val & (val & 0b11);
        }
        let d = ~c & 0b11; // Get the logical NOT for only 2 bits, exclude extra bits
        accumulator.val = d & 0b11; // Store those bits in the accumulator
        return;
    }
    mov(val) {
        // If the bit is set
        if(swp_bit && 0b1) {
            // Move the value at the RAM address (val & 0b11) -
            // i.e. the value addressed by the first 2 bits of
            // val
            accumulator.val = RAM.memory[val & 0b11] & 0b11;
        }
        // If the bit is not set
        else {
            // Move the value of the first 2 bits of val into
            // the accumulator
            accumulator.val = val & 0b11;
        }
        return;
    }
    swp(val) {
        // Flip the bit
        swp_bit = ~swp_bit & 0b1;
    }
    str(val) {
        // Store the value of the first 2 bits of the accumulator
        // at the address specified by the first 2 bits of val
        RAM.memory[val & 0b11] = accumulator.val & 0b11;
    }
};

instruction_functions = new operation_functions;

// When 0, use input value as an immediate
// When 1, use input value as an address
swp_bit = 0b0;

// ROM / Input

class rom {
    // The user will specify a file buffer to open at a later time
    file = [0, 1];
    // Program Counter
    pc = 0;
};

ROM = new rom;

// Check argument count
if(process.argv.length != 3) {
    console.log("Usage: node bitty.js [rom filename]");
    process.exit(1);
}

// Main program

ROM.pc = 0;

ROM.file = fs.readFileSync(process.argv[2]);

// Main loop
// Loop while the program counter has not reached the end of file
while(ROM.pc < ROM.file.length) {
    // Read instruction from file
    c_byte = ROM.file.readInt8(ROM.pc);
    instruction = (c_byte >> 4) & 0b11;
    val = c_byte & 0b11;
    opcode = "";
    switch(instruction & 0b11) {
        case instructions_codes.nnd:
            instruction_functions.nnd(val);
            opcode = "nnd"
            break;
        case instructions_codes.mov:
            opcode = "mov"
            instruction_functions.mov(val);
            break;
        case instructions_codes.swp:
            opcode = "swp"
            instruction_functions.swp(val);
            break;
        case instructions_codes.str:
            opcode = "str"
            instruction_functions.str(val);
            break;
        default:
            console.log(`Encountered invalid code: 0b${(instruction & 0b11).toString(2)}`);
            break;
    }
    console.log(`PC - ${ROM.pc}\nAccumulator - 0b${accumulator.val.toString(2)}\nRAM - [${RAM.memory}]\nOpcode - 0b${(instruction & 0b11).toString(2)} or ${opcode}\nOperand - 0b${(val & 0b11).toString(2)}\n`);
    ROM.pc++;
}