/**
 * This library provides a way to represent and manipulate ternary logic values using a single byte (uint8_t).
 * The values are represented as follows:
 * - Null: (0 in decimal)
 * - False: (-1 in decimal)
 * - Unknown: (1 in decimal)
 * - True: (2 in decimal)
 * @author ali lafi
 * @version 1.0
 * @date 2026-05-02
 */

#include "tlimites.h"
#include <stdio.h>
#include <stdint.h>

#ifndef METACORE___CGEN_TERNARY_TIRT_H
#define METACORE___CGEN_TERNARY_TIRT_H

#ifdef __cplusplus
#ifdef METACORE___META_HPP
namespace meta {
namespace cgen {
#endif // METACORE___META_HPP
#endif

typedef int8_t tirt;

/**
 * @brief Sets the value of a tirt variable to true.
 * @param value The reference to the tirt variable to be set to true.
 */
static inline void tirt_true(tirt *value) {
    *value = true_b;
}

/**
 * @brief Converts an array of trits (tirt) to a tyrt value by combining the trits into a single integer representation.
 * @param trits An array of tirt values representing the trits to be converted.
 * @return A tyrt value that represents the combined trits from the input array.
 * The function iterates through the first two elements of the input trits array, applies a bitwise AND operation with 0xFF to ensure that only the least significant byte is considered, and then shifts the result left by (i * 8) bits to position it correctly in the resulting tyrt value.
 * Finally, it combines all the shifted values using a bitwise OR operation to produce the final tyrt value.
 */
static inline void tirt_unknown(tirt *value) {
    *value = unknown_b;
}

/**
 * @brief Sets the value of a tirt variable to false.
 * @param value The reference to the tirt variable to be set to false.
 */
static inline void tirt_false(tirt *value) {
    *value = false_b;
}

/**
 * @brief Sets the value of a tirt variable to null.
 * @param value The reference to the tirt variable to be set to null.
 */
static inline void tirt_null(tirt *value) {
    *value = nullValue;
}

/**
 * @brief Gets the value of a tirt variable.
 * @param value The reference to the tirt variable.
 * @return The value of the tirt variable.
 */
static inline uint8_t tirt_get(tirt *value) {
    if(*value == 0)
        printf("nullValue error: null don't return correct values.");
    else if(*value > 0)
        return *value - 1;
    else
        return *value;
    printf("nullValue is not a real value in logical use.");
    return (uint8_t) 0;
}

/// @brief Displays the value of a ternary logic value
/// @param value The ternary logic value to display
static inline void tirt_show_value(tirt *value) {
    if(*value == 2) printf("true");
    else if(*value == 1) printf("unknown");
    else if(*value == -1) printf("false");
    else if(*value == 0) printf("null");
    else printf("Overflow/Underflow Error: the value is Exceeds the limites.\n");
}


/// @brief Performs the NOT operation on a ternary logic value
/// @param value The ternary logic value to negate
/// @return The negation of the input ternary logic value
static inline tirt tirt_not(tirt value) {
    tirt temp = 0;
    if(value == 0) {
        printf("nullValue error: null can't be used in logical operations.\n");
        temp = 0;
    } else if(value == 2) {
        temp = -1;
    } else if(value == 1) {
        temp = 1;
    } else if(value == -1) {
        temp = 3;
    } else {
        printf("Overflow/Underflow Error: the value is Exceeds the limites.\n");
        temp = 0;
    }
    return temp;
}

/// @brief Performs the AND operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the AND operation on the two input ternary logic values
static inline tirt tirt_and(tirt first, tirt second) {
    if(first == 0 || second == 0)
        printf("nullValue error: null can't be used in logical operations.");
    else if(first > second) return second;
    else return first;
    return (tirt) nullValue;
}


/// @brief Performs the OR operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the OR operation on the two input ternary logic values
static inline tirt tirt_or(tirt first, tirt second) {
    if(first == 0 || second == 0)
        printf("nullValue error: null can't be used in logical operations.");
    else if(first > second) return first;
    else return second;
    return (tirt) nullValue;
}

/// @brief Performs the XOR operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the XOR operation on the two input ternary logic values
static inline tirt tirt_xor(tirt first, tirt second) {
    return tirt_or(tirt_and(first, tirt_not(second)), 
        tirt_and(tirt_not(first), second));
}

/// @brief Performs the NOR operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the NOR operation on the two input ternary logic values
static inline tirt tirt_nor(tirt first, tirt second) {
    return tirt_not(tirt_or(first, second));
}

/// @brief Performs the NAND operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the NAND operation on the two input ternary logic values
static inline tirt tirt_nand(tirt first, tirt second) {
    return tirt_not(tirt_and(first, second));
}

/// @brief Performs the XNOR operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the XNOR operation on the two input ternary logic values
static inline tirt tirt_xnor(tirt first, tirt second) {
    return tirt_not(tirt_xor(first, second));
}

#ifdef __cplusplus
#ifdef METACORE___META_HPP
}}
#endif // METACORE___META_HPP
#endif

#endif // METACORE___CGEN_TERNARY_TIRT_H