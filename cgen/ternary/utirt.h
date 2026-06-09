#pragma once
#ifndef UTIRT_H
#define UTIRT_H
#include "tlimites.h"
#include <stdio.h>

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

typedef uint8_t utirt;

/// @brief Sets the high bit of a ternary logic value
/// @param value The ternary logic value to modify
void set_high(utirt *value) { *value |= 2; }

/// @brief Sets the low bit of a ternary logic value
/// @param value The ternary logic value to modify
void set_low(utirt *value) { *value |= 1; }

/// @brief Resets the high bit of a ternary logic value
/// @param value The ternary logic value to modify
void reset_high(utirt *value) { *value &= 1; }

/// @brief Resets the low bit of a ternary logic value
/// @param value The ternary logic value to modify
void reset_low(utirt *value) { *value &= 2; }

/// @brief Sets the high bit of a ternary logic value based on a boolean condition
/// @param value The ternary logic value to modify
/// @param newValue The boolean value to set
void set_high(utirt *value, bool newValue) {
    if(newValue) set_high(value);
    else reset_high(value);
}

/// @brief Sets the low bit of a ternary logic value based on a boolean condition
/// @param value The ternary logic value to modify
/// @param newValue The boolean value to set
void set_low(utirt *value, bool newValue) {
    if(newValue) set_low(value);
    else reset_low(value);
}

/// @brief Sets a bit of a ternary logic value based on a boolean condition
/// @param value The ternary logic value to modify
/// @param islow A boolean indicating whether to modify the low bit
/// @param newValue The boolean value to set
void set(utirt *value, bool islow, bool newValue) {
    if(islow) {
        if(newValue) set_low(value);
        else reset_low(value);
    }
    else {
        if(newValue) set_high(value);
        else reset_high(value);
    }
}

/// @brief to set a ternary logic value to true
/// @param value The ternary logic value to modify
void True(utirt *value) { *value = true_u; }

/// @brief to set a ternary logic value to unknown
/// @param value The ternary logic value to modify
void Unknown(utirt *value) { *value = unknown_u; }

/// @brief to set a ternary logic value to false
/// @param value The ternary logic value to modify
void False(utirt *value) { *value = false_u; }

/// @brief to set a ternary logic value to null
/// @param value The ternary logic value to modify
void Null(utirt *value) { *value = nullValue; }

/// @brief Displays the value of a ternary logic value
/// @param value The ternary logic value to display
void show_value(utirt *value) {
    if(*value == 3) printf("true");
    else if(*value == 2) printf("unknown");
    else if(*value == 1) printf("false");
    else if(*value == 0) printf("null");
}


/// @brief Performs the NOT operation on a ternary logic value
/// @param value The ternary logic value to negate
/// @return The negation of the input ternary logic value
utirt Not(utirt value) {
    if(value == 3) return utirt(1);
    else if(value == 2) return utirt(2);
    else if(value == 1) return utirt(3);
    else return utirt(0);
}

/// @brief Performs the AND operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the AND operation on the two input ternary logic values
utirt And(utirt first, utirt second) {
    if(first > second) return second;
    else return first;
}


/// @brief Performs the OR operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the OR operation on the two input ternary logic values
utirt Or(utirt first, utirt second) {
    if(first > second) return first;
    else return second;
}

/// @brief Performs the XOR operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the XOR operation on the two input ternary logic values
utirt Xor(utirt first, utirt second) {
    return Or(And(first, Not(second)), 
        And(Not(first), second));
}

/// @brief Performs the NOR operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the NOR operation on the two input ternary logic values
utirt Nor(utirt first, utirt second) {
    return Not(Or(first, second));
}

/// @brief Performs the NAND operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the NAND operation on the two input ternary logic values
utirt Nand(utirt first, utirt second) {
    return Not(And(first, second));
}

/// @brief Performs the XNOR operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the XNOR operation on the two input ternary logic values
utirt Xnor(utirt first, utirt second) {
    return Not(Xor(first, second));
}

#endif // UTIRT_H