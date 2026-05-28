# Warning Messages in MetaCore Library

-----------------------

## Overview

The MetaCore library provides a header file `warning.hpp` that defines functions for displaying various warning messages related to indexing, deprecated features, bad input, and undefined behavior. These functions are designed to provide informative messages to developers when certain conditions are met, such as using deprecated features or encountering bad input.

### Functions

#### Warning Constructors

* `wrong_indexing()`: Constructs a warning with the name 'Wrong Indexing' and no description.
* `wrong_declaration()`: Constructs a warning with the name 'Wrong Declaration' and no description.
* `wrong_construction()`: Constructs a warning with the name 'Wrong Construction' and no description.
* `bad_input()`: Constructs a warning with the name 'Bad Input'.
* `undefined_behavior()`: Constructs a warning with the name 'Undefined Behavior'.
* `invalid_argument()`: Constructs a warning with the name 'Invalid Argument'.
* `OutOfRange()`: Constructs a warning with the name 'Out Of Range'.
* `internal_problem()`: Constructs a warning with the name 'Internal Problem'.

#### Warning Methods

* `get()` : Returns the string representation of the warning.
* `get_name()` : Returns the name of the warning.
* `get_time()` : Returns the time associated with the warning.
* `get_des()`: Returns the description of the warning.
* `replace(name, description)`: Replaces the name and description of the warning.
* `clear()`: Clears the name, description, and time of the warning.

#### Warning Factory Functions

* `wrong_indexing(const std::string& name)`: Constructs a warning with the specified name and no description.
* `wrong_declaration(const std::string& name)`: Constructs a warning with the specified name and no description.
* `wrong_construction(const std::string& name)`: Constructs a warning with the specified name and no description.
* `bad_input()`: Constructs a warning with the specified name and no description.
* `undefined_behavior()`: Constructs a warning with the specified name and no description.
* `invalid_argument()`: Constructs a warning with the specified name and no description.
* `OutOfRange()`: Constructs a warning with the specified name and no description.
* `internal_problem()`: Constructs a warning with the specified name and no description.

#### Warning Formatting Functions

* `printingFormat()`: Generates a formatted string representation of the warning.
* `operator<<(std::ostream&, const warning&)`: Outputs the warning information to an output stream.

### Usage Example

```cpp
#include "warning.hpp"

// Create a 'Wrong Indexing' warning with no description
warning wrong_indexing;

// Output the warning message and its associated timestamp
std::cout << wrong_indexing.get() << "\nTime: 100 ms.\n";
```

Note that this is just an example usage, and you can customize the formatting and behavior of the warnings to suit your specific needs.
