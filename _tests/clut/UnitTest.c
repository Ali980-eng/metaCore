#include "clite/micros.h"
#include "clite/UnitTest.h"

/**
 * @file UnitTest.c
 * @brief Comprehensive test suite for UnitTest library functionality
 * @details Tests CTEST object creation, result tracking, and various test functions
 *          for multiple data types including boolean, char, short, int, size_t, long,
 *          float, double, and string testing.
 */

MAIN_TEST(CUTest)
    
    // ==================== CTEST OBJECT CREATION AND MANAGEMENT ====================
    
    // Test creating CTEST objects with boolean values
    CTEST test_bool_1 = creatNew(test_bool_1, "Boolean Test 1", "Testing true value", true);
    TEST_2(test_bool_1.name != NULL, true)
    TEST_2(test_bool_1.result, true)
    TEST_2(strlen(test_bool_1.name) > 0, true)
    
    CTEST test_bool_2 = creatNew(test_bool_2, "Boolean Test 2", "Testing false value", false);
    TEST_2(test_bool_2.result, false)
    TEST_2(get_result(test_bool_2), false)
    
    // Test creating CTEST with NULL name and description
    CTEST test_null = creatNew(test_null, NULL, NULL, true);
    TEST_2(test_null.name != NULL, true)
    TEST_2(test_null.description != NULL, true)
    TEST_2(test_null.result, true)
    
    // Test CTEST counter incrementation
    CTEST test_counter_1 = creatNew(test_counter_1, "Counter Test 1", "", true);
    CTEST test_counter_2 = creatNew(test_counter_2, "Counter Test 2", "", true);
    TEST_2(test_counter_2.num > test_counter_1.num, true)
    
    // ==================== BASIC TEST FUNCTIONS - BOOLEAN TYPE ====================
    
    // Test basic_test_bool without details
    bool bool_result_1 = basic_test_bool(true, true, false, 20, '-');
    TEST_2(bool_result_1, true)
    
    bool bool_result_2 = basic_test_bool(false, false, false, 20, '-');
    TEST_2(bool_result_2, true)
    
    bool bool_result_3 = basic_test_bool(true, false, false, 20, '-');
    TEST_2(bool_result_3, false)
    
    // ==================== BASIC TEST FUNCTIONS - CHAR TYPE ====================
    
    // Test basic_test_char
    bool char_result_1 = basic_test_char('A', 'A', false, 20, '-');
    TEST_2(char_result_1, true)
    
    bool char_result_2 = basic_test_char('B', 'A', false, 20, '-');
    TEST_2(char_result_2, false)
    
    bool char_result_3 = basic_test_char('\n', '\n', false, 20, '-');
    TEST_2(char_result_3, true)
    
    bool char_result_4 = basic_test_char('\t', '\t', false, 20, '-');
    TEST_2(char_result_4, true)
    
    // ==================== BASIC TEST FUNCTIONS - SHORT TYPE ====================
    
    // Test basic_test_short
    bool short_result_1 = basic_test_short(100, 100, false, 20, '-');
    TEST_2(short_result_1, true)
    
    bool short_result_2 = basic_test_short(-500, -500, false, 20, '-');
    TEST_2(short_result_2, true)
    
    bool short_result_3 = basic_test_short(32767, 32767, false, 20, '-');
    TEST_2(short_result_3, true)
    
    bool short_result_4 = basic_test_short(-32768, -32768, false, 20, '-');
    TEST_2(short_result_4, true)
    
    bool short_result_5 = basic_test_short(100, 200, false, 20, '-');
    TEST_2(short_result_5, false)
    
    // ==================== BASIC TEST FUNCTIONS - INT TYPE ====================
    
    // Test basic_test_int
    bool int_result_1 = basic_test_int(42, 42, false, 20, '-');
    TEST_2(int_result_1, true)
    
    bool int_result_2 = basic_test_int(-1000, -1000, false, 20, '-');
    TEST_2(int_result_2, true)
    
    bool int_result_3 = basic_test_int(0, 0, false, 20, '-');
    TEST_2(int_result_3, true)
    
    bool int_result_4 = basic_test_int(2147483647, 2147483647, false, 20, '-');
    TEST_2(int_result_4, true)
    
    bool int_result_5 = basic_test_int(100, 200, false, 20, '-');
    TEST_2(int_result_5, false)
    
    // ==================== BASIC TEST FUNCTIONS - SIZE_T TYPE ====================
    
    // Test basic_test_size
    bool size_result_1 = basic_test_size(0, 0, false, 20, '-');
    TEST_2(size_result_1, true)
    
    bool size_result_2 = basic_test_size(1024, 1024, false, 20, '-');
    TEST_2(size_result_2, true)
    
    bool size_result_3 = basic_test_size(999999, 999999, false, 20, '-');
    TEST_2(size_result_3, true)
    
    bool size_result_4 = basic_test_size(100, 200, false, 20, '-');
    TEST_2(size_result_4, false)
    
    // ==================== BASIC TEST FUNCTIONS - LONG TYPE ====================
    
    // Test basic_test_long
    bool long_result_1 = basic_test_long(100000L, 100000L, false, 20, '-');
    TEST_2(long_result_1, true)
    
    bool long_result_2 = basic_test_long(-999999L, -999999L, false, 20, '-');
    TEST_2(long_result_2, true)
    
    bool long_result_3 = basic_test_long(0L, 0L, false, 20, '-');
    TEST_2(long_result_3, true)
    
    bool long_result_4 = basic_test_long(100000L, 200000L, false, 20, '-');
    TEST_2(long_result_4, false)
    
    // ==================== BASIC TEST FUNCTIONS - FLOAT TYPE ====================
    
    // Test basic_test_float with exact values
    bool float_result_1 = basic_test_float(3.14f, 3.14f, false, 20, '-', 0.01f);
    TEST_2(float_result_1, true)
    
    bool float_result_2 = basic_test_float(2.5f, 2.5f, false, 20, '-', 0.01f);
    TEST_2(float_result_2, true)
    
    bool float_result_3 = basic_test_float(0.0f, 0.0f, false, 20, '-', 0.01f);
    TEST_2(float_result_3, true)
    
    // Test float with tolerance
    bool float_result_4 = basic_test_float(10.01f, 10.0f, false, 20, '-', 0.5f);
    TEST_2(float_result_4, true)
    
    bool float_result_5 = basic_test_float(10.1f, 10.0f, false, 20, '-', 0.5f);
    TEST_2(float_result_5, false)
    
    // Test float with high resolution warning
    bool float_result_6 = basic_test_float(1.0f, 1.0f, false, 20, '-', 10.0f);
    TEST_2(float_result_6, true)
    
    // ==================== BASIC TEST FUNCTIONS - DOUBLE TYPE ====================
    
    // Test basic_test_double with exact values
    bool double_result_1 = basic_test_double(3.14159, 3.14159, false, 20, '-', 0.01);
    TEST_2(double_result_1, true)
    
    bool double_result_2 = basic_test_double(2.71828, 2.71828, false, 20, '-', 0.01);
    TEST_2(double_result_2, true)
    
    bool double_result_3 = basic_test_double(0.0, 0.0, false, 20, '-', 0.01);
    TEST_2(double_result_3, true)
    
    // Test double with tolerance
    bool double_result_4 = basic_test_double(100.05, 100.0, false, 20, '-', 0.5);
    TEST_2(double_result_4, true)
    
    bool double_result_5 = basic_test_double(100.1, 100.0, false, 20, '-', 0.5);
    TEST_2(double_result_5, false)
    
    // Test double with high resolution warning
    bool double_result_6 = basic_test_double(1.0, 1.0, false, 20, '-', 10.0);
    TEST_2(double_result_6, true)
    
    // ==================== STRING TEST FUNCTION ====================
    
    // Test string_test with identical strings
    bool string_result_1 = string_test("Hello", "Hello", false, 20, '-');
    TEST_2(string_result_1, true)
    
    bool string_result_2 = string_test("", "", false, 20, '-');
    TEST_2(string_result_2, true)
    
    bool string_result_3 = string_test("Test123", "Test123", false, 20, '-');
    TEST_2(string_result_3, true)
    
    // Test string_test with different strings
    bool string_result_4 = string_test("Hello", "World", false, 20, '-');
    TEST_2(string_result_4, false)
    
    // Test string_test with different lengths
    bool string_result_5 = string_test("Hi", "Hello", false, 20, '-');
    TEST_2(string_result_5, false)
    
    bool string_result_6 = string_test("A", "B", false, 20, '-');
    TEST_2(string_result_6, false)
    
    // ==================== CTEST CREATION FUNCTIONS - TYPED VARIANTS ====================
    
    // Test ctest_bool
    CTEST ctest_bool_1 = ctest_bool(true, true, "Bool Test Pass", "Comparing true values");
    TEST_2(ctest_bool_1.result, true)
    TEST_2(strlen(ctest_bool_1.name) > 0, true)
    
    CTEST ctest_bool_2 = ctest_bool(false, true, "Bool Test Fail", "Comparing different bool values");
    TEST_2(ctest_bool_2.result, false)
    
    // Test ctest_char
    CTEST ctest_char_1 = ctest_char('X', 'X', "Char Test Pass", "Comparing identical chars");
    TEST_2(ctest_char_1.result, true)
    
    CTEST ctest_char_2 = ctest_char('A', 'B', "Char Test Fail", "Comparing different chars");
    TEST_2(ctest_char_2.result, false)
    
    // Test ctest_short
    CTEST ctest_short_1 = ctest_short(1000, 1000, "Short Test Pass", "Comparing identical shorts");
    TEST_2(ctest_short_1.result, true)
    
    CTEST ctest_short_2 = ctest_short(500, 1000, "Short Test Fail", "Comparing different shorts");
    TEST_2(ctest_short_2.result, false)
    
    // Test ctest_int
    CTEST ctest_int_1 = ctest_int(42, 42, "Int Test Pass", "Comparing identical integers");
    TEST_2(ctest_int_1.result, true)
    
    CTEST ctest_int_2 = ctest_int(10, 20, "Int Test Fail", "Comparing different integers");
    TEST_2(ctest_int_2.result, false)
    
    // Test ctest_size
    CTEST ctest_size_1 = ctest_size(512, 512, "Size Test Pass", "Comparing identical size_t values");
    TEST_2(ctest_size_1.result, true)
    
    CTEST ctest_size_2 = ctest_size(100, 200, "Size Test Fail", "Comparing different size_t values");
    TEST_2(ctest_size_2.result, false)
    
    // Test ctest_long
    CTEST ctest_long_1 = ctest_long(999999L, 999999L, "Long Test Pass", "Comparing identical long values");
    TEST_2(ctest_long_1.result, true)
    
    CTEST ctest_long_2 = ctest_long(100L, 200L, "Long Test Fail", "Comparing different long values");
    TEST_2(ctest_long_2.result, false)
    
    // Test ctest_float
    CTEST ctest_float_1 = ctest_float(3.14f, 3.14f, 0.01f, "Float Test Pass", "Comparing identical floats");
    TEST_2(ctest_float_1.result, true)
    
    CTEST ctest_float_2 = ctest_float(1.5f, 1.6f, 0.5f, "Float Test Pass Tolerance", "Comparing floats within tolerance");
    TEST_2(ctest_float_2.result, true)
    
    CTEST ctest_float_3 = ctest_float(1.0f, 2.0f, 0.01f, "Float Test Fail", "Comparing very different floats");
    TEST_2(ctest_float_3.result, false)
    
    // Test ctest_double
    CTEST ctest_double_1 = ctest_double(3.14159, 3.14159, 0.01, "Double Test Pass", "Comparing identical doubles");
    TEST_2(ctest_double_1.result, true)
    
    CTEST ctest_double_2 = ctest_double(2.0, 2.01, 0.5, "Double Test Pass Tolerance", "Comparing doubles within tolerance");
    TEST_2(ctest_double_2.result, true)
    
    CTEST ctest_double_3 = ctest_double(1.0, 5.0, 0.01, "Double Test Fail", "Comparing very different doubles");
    TEST_2(ctest_double_3.result, false)
    
    // Test string_ctest
    CTEST string_ctest_1 = string_ctest("MetaCore", "MetaCore", "String Test Pass", "Comparing identical strings");
    TEST_2(string_ctest_1.result, true)
    
    CTEST string_ctest_2 = string_ctest("Hello", "World", "String Test Fail", "Comparing different strings");
    TEST_2(string_ctest_2.result, false)
    
    CTEST string_ctest_3 = string_ctest("Test", "Testing", "String Test Length Fail", "Comparing strings with different lengths");
    TEST_2(string_ctest_3.result, false)
    
    // ==================== TEST STREAM STRUCT TESTS ====================
    
    // Test test_stream initialization
    test_stream ts = {false, 20, '-', 0, 0, 0};
    TEST_2(ts.details, false)
    TEST_2(ts.seplen, 20)
    TEST_2(ts.sepch, '-')
    TEST_2(ts.success_tests, 0)
    TEST_2(ts.failed_tests, 0)
    TEST_2(ts.total_tests, 0)
    
    // Test test_stream with details enabled
    test_stream ts_detail = {true, 30, '=', 0, 0, 0};
    TEST_2(ts_detail.details, true)
    TEST_2(ts_detail.seplen, 30)
    TEST_2(ts_detail.sepch, '=')
    
    // ==================== GET_RESULT FUNCTION TESTS ====================
    
    CTEST test_result_1 = creatNew(test_result_1, "Result Test 1", "Testing get_result", true);
    TEST_2(get_result(test_result_1), true)
    
    CTEST test_result_2 = creatNew(test_result_2, "Result Test 2", "Testing get_result", false);
    TEST_2(get_result(test_result_2), false)
    
    // ==================== PRINT TEST FUNCTION (Functional Test) ====================
    
    // Note: printTest writes to console but we verify it doesn't crash
    CTEST test_print = creatNew(test_print, "Print Test", "Testing printTest function", true);
    printTest(test_print);  // Should print without crashing
    TEST_0(test_print.name != NULL)
    
    // ==================== EDGE CASES AND SPECIAL VALUES ====================
    
    // Test with special floating point values
    bool float_edge_1 = basic_test_float(-3.14f, -3.14f, false, 20, '-', 0.01f);
    TEST_2(float_edge_1, true)
    
    bool double_edge_1 = basic_test_double(-3.14159, -3.14159, false, 20, '-', 0.01);
    TEST_2(double_edge_1, true)
    
    // Test with boundary integer values
    bool int_edge_1 = basic_test_int(-2147483648, -2147483648, false, 20, '-');
    TEST_2(int_edge_1, true)
    
    // Test character edge cases
    bool char_edge_1 = basic_test_char(0, 0, false, 20, '-');
    TEST_2(char_edge_1, true)
    
    bool char_edge_2 = basic_test_char(255, 255, false, 20, '-');
    TEST_2(char_edge_2, true)
    
    // Test string with special characters
    bool string_edge_1 = string_test("\n\t", "\n\t", false, 20, '-');
    TEST_2(string_edge_1, true)
    
    // Test CTEST with empty strings
    CTEST test_empty = creatNew(test_empty, "", "", true);
    TEST_2(test_empty.name != NULL, true)
    TEST_2(test_empty.description != NULL, true)

EXIT_TEST(true)