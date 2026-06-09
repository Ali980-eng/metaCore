/**
 * This library provides a way to represent and manipulate ternary logic values using a single byte (uint8_t).
 * The values are represented as follows:
 * - Null: 00 (0 in decimal)
 * - False: 01 (1 in decimal)
 * - Unknown: 10 (2 in decimal)
 * - True: 11 (3 in decimal)
 * @file utirt.h
 * @author ali lafi
 * @version 1.0
 * @date 2026-05-02
 */

#include "tlimites.h"
#include <stdio.h>
#include <stdbool.h>

#ifndef METACORE___CGEN_TERNARY_UTIRT_H
#define METACORE___CGEN_TERNARY_UTIRT_H

#ifdef __cplusplus
#ifdef METACORE___META_HPP
namespace meta {
namespace cgen {
#endif // METACORE___META_HPP
#endif

typedef uint8_t utirt;

/// @brief Sets the high bit of a ternary logic value
/// @param value The ternary logic value to modify
static inline void utirt_set_high(utirt *value) { *value |= 2; }

/// @brief Sets the low bit of a ternary logic value
/// @param value The ternary logic value to modify
static inline void utirt_set_low(utirt *value) { *value |= 1; }

/// @brief Resets the high bit of a ternary logic value
/// @param value The ternary logic value to modify
static inline void utirt_reset_high(utirt *value) { *value &= 1; }

/// @brief Resets the low bit of a ternary logic value
/// @param value The ternary logic value to modify
static inline void utirt_reset_low(utirt *value) { *value &= 2; }

/// @brief Sets the high bit of a ternary logic value based on a boolean condition
/// @param value The ternary logic value to modify
/// @param newValue The boolean value to set
static inline void utirt_set_high(utirt *value, bool newValue) {
    if(newValue) utirt_set_high(value);
    else utirt_reset_high(value);
}

/// @brief Sets the low bit of a ternary logic value based on a boolean condition
/// @param value The ternary logic value to modify
/// @param newValue The boolean value to set
static inline void utirt_set_low(utirt *value, bool newValue) {
    if(newValue) utirt_set_low(value);
    else utirt_reset_low(value);
}

/// @brief Sets a bit of a ternary logic value based on a boolean condition
/// @param value The ternary logic value to modify
/// @param islow A boolean indicating whether to modify the low bit
/// @param newValue The boolean value to set
static inline void utirt_set(utirt *value, bool islow, bool newValue) {
    if(islow) {
        if(newValue) utirt_set_low(value);
        else utirt_reset_low(value);
    }
    else {
        if(newValue) utirt_set_high(value);
        else utirt_reset_high(value);
    }
}

/// @brief to set a ternary logic value to true
/// @param value The ternary logic value to modify
static inline void utirt_true(utirt *value) { *value = true_u; }

/// @brief to set a ternary logic value to unknown
/// @param value The ternary logic value to modify
static inline void utirt_unknown(utirt *value) { *value = unknown_u; }

/// @brief to set a ternary logic value to false
/// @param value The ternary logic value to modify
static inline void utirt_false(utirt *value) { *value = false_u; }

/// @brief to set a ternary logic value to null
/// @param value The ternary logic value to modify
static inline void utirt_null(utirt *value) { *value = nullValue; }

/// @brief Displays the value of a ternary logic value
/// @param value The ternary logic value to display
static inline void utirt_show_value(utirt *value) {
    if(*value == 3) printf("true");
    else if(*value == 2) printf("unknown");
    else if(*value == 1) printf("false");
    else if(*value == 0) printf("null");
}

/// @brief Performs the NOT operation on a ternary logic value
/// @param value The ternary logic value to negate
/// @return The negation of the input ternary logic value
static inline utirt utirt_not(utirt value) {
    utirt temp;
    if(value == 3) temp = 1;
    else if(value == 2) temp = 2;
    else if(value == 1) temp = 3;
    else temp = 0;
    return temp;
}

/// @brief Performs the AND operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the AND operation on the two input ternary logic values
static inline utirt utirt_and(utirt first, utirt second) {
    if(first > second) return second;
    else return first;
}


/// @brief Performs the OR operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the OR operation on the two input ternary logic values
static inline utirt utirt_or(utirt first, utirt second) {
    if(first > second) return first;
    else return second;
}

/// @brief Performs the XOR operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the XOR operation on the two input ternary logic values
static inline utirt utirt_xor(utirt first, utirt second) {
    return utirt_or(utirt_and(first, utirt_not(second)), 
        utirt_and(utirt_not(first), second));
}

/// @brief Performs the NOR operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the NOR operation on the two input ternary logic values
static inline utirt utirt_nor(utirt first, utirt second) {
    return utirt_not(utirt_or(first, second));
}

/// @brief Performs the NAND operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the NAND operation on the two input ternary logic values
static inline utirt utirt_nand(utirt first, utirt second) {
    return utirt_not(utirt_and(first, second));
}

/// @brief Performs the XNOR operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the XNOR operation on the two input ternary logic values
static inline utirt utirt_xnor(utirt first, utirt second) {
    return utirt_not(utirt_xor(first, second));
}

#ifdef __cplusplus
#ifdef METACORE___META_HPP
}}
#endif // METACORE___META_HPP
#endif

#endif // METACORE___CGEN_TERNARY_UTIRT_H