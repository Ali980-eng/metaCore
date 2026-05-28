# Micro Definitions and Utility Macros

-----------------------

This file provides comprehensive macro definitions for constant declarations, object definitions, and testing utilities. It has two main modes controlled by `COBJECT_DATA`:

1. **Standard Mode**: Testing utilities and string operations
2. **Non-Strict Mode (Optional)**: Type inference macros in non-strict mode

## Functions

-----------------------

### Constant Declaration Macros

| Name | Purpose |
| --- | --- |
| cbool | Declare a boolean constant |
| cchar | Declare a character constant |
| cint | Declare an integer constant |
| cfloat | Declare a floating-point constant |
| cdouble | Declare a double-precision floating-point constant |
| clong | Declare a long integer constant |
| cuint | Declare a uint unsigned integer constant |
| cstring | Declare a string constant |
| cnl | Character literal (newline) |
| ctab | Character literal (tab) |

### Array Definitions

| Name | Purpose |
| --- | --- |
| carray_i32 | Define an array of 32-bit integers |
| carray_f64 | Define an array of 64-bit floating-point numbers |
| carray | Define a general-purpose array type |

### Section Attribute for Memory Placement (COBJECT_DATA)

* `DATA_SEC` defines the section where data will be placed in memory

## Standard Mode Functions

-----------------------

### Testing Utilities and String Operations

#### printSummary

Prints a summary of test results, including passed, failed, and total tests.

#### MAIN_TEST(name)

Runs a specific test with a given name.

#### EXIT_TEST(PS)

Exits the program if the specified number of tests (PS) fail.

#### TEST_0(cond)

Runs a test conditionally based on the value of cond.

#### TEST_1(cond, msg)

Runs a test conditionally based on the value of cond and prints an error message if it fails.

#### TEST_2(real, expected)

Runs a test that checks for equality between real and expected values.

#### TEST_3(real, expected, msg)

Runs a test that checks for equality between real and expected values and prints an error message if it fails.

#### ASSERT(cond)

Checks if the given condition is true. If false, prints an error message and exits the program with a non-zero exit code.

### Assertion Macro (cassert)

A custom assertion macro similar to `assert` in C99.

### Object/Struct Definition Macro (cobject)

Defines a struct or object type.

#### cobject(name, elements)

Type definition of a struct or object named name with elements elements.

## Non-Strict Mode Functions

-----------------------

### Type Inference Macros

* `cauto`: Allows for type inference in non-strict mode
* `cdynamic`: Uses the same type as `const __typeof__` to infer types

### Optional Logic Restriction Macros (ALLOW_LOGIC_MODE)

* `if ERROR_LOGIC_NOT_ALLOWED`
* `switch ERROR_LOGIC_NOT_ALLOWED`

## Example Usage

-----------------------

```c
#include "micros.h"

int main() {
    // Print test summary
    printSummary();

    // Run a test
    ASSERT(true);

    // Perform some operations
    length("Hello, World!");
    equal("Hello, World!", "Hello, Universe!");

    // Exit the program if tests fail
    EXIT_TEST(5);
}
```

Note: This is just a summary of the code. If you have any specific questions or need further clarification on certain aspects, feel free to ask!
