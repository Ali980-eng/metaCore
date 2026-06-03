/**
 * @file count_bit.h
 * @brief Bit Count Utilities
 * @author MetaCore Development Team
 * @date May 25, 2026
 * 
 * @details
 * This file provides functions to count set (1) or unset (0) bits in various integer types.
 * These utilities are useful for analyzing bit patterns and determining bit populations.
 * Supports 8-bit, 16-bit, 32-bit, and 64-bit signed and unsigned integers.
 * 
 * @functions
 * - count_u8bit()      : Count bits in uint8_t
 * - count_u16bit()     : Count bits in uint16_t
 * - count_u32bit()     : Count bits in uint32_t
 * - count_u64bit()     : Count bits in uint64_t
 * - count_8bit()       : Count bits in int8_t
 * - count_16bit()      : Count bits in int16_t
 * - count_32bit()      : Count bits in int32_t
 * - count_64bit()      : Count bits in int64_t
 * - count_char_bit()   : Count bits in character
 * - count_short_bit()  : Count bits in short integer
 * - count_int_bit()    : Count bits in integer
 * - count_long_bit()   : Count bits in long integer
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "get_bit.h"

#ifndef METACORE___CLITE_BITUTILITYS_COUNT_BIT_H
#define METACORE___CLITE_BITUTILITYS_COUNT_BIT_H

/// @brief Count set (1) or unset (0) bits in an 8-bit value
/// @param num The value to analyze
/// @param ones If true count 1-bits, else count 0-bits
/// @return Number of bits matching the criteria
static inline uint8_t count_u8bit(uint8_t num, bool ones) {
    uint8_t count = 0;
    for(uint8_t i = 0; i < 8; i++) {
        if(get_u8bit(num, i) == true && ones) count++;
        else if(get_u8bit(num, i) == false && !ones) count++;
    }
    return count;
}

/// @brief Count set (1) or unset (0) bits in a 16-bit value
/// @param num The value to analyze
/// @param ones If true count 1-bits, else count 0-bits
/// @return Number of bits matching the criteria
static inline uint8_t count_u16bit(uint16_t num, bool ones) {
    uint8_t count = 0;
    for(uint8_t i = 0; i < 16; i++) {
        if(get_u16bit(num, i) == true && ones) count++;
        else if(get_u16bit(num, i) == false && !ones) count++;
    }
    return count;
}

/// @brief Count set (1) or unset (0) bits in a 32-bit value
/// @param num The value to analyze
/// @param ones If true count 1-bits, else count 0-bits
/// @return Number of bits matching the criteria
static inline uint8_t count_u32bit(uint32_t num, bool ones) {
    uint8_t count = 0;
    for(uint8_t i = 0; i < 32; i++) {
        if(get_u32bit(num, i) == true && ones) count++;
        else if(get_u32bit(num, i) == false && !ones) count++;
    }
    return count;
}

/// @brief Count set (1) or unset (0) bits in a 64-bit value
/// @param num The value to analyze
/// @param ones If true count 1-bits, else count 0-bits
/// @return Number of bits matching the criteria
static inline uint8_t count_u64bit(uint64_t num, bool ones) {
    uint8_t count = 0;
    for(uint8_t i = 0; i < 64; i++) {
        if(get_u64bit(num, i) == true && ones) count++;
        else if(get_u64bit(num, i) == false && !ones) count++;
    }
    return count;
}

/// @brief Count set (1) or unset (0) bits in a signed 8-bit value
/// @param num The value to analyze
/// @param ones If true count 1-bits, else count 0-bits
/// @return Number of bits matching the criteria
static inline uint8_t count_8bit(int8_t num, bool ones) {
    return count_u8bit((uint8_t)num, ones);
}

/// @brief Count set (1) or unset (0) bits in a signed 16-bit value
/// @param num The value to analyze
/// @param ones If true count 1-bits, else count 0-bits
/// @return Number of bits matching the criteria
static inline uint8_t count_16bit(int16_t num, bool ones) {
    return count_u16bit((uint16_t)num, ones);
}

/// @brief Count set (1) or unset (0) bits in a signed 32-bit value
/// @param num The value to analyze
/// @param ones If true count 1-bits, else count 0-bits
/// @return Number of bits matching the criteria
static inline uint8_t count_32bit(int32_t num, bool ones) {
    return count_u32bit((uint32_t)num, ones);
}

/// @brief Count set (1) or unset (0) bits in a signed 64-bit value
/// @param num The value to analyze
/// @param ones If true count 1-bits, else count 0-bits
/// @return Number of bits matching the criteria
static inline uint8_t count_64bit(int64_t num, bool ones) {
    return count_u64bit((uint64_t)num, ones);
}

/// @brief Count set (1) or unset (0) bits in a character
/// @param c The character to analyze
/// @param ones If true count 1-bits, else count 0-bits
/// @return Number of bits matching the criteria
static inline uint8_t count_char_bit(char c, bool ones) {
    return count_u8bit((uint8_t)c, ones);
}

/// @brief Count set (1) or unset (0) bits in a short integer
/// @param num The value to analyze
/// @param ones If true count 1-bits, else count 0-bits
/// @return Number of bits matching the criteria
static inline uint8_t count_short_bit(short num, bool ones) {
    return count_u16bit((uint16_t)num, ones);
}

/// @brief Count set (1) or unset (0) bits in an integer
/// @param num The value to analyze
/// @param ones If true count 1-bits, else count 0-bits
/// @return Number of bits matching the criteria
static inline uint8_t count_int_bit(int num, bool ones) {
    return count_u32bit((uint32_t)num, ones);
}

/// @brief Count set (1) or unset (0) bits in a long integer
/// @param num The value to analyze
/// @param ones If true count 1-bits, else count 0-bits
/// @return Number of bits matching the criteria
static inline uint8_t count_long_bit(long num, bool ones) {
    return count_u64bit((uint64_t)num, ones);
}

#define count_bit(num, ones) _Generic((num), \
    int8_t: count_8bit(num, ones),           \
    int16_t: count_16bit(num, ones),         \
    int32_t: count_32bit(num, ones),         \
    int64_t: count_64bit(num, ones),         \
    uint8_t: count_u8bit(num, ones),         \
    uint16_t: count_u16bit(num, ones),       \
    uint32_t: count_u32bit(num, ones),       \
    uint64_t: count_u64bit(num, ones))

#endif // METACORE___CLITE_BITUTILITYS_COUNT_BIT_H