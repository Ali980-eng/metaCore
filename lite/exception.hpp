#include <stdexcept>

#pragma once
#ifndef METACORE___LITE_EXCEPTION_HPP
#define METACORE___LITE_EXCEPTION_HPP

namespace lite
{
    class internal_exception : 
    public std::exception {};

    class OutOfRange : 
    public std::exception {};

    class undefined_behavior : 
    public std::exception {};

    class wrong_indexing : 
    public std::exception {};

    class wrong_declaration : 
    public std::exception {};

    class wrong_construction : 
    public std::exception {};
    
    class wrong_input : 
    public std::exception {};
}
#endif // METACORE___LITE_EXCEPTION_HPP