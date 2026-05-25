#include <stdexcept>
#include <string>

#pragma once
#ifndef METACORE___LITE_EXCEPTION_HPP
#define METACORE___LITE_EXCEPTION_HPP

/**
 * @file exception.hpp
 * @brief Comprehensive exception classes for the lite library.
 *
 * This header defines a hierarchy of exception classes for error handling
 * in the lite library. Each exception class represents a specific error condition
 * and provides context information for debugging and error reporting.
 *
 * @author MetaCore Development Team
 * @date 2025/09/25
 * @version 1.0
 *
 * Exception Hierarchy:
 * - lite_exception (base class)
 *   - internal_exception: Internal library errors
 *   - OutOfRange: Index or value out of valid range
 *   - undefined_behavior: Undefined behavior detected
 *   - wrong_indexing: Invalid indexing operations
 *   - wrong_declaration: Incorrect declarations
 *   - wrong_construction: Invalid object construction
 *   - wrong_input: Invalid input data or parameters
 *
 * Helper functions in the exception_factory namespace provide convenient ways to create
 * exceptions with predefined messages and context information.
 *
 * @see exception_factory namespace for helper functions
 */

namespace lite
{
    /**
     * @class exception
     * @brief Base exception class for all lite library exceptions.
     *
     * Provides a consistent interface for error handling with support for
     * custom error messages and proper exception hierarchy.
     */
    class exception : public std::exception
    {
    protected:
        std::string message_;  ///< Error message describing the exception

    public:
        /**
         * @brief Constructs a exception with an optional message.
         * @param message The error message (default: empty string)
         */
        explicit exception(const std::string& message = "")
            : message_(message) {}

        /**
         * @brief Virtual destructor for proper cleanup in derived classes.
         */
        virtual ~exception() noexcept = default;

        /**
         * @brief Returns the error message as a C-string.
         * @return Pointer to the error message C-string
         */
        const char* what() const noexcept override
        {
            return message_.empty() ? "lite exception" : message_.c_str();
        }

        /**
         * @brief Gets the error message as a string object.
         * @return Reference to the error message string
         */
        const std::string& get_message() const noexcept
        {
            return message_;
        }
    };

    /**
     * @class internal_exception
     * @brief Exception for internal library errors.
     *
     * Thrown when an internal error occurs within the lite library that
     * indicates a logic error or implementation issue.
     */
    class internal_exception : public exception
    {
    public:
        /**
         * @brief Constructs an internal_exception with an optional message.
         * @param message The error message (default: "Internal library error")
         */
        explicit internal_exception(const std::string& message = "Internal library error")
            : exception(message) {}

        /**
         * @brief Virtual destructor.
         */
        virtual ~internal_exception() noexcept = default;
    };

    /**
     * @class OutOfRange
     * @brief Exception for out-of-range access attempts.
     *
     * Thrown when an index, iterator, or value is outside the valid range
     * of a container or data structure. Stores index and size information
     * for context.
     */
    class OutOfRange : public exception
    {
    private:
        size_t index_;      ///< The out-of-range index
        size_t valid_size_; ///< The maximum valid size

    public:
        /**
         * @brief Constructs an OutOfRange exception with optional details.
         * @param message The error message (default: "Out of range")
         * @param index The problematic index (default: 0)
         * @param valid_size The maximum valid size (default: 0)
         */
        explicit OutOfRange(const std::string& message = "Out of range",
                          size_t index = 0, size_t valid_size = 0)
            : exception(message), index_(index), valid_size_(valid_size) {}

        /**
         * @brief Virtual destructor.
         */
        virtual ~OutOfRange() noexcept = default;

        /**
         * @brief Gets the out-of-range index that caused the exception.
         * @return The problematic index value
         */
        size_t get_index() const noexcept { return index_; }

        /**
         * @brief Gets the maximum valid size of the range.
         * @return The valid range size
         */
        size_t get_valid_size() const noexcept { return valid_size_; }
    };

    /**
     * @class undefined_behavior
     * @brief Exception for undefined behavior detection.
     *
     * Thrown when undefined behavior is detected during execution, such as
     * null pointer dereferences or invalid state transitions.
     */
    class undefined_behavior : public exception
    {
    public:
        /**
         * @brief Constructs an undefined_behavior exception with an optional message.
         * @param message The error message (default: "Undefined behavior detected")
         */
        explicit undefined_behavior(const std::string& message = "Undefined behavior detected")
            : exception(message) {}

        /**
         * @brief Virtual destructor.
         */
        virtual ~undefined_behavior() noexcept = default;
    };

    /**
     * @class wrong_indexing
     * @brief Exception for invalid indexing operations.
     *
     * Thrown when an indexing operation is invalid, such as using negative
     * indices where only positive indices are expected, or accessing
     * uninitialized indices.
     */
    class wrong_indexing : public exception
    {
    private:
        int invalid_index_; ///< The invalid index value

    public:
        /**
         * @brief Constructs a wrong_indexing exception with optional details.
         * @param message The error message (default: "Invalid index")
         * @param invalid_index The problematic index value (default: -1)
         */
        explicit wrong_indexing(const std::string& message = "Invalid index",
                               int invalid_index = -1)
            : exception(message), invalid_index_(invalid_index) {}

        /**
         * @brief Virtual destructor.
         */
        virtual ~wrong_indexing() noexcept = default;

        /**
         * @brief Gets the invalid index value that caused the exception.
         * @return The problematic index
         */
        int get_invalid_index() const noexcept { return invalid_index_; }
    };

    /**
     * @class wrong_declaration
     * @brief Exception for incorrect variable or type declarations.
     *
     * Thrown when a variable, function, or type is declared incorrectly,
     * or when there is a type mismatch in declarations.
     */
    class wrong_declaration : public exception
    {
    public:
        /**
         * @brief Constructs a wrong_declaration exception with an optional message.
         * @param message The error message (default: "Incorrect declaration")
         */
        explicit wrong_declaration(const std::string& message = "Incorrect declaration")
            : exception(message) {}

        /**
         * @brief Virtual destructor.
         */
        virtual ~wrong_declaration() noexcept = default;
    };

    /**
     * @class wrong_construction
     * @brief Exception for invalid object construction.
     *
     * Thrown when an object cannot be constructed properly due to
     * invalid parameters or preconditions not being met.
     */
    class wrong_construction : public exception
    {
    public:
        /**
         * @brief Constructs a wrong_construction exception with an optional message.
         * @param message The error message (default: "Invalid construction")
         */
        explicit wrong_construction(const std::string& message = "Invalid construction")
            : exception(message) {}

        /**
         * @brief Virtual destructor.
         */
        virtual ~wrong_construction() noexcept = default;
    };

    /**
     * @class wrong_input
     * @brief Exception for invalid input data or parameters.
     *
     * Thrown when input data or parameters do not meet the expected
     * requirements, constraints, or format specifications.
     */
    class wrong_input : public exception
    {
    private:
        std::string input_value_; ///< The problematic input value

    public:
        /**
         * @brief Constructs a wrong_input exception with optional details.
         * @param message The error message (default: "Invalid input")
         * @param input_value The problematic input (default: empty string)
         */
        explicit wrong_input(const std::string& message = "Invalid input",
                            const std::string& input_value = "")
            : exception(message), input_value_(input_value) {}

        /**
         * @brief Virtual destructor.
         */
        virtual ~wrong_input() noexcept = default;

        /**
         * @brief Gets the invalid input value that caused the exception.
         * @return Reference to the problematic input string
         */
        const std::string& get_input_value() const noexcept
        {
            return input_value_;
        }
    };

    /**
     * @namespace Exception
     * @brief Helper namespace providing convenient exception creation functions.
     *
     * This namespace contains functions that create exceptions with
     * predefined messages and context information, making exception handling
     * more concise and consistent throughout the library.
     */
    namespace Exception
    {
        /**
         * @brief Creates an OutOfRange exception with index and size information.
         * @param index The out-of-range index
         * @param size The maximum valid size
         * @return OutOfRange exception object with formatted message
         */
        inline OutOfRange out_of_range(size_t index, size_t size) noexcept
        {
            return OutOfRange("Index " + std::to_string(index) + 
                            " out of range [0, " + std::to_string(size - 1) + "]",
                            index, size);
        }

        /**
         * @brief Creates a wrong_indexing exception with the problematic index.
         * @param index The invalid index value
         * @return wrong_indexing exception object with formatted message
         */
        inline wrong_indexing invalid_index(int index) noexcept
        {
            return wrong_indexing("Invalid index: " + std::to_string(index), index);
        }

        /**
         * @brief Creates a wrong_declaration exception for type mismatches.
         * @return wrong_declaration exception object
         */
        inline wrong_declaration type_mismatch() noexcept
        {
            return wrong_declaration("Type mismatch in declaration");
        }

        /**
         * @brief Creates a wrong_construction exception for construction failures.
         * @return wrong_construction exception object
         */
        inline wrong_construction construction_failed() noexcept
        {
            return wrong_construction("Object construction failed");
        }

        /**
         * @brief Creates a wrong_input exception with the problematic input.
         * @param input The invalid input value
         * @return wrong_input exception object with formatted message
         */
        inline wrong_input invalid_input(const std::string& input) noexcept
        {
            return wrong_input("Invalid input: " + input, input);
        }

        /**
         * @brief Creates an undefined_behavior exception.
         * @return undefined_behavior exception object
         */
        inline undefined_behavior undefined() noexcept
        {
            return undefined_behavior("Undefined behavior detected");
        }

        /**
         * @brief Creates an internal_exception for library errors.
         * @return internal_exception exception object
         */
        inline internal_exception internal_error() noexcept
        {
            return internal_exception("Internal library error");
        }
    }
}
#endif // METACORE___LITE_EXCEPTION_HPP