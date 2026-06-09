/**
 * @file B27.h
 * @author ali lafi
 * @version 1.0
 * @date 2026-05-03
 */

#include <stdio.h>
#include "tlimites.h"

#ifndef METACORE___CGEN_TERNARY_B27_H
#define METACORE___CGEN_TERNARY_B27_H

#ifdef __cplusplus
#ifdef METACORE___META_HPP
namespace meta {
namespace cgen {
#endif // METACORE___META_HPP
#endif

/// @brief An array of characters representing the values of a B27 variable.
const char* B27Chars[27] = {
    "(-D)", "(-C)", "(-B)", "(-A)",
    "(-9)", "(-8)", "(-7)", "(-6)",
    "(-5)", "(-4)", "(-3)", "(-2)",
    "(-1)", "(0)", "(1)", "(2)",
    "(3)", "(4)", "(5)", "(6)",
    "(7)", "(8)", "(9)", "(A)",
    "(B)", "(C)", "(D)"
};

typedef int8_t B27;

/// @brief Sets the value of a B27 variable.
/// @param value A reference to the B27 variable to set.
/// @param newValue The new value to assign.
static inline void b27_set(B27 *value, int8_t newValue) {
    if(newValue > 13 || newValue < -13) {
        printf("Overflow/Underflow error");
        return;
    }
    *value = newValue;
}

/// @brief Returns the character representation of the B27 value.
/// @param value The B27 value to convert.
/// @return The character representation of the value.
static inline const char* b27_get(B27 value) {
    if(value > 13 || value < -13) {
        printf("Overflow/Underflow error");
        return B27Chars[13];
    }
    if(value < 0) return B27Chars[-1 * value];
    else return B27Chars[value + 13];
}

#ifdef __cplusplus
#ifdef METACORE___META_HPP
}}
#endif // METACORE___META_HPP
#endif

#endif // METACORE___CGEN_TERNARY_B27_H