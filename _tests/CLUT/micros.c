#include "clite/micros.h"

MAIN_TEST(micros)
    
    short jmpval = 0;

    test_label:
    printf("(%d), ", jmpval);
    jmpval++;
    jump_if(jmpval  < 50, test_label)

    /*cstr(s1, "09iie8")
    TEST_2(length(s1), 6)
    cstr(s2, "88938")
    TEST_2(equal(s1, s2), false)
    TEST_2(length(s2), 5)
    cstr(s3, "88938")
    TEST_2(equal(s2, s3), true)
    cstr(s4, concatenate(s1, s2))
    TEST_2(length(s4), 11)
    TEST_2(is_empty(s3), false)
    cstr_empty(s4);
    TEST_2(is_empty(s4), true)
    TEST_2(exist(s2, '8'), true)
    TEST_2(exist(s2, 'i'), false)
    TEST_2(sub_exist(s2, "938"), true)
    TEST_2(sub_exist(s2, "88k"), false)
    TEST_2(count(s2, '8'), 3)
    TEST_2(count(s1, 'i'), 2)
    cstr_free(s1);
    cstr_free(s2);
    cstr_free(s3);
    cstr_free(s4);*/

EXIT_TEST(true)