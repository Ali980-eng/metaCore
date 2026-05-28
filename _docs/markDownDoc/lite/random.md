# Random Number Generation and Character Encryption Library

This is a C++ library that provides functions for generating random numbers, characters, and vectors as well as performing simple shift encryption on strings. The library uses the Mersenne Twister algorithm for random number generation.

## Overview of Functions

### Random Number Generation

* `GRN(int start, int end)`: Generates a random integer within the specified range using Mersenne Twister algorithm.
* `GRC()`: Generates a random printable ASCII character.

### Character Encryption and Shifts

* `SES(const std::string &input, int start, int end, std::vector<int> &shift_key_container)`: Encrypts a string by shifting all characters by the same randomly generated key.
* `SEC(const std::string &input, int start, int end, std::vector<int> &shift_key_container)`: Encrypts a string by shifting each character by a different randomly generated key.

### Vector Generation and Shifting

* `GRV(size_t ele_num, int start, int end)`: Generates a vector of random integers within the specified range.
* `GRV(size_t vec_num, size_t ele_num, int start, int end)`: Generates a 2D vector of random integers within the specified range.
* `GRV(size_t vv_num, size_t vec_num, size_t ele_num, int start, int end)`: Generates a 3D vector of random integers within the specified range.

### Vector Casting and Conversion

* `GRCV()`: Generates a vector of random printable ASCII characters.
* `GRC2DV()`: Generates a 2D vector of random printable ASCII characters.
* `GRC3DV()`: Generates a 3D vector of random printable ASCII characters.

### Usage Example

```cpp
#include "random.hpp"

int main() {
    // Generate a random integer between 1 and 100
    int number = GRN(1, 100);
    
    // Encrypt the string using shift key container
    std::string encrypted_string = SES("Hello, World!", 1, 100, {13});
    
    // Print the generated random number and encrypted string
    std::cout << "Random Number: " << number << std::endl;
    std::cout << "Encrypted String: " << encrypted_string << std::endl;

    return 0;
}
```

This example generates a random integer between 1 and 100 using the `GRN` function, then encrypts the string `"Hello, World!"` using the shift key container returned by the `SES` function. Finally, it prints both the generated random number and encrypted string to the console.
