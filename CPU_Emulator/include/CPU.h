#pragma once
#include "common.h"
#include "Memory.h"

/**
 * @brief 
    NOTE: New Link to look at: http://www.6502.org/users/obelisk/
    NOTE: Emulator Link: http://www.emulator101.com/6502-emulator.html
    NOTE: 6502 CPU Instruction Set: https://www.masswerk.at/6502/6502_instruction_set.html
    NOTE: We are emulating the 6502 CPU
*/

// This CPU (struct), will contain registers
// Program counter is a 16 bit register because 16 bit is the largest max register we can get
// NOTE: This CPU (struct), is implementing an older cpu but concepts applied to modern CPU. This is basically implementing a CPU (data structure - in a lower lvl perspective)
struct CPU{
    void reset(Memory& memory); // Reset also usually needs access to the memory as well to initialize it.

    Byte FetchByte(u32& Cycles, Memory& memory); // This is how to fetch 1 byte of data from memory.

    Byte FetchWord(u32& Cycles, Memory& memory);

    // We are not writing to memory, but reading from memory address
    // fetch the byte and read the byte and get the memory in that address
    Byte ReadByte(u32& Cycles, Byte& Address, Memory& memory);

    void LDASetStatus();

    //  Need to let Execute() know how much to exe
    // Ticks are how many cycles to execute
    void ExecuteCPU(u32 Cycles, Memory& memory);

    // PC = Program counter
    Word PC;

    // Stack ptr (which is the address to the stack, just this is just to note for review)
    Word SP; // SP = Stack Pointer

    // accumulator referred to as A
    Byte A, X, Y; // Registers

    // Processor State
    Byte C : 1; // status flag
    Byte Z : 1; // status flag
    Byte I : 1; // status flag
    Byte D : 1; // status flag
    Byte B : 1; // status flag
    Byte V : 1; // status flag
    Byte N : 1; // status flag
};