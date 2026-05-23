#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef METACORE___CLITE_BITUTILITYS_GET_BIT_H
#define METACORE___CLITE_BITUTILITYS_GET_BIT_H

/// @brief Get bit value at specified position from 8-bit number
/// @param num The value to read
/// @param position Bit position (0-7)
/// @return True if bit is 1, false if bit is 0
bool get_u8bit(uint8_t num, uint8_t position) {
    if (position > 7) {
        printf("outOfRange Error: position must be 0-7\n");
        return false;
    }
    return (num >> position) & 1;
}

/// @brief Get bit value at specified position from 16-bit number
/// @param num The value to read
/// @param position Bit position (0-15)
/// @return True if bit is 1, false if bit is 0
bool get_u16bit(uint16_t num, uint8_t position) {
    if (position > 15) {
        printf("outOfRange Error: position must be 0-15\n");
        return false;
    }
    return (num >> position) & 1;
}

/// @brief Get bit value at specified position from 32-bit number
/// @param num The value to read
/// @param position Bit position (0-31)
/// @return True if bit is 1, false if bit is 0
bool get_u32bit(uint32_t num, uint8_t position) {
    if (position > 31) {
        printf("outOfRange Error: position must be 0-31\n");
        return false;
    }
    return (num >> position) & 1;
}

/// @brief Get bit value at specified position from 64-bit number
/// @param num The value to read
/// @param position Bit position (0-63)
/// @return True if bit is 1, false if bit is 0
bool get_u64bit(uint64_t num, uint8_t position) {
    if (position > 63) {
        printf("outOfRange Error: position must be 0-63\n");
        return false;
    }
    return (num >> position) & 1;
}

/// @brief Get bit value at specified position from signed 8-bit number
/// @param num The value to read
/// @param position Bit position (0-7)
/// @return True if bit is 1, false if bit is 0
bool get_8bit(int8_t num, uint8_t position) {
    if (position > 7) {
        printf("outOfRange Error: position must be 0-7\n");
        return false;
    }
    return (num >> position) & 1;
}

/// @brief Get bit value at specified position from signed 16-bit number
/// @param num The value to read
/// @param position Bit position (0-15)
/// @return True if bit is 1, false if bit is 0
bool get_16bit(int16_t num, uint8_t position) {
    if (position > 15) {
        printf("outOfRange Error: position must be 0-15\n");
        return false;
    }
    return (num >> position) & 1;
}

/// @brief Get bit value at specified position from signed 32-bit number
/// @param num The value to read
/// @param position Bit position (0-31)
/// @return True if bit is 1, false if bit is 0
bool get_32bit(int32_t num, uint8_t position) {
    if (position > 31) {
        printf("outOfRange Error: position must be 0-31\n");
        return false;
    }
    return (num >> position) & 1;
}

/// @brief Get bit value at specified position from signed 64-bit number
/// @param num The value to read
/// @param position Bit position (0-63)
/// @return True if bit is 1, false if bit is 0
bool get_64bit(int64_t num, uint8_t position) {
    if (position > 63) {
        printf("outOfRange Error: position must be 0-63\n");
        return false;
    }
    return (num >> position) & 1;
}

/// @brief Get bit value at specified position from character
/// @param c The character to read
/// @param position Bit position (0-7)
/// @return True if bit is 1, false if bit is 0
bool get_char_bit(char c, uint8_t position) {
    return get_u8bit((uint8_t)c, position);
}

/// @brief Get bit value at specified position from short integer
/// @param num The value to read
/// @param position Bit position (0-15)
/// @return True if bit is 1, false if bit is 0
bool get_short_bit(short num, uint8_t position) {
    return get_16bit((int16_t)num, position);
}

/// @brief Get bit value at specified position from integer
/// @param num The value to read
/// @param position Bit position (0-31)
/// @return True if bit is 1, false if bit is 0
bool get_int_bit(int num, uint8_t position) {
    return get_32bit((int32_t)num, position);
}

/// @brief Get bit value at specified position from long integer
/// @param num The value to read
/// @param position Bit position (0-63)
/// @return True if bit is 1, false if bit is 0
bool get_long_bit(long num, uint8_t position) {
    return get_64bit((int64_t)num, position);
}

#endif // METACORE___CLITE_BITUTILITYS_GET_BIT_H