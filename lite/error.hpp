/**
 * @file error.hpp
 * @brief Error Management and Reporting System
 * @author MetaCore Development Team
 * @date May 25, 2026
 * 
 * @details
 * This file provides a comprehensive error handling system with an error class that tracks
 * error information including name, description, and occurrence time. It also provides
 * helper functions for creating common error types through the err namespace.
 * 
 * @classes
 * - error          : Main error class for storing and managing error information
 * 
 * @namespace err
 * Helper functions for creating predefined error types:
 * - wrong_indexing()         : Creates "Wrong Indexing" error
 * - wrong_declaration()      : Creates "Wrong declaration" error
 * - wrong_construction()     : Creates "Wrong Construction" error
 * - bad_input()              : Creates "Bad Input" error
 * - undefined_behavior()     : Creates "Undefined Behavior" error
 * - invalid_argument()       : Creates "Invalid Argument" error
 * - OutOfRange()             : Creates "Out Of Range" error
 * - internal_problem()       : Creates "Internal Problem" error
 * 
 * @key_functions
 * - error()                  : Multiple constructors for error initialization
 * - empty()                  : Check if name or description is empty
 * - length()                 : Get length of name or description
 * - printingFormat()         : Generate formatted error string
 * - operator<<()             : Stream output for error objects
 */

#if defined(__cpp_modules) && (__cplusplus >= 202302L)
    import std;
#else
    #include <string>
    #include <iostream>
    #include <cstdlib>
    #include <source_location>
#endif

#include "benchmark.hpp"

#pragma once
#ifndef METACORE___LITE_ERROR_HPP
#define METACORE___LITE_ERROR_HPP

#ifdef METACORE___META_HPP
namespace meta {
#endif // METACORE___META_HPP
#ifdef METACORE___LITE_HPP
namespace lite {
#endif // METACORE___LITE_HPP

    benchmark::code_timer<true> errTimer;
    
    /**
     * @brief Error class for storing and managing error information.
     * 
     * Tracks error name, description, and the time when the error occurred.
     */
    class error {
        private:
        std::string name;
        std::string description;
        std::source_location errLocation;
        float event;

        public:
        /**
         * @brief Default constructor that creates an unknown error.
         */
        error() {
            name = "Unknown Error";
            description = "no description for this error";
            errLocation = std::source_location::current();
            event = errTimer.get_duration();
        }

        /**
         * @brief Constructor that creates an error with a name.
         * @param name The name/type of the error.
         */
        error(const std::string& name) noexcept {
            this->name = name;
            errLocation = std::source_location::current();
            event = errTimer.get_duration();
        }

        /**
         * @brief Constructor that creates an error with name and description.
         * @param name The name/type of the error.
         * @param description A detailed description of the error.
         */
        error(const std::string& name, const std::string& description) noexcept {
            this->name = name;
            this->description = description;
            errLocation = std::source_location::current();
            event = errTimer.get_duration();
        }

        /**
         * @brief Checks if the error name or description is empty.
         * @param isName If true, checks the name; if false, checks the description.
         * @return True if the selected field is empty, false otherwise.
         */
        bool empty(bool isName) noexcept {
            return isName ? 
            name.empty() : 
            description.empty();
        }

        /**
         * @brief Returns the length of the error name or description.
         * @param isName If true, returns the name length; if false, returns the description length.
         * @return The length of the selected field.
         */
        size_t length(bool isName) noexcept {
            return isName ? 
            name.length() : 
            description.length();
        }

        constexpr float get_time() const noexcept { return event; }

        std::string get_file() const noexcept { return errLocation.file_name(); }

        constexpr size_t get_line() noexcept { return (size_t) errLocation.line(); }

        constexpr size_t get_column() noexcept { return (size_t) errLocation.column(); }

        /**
         * @brief Generates a formatted string representation of the error.
         * @return A formatted string containing error name, description, and time.
         */
        std::string printingFormat() noexcept {
            std::string result;
            if(!name.empty()) { 
                result += std::string("error name: " + 
                    name + "\n");
            }
            else {
                result += "error name: Unknown \n";
            }
            if(!description.empty()) {
                result += std::string("error description: " + 
                    description + "\n");
            }
            else {
                result += "error description: nothing \n";
            }
            result += std::string("Error File: " + get_file());
            result += std::string("Error Line: " + std::to_string(get_line()));
            result += std::string("Error Time: " + std::to_string(event) + " ms.\n");
            return result;
        }

        void operator=(const error& other) noexcept {
            name = other.name;
            description = other.description;
            errLocation = other.errLocation;
            event = other.event;
        }

        /**
         * @brief Stream output operator for the error class.
         * @param os The output stream.
         * @param e The error object to output.
         * @return Reference to the output stream.
         */
        friend std::ostream& operator<<(std::ostream& os, const error& e) noexcept;

        ~error() noexcept = default;
    };

    /**
     * @brief Stream output operator for the error class.
     * @param os The output stream.
     * @param e The error object to output.
     * @return Reference to the output stream.
     */
    std::ostream& operator<<(std::ostream& os, const error& e) noexcept {
        if(!e.name.empty()) { 
            os << std::string("error name: " + e.name + "\n");
        }
        else {
            os << "error name: Unknown \n";
        }
        if(!e.description.empty()) {
            os << std::string("error description: " + e.description + "\n");
        }
        else {
            os << "error description: nothing \n";
        }
        os << std::string("Error Time: " + std::to_string(e.event) + " ms.\n");
        return os;
    }

    /**
     * @namespace err
     * @brief Helper functions for creating common error types.
     */
    namespace err {
        /**
         * @brief Creates a "Wrong Indexing" error.
         * @return An error object with the type "Wrong Indexing".
         */
        error wrong_indexing() noexcept {
            return error{"Wrong Indexing"};
        }
        
        /**
         * @brief Creates a "Wrong Indexing" error with description.
         * @param description The error description.
         * @return An error object with the type "Wrong Indexing" and provided description.
         */
        error wrong_indexing(const std::string &description) noexcept {
            return error{"Wrong Indexing", description};
        }

        /**
         * @brief Creates a "Wrong declaration" error.
         * @return An error object with the type "Wrong declaration".
         */
        error wrong_declaration() noexcept {
            return error{"Wrong declaration"};
        }
        
        /**
         * @brief Creates a "Wrong declaration" error with description.
         * @param description The error description.
         * @return An error object with the type "Wrong declaration" and provided description.
         */
        error wrong_declaration(const std::string &description) noexcept {
            return error{"Wrong declaration", description};
        }

        /**
         * @brief Creates a "Wrong Construction" error.
         * @return An error object with the type "Wrong Construction".
         */
        error wrong_construction() noexcept {
            return error{"Wrong Construction"};
        }

        /**
         * @brief Creates a "Wrong Construction" error with description.
         * @param description The error description.
         * @return An error object with the type "Wrong Construction" and provided description.
         */
        error wrong_construction(const std::string &description) noexcept {
            return error{"Wrong Construction", description};
        }

        /**
         * @brief Creates a "Bad Input" error.
         * @return An error object with the type "Bad Input".
         */
        error bad_input() noexcept {
            return error{"Bad Input"};
        }

        /**
         * @brief Creates a "Bad Input" error with description.
         * @param description The error description.
         * @return An error object with the type "Bad Input" and provided description.
         */
        error bad_input(const std::string &description) noexcept {
            return error{"Bad Input", description};
        }

        /**
         * @brief Creates an "Undefined Behavior" error.
         * @return An error object with the type "Undefined Behavior".
         */
        error undefined_behavior() noexcept {
            return error{"Undefined Behavior"};
        }

        /**
         * @brief Creates an "Undefined Behavior" error with description.
         * @param description The error description.
         * @return An error object with the type "Undefined Behavior" and provided description.
         */
        error undefined_behavior(const std::string &description) noexcept {
            return error{"Undefined Behavior", description};
        }
        
        /**
         * @brief Creates an "Invalid Argument" error.
         * @return An error object with the type "Invalid Argument".
         */
        error invalid_argument() noexcept {
            return error{"Invalid Argument"};
        }

        /**
         * @brief Creates an "Invalid Argument" error with description.
         * @param description The error description.
         * @return An error object with the type "Invalid Argument" and provided description.
         */
        error invalid_argument(const std::string &description) noexcept {
            return error{"Invalid Argument", description};
        }
        
        /**
         * @brief Creates an "Out Of Range" error.
         * @return An error object with the type "Out Of Range".
         */
        error OutOfRange() noexcept {
            return error{"Out Of Range"};
        }

        /**
         * @brief Creates an "Out Of Range" error with description.
         * @param description The error description.
         * @return An error object with the type "Out Of Range" and provided description.
         */
        error OutOfRange(const std::string &description) noexcept {
            return error{"Out Of Range", description};
        }

        /**
         * @brief Creates an "Internal Problem" error.
         * @return An error object with the type "Internal Problem".
         */
        error internal_problem() noexcept {
            return error{"Internal Problem"};
        }
        
        /**
         * @brief Creates an "Internal Problem" error with description.
         * @param description The error description.
         * @return An error object with the type "Internal Problem" and provided description.
         */
        error internal_problem(const std::string &description) noexcept {
            return error{"Internal Problem", description};
        }
    }

#ifdef METACORE___LITE_HPP
}
#endif // METACORE___LITE_HPP
#ifdef METACORE___META_HPP
}
#endif // METACORE___META_HPP

#endif // METACORE___LITE_ERROR_HPP