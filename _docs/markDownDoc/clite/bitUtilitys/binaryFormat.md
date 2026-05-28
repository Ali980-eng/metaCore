# Binary Format Conversion Utilities

---------------------

## Overview

This C++ header file provides a set of functions for converting various integer types to their binary string representation. The utilities include functions for converting boolean values, char values, short, int, long, and 64-bit unsigned integers.

### Functions

#### Boolean Value Conversion

* `bool2char(bool value)`: Converts a boolean value to its character representation ('0' or '1')
* `bit_str_char(char value, bool high2low)`: Converts a char value to its binary string representation
* `bit_str_int(int value)`: Converts an int value to its binary string representation

#### Short Value Conversion

* `bit_str_short(short value)`: Converts a short value to its binary string representation
* `print8bit(int8_t value, bool pnl)`: Prints the binary representation of an 8-bit signed integer with or without a newline character

#### Long Value Conversion

* `bit_str_long(long value)`: Converts a long value to its binary string representation
* `print16bit(int16_t value, bool pnl)`: Prints the binary representation of a 16-bit signed integer with or without a newline character
* `print32bit(int32_t value, bool pnl)`: Prints the binary representation of a 32-bit signed integer with or without a newline character
* `print64bit(int64_t value, bool pnl)`: Prints the binary representation of a 64-bit signed integer with or without a newline character

#### 8-Bit and 16-Bit Signed Value Conversion

* `bit8_str(int8_t value)`: Converts an 8-bit unsigned integer to its binary string representation
* `bit16_str(int16_t value)`: Converts a 16-bit unsigned integer to its binary string representation
* `print_u8bit(uint8_t value, bool pnl)`: Prints the binary representation of an 8-bit unsigned integer with or without a newline character
* `bit32_str(int32_t value)`: Converts a 32-bit signed integer to its binary string representation
* `print_u16bit(uint16_t value, bool pnl)`: Prints the binary representation of a 16-bit unsigned integer with or without a newline character
* `bit64_str(int64_t value)`: Converts a 64-bit signed integer to its binary string representation

#### 8-Bit and 16-Bit Unsigned Value Conversion

* `ubit8_str(uint8_t value)`: Converts an 8-bit unsigned integer to its binary string representation
* `print_u8bit(uint8_t value, bool pnl)`: Prints the binary representation of an 8-bit unsigned integer with or without a newline character
* `bit16_str(uint16_t value)`: Converts a 16-bit unsigned integer to its binary string representation
* `print_u16bit(uint16_t value, bool pnl)`: Prints the binary representation of a 16-bit unsigned integer with or without a newline character
* `bit32_str(uint32_t value)`: Converts a 32-bit unsigned integer to its binary string representation
* `print_u32bit(uint32_t value, bool pnl)`: Prints the binary representation of a 32-bit unsigned integer with or without a newline character
* `bit64_str(uint64_t value)`: Converts a 64-bit unsigned integer to its binary string representation

### Usage Example

```cpp
#include "binaryFormat.h"

int main() {
    uint8_t value = 255;
    char result[9];

    bit8_str(value, false);
    printf("Binary representation of %u: ", value);
    for (uint8_t i = 7; i >= 0; i--)
        printf("%c", bool2char(get_u8bit(result[i], true)));
    printf("\n");

    print16bit(255, true);

    return 0;
}
```

This example demonstrates the usage of various functions to convert integers to binary string representations. The `print8bit` function is used to print the binary representation of an 8-bit signed integer, while the `print16bit` function is used to print the binary representation of a 16-bit unsigned integer.
