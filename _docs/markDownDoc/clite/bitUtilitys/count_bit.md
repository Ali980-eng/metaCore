# Bit Count Utilities

---------------------

This C++ header file provides functions to count set (1) or unset (0) bits in various integer types.

## Description

The `count_bit.h` file offers a range of functions for analyzing bit patterns and determining bit populations. These utilities are designed to be useful for examining the contents of binary data, such as images, audio files, or network packets.

## Functions

### Bit Count Utilities

* `count_u8bit(uint8_t num, bool ones)`: Counts set (1) or unset (0) bits in a 8-bit value.
* `count_u16bit(uint16_t num, bool ones)`: Counts set (1) or unset (0) bits in a 16-bit value.
* `count_u32bit(uint32_t num, bool ones)`: Counts set (1) or unset (0) bits in a 32-bit value.
* `count_u64bit(uint64_t num, bool ones)`: Counts set (1) or unset (0) bits in a 64-bit value.

### Signed Bit Count Utilities

* `count_8bit(int8_t num, bool ones)`: Counts set (1) or unset (0) bits in a signed 8-bit value.
* `count_16bit(int16_t num, bool ones)`: Counts set (1) or unset (0) bits in a signed 16-bit value.
* `count_32bit(int32_t num, bool ones)`: Counts set (1) or unset (0) bits in a signed 32-bit value.
* `count_64bit(int64_t num, bool ones)`: Counts set (1) or unset (0) bits in a signed 64-bit value.

### Character Bit Count Utilities

* `count_char_bit(char c, bool ones)`: Counts set (1) or unset (0) bits in a character.
* `count_short_bit(short num, bool ones)`: Counts set (1) or unset (0) bits in a short integer.

### Usage Example

```cpp
#include "count_bit.h"

int main() {
    // Create a signed 8-bit value
    int8_t num = -5;
    
    // Count the number of set bits (1's)
    uint8_t count_u8bit = count_8bit(num, true);
    printf("Number of set bits: %u\n", count_u8bit);
    
    return 0;
}
```

This example demonstrates how to use the `count_8bit` function to count the number of set bits (1's) in a signed 8-bit value.
