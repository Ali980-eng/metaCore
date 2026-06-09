#include "cgen/micros.h"
#include "cgen/error.h"

MAIN_TEST(error);

    // Test 1: errInit() - Initialize error with default values
    cerror err1 = errInit();
    TEST_2(err1.name == NULL, true); // name should be NULL
    TEST_2(err1.description == NULL, true); // description should be NULL
    TEST_2(err1.file == NULL, true); // file should be NULL
    TEST_2(err1.time == NULL, true); // time should be NULL
    TEST_2(err1.line, 0); // line should be 0
    
    // Test 2: errIndexing() - Create wrong indexing error
    cerror err_index = errIndexing("Array out of bounds");
    TEST_2(err_index.name != NULL, true); // name should not be NULL
    TEST_2(strcmp(err_index.name, "Wrong Indexing"), 0); // name should be "Wrong Indexing"
    TEST_2(err_index.description != NULL, true); // description should not be NULL
    TEST_2(strcmp(err_index.description, "Array out of bounds"), 0); // verify description
    TEST_2(err_index.file != NULL, true); // file should be set
    TEST_2(err_index.time != NULL, true); // time should be set
    ASSERT_TEST(err_index.line > 0); // line should be set (> 0)
    
    // Test 3: errDeclaration() - Create wrong declaration error
    cerror err_decl = errDeclaration("Invalid variable type");
    TEST_2(err_decl.name != NULL, true); // name should not be NULL
    TEST_2(strcmp(err_decl.name, "Wrong declaration"), 0); // verify name
    TEST_2(err_decl.description != NULL, true); // description should not be NULL
    TEST_2(strcmp(err_decl.description, "Invalid variable type"), 0); // verify description
    
    // Test 4: errConstruction() - Create wrong construction error
    cerror err_cons = errConstruction("Struct member missing");
    TEST_2(err_cons.name != NULL, true); // name should not be NULL
    TEST_2(strcmp(err_cons.name, "Wrong Construction"), 0); // verify name
    TEST_2(err_cons.description != NULL, true); // description should not be NULL
    
    // Test 5: errBadInput() - Create bad input error
    cerror err_input = errBadInput("Invalid parameter value");
    TEST_2(err_input.name != NULL, true); // name should not be NULL
    TEST_2(strcmp(err_input.name, "Bad Input"), 0); // verify name
    TEST_2(err_input.description != NULL, true); // description should not be NULL
    
    // Test 6: errUndefinedBehavior() - Create undefined behavior error
    cerror err_undef = errUndefinedBehavior("NULL pointer dereference");
    TEST_2(err_undef.name != NULL, true); // name should not be NULL
    TEST_2(strcmp(err_undef.name, "Undefined Behavior"), 0); // verify name
    TEST_2(err_undef.description != NULL, true); // description should not be NULL
    
    // Test 7: errInvalidArgument() - Create invalid argument error
    cerror err_arg = errInvalidArgument("Argument count mismatch");
    TEST_2(err_arg.name != NULL, true); // name should not be NULL
    TEST_2(strcmp(err_arg.name, "Invalid Argument"), 0); // verify name
    TEST_2(err_arg.description != NULL, true); // description should not be NULL
    
    // Test 8: Multiple errors with different descriptions
    cerror err_multi1 = errIndexing("First error");
    cerror err_multi2 = errIndexing("Second error");
    TEST_2(strcmp(err_multi1.description, "First error"), 0);   // verify first
    TEST_2(strcmp(err_multi2.description, "Second error"), 0);  // verify second
    TEST_2(strcmp(err_multi1.name, err_multi2.name), 0);         // both have same name
    
    // Test 9: Error with empty string description
    cerror err_empty = errBadInput("");
    TEST_2(err_empty.name != NULL, true);             // name should not be NULL
    TEST_2(err_empty.description != NULL, true);      // description initialized (empty string)
    TEST_2(strlen(err_empty.description), 0);         // should be empty
    
    // Test 10: All error creators preserve name correctly
    cerror e1 = errIndexing("test");
    cerror e2 = errDeclaration("test");
    cerror e3 = errConstruction("test");
    cerror e4 = errBadInput("test");
    cerror e5 = errUndefinedBehavior("test");
    cerror e6 = errInvalidArgument("test");
    ASSERT_TEST(e1.name != NULL && strlen(e1.name) > 0); // all names set
    ASSERT_TEST(e2.name != NULL && strlen(e2.name) > 0);
    ASSERT_TEST(e3.name != NULL && strlen(e3.name) > 0);
    ASSERT_TEST(e4.name != NULL && strlen(e4.name) > 0);
    ASSERT_TEST(e5.name != NULL && strlen(e5.name) > 0);
    ASSERT_TEST(e6.name != NULL && strlen(e6.name) > 0);

EXIT_TEST(true)