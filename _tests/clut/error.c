#include "clite/micros.h"
#include "clite/error.h"

MAIN_TEST(error)

    // Test 1: cerror_init() - Initialize error with default values
    cerror err1 = cerror_init();
    TEST_2(err1.name == NULL, true)                  // name should be NULL
    TEST_2(err1.description == NULL, true)           // description should be NULL
    TEST_2(err1.file == NULL, true)                  // file should be NULL
    TEST_2(err1.time == NULL, true)                  // time should be NULL
    TEST_2(err1.line, 0)                             // line should be 0
    
    // Test 2: wrong_indexing() - Create wrong indexing error
    cerror err_index = wrong_indexing("Array out of bounds");
    TEST_2(err_index.name != NULL, true)             // name should not be NULL
    TEST_2(strcmp(err_index.name, "Wrong Indexing"), 0)  // name should be "Wrong Indexing"
    TEST_2(err_index.description != NULL, true)      // description should not be NULL
    TEST_2(strcmp(err_index.description, "Array out of bounds"), 0)  // verify description
    TEST_2(err_index.file != NULL, true)             // file should be set
    TEST_2(err_index.time != NULL, true)             // time should be set
    ASSERT_TEST(err_index.line > 0)                  // line should be set (> 0)
    
    // Test 3: wrong_declaration() - Create wrong declaration error
    cerror err_decl = wrong_declaration("Invalid variable type");
    TEST_2(err_decl.name != NULL, true)              // name should not be NULL
    TEST_2(strcmp(err_decl.name, "Wrong declaration"), 0)  // verify name
    TEST_2(err_decl.description != NULL, true)       // description should not be NULL
    TEST_2(strcmp(err_decl.description, "Invalid variable type"), 0)  // verify description
    
    // Test 4: wrong_construction() - Create wrong construction error
    cerror err_cons = wrong_construction("Struct member missing");
    TEST_2(err_cons.name != NULL, true)              // name should not be NULL
    TEST_2(strcmp(err_cons.name, "Wrong Construction"), 0)  // verify name
    TEST_2(err_cons.description != NULL, true)       // description should not be NULL
    
    // Test 5: bad_input() - Create bad input error
    cerror err_input = bad_input("Invalid parameter value");
    TEST_2(err_input.name != NULL, true)             // name should not be NULL
    TEST_2(strcmp(err_input.name, "Bad Input"), 0)   // verify name
    TEST_2(err_input.description != NULL, true)      // description should not be NULL
    
    // Test 6: undefined_behavior() - Create undefined behavior error
    cerror err_undef = undefined_behavior("NULL pointer dereference");
    TEST_2(err_undef.name != NULL, true)             // name should not be NULL
    TEST_2(strcmp(err_undef.name, "Undefined Behavior"), 0)  // verify name
    TEST_2(err_undef.description != NULL, true)      // description should not be NULL
    
    // Test 7: invalid_argument() - Create invalid argument error
    cerror err_arg = invalid_argument("Argument count mismatch");
    TEST_2(err_arg.name != NULL, true)               // name should not be NULL
    TEST_2(strcmp(err_arg.name, "Invalid Argument"), 0)  // verify name
    TEST_2(err_arg.description != NULL, true)        // description should not be NULL
    
    // Test 8: Multiple errors with different descriptions
    cerror err_multi1 = wrong_indexing("First error");
    cerror err_multi2 = wrong_indexing("Second error");
    TEST_2(strcmp(err_multi1.description, "First error"), 0)   // verify first
    TEST_2(strcmp(err_multi2.description, "Second error"), 0)  // verify second
    TEST_2(strcmp(err_multi1.name, err_multi2.name), 0)         // both have same name
    
    // Test 9: Error with empty string description
    cerror err_empty = bad_input("");
    TEST_2(err_empty.name != NULL, true)             // name should not be NULL
    TEST_2(err_empty.description != NULL, true)      // description initialized (empty string)
    TEST_2(strlen(err_empty.description), 0)         // should be empty
    
    // Test 10: All error creators preserve name correctly
    cerror e1 = wrong_indexing("test");
    cerror e2 = wrong_declaration("test");
    cerror e3 = wrong_construction("test");
    cerror e4 = bad_input("test");
    cerror e5 = undefined_behavior("test");
    cerror e6 = invalid_argument("test");
    ASSERT_TEST(e1.name != NULL && strlen(e1.name) > 0)   // all names set
    ASSERT_TEST(e2.name != NULL && strlen(e2.name) > 0)
    ASSERT_TEST(e3.name != NULL && strlen(e3.name) > 0)
    ASSERT_TEST(e4.name != NULL && strlen(e4.name) > 0)
    ASSERT_TEST(e5.name != NULL && strlen(e5.name) > 0)
    ASSERT_TEST(e6.name != NULL && strlen(e6.name) > 0)

EXIT_TEST(true)