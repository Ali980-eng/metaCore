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
 * - Character constants (nl, ctab)
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

#ifndef METACORE___CGEN_MICROS_H
#define METACORE___CGEN_MICROS_H

#ifdef cobject_data_micros
#include "micros/object_data.h"
#endif // cobject_data_micros

#ifndef cobject_data_micros

    #include "micros/io.h"
    #include "micros/string.h"
    #include "micros/structure.h"
    #include "micros/test.h"

    #ifdef METACORE___CGEN_IOUTILITYS_H
    
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

    #endif // METACORE___CGEN_IOUTILITYS_H

    #ifdef METACORE___CGEN_UNITTEST_H

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

    #endif // METACORE___CGEN_UNITTEST_H

    #ifdef METACORE___CGEN_BITUTILITYS_H

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
        
    #endif // METACORE___CGEN_BITUTILITYS_H

#endif // cobject_data_micros

#endif // METACORE___CGEN_MICROS_H