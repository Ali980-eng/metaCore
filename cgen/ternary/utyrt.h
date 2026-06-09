/**
 * @file utirt.h
 * @author ali lafi
 * @version 1.0
 * @date 2026-05-03
 */

#include "utirt.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef METACORE___CGEN_TERNARY_UTYRT_H
#define METACORE___CGEN_TERNARY_UTYRT_H

#ifdef __cplusplus
#ifdef METACORE___META_HPP
namespace meta {
namespace cgen {
#endif // METACORE___META_HPP
#endif

typedef uint16_t utyrt;

/**
 * @brief Sets the value of a utyrt variable with overflow and underflow checks.
 * @param currentValue The reference to the utyrt variable to be set.
 * @param value The value to be assigned to the utyrt variable.
 * This function checks if the provided value exceeds the maximum or minimum limits of the utyrt data type.
 * If it does, an error message is printed and the function returns without modifying the currentValue
 */
static inline void utyrt_set(utyrt *currentValue, utyrt value) {
    if(value >= 729 || value < 0) {
        printf("Value out of range. Must be between 0 and 728.\n");
        return;
    }
    *currentValue = value;
}

/**
 * @brief Sets the value of a utyrt variable at a specific position with overflow and underflow checks.
 * @param currentValue The reference to the utyrt variable to be set.
 * @param value The value to be assigned to the utyrt variable at the specified position.
 * @param position The position (0 to 5) where the value should be set in the utyrt variable.
 * This function checks if the provided position is valid (0 to 5) and if the value exceeds the maximum or minimum limits of the utirt data type.
 * If any of these conditions are violated, an error message is printed and the function returns without
 */
static inline void utyrt_set_(utyrt *currentValue, utirt value, uint8_t position) {
    if(position > 1) {
        printf("Position out of range. Must be 0 or 1.\n");
        return;
    }
    if(value >= 27 || value < 0) {
        printf("Value out of range. Must be between 0 and 26.\n");
        return;
    }
    *currentValue &= ~(0x1F << (position * 5));
    *currentValue |= (value << (position * 5));
}

/**
 * @brief Resets the value of a utyrt variable to zero.
 * @param currentValue The reference to the utyrt variable to be reset.
 * This function sets all bits of the currentValue variable to zero, effectively resetting its value to zero.
 * This can be useful for clearing the value of a utyrt variable before assigning a new value or for initializing it to a known state.
 */
static inline void utyrt_reset(utyrt *currentValue) {
    *currentValue &= 0;
}

/**
 * @brief Gets the size of a utyrt variable.
 * @param value The utyrt variable.
 * @param inBits Whether to return the size in bits or bytes.
 * @return The size of the utyrt variable.
 */
static inline uint8_t utyrt_size(utyrt *value, bool inBits) {
    if(inBits) return 12;
    else return 2;
}

/**
 * @brief Converts a utyrt variable to an array of trits.
 * @param value The utyrt variable to be converted.
 * @return A pointer to the array of trits.
 */
static utirt *utyrt2trits(utyrt *value) {
    utirt *trits = (uint8_t*) malloc(6 * sizeof(utirt));
    for(int i = 0; i < 6; i++) {
        trits[i] = (*value >> (i * 5)) & 0x1F;
    }
    return trits;
}

/**
 * @brief Converts an array of trits to a utyrt variable.
 * @param trbits The array of trits to be converted.
 * @return The resulting utyrt variable.
 * This function takes an array of trits (utirt) and combines them into a single utyrt variable by left-shifting each trit value and performing a bitwise OR operation to accumulate the final utyrt value.
 */
static inline utyrt utyrt_from_trits(utirt trits[6]) {
    utyrt value = 0;
    for(int i = 0; i < 6; i++) {
        if(trits[i] >= 27 || trits[i] < 0) {
            printf("Trit value out of range. Must be between 0 and 26.\n");
            return 0;
        }
        value |= (trits[i] << (i * 5));
    }
    return value;
}

/**
 * @brief Performs the AND operation on two utyrt variables by applying the AND operation to their corresponding trits.
 * @param a The first utyrt variable.
 * @param b The second utyrt variable.
 * @return A utyrt variable resulting from the AND operation applied to the corresponding trits of the input utyrt variables.
 * This function extracts the trits from each input utyrt variable, applies the AND operation to each pair of corresponding trits, and then combines the resulting trits back into a single utyrt variable using the fromTrits function.
 */
static utyrt utyrt_and(utyrt *a, utyrt *b) {
    utirt *tempA = utyrt2trits(a);
    utirt *tempB = utyrt2trits(b);
    utyrt result = 0;
    for(int i = 0; i < 6; i++) {
        result |= And(tempA[i], tempB[i]) << (i * 5);
    }
    return result;
}

/**
 * @brief Performs the OR operation on two utyrt variables by applying the OR operation to their corresponding trits.
 * @param a The first utyrt variable.
 * @param b The second utyrt variable.
 * @return A utyrt variable resulting from the OR operation applied to the corresponding trits of the input utyrt variables.
 */
static utyrt utyrt_or(utyrt *a, utyrt *b) {
    utirt *tempA = utyrt2trits(a);
    utirt *tempB = utyrt2trits(b);
    utyrt result = 0;
    for(int i = 0; i < 6; i++) {
        result |= (tempA[i] > tempB[i] ? tempA[i] : tempB[i]) << (i * 5);
    }
    return result;
}

/**
 * @brief Performs the XOR operation on two utyrt variables by applying the XOR operation to their corresponding trits.
 * @param a The first utyrt variable.
 * @param b The second utyrt variable.
 * @return A utyrt variable resulting from the XOR operation applied to the corresponding trits of the input utyrt variables.
 */
static utyrt utyrt_xor(utyrt *a, utyrt *b) {
    utirt *tempA = utyrt2trits(a);
    utirt *tempB = utyrt2trits(b);
    utyrt result = 0;
    for(int i = 0; i < 6; i++) {
        result |= ((tempA[i] > tempB[i] ? tempA[i] : tempB[i]) - (tempA[i] > tempB[i] ? tempB[i] : tempA[i])) << (i * 5);
    }
    return result;
}

/**
 * @brief Performs the NOT operation on a utyrt variable by applying the NOT operation to its corresponding trits.
 * @param value The utyrt variable to be negated.
 * @return A utyrt variable resulting from the NOT operation applied to the corresponding trits
 */
static utyrt utyrt_not(utyrt *value) {
    utirt *temp = utyrt2trits(value);
    utyrt result = 0;
    for(int i = 0; i < 6; i++) {
        result |= (26 - temp[i]) << (i * 5);
    }
    return result;
}

/**
 * @brief Performs the NOR operation on two utyrt variables by applying the NOR operation to their corresponding trits.
 * @param a The first utyrt variable.
 * @param b The second utyrt variable.
 * @return A utyrt variable resulting from the NOR operation applied to the corresponding trits of the input utyrt variables.
 */
static inline utyrt utyrt_nor(utyrt *a, utyrt *b) {
    return utyrt_not(Or(a, b));
}

/**
 * @brief Performs the NAND operation on two utyrt variables by applying the NAND operation to their corresponding trits.
 * @param a The first utyrt variable.
 * @param b The second utyrt variable.
 * @return A utyrt variable resulting from the NAND operation applied to the corresponding trits of the input utyrt variables.
 */
static inline utyrt utyrt_nand(utyrt *a, utyrt *b) {
    return utyrt_not(utyrt_and(a, b));
}

/**
 * @brief Performs the XNOR operation on two utyrt variables by applying the XNOR operation to their corresponding trits.
 * @param a The first utyrt variable.
 * @param b The second utyrt variable.
 * @return A utyrt variable resulting from the XNOR operation applied to the corresponding tr
 */
static inline utyrt utyrt_xnor(utyrt *a, utyrt *b) {
    return utyrt_not(utyrt_xor(a, b));
}

/**
 * @brief Performs a left shift operation on a utyrt variable by a specified number of positions.
 * @param value The utyrt variable to be shifted.
 * @param positions The number of positions to shift the value to the left.
 * @return A utyrt variable resulting from the left shift operation applied to the input utyrt variable.
 */
static inline utyrt utyrt_shift_left(utyrt *value, uint8_t positions) {
    if(positions >= 12) {
        printf("Shift positions out of range. Must be between 0 and 11.\n");
        return 0;
    }
    return *value << (positions * 5);
}

/**
 * @brief Performs a right shift operation on a utyrt variable by a specified number of positions.
 * @param value The utyrt variable to be shifted.
 * @param positions The number of positions to shift the value to the right.
 * @return A utyrt variable resulting from the right shift operation applied to the input utyrt variable.
 */
static inline utyrt utyrt_shift_right(utyrt *value, uint8_t positions) {
    if(positions >= 12) {
        printf("Shift positions out of range. Must be between 0 and 11.\n");
        return 0;
    }
    return *value >> (positions * 5);
}

#ifdef __cplusplus
#ifdef METACORE___META_HPP
}}
#endif // METACORE___META_HPP
#endif

#endif // METACORE___CGEN_TERNARY_UTYRT_H