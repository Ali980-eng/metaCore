# Bit Toggle Utilities

-----------------------

This C++ header file provides functions to toggle (flip) bits at specified positions in various integer types. The operations perform XOR with a bitmask to flip the bit from 0 to 1 or 1 to 0.

## Functions

### Bitwise Operations

* `toggle_u8bit(uint8_t num, uint8_t position)`
	+ Toggles bit at specified position (0-7) in unsigned 8-bit integer.
* `toggle_u16bit(uint16_t num, uint8_t position)`
	+ Toggles bit at specified position (0-15) in unsigned 16-bit integer.
* `toggle_u32bit(uint32_t num, uint8_t position)`
	+ Toggles bit at specified position (0-31) in unsigned 32-bit integer.
* `toggle_u64bit(uint64_t num, uint8_t position)`
	+ Toggles bit at specified position (0-63) in unsigned 64-bit integer.
* `toggle_8bit(int8_t num, uint8_t position)`
	+ Toggles bit at specified position (0-7) in signed 8-bit integer.
* `toggle_16bit(int16_t num, uint8_t position)`
	+ Toggles bit at specified position (0-15) in signed 16-bit integer.
* `toggle_32bit(int32_t num, uint8_t position)`
	+ Toggles bit at specified position (0-31) in signed 32-bit integer.
* `toggle_64bit(int64_t num, uint8_t position)`
	+ Toggles bit at specified position (0-63) in signed 64-bit integer.

#### Character and Short Integer Operations

* `toggle_char_bit(char c, uint8_t position)`
	+ Toggles bit at specified position (0-7) in character.
* `toggle_short_bit(short num, uint8_t position)`
	+ Toggles bit at specified position (0-15) in short integer.

### Usage Example

```cpp
#include "toggle_bit.h"

int main() {
    // Toggle a signed 8-bit integer
    int8_t num = -5;
    uint8_t position = 2; // 3rd bit from the right
    printf("Before toggle: %d\n", num);
    num = toggle_8bit(num, position); // Toggles bit at position 2
    printf("After toggle: %d\n", num);

    return 0;
}
```

Note: This code assumes that the input values are valid and do not overflow or wrap around. Additionally, this implementation does not handle cases where the input value is outside the range of the specified integer type.
