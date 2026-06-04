#include "clite/UnitTest.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

int main() {
    printf("|========================================================|\n");
    printf("|         UnitTest Framework - Practical Examples        |\n");
    printf("|========================================================|\n\n");

    // ============================================================
    // Example 1: CTEST Structure - Create and Display Tests
    // ============================================================
    printf("EXAMPLE 1: CTEST Structure Basics\n");
    printf("-------------------------------------\n");
    
    CTEST test1;
    test1 = creatNew(test1, "Boolean Test", "Testing true == true", true);
    printTest(test1);
    
    CTEST test2;
    test2 = creatNew(test2, "Arithmetic Test", "Testing 5 + 3 == 8", 5 + 3 == 8);
    printTest(test2);

    // ============================================================
    // Example 2: Basic Test Functions - Boolean
    // ============================================================
    printf("EXAMPLE 2: Testing Boolean Values\n");
    printf("------------------------------------\n");
    
    bool actual_bool = true;
    bool expected_bool = true;
    
    bool result = basic_test_bool(actual_bool, expected_bool, true, 40, '=');
    printf("Result: %s\n\n", result ? "PASSED" : "FAILED");

    // ============================================================
    // Example 3: Basic Test Functions - Character
    // ============================================================
    printf("EXAMPLE 3: Testing Character Values\n");
    printf("--------------------------------------\n");
    
    char ch_actual = 'A';
    char ch_expected = 'A';
    
    bool ch_result = basic_test_char(ch_actual, ch_expected, true, 40, '-');
    printf("Result: %s\n\n", ch_result ? "PASSED" : "FAILED");

    // ============================================================
    // Example 4: Basic Test Functions - Integer
    // ============================================================
    printf("EXAMPLE 4: Testing Integer Values\n");
    printf("------------------------------------\n");
    
    int actual_int = 100;
    int expected_int = 100;
    
    bool int_result = basic_test_int(actual_int, expected_int, true, 40, '*');
    printf("Result: %s\n\n", int_result ? "PASSED" : "FAILED");

    // ============================================================
    // Example 5: Basic Test Functions - Float with Tolerance
    // ============================================================
    printf("EXAMPLE 5: Testing Float Values (with tolerance)\n");
    printf("----------------------------------------------------\n");
    
    float actual_float = 3.14f;
    float expected_float = 3.14f;
    
    bool float_result = basic_test_float(actual_float, expected_float, true, 40, '=', 0.1f);
    printf("Result: %s\n\n", float_result ? "PASSED" : "FAILED");

    // ============================================================
    // Example 6: Basic Test Functions - Double
    // ============================================================
    printf("EXAMPLE 6: Testing Double Values\n");
    printf("-----------------------------------\n");
    
    double actual_double = 2.71828;
    double expected_double = 2.71828;
    
    bool double_result = basic_test_double(actual_double, expected_double, true, 40, '-', 0.01);
    printf("Result: %s\n\n", double_result ? "PASSED" : "FAILED");

    // ============================================================
    // Example 7: String Testing
    // ============================================================
    printf("EXAMPLE 7: Testing C-Style Strings\n");
    printf("--------------------------------------\n");
    
    const char *str1 = "Hello";
    const char *str2 = "Hello";
    
    bool string_result = string_test(str1, str2, true, 40, '=');
    printf("Result: %s\n\n", string_result ? "PASSED" : "FAILED");

    // ============================================================
    // Example 8: CTEST Variants - ctest_int
    // ============================================================
    printf("EXAMPLE 8: Using ctest_int Function\n");
    printf("--------------------------------------\n");
    
    CTEST math_test = ctest_int(2 + 3, 5, "Addition", "Testing 2 + 3 == 5");
    printTest(math_test);
    printf("Result: %s\n\n", get_result(math_test) ? "PASSED" : "FAILED");

    // ============================================================
    // Example 9: CTEST Variants - ctest_bool
    // ============================================================
    printf("EXAMPLE 9: Using ctest_bool Function\n");
    printf("--------------------------------------\n");
    
    CTEST logic_test = ctest_bool(true && true, true, "Logic AND", "Testing true AND true == true");
    printTest(logic_test);

    // ============================================================
    // Example 10: CTEST Variants - ctest_float
    // ============================================================
    printf("EXAMPLE 10: Using ctest_float Function\n");
    printf("----------------------------------------\n");
    
    CTEST precision_test = ctest_float(3.14159f, 3.14159f, 0.1f, "Pi Value", "Testing PI precision");
    printTest(precision_test);

    // ============================================================
    // Example 11: CTEST Variants - string_ctest
    // ============================================================
    printf("EXAMPLE 11: Using string_ctest Function\n");
    printf("-----------------------------------------\n");
    
    CTEST str_ctest = string_ctest("MetaCore", "MetaCore", "String Equality", "Testing library name");
    printTest(str_ctest);

    // ============================================================
    // Example 12: test_stream Structure - Basic Usage
    // ============================================================
    printf("EXAMPLE 12: test_stream Structure\n");
    printf("--------------------------------------\n");
    
    test_stream ts;
    ts.details = true;
    ts.seplen = 40;
    ts.sepch = '*';
    ts.success_tests = 0;
    ts.failed_tests = 0;
    ts.total_tests = 0;
    
    printf("Created test_stream with settings:\n");
    printf("  Details: %s\n", ts.details ? "true" : "false");
    printf("  Separator: '%c' with length %u\n\n", ts.sepch, ts.seplen);

    // ============================================================
    // Example 13: Adding Multiple Tests to Stream
    // ============================================================
    printf("EXAMPLE 13: Batch Testing with test_stream\n");
    printf("----------------------------------------------\n\n");
    
    // Create a fresh test stream
    test_stream batch_tests;
    batch_tests.details = false;  // Disable detailed output for batch
    batch_tests.seplen = 35;
    batch_tests.sepch = '-';
    batch_tests.success_tests = 0;
    batch_tests.failed_tests = 0;
    batch_tests.total_tests = 0;
    
    // Add boolean tests
    batch_tests = addTestBool(batch_tests, true, true, false);
    batch_tests = addTestBool(batch_tests, false, false, false);
    batch_tests = addTestBool(batch_tests, true, false, false);
    
    // Add integer tests
    batch_tests = addTestInt(batch_tests, 5, 5, false);
    batch_tests = addTestInt(batch_tests, 10, 20, false);
    batch_tests = addTestInt(batch_tests, 42, 42, false);
    
    // Add float tests
    batch_tests = addTestFloat(batch_tests, 3.14f, 3.14f, false);
    batch_tests = addTestFloat(batch_tests, 2.71f, 2.72f, false);
    
    // Add double tests
    batch_tests = addTestDouble(batch_tests, 1.414, 1.414, false);
    batch_tests = addTestDouble(batch_tests, 1.732, 1.733, false);
    
    // Print summary
    print(batch_tests);
    NewLines(1);

    // ============================================================
    // Example 14: ASR and AFR Calculation
    // ============================================================
    printf("EXAMPLE 14: Success and Failure Rate Calculation\n");
    printf("--------------------------------------------------\n");
    
    test_stream rate_tests;
    rate_tests.success_tests = 7;
    rate_tests.failed_tests = 3;
    rate_tests.total_tests = 10;
    
    float success_rate = ASR(rate_tests);
    float failure_rate = AFR(rate_tests);
    
    printf("Test Statistics:\n");
    printf("  Passed: %zu\n", rate_tests.success_tests);
    printf("  Failed: %zu\n", rate_tests.failed_tests);
    printf("  Total: %zu\n", rate_tests.total_tests);
    printf("  Average Success Rate (ASR): %.2f%%\n", success_rate);
    printf("  Average Failure Rate (AFR): %.2f%%\n\n", failure_rate);

    // ============================================================
    // Example 15: Practical Use Case - Calculator Module Tests
    // ============================================================
    printf("EXAMPLE 15: Practical Use - Calculator Module\n");
    printf("----------------------------------------------\n\n");
    
    test_stream calc_tests;
    calc_tests.details = false;
    calc_tests.seplen = 40;
    calc_tests.sepch = '=';
    calc_tests.success_tests = 0;
    calc_tests.failed_tests = 0;
    calc_tests.total_tests = 0;
    
    printf("Running Calculator Tests:\n");
    
    // Test addition
    calc_tests = addTestInt(calc_tests, 5 + 3, 8, false);
    printf("✓ Addition: 5 + 3 = 8\n");
    
    // Test subtraction
    calc_tests = addTestInt(calc_tests, 10 - 4, 6, false);
    printf("✓ Subtraction: 10 - 4 = 6\n");
    
    // Test multiplication
    calc_tests = addTestInt(calc_tests, 7 * 6, 42, false);
    printf("✓ Multiplication: 7 * 6 = 42\n");
    
    // Test division
    calc_tests = addTestFloat(calc_tests, 15.0f / 3.0f, 5.0f, false);
    printf("✓ Division: 15.0 / 3.0 = 5.0\n");
    
    // Test power
    calc_tests = addTestFloat(calc_tests, powf(2.0f, 8.0f), 256.0f, false);
    printf("✓ Power: 2^8 = 256\n\n");
    
    print(calc_tests);
    NewLines(1);

    // ============================================================
    // Example 16: Practical Use Case - String Processing Tests
    // ============================================================
    printf("EXAMPLE 16: Practical Use - String Processing\n");
    printf("-----------------------------------------------\n\n");
    
    test_stream string_tests;
    string_tests.details = false;
    string_tests.seplen = 40;
    string_tests.sepch = '-';
    string_tests.success_tests = 0;
    string_tests.failed_tests = 0;
    string_tests.total_tests = 0;
    
    // Test string length
    const char *test_str = "Hello";
    string_tests = addTestSize(string_tests, strlen(test_str), 5, false);
    printf("✓ String Length: strlen('Hello') = 5\n");
    
    // Test string comparison
    bool strcmp_result = string_test("MetaCore", "MetaCore", false, 40, '-');
    string_tests = addTestBool(string_tests, strcmp_result, true, false);
    printf("✓ String Comparison: 'MetaCore' == 'MetaCore'\n");
    
    // Test character matching
    string_tests = addTestChar(string_tests, 'A', 'A', false);
    printf("✓ Character Match: 'A' == 'A'\n\n");
    
    print(string_tests);
    NewLines(1);

    // ============================================================
    // Example 17: Practical Use Case - Data Validation Tests
    // ============================================================
    printf("EXAMPLE 17: Practical Use - Data Validation\n");
    printf("----------------------------------------------\n\n");
    
    test_stream validation_tests;
    validation_tests.details = false;
    validation_tests.seplen = 40;
    validation_tests.sepch = '*';
    validation_tests.success_tests = 0;
    validation_tests.failed_tests = 0;
    validation_tests.total_tests = 0;
    
    // Validate user ID
    int user_id = 12345;
    validation_tests = addTestInt(validation_tests, user_id > 0 ? 1 : 0, 1, false);
    printf("✓ User ID validation: %d > 0\n", user_id);
    
    // Validate email format check (simplified)
    bool has_email = true;
    validation_tests = addTestBool(validation_tests, has_email, true, false);
    printf("✓ Email field present: %s\n", has_email ? "true" : "false");
    
    // Validate age
    int age = 25;
    validation_tests = addTestBool(validation_tests, age >= 18 && age <= 120, true, false);
    printf("✓ Age validation: 18 <= %d <= 120\n\n", age);
    
    print(validation_tests);
    NewLines(1);

    // ============================================================
    // Example 18: Test Statistics Summary
    // ============================================================
    printf("EXAMPLE 18: Complete Test Report\n");
    printf("----------------------------------\n\n");
    
    test_stream final_report;
    final_report.details = false;
    final_report.seplen = 45;
    final_report.sepch = '=';
    final_report.success_tests = 0;
    final_report.failed_tests = 0;
    final_report.total_tests = 0;
    
    printf("Consolidating all test results...\n\n");
    
    // Aggregate results
    final_report.success_tests = batch_tests.success_tests + calc_tests.success_tests + 
                                  string_tests.success_tests + validation_tests.success_tests;
    final_report.failed_tests = batch_tests.failed_tests + calc_tests.failed_tests + 
                                 string_tests.failed_tests + validation_tests.failed_tests;
    final_report.total_tests = batch_tests.total_tests + calc_tests.total_tests + 
                                string_tests.total_tests + validation_tests.total_tests;
    
    print(final_report);
    NewLines(1);

    // ============================================================
    // Summary
    // ============================================================
    printf("|========================================================|\n");
    printf("|  UnitTest Framework provides comprehensive testing:    |\n");
    printf("|                                                        |\n");
    printf("|  • CTEST - Test object structure                       |\n");
    printf("|  • basic_test_*() - Simple type testing                |\n");
    printf("|  • ctest_*() - Named test creation                     |\n");
    printf("|  • string_test() - String comparison                   |\n");
    printf("|  • test_stream - Batch test management                 |\n");
    printf("|  • addTest*() - Add tests to stream                    |\n");
    printf("|  • ASR/AFR - Success/failure rate calculation          |\n");
    printf("|  • print() - Summary report generation                 |\n");
    printf("|                                                        |\n");
    printf("|  Supports: bool, char, short, int, long, size_t,       |\n");
    printf("|            float, double, C-strings                    |\n");
    printf("|========================================================|\n");

    return 0;
}