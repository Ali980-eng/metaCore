#include "lite/type.hpp"
#include "cgen/micros.h"

MAIN_TEST(typeHpp)

    bool val = true;
    TEST_2(lite::type(val), "bool")

    char val1 = '9';
    TEST_2(lite::type(val1), "char")

    short val2 = 990;
    TEST_2(lite::type(val2), "short")

    int val3 = 10;
    TEST_2(lite::type(val3), "int")

    long val4 = 3993;
    TEST_2(lite::type(val4), "long")

    float val5 = 99.9f;
    TEST_2(lite::type(val5), "float")

    double val6 = 99.9;
    TEST_2(lite::type(val6), "double")

    long double val7 = 9993.983;
    TEST_2(lite::type(val7), "long double")

    TEST_2(lite::is_bool(val), true)
    TEST_2(lite::is_bool(val1), false)
    TEST_2(lite::is_char(val1), true)
    TEST_2(lite::is_char(val2), false)
    TEST_2(lite::is_short(val2), true)
    TEST_2(lite::is_short(val3), false)
    TEST_2(lite::is_int(val3), true)
    TEST_2(lite::is_int(val4), false)
    TEST_2(lite::is_float(val5), true)
    TEST_2(lite::is_float(val4), false)
    TEST_2(lite::is_double(val6), true)
    TEST_2(lite::is_double(val), false)
    TEST_2(lite::is_numeric(val2), true)
    TEST_2(lite::is_numeric(val), false)

    std::string val8 = "ken";
    TEST_2(lite::type(val8), "std: string")
    TEST_2(lite::is_string(val8), true)
    TEST_2(lite::is_string(val3), false)
EXIT_TEST(true)