#include "clite/IOUtilitys.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

int main() {
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║        IOUtilitys Library - Practical Examples         ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    NewLines(1);

    // ============================================================
    // Example 1: Basic Output Functions
    // ============================================================
    print_category("📖 EXAMPLE 1: Basic Output Functions");
    NewLines(1);
    
    printf("Single newline with PNL():\n");
    printf("Line 1"); PNL();
    printf("Line 2"); PNL();
    
    printf("\nSingle tab with PTab():\n");
    printf("Name:"); PTab(); printf("John\n");
    printf("Age:"); PTab(); printf("30\n");
    NewLines(1);

    // ============================================================
    // Example 2: Multiple Newlines and Tabs
    // ============================================================
    print_category("📖 EXAMPLE 2: Multiple Newlines and Tabs");
    NewLines(1);
    
    printf("Text with multiple newlines (3 lines):\n");
    printf("This is line 1");
    NewLines(3);
    printf("This is line 5");
    NewLines(2);
    
    printf("Indentation with multiple tabs:\n");
    printf("No indent: Start\n");
    Tabs(2); printf("2 tabs indent\n");
    Tabs(4); printf("4 tabs indent\n");
    Tabs(6); printf("6 tabs indent\n");
    NewLines(1);

    // ============================================================
    // Example 3: Separator Characters
    // ============================================================
    print_category("📖 EXAMPLE 3: Separator Functions");
    NewLines(1);
    
    printf("Different separator characters:\n\n");
    
    printf("Separator with dashes (-):\n");
    separator(40, '-');
    
    printf("Separator with equals (=):\n");
    separator(40, '=');
    
    printf("Separator with asterisks (*):\n");
    separator(40, '*');
    
    printf("Separator with hashes (#):\n");
    separator(40, '#');
    
    printf("Separator with tildes (~):\n");
    separator(40, '~');
    NewLines(1);

    // ============================================================
    // Example 4: Multiple Separators
    // ============================================================
    printCategory("📖 EXAMPLE 4: Multiple Separators", 2, 45, '=');
    NewLines(1);
    
    printf("Multiple separators in a row:\n");
    separators(3, 20, '-');
    printf("\nThis creates visual breaks\n\n");
    separators(2, 30, '*');
    NewLines(1);

    // ============================================================
    // Example 5: Print Character String
    // ============================================================
    print_category("📖 EXAMPLE 5: Print Character from String");
    NewLines(1);
    
    printf("Print all characters from 'Hello World':\n");
    print_char_str("Hello World", 0);
    
    printf("Print characters starting from index 6:\n");
    print_char_str("Hello World", 6);
    
    printf("Print characters starting from index 12 (out of bounds, defaults to 0):\n");
    print_char_str("Hello World", 12);
    NewLines(1);

    // ============================================================
    // Example 6: Test Message Function
    // ============================================================
    print_category("📖 EXAMPLE 6: Test Message Function");
    NewLines(1);
    
    int value = 42;
    bool test1 = (value == 42);
    bool test2 = (value == 50);
    
    printf("Test 1 (42 == 42): %s\n", test_msg(test1));
    printf("Test 2 (42 == 50): %s\n", test_msg(test2));
    NewLines(1);

    // ============================================================
    // Example 7: Testing Boolean Values
    // ============================================================
    printCategory("📖 EXAMPLE 7: Testing Boolean Values", 1, 50, '-');
    NewLines(1);
    
    bool actual_bool = true;
    bool expected_bool = true;
    printf("Boolean Test (true == true):\n");
    print_test_bool(actual_bool, expected_bool, 40, '=');
    
    printf("\nBoolean Test (true == false):\n");
    print_test_bool(true, false, 40, '-');
    NewLines(1);

    // ============================================================
    // Example 8: Testing Character Values
    // ============================================================
    print_category("📖 EXAMPLE 8: Testing Character Values");
    NewLines(1);
    
    printf("Character Test ('A' == 'A'):\n");
    print_test_char('A', 'A', 40, '*');
    
    printf("Character Test ('A' == 'B'):\n");
    print_test_char('A', 'B', 40, '#');
    NewLines(1);

    // ============================================================
    // Example 9: Testing Short Integer
    // ============================================================
    print_category("📖 EXAMPLE 9: Testing Short Integer");
    NewLines(1);
    
    printf("Short Integer Test (100 == 100):\n");
    print_test_short(100, 100, 40, '-');
    
    printf("Short Integer Test (50 == 75):\n");
    print_test_short(50, 75, 40, '*');
    NewLines(1);

    // ============================================================
    // Example 10: Testing Regular Integer
    // ============================================================
    print_category("📖 EXAMPLE 10: Testing Integer Values");
    NewLines(1);
    
    printf("Integer Test (12345 == 12345):\n");
    print_test_int(12345, 12345, 40, '=');
    
    printf("Integer Test (1000 == 2000):\n");
    print_test_int(1000, 2000, 40, '-');
    NewLines(1);

    // ============================================================
    // Example 11: Testing Long Integer
    // ============================================================
    print_category("📖 EXAMPLE 11: Testing Long Integer");
    NewLines(1);
    
    printf("Long Integer Test (999999999 == 999999999):\n");
    print_test_long(999999999, 999999999, 45, '=');
    
    printf("Long Integer Test (111111111 == 222222222):\n");
    print_test_long(111111111, 222222222, 45, '-');
    NewLines(1);

    // ============================================================
    // Example 12: Testing Size_t Values
    // ============================================================
    print_category("📖 EXAMPLE 12: Testing Size_t Values");
    NewLines(1);
    
    size_t size1 = 256;
    size_t size2 = 256;
    printf("Size_t Test (256 == 256):\n");
    print_test_size(size1, size2, 40, '*');
    
    printf("Size_t Test (100 == 200):\n");
    print_test_size(100, 200, 40, '#');
    NewLines(1);

    // ============================================================
    // Example 13: Testing Float Values
    // ============================================================
    print_category("📖 EXAMPLE 13: Testing Float Values");
    NewLines(1);
    
    printf("Float Test (3.14 ≈ 3.14, tolerance 1%%):\n");
    print_test_float(3.14f, 3.14f, 40, '=', 1.0f);
    
    printf("Float Test (3.10 ≈ 3.14, tolerance 2%%):\n");
    print_test_float(3.10f, 3.14f, 40, '-', 2.0f);
    
    printf("Float Test (3.0 ≈ 3.14, tolerance 0.1%%):\n");
    print_test_float(3.0f, 3.14f, 40, '*', 0.1f);
    NewLines(1);

    // ============================================================
    // Example 14: Testing Double Values
    // ============================================================
    print_category("📖 EXAMPLE 14: Testing Double Values");
    NewLines(1);
    
    printf("Double Test (2.71828 ≈ 2.71828, tolerance 1%%):\n");
    print_test_double(2.71828, 2.71828, 40, '=', 1.0);
    
    printf("Double Test (2.71 ≈ 2.71828, tolerance 0.5%%):\n");
    print_test_double(2.71, 2.71828, 40, '-', 0.5);
    
    printf("Double Test (2.5 ≈ 2.71828, tolerance 5%% - WARNING):\n");
    print_test_double(2.5, 2.71828, 40, '*', 5.0);
    NewLines(1);

    // ============================================================
    // Example 15: Testing C-Style Strings
    // ============================================================
    print_category("📖 EXAMPLE 15: Testing C-Style Strings");
    NewLines(1);
    
    const char *str1 = "Hello";
    const char *str2 = "Hello";
    const char *str3 = "World";
    
    printf("String Test ('Hello' == 'Hello'):\n");
    print_test_string(str1, str2, 40, '=', strcmp(str1, str2) == 0);
    
    printf("String Test ('Hello' == 'World'):\n");
    print_test_string(str1, str3, 40, '-', strcmp(str1, str3) == 0);
    NewLines(1);

    // ============================================================
    // Example 16: Practical Use Case - Unit Test Output
    // ============================================================
    printCategory("📖 EXAMPLE 16: Practical Use - Unit Test Output", 1, 55, '=');
    NewLines(1);
    
    printf("Module: Calculator Tests\n");
    separator(50, '-');
    NewLines(1);
    
    // Test 1: Addition
    int add_result = 5 + 3;
    printf("Test 1: Addition (5 + 3 = 8)\n");
    print_test_int(add_result, 8, 45, '*');
    
    // Test 2: Division with precision
    float div_result = 10.0f / 3.0f;
    printf("Test 2: Division (10.0 / 3.0 ≈ 3.333)\n");
    print_test_float(div_result, 3.333f, 45, '-', 0.1f);
    NewLines(1);

    // ============================================================
    // Example 17: Practical Use Case - Data Validation Report
    // ============================================================
    print_category("📖 EXAMPLE 17: Practical Use - Data Validation");
    NewLines(1);
    
    Tabs(2); printf("USER DATA VALIDATION REPORT\n");
    separator(50, '=');
    
    printf("\nUser ID: ");
    print_test_int(12345, 12345, 35, '-');
    
    printf("User Age: ");
    print_test_short(25, 25, 35, '*');
    
    printf("Username: ");
    print_test_string("john_doe", "john_doe", 35, '=', true);
    
    printf("Email Match: ");
    print_test_bool(true, true, 35, '#');
    NewLines(1);

    // ============================================================
    // Example 18: Practical Use Case - Performance Test Results
    // ============================================================
    print_category("📖 EXAMPLE 18: Practical Use - Performance Test");
    NewLines(1);
    
    printf("Memory Usage Test:\n");
    print_test_size(1024000, 1024000, 40, '=');
    
    printf("\nExecution Time Test:\n");
    print_test_double(0.00523, 0.00527, 40, '-', 1.0);
    
    printf("\nCPU Efficiency Test:\n");
    print_test_float(98.5f, 99.0f, 40, '*', 0.5f);
    NewLines(1);

    // ============================================================
    // Example 19: Formatting with Custom Categories
    // ============================================================
    printCategory("📖 EXAMPLE 19: Custom Category Headers", 2, 50, '*');
    NewLines(1);
    
    printCategory("Network Tests", 3, 40, '=');
    NewLines(1);
    printf("Checking connectivity...\n");
    print_test_bool(true, true, 35, '-');
    
    NewLines(1);
    printCategory("Database Tests", 3, 40, '=');
    NewLines(1);
    printf("Connection pool size: 50\n");
    print_test_size(50, 50, 35, '*');
    NewLines(1);

    // ============================================================
    // Summary
    // ============================================================
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║  IOUtilitys Library provides comprehensive I/O tools:  ║\n");
    printf("║                                                        ║\n");
    printf("║  • PNL() / NewLines()   - Manage newlines             ║\n");
    printf("║  • PTab() / Tabs()      - Manage indentation          ║\n");
    printf("║  • separator(s)         - Visual separators           ║\n");
    printf("║  • print_category()     - Format section headers      ║\n");
    printf("║  • print_test_*()       - Display test results        ║\n");
    printf("║  • test_msg()           - Success/fail messages       ║\n");
    printf("║  • print_char_str()     - Print char-by-char output   ║\n");
    printf("║                                                        ║\n");
    printf("║  Supports: bool, char, short, int, long, size_t,      ║\n");
    printf("║            float, double, strings (C-style)           ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");

    return 0;
}