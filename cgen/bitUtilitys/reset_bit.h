/**
 * @file reset_bit.h
 * @brief Bit Reset Utilities
 * @author MetaCore Development Team
 * @date May 25, 2026
 * 
 * @details
 * This file provides functions to reset (clear to 0) bits at specified positions in various integer types.
 * Reset operation performs AND with an inverted bitmask to ensure the bit is set to 0.
 * Supports 8-bit, 16-bit, 32-bit, and 64-bit signed and unsigned integers.
 * 
 * @functions
 * - reset_u8bit()      : Reset bit to 0 in uint8_t
 * - reset_u16bit()     : Reset bit to 0 in uint16_t
 * - reset_u32bit()     : Reset bit to 0 in uint32_t
 * - reset_u64bit()     : Reset bit to 0 in uint64_t
 * - reset_8bit()       : Reset bit to 0 in int8_t
 * - reset_16bit()      : Reset bit to 0 in int16_t
 * - reset_32bit()      : Reset bit to 0 in int32_t
 * - reset_64bit()      : Reset bit to 0 in int64_t
 * - reset_char_bit()   : Reset bit to 0 in character
 * - reset_short_bit()  : Reset bit to 0 in short integer
 * - reset_int_bit()    : Reset bit to 0 in integer
 * - reset_long_bit()   : Reset bit to 0 in long integer
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef METACORE___CLITE_BITUTILITYS_RESET_BIT_H
#define METACORE___CLITE_BITUTILITYS_RESET_BIT_H

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Reset (clear) bit at specified position to 0 in 8-bit number
/// @param num The value to modify
/// @param position Bit position (0-7)
/// @return Modified value with bit cleared
static inline uint8_t reset_u8bit(uint8_t num, uint8_t position) {
    if (position > 7) {
        printf("outOfRange Error: position must be 0-7\n");
        return num;
    }
    return num & ~(1 << position);
}

/// @brief Reset (clear) bit at specified position to 0 in 16-bit number
/// @param num The value to modify
/// @param position Bit position (0-15)
/// @return Modified value with bit cleared
static inline uint16_t reset_u16bit(uint16_t num, uint8_t position) {
    if (position > 15) {
        printf("outOfRange Error: position must be 0-15\n");
        return num;
    }
    return num & ~(1U << position);
}

/// @brief Reset (clear) bit at specified position to 0 in 32-bit number
/// @param num The value to modify
/// @param position Bit position (0-31)
/// @return Modified value with bit cleared
static inline uint32_t reset_u32bit(uint32_t num, uint8_t position) {
    if (position > 31) {
        printf("outOfRange Error: position must be 0-31\n");
        return num;
    }
    return num & ~(1UL << position);
}

/// @brief Reset (clear) bit at specified position to 0 in 64-bit number
/// @param num The value to modify
/// @param position Bit position (0-63)
/// @return Modified value with bit cleared
static inline uint64_t reset_u64bit(uint64_t num, uint8_t position) {
    if (position > 63) {
        printf("outOfRange Error: position must be 0-63\n");
        return num;
    }
    return num & ~(1ULL << position);
}

/// @brief Reset (clear) bit at specified position to 0 in signed 8-bit number
/// @param num The value to modify
/// @param position Bit position (0-7)
/// @return Modified value with bit cleared
static inline int8_t reset_8bit(int8_t num, uint8_t position) {
    if (position > 7) {
        printf("outOfRange Error: position must be 0-7\n");
        return num;
    }
    return num & ~(1 << position);
}

/// @brief Reset (clear) bit at specified position to 0 in signed 16-bit number
/// @param num The value to modify
/// @param position Bit position (0-15)
/// @return Modified value with bit cleared
static inline int16_t reset_16bit(int16_t num, uint8_t position) {
    if (position > 15) {
        printf("outOfRange Error: position must be 0-15\n");
        return num;
    }
    return num & ~(1 << (position & 0xF));
}

/// @brief Reset (clear) bit at specified position to 0 in signed 32-bit number
/// @param num The value to modify
/// @param position Bit position (0-31)
/// @return Modified value with bit cleared
static inline int32_t reset_32bit(int32_t num, uint8_t position) {
    if (position > 31) {
        printf("outOfRange Error: position must be 0-31\n");
        return num;
    }
    return num & ~(1L << position);
}

/// @brief Reset (clear) bit at specified position to 0 in signed 64-bit number
/// @param num The value to modify
/// @param position Bit position (0-63)
/// @return Modified value with bit cleared
static inline int64_t reset_64bit(int64_t num, uint8_t position) {
    if (position > 63) {
        printf("outOfRange Error: position must be 0-63\n");
        return num;
    }
    return num & ~(1LL << position);
}

/// @brief Reset (clear) bit at specified position to 0 in character
/// @param c The character to modify
/// @param position Bit position (0-7)
/// @return Modified character with bit cleared
static inline char reset_char_bit(char c, uint8_t position) {
    return (char)reset_u8bit((uint8_t)c, position);
}

/// @brief Reset (clear) bit at specified position to 0 in short integer
/// @param num The value to modify
/// @param position Bit position (0-15)
/// @return Modified value with bit cleared
static inline short reset_short_bit(short num, uint8_t position) {
    return (short)reset_16bit((int16_t)num, position);
}

/// @brief Reset (clear) bit at specified position to 0 in integer
/// @param num The value to modify
/// @param position Bit position (0-31)
/// @return Modified value with bit cleared
static inline int reset_int_bit(int num, uint8_t position) {
    return (int)reset_32bit((int32_t)num, position);
}

/// @brief Reset (clear) bit at specified position to 0 in long integer
/// @param num The value to modify
/// @param position Bit position (0-63)
/// @return Modified value with bit cleared
static inline long reset_long_bit(long num, uint8_t position) {
    return (long)reset_64bit((int64_t)num, position);
}

#define reset_bit(num, position) _Generic((num), \
    int8_t: reset_8bit(num, position),           \
    int16_t: reset_16bit(num, position),         \
    int32_t: reset_32bit(num, position),         \
    int64_t: reset_64bit(num, position),         \
    uint8_t: reset_u8bit(num, position),         \
    uint16_t: reset_u16bit(num, position),       \
    uint32_t: reset_u32bit(num, position),       \
    uint64_t: reset_u64bit(num, position))

#ifdef __cplusplus
}
#endif

#endif // METACORE___CLITE_BITUTILITYS_RESET_BIT_H