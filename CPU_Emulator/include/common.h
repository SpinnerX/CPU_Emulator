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
     */
    static constexpr Byte INS_LDA_IM = 0xA9; // Immediate
    static constexpr Byte INS_LDA_ZP = 0xA5; // Zero-page
    static constexpr Byte INS_LDA_ZPX = 0xB5; // address to the Zero-PageX
    static constexpr Byte INS_JSR = 0x20; // address to addressing mode "Absolute" which thhe op-code is 20.
};