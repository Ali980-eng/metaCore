/**
 * @file binaryFormat.h
 * @brief Binary Format Conversion Utilities
 * @author MetaCore Development Team
 * @date May 25, 2026
 * 
 * @details
 * This file provides functions to convert various integer types to their binary string representation.
 * It includes utilities for converting 8-bit, 16-bit, 32-bit, and 64-bit signed and unsigned integers,
 * as well as functions to print binary representations directly to output.
 * 
 * @functions
 * - bool2char()      : Convert boolean to character ('0' or '1')
 * - bit_str_char()   : Convert char to binary string
 * - bit_str_short()  : Convert short to binary string
 * - bit_str_int()    : Convert int to binary string
 * - bit_str_long()   : Convert long to binary string
 * - bit8_str()       : Convert int8_t to binary string
 * - bit16_str()      : Convert int16_t to binary string
 * - bit32_str()      : Convert int32_t to binary string
 * - bit64_str()      : Convert int64_t to binary string
 * - ubit8_str()      : Convert uint8_t to binary string
 * - ubit16_str()     : Convert uint16_t to binary string
 * - ubit32_str()     : Convert uint32_t to binary string
 * - ubit64_str()     : Convert uint64_t to binary string
 * - print8bit()      : Print binary representation of int8_t
 * - print16bit()     : Print binary representation of int16_t
 * - print32bit()     : Print binary representation of int32_t
 * - print64bit()     : Print binary representation of int64_t
 * - print_u8bit()    : Print binary representation of uint8_t
 * - print_u16bit()   : Print binary representation of uint16_t
 * - print_u32bit()   : Print binary representation of uint32_t
 * - print_u64bit()   : Print binary representation of uint64_t
 */

#include "get_bit.h"
#include <stdlib.h>

#ifndef METACORE___CLITE_BITUTILITYS_BINARYFORMAT_H
#define METACORE___CLITE_BITUTILITYS_BINARYFORMAT_H

/**
 * @brief Converts a boolean value to its character representation ('0' or '1').
 * @param value The boolean value to convert.
 * @return The character representation of the boolean value.
 * This function takes a boolean value and returns '0' if the value is false, and '1' if the value is true.
 * It does this by adding the boolean value (which is either 0 or 1) to the character '0', resulting in the correct character representation.
 * Example usage:
 *   bool value = true;
 *  char result = bool2char(value); // result will be '1'
 *  value = false;
 *  result = bool2char(value); // result will be '0'
 */
char bool2char(bool value) {
    return (char)('0' + value);
}

/**
 * @brief Converts a char value to its binary string representation.
 * @param value The char value to convert.
 * @param high2low If true, the binary string will be ordered from high bit to low bit; if false, it will be ordered from low bit to high bit.
 * @return A dynamically allocated string representing the binary format of the char value. The caller is responsible for freeing this memory.
 */
char* bit_str_char(char value, bool high2low) {
    char* result = (char*) malloc(9);
    
    if (result == NULL)
        return NULL;
    
    for(uint8_t i = 7; i >= 0; i--)
        result[i] = bool2char(get_char_bit(value, i));
    
    result[8] = '\0';
    return result;
}

/**
 * @brief Converts a short value to its binary string representation.
 * @param value The short value to convert.
 * @return A dynamically allocated string representing the binary format of the short value. The caller is responsible for freeing this memory.
 */
char* bit_str_short(short value) {
    char* result = (char*) malloc(8 * sizeof(short) + 1);
    
    if (result == NULL)
        return NULL;

    for(uint8_t i = 8 * sizeof(short) - 1; i >= 0; i--)
        result[i] = bool2char(get_short_bit(value, i));
    
    result[8 * sizeof(short)] = '\0';
    return result;
}

/**
 * @brief Converts an int value to its binary string representation.
 * @param value The int value to convert.
 * @return A dynamically allocated string representing the binary format of the int value. The caller is responsible for freeing this memory.
 */
char* bit_str_int(int value) {
    char* result = (char*) malloc(8 * sizeof(int) + 1);

    if (result == NULL)
        return NULL;

    for(uint8_t i = 8 * sizeof(int) - 1; i >= 0; i--)
        result[i] = bool2char(get_int_bit(value, i));
    
    result[8 * sizeof(int)] = '\0';
    return result;
}

/**
 * @brief Converts a long value to its binary string representation.
 * @param value The long value to convert.
 * @return A dynamically allocated string representing the binary format of the long value. The caller is responsible for freeing this memory.
 */
char* bit_str_long(long value) {
    char* result = (char*) malloc(8 * sizeof(long) + 1);
    
    if (result == NULL)
        return NULL;

    for(uint8_t i = 8 * sizeof(long) - 1; i >= 0; i--)
        result[i] = bool2char(get_long_bit(value, i));

    result[8 * sizeof(long)] = '\0';
    return result;
}

/**
 * @brief Converts an 8-bit signed integer to its binary string representation.
 * @param value The value to convert.
 * @return A dynamically allocated string representing the binary format. Caller must free memory.
 */
char* bit8_str(int8_t value) {
    char* result = (char*) malloc(9);
    
    if (result == NULL)
        return NULL;

    for(uint8_t i = 7; i >= 0; i--) 
        result[i] = bool2char(get_u8bit(value, i));

    result[8] = '\0';
    return result;
}

/**
 * @brief Converts a 16-bit signed integer to its binary string representation.
 * @param value The value to convert.
 * @return A dynamically allocated string representing the binary format. Caller must free memory.
 */
char* bit16_str(int16_t value) {
    char* result = (char*) malloc(17);

    if (result == NULL) 
        return NULL;

    for(uint8_t i = 15; i >= 0; i--) 
        result[i] = bool2char(get_16bit(value, i));
    
    result[16] = '\0';
    return result;
}

/**
 * @brief Converts a 32-bit signed integer to its binary string representation.
 * @param value The value to convert.
 * @return A dynamically allocated string representing the binary format. Caller must free memory.
 */
char* bit32_str(int32_t value) {
    char* result = (char*) malloc(33);

    if (result == NULL)
        return NULL;

    for(uint8_t i = 31; i >= 0; i--)
        result[i] = bool2char(get_32bit(value, i));
    
    result[32] = '\0';
    return result;
}

/**
 * @brief Converts a 64-bit signed integer to its binary string representation.
 * @param value The value to convert.
 * @return A dynamically allocated string representing the binary format. Caller must free memory.
 */
char* bit64_str(int64_t value) {
    char* result = (char*) malloc(65);

    if (result == NULL)
        return NULL;

    for(uint8_t i = 63; i >= 0; i--)
        result[i] = bool2char(get_64bit(value, i));

    result[64] = '\0';
    return result;
}


/**
 * @brief Converts an 8-bit unsigned integer to its binary string representation.
 * @param value The value to convert.
 * @return A dynamically allocated string representing the binary format. Caller must free memory.
 */
char* ubit8_str(uint8_t value) {
    char* result = (char*) malloc(9);

    if (result == NULL)
        return NULL;

    for(uint8_t i = 7; i >= 0; i--)
        result[i] = bool2char(get_u8bit(value, i));

    result[8] = '\0';
    return result;
}

/**
 * @brief Converts a 16-bit unsigned integer to its binary string representation.
 * @param value The value to convert.
 * @return A dynamically allocated string representing the binary format. Caller must free memory.
 */
char* ubit16_str(uint16_t value) {
    char* result = (char*) malloc(17);

    if (result == NULL) 
        return NULL;

    for(uint8_t i = 15; i >= 0; i--)
        result[i] = bool2char(get_u8bit(value, i));

    result[16] = '\0';
    return result;
}

/**
 * @brief Converts a 32-bit unsigned integer to its binary string representation.
 * @param value The value to convert.
 * @return A dynamically allocated string representing the binary format. Caller must free memory.
 */
char* ubit32_str(uint32_t value) {
    char* result = (char*) malloc(33);

    if (result == NULL)
        return NULL;

    for(uint8_t i = 31; i >= 0; i--)
        result[i] = bool2char(get_u8bit(value, i));

    result[32] = '\0';
    return result;
}

/**
 * @brief Converts a 64-bit unsigned integer to its binary string representation.
 * @param value The value to convert.
 * @return A dynamically allocated string representing the binary format. Caller must free memory.
 */
char* ubit64_str(uint64_t value) {
    char* result = (char*) malloc(65);

    if (result == NULL)
        return NULL;

    for(uint8_t i = 63; i >= 0; i--)
        result[i] = bool2char(get_u8bit(value, i));
    
    result[64] = '\0';
    return result;
}

/**
 * @brief Prints the binary representation of an 8-bit signed integer.
 * @param value The value to print.
 * @param pnl If true, prints a newline after the binary representation.
 */
void print8bit(int8_t value, bool pnl) {
    for(uint8_t i = 7; i >= 0; i--)
        printf("%c", bool2char(get_8bit(value, i)));
    if(pnl) printf("%c", '\n');
}

/**
 * @brief Prints the binary representation of a 16-bit signed integer.
 * @param value The value to print.
 * @param pnl If true, prints a newline after the binary representation.
 */
void print16bit(int16_t value, bool pnl) {
    for(uint8_t i = 15; i >= 0; i--)
        printf("%c", bool2char(get_16bit(value, i)));
    if(pnl) printf("%c", '\n');
}

/**
 * @brief Prints the binary representation of a 32-bit signed integer.
 * @param value The value to print.
 * @param pnl If true, prints a newline after the binary representation.
 */
void print32bit(int32_t value, bool pnl) {
    for(uint8_t i = 31; i >= 0; i--)
        printf("%c", bool2char(get_32bit(value, i)));
    if(pnl) printf("%c", '\n');
}

/**
 * @brief Prints the binary representation of a 64-bit signed integer.
 * @param value The value to print.
 * @param pnl If true, prints a newline after the binary representation.
 */
void print64bit(int64_t value, bool pnl) {
    for(uint8_t i = 63; i >= 0; i--)
        printf("%c", bool2char(get_64bit(value, i)));
    if(pnl) printf("%c", '\n');
}

/**
 * @brief Prints the binary representation of an 8-bit unsigned integer.
 * @param value The value to print.
 * @param pnl If true, prints a newline after the binary representation.
 */
void print_u8bit(uint8_t value, bool pnl) {
    for(uint8_t i = 7; i >= 0; i--)
        printf("%c", bool2char(get_u8bit(value, i)));
    if(pnl) printf("%c", '\n');
}

/**
 * @brief Prints the binary representation of a 16-bit unsigned integer.
 * @param value The value to print.
 * @param pnl If true, prints a newline after the binary representation.
 */
void print_u16bit(uint16_t value, bool pnl) {
    for(uint8_t i = 15; i >= 0; i--)
        printf("%c", bool2char(get_u16bit(value, i)));
    if(pnl) printf("%c", '\n');
}

/**
 * @brief Prints the binary representation of a 32-bit unsigned integer.
 * @param value The value to print.
 * @param pnl If true, prints a newline after the binary representation.
 */
void print_u32bit(uint32_t value, bool pnl) {
    for(uint8_t i = 31; i >= 0; i--)
        printf("%c", bool2char(get_u32bit(value, i)));
    if(pnl) printf("%c", '\n');
}

/**
 * @brief Prints the binary representation of a 64-bit unsigned integer.
 * @param value The value to print.
 * @param pnl If true, prints a newline after the binary representation.
 */
void print_u64bit(uint64_t value, bool pnl) {
    for(uint8_t i = 63; i >= 0; i--)
        printf("%c", bool2char(get_u64bit(value, i)));
    if(pnl) printf("%c", '\n');
}

#endif // METACORE___CLITE_BITUTILITYS_BINARYFORMAT_H