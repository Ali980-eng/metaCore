# MetaCore Type Definition Library

-----------------------

This library provides functions for getting type names as strings and checking types. It is part of the MetaCore Lite project, which aims to improve C++ programming by providing a more powerful and flexible toolset.

## Functions

-----------------------

### `type()` Function

* Returns the name of the specified type as a string.
* Default implementation returns "***" for any type that is not specialized.
* Template parameters can be any of the standard library types, such as `bool`, `char`, `short`, etc.

```cpp
/**
 * @brief Get the type name as a string.
 *
 * @tparam T The type to get the name of.
 * @return The name of the type as a string.
 */
template <typename T>
constexpr std::string type() noexcept { return "unkown"; }
```

### `is_*()` Functions

* Check if a specified type matches a specific type.
* Default implementations return false for any type that is not specialized.

```cpp
/**
 * @brief Specializations for common types.
 *
 * @return The name of the type as a string.
 */
template <>
std::string type<bool>() noexcept { return "bool"; }

template <>
std::string type<char>() noexcept { return "char"; }
```

### `boolean_msg()` Function

* Converts a boolean value to its string representation.
* Default implementation returns the string "**true**" if the input is true, and "**false**" otherwise.

```cpp
/**
 * @brief Converts a boolean value to its string representation.
 *
 * @param value The boolean value to convert.
 * @return The string representation of the boolean value.
 */
std::string boolean_msg(bool value) noexcept { return value ? "true" : "false"; }
```

### `is_*()` Template Parameters

* Checks if a specified type matches a specific type using default implementations.

```cpp
/**
 * @brief Specialization for bool type.
 *
 * @return true since T is bool.
 */
template <>
bool is_bool(bool) noexcept { return true; }

/**
 * @brief Specialization for char type.
 *
 * @return true since T is char.
 */
template <>
bool is_char(char) noexcept { return true; }
```

### `is_*()` Template Parameters

* Checks if a specified type matches a specific type using default implementations.

```cpp
/**
 * @brief Specialization for std::string type.
 *
 * @param input The string to check.
 * @return true since T is std::string.
 */
template <>
bool is_string(const std::string& input) noexcept { return true; }

/**
 * @brief Specialization for numeric types.
 *
 * @param input The number to check.
 * @return true since T is a numeric type.
 */
template <>
bool is_numeric(const int& input) noexcept { return true; }
```

## Example Use Cases

-----------------------

```cpp
int main() {
    std::cout << "Type of x: " << type<int>() << std::endl;
    
    // Check if bool returns false
    bool b = !true;
    std::cout << "bool(b) is " << boolean_msg(b) << std::endl;
    
    int num = 10;
    std::cout << "Is string(num): " << (is_string(num)) << std::endl;
    
    return 0;
}
```

This code demonstrates how to use the `type()` function, check if a value is of a specific type using the `is_*()` functions, and convert a boolean value to its string representation using the `boolean_msg()` function.
