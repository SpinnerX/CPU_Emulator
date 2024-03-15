#include "../include/CPU.h"
#include <formatCpp/formatCpp.h>

void CPU::reset(Memory& memory){
    PC = 0xFFFC;
    // SP = 0x01FF; // This is transferring the stack ptr to 0100.
    SP = 0x0100; // This is transferring the stack ptr to 0100.
    C = Z = I = D = B = V = N = 0;
    A = X = Y = 0;
    memory.Initialize();
}

void CPU::ExecuteCPU(u32 Cycles, Memory& memory){
    // Iterating cycles, while fetching instructions
    while(Cycles > 0){
        Byte Instruction = FetchByte(Cycles, memory); // get each instruction

        // Emulating the instructions
        switch (Instruction){
        case CPU_OP_CODES::INS_LDA_IM: // Immediate means the first byte is the op-code, and the second byte is actual value to load.
        {
            Byte Value = FetchByte(Cycles, memory);
            A = Value; // Setting the A register to the Value.
            LDASetStatus();
        } break;
        case CPU_OP_CODES::INS_LDA_ZP: // Zero page
        {
            Byte zeroPageAddress = FetchByte(Cycles, memory); // the address in the zero page
            A = ReadByte(Cycles, zeroPageAddress, memory); // takes three cycles. 1 cycle to fetch a byte in memory, a clock cycle to fetch immediate value stored in machine code, and another cycle to read byte from memory

            // Use clock cycles to read byte from memory
            // read byte wont take program counter, but effect clock cycles
            LDASetStatus();
        } break;
        case CPU_OP_CODES::INS_LDA_ZPX:
        {
            Byte zeroPageAddress = FetchByte(Cycles, memory);
            zeroPageAddress += X;
            Cycles--;
            LDASetStatus();
        } break;
        case CPU_OP_CODES::INS_JSR:
        {
            Word SubAddress = FetchWord(Cycles, memory);

            // This is where we need stack ptr
            memory.WriteWord(PC - 1, SP, Cycles);
            SP += 2;
            PC = SubAddress;
            Cycles--;
        } break;
            
        default:
        {
            formatCpp::print("Instruction not handled value: {}\n", Instruction);
        }
            break;
        }
    }
}

Byte CPU::FetchByte(u32& Cycles, Memory& memory){
    Byte Data = memory[PC];
    PC++;
    Cycles--;
    return Data;
}

Byte CPU::FetchWord(u32& Cycles, Memory& memory){
    // 6502 is little endian meaning first byte read is the least significant byte of the given data
    Word Data = memory[PC];
    PC++;

    Data |= (memory[PC] << 8);
    PC++;

    Cycles -= 2;

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

Byte CPU::ReadByte(u32& Cycles, Byte& Address, Memory& memory){
    Byte Data = memory[Address];
    Cycles--;
    return Data;
}

void CPU::LDASetStatus(){
    Z =  (A == 0);
    N = (A & 0b10000000) > 0;
}