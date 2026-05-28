# Exception Classes for Lite Library

-----------------------

The following is a summary of the C++ code that defines exception classes for the lite library:

## Exception Hierarchy

The lite library provides an exception hierarchy with several base classes, including `lite_exception`, `internal_exception`, and others. The exception hierarchy is organized into the following categories:

* `lite_exception`: Base class for all lite library exceptions.
* `internal_exception`: Thrown when internal errors occur within the lite library.
* `OutOfRange`: Exception for out-of-range access attempts.
* `undefined_behavior`: Thrown when undefined behavior is detected during execution.
* `wrong_indexing`, `wrong_declaration`, and `wrong_construction`: Exceptions for invalid indexing operations, type mismatches in declarations, and construction failures, respectively.
* `wrong_input`: Exception for invalid input data or parameters.

### Helper Functions

The exception factory namespace provides helper functions to create exceptions with predefined messages and context information. These functions include:

* `out_of_range(size_t index, size_t size)`: Creates an `OutOfRange` exception with index and size information.
* `invalid_index(int index)`: Creates a `wrong_indexing` exception for the specified index value.
* `type_mismatch()`: Creates a `wrong_declaration` exception for type mismatches in declarations.
* `construction_failed()`: Creates a `wrong_construction` exception for construction failures.
* `invalid_input(const std::string& input)`: Creates a `wrong_input` exception with the specified invalid input value.

### Usage Example

Here's an example of how to use these exceptions:

```cpp
#include <iostream>
#include "lite/exception.hpp"

int main() {
    try {
        // Code that might throw an exception...
        int index = 5;
        size_t size = 10;

        OutOfRange out_range(index, size);
        if (out_range.what() != "Index 5 out of range [0, 9]") {
            std::cout << "Invalid index: " << out_range.get_index() << std::endl;
            return 1; // Return an error code
        }

        int invalid_index = -1;
        wrong_indexing wrong_inc(invalid_index);
    } catch (const OutRange& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
```

In this example, we attempt to access an out-of-range index and create an `OutOfRange` exception. If the invalid index is detected, we print an error message to stderr instead of re-throwing the exception.
