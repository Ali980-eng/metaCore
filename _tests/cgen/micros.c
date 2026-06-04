#include "cgen/micros.h"

/**
 * @file micros.c
 * @brief Comprehensive test suite for micros.h library
 * @details Tests cstring_micros functions and jump macros with various edge cases
 * @note References constant values from CObjectData.c (compiled separately)
 */

// External declarations for CObjectData constants (compiled in object file)
extern const _Bool value1;
extern const char value2;
extern const short value3;
extern const int value4;
extern const long value5;
extern const unsigned char value6;
extern const unsigned short value7;
extern const unsigned int value8;
extern const unsigned long value9;
extern const signed char value10;
extern const short value11;
extern const int value12;
extern const long value13;
extern const double value14;
extern const float value15;
extern const double value16;
extern const char value17[];
extern const int value18[];
extern const double value19[];
extern const int value20;

MAIN_TEST(micros)
    
    // ==================== JUMP MACROS TESTS ====================
    // Test basic jump loop
    short jv1 = 0, jv2 = 0, jv3 = 100, jv4 = 200, jv5 = 10;
    
    // Jump loop 1: increment until reaching 50
    tl1: jv1++;
    jump_if(jv1 < 50, tl1);
    TEST_2(jv1, 50)  // Should stop at 50
    
    // Jump loop 2: increment from 0 to 50 (inclusive)
    tl2: jv2++;
    jump_if(jv2 <= 50, tl2);
    TEST_2(jv2, 51)  // Should be 51 when loop breaks
    
    // Jump loop 3: decrement from 100 to 0
    tl3: jv3--;
    jump_if(jv3 > 0, tl3);
    TEST_2(jv3, 0)  // Should stop at 0
    
    // Jump loop 4: decrement from 200 to -1
    tl4: jv4--;
    jump_if(jv4 >= 0, tl4);
    TEST_2(jv4, -1)  // Should be -1 when loop breaks
    
    // Jump loop 5: decrement until not equal to 5
    tl5: jv5--;
    jump_if(jv5 != 5, tl5);
    TEST_2(jv5, 5)  // Should stop at 5
    
    // Advanced jump test: nested labels
    int counter = 0, result = 0;
    tl_outer: counter++;
    if (counter < 3) {
        result += 10;
        jump_if(counter < 3, tl_outer);
    }
    TEST_2(counter, 3)
    TEST_2(result, 20)
    
    // Edge case: jump with boundary conditions
    int boundary_test = 0;
    tl_boundary: boundary_test++;
    jump_if(boundary_test < 1, tl_boundary);
    TEST_2(boundary_test, 1)
    
    // ==================== CSTRING_MICROS TESTS ====================
    
    // Test 1: length() function
    cstr(s1,) = "09iie8";
    TEST_2(length(s1), 6)
    
    cstr(s_empty,) = "";
    TEST_2(length(s_empty), 0)
    
    cstr(s_single,) = "A";
    TEST_2(length(s_single), 1)
    
    cstr(s_long,) = "This is a longer test string";
    TEST_2(length(s_long), 28)
    
    // Test 2: equal() function
    cstr(s2,) = "88938";
    TEST_2(equal(s1, s2), false)  // Different strings
    TEST_2(length(s2), 5)
    
    cstr(s3,) = "88938";
    TEST_2(equal(s2, s3), true)  // Identical strings
    
    cstr(s_test1,) = "test";
    cstr(s_test2,) = "test";
    TEST_2(equal(s_test1, s_test2), true)
    
    cstr(s_test3,) = "Test";
    TEST_2(equal(s_test1, s_test3), false)  // Case sensitive
    
    TEST_2(equal(NULL, s_test1), false)  // NULL check
    TEST_2(equal(s_test1, NULL), false)  // NULL check
    
    // Test 3: is_empty() function
    TEST_2(is_empty(s3), false)
    TEST_2(is_empty(s_empty), true)
    TEST_2(is_empty(NULL), true)  // NULL is empty
    
    // Test 4: exist() function - check if character exists
    TEST_2(exist(s2, '8'), true)  // '8' exists in "88938"
    TEST_2(exist(s2, '3'), true)  // '3' exists
    TEST_2(exist(s2, 'i'), false) // 'i' doesn't exist
    TEST_2(exist(s2, '9'), true)  // '9' exists
    
    cstr(s_alpha,) = "abcdefghijklmnopqrstuvwxyz";
    TEST_2(exist(s_alpha, 'a'), true)
    TEST_2(exist(s_alpha, 'z'), true)
    TEST_2(exist(s_alpha, 'm'), true)
    TEST_2(exist(s_alpha, 'A'), false)  // Case sensitive
    
    // Test 5: concatenate() function
    cstr(s_concat1, 100) = "Hello";
    cstr(s_concat2,) = " World";
    cstr(s_result,) = concatenate(s_concat1, s_concat2);
    TEST_2(length(s_result), 11)  // "Hello World" is 11 chars
    TEST_2(equal(s_result, "Hello World"), true)
    
    cstr(s_c1, 50) = "Test";
    cstr(s_c2,) = "123";
    concatenate(s_c1, s_c2);
    TEST_2(equal(s_c1, "Test123"), true)
    
    // Test concatenate with empty string
    cstr(s_c3, 50) = "Base";
    cstr(s_c4,) = "";
    concatenate(s_c3, s_c4);
    TEST_2(equal(s_c3, "Base"), true)  // Should remain unchanged
    
    // Test 6: sub_exist() function - check if substring exists
    TEST_2(sub_exist(s2, "938"), true)  // "938" exists in "88938"
    TEST_2(sub_exist(s2, "88"), true)   // "88" exists at start
    TEST_2(sub_exist(s2, "8"), true)    // "8" exists
    TEST_2(sub_exist(s2, "88k"), false) // "88k" doesn't exist
    TEST_2(sub_exist(s2, "xyz"), false) // "xyz" doesn't exist
    
    cstr(s_sub1,) = "MetaCoreSystem";
    TEST_2(sub_exist(s_sub1, "Meta"), true)
    TEST_2(sub_exist(s_sub1, "Core"), true)
    TEST_2(sub_exist(s_sub1, "System"), true)
    TEST_2(sub_exist(s_sub1, "CoreSys"), true)  // Overlapping match
    TEST_2(sub_exist(s_sub1, "meta"), false)    // Case sensitive
    TEST_2(sub_exist(s_sub1, "xyz"), false)
    
    // Test 7: count() function - count character occurrences
    TEST_2(count(s2, '8'), 3)   // "88938" has three '8's (positions 0, 1, 4)
    TEST_2(count(s1, 'i'), 2)   // "09iie8" has two 'i's
    TEST_2(count(s1, 'e'), 1)   // "09iie8" has one 'e'
    TEST_2(count(s1, '0'), 1)   // "09iie8" has one '0'
    
    cstr(s_count,) = "aaaaabbbccc";
    TEST_2(count(s_count, 'a'), 5)
    TEST_2(count(s_count, 'b'), 3)
    TEST_2(count(s_count, 'c'), 3)
    TEST_2(count(s_count, 'd'), 0)  // Character doesn't exist
    
    cstr(s_special,) = "...***===***...";
    TEST_2(count(s_special, '.'), 6)
    TEST_2(count(s_special, '*'), 6)
    TEST_2(count(s_special, '='), 3)
    
    // Test 8: cstr_empty() function
    cstr(s_to_empty, 100) = "ToBeCleared";
    TEST_2(is_empty(s_to_empty), false)
    cstr_empty(s_to_empty);
    TEST_2(is_empty(s_to_empty), true)  // Should be empty now
    
    // Test 9: cstr_free() function
    cstr(s_temp1,) = "test1";
    cstr_free(s_temp1);  // Should free without error
    
    cstr(s_temp2,) = "";
    cstr_free(s_temp2);  // Should free empty string
    
    // ==================== EDGE CASES AND SPECIAL CHARACTERS ====================
    
    // Test with special characters
    cstr(s_special_chars,) = "\n\t\r\\";
    TEST_2(length(s_special_chars), 4)  // 4 escape sequences
    
    // Test with numeric strings
    cstr(s_numeric,) = "1234567890";
    TEST_2(length(s_numeric), 10)
    TEST_2(count(s_numeric, '1'), 1)
    TEST_2(exist(s_numeric, '5'), true)
    
    // Test with mixed case
    cstr(s_mixed,) = "AbCdEfGhIj";
    TEST_2(length(s_mixed), 10)
    TEST_2(count(s_mixed, 'A'), 1)
    TEST_2(count(s_mixed, 'a'), 0)  // Case sensitive
    
    // ==================== TEST COBJECT_DATA CONSTANTS ====================
    // These values are defined in CObjectData.c
    
    // Verify const values are properly compiled
    TEST_2(value1, true)  // cbool(value1, true)
    TEST_2(value2, '9')   // cchar(value2, '9')
    TEST_2(value3, 8880)  // cshort(value3, 8880)
    TEST_2(value4, 199983)  // cint(value4, 199983)
    TEST_2(value5, 10009389)  // clong(value5, 10009389)
    
    TEST_2(value6, 199)  // cuint8(value6, 199)
    TEST_2(value7, 8889)  // cuint16(value7, 8889)
    TEST_2(value8, 98883)  // cuint32(value8, 98883)
    TEST_2(value9, 998938)  // cuint64(value9, 998938)
    
    TEST_2(value10, -10)  // cint8(value10, -10)
    TEST_2(value11, -1183)  // cint16(value11, -1183)
    TEST_2(value12, -77787)  // cint32(value12, -77787)
    TEST_2(value13, -188388)  // cint64(value13, -188388)
    
    // Float/Double comparison with tolerance
    float diff14 = value14 > 2.88 ? value14 - 2.88 : 2.88 - value14;
    TEST_2(diff14 < 0.01f, true)  // value14 ≈ 2.89
    
    // Test cstring and arrays
    TEST_2(length(value17), 3)  // cstring(value17, "ken")
    TEST_2(equal(value17, "ken"), true)
    
    // Array tests
    TEST_2(value18[0], 19)
    TEST_2(value18[1], 38)
    TEST_2(value18[2], 183)
    TEST_2(value18[3], 198)
    
    // Test cdynamic macro
    TEST_2(value20, 880)  // cdynamic(value20, 880)
    
    // ==================== COMPREHENSIVE STRING OPERATIONS ====================
    
    // Multiple operations in sequence
    cstr(s_ops, 200) = "Start";
    TEST_2(length(s_ops), 5)
    concatenate(s_ops, "-Middle");
    TEST_2(length(s_ops), 12)
    concatenate(s_ops, "-End");
    TEST_2(length(s_ops), 16)
    TEST_2(equal(s_ops, "Start-Middle-End"), true)
    
    TEST_2(exist(s_ops, '-'), true)
    TEST_2(count(s_ops, '-'), 2)  // Two dashes
    TEST_2(sub_exist(s_ops, "Middle"), true)
    TEST_2(sub_exist(s_ops, "Start-Middle"), true)

EXIT_TEST(true)