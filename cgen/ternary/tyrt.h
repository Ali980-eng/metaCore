/**
 * @file tyrt.h
 * @author ali lafi
 * @version 1.0
 * @date 2026-05-03
 */

#include "tirt.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef METACORE___CGEN_TERNARY_TYRT_H
#define METACORE___CGEN_TERNARY_TYRT_H

#ifdef __cplusplus
#ifdef METACORE___META_HPP
namespace meta {
namespace cgen {
#endif // METACORE___META_HPP
#endif

typedef int16_t tyrt;

/**
 * @brief Sets the value of a tyrt variable with overflow and underflow checks.
 * @param currentValue The reference to the tyrt variable to be set.
 * @param value The value to be assigned to the tyrt variable.
 * This function checks if the provided value exceeds the maximum or minimum limits of the tyrt data type.
 * If it does, an error message is printed and the function returns without modifying the currentValue.
 * Otherwise, currentValue is updated with the new value.
 */
static inline void tyrt_set(tyrt *currentValue, tyrt value) {
    if(value > MAX_VALUE_TYRT || value < MIN_VALUE_TYRT) {
        printf("Overflow/Underflow Error: the value exceeded the limits of the data type.");
        return;
    }
    *currentValue = value;
}

/**
 * @brief Sets the value of a tyrt variable at a specific position with overflow and underflow checks.
 * @param currentValue The reference to the tyrt variable to be set.
 * @param value The value to be assigned to the tyrt variable at the specified position.
 * @param position The position (0 or 1) where the value should be set in the tyrt variable.
 * This function checks if the provided position is valid (0 or 1) and if the value exceeds the maximum or minimum limits of the tirt data type.
 * If any of these conditions are violated, an error message is printed and the function returns without modifying the currentValue.
 * Otherwise, the specified value is set at the given position in the currentValue variable.
 */
static inline void tyrt_set_tirt(tyrt *currentValue, tirt value, uint8_t position) {
    if(position > 1) {
        printf("Position Error: the position exceeded the limits of the data type.");
        return;
    }
    if(value > MAX_VALUE_TIRT || value < MIN_VALUE_TIRT) {
        printf("Overflow/Underflow Error: the value exceeded the limits of the data type.");
        return;
    }
    *currentValue &= ~(0xFF << (position * 8));
    *currentValue |= (value << (position * 8));
}

/**
 * @brief Sets the value of a tyrt variable with overflow and underflow checks.
 * @param currentValue The reference to the tyrt variable to be set.
 * @param value The value to be assigned to the tyrt variable.
 * This function checks if the provided value exceeds the maximum or minimum limits of the tyrt data type.
 * If it does, an error message is printed and the function returns without modifying the currentValue.
 * Otherwise, currentValue is updated with the new value.
 */
static inline void tyrt_set_16(tyrt *currentValue, int16_t value) {
    if(value > MAX_VALUE_TYRT || value < MIN_VALUE_TYRT) {
        printf("Overflow/Underflow Error: the value exceeded the limits of the data type.");
        return;
    }
    *currentValue = value;
}

/**
 * @brief Returns the size of the tyrt data type in bits or bytes.
 * @param value The reference to the tyrt variable (not used in the function but included for consistency).
 * @param inBits A boolean flag indicating whether to return the size in bits (true) or bytes (false).
 * @return size of the tyrt data type, which is 12 bits (1.5 bytes) when inBits is true, and 2 bytes when inBits is false.
 */
static inline uint8_t tyrt_size(tyrt *value, bool inBits) {
    if(inBits) return 12;
    else return 2;
}

/**
 * @brief Converts a tyrt value to an array of tirt values representing its trits.
 * @param value The tyrt value to be converted.
 * @return An array of tirt values representing the trits of the input tyrt value.
 * The array has a size of 6, where each element corresponds to a trit (2 bits) of the tyrt value.
 * The first element represents the least significant trit, and the second element represents the next trit.
 * This function extracts the trits from the input tyrt value by right-shifting the value and masking it with 0xFF to obtain the individual trit values.
 * The resulting array of tirt values can be used for further logical operations or manipulations as needed.
 */
static tirt *tyrt2trits(tyrt value) {
    tirt *trits = (int8_t*) malloc(6 * sizeof(tirt));
    for(int i = 0; i < 2; i++) {
        trits[i] = (value >> (i * 8)) & 0xFF;
    }
    return trits;
}

/**
 * @brief Converts an array of tirt values representing trits back to a tyrt value.
 * @param trits The array of tirt values representing the trits to be converted.
 * The array should have a size of 6, where each element corresponds to a trit (2 bits) of the resulting tyrt value.
 * The first element represents the least significant trit, and the second element represents the next trit.
 * @return A tyrt value constructed from the input array of tirt values.
 * The function combines the trits by left-shifting each trit value and performing a bitwise OR operation to accumulate the final tyrt value.
 * This allows for the reconstruction of the original tyrt value from its trit representation, enabling further logical operations or manipulations as needed.
 */
static inline tyrt tyrt_from_trits(tirt *trits) {
    tyrt value = 0;
    for(int i = 0; i < 2; i++) {
        value |= (trits[i] & 0xFF) << (i * 8);
    }
    return value;
}

/**
 * @brief Performs the AND operation on two tyrt values by applying the AND operation to their corresponding trits.
 * @param a The first tyrt value.
 * @param b The second tyrt value.
 * @return A tyrt value resulting from the AND operation applied to the corresponding trits of the input tyrt values.
 */
static tyrt tyrt_and(tyrt a, tyrt b) {
    tirt *tritsA = (int8_t*) malloc(6 * sizeof(tirt));
    tirt *tritsB = (int8_t*) malloc(6 * sizeof(tirt));
    tirt *resultTrits = (int8_t*) malloc(6 * sizeof(tirt));
    for(int i = 0; i < 2; i++) {
        tritsA[i] = (a >> (i * 8)) & 0xFF;
        tritsB[i] = (b >> (i * 8)) & 0xFF;
        resultTrits[i] = tirt_and(tritsA[i], tritsB[i]);
    }
    free(tritsA);
    free(tritsB);
    return tyrt_from_trits(resultTrits);
}

/**
 * @brief Performs the OR operation on two tyrt values by applying the OR operation to their corresponding trits.
 * @param a The first tyrt value.
 * @param b The second tyrt value.
 * @return A tyrt value resulting from the OR operation applied to the corresponding trits of the input tyrt values.
 * The function extracts the trits from each input tyrt value, applies the OR operation to each pair of corresponding trits, and then combines the resulting trits back into a single tyrt value using the fromTrits function.
 * This allows for the logical OR operation to be performed on the individual trits of the input tyrt values, yielding a new tyrt value that represents the result of the OR operation.
 */
static tyrt tyrt_or(tyrt a, tyrt b) {
    tirt *tritsA = (int8_t*) malloc(6 * sizeof(tirt));
    tirt *tritsB = (int8_t*) malloc(6 * sizeof(tirt));
    tirt *resultTrits = (int8_t*) malloc(6 * sizeof(tirt));
    for(int i = 0; i < 2; i++) {
        tritsA[i] = (a >> (i * 8)) & 0xFF;
        tritsB[i] = (b >> (i * 8)) & 0xFF;
        resultTrits[i] = tirt_or(tritsA[i], tritsB[i]);
    }
    free(tritsA);
    free(tritsB);
    return tyrt_from_trits(resultTrits);
}

/**
 * @brief Performs the XOR operation on two tyrt values by applying the XOR operation to their corresponding trits.
 * @param a The first tyrt value.
 * @param b The second tyrt value.
 * @return A tyrt value resulting from the XOR operation applied to the corresponding trits of the input tyrt values.
 * The function extracts the trits from each input tyrt value, applies the XOR operation to each pair of corresponding trits, and then combines the resulting trits back into a single tyrt value using the fromTrits function.
 * This allows for the logical XOR operation to be performed on the individual trits of the input tyrt values, yielding a new tyrt value that represents the result of the XOR operation.
 */
static tyrt tyrt_xor(tyrt a, tyrt b) {
    tirt *tritsA = (int8_t*) malloc(6 * sizeof(tirt));
    tirt *tritsB = (int8_t*) malloc(6 * sizeof(tirt));
    tirt *resultTrits = (int8_t*) malloc(6 * sizeof(tirt));
    for(int i = 0; i < 2; i++) {
        tritsA[i] = (a >> (i * 8)) & 0xFF;
        tritsB[i] = (b >> (i * 8)) & 0xFF;
        resultTrits[i] = tirt_xor(tritsA[i], tritsB[i]);
    }
    free(tritsA);
    free(tritsB);
    return tyrt_from_trits(resultTrits);
}

/**
 * @brief Performs the NOT operation on a tyrt value by applying the NOT operation to its corresponding trits.
 * @param a The tyrt value to be negated.
 * @return A tyrt value resulting from the NOT operation applied to the corresponding trits of the input tyrt value.
 * The function extracts the trits from the input tyrt value, applies the NOT operation to each trit, and then combines the resulting trits back into a single tyrt value using the fromTrits function.
 * This allows for the logical NOT operation to be performed on the individual trits of the input tyrt value, yielding a new tyrt value that represents the result of the NOT operation.
 */
static tyrt tyrt_not(tyrt a) {
    tirt *tritsA = (int8_t*) malloc(6 * sizeof(tirt));
    tirt *resultTrits = (int8_t*) malloc(6 * sizeof(tirt));
    for(int i = 0; i < 2; i++) {
        tritsA[i] = (a >> (i * 8)) & 0xFF;
        resultTrits[i] = tirt_not(tritsA[i]);
    }
    free(tritsA);
    return tyrt_from_trits(resultTrits);
}

/**
 * @brief Performs the NOR operation on two tyrt values by applying the NOR operation to their corresponding trits.
 * @param a The first tyrt value.
 * @param b The second tyrt value.
 * @return A tyrt value resulting from the NOR operation applied to the corresponding trits of the input tyrt values.
 */
static tyrt tyrt_nor(tyrt a, tyrt b) {
    return tyrt_not(or(a, b));
}

/**
 * @brief Performs the NAND operation on two tyrt values by applying the NAND operation to their corresponding trits.
 * @param a The first tyrt value.
 * @param b The second tyrt value.
 * @return A tyrt value resulting from the NAND operation applied to the corresponding trits of the input tyrt values.
 */
static tyrt tyrt_nand(tyrt a, tyrt b) {
    return tyrt_not(tyrt_and(a, b));
}

/**
 * @brief Performs the XNOR operation on two tyrt values by applying the XNOR operation to their corresponding trits.
 * @param a The first tyrt value.
 * @param b The second tyrt value.
 * @return A tyrt value resulting from the XNOR operation applied to the corresponding trits of the input tyrt values.
 */
static tyrt tyrt_xnor(tyrt a, tyrt b) {
    return tyrt_not(xor(a, b));
}

#ifdef __cplusplus
    #ifdef METACORE___META_HPP
    }}
    #endif // METACORE___META_HPP
#endif

#endif // METACORE___CGEN_TERNARY_TYRT_H