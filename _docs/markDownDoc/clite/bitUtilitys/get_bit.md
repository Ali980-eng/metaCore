# Bit Retrieval Utilities for Reading Individual Bits from Integers

---------------------

This header provides a comprehensive set of functions for reading or retrieving the value of individual bits at specified positions from various integer types.

## Functions

### Bit Widths

#### 8-bit (u8)

* `get_u8bit(num, position)`: Returns true if bit is 1, false if bit is 0.
* `get_8bit(num, position)`: Returns true if bit is 1, false if bit is 0.

#### 16-bit (u16)

* `get_u16bit(num, position)`: Returns true if bit is 1, false if bit is 0.
* `get_16bit(num, position)`: Returns true if bit is 1, false if bit is 0.

#### 32-bit (u32)

* `get_u32bit(num, position)`: Returns true if bit is 1, false if bit is 0.
* `get_32bit(num, position)`: Returns true if bit is 1, false if bit is 0.

#### 64-bit (u64)

* `get_u64bit(num, position)`: Returns true if bit is 1, false if bit is 0.
* `get_64bit(num, position)`: Returns true if bit is 1, false if bit is 0

### Signed Bit Types

#### 8-bit (int8)

* `get_8bit(num, position)`: Returns true if bit is 1, false if bit is 0.
* `get_8bit(num, position)` is a wrapper for `get_u8bit` as it's the same type.

#### 16-bit (int16)

* `get_16bit(num, position)`: Returns true if bit is 1, false if bit is 0.
* `get_16bit(num, position)`: Returns true if bit is 1, false if bit is 0.

#### 32-bit (int32)

* `get_32bit(num, position)`: Returns true if bit is 1, false if bit is 0.
* `get_32bit(num, position)`: Returns true if bit is 1, false if bit is 0.

#### 64-bit (int64)

* `get_64bit(num, position)`: Returns true if bit is 1, false if bit is 0.
* `get_64bit(num, position)`: Returns true if bit is 1, false if bit is 0.

### Non-Signed Bit Types

#### Character (char)

* `get_char_bit(c, position)`: Returns true if bit is 1, false if bit is 0.
