/**
 * @file get_bit.h
 * @brief Bit retrieval utilities for reading individual bits from integers.
 *
 * This header provides a comprehensive set of functions for reading or retrieving
 * the value of individual bits at specified positions from various integer types.
 * Supports both signed and unsigned integer types ranging from 8-bit to 64-bit,
 * as well as convenience wrappers for common types like char, short, int, and long.
 *
 * All functions perform boundary checking to ensure the position parameter is
 * within valid range for the respective integer type. Out-of-range positions
 * trigger an error message and return false.
 *
 * Functions are organized by bit width:
 * - 8-bit: get_u8bit(), get_8bit(), get_char_bit()
 * - 16-bit: get_u16bit(), get_16bit(), get_short_bit()
 * - 32-bit: get_u32bit(), get_32bit(), get_int_bit()
 * - 64-bit: get_u64bit(), get_64bit(), get_long_bit()
 *
 * Bit positions are zero-indexed from the least significant bit (LSB).
 * For example, in the number 0b10101010:
 * - Position 0 returns the rightmost bit (0)
 * - Position 1 returns the next bit to the left (1)
 * - Position 7 returns the leftmost bit (1)
 *
 * @author MetaCore Development Team
 * @date 2025/09/25
 * @version 1.0
 *
 * @see get_bit.h for bit retrieval operations
 * @see set_bit.h for bit setting operations
 * @see reset_bit.h for bit clearing operations
 * @see toggle_bit.h for bit toggling operations
 * @see count_bit.h for bit counting operations
 * @see binaryFormat.h for binary string conversion operations
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef METACORE___CLITE_BITUTILITYS_GET_BIT_H
#define METACORE___CLITE_BITUTILITYS_GET_BIT_H

/// @brief Get bit value at specified position from 8-bit number
/// @param num The value to read
/// @param position Bit position (0-7)
/// @return True if bit is 1, false if bit is 0
static inline bool get_u8bit(uint8_t num, uint8_t position) {
    if (position > 7) {
        printf("outOfRange Error: position must be 0-7\n");
        return false;
    }
    return (num >> position) & 1;
}

/// @brief Get bit value at specified position from 16-bit number
/// @param num The value to read
/// @param position Bit position (0-15)
/// @return True if bit is 1, false if bit is 0
static inline bool get_u16bit(uint16_t num, uint8_t position) {
    if (position > 15) {
        printf("outOfRange Error: position must be 0-15\n");
        return false;
    }
    return (num >> position) & 1;
}

/// @brief Get bit value at specified position from 32-bit number
/// @param num The value to read
/// @param position Bit position (0-31)
/// @return True if bit is 1, false if bit is 0
static inline bool get_u32bit(uint32_t num, uint8_t position) {
    if (position > 31) {
        printf("outOfRange Error: position must be 0-31\n");
        return false;
    }
    return (num >> position) & 1;
}

/// @brief Get bit value at specified position from 64-bit number
/// @param num The value to read
/// @param position Bit position (0-63)
/// @return True if bit is 1, false if bit is 0
static inline bool get_u64bit(uint64_t num, uint8_t position) {
    if (position > 63) {
        printf("outOfRange Error: position must be 0-63\n");
        return false;
    }
    return (num >> position) & 1;
}

/// @brief Get bit value at specified position from signed 8-bit number
/// @param num The value to read
/// @param position Bit position (0-7)
/// @return True if bit is 1, false if bit is 0
static inline bool get_8bit(int8_t num, uint8_t position) {
    if (position > 7) {
        printf("outOfRange Error: position must be 0-7\n");
        return false;
    }
    return (num >> position) & 1;
}

/// @brief Get bit value at specified position from signed 16-bit number
/// @param num The value to read
/// @param position Bit position (0-15)
/// @return True if bit is 1, false if bit is 0
static inline bool get_16bit(int16_t num, uint8_t position) {
    if (position > 15) {
        printf("outOfRange Error: position must be 0-15\n");
        return false;
    }
    return (num >> position) & 1;
}

/// @brief Get bit value at specified position from signed 32-bit number
/// @param num The value to read
/// @param position Bit position (0-31)
/// @return True if bit is 1, false if bit is 0
static inline bool get_32bit(int32_t num, uint8_t position) {
    if (position > 31) {
        printf("outOfRange Error: position must be 0-31\n");
        return false;
    }
    return (num >> position) & 1;
}

/// @brief Get bit value at specified position from signed 64-bit number
/// @param num The value to read
/// @param position Bit position (0-63)
/// @return True if bit is 1, false if bit is 0
static inline bool get_64bit(int64_t num, uint8_t position) {
    if (position > 63) {
        printf("outOfRange Error: position must be 0-63\n");
        return false;
    }
    return (num >> position) & 1;
}

/// @brief Get bit value at specified position from character
/// @param c The character to read
/// @param position Bit position (0-7)
/// @return True if bit is 1, false if bit is 0
static inline bool get_char_bit(char c, uint8_t position) {
    return get_u8bit((uint8_t)c, position);
}

/// @brief Get bit value at specified position from short integer
/// @param num The value to read
/// @param position Bit position (0-15)
/// @return True if bit is 1, false if bit is 0
static inline bool get_short_bit(short num, uint8_t position) {
    return get_16bit((int16_t)num, position);
}

/// @brief Get bit value at specified position from integer
/// @param num The value to read
/// @param position Bit position (0-31)
/// @return True if bit is 1, false if bit is 0
static inline bool get_int_bit(int num, uint8_t position) {
    return get_32bit((int32_t)num, position);
}

/// @brief Get bit value at specified position from long integer
/// @param num The value to read
/// @param position Bit position (0-63)
/// @return True if bit is 1, false if bit is 0
static inline bool get_long_bit(long num, uint8_t position) {
    return get_64bit((int64_t)num, position);
}

#define get_bit(num, position) _Generic((num), \
    int8_t: get_8bit(num, position),           \
    int16_t: get_16bit(num, position),         \
    int32_t: get_32bit(num, position),         \
    int64_t: get_64bit(num, position),         \
    uint8_t: get_u8bit(num, position),         \
    uint16_t: get_u16bit(num, position),       \
    uint32_t: get_u32bit(num, position),       \
    uint64_t: get_u64bit(num, position))

#endif // METACORE___CLITE_BITUTILITYS_GET_BIT_H