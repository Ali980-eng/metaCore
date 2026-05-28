# Boolean Structure and Operations

---------------------

## Description

This C++ header file provides a compact boolean container for managing multiple boolean values in a single byte. It includes functions to set or reset individual bits, retrieve the value of a specific bit position, create an empty structure, check if a structure is empty, and more.

## Functions

### `set(boolean current, bool value)`

* Sets or resets a boolean value at a specified bit position
* Creates a new boolean structure with the bit at the specified position set to the provided boolean value. If value is true, the bit is set to 1; if false, it's reset to 0.

### `get(boolean current)`

* Retrieves the boolean value at a specified bit position
* Returns the boolean value stored at the specified bit position in the boolean structure. Returns true if the bit is 1, false if the bit is 0.

### `empty()`

* Creates an empty boolean structure (all bits set to 0)
* Initializes and returns a new boolean structure with all bits set to 0, representing an empty or unset state.

### `isEmpty(boolean current)`

* Checks if a boolean structure is empty (all bits are 0)
* Compares the provided boolean structure to an empty boolean structure and returns true if they are equal (i.e., all bits are 0).

## Usage Example

```c
#include "boolean.h"

// Create an empty boolean structure
boolean flags = empty();

// Set bit 0 to true
flags = set(flags, true, 0);

// Read the value of bit 0
bool bit0 = get(flags, 0);
printf("Bit 0: %s\n", (bit0 ? "true" : "false"));

// Check if the structure is empty
bool isEmpty_check = isEmpty(flags);
printf("Is struct empty? %s\n", (isEmpty_check ? "yes" : "no"));
```

This example demonstrates how to use the `set` and `get` functions to manipulate a boolean value in a 8-bit unsigned integer.
