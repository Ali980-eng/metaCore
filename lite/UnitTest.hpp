/**
 * @file UnitTest.hpp
 * @brief Lightweight C++ Unit Testing Framework
 * @author Ali Lafi
 * @date 2025 / 9 / 25
 * 
 * @overview
 * A comprehensive and easy-to-use unit testing framework for C++23 projects.
 * This header provides a complete set of testing utilities for validating functions,
 * vectors (1D, 2D, 3D), and basic data type comparisons. The framework is designed
 * for simplicity and efficiency, with minimal overhead and clear reporting.
 * 
 * @main_components
 * 
 * 1. TEST Class
 *    - Represents a single test case with name, description, and result
 *    - Supports copy construction and assignment operators
 *    - Provides logical operators (==, !=, ||, &&, ^, |=, &=, ^=)
 *    - Methods: set(), get(), operator[]()
 * 
 * 2. test Namespace
 *    - count struct: Tracks test counts for different categories (function, vector, basic)
 *    - index: Global counter instance
 * 
 * @functions_overview
 * 
 * Basic Testing:
 *   - basic<T>()                : Compare single values (with/without metadata)
 * 
 * Vector Testing:
 *   - vector<T>()               : Compare 1D vectors
 *   - vector_2d<T>()            : Compare 2D vectors
 *   - vector_3d<T>()            : Compare 3D vectors
 * 
 * Function Testing:
 *   - function<T>()             : Test parameterless functions
 *   - function<T>(T, T)         : Test single-parameter functions
 *   - function<T1, T2>()        : Test functions with type conversion
 *   - function<T1, T2, T3>()    : Test two-parameter functions
 * 
 * Utility Functions:
 *   - test_message()            : Convert test result to "Success" or "Failed"
 *   - reset_count()             : Reset basic test counter
 *   - reset_vector_count()      : Reset vector test counter
 *   - reset_function_count()    : Reset function test counter
 *   - reset_all_counts()        : Reset all counters
 * 
 * @features
 * - Template-based for type flexibility
 * - No-throw guarantee (noexcept)
 * - Support for parameterized tests with names and descriptions
 * - Automatic test counting and categorization
 * - Works with STL containers (std::vector)
 * - Compile-time evaluation support (constexpr)
 * 
 * @usage_example
 * TEST result = lite::test::basic<int>(42, 42, "Integer Test", "Testing if 42 equals 42");
 * std::cout << result.get(true) << ": " << lite::test::test_message(result.get());
 * 
 * @note Requires C++23 or later for full compatibility.
 */

#include <string>
#include <memory>

#pragma once
#ifndef METACORE___LITE_UNITTEST_HPP
#define METACORE___LITE_UNITTEST_HPP

namespace lite
{
    /**
     * @class TEST
     * @brief Represents a single test case with metadata and result tracking.
     * 
     * The TEST class encapsulates a test case with optional name, description,
     * and boolean result. It provides comprehensive operators for logical operations.
     */
    class TEST
    {
    private:
        std::string name;
        std::string description;
        bool result;
    public:
        /**
         * @brief Default constructor initializing a test with default values.
         */
        TEST() : name("default"), description("no description"), result(false) {};

        /**
         * @brief Constructor with test result only.
         * @param value The boolean result of the test
         */
        TEST(bool value) noexcept {
            name = "default";
            description = "no description";
            result = value;
        }
        
        /**
         * @brief Constructor with test name only.
         * @param name The name/identifier of the test
         */
        TEST(const std::string& name) noexcept { 
            this->name = name;
            description = "no description";
            result = false;
        }
        
        /**
         * @brief Constructor with test name and description.
         * @param name The name/identifier of the test
         * @param description The detailed description of the test
         */
        TEST(const std::string& name, const std::string& description) noexcept {
            this->name = name;
            this->description = description;
            result = false;
        }
        
        /**
         * @brief Full constructor with all test properties.
         * @param name The name/identifier of the test
         * @param description The detailed description of the test
         * @param result The boolean result of the test
         */
        TEST(const std::string& name, const std::string& description, bool result) noexcept {
            this->name = name;
            this->description = description;
            this->result = result;
        }

        /**
         * @brief Copy constructor.
         * @param other The TEST object to copy from
         */
        TEST(const TEST& other) {
            name = other.name;
            description = other.description;
            result = other.result;
        }

        /**
         * @brief Destructor.
         */
        ~TEST() noexcept = default;

        /**
         * @brief Set the test name.
         * @param name The new test name
         */
        constexpr void set(const std::string& name) noexcept {
            this->name = name;
        }

        /**
         * @brief Set the test result.
         * @param result The new test result (true = pass, false = fail)
         */
        constexpr void set(bool result) noexcept {
            this->result = result;
        }

        /**
         * @brief Get the test name or description.
         * @param isName If true, returns the name; if false, returns the description
         * @return The requested string property
         */
        constexpr std::string get(bool isName) noexcept {
            return isName ? name : description;
        }

        /**
         * @brief Get the test result.
         * @return The test result (true = pass, false = fail)
         */
        constexpr bool get() noexcept {
            return result;
        }

        /**
         * @brief Assignment operator for boolean value.
         * @param result The new result value
         */
        constexpr void operator=(bool result) noexcept {
            this->result = result;
        }

        /**
         * @brief Equality comparison operator with boolean.
         * @param value The value to compare with
         * @return True if result equals value
         */
        constexpr bool operator==(bool value) noexcept {
            return result == value;
        }

        /**
         * @brief Inequality comparison operator with boolean.
         * @param value The value to compare with
         * @return True if result does not equal value
         */
        constexpr bool operator!=(bool value) noexcept {
            return result != value;
        }

        /**
         * @brief Logical OR operator with boolean.
         * @param value The value to OR with
         * @return Logical OR of result and value
         */
        constexpr bool operator||(bool value) noexcept {
            return result || value;
        }

        /**
         * @brief Logical AND operator with boolean.
         * @param value The value to AND with
         * @return Logical AND of result and value
         */
        constexpr bool operator&&(bool value) noexcept {
            return result && value;
        }

        /**
         * @brief Bitwise XOR operator with boolean.
         * @param value The value to XOR with
         * @return Bitwise XOR of result and value
         */
        constexpr bool operator^(bool value) noexcept {
            return result ^ value;
        }

        /**
         * @brief Bitwise OR assignment operator with boolean.
         * @param value The value to OR assign with
         */
        constexpr void operator|=(bool value) noexcept {
            result |= value;
        }

        /**
         * @brief Bitwise AND assignment operator with boolean.
         * @param value The value to AND assign with
         */
        constexpr void operator&=(bool value) noexcept {
            result &= value;
        }

        /**
         * @brief Bitwise XOR assignment operator with boolean.
         * @param value The value to XOR assign with
         */
        constexpr void operator^=(bool value) noexcept {
            result ^= value;
        }

        /**
         * @brief Copy assignment operator with another TEST object.
         * @param other The TEST object to copy from
         */
        constexpr void operator=(const TEST& other) noexcept {
            name = other.name;
            description = other.description;
            result = other.result;
        }

        /**
         * @brief Equality comparison operator with another TEST object.
         * @param value The TEST object to compare with
         * @return True if both results are equal
         */
        constexpr bool operator==(const TEST& value) noexcept {
            return result == value.result;
        }

        /**
         * @brief Inequality comparison operator with another TEST object.
         * @param value The TEST object to compare with
         * @return True if results are not equal
         */
        constexpr bool operator!=(const TEST& value) noexcept {
            return result != value.result;
        }

        /**
         * @brief Logical OR operator with another TEST object.
         * @param value The TEST object to OR with
         * @return Logical OR of both results
         */
        constexpr bool operator||(const TEST& value) noexcept {
            return result || value.result;
        }

        /**
         * @brief Logical AND operator with another TEST object.
         * @param value The TEST object to AND with
         * @return Logical AND of both results
         */
        constexpr bool operator&&(const TEST& value) noexcept {
            return result && value.result;
        }

        /**
         * @brief Bitwise XOR operator with another TEST object.
         * @param value The TEST object to XOR with
         * @return Bitwise XOR of both results
         */
        constexpr bool operator^(const TEST& value) noexcept {
            return result ^ value.result;
        }

        /**
         * @brief Bitwise OR assignment operator with another TEST object.
         * @param value The TEST object to OR assign with
         */
        constexpr void operator|=(const TEST& value) noexcept {
            result |= value.result;
        }

        /**
         * @brief Bitwise AND assignment operator with another TEST object.
         * @param value The TEST object to AND assign with
         */
        constexpr void operator&=(const TEST& value) noexcept {
            result &= value.result;
        }

        /**
         * @brief Bitwise XOR assignment operator with another TEST object.
         * @param value The TEST object to XOR assign with
         */
        constexpr void operator^=(const TEST& value) noexcept {
            result ^= value.result;
        }

        /**
         * @brief Subscript operator to retrieve result by test name.
         * @param name The test name to look up
         * @return The test result if name matches, bool() otherwise with error message
         */
        constexpr bool operator[](const std::string& name) noexcept {
            if(name == this->name) return result;
            std::cerr << "Name Error: Unknown name." << std::endl;
            return bool();
        }
    };

    namespace test
    {
        /**
         * @brief Structure to keep track of test counts for different categories.
         *
         * This structure contains counters for various test categories:
         * - function: Number of function-related tests.
         * - vector: Number of vector-related tests.
         * - basic: Number of basic tests.
         *
         * The default value for each counter is 1.
         */
        struct count
        {
            size_t function = 0;
            size_t vector = 0;
            size_t basic = 0;
        } index;

        /**
         * @brief Returns a message indicating the result of a test.
         *
         * This function returns "Success" if the test_result is true,
         * otherwise it returns "Failed".
         *
         * @param test_result The result of the test (true for success, false for failure).
         * @return const char* A string message representing the test result.
         * @note This function is noexcept and guarantees not to throw exceptions.
         */
        const std::string test_message(bool test_result) noexcept
        {
            return test_result ? 
            "Success" : "Failed";
        }

        /**
         * @brief Basic template test function comparing two values.
         * @tparam T The type of values being compared
         * @param realvalue The actual value from code execution
         * @param expvalue The expected value
         * @return True if values are equal, false otherwise
         * @note Increments the basic test counter
         */
        template <typename T>
        bool basic(T realvalue, T expvalue) noexcept
        {
            index.basic++;
            return realvalue == expvalue;
        }

        /**
         * @brief Basic template test function with metadata.
         * @tparam T The type of values being compared
         * @param realvalue The actual value from code execution
         * @param expvalue The expected value
         * @param name The test name
         * @param description The test description
         * @return TEST object containing result and metadata
         * @note Increments the basic test counter
         */
        template <typename T>
        TEST basic(
            T realvalue, T expvalue,
            const std::string& name,
            const std::string& description) noexcept
        {
            index.basic++;
            return !(name.empty()) && !(description.empty()) ?
            TEST{name, description, realvalue == expvalue} :
            TEST{realvalue == expvalue};
        }

        /**
         * @brief Test function for comparing 1D vectors.
         * @tparam T The type of elements in the vectors
         * @param real_v The actual vector from code execution
         * @param expected_v The expected vector
         * @return True if vectors are equal, false otherwise
         * @note Increments the vector test counter
         */
        template <typename T>
        bool vector(std::vector<T> real_v, std::vector<T> expected_v) noexcept
        {
            index.vector++;
            if (real_v.size() != expected_v.size()) {
                return false;
            }
            for (size_t i = 0; i < real_v.size(); i++) {
                if(real_v[i] != expected_v[i])
                    return false;
            }
            return true;
        }

        /**
         * @brief Test function for comparing 1D vectors with metadata.
         * @tparam T The type of elements in the vectors
         * @param real_v The actual vector from code execution
         * @param expected_v The expected vector
         * @param name The test name
         * @param description The test description
         * @return TEST object containing result and metadata
         * @note Increments the vector test counter
         */
        template <typename T>
        TEST vector(
            std::vector<T> real_v,
            std::vector<T> expected_v,
            const std::string& name,
            const std::string& description) noexcept
        {
            index.vector++;
            if (real_v.size() != expected_v.size()) {
                return !(name.empty()) && !(description.empty()) ? 
                TEST{name, description, false} : TEST{false};
            }
            for (size_t i = 0; i < real_v.size(); i++) {
                if(real_v[i] != expected_v[i]) {
                    return !(name.empty()) && !(description.empty()) ?
                    TEST{name, description, false} : TEST{false};
                }
            }
            return !(name.empty()) && !(description.empty()) ? 
            TEST{name, description, true} : TEST{true};
        }

        /**
         * @brief Test function for comparing 2D vectors.
         * @tparam T The type of elements in the vectors
         * @param real_2dv The actual 2D vector from code execution
         * @param expected_2dv The expected 2D vector
         * @return True if 2D vectors are equal, false otherwise
         * @note Increments the vector test counter
         */
        template <typename T>
        bool vector_2d(std::vector<std::vector<T>> real_2dv,
                       std::vector<std::vector<T>> expected_2dv) noexcept
        {
            index.vector++;
            if (real_2dv.size() != expected_2dv.size()) {
                return false;
            }
            for (size_t i = 0; i < real_2dv.size(); i++) {
                if(real_2dv[i].size() != expected_2dv[i].size()) {
                    return false;
                }
                for(size_t j = 0; j < real_2dv[i].size(); j++) {
                    if(real_2dv[i][j] != expected_2dv[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }

        /**
         * @brief Test function for comparing 2D vectors with metadata.
         * @tparam T The type of elements in the vectors
         * @param real_2dv The actual 2D vector from code execution
         * @param expected_2dv The expected 2D vector
         * @param name The test name
         * @param description The test description
         * @return TEST object containing result and metadata
         * @note Increments the vector test counter
         */
        template <typename T>
        TEST vector_2d(std::vector<std::vector<T>> real_2dv,
                       std::vector<std::vector<T>> expected_2dv,
                       const std::string& name,
                       const std::string& description) noexcept
        {
            index.vector++;
            if (real_2dv.size() != expected_2dv.size()) {
                return !(name.empty()) && !(description.empty()) ? 
                TEST{name, description, false} : TEST{false};
            }
            for (size_t i = 0; i < real_2dv.size(); i++) {
                if(real_2dv[i].size() != expected_2dv.size()) {
                    return !(name.empty()) && !(description.empty()) ? 
                    TEST{name, description, false} : TEST{false};
                }
                for(size_t j = 0; j < real_2dv[i].size(); j++) {
                    if(real_v[i] != expected_v[i]) {
                        return !(name.empty()) && !(description.empty()) ?
                        TEST{name, description, false} : TEST{false};
                    }
                }
            }
            return !(name.empty()) && !(description.empty()) ?
            TEST{name, description, false} : TEST{false};
        }

        /**
         * @brief Test function for comparing 3D vectors.
         * @tparam T The type of elements in the vectors
         * @param real_3dv The actual 3D vector from code execution
         * @param expected_3dv The expected 3D vector
         * @return True if 3D vectors are equal, false otherwise
         * @note Increments the vector test counter
         */
        template <typename T>
        bool vector_3d(const std::vector<std::vector<std::vector<T>>>& real_3dv,
                       const std::vector<std::vector<std::vector<T>>>& expected_3dv) noexcept
        {
            index.vector++;
            if (real_3dv.size() != expected_3dv.size()) {
                return false;
            }
            for (size_t i = 0; i < real_3dv.size(); i++) {
                if(real_3dv[i].size() != expected_3dv[i].size()) {
                    return false;
                }
                for(size_t j = 0; j < real_3dv[i].size(); j++) {
                    if(real_3dv[i][j].size() != expected_3dv[i][j].size()) {
                        return false;
                    }
                    for(size_t z = 0; z < real_3dv[i][j].size(); z++) {
                        if(real_3dv[i][j][z] != expected_3dv[i][j][z]) {
                            return false;
                        }
                    }
                }
            }
            return true;
        }

        /**
         * @brief Test function for comparing 3D vectors with metadata.
         * @tparam T The type of elements in the vectors
         * @param real_3dv The actual 3D vector from code execution
         * @param expected_3dv The expected 3D vector
         * @param name The test name
         * @param description The test description
         * @return TEST object containing result and metadata
         * @note Increments the vector test counter
         */
        template <typename T>
        TEST vector_3d(const std::vector<std::vector<std::vector<T>>>& real_3dv,
                       const std::vector<std::vector<std::vector<T>>>& expected_3dv,
                       const std::string& name, const std::string& description) noexcept
        {
            if (real_3dv.size() != expected_3dv.size()) {
                return !(name.empty()) && !(description.empty()) ? 
                TEST{name, description, false} : TEST{false};
            }
            for (size_t i = 0; i < real_3dv.size(); i++) {
                if(real_3dv[i].size() != expected_3dv[i].size()) {
                    return !(name.empty()) && !(description.empty()) ? 
                    TEST{name, description, false} : TEST{false};
                }
                for(size_t j = 0; j < real_3dv[i].size(); j++) {
                    if(real_3dv[i][j].size() != expected_3dv[i][j].size()) {
                        return !(name.empty()) && !(description.empty()) ? 
                        TEST{name, description, false} : TEST{false};
                    }
                    for(size_t z = 0; z < real_3dv[i][j].size(); z++) {
                        if(real_3dv[i][j][z] != expected_3dv[i][j][z]) {
                            return !(name.empty()) && !(description.empty()) ? 
                            TEST{name, description, false} : TEST{false};
                        }
                    }
                }
            }
            return !(name.empty()) && !(description.empty()) ? 
            TEST{name, description, false} : TEST{false};
        }

        /**
         * @brief Test function without parameters.
         * @tparam T The return type of the function
         * @param fx The parameterless function to test
         * @param expected The expected return value
         * @return True if function result equals expected, false otherwise
         * @note Increments the function test counter
         */
        template <typename T>
        bool function(std::function<T()> fx, T expected) noexcept
        {
            index.function++;
            return fx() == expected;
        }

        /**
         * @brief Test function without parameters with metadata.
         * @tparam T The return type of the function
         * @param fx The parameterless function to test
         * @param expected The expected return value
         * @param name The test name
         * @param description The test description
         * @return TEST object containing result and metadata
         * @note Increments the function test counter
         */
        template <typename T>
        TEST function(std::function<T()> fx, T expected,
                    const std::string& name,
                    const std::string& description) noexcept
        {
            index.function++;
            return !(name.empty()) && !(description.empty()) ? 
            TEST{name, description, fx() == expected} :
            TEST{fx() == expected};
        }

        /**
         * @brief Test function with single parameter (same type).
         * @tparam T The parameter and return type of the function
         * @param fx The function to test
         * @param value The input value
         * @param expected The expected return value
         * @return True if function result equals expected, false otherwise
         * @note Increments the function test counter
         */
        template <typename T>
        bool function(std::function<T(T)> fx, T value, T expected) noexcept
        {
            index.function++;
            return fx(value) == expected;
        }

        /**
         * @brief Test function with single parameter with metadata.
         * @tparam T The parameter and return type of the function
         * @param fx The function to test
         * @param value The input value
         * @param expected The expected return value
         * @param name The test name
         * @param description The test description
         * @return TEST object containing result and metadata
         * @note Increments the function test counter
         */
        template <typename T>
        TEST function(std::function<T(T)> fx, T value, T expected,
                    const std::string& name,
                    const std::string& description) noexcept
        {
            index.function++;
            return !(name.empty()) && !(description.empty()) ? 
            TEST{name, description, fx(value) == expected} :
            TEST{fx(value) == expected};
        }

        /**
         * @brief Test function with type conversion.
         * @tparam T1 The return type of the function
         * @tparam T2 The parameter type of the function
         * @param fx The function to test
         * @param value The input value
         * @param expected The expected return value
         * @return True if function result equals expected, false otherwise
         * @note Increments the function test counter
         */
        template <typename T1, typename T2>
        bool function(std::function<T1(T2)> fx, T2 value, T1 expected) noexcept
        {
            index.function++;
            return fx(value) == expected;
        }

        /**
         * @brief Test function with type conversion with metadata.
         * @tparam T1 The return type of the function
         * @tparam T2 The parameter type of the function
         * @param fx The function to test
         * @param value The input value
         * @param expected The expected return value
         * @param name The test name
         * @param description The test description
         * @return TEST object containing result and metadata
         * @note Increments the function test counter
         */
        template <typename T1, typename T2>
        TEST function(std::function<T1(T2)> fx, T2 value, T1 expected,
                    const std::string& name, const std::string& description) noexcept
        {
            index.function++;
            return !(name.empty()) && !(description.empty()) ? 
            TEST{name, description, fx(value) == expected} :
            TEST{fx(value) == expected};
        }

        /**
         * @brief Test function with two parameters.
         * @tparam T1 The return type of the function
         * @tparam T2 The first parameter type
         * @tparam T3 The second parameter type
         * @param fx The function to test
         * @param expected The expected return value
         * @param value1 The first input value
         * @param value2 The second input value
         * @return Result of function call
         * @note Increments the function test counter
         */
        template <typename T1, typename T2, typename T3>
        bool function(std::function<T1(T2, T3)> fx, T1 expected, T2 value1, T3 value2) noexcept
        {
            index.function++;
            return fx(value1, value2) == expected;
        }

        /**
         * @brief Test function with two parameters with metadata.
         * @tparam T1 The return type of the function
         * @tparam T2 The first parameter type
         * @tparam T3 The second parameter type
         * @param fx The function to test
         * @param expected The expected return value
         * @param value1 The first input value
         * @param value2 The second input value
         * @param name The test name
         * @param description The test description
         * @return TEST object containing result and metadata
         * @note Increments the function test counter
         */
        template <typename T1, typename T2, typename T3>
        TEST function(std::function<T1(T2, T3)> fx, T1 expected,
                    T2 value1, T3 value2, const std::string& name,
                    const std::string& description) noexcept
        {
            index.function++;
            return !(name.empty()) && !(description.empty()) ? 
            TEST{name, description, fx(value1, value2) == expected} :
            TEST{fx(value1, value2) == expected};
        }

        /**
         * @brief Resets the basic test counter to its initial value.
         * Sets index.basic = 1. This function is constexpr and noexcept.
         */
        constexpr inline void reset_count() noexcept { index.basic = 1; }

        /**
         * @brief Resets the vector test counter to its initial value.
         * Sets index.vector = 1. This function is constexpr and noexcept.
         */
        constexpr inline void reset_vector_count() noexcept { index.vector = 1; }

        /**
         * @brief Resets the function test counter to its initial value.
         * Sets index.function = 1. This function is constexpr and noexcept.
         */
        constexpr inline void reset_function_count() noexcept { index.function = 1; }

        /**
         * @brief Resets all internal test counters to their initial state.
         * Calls reset_count(), reset_vector_count(), and reset_function_count()
         * to reset all respective counters. This function is constexpr and noexcept.
         */
        constexpr inline void reset_all_counts() noexcept
        {
            reset_count();
            reset_vector_count();
            reset_function_count();
        }
    };
}
#endif // METACORE___LITE_UNITTEST_HPP