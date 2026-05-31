#include "clite/micros.h"

MAIN_TEST(micros)
    
    short jv1 = 0, jv2 = 0, jv3 = 100, jv4 = 200, jv5 = 10;
    tl1: jv1++;
    jump_if(jv1 < 50, tl1);
    tl2: jv2++;
    jump_if(jv2 <= 50, tl2);
    tl3: jv3--;
    jump_if(jv3 > 0, tl3);
    tl4: jv4--;
    jump_if(jv4 >= 0, tl4);
    tl5: jv5--;
    jump_if(jv5 != 5, tl5);
    
    TEST_2(jv1, 49)
    TEST_2(jv2, 50)
    TEST_2(jv3, 0)
    TEST_2(jv4, -1)
    TEST_2(jv5, 5)

    cstr(s1,) = "09iie8";
    TEST_2(length(s1), 6)
    cstr(s2,) = "88938";
    TEST_2(equal(s1, s2), false)
    TEST_2(length(s2), 5)
    cstr(s3,) = "88938";
    TEST_2(equal(s2, s3), true)
    cstr(s4,) = concatenate(s1, s2);
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
    cstr_free(s4);

EXIT_TEST(true)