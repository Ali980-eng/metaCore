/**
 * @file UnitTest.h
 * @brief Unit testing framework for the CLite library.
 * @details This module provides a comprehensive testing framework with support for:
 *          - Multiple data types (bool, char, short, int, long, size_t, float, double, C-strings)
 *          - Detailed and simplified test output modes
 *          - String comparison with length validation
 *          - Floating-point comparison with configurable tolerance
 *          - Test statistics tracking and reporting (success/failure rates)
 *          - Customizable separator characters and formatting
 * @author Ali Lafi
 * @date 2025 / 9 / 25
 * @see IOUtilitys.h for I/O utility functions
 */

#include "IOUtilitys.h"
#include "micros.h"

#include <string.h>
#include <math.h>
#include <stdbool.h>

#ifndef METACORE___CLITE_UNITTEST_H
#define METACORE___CLITE_UNITTEST_H

size_t cttn = 0;

typedef struct {
    char* name;
    char* description;
    size_t num;
    bool result;
} CTEST;


static inline CTEST creatNew(CTEST current, char* name, char* des, bool value) {
    current.name = (name != NULL) ? name : strdup("");
    current.description = (des != NULL) ? des : strdup("");
    current.num = cttn;
    cttn++;
    current.result = value;
    return current;
}

static inline bool catchValue(CTEST current) {
    return current.result;
}

static inline void printTest(CTEST current) {
    printf("\n");
    printf("------------\n");
    printf("<<< TEST >>>\n");
    printf("------------\n");
    if(current.name != NULL && strlen(current.name) != 0) {
        printf("NAME: %s \n", current.name);
    }
    if(current.description != NULL && strlen(current.description) != 0) {
        printf("DESCRIPTION: %s \n", current.description);
    }
    printf("NUMBER: %d \n", current.num);
    printf("RESULT: %s \n", current.result ? "PASSED" : "FAILED");
    printf("------------\n");
}

/**
 * @brief Tests boolean values for equality.
 * @param real The actual boolean value obtained from the test.
 * @param expected The expected boolean value.
 * @param details Whether to print detailed test results.
 * @param seplen The length of the separator line.
 * @param sepch The character to use for the separator.
 * @return true if real equals expected, false otherwise.
 * @note When details is true, prints formatted output with separators.
 */
static inline bool basic_test_bool(bool real, bool expected, bool details, unsigned int seplen, char sepch)
{
    if (details)
        print_test_bool(real, expected, seplen, sepch);
    return real == expected;
}

/**
 * @brief Tests char values for equality.
 * @param real The actual character value obtained from the test.
 * @param expected The expected character value.
 * @param details Whether to print detailed test results.
 * @param seplen The length of the separator line.
 * @param sepch The character to use for the separator.
 * @return true if real equals expected, false otherwise.
 * @note When details is true, prints formatted output with separators.
 */
static inline bool basic_test_char(char real, char expected, bool details, unsigned int seplen, char sepch)
{
    if (details)
        print_test_char(real, expected, seplen, sepch);
    return real == expected;
}

/**
 * @brief Tests short values for equality.
 * @param real The actual short value obtained from the test.
 * @param expected The expected short value.
 * @param details Whether to print detailed test results.
 * @param seplen The length of the separator line.
 * @param sepch The character to use for the separator.
 * @return true if real equals expected, false otherwise.
 * @note When details is true, prints formatted output with separators.
 */
static inline bool basic_test_short(short real, short expected, bool details, unsigned int seplen, char sepch)
{
    if (details)
        print_test_short(real, expected, seplen, sepch);
    return real == expected;
}

/**
 * @brief Tests integer values for equality.
 * @param real The actual integer value obtained from the test.
 * @param expected The expected integer value.
 * @param details Whether to print detailed test results.
 * @param seplen The length of the separator line.
 * @param sepch The character to use for the separator.
 * @return true if real equals expected, false otherwise.
 * @note When details is true, prints formatted output with separators.
 */
static inline bool basic_test_int(int real, int expected, bool details, unsigned int seplen, char sepch)
{
    if (details)
        print_test_int(real, expected, seplen, sepch);
    return real == expected;
}

/**
 * @brief Tests size_t values for equality.
 * @param real The actual size_t value obtained from the test.
 * @param expected The expected size_t value.
 * @param details Whether to print detailed test results.
 * @param seplen The length of the separator line.
 * @param sepch The character to use for the separator.
 * @return true if real equals expected, false otherwise.
 * @note When details is true, prints formatted output with separators.
 */
static inline bool basic_test_size(size_t real, size_t expected, bool details, unsigned int seplen, char sepch)
{
    if (details)
        print_test_size(real, expected, seplen, sepch);
    return real == expected;
}

/**
 * @brief Tests long integer values for equality.
 * @param real The actual long value obtained from the test.
 * @param expected The expected long value.
 * @param details Whether to print detailed test results.
 * @param seplen The length of the separator line.
 * @param sepch The character to use for the separator.
 * @return true if real equals expected, false otherwise.
 * @note Provides optional detailed output with visual separators.
 */
static inline bool basic_test_long(long real, long expected, bool details, unsigned int seplen, char sepch)
{
    if (details)
        print_test_long(real, expected, seplen, sepch);
    return real == expected;
}

/**
 * @brief Tests float values for equality.
 * @param real The actual floating point value obtained from the test.
 * @param expected The expected floating point value.
 * @param details Whether to print detailed test results.
 * @param seplen The length of the separator line.
 * @param sepch The character to use for the separator.
 * @return true if real equals expected, false otherwise.
 * @note Provides optional detailed output with visual separators.
 */
static inline bool basic_test_float(float real, float expected, bool details, unsigned int seplen, char sepch, float resolution)
{
    if (resolution >= 5.0f)
    {
        printf("Warning[bad input]: high-resolution input.\n");
        resolution = 0.01f;
    }
    if (details)
        print_test_float(real, expected, seplen, sepch, resolution);
    return 100 * (fabs(expected - real) / fabs(expected)) <= resolution;
}

/**
 * @brief Tests double values for equality.
 * @param real The actual double value obtained from the test.
 * @param expected The expected double value.
 * @param details Whether to print detailed test results.
 * @param seplen The length of the separator line.
 * @param sepch The character to use for the separator.
 * @return true if real equals expected, false otherwise.
 * @note Provides optional detailed output with visual separators.
 */
static inline bool basic_test_double(double real, double expected, bool details, unsigned int seplen, char sepch, double resolution)
{
    if (resolution >= 5.0)
    {
        printf("Warning[bad input]: high-resolution input.\n");
        resolution = 0.01;
    }
    if (details)
        print_test_double(real, expected, seplen, sepch, resolution);
    return 100 * (fabs(expected - real) / fabs(expected)) <= resolution;
}

/**
 * @brief Tests strings values for equality.
 * @param real The actual const char ptr or(string) value obtained from the test.
 * @param expected The expected const char ptr or(string) value.
 * @param details Whether to print detailed test results.
 * @param seplen The length of the separator line.
 * @param sepch The character to use for the separator.
 * @return true if real equals expected, false otherwise.
 * @note Provides optional detailed output with visual separators.
 */
static bool string_test(const char *real, const char *expected, bool details, unsigned int seplen, char sepch)
{
    if (strlen(real) != strlen(expected))
    {
        if (details)
        {
            printf("context: unmatched length.\n");
            print_test_size(strlen(real), strlen(expected), seplen, sepch);
            return false;
        }
    }
    for (size_t i = 0; i < strlen(real); i++)
    {
        if (real[i] != expected[i])
        {
            if (details)
                print_test_string(real, expected, seplen, sepch, false);
            return false;
        }
    }
    if (details)
        print_test_string(real, expected, seplen, sepch, true);
    return true;
}

#ifdef METACORE___CLITE_MICROS_H

static inline CTEST ctest_bool(bool real, bool expected, cstrptr name, cstrptr description)
{
    CTEST newVal;
    return creatNew(newVal, name, description, real == expected);
}

static inline CTEST ctest_char(char real, char expected, cstrptr name, cstrptr description)
{
    CTEST newVal;
    return creatNew(newVal, name, description, real == expected);
}

static inline CTEST ctest_short(short real, short expected, cstrptr name, cstrptr description)
{
    CTEST newVal;
    return creatNew(newVal, name, description, real == expected);
}

static inline CTEST ctest_int(int real, int expected, cstrptr name, cstrptr description)
{
    CTEST newVal;
    return creatNew(newVal, name, description, real == expected);
}

static inline CTEST ctest_size(size_t real, size_t expected, cstrptr name, cstrptr description)
{
    CTEST newVal;
    return creatNew(newVal, name, description, real == expected);
}

static inline CTEST ctest_long(long real, long expected, cstrptr name, cstrptr description)
{
    CTEST newVal;
    return creatNew(newVal, name, description, real == expected);
}

static inline CTEST ctest_float(float real, float expected, float resolution, cstrptr name, cstrptr description)
{
    if (resolution >= 5.0f)
    {
        printf("Warning[bad input]: high-resolution input.\n");
        resolution = 0.01f;
    }
    CTEST newVal;
    return creatNew(newVal, name, description, 100 * (fabs(expected - real) / fabs(expected)) <= resolution);
}

static inline CTEST ctest_double(double real, double expected, double resolution, cstrptr name, cstrptr description)
{
    if (resolution >= 5.0)
    {
        printf("Warning[bad input]: high-resolution input.\n");
        resolution = 0.01;
    }
    CTEST newVal;
    return creatNew(newVal, name, description, 100 * (fabs(expected - real) / fabs(expected)) <= resolution);
}


static CTEST string_ctest(const cstrptr real, const cstrptr expected, cstrptr name, cstrptr description)
{
    CTEST newVal;
    if (strlen(real) != strlen(expected))
        return creatNew(newVal, name, description, false);
    for (size_t i = 0; i < strlen(real); i++)
    {
        if (real[i] != expected[i])
            return creatNew(newVal, name, description, false);
    }
    return creatNew(newVal, name, description, true);
}

#endif // METACORE___CLITE_MICROS_H

#ifdef OPENUDT___CUDT_CSTRING_H
static inline bool string_test(cstring real, cstring expected, bool details, unsigned int seplen, char sepch)
{
    return string_test(real.data, expected.data,
                       details, seplen, sepch);
}
#endif // OPENUDT___CUDT_CSTRING_H

typedef struct 
{
    bool details;
    unsigned int seplen;
    char sepch;
    size_t success_tests,
           failed_tests,
           total_tests;
} test_stream;

/// @brief this function will add a test value to the test stream struct.
/// @param current the current test stream value.
/// @param real the actual boolean value the we want to test.
/// @param expected the expected boolean value base on the desired behaver.
/// @param details Whether to print detailed test results.
/// @return test stream value after changing the values of it.
static inline test_stream addTestBool(test_stream current, bool real, bool expected, bool details) {
    bool temp = basic_test_bool(real, expected, details, current.seplen, current.sepch);
    if(temp) current.success_tests++;
    else current.failed_tests++;
    current.total_tests++;
    return current;
}

/// @brief this function will add a test value to the test stream struct.
/// @param current the current test stream value.
/// @param real the actual charater value the we want to test.
/// @param expected the expected charater value base on the desired behaver.
/// @param details Whether to print detailed test results.
/// @return test stream value after changing the values of it.
static inline test_stream addTestChar(test_stream current, char real, char expected, bool details) {
    bool temp = basic_test_char(real, expected, details, current.seplen, current.sepch);
    if(temp) current.success_tests++;
    else current.failed_tests++;
    current.total_tests++;
    return current;
}

/// @brief this function will add a test value to the test stream struct.
/// @param current the current test stream value.
/// @param real the actual short value the we want to test.
/// @param expected the expected short value base on the desired behaver.
/// @param details Whether to print detailed test results.
/// @return test stream value after changing the values of it.
static inline test_stream addTestShort(test_stream current, short real, short expected, bool details) {
    bool temp = basic_test_short(real, expected, details, current.seplen, current.sepch);
    if(temp) current.success_tests++;
    else current.failed_tests++;
    current.total_tests++;
    return current;
}

/// @brief this function will add a test value to the test stream struct.
/// @param current the current test stream value.
/// @param real the actual integer value the we want to test.
/// @param expected the expected integer value base on the desired behaver.
/// @param details Whether to print detailed test results.
/// @return test stream value after changing the values of it.
static inline test_stream addTestInt(test_stream current, int real, int expected, bool details) {
    bool temp = basic_test_int(real, expected, details, current.seplen, current.sepch);
    if(temp) current.success_tests++;
    else current.failed_tests++;
    current.total_tests++;
    return current;
}

/// @brief this function will add a test value to the test stream struct.
/// @param current the current test stream value.
/// @param real the actual long value the we want to test.
/// @param expected the expected long value base on the desired behaver.
/// @param details Whether to print detailed test results.
/// @return test stream value after changing the values of it.
static inline test_stream addTestLong(test_stream current, long real, long expected, bool details) {
    bool temp = basic_test_long(real, expected, details, current.seplen, current.sepch);
    if(temp) current.success_tests++;
    else current.failed_tests++;
    current.total_tests++;
    return current;
}

/// @brief this function will add a test value to the test stream struct.
/// @param current the current test stream value.
/// @param real the actual floating point value the we want to test.
/// @param expected the expected floating point value base on the desired behaver.
/// @param details Whether to print detailed test results.
/// @return test stream value after changing the values of it.
static inline test_stream addTestFloat(test_stream current, float real, float expected, bool details) {
    bool temp = basic_test_float(real, expected, details, current.seplen, current.sepch, 0.01f);
    if(temp) current.success_tests++;
    else current.failed_tests++;
    current.total_tests++;
    return current;
}

/// @brief this function will add a test value to the test stream struct.
/// @param current the current test stream value.
/// @param real the actual double value the we want to test.
/// @param expected the expected double value base on the desired behaver.
/// @param details Whether to print detailed test results.
/// @return test stream value after changing the values of it.
static inline test_stream addTestDouble(test_stream current, double real, double expected, bool details) {
    bool temp = basic_test_double(real, expected, details, current.seplen, current.sepch, 0.01);
    if(temp) current.success_tests++;
    else current.failed_tests++;
    current.total_tests++;
    return current;
}

/// @brief this function will add a test value to the test stream struct.
/// @param current the current test stream value.
/// @param real the actual size_t value the we want to test.
/// @param expected the expected size_t value base on the desired behaver.
/// @param details Whether to print detailed test results.
/// @return test stream value after changing the values of it.
static inline test_stream addTestSize(test_stream current, size_t real, size_t expected, bool details) {
    bool temp = basic_test_size(real, expected, details, current.seplen, current.sepch);
    if(temp) current.success_tests++;
    else current.failed_tests++;
    current.total_tests++;
    return current;
}

/**
 * @brief Calculates the average success rate (ASR) of tests.
 * @param ts The test_stream structure containing test statistics.
 * @return The average success rate as a percentage (0.0 - 100.0).
 * @note Uses floating-point arithmetic to avoid integer division truncation.
 */
static inline float ASR(test_stream ts) {
    if (ts.total_tests == 0) return 0.0f;
    return 100.0f * ts.success_tests / ts.total_tests;
}

/**
 * @brief Calculates the average failure rate (AFR) of tests.
 * @param ts The test_stream structure containing test statistics.
 * @return The average failure rate as a percentage (0.0 - 100.0).
 * @note Uses floating-point arithmetic to avoid integer division truncation.
 */
static inline float AFR(test_stream ts) {
    if (ts.total_tests == 0) return 0.0f;
    return 100.0f * ts.failed_tests / ts.total_tests;
}

/**
 * @brief Prints a comprehensive test summary report.
 * @param testResults The test_stream structure containing accumulated test results.
 * @details This function displays formatted test statistics including:
 *          - Success test count
 *          - Failure test count
 *          - Total test count
 *          - Average success rate (ASR) as a percentage
 *          - Average failure rate (AFR) as a percentage
 */
static inline void print(test_stream testResults) {
    const char *category = "test summary";
    print_category(category);
    printf("\nThe success tests: %zu\n", testResults.success_tests);
    printf("The failed tests: %zu\n", testResults.failed_tests);
    printf("The total tests: %zu\n", testResults.total_tests);
    printf("Average success rate: %.2f%%\n", ASR(testResults));
    printf("Average failed rate: %.2f%%\n", AFR(testResults));
}

#endif // METACORE___CLITE_UNITTEST_H