/**
 * @file xchg_bit.h
 * @brief Bit exchange (swap) operations for integers of various sizes
 * @details Provides functions to exchange (swap) two bit positions in 8-bit, 16-bit, 32-bit,
 *          and 64-bit integers, both signed and unsigned variants.
 *          
 *          The exchange operation swaps the bits at two specified positions only if they
 *          differ. If the bits at both positions have the same value (both 0 or both 1),
 *          no exchange occurs and the original value is returned.
 *
 * @author Ali Lafi
 * @date 2025 / 9 / 25
 * 
 * @note All functions validate input positions and return 0 if positions exceed valid range.
 *       Error messages are printed to console for invalid positions.
 * @note Position 0 represents the least significant bit (LSB).
 * 
 * Functions provided:
 * - Unsigned variants: xchg_u8bit(), xchg_u16bit(), xchg_u32bit(), xchg_u64bit()
 * - Signed variants: xchg_8bit(), xchg_16bit(), xchg_32bit(), xchg_64bit()
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "get_bit.h"
#include "set_bit.h"
#include "reset_bit.h"

#ifndef METACORE___CLITE_BITUTILITYS_XCHG_BIT_H
#define METACORE___CLITE_BITUTILITYS_XCHG_BIT_H

/// @brief Exchange (swap) two bit positions in an 8-bit unsigned integer
/// @details Swaps the bits at positions pos1 and pos2. If both bits have the same value,
///          the value is returned unchanged. Only swaps when bits differ.
/// @param value The 8-bit unsigned integer to modify
/// @param pos1 First bit position to exchange (0-7, where 0 is LSB)
/// @param pos2 Second bit position to exchange (0-7)
/// @return Modified value with bits at pos1 and pos2 exchanged, or 0 if positions are invalid
/// @note Prints error message to console if pos1 or pos2 exceed valid range (0-7)
/// @example xchg_u8bit(0b10100101, 0, 7) returns 0b00100101 (swap LSB and MSB)
uint8_t xchg_u8bit(uint8_t value, uint8_t pos1, uint8_t pos2) {
    if(pos1 > 7 || pos2 > 7) {
        printf("outOfRange Error: the position 1 or 2 is out of the range 0-7");
        return 0;
    }
    uint8_t result = 0;
    if(!get_u8bit(value, pos1) && get_u8bit(value, pos2)) {
        result = set_u8bit(value, pos1);
        result = reset_u8bit(result, pos2);
    }
    else if(get_u8bit(value, pos1) && !get_u8bit(value, pos2)) {
        result = set_u8bit(value, pos2);
        result = reset_u8bit(result, pos1);
    }
    else return value;
    return result;
}

/// @brief Exchange (swap) two bit positions in a 16-bit unsigned integer
/// @details Swaps the bits at positions pos1 and pos2. If both bits have the same value,
///          the value is returned unchanged. Only swaps when bits differ.
/// @param value The 16-bit unsigned integer to modify
/// @param pos1 First bit position to exchange (0-15, where 0 is LSB)
/// @param pos2 Second bit position to exchange (0-15)
/// @return Modified value with bits at pos1 and pos2 exchanged, or 0 if positions are invalid
/// @note Prints error message to console if pos1 or pos2 exceed valid range (0-15)
uint16_t xchg_u16bit(uint16_t value, uint8_t pos1, uint8_t pos2) {
    if(pos1 > 15 || pos2 > 15) {
        printf("outOfRange Error: the position 1 or 2 is out of the range 0-15");
        return 0;
    }
    uint16_t result = 0;
    if(!get_u16bit(value, pos1) && get_u16bit(value, pos2)) {
        result = set_u16bit(value, pos1);
        result = reset_u16bit(result, pos2);
    }
    else if(get_u16bit(value, pos1) && !get_u16bit(value, pos2)) {
        result = set_u16bit(value, pos2);
        result = reset_u16bit(result, pos1);
    }
    else return value;
    return result;
}

/// @brief Exchange (swap) two bit positions in a 32-bit unsigned integer
/// @details Swaps the bits at positions pos1 and pos2. If both bits have the same value,
///          the value is returned unchanged. Only swaps when bits differ.
/// @param value The 32-bit unsigned integer to modify
/// @param pos1 First bit position to exchange (0-31, where 0 is LSB)
/// @param pos2 Second bit position to exchange (0-31)
/// @return Modified value with bits at pos1 and pos2 exchanged, or 0 if positions are invalid
/// @note Prints error message to console if pos1 or pos2 exceed valid range (0-31)
uint32_t xchg_u32bit(uint32_t value, uint8_t pos1, uint8_t pos2) {
    if(pos1 > 31 || pos2 > 31) {
        printf("outOfRange Error: the position 1 or 2 is out of the range 0-31");
        return 0;
    }
    uint32_t result = 0;
    if(!get_u32bit(value, pos1) && get_u32bit(value, pos2)) {
        result = set_u32bit(value, pos1);
        result = reset_u32bit(result, pos2);
    }
    else if(get_u32bit(value, pos1) && !get_u32bit(value, pos2)) {
        result = set_u32bit(value, pos2);
        result = reset_u32bit(result, pos1);
    }
    else return value;
    return result;
}

/// @brief Exchange bits at specified positions in a 64-bit number
/// @param value The value to modify
/// @param pos1 First bit position (0-63)
/// @param pos2 Second bit position (0-63)
/// @return Modified value with bits exchanged
uint64_t xchg_u64bit(uint64_t value, uint8_t pos1, uint8_t pos2) {
    if(pos1 > 63 || pos2 > 63) {
        printf("outOfRange Error: the position 1 or 2 is out of the range 0-63");
        return 0;
    }
    uint64_t result = 0;
    if(!get_u64bit(value, pos1) && get_u64bit(value, pos2)) {
        result = set_u64bit(value, pos1);
        result = reset_u64bit(result, pos2);
    }
    else if(get_u64bit(value, pos1) && !get_u64bit(value, pos2)) {
        result = set_u64bit(value, pos2);
        result = reset_u64bit(result, pos1);
    }
    else return value;
    return result;
}

/// @brief Exchange (swap) two bit positions in a signed 8-bit integer
/// @details Wrapper function that converts signed value to unsigned, performs bit exchange,
///          then converts back to signed. Swaps bits at positions pos1 and pos2.
/// @param value The signed 8-bit integer to modify
/// @param pos1 First bit position to exchange (0-7, where 0 is LSB)
/// @param pos2 Second bit position to exchange (0-7)
/// @return Modified value with bits at pos1 and pos2 exchanged, or 0 if positions are invalid
/// @note Prints error message to console if pos1 or pos2 exceed valid range (0-7)
int8_t xchg_8bit(int8_t value, uint8_t pos1, uint8_t pos2) {
    return (int8_t)xchg_u8bit((uint8_t) value, pos1, pos2);
}

/// @brief Exchange (swap) two bit positions in a signed 16-bit integer
/// @details Wrapper function that converts signed value to unsigned, performs bit exchange,
///          then converts back to signed. Swaps bits at positions pos1 and pos2.
/// @param value The signed 16-bit integer to modify
/// @param pos1 First bit position to exchange (0-15, where 0 is LSB)
/// @param pos2 Second bit position to exchange (0-15)
/// @return Modified value with bits at pos1 and pos2 exchanged, or 0 if positions are invalid
/// @note Prints error message to console if pos1 or pos2 exceed valid range (0-15)
int16_t xchg_16bit(int16_t value, uint8_t pos1, uint8_t pos2) {
    return (int16_t)xchg_u16bit((uint16_t) value, pos1, pos2);
}

/// @brief Exchange (swap) two bit positions in a signed 32-bit integer
/// @details Wrapper function that converts signed value to unsigned, performs bit exchange,
///          then converts back to signed. Swaps bits at positions pos1 and pos2.
/// @param value The signed 32-bit integer to modify
/// @param pos1 First bit position to exchange (0-31, where 0 is LSB)
/// @param pos2 Second bit position to exchange (0-31)
/// @return Modified value with bits at pos1 and pos2 exchanged, or 0 if positions are invalid
/// @note Prints error message to console if pos1 or pos2 exceed valid range (0-31)
int32_t xchg_32bit(int32_t value, uint8_t pos1, uint8_t pos2) {
    return (int32_t)xchg_u32bit((uint32_t) value, pos1, pos2);
}

/// @brief Exchange (swap) two bit positions in a signed 64-bit integer
/// @details Wrapper function that converts signed value to unsigned, performs bit exchange,
///          then converts back to signed. Swaps bits at positions pos1 and pos2.
/// @param value The signed 64-bit integer to modify
/// @param pos1 First bit position to exchange (0-63, where 0 is LSB)
/// @param pos2 Second bit position to exchange (0-63)
/// @return Modified value with bits at pos1 and pos2 exchanged, or 0 if positions are invalid
/// @note Prints error message to console if pos1 or pos2 exceed valid range (0-63)
int64_t xchg_64bit(int64_t value, uint8_t pos1, uint8_t pos2) {
    return (int64_t)xchg_u64bit((uint64_t) value, pos1, pos2);
}

#endif // METACORE___CLITE_BITUTILITYS_XCHG_BIT_H