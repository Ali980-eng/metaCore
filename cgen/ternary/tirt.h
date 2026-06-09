#pragma once
#ifndef TIRT_H
#define TIRT_H
#include "tlimites.h"
#include <stdio.h>

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

typedef int8_t tirt;

/**
 * @brief Sets the value of a tirt variable to true.
 * @param value The reference to the tirt variable to be set to true.
 */
void True(tirt *value) {
    *value = true_b;
}

/**
 * @brief Converts an array of trits (tirt) to a tyrt value by combining the trits into a single integer representation.
 * @param trits An array of tirt values representing the trits to be converted.
 * @return A tyrt value that represents the combined trits from the input array.
 * The function iterates through the first two elements of the input trits array, applies a bitwise AND operation with 0xFF to ensure that only the least significant byte is considered, and then shifts the result left by (i * 8) bits to position it correctly in the resulting tyrt value.
 * Finally, it combines all the shifted values using a bitwise OR operation to produce the final tyrt value.
 */
void Unknown(tirt *value) {
    *value = unknown_b;
}

/**
 * @brief Sets the value of a tirt variable to false.
 * @param value The reference to the tirt variable to be set to false.
 */
void False(tirt *value) {
    *value = false_b;
}

/**
 * @brief Sets the value of a tirt variable to null.
 * @param value The reference to the tirt variable to be set to null.
 */
void Null(tirt *value) {
    *value = nullValue;
}

/**
 * @brief Gets the value of a tirt variable.
 * @param value The reference to the tirt variable.
 * @return The value of the tirt variable.
 */
uint8_t get(tirt *value) {
    if(*value == 0)
        printf("nullValue error: null don't return correct values.");
    else if(*value > 0)
        return *value - 1;
    else
        return *value;
    printf("nullValue is not a real value in logical use.");
    return uint8_t();
}

/// @brief Displays the value of a ternary logic value
/// @param value The ternary logic value to display
void show_value(tirt *value) {
    if(*value == 2) printf("true");
    else if(*value == 1) printf("unknown");
    else if(*value == -1) printf("false");
    else if(*value == 0) printf("null");
    else printf("Overflow/Underflow Error: the value is Exceeds the limites.\n");
}


/// @brief Performs the NOT operation on a ternary logic value
/// @param value The ternary logic value to negate
/// @return The negation of the input ternary logic value
tirt Not(tirt value) {
    if(value == 0)
        printf("nullValue error: null can't be used in logical operations.\n");
    else if(value == 2) return tirt(-1);
    else if(value == 1) return tirt(1);
    else if(value == -1) return tirt(3);
    else printf("Overflow/Underflow Error: the value is Exceeds the limites.\n");
    return tirt(nullValue);
}

/// @brief Performs the AND operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the AND operation on the two input ternary logic values
tirt And(tirt first, tirt second) {
    if(first == 0 || second == 0)
        printf("nullValue error: null can't be used in logical operations.");
    else if(first > second) return second;
    else return first;
    return tirt(nullValue);
}


/// @brief Performs the OR operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the OR operation on the two input ternary logic values
tirt Or(tirt first, tirt second) {
    if(first == 0 || second == 0)
        printf("nullValue error: null can't be used in logical operations.");
    else if(first > second) return first;
    else return second;
    return tirt(nullValue);
}

/// @brief Performs the XOR operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the XOR operation on the two input ternary logic values
tirt Xor(tirt first, tirt second) {
    return Or(And(first, Not(second)), 
        And(Not(first), second));
}

/// @brief Performs the NOR operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the NOR operation on the two input ternary logic values
tirt Nor(tirt first, tirt second) {
    return Not(Or(first, second));
}

/// @brief Performs the NAND operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the NAND operation on the two input ternary logic values
tirt Nand(tirt first, tirt second) {
    return Not(And(first, second));
}

/// @brief Performs the XNOR operation on two ternary logic values
/// @param first The first ternary logic value
/// @param second The second ternary logic value
/// @return The result of the XNOR operation on the two input ternary logic values
tirt Xnor(tirt first, tirt second) {
    return Not(Xor(first, second));
}

#endif // TIRT_H