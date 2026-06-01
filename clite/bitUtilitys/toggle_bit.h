/**
 * @file toggle_bit.h
 * @brief Bit Toggle Utilities
 * @author MetaCore Development Team
 * @date May 25, 2026
 * 
 * @details
 * This file provides functions to toggle (flip) bits at specified positions in various integer types.
 * Toggle operation performs XOR with a bitmask to flip the bit from 0 to 1 or 1 to 0.
 * Supports 8-bit, 16-bit, 32-bit, and 64-bit signed and unsigned integers.
 * 
 * @functions
 * - toggle_u8bit()      : Toggle bit in uint8_t
 * - toggle_u16bit()     : Toggle bit in uint16_t
 * - toggle_u32bit()     : Toggle bit in uint32_t
 * - toggle_u64bit()     : Toggle bit in uint64_t
 * - toggle_8bit()       : Toggle bit in int8_t
 * - toggle_16bit()      : Toggle bit in int16_t
 * - toggle_32bit()      : Toggle bit in int32_t
 * - toggle_64bit()      : Toggle bit in int64_t
 * - toggle_char_bit()   : Toggle bit in character
 * - toggle_short_bit()  : Toggle bit in short integer
 * - toggle_int_bit()    : Toggle bit in integer
 * - toggle_long_bit()   : Toggle bit in long integer
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef METACORE___CLITE_BITUTILITYS_TOGGLE_BIT_H
#define METACORE___CLITE_BITUTILITYS_TOGGLE_BIT_H

/// @brief Toggle (flip) bit at specified position in 8-bit number
/// @param num The value to modify
/// @param position Bit position (0-7)
/// @return Modified value with bit toggled
static inline uint8_t toggle_u8bit(uint8_t num, uint8_t position) {
    if (position > 7) {
        printf("Error: position must be 0-7\n");
        return num;
    }
    return num ^ (1 << position);
}

/// @brief Toggle (flip) bit at specified position in 16-bit number
/// @param num The value to modify
/// @param position Bit position (0-15)
/// @return Modified value with bit toggled
static inline uint16_t toggle_u16bit(uint16_t num, uint8_t position) {
    if (position > 15) {
        printf("Error: position must be 0-15\n");
        return num;
    }
    return num ^ (1U << position);
}

/// @brief Toggle (flip) bit at specified position in 32-bit number
/// @param num The value to modify
/// @param position Bit position (0-31)
/// @return Modified value with bit toggled
static inline uint32_t toggle_u32bit(uint32_t num, uint8_t position) {
    if (position > 31) {
        printf("Error: position must be 0-31\n");
        return num;
    }
    return num ^ (1UL << position);
}

/// @brief Toggle (flip) bit at specified position in 64-bit number
/// @param num The value to modify
/// @param position Bit position (0-63)
/// @return Modified value with bit toggled
static inline uint64_t toggle_u64bit(uint64_t num, uint8_t position) {
    if (position > 63) {
        printf("Error: position must be 0-63\n");
        return num;
    }
    return num ^ (1ULL << position);
}

/// @brief Toggle (flip) bit at specified position in signed 8-bit number
/// @param num The value to modify
/// @param position Bit position (0-7)
/// @return Modified value with bit toggled
static inline int8_t toggle_8bit(int8_t num, uint8_t position) {
    if (position > 7) {
        printf("Error: position must be 0-7\n");
        return num;
    }
    return num ^ (1 << position);
}

/// @brief Toggle (flip) bit at specified position in signed 16-bit number
/// @param num The value to modify
/// @param position Bit position (0-15)
/// @return Modified value with bit toggled
static inline int16_t toggle_16bit(int16_t num, uint8_t position) {
    if (position > 15) {
        printf("Error: position must be 0-15\n");
        return num;
    }
    return num ^ (1 << (position & 0xF));
}

/// @brief Toggle (flip) bit at specified position in signed 32-bit number
/// @param num The value to modify
/// @param position Bit position (0-31)
/// @return Modified value with bit toggled
static inline int32_t toggle_32bit(int32_t num, uint8_t position) {
    if (position > 31) {
        printf("Error: position must be 0-31\n");
        return num;
    }
    return num ^ (1L << position);
}

/// @brief Toggle (flip) bit at specified position in signed 64-bit number
/// @param num The value to modify
/// @param position Bit position (0-63)
/// @return Modified value with bit toggled
static inline int64_t toggle_64bit(int64_t num, uint8_t position) {
    if (position > 63) {
        printf("Error: position must be 0-63\n");
        return num;
    }
    return num ^ (1LL << position);
}

/// @brief Toggle (flip) bit at specified position in character
/// @param c The character to modify
/// @param position Bit position (0-7)
/// @return Modified character with bit toggled
static inline char toggle_char_bit(char c, uint8_t position) {
    return (char)toggle_u8bit((uint8_t)c, position);
}

/// @brief Toggle (flip) bit at specified position in short integer
/// @param num The value to modify
/// @param position Bit position (0-15)
/// @return Modified value with bit toggled
static inline short toggle_short_bit(short num, uint8_t position) {
    return (short)toggle_16bit((int16_t)num, position);
}

/// @brief Toggle (flip) bit at specified position in integer
/// @param num The value to modify
/// @param position Bit position (0-31)
/// @return Modified value with bit toggled
static inline int toggle_int_bit(int num, uint8_t position) {
    return (int)toggle_32bit((int32_t)num, position);
}

/// @brief Toggle (flip) bit at specified position in long integer
/// @param num The value to modify
/// @param position Bit position (0-63)
/// @return Modified value with bit toggled
static inline long toggle_long_bit(long num, uint8_t position) {
    return (long)toggle_64bit((int64_t)num, position);
}

#endif // METACORE___CLITE_BITUTILITYS_TOGGLE_BIT_H