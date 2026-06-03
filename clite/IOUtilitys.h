/**
 * @file IOUtilitys.h
 * @brief Utility functions for input/output operations and testing.
 * @details This module provides a collection of helper functions for printing formatted output,
 * creating separators, and displaying test results for various data types.  These functions are
 * designed to facilitate consistent and readable output in test cases and demonstrations.  Users can
 * call these functions to print newlines, tabs, separators, and structured test results for char, short,
 * int, float, double, C-style strings, and cstring objects.  The separator functions allow for
 * customizable visual dividers in the output, and the print_test functions standardize the display of
 * actual vs expected values in tests.
 * @author Ali Lafi
 * @date 2025 / 9 / 25
 */

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#ifndef METACORE___CLITE___IOUTILITYS_H
#define METACORE___CLITE___IOUTILITYS_H

/// @brief Prints a newline character.
static inline void PNL() { printf("\n"); }

/// @brief Prints a specified number of tab characters.
static inline void PTab() { printf("\t"); }

/**
 * @brief Returns a message indicating the result of a test.
 * @param result A boolean value representing the outcome of a test (true for success, false for failure).
 * @return A C-style string message indicating whether the test succeeded or failed.
 * @details This function takes a boolean input and returns a corresponding message. If the input is true, it returns "succeed"; if false, it returns "failed".
 * This function is useful for standardizing the output of test results in a consistent format across different test cases.
 * Example usage:
 * bool test_result = (actual_value == expected_value);
 * printf("The test result: %s\n", test_msg(test_result)); // This will print "The test result: succeed" if the test passed, or "The test result: failed" if it did not.
 * This function can be used in conjunction with the print_test functions to provide a clear indication of whether a test case has passed or failed, enhancing the readability and clarity of test outputs.
 */
const char *test_msg(bool result)
{
    if (result)
        return "succeed";
    return "failed";
}

/**
 * @brief Prints a specified number of newline characters.
 * @param num The number of newline characters to be printed. If the number exceeds the maximum value for an unsigned integer, an exception is thrown.
 * @details This function iterates a specified number of times and prints a newline character ('\n') during each iteration.
 * It includes a check to ensure that the number of newlines requested does not exceed the maximum value for an unsigned integer, throwing an exception if it does.
 * This allows for safe usage of the function without risking overflow or excessive output.
 * Example usage:
 * NewLines(5); // This will print 5 newline characters.
 * NewLines(0); // This will not print any newlines.
 * NewLines(100); // This will print 100 newline characters.
 * If an excessively large number is provided, such as NewLines(UINT_MAX), the function will throw an exception to prevent potential issues with output formatting.
 * This function is useful for creating spacing in output, especially when formatting structured data or creating visually organized displays in console applications.
 */
static inline void NewLines(unsigned int num)
{
    for (unsigned int i = 0; i < num; i++)
        printf("\n");
}

/**
 * @brief Prints a specified number of tab characters.
 * @param num The number of tab characters to be printed. If the number exceeds the maximum value for an unsigned integer, an exception is thrown.
 * @details This function iterates a specified number of times and prints a tab character ('\t') during each iteration.  It includes a check to ensure that the number of tabs requested does not exceed the maximum value for an unsigned integer, throwing an exception if it does.  This allows for safe usage of the function without risking overflow or excessive output.
 * Example usage:
 * Tabs(5); // This will print 5 tab characters.
 * Tabs(0); // This will not print any tabs.
 * Tabs(100); // This will print 100 tab characters.
 * If an excessively large number is provided, such as Tabs(UINT_MAX), the function will throw an exception to prevent potential issues with output formatting.
 * This function is useful for creating indents in output, especially when formatting structured data or creating visually organized displays in console applications.
 */
static inline void Tabs(unsigned int num)
{
    for (unsigned int i = 0; i < num; i++)
        printf("\t");
}

/**
 * @brief Prints characters from a string starting from a specified index.
 * @param str The input string from which characters will be printed.
 * @param index The starting index from which characters will be printed. If the index is out of bounds, it defaults to 0.
 * @details This function iterates through the characters of the input string starting from the specified index and prints each character followed by a space.
 * If the provided index is negative or exceeds the length of the string, the function defaults to starting from index 0, ensuring that it always prints characters from a valid position in the string.
 * After printing the characters, it outputs a newline for better formatting.
 * Example usage:
 * print_char_str("Hello, World!", 7); // This will print "W o r l d !"
 * print_char_str("Test String", -5); // This will print "T e s t   S t r i n g" (starting from index 0)
 * print_char_str("Another Test", 20); // This will print "A n o t h e r   T e s t" (starting from index 0)
 * This function is useful for displaying specific parts of a string or for debugging purposes when you want to see the characters from a certain point onward.
 */
static inline void print_char_str(const char* str, unsigned int index)
{
    if (index >= strlen(str))
        index = 0;
    for (size_t i = index; i < strlen(str); i++)
        printf("%c ", str[i]);
    printf("\n");
}

/**
 * @brief Prints a separator line of a specified length and character.
 * @param length The length of the separator line to be printed.
 * @param ch The character to be used for the separator line. Valid characters are '~', '-', '#', '*', and '='.
 * @details This function prints a separator line consisting of the specified character repeated for the given length.
 * The function validates the separator character and throws an exception if an invalid character is provided.  This allows for consistent formatting of output with customizable visual dividers.
 * The separator can be used to visually separate different sections of output, making it easier to read and understand the structure of the displayed information.
 * Example usage:
 * separator(30, '-'); // This will print a line of 30 dashes.
 * separator(20, '*'); // This will print a line of 20 asterisks.
 * separator(25, '='); // This will print a line of 25 equal signs.
 * If an invalid character is provided, such as separator(15, '@'), the function will
 */
static inline void separator(unsigned int length, char ch)
{
    if (ch == '~' || ch == '-' || ch == '#' || ch == '*' || ch == '=')
    {
        for (unsigned int i = 0; i < length; i++)
            printf("%c", ch);
        printf("\n");
    }
    else
        printf("Invalid separator character.");
}

/**
 * @brief Prints multiple separators in a row.
 * @param numsep The number of separators to be printed.
 * @param length The length of each separator to be printed.
 * @param ch The character to be used for the separators. Valid characters are '~', '-', '#', '*', and '='.
 * @details This function prints the specified number of separators in a row, each with the given length and character.
 * The function validates the separator character and throws an exception if an invalid character is provided.  This allows for consistent formatting of output with customizable visual dividers.
 */
static inline void separators(unsigned int numsep, unsigned int length, char ch)
{
    for (unsigned int i = 0; i < numsep; i++)
        separator(length, ch);
}

/**
 * @brief Prints a category header with separators.
 * @param category The category string to be printed.
 * @details This function prints a formatted category header with separators for better readability.
 */
static inline void print_category(const char *category)
{
    separator(2 * strlen(category), '-');
    Tabs(strlen(category) / 10);
    printf("%s\n", category);
    separator(2 * strlen(category), '-');
}

/**
 * @brief Prints a category header with separators and customizable formatting.
 * @param category_s The category string to be printed.
 * @param tabs_num The number of tabs to be printed before the category string for indentation.
 * @param seplen The length of the separators to be printed before and after the category string.
 * @param sepch The character to be used for the separators.
 * @details This function prints a formatted category header with customizable separators and indentation for better readability.
 * The user can specify the number of tabs for indentation, the length of the separators, and the character to be used for the separators, allowing for flexible formatting of the category header in the output.
 */
static inline void printCategory(const char *category_s, unsigned int tabs_num, unsigned int seplen, char sepch)
{
    separator(seplen, sepch);
    Tabs(tabs_num);
    printf("%s\n", category_s);
    separator(seplen, sepch);
}

/**
 * @brief Prints the test result for boolean values.
 * @param real The actual boolean value obtained from the test.
 * @param expected The expected boolean value that the test is comparing against.
 * @param seplen The length of the separator to be printed before and after the test results.
 * @param sepch The character to be used for the separator.
 * @details This function compares the real and expected boolean values, prints whether the test succeeded or failed,
 * and then displays the real and expected values along with separators for better readability.  The test result is
 * determined by a simple equality check between the real and expected values, and the output is formatted to clearly
 * indicate the results of the test.
 */
static inline void print_test_bool(bool real, bool expected, unsigned int seplen, char sepch)
{
    printf("The test result: %s\n", test_msg(real == expected));
    separator(seplen, sepch);
    printf("The real value is: %d\n", (int)real);
    printf("The expected value is: %d\n", (int)expected);
    separator(seplen, sepch);
}

/**
 * @brief Prints the test result for character values.
 * @param real The actual character value obtained from the test.
 * @param expected The expected character value that the test is comparing against.
 * @param seplen The length of the separator to be printed before and after the test results.
 * @param sepch The character to be used for the separator.
 * @details This function compares the real and expected character values, prints whether the test succeeded or failed,
 * and then displays the real and expected values along with separators for better readability.  The test result is
 * determined by a simple equality check between the real and expected values, and the output is formatted to clearly
 * indicate the results of the test.
 */
static inline void print_test_char(char real, char expected, unsigned int seplen, char sepch)
{
    printf("The test result: %s\n", test_msg(real == expected));
    separator(seplen, sepch);
    printf("The real value is: %c\n", real);
    printf("The expected value is: %c\n", expected);
    separator(seplen, sepch);
}

/**
 * @brief Prints the test result for short integer values.
 * @param real The actual short integer value obtained from the test.
 * @param expected The expected short integer value that the test is comparing against.
 * @param seplen The length of the separator to be printed before and after the test results.
 * @param sepch The character to be used for the separator.
 * @details This function compares the real and expected short integer values, prints whether the test succeeded or failed,
 * and then displays the real and expected values along with separators for better readability.  The test result is
 * determined by a simple equality check between the real and expected values, and the output is formatted to clearly
 * indicate the results of the test.
 */
static inline void print_test_short(short real, short expected, unsigned int seplen, char sepch)
{
    printf("The test result: %s\n", test_msg(real == expected));
    separator(seplen, sepch);
    printf("The real value is: %d\n", real);
    printf("The expected value is: %d\n", expected);
    separator(seplen, sepch);
}

/**
 * @brief Prints the test result for integer values.
 * @param real The actual integer value obtained from the test.
 * @param expected The expected integer value that the test is comparing against.
 * @param seplen The length of the separator to be printed before and after the test results.
 * @param sepch The character to be used for the separator.
 * @details This function compares the real and expected integer values, prints whether the test succeeded or failed,
 * and then displays the real and expected values along with separators for better readability.  The test result is
 * determined by a simple equality check between the real and expected values, and the output is formatted to clearly
 * indicate the results of the test.
 */
static inline void print_test_int(int real, int expected, unsigned int seplen, char sepch)
{
    printf("The test result: %s\n", test_msg(real == expected));
    separator(seplen, sepch);
    printf("The real value is: %d\n", real);
    printf("The expected value is: %d\n", expected);
    separator(seplen, sepch);
}

/**
 * @brief Prints the test result for long integer values.
 * @param real The actual long integer value obtained from the test.
 * @param expected The expected long integer value that the test is comparing against.
 * @param seplen The length of the separator to be printed before and after the test results.
 * @param sepch The character to be used for the separator.
 * @details This function compares the real and expected integer values, prints whether the test succeeded or failed,
 * and then displays the real and expected values along with separators for better readability.  The test result is
 * determined by a simple equality check between the real and expected values, and the output is formatted to clearly
 * indicate the results of the test.
 */
static inline void print_test_long(long real, long expected, unsigned int seplen, char sepch)
{
    printf("The test result: %s\n", test_msg(real == expected));
    separator(seplen, sepch);
    printf("The real value is: %d\n", real);
    printf("The expected value is: %d\n", expected);
    separator(seplen, sepch);
}

/**
 * @brief Prints the test result for size_t values.
 * @param real The actual size_t value obtained from the test.
 * @param expected The expected size_t value that the test is comparing against.
 * @param seplen The length of the separator to be printed before and after the test results.
 * @param sepch The character to be used for the separator.
 * @details This function compares the real and expected size_t values, prints whether the test succeeded or failed,
 * and then displays the real and expected values along with separators for better readability.  The test result is
 * determined by a simple equality check between the real and expected values, and the output is formatted to clearly
 * indicate the results of the test.
 */
static inline void print_test_size(size_t real, size_t expected, unsigned int seplen, char sepch)
{
    printf("The test result: %s\n", test_msg(real == expected));
    separator(seplen, sepch);
    printf("The real value is: %zu\n", real);
    printf("The expected value is: %zu\n", expected);
    separator(seplen, sepch);
}

/**
 * @brief Prints the test result for float values.
 * @param real The actual float value obtained from the test.
 * @param expected The expected float value that the test is comparing against.
 * @param seplen The length of the separator to be printed before and after the test results.
 * @param sepch The character to be used for the separator.
 * @param resolution The acceptable percentage difference between the real and expected values for the test to be considered successful.
 * @details This function calculates the percentage difference between the real and expected float values and determines if the test succeeded based on whether this difference is within the specified resolution.
 * It then prints the test result, the real value, and the expected value, with separators for better readability.
 * If the provided resolution is unreasonably high (greater than or equal to 5.
 */
static inline void print_test_float(float real, float expected, unsigned int seplen,
                char sepch, float resolution)
{
    if (resolution >= 5.0f)
    {
        printf("Warning[bad input]: high-resolution input.\n");
        resolution = 0.01f;
    }
    printf("The test result: %s\n",
           test_msg(100 * (fabs(expected - real) / fabs(expected)) <= resolution));
    separator(seplen, sepch);
    printf("The real value is: %f\n", real);
    printf("The expected value is: %f\n", expected);
    separator(seplen, sepch);
}

/**
 * @brief Prints the test result for double values.
 * @param real The actual double value obtained from the test.
 * @param expected The expected double value that the test is comparing against.
 * @param seplen The length of the separator to be printed before and after the test results.
 * @param sepch The character to be used for the separator.
 * @param resolution The acceptable percentage difference between the real and expected values for the test to be considered successful.
 * @details This function calculates the percentage difference between the real and expected double values and determines if the test succeeded based on whether this difference is within the specified resolution.
 * It then prints the test result, the real value, and the expected value, with separators for better readability.
 * If the provided resolution is unreasonably high (greater than or equal to 5.0), a warning is printed and the resolution is reset to 0.01 to ensure meaningful test results.
 */
static inline void print_test_double(double real, double expected, unsigned int seplen,
                char sepch, double resolution)
{
    if (resolution >= 5.0)
    {
        printf("Warning[bad input]: high-resolution input.\n");
        resolution = 0.01;
    }
    printf("The test result: %s\n",
           test_msg(100 * (fabs(expected - real) / fabs(expected)) <= resolution));
    separator(seplen, sepch);
    printf("The real value is: %lf\n", real);
    printf("The expected value is: %lf\n", expected);
    separator(seplen, sepch);
}

/**
 * @brief Prints the test result for C-style strings.
 * @param real The actual C-style string value.
 * @param expected The expected C-style string value.
 * @param seplen The length of the separator to be printed before and after the test results.
 * @param sepch The character to be used for the separator.
 * @param result The boolean result of the test (true if the test passed, false otherwise).
 * @details This function compares the actual and expected C-style strings, prints whether the test succeeded or failed,
 * and then displays the real and expected values along with separators for better readability.
 * The test result is determined by comparing the two strings using strcmp, and the output is formatted to clearly indicate the results of the test.
 */
static inline void print_test_string(const char *real, const char *expected,
                unsigned int seplen, char sepch, bool result)
{
    printf("The test result: %s\n", test_msg(result));
    separator(seplen, sepch);
    printf("The real value is: %s\n", real);
    printf("The expected value is: %s\n", expected);
    separator(seplen, sepch);
}

#define print_test(real, expected, seplen, sepch) _Generic((real), \
    bool: print_test_bool(real, expected, seplen, sepch),          \
    char: print_test_char(real, expected, seplen, sepch),          \
    short: print_test_short(real, expected, seplen, sepch),        \
    int: print_test_int(real, expected, seplen, sepch),            \
    long: print_test_long(real, expected, seplen, sepch),          \
    size_t: print_test_size(real, expected, seplen, sepch),        \
    float: print_test_float(real, expected, seplen, sepch),        \
    double: print_test_double(real, expected, seplen, sepch),      \
    const char*: print_test_string(real, expected, seplen, sepch))

#ifdef OPENUDT___CUDT_CSTRING_CSTRINGTYPE_H
static inline void print_test_cstring(cstring real, cstring expected, unsigned int seplen, char sepch)
{
    printf("The test result:\n");
    separator(seplen, sepch);
    printf("The real value is: %s\n", real.data);
    printf("The expected value is: %s\n", expected.data);
    separator(seplen, sepch);
}
#endif // OPENUDT___CUDT_CSTRING_CSTRINGTYPE_H

#endif // METACORE___CLITE___IOUTILITYS_H