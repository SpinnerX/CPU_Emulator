#pragma once
#include <gtest/gtest.h>
#include "CPU_Emulator.h"
#include <sstream>
#include <formatCpp/core/format.h>

// Creating a mock test of this class
class CPU6502Test1 : public testing::Test{

    virtual void SetUp(){ }

    virtual void TearDown(){}
public:
    Memory memory;
    CPU cpu;
};

// Testing the mock class
TEST_F(CPU6502Test1, RunALittleProgram){
    memory[0xFFFC] = CPU_OP_CODES::INS_JSR;
    memory[0xFFFD] = 0x42;
    memory[0xFFFE] = 0x42;
    memory[0x4242] = CPU_OP_CODES::INS_LDA_IM;
    memory[0x4243] = 0x84;

    cpu.ExecuteCPU(9, memory);
    // cpu.ExecuteCPU(9, memory); // this will execute instructions, by also allowing how many cycles to execute
    formatCpp::print("VALUE: {}\n", static_cast<Byte>(cpu.A));
    EXPECT_EQ(static_cast<Byte>(cpu.A), 0x84);
}