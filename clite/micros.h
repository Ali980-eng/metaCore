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
 * - String type alias (cstr)
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

    #ifdef COBJECT_DATA

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
    
    #endif // COBJECT_DATA
    
    #ifndef COBJECT_DATA

        #define INIT_TEST(name)        \
            double tests_passed = 0.0; \
            double tests_failed = 0.0; \
            double total_tests = 0.0;  \
            char testName[] = #name;

        #define printSummary                                    \
            printf("\n-------------------------------");        \
            printf("\n<<<<<<<<< test summary >>>>>>>>");        \
            printf("\n-------------------------------");        \
            printf("TEST NAME: %s", testName);                  \
            printf("\npassed tests: %i", (int)tests_passed);    \
            printf("\nfailed tests: %i", (int)tests_failed);    \
            printf("\ntotal tests: %i", (int)total_tests);      \
            if(total_tests > 0) {                               \
                printf("\npassed tests ratio: %f",              \
                    (double) (100 * (tests_passed / total_tests))); \
                printf("\nfailed tests ratio: %f",              \
                    (double) (100 * (tests_failed / total_tests))); \
            } else {                                            \
                printf("\npassed tests ratio: 0.0");            \
                printf("\nfailed tests ratio: 0.0");            \
            }                                                   \
            printf("\n-------------------------------\n");

        #define MAIN_TEST(name)            \
            int main()                     \
            {                              \
                double tests_passed = 0.0; \
                double tests_failed = 0.0; \
                double total_tests = 0.0;  \
                char testName[] = #name;

        #define EXIT_TEST(PS)             \
                if(PS) {                  \
                    printSummary          \
                }                         \
                return (int)tests_failed; \
            }

        #define TEST_0(cond)                            \
            total_tests++;                              \
            if (cond) {                                 \
                tests_passed++;                         \
            } else {                                    \
                tests_failed++;                         \
                printf("FAIL[%d]\n", (int)total_tests); \
            }

        #define TEST_1(cond, msg)                                \
            total_tests++;                                       \
            if (cond) {                                          \
                tests_passed++;                                  \
            } else {                                             \
                tests_failed++;                                  \
                printf("FAIL[%d]: %s\n", (int)total_tests, msg); \
            }

        #define TEST_2(real, expected)                  \
            total_tests++;                              \
            if(real == expected) {                      \
                tests_passed++;                         \
            } else {                                    \
                tests_failed++;                         \
                printf("FAIL[%d]\n", (int)total_tests); \
            }

        #define TEST_3(real, expected, msg)                      \
            total_tests++;                                       \
            if(real == expected) {                               \
                tests_passed++;                                  \
            } else {                                             \
                tests_failed++;                                  \
                printf("FAIL[%d]: %s\n", (int)total_tests, msg); \
            }

        #define ASSERT(cond)                \
            if (!(cond)) {                  \
                retval = 1;                 \
                printf("FAILED: %s", cond); \
            }

        #define MAIN   \
            int main() \
            {

        #define RET(retval)         \
                return (int)retval; \
            }

        #define cobject(name, elements) \
            typedef struct { elements } name;
        
        #define cnl '\n'
        
        #define ctab '\t'

        #define cstr char*

        size_t length(const cstr value) {
            return (value != NULL) ? strlen(value) : 0;
        }

        bool equal(const cstr value_1, const cstr value_2) {
            if(value_1 == NULL || value_2 == NULL) return false;
            return strcmp(value_1, value_2) == 0 ? true : false;
        }

        cstr concatenate(cstr value_1, const cstr value_2) {
            if(value_1 == NULL || value_2 == NULL) return value_1;
            return strcat(value_1, value_2);
        }

        bool is_empty(const cstr value) {
            return (value == NULL || strlen(value) == 0) ? true : false;
        }

        void* cstr_empty(cstr value) {
            if(is_empty(value)) return NULL;
            return realloc(value, 1);
        }

        void cstr_free(cstr value) {
            if(is_empty(value)) {
                printf("Error: can't free NULL or empty strings.\n");
                return;
            }
            free(value);
        }

        bool exist(const cstr value, char c) {
            if(value == NULL || is_empty(value)) {
                printf("bad input: input string is empty.\n");
                return false;
            }
            for(size_t i = 0, e = length(value); i < e; i++) {
                if(value[i] == c) return true;
            }
            return false;
        }

        bool sub_exist(const cstr value_1, const cstr value_2) {
            if(value_1 == NULL || value_2 == NULL || is_empty(value_1) || is_empty(value_2)) {
                printf("bad input: one of the input strings is empty.\n");
                return false;
            }
            bool sequence = false;
            size_t ei = length(value_1), ej = length(value_2);
            for(size_t i = 0, j = 0; i < ei; i++) {
                if(value_1[i] == value_2[j] && sequence) {
                    if(j == ej - 1) return true;
                    j++;
                    continue;
                }
                if(value_1[i] == value_2[j]) {
                    sequence = true;
                    j++;
                }
            }
            return false;
        }

        size_t count(const cstr value, char c) {
            if(value == NULL || is_empty(value)) {
                printf("bad input: input string is empty.");
                return (size_t)0;
            }
            size_t result = 0;
            for(size_t i = 0, e = length(value); i < e; i++) {
                if(value[i] == c) result++;
            }
            return result;
        }

        #define jump goto

        #define jump_if(condition, label) \ 
            if(condition) goto label;

    #endif // COBJECT_DATA

#endif // METACORE___CLITE_CMICROS_H