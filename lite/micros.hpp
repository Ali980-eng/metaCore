#include <string>
#include <iostream>

#pragma once
#ifndef METACORE___LITE_MICROS_HPP
#define METACORE___LITE_MICROS_HPP

#define nl '\n'
#define tab '\t'
#define object class
#define microPrint(output) \
    std::cout << output;
#define microPrintLn(output) \
    std::cout << output << '\n';
typedef std::string str;

#endif // METACORE___LITE_MICROS_HPP