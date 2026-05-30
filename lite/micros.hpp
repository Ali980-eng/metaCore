#include <string>
#include <iostream>

#pragma once
#ifndef METACORE___LITE_MICROS_HPP
#define METACORE___LITE_MICROS_HPP

#define nl '\n'

#define tab '\t'

#define object class

#define Print(output) \
    std::cout << output;

#define PrintLn(output) \
    std::cout << output << nl;

typedef std::string str;

#define lambda_lite(capture_clause, parameters, return_type, script) \
    [capture_clause] parameters -> return_type { script }

#endif // METACORE___LITE_MICROS_HPP