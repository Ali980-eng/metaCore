/**
 * @file warning.hpp
 * @brief A header file for warning messages in the MetaCore library.
 * This file defines functions for displaying various warning messages related to indexing, deprecated features, bad input, and undefined behavior.
 * The functions are designed to provide informative messages to developers when certain conditions are met, such as using deprecated features or encountering bad input.
 * Each function can be called with or without a custom message, allowing for flexibility in how warnings are presented.
 * The functions are intended to be used throughout the MetaCore library to help developers identify and address potential issues in their code.
 * @note This header is part of the MetaCore library and is intended for use in C++ projects that utilize this library.
 * @author Ali Lafi
 * @date 2025 / 9 / 25
 * @see Lite/UnitTest.hpp for related testing functions and structures.
 */

#if defined(__cpp_modules) && (__cplusplus >= 202302L)
    import std;
#else
    #include <string>
    #include <iostream>
    #include <source_location>
#endif

// local headers
#include "io.hpp"
#include "benchmark.hpp"
#include "cgen/micros/structure.h"

#pragma once
#ifndef METACORE___LITE_WARNING_HPP
#define METACORE___LITE_WARNING_HPP

#ifdef METACORE___META_HPP
namespace meta {
#endif // METACORE___META_HPP
#ifdef METACORE___LITE_HPP
namespace lite {
#endif // METACORE___LITE_HPP

    benchmark::code_timer<true> warning_time;

    class warning
    {
    private:
        str name;
        str description;
        std::source_location warningLocation;
        float event;
    public:

        /// @brief Constructs a warning with default name and description.
        warning() noexcept {
            name = "Undefined";
            description = "This warning has no description";
            warningLocation = std::source_location::current();
            event = warning_time.get_duration();
        }

        /// @brief Constructs a warning with the specified name and description.
        /// @param name The name of the warning.
        /// @param description The description of the warning.
        warning(const str& name, const str& description) noexcept {
            this->name = name;
            this->description = description;
            warningLocation = std::source_location::current();
            event = warning_time.get_duration();
        }

        /// @brief Constructs a warning with the specified name.
        /// @param name The name of the warning.
        warning(const str& name) noexcept {
            this->name = name;
            description = "";
            warningLocation = std::source_location::current();
            event = warning_time.get_duration();
        }

        /// @brief Constructs a warning by copying another warning.
        /// @param other The warning to copy.
        warning(const warning& other) noexcept {
            name = other.name;
            description = other.description;
            warningLocation = std::source_location::current();
            event = other.event;
        }

        /// @brief Gets the string representation of the warning.
        /// @return The string representation of the warning.
        str get() const noexcept {
            str result;
            if(description.empty()) {
                result += "Warning[";
                result += name;
                result += "]";
            } else {
                result += "Warning[";
                result += name;
                result += "]: ";
                result += description;
            }
            result += ".\n";
            return result;
        }

        /// @brief Gets the name of the warning.
        /// @return The name of the warning.
        str get_name() const noexcept { return name; }

        /// @brief Gets the time associated with the warning.
        /// @return The time associated with the warning.
        float get_time() const noexcept { return event; }

        /// @brief Gets the description of the warning.
        /// @return The description of the warning.
        str get_des() const noexcept { return description; }

        constexpr size_t get_line() const noexcept { return (size_t) warningLocation.line(); }

        str get_file() const noexcept { return warningLocation.file_name(); }

        constexpr size_t get_column() const noexcept { return (size_t) warningLocation.column(); }

        /// @brief Replaces the name and description of the warning.
        /// @param name The new name of the warning.
        /// @param description The new description of the warning.
        void replace(const str &name, 
            const str &description) noexcept {
            this->name = name;
            this->description = description;
        }

        // SRV: standard return value.
        /// @brief this function returns a default value of the specified type, which can be used as a standard return value in various contexts.
        /// @tparam T The type of the default value to return.
        /// @return The default value of the specified type.
        template<typename T>
        constexpr T SRV() noexcept { return T(); }

        /**
         * @brief Assignment operator from a string.
         * 
         * Assigns a string value to the warning's name and resets the description.
         * Updates the event timestamp to the current duration.
         * 
         * @param name The name to assign to this warning.
         * @note Sets description to empty string and updates event time.
         * @note This operator is marked noexcept.
         */
        void operator=(const str& name) noexcept {
            this->name = name;
            description = "";
            warningLocation = std::source_location::current();
            event = warning_time.get_duration();
        }

        /**
         * @brief Copy assignment operator.
         * 
         * Assigns the contents of another warning object to this warning.
         * Copies the name, description, and event timestamp.
         * 
         * @param other The warning object to copy from.
         * @note This operator performs a deep copy of all warning attributes.
         * @note This operator is marked noexcept.
         */
        void operator=(const warning& other) noexcept {
            name = other.name;
            description = other.description;
            warningLocation = other.warningLocation;
            event = other.event;
        }

        /**
         * @brief Generates a formatted string representation of the warning.
         * @return A formatted string containing the warning's name, description, and event time.
         */
        str printingFormat() const noexcept {
            str result = get();
            result += str("File: " + get_file());
            result += str("Line: " + std::to_string(get_line()));
            result += str("Column: " + std::to_string(get_column()));
            result += str("Time: " + std::to_string(get_time()) + " ms.\n");
            return result;
        }

        /// @brief Stream output operator for warning class.
        /// @param os The output stream to write to.
        /// @param w The warning object to output.
        /// @return Reference to the output stream for chaining operations.
        friend std::ostream& operator<<(std::ostream& os, const warning& w) noexcept;
    };

    /**
     * @brief Stream output operator for warning class.
     * 
     * Outputs the warning information to the provided output stream.
     * Prints the warning message and its associated timestamp.
     * 
     * @param os The output stream to write to.
     * @param w The warning object to output.
     * @return Reference to the output stream for chaining operations.
     * @note This operator is marked noexcept.
     * @see warning::get(), warning::get_time()
     */
    std::ostream& operator<<(std::ostream& os, const warning& w) noexcept {
        os << w.get();
        os << "Time: " << w.get_time() << " ms.\n";
        return os;
    }

    namespace Warning {
        /**
         * @brief Factory function to create a 'Wrong Indexing' warning.
         * 
         * @return A new warning object with the name 'Wrong Indexing'.
         * @note This overload creates a warning without a description.
         * @note This function is marked noexcept.
         */
        warning wrong_indexing() noexcept {
            return warning{"Wrong Indexing"};
        }

        /**
         * @brief Factory function to create a 'Wrong Indexing' warning with description.
         * 
         * @param description A custom description for the warning.
         * @return A new warning object with the name 'Wrong Indexing' and the provided description.
         * @note This overload creates a warning with a custom description.
         * @note This function is marked noexcept.
         */
        warning wrong_indexing(const str &description) noexcept {
            return warning{"Wrong Indexing", description};
        }

        /**
         * @brief Factory function to create a 'Wrong Declaration' warning.
         * 
         * @return A new warning object with the name 'Wrong declaration'.
         * @note This overload creates a warning without a description.
         * @note This function is marked noexcept.
         */
        warning wrong_declaration() noexcept {
            return warning{"Wrong declaration"};
        }

        /**
         * @brief Factory function to create a 'Wrong Declaration' warning with description.
         * 
         * @param description A custom description for the warning.
         * @return A new warning object with the name 'Wrong declaration' and the provided description.
         * @note This overload creates a warning with a custom description.
         * @note This function is marked noexcept.
         */
        warning wrong_declaration(const str &description) noexcept {
            return warning{"Wrong declaration", description};
        }

        /**
         * @brief Factory function to create a 'Wrong Construction' warning.
         * 
         * @return A new warning object with the name 'Wrong Construction'.
         * @note This overload creates a warning without a description.
         * @note This function is marked noexcept.
         */
        warning wrong_construction() noexcept {
            return warning{"Wrong Construction"};
        }

        /**
         * @brief Factory function to create a 'Wrong Construction' warning with description.
         * 
         * @param description A custom description for the warning.
         * @return A new warning object with the name 'Wrong Construction' and the provided description.
         * @note This overload creates a warning with a custom description.
         * @note This function is marked noexcept.
         */
        warning wrong_construction(const str &description) noexcept {
            return warning{"Wrong Construction", description};
        }

        /**
         * @brief Factory function to create a 'Bad Input' warning.
         * 
         * @return A new warning object with the name 'Bad Input'.
         * @note This overload creates a warning without a description.
         * @note This function is marked noexcept.
         */
        warning bad_input() noexcept {
            return warning{"Bad Input"};
        }

        /**
         * @brief Factory function to create a 'Bad Input' warning with description.
         * 
         * @param description A custom description for the warning.
         * @return A new warning object with the name 'Bad Input' and the provided description.
         * @note This overload creates a warning with a custom description.
         * @note This function is marked noexcept.
         */
        warning bad_input(const str &description) noexcept {
            return warning{"Bad Input", description};
        }

        /**
         * @brief Factory function to create an 'Undefined Behavior' warning.
         * 
         * @return A new warning object with the name 'Undefined Behavior'.
         * @note This overload creates a warning without a description.
         * @note This function is marked noexcept.
         */
        warning undefined_behavior() noexcept {
            return warning{"Undefined Behavior"};
        }

        /**
         * @brief Factory function to create an 'Undefined Behavior' warning with description.
         * 
         * @param description A custom description for the warning.
         * @return A new warning object with the name 'Undefined Behavior' and the provided description.
         * @note This overload creates a warning with a custom description.
         * @note This function is marked noexcept.
         */
        warning undefined_behavior(const str &description) noexcept {
            return warning{"Undefined Behavior", description};
        }

        /**
         * @brief Factory function to create an 'Invalid Argument' warning.
         * 
         * @return A new warning object with the name 'Invalid Argument'.
         * @note This overload creates a warning without a description.
         * @note This function is marked noexcept.
         */
        warning invalid_argument() noexcept {
            return warning{"Invalid Argument"};
        }

        /**
         * @brief Factory function to create an 'Invalid Argument' warning with description.
         * 
         * @param description A custom description for the warning.
         * @return A new warning object with the name 'Invalid Argument' and the provided description.
         * @note This overload creates a warning with a custom description.
         * @note This function is marked noexcept.
         */
        warning invalid_argument(const str &description) noexcept {
            return warning{"Invalid Argument", description};
        }

        /**
         * @brief Factory function to create an 'Out Of Range' warning.
         * 
         * @return A new warning object with the name 'Out Of Range'.
         * @note This overload creates a warning without a description.
         * @note This function is marked noexcept.
         */
        warning OutOfRange() noexcept {
            return warning{"Out Of Range"};
        }

        /**
         * @brief Factory function to create an 'Out Of Range' warning with description.
         * 
         * @param description A custom description for the warning.
         * @return A new warning object with the name 'Out Of Range' and the provided description.
         * @note This overload creates a warning with a custom description.
         * @note This function is marked noexcept.
         */
        warning OutOfRange(const str &description) noexcept {
            return warning{"Out Of Range", description};
        }

        /**
         * @brief Factory function to create an 'Internal Problem' warning.
         * 
         * @return A new warning object with the name 'Internal Problem'.
         * @note This overload creates a warning without a description.
         * @note This function is marked noexcept.
         */
        warning internal_problem() noexcept {
            return warning{"Internal Problem"};
        }

        /**
         * @brief Factory function to create an 'Internal Problem' warning with description.
         * 
         * @param description A custom description for the warning.
         * @return A new warning object with the name 'Internal Problem' and the provided description.
         * @note This overload creates a warning with a custom description.
         * @note This function is marked noexcept.
         */
        warning internal_problem(const str &description) noexcept {
            return warning{"Internal Problem", description};
        }
    }

#ifdef METACORE___LITE_HPP
}
#endif // METACORE___LITE_HPP
#ifdef METACORE___META_HPP
}
#endif // METACORE___META_HPP

#endif // METACORE___LITE_WARNING_HPP