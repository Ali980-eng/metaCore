#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ALL_MICROS

#ifndef METACORE___CLITE_MICROS_H
#define METACORE___CLITE_MICROS_H

    #ifdef ALL_MICROS
        #define TESTING_MICROS
        #define UTILITYS_FORMAT
        #define STRING_MICROS
    #endif // ALL_MICROS

    #ifdef OBJECT_DATA

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
    
    #endif // OBJECT_DATA
    
    #if defined(TESTING_MICROS) && !defined(OBJECT_DATA)

        size_t cttn = 0;

        typedef struct {
            char* name;
            char* description;
            size_t num;
            bool result;
        } ctt;

        #define INIT_TEST(name)        \
            double tests_passed = 0.0; \
            double tests_failed = 0.0; \
            double total_tests = 0.0;  \
            char testName[] = name;

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
                char testName[] = name;

        #define EXIT_TEST(PS)             \
                if(PS) {                  \
                    printSummary          \
                }                         \
                return (int)tests_failed; \
            }

        #define TEST ctt

        TEST creatNew(TEST current, char* name, char* des, bool value) {
            current.name = (name != NULL) ? name : "";
            current.description = (des != NULL) ? des : "";
            current.num = cttn;
            cttn++;
            current.result = value;
            return current;
        }

        bool catchValue(TEST current) {
            return current.result;
        }

        void printTest(TEST current) {
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

    #endif // TESTING_MICROS

    #if defined(UTILITYS_FORMAT) && !defined(OBJECT_DATA)

        #define MAIN   \
            int main() \
            {

        #define RET(retval)         \
                return (int)retval; \
            }

        #define cobject(name, script) \
            typedef struct { script } name;
        
        #define cnl '\n'
        
        #define ctab '\t'
        
    #endif // UTILITYS_FORMAT
    
    #if defined(STRING_MICROS) && !defined(OBJECT_DATA)

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

        void* empty(const cstr value) {
            if(value == NULL || is_empty(value)) return NULL;
            return realloc(value, 1);
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

    #endif // STRING_MICROS

#endif // METACORE___CLITE_CMICROS_H