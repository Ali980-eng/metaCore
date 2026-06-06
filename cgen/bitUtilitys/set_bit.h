/**
 * @file set_bit.h
 * @brief Bit Set Utilities
 * @author MetaCore Development Team
 * @date May 25, 2026
 * 
 * @details
 * This file provides functions to set (set to 1) bits at specified positions in various integer types.
 * Set operation performs OR with a bitmask to ensure the bit is set to 1.
 * Supports 8-bit, 16-bit, 32-bit, and 64-bit signed and unsigned integers.
 * 
 * @functions
 * - set_u8bit()       : Set bit to 1 in uint8_t
 * - set_u16bit()      : Set bit to 1 in uint16_t
 * - set_u32bit()      : Set bit to 1 in uint32_t
 * - set_u64bit()      : Set bit to 1 in uint64_t
 * - set_8bit()        : Set bit to 1 in int8_t
 * - set_16bit()       : Set bit to 1 in int16_t
 * - set_32bit()       : Set bit to 1 in int32_t
 * - set_64bit()       : Set bit to 1 in int64_t
 * - set_char_bit()    : Set bit to 1 in character
 * - set_short_bit()   : Set bit to 1 in short integer
 * - set_int_bit()     : Set bit to 1 in integer
 * - set_long_bit()    : Set bit to 1 in long integer
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef METACORE___CGEN_BITUTILITYS_SET_BIT_H
#define METACORE___CGEN_BITUTILITYS_SET_BIT_H

#ifdef __cplusplus
    #ifdef METACORE___META_HPP
    namespace meta {
    namespace cgen {
    #endif // METACORE___META_HPP
#endif

/// @brief Set bit at specified position to 1 in 8-bit number
/// @param num The value to modify
/// @param position Bit position (0-7)
/// @return Modified value with bit set
static inline uint8_t set_u8bit(uint8_t num, uint8_t position) {
    if (position > 7) {
        printf("OutOfRange Error: position must be 0-7\n");
        return num;
    }
    return num | (1 << position);
}

/// @brief Set bit at specified position to 1 in 16-bit number
/// @param num The value to modify
/// @param position Bit position (0-15)
/// @return Modified value with bit set
static inline uint16_t set_u16bit(uint16_t num, uint8_t position) {
    if(position > 15) {
        printf("OutOfRange Error: position must be 0-15\n");
        return num;
    }
    return num | (1U << position);
}

/// @brief Set bit at specified position to 1 in 32-bit number
/// @param num The value to modify
/// @param position Bit position (0-31)
/// @return Modified value with bit set
static inline uint32_t set_u32bit(uint32_t num, uint8_t position) {
    if(position > 31) {
        printf("outOfRange Error: position must be 0-31\n");
        return num;
    }
    return num | (1UL << position);
}

/// @brief Set bit at specified position to 1 in 64-bit number
/// @param num The value to modify
/// @param position Bit position (0-63)
/// @return Modified value with bit set
static inline uint64_t set_u64bit(uint64_t num, uint8_t position) {
    if(position > 63) {
        printf("outOfRange Error: position must be 0-63\n");
        return num;
    }
    return num | (1ULL << position);
}

/// @brief Set bit at specified position to 1 in signed 8-bit number
/// @param num The value to modify
/// @param position Bit position (0-7)
/// @return Modified value with bit set
static inline int8_t set_8bit(int8_t num, uint8_t position) {
    if (position > 7) {
        printf("OutOfRange Error: position must be 0-7\n");
        return num;
    }
    return num | (1 << position);
}

/// @brief Set bit at specified position to 1 in signed 16-bit number
/// @param num The value to modify
/// @param position Bit position (0-15)
/// @return Modified value with bit set
static inline int16_t set_16bit(int16_t num, uint8_t position) {
    if(position > 15) {
        printf("OutOfRange Error: position must be 0-15\n");
        return num;
    }
    return num | (1 << (position & 0xF));
}

/// @brief Set bit at specified position to 1 in signed 32-bit number
/// @param num The value to modify
/// @param position Bit position (0-31)
/// @return Modified value with bit set
static inline int32_t set_32bit(int32_t num, uint8_t position) {
    if(position > 31) {
        printf("outOfRange Error: position must be 0-31\n");
        return num;
    }
    return num | (1L << position);
}

/// @brief Set bit at specified position to 1 in signed 64-bit number
/// @param num The value to modify
/// @param position Bit position (0-63)
/// @return Modified value with bit set
static inline int64_t set_64bit(int64_t num, uint8_t position) {
    if(position > 63) {
        printf("outOfRange Error: position must be 0-63\n");
        return num;
    }
    return num | (1LL << position);
}

/// @brief Set bit at specified position to 1 in character
/// @param c The character to modify
/// @param position Bit position (0-7)
/// @return Modified character with bit set
static inline char set_char_bit(char c, uint8_t position) {
    return (char)set_u8bit((uint8_t)c, position);
}

/// @brief Set bit at specified position to 1 in short integer
/// @param num The value to modify
/// @param position Bit position (0-15)
/// @return Modified value with bit set
static inline short set_short_bit(short num, uint8_t position) {
    return (short)set_16bit((int16_t)num, position);
}

/// @brief Set bit at specified position to 1 in integer
/// @param num The value to modify
/// @param position Bit position (0-31)
/// @return Modified value with bit set
static inline int set_int_bit(int num, uint8_t position) {
    return (int)set_32bit((int32_t)num, position);
}

/// @brief Set bit at specified position to 1 in long integer
/// @param num The value to modify
/// @param position Bit position (0-63)
/// @return Modified value with bit set
static inline long set_long_bit(long num, uint8_t position) {
    return (long)set_64bit((int64_t)num, position);
}

#ifdef __cplusplus
    #ifdef METACORE___META_HPP
}}
    #endif // METACORE___META_HPP
#endif

#endif // METACORE___CGEN_BITUTILITYS_SET_BIT_H