// #include "CPU_Emulator/include/CPU.h"
// #include "CPU_Emulator/include/Memory.h"
// #include "tests/initGoogleTest.h"
#include "CPU_Emulator2/include/test.h"
#include <formatCpp/core/format.h>
#include <gtest/gtest.h>

int testMain(){
    Mem mem;
    CPU cpu;
    cpu.Reset(mem);
    // start inline program
    // mem[0xFFFC] = CPU::INS_LDA_ZP;
    // mem[0xFFFC] = CPU_OP_CODES::INS_JSR;
    // mem[0xFFFD] = 0x42;
    // mem[0xFFFE] = 0x42;
    // mem[0x4242] = CPU_OP_CODES::INS_LDA_IM;
    mem[0xFFFC] = CPU::INS_JSR;
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;
    mem[0x4242] = CPU::INS_LDA_IM;
    mem[0x4243] = 0x84;


    
    // end inline program

    cpu.Execute(9, mem); // this will execute instructions, by also allowing how many cycles to execute
    return 0;
}


int main(int argc, char** argv){
    // return InitializeGoogletest();
    // return 0;
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}

TEST(SuiteNameOne, Add){
    Mem mem;
    CPU cpu;
    cpu.Reset(mem);
    // start inline program
    // mem[0xFFFC] = CPU::INS_LDA_ZP;
    // mem[0xFFFC] = CPU_OP_CODES::INS_JSR;
    // mem[0xFFFD] = 0x42;
    // mem[0xFFFE] = 0x42;
    // mem[0x4242] = CPU_OP_CODES::INS_LDA_IM;
    mem[0xFFFC] = CPU::INS_JSR;
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;
    mem[0x4242] = CPU::INS_LDA_IM;
    mem[0x4243] = 0x84;
    
    // end inline program

    cpu.Execute(9, mem); // this will execute instructions, by also allowing how many cycles to execute
    // return testMain();
    EXPECT_EQ(cpu.A, 0x84);
}
