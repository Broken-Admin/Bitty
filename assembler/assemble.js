const fs = require('fs');

const instructions = ['nnd', 'mov', 'swp', 'str', 'nop'];

let file = fs.readFileSync(process.argv[2]);
let fdout = fs.openSync(process.argv[3], 'w');

let states = { // Assembler States
    newline: 0, // Currently reading from a new line and interpreting an opcode
    operand: 1  // Still on the same line, interpreting the decimal operand
}
// Current Assembler State
let state = states.newline;

let instruction;
let operand;

for (let pc = 0; pc < file.length; pc++) {
    instruction = ""
    operand = 0;
    switch (state) {
        case states.newline:
            // Interpret the opcode
            instruction += String.fromCharCode(file[pc++]);
            if (instruction[0] == ';') {
                // Move to next line
                while (file[pc] != 0x0A && pc < file.length) pc++;
                // Prepare to read next opcode
                state = states.newline;
            }
            instruction += String.fromCharCode(file[pc++]);
            instruction += String.fromCharCode(file[pc++]);
            console.log(instruction)
            switch (instructions.indexOf(instruction)) {
                case 0b00: // nnd
                    fs.writeSync(fdout, Buffer.from('\00'));
                    break;
                case 0b01: // mov
                    fs.writeSync(fdout, Buffer.from('\01'));
                    break;
                case 0b10: // swp
                    fs.writeSync(fdout, Buffer.from('\02'));
                    break;
                case 0b11: // str
                    fs.writeSync(fdout, Buffer.from('\03'));
                    break;
                default:
                    console.log("Encountered unknown opcode")
                    break;
            }
            // TODO: Remove this
            // Move to the next line
            while (file[pc] != 0x0A && pc < file.length) pc++;
            // Break out and interpret operand
            state = states.operand;
            break;
        case states.operand:
            while (file[pc] != "\n" && false) {
                // If encountered number
                if (file[pc] > 0x30 && file[pc] < 0x39) {

                }
            }
            break;
    }
}

fs.close(fdout, () => { });