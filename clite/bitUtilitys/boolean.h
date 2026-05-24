/**
 * @file boolean.h
 * @brief A compact boolean container for managing multiple boolean values in a single byte
 * @details Provides a boolean structure and operations to efficiently store and manipulate
 *          up to 8 independent boolean values using bit-level operations. Each bit position
 *          (0-7) represents one boolean value, making this ideal for applications requiring
 *          efficient storage of multiple boolean flags.
 *
 * @author Ali Lafi
 * @date 2025 / 9 / 25
 * 
 * @note Position 0 represents the least significant bit (LSB) and position 7 the most significant bit (MSB).
 * @note All functions preserve the original value and return new structures (immutable design).
 * 
 * Functions provided:
 * - set(): Set or reset a boolean value at a specified bit position
 * - get(): Retrieve the boolean value at a specified bit position
 * - empty(): Create an empty boolean structure (all bits 0)
 * - isEmpty(): Check if a boolean structure is empty
 * 
 * Usage example:
 * @code
 * boolean flags = empty();              // Create empty structure
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

#ifndef METACORE___CLITE_BITUTILITYS_BOOLEAN_H
#define METACORE___CLITE_BITUTILITYS_BOOLEAN_H

/// @brief A structure representing an 8-bit boolean value that can store multiple boolean states
/// @details This structure encapsulates an 8-bit unsigned integer (uint8_t) to store multiple
///          boolean values, one for each bit position (0-7). This allows efficient storage
///          and manipulation of up to 8 independent boolean values in a single byte.
/// @members value The underlying 8-bit unsigned integer storing the boolean flags
typedef struct { uint8_t value; } boolean;

/// @brief Set or reset the boolean value at position 0
/// @param current The current boolean structure
/// @param value The boolean value to set
/// @return A new boolean structure with the specified bit modified
boolean set(boolean current, bool value) {
    return value ? (boolean){set_u8bit(current.value, 0)} 
                 : (boolean){reset_u8bit(current.value, 0)};
}

/// @brief Retrieve the boolean value at position 0
/// @param current The current boolean structure
/// @return The boolean value at position 0 (true for 1, false for 0)
bool get(boolean current) {
    return get_u8bit(current.value, 0);
}

/// @brief Set or reset a boolean bit at a specified position
/// @details Creates a new boolean structure with the bit at the specified position set to the
///          provided boolean value. If value is true, the bit is set to 1; if false, it's reset to 0.
/// @param current The current boolean structure
/// @param value The boolean value to set (true sets bit, false resets bit)
/// @param position The bit position to modify (0-7, where 0 is LSB)
/// @return A new boolean structure with the specified bit modified
/// @note Position 0 represents the least significant bit (LSB)
boolean set_in(boolean current, bool value, uint8_t position) {
    return value ? (boolean){set_u8bit(current.value, position)} 
                 : (boolean){reset_u8bit(current.value, position)};
}

/// @brief Retrieve the boolean value at a specified bit position
/// @details Extracts and returns the boolean value stored at the specified bit position
///          in the boolean structure. Returns true if the bit is 1, false if the bit is 0.
/// @param current The boolean structure to read from
/// @param position The bit position to read (0-7, where 0 is LSB)
/// @return The boolean value at the specified position (true for 1, false for 0)
/// @note Position 0 represents the least significant bit (LSB)
bool get_in(boolean current, uint8_t position) {
    return get_u8bit(current.value, position);
}

/// @brief Create an empty boolean structure (all bits set to 0)
/// @details Initializes and returns a new boolean structure with all bits set to 0,
///          representing an empty or unset state.
/// @return A new boolean structure with value 0 (all bits cleared)
/// @note This function is commonly used to initialize a fresh boolean container
boolean empty() {
    return (boolean){0};
}

/// @brief Check if a boolean structure is empty (all bits are 0)
/// @details Compares the provided boolean structure to an empty boolean structure
///          and returns true if they are equal (i.e., all bits are 0).
/// @param current The boolean structure to check
/// @return true if the structure is empty (all bits are 0), false otherwise
bool isEmpty(boolean current) {
    return (current.value == (uint8_t)0) ? true : false;
}

#endif // METACORE___CLITE_BITUTILITYS_BOOLEAN_H