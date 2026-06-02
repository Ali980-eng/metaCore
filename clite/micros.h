/**
 * @file micros.h
 * @brief Micro Definitions and Utility Macros
 * @author MetaCore Development Team
 * @date May 25, 2026
 *
 * @details
 * This file provides comprehensive macro definitions for constant declarations, object definitions,
 * and testing utilities. It has two main modes controlled by COBJECT_DATA:
 *
 * COBJECT_DATA Mode: Constant declaration macros
 * - Macros for declaring typed constants (cbool, cchar, cint, cfloat, cdouble, etc.)
 * - Array definition macros (carray_i32, carray_f64)
 * - Section attribute for memory placement (DATA_SEC)
 * - Type inference macros in non-strict mode (cauto, cdynamic)
 * - Optional logic restriction macros when ALLOW_LOGIC_MODE is disabled
 *
 * Standard Mode: Testing utilities and string operations
 * - Test framework macros (INIT_TEST, MAIN_TEST, EXIT_TEST, TEST_0 through TEST_3)
 * - Assertion macro (ASSERT)
 * - Object/struct definition macro (cobject)
 * - Character constants (cnl, ctab)
 * - String type alias (cstrptr)
 *
 * @functions (Standard Mode)
 * - length()           : Get string length
 * - equal()            : Compare two strings for equality
 * - concatenate()      : Concatenate two strings
 * - is_empty()         : Check if string is empty or NULL
 * - empty()            : Clear string content
 * - free()             : Free string memory
 * - exist()            : Check if character exists in string
 * - sub_exist()        : Check if substring exists in string
 * - count()            : Count occurrences of character in string
 */

#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef METACORE___CLITE_MICROS_H
#define METACORE___CLITE_MICROS_H

#define cstring_micros
#define ctesting_micros
#define cstructure_micros
#define cio_micros

#ifdef cobject_data_micros

    #include <stdint.h>

    /// Section attribute for placing data in a specific section of memory
    #define DATA_SEC __attribute__((section(".cdata_space")))

    /// Boolean definitions
    #define cbool(name, val) const _Bool name = val;

    /// 8-bit integer definitions
    #define cchar(name, val) const char name = val;

    /// 16-bit integer definitions
    #define cshort(name, val) const short name = val;

    /// 32-bit integer definitions
    #define cint(name, val) const int name = val;

    /// 32-bit floating-point definitions
    #define cfloat(name, val) const float name = val;

    /// 64-bit floating-point definitions
    #define cdouble(name, val) const double name = val;

    /// 64-bit integer definitions
    #define clong(name, val) const long name = val;

    /// 64-bit integer definitions
    #define cint8(name, val) const int8_t name = val;

    /// 16-bit integer definition
    #define cint16(name, val) const int16_t name = val;

    /// 32-bit integer definition
    #define cint32(name, val) const int32_t name = val;

    /// 8-bit unsigned integer definition
    #define cuint8(name, val) const uint8_t name = val;

    /// 16-bit unsigned integer definition
    #define cuint16(name, val) const uint16_t name = val;

    /// 32-bit unsigned integer definition
    #define cuint32(name, val) const uint32_t name = val;

    /// String definitions
    #define cstring(name, val) const char name[] = val;

    /// In strict mode, we can use 'const auto' for type inference. In non-strict mode, we fall back to 'const __typeof__' for compatibility.
    #ifndef STRICT_MODE

    /// In non-strict mode, we use 'const __typeof__' to infer the type of the value.
    #define cauto(name, val) const auto name = val;

    /// In non-strict mode, we use 'const __typeof__' to infer the type of the value.
    #define cdynamic(name, val) const __typeof__(val) name = val;

    #endif // STRICT_MODE

    /// 64-bit integer definitions with alignment for 64-bit platforms
    #if defined(_WIN64)

    /// On Windows 64-bit, __int64 is already 8-byte aligned, so no special attribute is needed.
    #define cint64(name, val) const int64_t name __attribute__((aligned(8))) = val;

    /// On Windows 64-bit, __int64 is already 8-byte aligned, so no special attribute is needed.
    #define cuint64(name, val) const uint64_t name __attribute__((aligned(8))) = val;

    #endif // _WIN64

    /// Array definitions
    #define carray_i32(name, ...) const int32_t name[] = {__VA_ARGS__};

    /// Array definitions
    #define carray_f64(name, ...) const double name[] = {__VA_ARGS__};

    // allows for using in regular libraries without previnting basic language features
    #ifndef ALLOW_LOGIC_MODE

    /// Function definitions
    #define void ERROR_FUNCTIONS_NOT_ALLOWED

    /// Control flow definitions
    #define if ERROR_LOGIC_NOT_ALLOWED

    /// Loop definitions
    #define for ERROR_LOGIC_NOT_ALLOWED

    /// Switch-case definitions
    #define do ERROR_LOGIC_NOT_ALLOWED

    /// Switch-case definitions
    #define switch ERROR_LOGIC_NOT_ALLOWED

    /// Jump definitions
    #define while ERROR_LOGIC_NOT_ALLOWED

    /// Structure definitions
    #define struct ERROR_STRUCT_NOT_ALLOWED

    /// Union definitions
    #define register ERROR_NOT_ALLOWED

    /// Type definitions
    #define goto ERROR_LOGIC_NOT_ALLOWED

    /// Type definitions
    #define typedef ERROR_TYPE_NOT_ALLOWED

    #endif // ALLOW_LOGIC_MODE

#endif // cobject_data_micros

#ifndef cobject_data_micros

    #ifdef cio_micros

        #define cnl '\n'

        #define ctab '\t'

        #define cprint(output) \
            printf(output)

        #define cprintln(output) \
            printf(output);      \
            printf(cnl)

        #define cprint_if(condition, output) \
            if(condition) printf(output)

        #define cprintln_if(condition, output) \
            if(condition) printf(output);      \
            printf(cnl)

    #endif // cio_micros

    #ifdef ctesting_micros

        #define INIT_TEST(name)        \
            double tests_passed = 0.0; \
            double tests_failed = 0.0; \
            double total_tests = 0.0;  \
            char testName[] = #name;

        #define printSummary                                          \
            printf("\n-------------------------------");              \
            printf("\n<<<<<<<<< test summary >>>>>>>>");              \
            printf("\n-------------------------------");              \
            printf("\nTEST NAME: %s", testName);                      \
            printf("\npassed tests: %i", (int)tests_passed);          \
            printf("\nfailed tests: %i", (int)tests_failed);          \
            printf("\ntotal tests: %i", (int)total_tests);            \
            if (total_tests > 0)                                      \
            {                                                         \
                printf("\npassed tests ratio: %f",                    \
                    (double)(100 * (tests_passed / total_tests))); \
                printf("\nfailed tests ratio: %f",                    \
                    (double)(100 * (tests_failed / total_tests))); \
            }                                                         \
            else                                                      \
            {                                                         \
                printf("\npassed tests ratio: 0.0");                  \
                printf("\nfailed tests ratio: 0.0");                  \
            }                                                         \
            printf("\n-------------------------------\n");

        #define MAIN_TEST(name)            \
            int main()                     \
            {                              \
                double tests_passed = 0.0; \
                double tests_failed = 0.0; \
                double total_tests = 0.0;  \
                char testName[] = #name;

        #define EXIT_TEST(PS)         \
            if (PS)                   \
            {                         \
                printSummary          \
            }                         \
            return (int)tests_failed; \
            }

        #define TEST_0(cond)                            \
            total_tests++;                              \
            if (cond)                                   \
            {                                           \
                tests_passed++;                         \
            }                                           \
            else                                        \
            {                                           \
                tests_failed++;                         \
                printf("FAIL[%d]\n", (int)total_tests); \
            }

        #define TEST_1(cond, msg)                                \
            total_tests++;                                       \
            if (cond)                                            \
            {                                                    \
                tests_passed++;                                  \
            }                                                    \
            else                                                 \
            {                                                    \
                tests_failed++;                                  \
                printf("FAIL[%d]: %s\n", (int)total_tests, msg); \
            }

        #define TEST_2(real, expected)                  \
            total_tests++;                              \
            if (real == expected)                       \
            {                                           \
                tests_passed++;                         \
            }                                           \
            else                                        \
            {                                           \
                tests_failed++;                         \
                printf("FAIL[%d]\n", (int)total_tests); \
            }

        #define TEST_3(real, expected, msg)                      \
            total_tests++;                                       \
            if (real == expected)                                \
            {                                                    \
                tests_passed++;                                  \
            }                                                    \
            else                                                 \
            {                                                    \
                tests_failed++;                                  \
                printf("FAIL[%d]: %s\n", (int)total_tests, msg); \
            }

        #define ASSERT_TEST(cond)                                \
            if(!(cond)) {                                        \
                tests_failed++;                                  \
                printf("FAIL[%d]\n", (int)total_tests); \
            } else {                                             \
                tests_passed++;                                  \
            }                                                    \
            total_tests++;

        #define ASSERT(cond)                \
            if (!(cond))                    \
            {                               \
                retval = 1;                 \
                printf("FAILED: %s", cond); \
            }

    #endif // ctesting_micros

    #ifdef cstructure_micros

        #define MAIN   \
            int main() \
            {

        #define RET(retval)     \
            return (int)retval; \
            }

        #define cobject(name, elements) \
            typedef struct              \
            {                           \
                elements                \
            } name

        #define cenum \
            typedef enum

        #define jump(label) \
            goto label

        #define jump_if(condition, label) \
            if (condition)                \
                goto label

    #endif // cstructure_micros

    #ifdef cstring_micros

        #define cstrptr char *

        #define cstr(name, sizeValue) \
            char name[sizeValue]

        static size_t length(const cstrptr value)
        {
            return (value != NULL) ? strlen(value) : 0;
        }

        static inline bool equal(const cstrptr value_1, const cstrptr value_2)
        {
            if (value_1 == NULL || value_2 == NULL)
                return false;
            return strcmp(value_1, value_2) == 0 ? true : false;
        }

        static inline cstrptr concatenate(cstrptr value_1, const cstrptr value_2)
        {
            if (value_1 == NULL || value_2 == NULL)
                return value_1;
            return strcat(value_1, value_2);
        }

        static inline bool is_empty(const cstrptr value)
        {
            return (value == NULL || strlen(value) == 0) ? true : false;
        }

        /**
         * @brief Clear string content by reallocating to empty string
         * @param value The string to clear
         * @return Pointer to cleared string or NULL if input is NULL
         * @note Properly handles memory reallocation for empty string
         */
        static void *cstr_empty(cstrptr value)
        {
            if (value == NULL)
                return NULL;
            
            // Free old memory and allocate fresh 1 byte for empty string
            char *temp = (char *)malloc(1);
            if (temp != NULL) {
                temp[0] = '\0';
                free(value);
                return temp;
            }
            return NULL;
        }

        /**
         * @brief Free allocated string memory
         * @param value The string to free
         * @note Safely handles NULL pointers, frees any non-NULL string regardless of content
         */
        static void cstr_free(cstrptr value)
        {
            if (value == NULL)
            {
                printf("Warning: attempting to free NULL pointer.\n");
                return;
            }
            free(value);
        }

        static bool exist(const cstrptr value, char c)
        {
            if (value == NULL || is_empty(value))
            {
                printf("bad input: input string is empty.\n");
                return false;
            }
            for (size_t i = 0, e = length(value); i < e; i++)
            {
                if (value[i] == c)
                    return true;
            }
            return false;
        }

        /**
         * @brief Check if substring exists in string
         * @param value_1 The main string to search in
         * @param value_2 The substring to search for
         * @return true if substring is found, false otherwise
         * @note Uses standard strstr for reliable substring search with proper pattern handling
         */
        static bool sub_exist(const cstrptr value_1, const cstrptr value_2)
        {
            if (value_1 == NULL || value_2 == NULL || is_empty(value_1) || is_empty(value_2))
            {
                printf("bad input: one of the input strings is empty.\n");
                return false;
            }
            
            // Use standard strstr function for reliable substring search
            // This properly handles overlapping patterns and multiple occurrences
            return strstr(value_1, value_2) != NULL ? true : false;
        }

        static size_t count(const cstrptr value, char c)
        {
            if (value == NULL || is_empty(value))
            {
                printf("bad input: input string is empty.");
                return (size_t)0;
            }
            size_t result = 0;
            for (size_t i = 0, e = length(value); i < e; i++)
            {
                if (value[i] == c)
                    result++;
            }
            return result;
        }

    #endif // cstring_micros

#endif // cobject_data_micros

#endif // METACORE___CLITE_CMICROS_H