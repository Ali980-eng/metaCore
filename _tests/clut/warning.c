#include "clite/micros.h"
#include "clite/warning.h"

MAIN_TEST(warning)

    // Reset counter for consistent testing
    cwarningCounter = 0;
    
    // Test 1: cwarning_init() - Initialize warning with default values
    cwarning w1 = cwarning_init();
    TEST_2(w1.name == NULL, true)                    // name should be NULL
    TEST_2(w1.description == NULL, true)             // description should be NULL
    TEST_2(w1.file == NULL, true)                    // file should be NULL
    TEST_2(w1.time == NULL, true)                    // time should be NULL
    TEST_2(w1.line, 0)                               // line should be 0
    TEST_2(w1.number, 0)                             // number should be 0 (first init)
    
    // Test 2: Counter increments after init
    size_t counter_before = cwarningCounter;
    cwarning w2 = cwarning_init();
    TEST_2(w2.number, counter_before)                // number should match counter
    TEST_2(cwarningCounter, counter_before + 1)      // counter should increment
    
    // Test 3: wrong_indexing() - Create wrong indexing warning
    size_t counter_start = cwarningCounter;
    cwarning w_index = wrong_indexing("Array boundary check");
    TEST_2(w_index.name != NULL, true)               // name should not be NULL
    TEST_2(strcmp(w_index.name, "Wrong Indexing"), 0)    // verify name
    TEST_2(w_index.description != NULL, true)        // description should not be NULL
    TEST_2(strcmp(w_index.description, "Array boundary check"), 0)  // verify description
    TEST_2(w_index.file != NULL, true)               // file should be set
    TEST_2(w_index.time != NULL, true)               // time should be set
    ASSERT_TEST(w_index.line > 0)                    // line should be set (> 0)
    TEST_2(w_index.number, counter_start)            // number should match counter
    TEST_2(cwarningCounter, counter_start + 1)       // counter should increment
    
    // Test 4: wrong_declaration() - Create wrong declaration warning
    counter_before = cwarningCounter;
    cwarning w_decl = wrong_declaration("Unused variable");
    TEST_2(w_decl.name != NULL, true)                // name should not be NULL
    TEST_2(strcmp(w_decl.name, "Wrong declaration"), 0)   // verify name
    TEST_2(w_decl.description != NULL, true)         // description should not be NULL
    TEST_2(strcmp(w_decl.description, "Unused variable"), 0)  // verify description
    TEST_2(w_decl.number, counter_before)            // verify counter
    TEST_2(cwarningCounter, counter_before + 1)      // counter incremented
    
    // Test 5: wrong_construction() - Create wrong construction warning
    counter_before = cwarningCounter;
    cwarning w_cons = wrong_construction("Incomplete initialization");
    TEST_2(w_cons.name != NULL, true)                // name should not be NULL
    TEST_2(strcmp(w_cons.name, "Wrong Construction"), 0)   // verify name
    TEST_2(w_cons.description != NULL, true)         // description should not be NULL
    TEST_2(w_cons.number, counter_before)            // verify counter
    
    // Test 6: bad_input() - Create bad input warning
    counter_before = cwarningCounter;
    cwarning w_input = bad_input("Suspicious value detected");
    TEST_2(w_input.name != NULL, true)               // name should not be NULL
    TEST_2(strcmp(w_input.name, "Bad Input"), 0)     // verify name
    TEST_2(w_input.description != NULL, true)        // description should not be NULL
    TEST_2(w_input.number, counter_before)           // verify counter incremented
    
    // Test 7: undefined_behavior() - Create undefined behavior warning
    counter_before = cwarningCounter;
    cwarning w_undef = undefined_behavior("Potential memory issue");
    TEST_2(w_undef.name != NULL, true)               // name should not be NULL
    TEST_2(strcmp(w_undef.name, "Undefined Behavior"), 0)  // verify name
    TEST_2(w_undef.description != NULL, true)        // description should not be NULL
    TEST_2(w_undef.number, counter_before)           // verify counter
    
    // Test 8: invalid_argument() - Create invalid argument warning
    counter_before = cwarningCounter;
    cwarning w_arg = invalid_argument("Type mismatch warning");
    TEST_2(w_arg.name != NULL, true)                 // name should not be NULL
    TEST_2(strcmp(w_arg.name, "Invalid Argument"), 0)     // verify name
    TEST_2(w_arg.description != NULL, true)          // description should not be NULL
    TEST_2(w_arg.number, counter_before)             // verify counter incremented
    
    // Test 9: Sequential warnings have unique numbers
    cwarningCounter = 100;  // Set custom start
    cwarning seq1 = wrong_indexing("First");
    cwarning seq2 = bad_input("Second");
    cwarning seq3 = invalid_argument("Third");
    TEST_2(seq1.number, 100)                         // first number
    TEST_2(seq2.number, 101)                         // second number (incremented)
    TEST_2(seq3.number, 102)                         // third number (incremented)
    TEST_2(cwarningCounter, 103)                     // counter at 103
    
    // Test 10: Warning with empty description
    counter_before = cwarningCounter;
    cwarning w_empty = bad_input("");
    TEST_2(w_empty.name != NULL, true)               // name should not be NULL
    TEST_2(w_empty.description != NULL, true)        // description initialized
    TEST_2(strlen(w_empty.description), 0)           // should be empty
    TEST_2(w_empty.number, counter_before)           // number properly set
    
    // Test 11: All warning creators preserve name correctly
    cwarning wt1 = wrong_indexing("test");
    cwarning wt2 = wrong_declaration("test");
    cwarning wt3 = wrong_construction("test");
    cwarning wt4 = bad_input("test");
    cwarning wt5 = undefined_behavior("test");
    cwarning wt6 = invalid_argument("test");
    ASSERT_TEST(wt1.name != NULL && strlen(wt1.name) > 0)  // all names set
    ASSERT_TEST(wt2.name != NULL && strlen(wt2.name) > 0)
    ASSERT_TEST(wt3.name != NULL && strlen(wt3.name) > 0)
    ASSERT_TEST(wt4.name != NULL && strlen(wt4.name) > 0)
    ASSERT_TEST(wt5.name != NULL && strlen(wt5.name) > 0)
    ASSERT_TEST(wt6.name != NULL && strlen(wt6.name) > 0)
    
    // Test 12: All warnings properly initialized
    TEST_2(wt1.number < wt2.number, true)            // numbers incrementing
    TEST_2(wt2.number < wt3.number, true)
    TEST_2(wt3.number < wt4.number, true)
    TEST_2(wt4.number < wt5.number, true)
    TEST_2(wt5.number < wt6.number, true)

EXIT_TEST(true)