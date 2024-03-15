#pragma once

// Aliases
using u32 = unsigned int;
using Byte = unsigned char;
using Word = unsigned short;



/**
* @brief 
 *
 * NOTE: 0xNA = NA is the Op codes for that specific address in memory.
 * 
*/

namespace CPU_OP_CODES{
    /**
     * @brief 
     * 
     * NOTE: 0xNA = NA is the Op codes for that specific address in memory.
     * 
     * On Mac for some reason we have to explicitly tell thhe compiler we want these values as unsigned char for hex.
     * Or else, the compiler automatically appends these values as unsigned ints (which is not what we want)
     * 
     * May need to change this later on, to work with how other compilers handle these sort of things.  (possibly...)
     * 
     */
    static constexpr Byte INS_LDA_IM = (Byte)0xA9; // Immediate
    static constexpr Byte INS_LDA_ZP = (Byte)0xA5; // Zero-page
    static constexpr Byte INS_LDA_ZPX = 0xB5; // address to the Zero-PageX
    static constexpr Byte INS_JSR = 0x20; // address to addressing mode "Absolute" which thhe op-code is 20.
};