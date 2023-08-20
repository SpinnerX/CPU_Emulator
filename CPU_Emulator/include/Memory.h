#pragma once
#include "common.h"

struct Memory{
    void Initialize();

    void WriteWord(Word Value, u32 Address, u32& Cycles);

    Byte operator[](u32 Address) const;
    Byte& operator[](u32 Address);

    static constexpr u32 MAX_MEMORY = 1024 * 64;
    Byte Data[MAX_MEMORY];
};