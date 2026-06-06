/**
 * @file io.hpp
 * @brief A simple I/O utility class for handling standard input and output operations.
 * @author Ali Lafi
 * @date 2025 / 9 / 25
 * @details This library provides a simple I/O utility class for handling standard input and output operations.
 * The `io` class encapsulates various functions for printing to the console, taking user input, and formatting output.
 * It includes methods for printing values with or without newlines, printing error messages, and taking user input for different types of variables and vectors.
 * Additionally, it offers functions for printing formatted test outputs and separators for better readability.
 * Overall, this library is designed to simplify common I/O tasks in C++ and enhance the user experience when interacting with the console.
 * - NewLines: Prints a specified number of newline characters.
 * - println: Prints a value followed by a newline to standard output.
 * - print: Prints a value without a newline to standard output.
 * - println_error: Prints an error message followed by a newline to standard error.
 * - print_error: Prints an error message without a newline to standard error.
 * - input: Prints a prompt message and takes user input of the same type.
 * - input (overload): Prints a prompt message and takes user input of a different type.
 * - input_vector: Prints a prompt message and takes user input for a vector of a different type.
 * - input_vector_2d: Prompts the user for input to fill a 2D vector.
 * - input_vector_3d: Prompts the user for input to fill a 3D vector.
 * - Tabs: Prints a specified number of tab characters.
 * - print_test: Prints a standardized test output with optional vector content.
 * - print (vector overload): Prints all elements in a vector with formatting.
 * - print (2D vector overload): Prints a 2D vector to the standard output in a formatted manner.
 * - print (3D vector overload): Prints a 3D vector to the standard output in a formatted manner.
 * - println (2D vector overload): Prints a 2D vector to the standard output in a formatted manner.
 * - println (3D vector overload): Prints a 3D vector to the standard output in a formatted manner.
 * @note This library is designed for C++23 and is part of the metaCore library, specifically within the CXXLite module, and is intended for simplifying I/O operations in C++.
 */

#if defined(__cpp_modules) && (__cplusplus >= 202302L)
    import std;
#else
    #include <iostream>
    #include <string>
    #include <vector>
    #include <limits>
    #include <algorithm>
    #include <functional>
    #include <type_traits>
    #include <climits>
    #include <stdexcept>
#endif

#include "cgen/micros.h"

#pragma once
#ifndef METACORE___LITE_IO_HPP
#define METACORE___LITE_IO_HPP

#ifdef METACORE___META_HPP
namespace meta {
#endif // METACORE___META_HPP
#ifdef METACORE___LITE_HPP
namespace lite {
#endif // METACORE___LITE_HPP

    namespace io
    {

        /**
         * @brief Prints a number of newline characters.
         * @param num Number of new lines to print (default = 2).
         */
        void NewLines(short num = 1)
        {
            if (SHRT_MAX <= num)
                throw std::out_of_range("num is bigger than SHRT_MAX");
            for (short i = 0; i < num; i++)
                std::cout << nl;
        }

        /**
         * @brief Prints a horizontal line using a specific character.
         * @param length The number of characters in the line.
         * @param ch The character to use (must be one of: ~, -, #, *, =).
         */
        void separator(short length, char ch = '-')
        {
            if (ch == '~' || ch == '-' || ch == '#' || ch == '*' || ch == '=')
            {
                for (int i = length; i >= 0; i--)
                    std::cout << ch;
                std::cout << nl;
            }
            else
                throw std::invalid_argument("Invalid separator character.");
        }

        /**
         * @brief Prints multiple separator lines.
         * @param numsep The number of separator lines to print.
         * @param length The number of characters in each separator line.
         * @param ch The character to use for the separator lines (must be one of: ~, -, #, *, =).
         * @details This function prints a specified number of separator lines, each consisting of a specific character repeated a certain number of times. The character used for the separator lines must be one of the following: ~, -, #, *, =. If an invalid character is provided, an exception is thrown.
         */
        void separators(short numsep, short length, char ch)
        {
            for (int i = 0; i < numsep; i++)
                separator(length, ch);
        }

        /**
         * @brief Prints a value followed by a newline to standard output.
         * @tparam T Type of the value to print.
         * @param output The value to be printed.
         */
        void println() noexcept { std::cout << nl; }
        template <typename T, typename... Args>
        inline void println(const T &output, Args... remaining_t) noexcept
        {
            std::cout << output;
            println(remaining_t...);
        }

        /**
         * @brief Prints a value without a newline to standard output.
         * @tparam T Type of the value to print.
         * @param output The value to be printed.
         */
        void print() noexcept { return; }
        template <typename T, typename... Args>
        inline void print(const T &output, Args... remaining_t) noexcept
        {
            std::cout << output;
            print(remaining_t...);
        }

        /**
         * @brief Prints an error message followed by a newline to standard error.
         * @tparam T Type of the message to print.
         * @param output The error message to be printed.
         */
        void println_error() noexcept { std::cerr << nl; }
        template <typename T, typename... Args>
        inline void println_error(const T &output, Args... remaining_t) noexcept
        {
            std::cerr << output;
            println_error(remaining_t...);
        }

        /**
         * @brief Prints an error message without a newline to standard error.
         * @tparam T Type of the message to print.
         * @param output The error message to be printed.
         */
        void print_error() noexcept { return; }
        template <typename T, typename... Args>
        inline void print_error(const T &output, Args... remaining_t) noexcept
        {
            std::cerr << output;
            print_error(remaining_t...);
        }

        /**
         * @brief Prints a prompt message and takes user input of a different type.
         * @tparam T Type of the input variable.
         * @param output The prompt message to display.
         * @return T The user input.
         */
        template <typename T>
        T input(const std::string &output)
        {
            T var;
            std::cout << output << std::endl;
            std::cin >> var;
            return var;
        }

        /**
         * @brief Prints a prompt message and takes user input for a vector of a different type.
         * @tparam T Type of the input variable.
         * @param output The prompt message to display.
         * @param size The number of elements in the vector.
         * @return std::vector<T> The user input vector.
         */
        template <typename T>
        std::vector<T> input_vector(const std::string &output, size_t size)
        {
            if (size <= 0)
                throw std::invalid_argument("Size must be greater than zero");
            std::vector<T> vec;
            T var;
            std::cout << output << std::endl;
            for (size_t i = 0; i < size; i++)
            {
                std::cin >> var;
                vec.push_back(var);
            }
            return vec;
        }

        /**
         * @brief Prompts the user for input to fill a 2D vector.
         * @tparam T The type of elements in the 2D vector.
         * @param output The prompt message to display.
         * @param rows The number of rows (must be > 0).
         * @param cols The number of columns (must be > 0).
         * @return A 2D vector filled with user input.
         * @throws std::invalid_argument if rows or cols is less than or equal to zero
         */
        template <typename T>
        std::vector<std::vector<T>> input_vector_2d(const std::string &output, size_t rows, size_t cols)
        {
            if (rows <= 0 || cols <= 0)
                throw std::invalid_argument("Rows and columns must be greater than zero");
            std::vector<std::vector<T>> vec2d;
            T var;
            std::cout << output << std::endl;
            for (size_t i = 0; i < rows; i++)
            {
                std::vector<T> row;
                for (size_t j = 0; j < cols; j++)
                {
                    std::cin >> var;
                    row.push_back(var);
                }
                vec2d.push_back(row);
            }
            return vec2d;
        }

        /**
         * @brief Prompts the user for input to fill a 3D vector.
         * @tparam T The type of elements in the 3D vector.
         * @param output The prompt message to display.
         * @param x The size of the first dimension (must be > 0).
         * @param y The size of the second dimension (must be > 0).
         * @param z The size of the third dimension (must be > 0).
         * @return A 3D vector filled with user input.
         * @throws std::invalid_argument if any dimension is less than or equal to zero.
         */
        template <typename T>
        std::vector<std::vector<std::vector<T>>> input_vector_3d(const std::string &output, size_t x, size_t y, size_t z)
        {
            if (x <= 0 || y <= 0 || z <= 0)
                throw std::invalid_argument("Dimensions must be greater than zero");
            std::vector<std::vector<std::vector<T>>> vec3d;
            T var;
            std::cout << output << std::endl;
            for (size_t i = 0; i < x; i++)
            {
                std::vector<std::vector<T>> layer;
                for (size_t j = 0; j < y; j++)
                {
                    std::vector<T> row;
                    for (size_t k = 0; k < z; k++)
                    {
                        std::cin >> var;
                        row.push_back(var);
                    }
                    layer.push_back(row);
                }
                vec3d.push_back(layer);
            }
            return vec3d;
        }

        /**
         * @brief Prints a number of tab characters.
         * @param num Number of tabs to print (default = 2).
         */
        void Tabs(short num = 1)
        {
            if (num >= SHRT_MAX)
                throw std::out_of_range("num is bigger than SHRT_MAX");
            for (short i = 0; i < num; i++)
                std::cout << tab;
        }

        /**
         * @brief Prints a standardized test output.
         * @tparam T The type of the output value.
         * @param testNum The test number.
         * @param OutPut The output value to print.
         */
        template <typename T>
        void print_test(size_t testNum, const T &OutPut)
        {
            std::cout << "Test(" << testNum << "): " 
            << OutPut << nl;
        }

        /**
         * @brief Prints a standardized test output without a specific value.
         * @param testNum The test number.
         */
        void print_test(size_t testNum) noexcept
        {
            std::cout << "Test(" 
            << testNum << "): " 
            << nl;
        }

        void print_test(const std::string& name,
            const std::string& description,
            bool result, size_t testNum,
            size_t whiteSpace = 2,
            size_t seplen = 25,
            size_t sepch = '-') noexcept {
            NewLines(whiteSpace);
            separator(seplen, sepch);
            println("<<< TEST >>>");
            separator(seplen, sepch);
            if(name.length() != 0) {
                println("NAME: ", name);
            }
            if(description.length() != 0) {
                println("DESCRIPTION: ", description);
            }
            println("NUMBER: ", testNum);
            println("RESULT: ", result ? "PASSED" : "FAILED");
            separator(seplen, sepch);
        }

        /**
         * @brief Prints all elements in a vector with formatting.
         * @tparam T The type of vector elements.
         * @param vec The vector to print.
         */
        template <typename T>
        void print(const std::vector<T> &vec)
        {
            if (vec.empty())
                throw std::invalid_argument("The vector is empty");
            if (vec.size() == 1)
            {
                std::cout << " [" << vec[0] << "] ";
                return;
            }
            for (size_t i = 0; i < vec.size(); i++)
            {
                if (i == 0)
                    std::cout << " [" << vec[i] << ", ";
                else if (i == vec.size() - 1)
                    std::cout << vec[i] << "] ";
                else
                    std::cout << vec[i] << ", ";
            }
        }

        /**
         * @brief Prints the contents of a std::vector to the standard output in a formatted manner.
         *
         * This function outputs the elements of the given vector enclosed in square brackets and separated by commas.
         * If the vector is empty, it prints "[]".
         *
         * @tparam T The type of the elements stored in the vector.
         * @param output The vector whose contents are to be printed.
         * @note The function is marked noexcept and does not throw exceptions.
         */
        template <typename T>
        inline void println(const std::vector<T> &output) noexcept
        {
            if (output.empty())
            {
                std::cout << "[]" << nl;
                return;
            }
            std::cout << "[";
            for (size_t i = 0; i < output.size(); ++i)
            {
                std::cout << output[i];
                if (i != output.size() - 1)
                    std::cout << ", ";
            }
            std::cout << "]" << nl;
        }

        /**
         * @brief Prints a 2D vector to the standard output in a formatted manner.
         *
         * This function outputs the contents of a two-dimensional std::vector to std::cout,
         * formatting it as nested lists (e.g., [[1, 2], [3, 4]]). If the input vector is empty,
         * it prints "[]".
         *
         * @tparam T The type of the elements stored in the inner vectors.
         * @param output The 2D vector to be printed.
         */
        template <typename T>
        inline void print(const std::vector<std::vector<T>> &output) noexcept
        {
            if (output.empty())
            {
                std::cout << "[]";
                return;
            }
            std::cout << "[";
            for (size_t i = 0; i < output.size(); ++i)
            {
                std::cout << "[";
                for (size_t j = 0; j < output[i].size(); ++j)
                {
                    std::cout << output[i][j];
                    if (j != output[i].size() - 1)
                        std::cout << ", ";
                }
                std::cout << "]";
                if (i != output.size() - 1)
                    std::cout << ", ";
            }
            std::cout << "]";
        }

        /**
         * @brief Prints a 2D vector to the standard output in a formatted manner.
         *
         * This function outputs the contents of a two-dimensional std::vector to std::cout,
         * formatting it as nested lists (e.g., [[1, 2], [3, 4]]). If the input vector is empty,
         * it prints "[]".
         *
         * @tparam T The type of the elements stored in the inner vectors.
         * @param output The 2D vector to be printed.
         */
        template <typename T>
        inline void println(const std::vector<std::vector<T>> &output) noexcept
        {
            if (output.empty())
            {
                std::cout << "[]" << nl;
                return;
            }
            std::cout << "[";
            for (size_t i = 0; i < output.size(); ++i)
            {
                std::cout << "[";
                for (size_t j = 0; j < output[i].size(); ++j)
                {
                    std::cout << output[i][j];
                    if (j != output[i].size() - 1)
                        std::cout << ", ";
                }
                std::cout << "]";
                if (i != output.size() - 1)
                    std::cout << ", ";
            }
            std::cout << "]" << nl;
        }

        /**
         * @brief Prints a 3D vector to the standard output in a formatted manner.
         * This function outputs the contents of a three-dimensional std::vector to std::cout,
         * formatting it as nested lists (e.g., [[[1, 2], [3, 4]], [[5, 6], [7, 8]]]). If the input vector is empty,
         * it prints "[]".
         * @param output The 3D vector to be printed.
         * @tparam T The type of the elements stored in the innermost vectors.
         * @note The function is marked noexcept and does not throw exceptions.
         * @example
         * std::vector<std::vector<std::vector<int>>> vec3d = {
         *     {{1, 2}, {3, 4}},
         *     {{5, 6}, {7, 8}}
         * };
         */
        template <typename T>
        inline void print(const std::vector<std::vector<std::vector<T>>> &output) noexcept
        {
            if (output.empty())
            {
                std::cout << "[]";
                return;
            }
            std::cout << "[";
            for (size_t i = 0; i < output.size(); ++i)
            {
                std::cout << "[";
                for (size_t j = 0; j < output[i].size(); ++j)
                {
                    std::cout << "[";
                    for (size_t k = 0; k < output[i][j].size(); ++k)
                    {
                        std::cout << output[i][j][k];
                        if (k != output[i][j].size() - 1)
                            std::cout << ", ";
                    }
                    std::cout << "]";
                    if (j != output[i].size() - 1)
                        std::cout << ", ";
                }
                std::cout << "]";
                if (i != output.size() - 1)
                    std::cout << ", ";
            }
            std::cout << "]";
        }

        /**
         * @brief Prints a 3D vector to the standard output in a formatted manner.
         * This function outputs the contents of a three-dimensional std::vector to std::cout,
         * formatting it as nested lists (e.g., [[[1, 2], [3, 4]], [[5, 6], [7, 8]]]). If the input vector is empty,\
         * it prints "[]".
         * @param output The 3D vector to be printed.
         * @tparam T The type of the elements stored in the innermost vectors.
         * @note The function is marked noexcept and does not throw exceptions.
         * @example
         * std::vector<std::vector<std::vector<int>>> vec3d = {
         *     {{1, 2}, {3, 4}},
         *     {{5, 6}, {7, 8}}
         * };
         */
        template <typename T>
        inline void println(const std::vector<std::vector<std::vector<T>>> &output) noexcept
        {
            if (output.empty())
            {
                std::cout << "[]" << nl;
                return;
            }
            std::cout << "[";
            for (size_t i = 0; i < output.size(); ++i)
            {
                std::cout << "[";
                for (size_t j = 0; j < output[i].size(); ++j)
                {
                    std::cout << "[";
                    for (size_t k = 0; k < output[i][j].size(); ++k)
                    {
                        std::cout << output[i][j][k];
                        if (k != output[i][j].size() - 1)
                            std::cout << ", ";
                    }
                    std::cout << "]";
                    if (j != output[i].size() - 1)
                        std::cout << ", ";
                }
                std::cout << "]";
                if (i != output.size() - 1)
                    std::cout << ", ";
            }
            std::cout << "]" << nl;
        }

        /**
         * @brief Combines Test() and PrintVec() to test and print vector content.
         * @tparam T The type of vector elements.
         * @param testNum Test number.
         * @param vec The vector to test and print.
         */
        template <typename T>
        void print_test(long testNum, const std::vector<T> &vec)
        {
            if (vec.empty())
                throw std::invalid_argument("The vector is empty");
            print_test(testNum);
            print<T>(vec);
        }

        /**
         * @brief Combines Test() and PrintVec() to test and print 2D vector content.
         * @tparam T The type of vector elements.
         * @param testNum Test number.
         * @param vec The 2D vector to test and print.
         * @note This function throws an exception if the input vector is empty.
         * @example
         * std::vector<std::vector<int>> vec2d = {
         *    {1, 2},
         *    {3, 4}
         * };
         */
        template <typename T>
        void print_test(long testNum, const std::vector<std::vector<T>> &vec)
        {
            if (vec.empty())
                throw std::invalid_argument("The vector is empty");
            print_test(testNum);
            print<T>(vec);
        }

        /**
         * @brief Combines Test() and PrintVec() to test and print 3D vector content.
         * @tparam T The type of vector elements.
         * @param testNum Test number.
         * @param vec The 3D vector to test and print.
         * @note This function throws an exception if the input vector is empty.
         * @example
         * std::vector<std::vector<std::vector<int>>> vec3d = {
         *    {{1, 2}, {3, 4}},
         *    {{5, 6}, {7, 8}}
         * };
         */
        template <typename T>
        void print_test(long testNum, const std::vector<std::vector<std::vector<T>>> &vec)
        {
            if (vec.empty())
                throw std::invalid_argument("The vector is empty");
            print_test(testNum);
            print<T>(vec);
        }

        /**
         * @brief Prints characters of a string individually starting from a given
         * index.
         * @param str The string to print.
         * @param index Starting index (default = 0). If out of range, starts from 0.
         */
        void print_char_str(const std::string &str, size_t index) noexcept
        {
            if (index < 0 || index >= str.length())
                index = 0;
            for (size_t i = index; i < str.length(); i++)
                std::cout << str[i] << ' ';
            std::cout << nl;
        }

        /**
         * @brief Prints a decorated category title.
         * @param category The category title to print.
         */
        void print_category(const std::string &category)
        {
            separator(2 * category.length());
            Tabs(category.length() / 10);
            std::cout << category << nl;
            separator(2 * category.length());
        }

        /**
         * @brief Prints a formatted category name with separators and indentation.
         *
         * This function outputs the given category string (`category_s`) to the
         * standard output stream, surrounded by separator lines of a specified
         * length and character. It also indents the category text by a given
         * number of tab characters before printing.
         *
         * @param category_s  The category name to be printed.
         * @param tabs_num    Number of tab characters to print before the category text.
         * @param seplen      The length of the separator line (number of repeated characters).
         * @param sepch       The character used to build the separator line.
         *
         * @note This function relies on external helper functions:
         *       - separator(int length, char ch): prints a separator line.
         *       - Tabs(int n): prints a number of tab characters.
         *
         * @example
         * // Example: print the word "Settings" with 1 tab,
         * // a separator of length 20 made of '=' characters:
         * print_category("Settings", 1, 20, '=');
         *
         * // Expected output:
         * ====================
         *     Settings
         * ====================
         */
        void print_category(const std::string &category_s, int tabs_num, int seplen, char sepch)
        {
            separator(seplen, sepch);
            Tabs(tabs_num);
            std::cout << category_s << nl;
            separator(seplen, sepch);
        }

        /**
         * @brief Prints a value followed by a newline to standard output if a given condition is true.
         * @tparam T Type of the value to print.
         * @param Fp A function that takes a value of type T and returns a boolean indicating whether to print the value.
         * @param data The value to be evaluated and potentially printed.
         * @details This function evaluates the provided value using the given function pointer (or lambda). If the function returns true for the provided data, the value is printed to standard output followed by a newline. If the function returns false, nothing is printed.
         */
        template<typename T>
        void print_if(std::function<bool(T)> Fp, const T& data) noexcept {
            if(Fp(data)) print(data);
        }

        /**
         * @brief Prints a value followed by a newline to standard output if a given condition is true.
         * @tparam T Type of the value to print.
         * @param Fp A function that takes a value of type T and returns a boolean indicating whether to print the value.
         * @param data The value to be evaluated and potentially printed.
         * @details This function evaluates the provided value using the given function pointer (or lambda). If the function returns true for the provided data, the value is printed to standard output followed by a newline. If the function returns false, nothing is printed.
         */
        template<typename T>
        void println_if(std::function<bool(T)> Fp, const T& data) noexcept {
            if(Fp(data)) println(data);
        }

        template<typename T>
        void print_if(bool result, const T& data) noexcept {
            if(result) print(data);
        }

        template<typename T>
        void println_if(bool result, const T& data) noexcept {
            if(result) print(data);
        }
    }

#ifdef METACORE___LITE_HPP
}
#endif // METACORE___LITE_HPP
#ifdef METACORE___META_HPP
}
#endif // METACORE___META_HPP

#endif // METACORE___LITE_IO_HPP