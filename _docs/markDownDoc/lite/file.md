# File Manager Class in C++

## Overview

This is a simple text file manager class for creating, reading, appending, checking existence, and removing text files in a specified directory. The class uses the `std::filesystem` library to interact with the operating system.

### Functions

#### Constructors

* `file()`: Constructs a `txtfile_manager` object, creating the specified directory if it does not exist.
* `file(const std::string &dirPath)`: Constructs a `txtfile_manager` object for managing text files in the specified directory. If the new directory does not exist, it will be created.

#### Directory Operations

* `change_directory(const std::string &dirPath)`: Changes the directory where text files are managed.
* `make_directory(const std::string &dirPath)`: Creates a new directory at the specified path if it does not already exist.
* `exists(const std::string &filename)`: Checks if a text file with the specified name exists in the managed directory.

#### File Operations

* `create(const std::string &filename)`: Creates a new text file with the specified name in the managed directory.
* `append(const std::string &filename, const std::string &content)`: Appends content to an existing text file.
* `read(const std::string &filename)`: Reads the contents of a text file and returns it as a string.
* `remove(const std::string &filename)`: Removes a text file from the managed directory.

#### Utility Functions

* `set(const std::string &fileName)`: Initializes a file with an include statement for "SDT.h" at the beginning.
* `save(const std::string &fileName, const std::string &varName, char data)`: Saves a character value to a file.
* `save(const std::string &fileName, const std::string &varName, short data)`: Saves a short value to a file.
* `save(const std::string &fileName, const std::string &varName, int data)`: Saves an integer value to a file.
* `save(const std::string &fileName, const std::string &varName, float data)`: Saves a float value to a file.
* `save(const std::string &fileName, const std::string &varName, double data)`: Saves a double value to a file.

### Usage Example

```cpp
#include <iostream>
#include "lite/file.hpp"

int main() {
    // Create a txtfile_manager object for managing text files in the current directory.
    lite::file manager;

    // Set the directory where text files are managed.
    std::string dirPath = "/path/to/directory";

    // Initialize the file with an include statement.
    manager.set(dirPath);

    // Append content to a new text file.
    manager.append("example.txt", "This is an example.");

    // Read the contents of a text file and print it.
    std::string content = manager.read("example.txt");
    std::cout << content << std::endl;

    return 0;
}
```

Note: This code assumes that the `file.hpp` header file includes the necessary libraries and defines the namespace for CDataGenerator.
