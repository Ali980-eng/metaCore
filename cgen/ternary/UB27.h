#pragma once
#ifndef UB27_H
#define UB27_H
#include <stdio.h>
#include "tlimites.h"

/**
 * @file UB27.h
 * @author ali lafi
 * @version 1.0
 * @date 2026-05-03
 */

/// @brief An array of characters representing the values of a UB27 variable.
const char UB27Chars[27] = {
    '0', '1', '2', '3', '4', '5',
    '6', '7', '8', '9', 'A', 'B',
    'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q'
};

typedef uint8_t UB27;

/// @brief Sets the value of a UB27 variable.
/// @param value A reference to the UB27 variable to set.
/// @param newValue The new value to assign.
void set(UB27 *value, uint8_t newValue) {
    if(newValue >= 27) {
        printf("Overflow error");
        return;
    }
    *value = newValue;
}

/// @brief Returns the character representation of the UB27 value.
/// @param value The UB27 value to convert.
/// @return The character representation of the value.
char get(UB27 value) {
    if(value >= 27) {
        printf("Overflow error");
        return UB27Chars[26];
    }
    return UB27Chars[value];
}

#endif // UB27_H