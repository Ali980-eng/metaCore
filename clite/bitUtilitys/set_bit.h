#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef METACORE___CLITE_BITUTILITYS_SET_BIT_H
#define METACORE___CLITE_BITUTILITYS_SET_BIT_H

/// @brief Set bit at specified position to 1 in 8-bit number
/// @param num The value to modify
/// @param position Bit position (0-7)
/// @return Modified value with bit set
uint8_t set_u8bit(uint8_t num, uint8_t position) {
    if (position > 7) {
        printf("OutOfRange Error: position must be 0-7\n");
        return num;
    }
    return num | (1 << position);
}

/// @brief Set bit at specified position to 1 in 16-bit number
/// @param num The value to modify
/// @param position Bit position (0-15)
/// @return Modified value with bit set
uint16_t set_u16bit(uint16_t num, uint8_t position) {
    if(position > 15) {
        printf("OutOfRange Error: position must be 0-15\n");
        return num;
    }
    return num | (1U << position);
}

/// @brief Set bit at specified position to 1 in 32-bit number
/// @param num The value to modify
/// @param position Bit position (0-31)
/// @return Modified value with bit set
uint32_t set_u32bit(uint32_t num, uint8_t position) {
    if(position > 31) {
        printf("outOfRange Error: position must be 0-31\n");
        return num;
    }
    return num | (1UL << position);
}

/// @brief Set bit at specified position to 1 in 64-bit number
/// @param num The value to modify
/// @param position Bit position (0-63)
/// @return Modified value with bit set
uint64_t set_u64bit(uint64_t num, uint8_t position) {
    if(position > 63) {
        printf("outOfRange Error: position must be 0-63\n");
        return num;
    }
    return num | (1ULL << position);
}

/// @brief Set bit at specified position to 1 in signed 8-bit number
/// @param num The value to modify
/// @param position Bit position (0-7)
/// @return Modified value with bit set
int8_t set_8bit(int8_t num, uint8_t position) {
    if (position > 7) {
        printf("OutOfRange Error: position must be 0-7\n");
        return num;
    }
    return num | (1 << position);
}

/// @brief Set bit at specified position to 1 in signed 16-bit number
/// @param num The value to modify
/// @param position Bit position (0-15)
/// @return Modified value with bit set
int16_t set_16bit(int16_t num, uint8_t position) {
    if(position > 15) {
        printf("OutOfRange Error: position must be 0-15\n");
        return num;
    }
    return num | (1 << (position & 0xF));
}

/// @brief Set bit at specified position to 1 in signed 32-bit number
/// @param num The value to modify
/// @param position Bit position (0-31)
/// @return Modified value with bit set
int32_t set_32bit(int32_t num, uint8_t position) {
    if(position > 31) {
        printf("outOfRange Error: position must be 0-31\n");
        return num;
    }
    return num | (1L << position);
}

/// @brief Set bit at specified position to 1 in signed 64-bit number
/// @param num The value to modify
/// @param position Bit position (0-63)
/// @return Modified value with bit set
int64_t set_64bit(int64_t num, uint8_t position) {
    if(position > 63) {
        printf("outOfRange Error: position must be 0-63\n");
        return num;
    }
    return num | (1LL << position);
}

/// @brief Set bit at specified position to 1 in character
/// @param c The character to modify
/// @param position Bit position (0-7)
/// @return Modified character with bit set
char set_char_bit(char c, uint8_t position) {
    return (char)set_u8bit((uint8_t)c, position);
}

/// @brief Set bit at specified position to 1 in short integer
/// @param num The value to modify
/// @param position Bit position (0-15)
/// @return Modified value with bit set
short set_short_bit(short num, uint8_t position) {
    return (short)set_16bit((int16_t)num, position);
}

/// @brief Set bit at specified position to 1 in integer
/// @param num The value to modify
/// @param position Bit position (0-31)
/// @return Modified value with bit set
int set_int_bit(int num, uint8_t position) {
    return (int)set_32bit((int32_t)num, position);
}

/// @brief Set bit at specified position to 1 in long integer
/// @param num The value to modify
/// @param position Bit position (0-63)
/// @return Modified value with bit set
long set_long_bit(long num, uint8_t position) {
    return (long)set_64bit((int64_t)num, position);
}

#endif // METACORE___CLITE_BITUTILITYS_SET_BIT_H