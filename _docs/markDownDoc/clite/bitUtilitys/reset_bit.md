# Bit Reset Utilities

-----------------------

This C++ header file provides functions to reset (clear to 0) bits at specified positions in various integer types.

## Usage Example

-----------------------

```cpp
#include "reset_bit.h"

int main() {
    // Clear bit at position 2 for an unsigned 8-bit number
    uint8_t num = 255;
    uint8_t position = 2;
    uint8_t result = reset_u8bit(num, position);
    
    // Print the modified value
    printf("Result: %u\n", result);

    return 0;
}
```

## Functions

-----------------------

### Bit Reset Functions

* `reset_u8bit(uint8_t num, uint8_t position)`
    * Resets bit at specified position to 0 in unsigned 8-bit integer.
    * Position (0-7) indicates the bit to be cleared.
* `reset_u16bit(uint16_t num, uint8_t position)`
    * Resets bit at specified position to 0 in unsigned 16-bit integer.
    * Position (0-15) indicates the bit to be cleared.
* `reset_u32bit(uint32_t num, uint8_t position)`
    * Resets bit at specified position to 0 in unsigned 32-bit integer.
    * Position (0-31) indicates the bit to be cleared.
* `reset_u64bit(uint64_t num, uint8_t position)`
    * Resets bit at specified position to 0 in unsigned 64-bit integer.
    * Position (0-63) indicates the bit to be cleared.
* `reset_8bit(int8_t num, uint8_t position)`
    * Resets bit at specified position to 0 in signed 8-bit integer.
    * Position (0-7) indicates the bit to be cleared.
* `reset_16bit(int16_t num, uint8_t position)`
    * Resets bit at specified position to 0 in signed 16-bit integer.
    * Position (0-15) indicates the bit to be cleared.
* `reset_32bit(int32_t num, uint8_t position)`
    * Resets bit at specified position to 0 in signed 32-bit integer.
    * Position (0-31) indicates the bit to be cleared.
* `reset_64bit(int64_t num, uint8_t position)`
    * Resets bit at specified position to 0 in signed 64-bit integer.
    * Position (0-63) indicates the bit to be cleared.

## Notes

-----------------------

* The `reset` functions perform an AND operation with an inverted bitmask to ensure the bit is set to 0.
* The positions are 0-based, meaning the leftmost position is 0.
