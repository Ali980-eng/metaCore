#ifndef METACORE___CGEN_MICROS_TEST_H
#define METACORE___CGEN_MICROS_TEST_H

    #define INIT_TEST(name)        \
        double tests_passed = 0.0; \
        double tests_failed = 0.0; \
        double total_tests = 0.0;  \
        char testName[] = #name

    #define printSummary                                       \
        printf("\n-------------------------------");           \
        printf("\n<<<<<<<<< test summary >>>>>>>>");           \
        printf("\n-------------------------------");           \
        printf("\nTEST NAME: %s", testName);                   \
        printf("\npassed tests: %i", (int)tests_passed);       \
        printf("\nfailed tests: %i", (int)tests_failed);       \
        printf("\ntotal tests: %i", (int)total_tests);         \
        if (total_tests > 0)                                   \
        {                                                      \
            printf("\npassed tests ratio: %f",                 \
                (double)(100 * (tests_passed / total_tests))); \
            printf("\nfailed tests ratio: %f",                 \
                (double)(100 * (tests_failed / total_tests))); \
        }                                                      \
        else                                                   \
        {                                                      \
            printf("\npassed tests ratio: 0.0");               \
            printf("\nfailed tests ratio: 0.0");               \
        }                                                      \
        printf("\n-------------------------------\n")

    #define MAIN_TEST(name)            \
        int main()                     \
        {                              \
            double tests_passed = 0.0; \
            double tests_failed = 0.0; \
            double total_tests = 0.0;  \
            char testName[] = #name

    #define EXIT_TEST(PS)             \
            if (PS) printSummary;     \
            return (int)tests_failed; \
        }

    #define TEST_0(cond)                            \
        if (cond) { tests_passed++; }               \
        else                                        \
        {                                           \
            tests_failed++;                         \
            printf("FAIL[%d]\n", (int)total_tests); \
        }                                           \
        total_tests++

    #define TEST_1(cond, msg)                                \
        if (cond) { tests_passed++; }                        \
        else                                                 \
        {                                                    \
            tests_failed++;                                  \
            printf("FAIL[%d]: %s\n", (int)total_tests, msg); \
        }                                                    \
        total_tests++

    #define TEST_2(real, expected)                  \
        if (real == expected) { tests_passed++; }   \
        else                                        \
        {                                           \
            tests_failed++;                         \
            printf("FAIL[%d]\n", (int)total_tests); \
        }                                           \
        total_tests++

    #define TEST_3(real, expected, msg)                      \
        if (real == expected) { tests_passed++; }            \
        else                                                 \
        {                                                    \
            tests_failed++;                                  \
            printf("FAIL[%d]: %s\n", (int)total_tests, msg); \
        }                                                    \
        total_tests++

    #define ASSERT_TEST(cond)                       \
        if(!(cond)) {                               \
            tests_failed++;                         \
            printf("FAIL[%d]\n", (int)total_tests); \
        } else { tests_passed++; }                  \
        total_tests++

    #define ASSERT(cond)                \
        if (!(cond))                    \
        {                               \
            retval = 1;                 \
            printf("FAILED: %s", cond); \
        }

#endif // METACORE___CGEN_MICROS_TEST_H