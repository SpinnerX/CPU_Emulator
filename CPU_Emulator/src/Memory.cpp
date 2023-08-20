#include "../include/Memory.h"

void Memory::Initialize(){
    for(u32 i = 0; i < MAX_MEMORY; i++){
        Data[i] = 0;
    }
}

Byte Memory::operator[](u32 Address) const {
    return Data[Address];
}

Byte& Memory::operator[](u32 Address) {
    return Data[Address];
}

void Memory::WriteWord(Word Value, u32 Address, u32& Cycles){
    Data[Address] = Value & 0xFF;
    Data[Address+1] = (Value >> 8);
}