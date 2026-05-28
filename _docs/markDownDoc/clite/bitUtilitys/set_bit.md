# Bit Set Utilities

-----------------------

## Overview

This C++ header file provides functions to set bits at specified positions in various integer types. It supports 8-bit, 16-bit, 32-bit, and 64-bit signed and unsigned integers.

### Functions

#### Bit Setting Functions

* `set_u8bit(uint8_t num, uint8_t position)`: Set a single bit (0-7) to 1 in an 8-bit unsigned integer.
* `set_u16bit(uint16_t num, uint8_t position)`: Set a single bit (0-15) to 1 in a 16-bit unsigned integer.
* `set_u32bit(uint32_t num, uint8_t position)`: Set a single bit (0-31) to 1 in a 32-bit unsigned integer.
* `set_u64bit(uint64_t num, uint8_t position)`: Set a single bit (0-63) to 1 in a 64-bit unsigned integer.
* `set_8bit(int8_t num, uint8_t position)`: Set a single bit (0-7) to 1 in an 8-bit signed integer.

#### Bit Mask Functions

* `set_char_bit(char c, uint8_t position)`: Set a single bit (0-7) to 1 in a character.
* `set_short_bit(short num, uint8_t position)`: Set a single bit (0-15) to 1 in a short integer.

#### Bit Setting Functions for Specific Data Types

* `set_int_bit(int num, uint8_t position)`: Set the corresponding bit (0-31) in an integer.
* `set_long_bit(long num, uint8_t position)`: Set the corresponding bit (0-63) in a long integer.

### Usage Example

```c
#include <iostream>

int main() {
    int num = 10; // signed 32-bit integer
    char c = 'A'; // character

    std::cout << "Before setting bit: " << num << ", " << c << std::endl;

    set_u8bit(num, 1); // Set single bit to 1 in 8-bit unsigned integer
    set_char_bit(c, 0);

    return 0;
}
```

This example sets the first bit (position 0) of a signed 32-bit integer `num` and a character `c` to 1.
