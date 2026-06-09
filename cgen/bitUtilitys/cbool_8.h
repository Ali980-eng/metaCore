/**
 * @file cbool_8.h
 * @brief A compact cbool_8 container for managing multiple cbool_8 values in a single byte
 * @details Provides a cbool_8 structure and operations to efficiently store and manipulate
 *          up to 8 independent cbool_8 values using bit-level operations. Each bit position
 *          (0-7) represents one cbool_8 value, making this ideal for applications requiring
 *          efficient storage of multiple cbool_8 flags.
 *
 * @author Ali Lafi
 * @date 2025 / 9 / 25
 * 
 * @note Position 0 represents the least significant bit (LSB) and position 7 the most significant bit (MSB).
 * @note All functions preserve the original value and return new structures (immutable design).
 * 
 * Functions provided:
 * - set(): Set or reset a cbool_8 value at a specified bit position
 * - get(): Retrieve the cbool_8 value at a specified bit position
 * - empty(): Create an empty cbool_8 structure (all bits 0)
 * - isEmpty(): Check if a cbool_8 structure is empty
 * 
 * Usage example:
 * @code
 * cbool_8 flags = empty();              // Create empty structure
 * flags = set(flags, true, 0);          // Set bit 0 to true
 * flags = set(flags, true, 1);          // Set bit 1 to true
 * bool bit0 = get(flags, 0);            // Read bit 0 (returns true)
 * bool isEmpty_check = isEmpty(flags);  // Returns false
 * @endcode
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "get_bit.h"
#include "reset_bit.h"
#include "set_bit.h"

#ifndef METACORE___CGEN_BITUTILITYS_CBOOL_8_H
#define METACORE___CGEN_BITUTILITYS_CBOOL_8_H

#ifdef __cplusplus
#ifdef METACORE___META_HPP
namespace meta {
namespace cgen {
#endif // METACORE___META_HPP
#endif

/// @brief A structure representing an 8-bit cbool_8 value that can store multiple cbool_8 states
/// @details This structure encapsulates an 8-bit unsigned integer (uint8_t) to store multiple
///          cbool_8 values, one for each bit position (0-7). This allows efficient storage
///          and manipulation of up to 8 independent cbool_8 values in a single byte.
/// @members value The underlying 8-bit unsigned integer storing the cbool_8 flags
typedef struct { uint8_t value; } cbool_8;

/// @brief Set or reset the cbool_8 value at position 0
/// @param current The current cbool_8 structure
/// @param value The cbool_8 value to set
/// @return A new cbool_8 structure with the specified bit modified
static inline cbool_8 set(cbool_8 current, bool value) {
    return value ? (cbool_8){set_u8bit(current.value, 0)} : (cbool_8){reset_u8bit(current.value, 0)};
}

/// @brief Retrieve the cbool_8 value at position 0
/// @param current The current cbool_8 structure
/// @return The cbool_8 value at position 0 (true for 1, false for 0)
static inline bool get(cbool_8 current) {
    return get_u8bit(current.value, 0);
}

/// @brief Set or reset a cbool_8 bit at a specified position
/// @details Creates a new cbool_8 structure with the bit at the specified position set to the
///          provided cbool_8 value. If value is true, the bit is set to 1; if false, it's reset to 0.
/// @param current The current cbool_8 structure
/// @param value The cbool_8 value to set (true sets bit, false resets bit)
/// @param position The bit position to modify (0-7, where 0 is LSB)
/// @return A new cbool_8 structure with the specified bit modified
/// @note Position 0 represents the least significant bit (LSB)
static inline cbool_8 set_in(cbool_8 current, bool value, uint8_t position) {
    return value ? (cbool_8){set_u8bit(current.value, position)} 
                 : (cbool_8){reset_u8bit(current.value, position)};
}

/// @brief Retrieve the cbool_8 value at a specified bit position
/// @details Extracts and returns the cbool_8 value stored at the specified bit position
///          in the cbool_8 structure. Returns true if the bit is 1, false if the bit is 0.
/// @param current The cbool_8 structure to read from
/// @param position The bit position to read (0-7, where 0 is LSB)
/// @return The cbool_8 value at the specified position (true for 1, false for 0)
/// @note Position 0 represents the least significant bit (LSB)
static inline bool get_in(cbool_8 current, uint8_t position) {
    return get_u8bit(current.value, position);
}

/// @brief Create an empty cbool_8 structure (all bits set to 0)
/// @details Initializes and returns a new cbool_8 structure with all bits set to 0,
///          representing an empty or unset state.
/// @return A new cbool_8 structure with value 0 (all bits cleared)
/// @note This function is commonly used to initialize a fresh cbool_8 container
static inline cbool_8 empty() {
    return (cbool_8){0};
}

/// @brief Check if a cbool_8 structure is empty (all bits are 0)
/// @details Compares the provided cbool_8 structure to an empty cbool_8 structure
///          and returns true if they are equal (i.e., all bits are 0).
/// @param current The cbool_8 structure to check
/// @return true if the structure is empty (all bits are 0), false otherwise
static inline bool isEmpty(cbool_8 current) {
    return (current.value == (uint8_t)0) ? true : false;
}

#ifdef __cplusplus
#ifdef METACORE___META_HPP
}}
#endif // METACORE___META_HPP
#endif

#endif // METACORE___CGEN_BITUTILITYS_CBOOL_8_H