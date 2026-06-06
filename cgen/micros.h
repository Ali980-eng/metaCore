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

#ifndef METACORE___META_CGEN_MICROS_H
#define METACORE___META_CGEN_MICROS_H

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

        #define nl '\n'

        #define tab '\t'

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

        static inline size_t length(const cstrptr value)
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
    
    #ifdef METACORE___META_CGEN_IOUTILITYS_H
    
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

    #endif // METACORE___META_CGEN_IOUTILITYS_H

    #ifdef METACORE___META_CGEN_UNITTEST_H

        #define addTest(current, real, expected, details) _Generic((real), \
            bool: addTestBool(current, real, expected, details),           \
            char: addTestChar(current, real, expected, details),           \
            short: addTestShort(current, real, expected, details),         \
            int: addTestInt(current, real, expected, details),             \
            long: addTestLong(current, real, expected, details),           \
            size_t: addTestSize(current, real, expected, details),         \
            float: addTestFloat(current, real, expected, details),         \
            double: addTestDouble(current, real, expected, details))

        #define basic_test(real, expected, details, seplen, sepch) _Generic((real), \
            bool: basic_test_bool(real, expected, details, seplen, sepch),          \
            char: basic_test_char(real, expected, details, seplen, sepch),          \
            short: basic_test_short(real, expected, details, seplen, sepch),        \
            int: basic_test_int(real, expected, details, seplen, sepch),            \
            long: basic_test_long(real, expected, details, seplen, sepch),          \
            size_t: basic_test_size(real, expected, details, seplen, sepch),        \
            float: basic_test_float(real, expected, details, seplen, sepch),        \
            double: basic_test_double(real, expected, details, seplen, sepch))

        #define ctest(real, expected, name, description) _Generic((real), \
            bool: ctest_bool(real, expected, name, description),          \
            char: ctest_char(real, expected, name, description),          \
            short: ctest_short(real, expected, name, description),        \
            int: ctest_int(real, expected, name, description),            \
            long: ctest_long(real, expected, name, description),          \
            size_t: ctest_size(real, expected, name, description),        \
            float: ctest_float(real, expected, 0.01f, name, description), \
            double: ctest_double(real, expected, 0.01, name, description))

    #endif // METACORE___META_CGEN_UNITTEST_H

    #ifdef METACORE___META_CGEN_BITUTILITYS_H

        #define to_binary_string(value) _Generic((value), \
            int8_t: bit8_str(value),                      \
            int16_t: bit16_str(value),                    \
            int32_t: bit32_str(value),                    \
            int64_t: bit64_str(value),                    \
            uint8_t: ubit8_str(value),                    \
            uint16_t: ubit16_str(value),                  \
            uint32_t: ubit32_str(value),                  \
            uint64_t: ubit64_str(value))

        #define print_binary(value, pnl) _Generic((value), \
            int8_t: print8bit(value, pnl),                 \
            int16_t: print16bit(value, pnl),               \
            int32_t: print32bit(value, pnl),               \
            int64_t: print64bit(value, pnl),               \
            uint8_t: print_u8bit(value, pnl),              \
            uint16_t: print_u16bit(value, pnl),            \
            uint32_t: print_u32bit(value, pnl),            \
            uint64_t: print_u64bit(value, pnl))


        #define count_bit(num, ones) _Generic((num), \
            int8_t: count_8bit(num, ones),           \
            int16_t: count_16bit(num, ones),         \
            int32_t: count_32bit(num, ones),         \
            int64_t: count_64bit(num, ones),         \
            uint8_t: count_u8bit(num, ones),         \
            uint16_t: count_u16bit(num, ones),       \
            uint32_t: count_u32bit(num, ones),       \
            uint64_t: count_u64bit(num, ones))

        #define get_bit(num, position) _Generic((num), \
            int8_t: get_8bit(num, position),           \
            int16_t: get_16bit(num, position),         \
            int32_t: get_32bit(num, position),         \
            int64_t: get_64bit(num, position),         \
            uint8_t: get_u8bit(num, position),         \
            uint16_t: get_u16bit(num, position),       \
            uint32_t: get_u32bit(num, position),       \
            uint64_t: get_u64bit(num, position))

        #define reset_bit(num, position) _Generic((num), \
            int8_t: reset_8bit(num, position),           \
            int16_t: reset_16bit(num, position),         \
            int32_t: reset_32bit(num, position),         \
            int64_t: reset_64bit(num, position),         \
            uint8_t: reset_u8bit(num, position),         \
            uint16_t: reset_u16bit(num, position),       \
            uint32_t: reset_u32bit(num, position),       \
            uint64_t: reset_u64bit(num, position))
        
        #define set_bit(num, position) _Generic((num), \
            int8_t: set_char_bit(num, position),       \
            int16_t: set_short_bit(num, position),     \
            int32_t: set_int_bit(num, position),       \
            int64_t: set_long_bit(num, position),      \
            uint8_t: set_u8bit(num, position),         \
            uint16_t: set_u16bit(num, position),       \
            uint32_t: set_u32bit(num, position),       \
            uint64_t: set_u64bit(num, position))

        #define toggle_bit(num, position) _Generic((num), \
            uint8_t: toggle_u8bit(num, position),         \
            uint16_t: toggle_u16bit(num, position),       \
            uint32_t: toggle_u32bit(num, position),       \
            uint64_t: toggle_u64bit(num, position),       \
            int8_t: toggle_8bit(num, position),           \
            int16_t: toggle_16bit(num, position),         \
            int32_t: toggle_32bit(num, position),         \
            int64_t: toggle_64bit(num, position))

        
        #define xchg_bit(value, pos1, pos2) _Generic((value), \
            uint8_t: xchg_u8bit(value, pos1, pos2),           \
            uint16_t: xchg_u16bit(value, pos1, pos2),         \
            uint32_t: xchg_u32bit(value, pos1, pos2),         \
            uint64_t: xchg_u64bit(value, pos1, pos2),         \
            int8_t: xchg_8bit(value, pos1, pos2),             \
            int16_t: xchg_16bit(value, pos1, pos2),           \
            int32_t: xchg_32bit(value, pos1, pos2),           \
            int64_t: xchg_64bit(value, pos1, pos2))
        
    #endif // METACORE___META_CGEN_BITUTILITYS_H
    
    #ifdef __cplusplus

        #include <string>

        #define object class
        
        typedef std::string str;

        #define meta_lambda(capture_clause, parameters, return_type, script) \
            [capture_clause] parameters -> return_type { script }

    #endif // __cplusplus

#endif // cobject_data_micros

#endif // METACORE___META_CGEN_MICROS_H