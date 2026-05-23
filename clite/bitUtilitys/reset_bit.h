#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef METACORE___CLITE_BITUTILITYS_RESET_BIT_H
#define METACORE___CLITE_BITUTILITYS_RESET_BIT_H

/// @brief Reset (clear) bit at specified position to 0 in 8-bit number
/// @param num The value to modify
/// @param position Bit position (0-7)
/// @return Modified value with bit cleared
uint8_t reset_u8bit(uint8_t num, uint8_t position) {
    if (position > 7) {
        printf("outOfRange Error: position must be 0-7\n");
        return num;
    }
    return num & ~(1 << position);
}

/// @brief Reset (clear) bit at specified position to 0 in 16-bit number
/// @param num The value to modify
/// @param position Bit position (0-15)
/// @return Modified value with bit cleared
uint16_t reset_u16bit(uint16_t num, uint8_t position) {
    if (position > 15) {
        printf("outOfRange Error: position must be 0-15\n");
        return num;
    }
    return num & ~(1U << position);
}

/// @brief Reset (clear) bit at specified position to 0 in 32-bit number
/// @param num The value to modify
/// @param position Bit position (0-31)
/// @return Modified value with bit cleared
uint32_t reset_u32bit(uint32_t num, uint8_t position) {
    if (position > 31) {
        printf("outOfRange Error: position must be 0-31\n");
        return num;
    }
    return num & ~(1UL << position);
}

/// @brief Reset (clear) bit at specified position to 0 in 64-bit number
/// @param num The value to modify
/// @param position Bit position (0-63)
/// @return Modified value with bit cleared
uint64_t reset_u64bit(uint64_t num, uint8_t position) {
    if (position > 63) {
        printf("outOfRange Error: position must be 0-63\n");
        return num;
    }
    return num & ~(1ULL << position);
}

/// @brief Reset (clear) bit at specified position to 0 in signed 8-bit number
/// @param num The value to modify
/// @param position Bit position (0-7)
/// @return Modified value with bit cleared
int8_t reset_8bit(int8_t num, uint8_t position) {
    if (position > 7) {
        printf("outOfRange Error: position must be 0-7\n");
        return num;
    }
    return num & ~(1 << position);
}

/// @brief Reset (clear) bit at specified position to 0 in signed 16-bit number
/// @param num The value to modify
/// @param position Bit position (0-15)
/// @return Modified value with bit cleared
int16_t reset_16bit(int16_t num, uint8_t position) {
    if (position > 15) {
        printf("outOfRange Error: position must be 0-15\n");
        return num;
    }
    return num & ~(1 << (position & 0xF));
}

/// @brief Reset (clear) bit at specified position to 0 in signed 32-bit number
/// @param num The value to modify
/// @param position Bit position (0-31)
/// @return Modified value with bit cleared
int32_t reset_32bit(int32_t num, uint8_t position) {
    if (position > 31) {
        printf("outOfRange Error: position must be 0-31\n");
        return num;
    }
    return num & ~(1L << position);
}

/// @brief Reset (clear) bit at specified position to 0 in signed 64-bit number
/// @param num The value to modify
/// @param position Bit position (0-63)
/// @return Modified value with bit cleared
int64_t reset_64bit(int64_t num, uint8_t position) {
    if (position > 63) {
        printf("outOfRange Error: position must be 0-63\n");
        return num;
    }
    return num & ~(1LL << position);
}

/// @brief Reset (clear) bit at specified position to 0 in character
/// @param c The character to modify
/// @param position Bit position (0-7)
/// @return Modified character with bit cleared
char reset_char_bit(char c, uint8_t position) {
    return (char)reset_u8bit((uint8_t)c, position);
}

/// @brief Reset (clear) bit at specified position to 0 in short integer
/// @param num The value to modify
/// @param position Bit position (0-15)
/// @return Modified value with bit cleared
short reset_short_bit(short num, uint8_t position) {
    return (short)reset_16bit((int16_t)num, position);
}

/// @brief Reset (clear) bit at specified position to 0 in integer
/// @param num The value to modify
/// @param position Bit position (0-31)
/// @return Modified value with bit cleared
int reset_int_bit(int num, uint8_t position) {
    return (int)reset_32bit((int32_t)num, position);
}

/// @brief Reset (clear) bit at specified position to 0 in long integer
/// @param num The value to modify
/// @param position Bit position (0-63)
/// @return Modified value with bit cleared
long reset_long_bit(long num, uint8_t position) {
    return (long)reset_64bit((int64_t)num, position);
}

#endif // METACORE___CLITE_BITUTILITYS_RESET_BIT_H