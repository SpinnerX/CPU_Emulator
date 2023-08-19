// #include <formatCpp/formatCpp.h>
#include "dependencies/formatCpp/include/formatCpp/formatCpp.h"
using namespace formatCpp;

/**
 * @brief 
    NOTE: New Link to look at: http://www.6502.org/users/obelisk/
    NOTE: Emulator Link: http://www.emulator101.com/6502-emulator.html
    NOTE: 6502 CPU Instruction Set: https://www.masswerk.at/6502/6502_instruction_set.html
    NOTE: We are emulating the 6502 CPU
*/

using u32 = unsigned int;
using Byte = unsigned char;
using Word = unsigned short;

struct Memory{

    void Initialize(){
        for(u32 i = 0; i < MAX_MEMORY; i++) Data[i] = 0;
    }

    // A way to access 1 byte as the index being the address to memory.
    // read 1 byte
    Byte operator[](u32 address) const {
        return Data[address];
    }
    
    // write 1 byte
    Byte& operator[](u32 address) {
        return Data[address];
    }

    /**
     * @brief 
     * 
     * writes two bytes. (2 bytes)
     * 
     * @param Value 
     * @param Address 
     */
    void WriteWord(Word Value, u32 Address, u32& Cycles){
        Data[Address] = Value & 0xFF;
        Data[Address+1] = (Value >> 8);
        Cycles -= 2;
    }



    static constexpr u32 MAX_MEMORY = 1024 * 64;

    Byte Data[MAX_MEMORY];
};


// This CPU (struct), will contain registers
// Program counter is a 16 bit register because 16 bit is the largest max register we can get
// NOTE: This CPU (struct), is implementing an older cpu but concepts applied to modern CPU. This is basically implementing a CPU (data structure - in a lower lvl perspective)
struct CPU{
    // Reset also usually needs access to the memory as well to initialize it.
    void reset(Memory& mem){
        PC = 0xFFFC;
        SP = 0x01FF; // This is transferring the stack ptr to 0100.
        C = Z = I = D = B = V = N = 0;
        A = X = Y = 0;
        mem.Initialize();
    }

    // This is how to fetch 1 byte of data from memory.
    Byte FetchByte(u32& Cycles, Memory& memory){
        Byte Data = memory[PC];
        PC++;
        Cycles--;
        return Data;
    }

    Byte FetchWord(u32& Cycles, Memory& memory){
        // 6502 is little endian meaning first byte read is the least significant byte of the given data
        Word Data = memory[PC];
        PC++;
        Cycles--;

        Data |= (memory[PC] << 8);
        PC++;

        Cycles += 2;

        /**
         * @brief
        TODO:
        // This is where you want to ahndle endianness
        // you wqould have swap bytes here
        // IF (PLATFORM_BIG_ENDIAN)
        //  SwapBytesInWords(Data);
        */

        return Data;
    }

    // We are not writing to memory, but reading from memory address
    // fetch the byte and read the byte and get the memory in that address
    Byte ReadByte(u32& Cycles, Byte& address, Memory& memory){
        Byte Data = memory[address];
        Cycles--;
        return Data;
    }

    void LDASetStatus(){
        Z =  (A == 0);
        N = (A & 0b10000000) > 0;
    }

    /**
     * @brief 
     * 
     * NOTE: 0xNA = NA is the Op codes for that specific address in memory.
     * 
     */
    static constexpr Byte INS_LDA_IM = 0xA9; // Immediate
    static constexpr Byte INS_LDA_ZP = 0xA5; // Zero-page
    static constexpr Byte INS_LDA_ZPX = 0xB5; // address to the Zero-PageX
    static constexpr Byte INS_JSR = 0x20; // address to addressing mode "Absolute" which thhe op-code is 20.

    //  Need to let Execute() know how much to exe
    // Ticks are how many cycles to execute
    void Execute(u32 Cycles, Memory& mem){
        // Iterating the cycles. And Fetching an instruction
        while(Cycles > 0){
            Byte Intsruction = FetchByte(Cycles, mem);

            // Emulating the instructions
            switch (Intsruction){
            case INS_LDA_IM: // Immediate means the first byte is the op-code, and the second byte is actual value to load.
            {
                Byte Value = FetchByte(Cycles, mem);
                A = Value; // Setting the A register to the Value.
                LDASetStatus();
            } break;
            case INS_LDA_ZP: // Zero page
            {
                Byte zeroPageAddress = FetchByte(Cycles, mem); // the address in the zero page
                A = ReadByte(Cycles, zeroPageAddress, mem); // takes three cycles. 1 cycle to fetch a byte in memory, a clock cycle to fetch immediate value stored in machine code, and another cycle to read byte from memory

                // Use clock cycles to read byte from memory
                // read byte wont take program counter, but effect clock cycles
                LDASetStatus();
            } break;
            case INS_LDA_ZPX:
            {
                Byte zeroPageAddress = FetchByte(Cycles, mem);
                zeroPageAddress += X;
                Cycles--;
                LDASetStatus();
            } break;
            case INS_JSR:
            {
                Word SubAddress = FetchWord(Cycles, mem);

                // This is where we need stack ptr
                mem.WriteWord(PC - 1, SP, Cycles);
                PC = SubAddress;
                
                Cycles--;
            } break;
            
            default:
            {
                formatCpp::print("Instruction not handled value: {}\n", Intsruction);
            }
                break;
            }
        }
    }


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

int main(){
    Memory mem;
    CPU cpu;
    cpu.reset(mem);

    // start inline program
    // mem[0xFFFC] = CPU::INS_LDA_ZP;
    mem[0xFFFC] = CPU::INS_JSR;
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;
    mem[0x4242] = CPU::INS_LDA_IM;
    mem[0x4243] = 0x84;
    // end inline program

    cpu.Execute(9, mem); // this will execute instructions, by also allowing how many cycles to execute

    return 0;
}