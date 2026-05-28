# Bit Exchange Operations

-----------------------

## Description

This C++ header file provides functions for exchanging (swapping) two bit positions in various integer data types, including signed and unsigned 8-bit, 16-bit, 32-bit, and 64-bit integers. The functions validate input positions and return 0 if positions exceed the valid range.

### Functions

#### Unsigned Variants

* `xchg_u8bit`: Exchanges two bit positions in an 8-bit unsigned integer.
* `xchg_u16bit`: Exchanges two bit positions in a 16-bit unsigned integer.
* `xchg_u32bit`: Exchanges two bit positions in a 32-bit unsigned integer.
* `xchg_u64bit`: Exchanges two bit positions in a 64-bit unsigned integer.

#### Signed Variants

* `xchg_8bit`: Exchanges two bit positions in a signed 8-bit integer (wrapper function that converts signed value to unsigned).
* `xchg_16bit`: Exchanges two bit positions in a signed 16-bit integer.
* `xchg_32bit`: Exchanges two bit positions in a signed 32-bit integer.
* `xchg_64bit`: Exchanges two bit positions in a signed 64-bit integer.

### Usage Example

```c
#include "get_bit.h"

int main() {
    uint8_t value = 0b10100101;
    int8_t modified_value = xchg_u8bit(value, 0, 7);
    printf("%u\n", modified_value); // Output: 0x00100001

    return 0;
}
```

Note that this code snippet demonstrates the usage of only the unsigned variants and does not include signed variants.
