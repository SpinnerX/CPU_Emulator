#include "CPU_Emulator/include/CPU.h"
#include "CPU_Emulator/include/Memory.h"
#include "CPU_Emulator/include/common.h"
#include <formatCpp/core/format.h>


int main(){
    Memory mem;
    CPU cpu;
    formatCpp::print("Before resetting!\n");
    cpu.reset(mem);
    // start inline program
    // mem[0xFFFC] = CPU::INS_LDA_ZP;
    mem[0xFFFC] = CPU_OP_CODES::INS_JSR;
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;
    mem[0x4242] = CPU_OP_CODES::INS_LDA_IM;
    mem[0x4243] = 0x84;
    // end inline program

    cpu.ExecuteCPU(9, mem); // this will execute instructions, by also allowing how many cycles to execute
}