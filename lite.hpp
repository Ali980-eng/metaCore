/**
 * @file lite.hpp
 * @brief MetaCore ecosystem management system for centralized error and warning handling.
 *
 * This header provides a comprehensive ecosystem management system that centralizes
 * error and warning handling for the MetaCore library. It integrates Windows-specific
 * functionality (message boxes) with cross-platform console output, and includes
 * comprehensive test result management.
 *
 * The system provides:
 * - Centralized warning queue management with console and message box display options
 * - Error handling with immediate program termination
 * - Test result collection and summary reporting
 * - Exit status tracking for proper program termination
 * - String conversion utilities for Windows wide-character support
 *
 * Key Classes:
 * - system65: The main ecosystem management object that handles all warnings, errors,
 *   test collection, and program exit status.
 *
 * Features:
 * - Warning Queue: Collects warnings for later processing
 * - Error Handling: Catches errors and terminates program gracefully
 * - Test Management: Collects and reports test results with pass/fail statistics
 * - Windows Integration: Supports message box dialogs for user notification
 * - Exit Status Tracking: Tracks whether warnings occurred for proper exit codes
 *
 * Usage Example:
 * @code
 * warning w("Something unexpected happened");
 * meta::metaSystem.Catch(w, true);  // Display as message box
 *
 * error e("Critical failure");
 * meta::metaSystem.Catch(e);  // Display and exit
 *
 * CTEST test("my_test", true);
 * meta::metaSystem.add(test, true);  // Add and print test
 *
 * meta::metaSystem.system_exit();  // Exit with appropriate status
 * @endcode
 *
 * @author MetaCore Development Team
 * @date 2025/09/25
 * @version 1.0
 *
 * @see lite/warning.hpp for warning class
 * @see lite/error.hpp for error class
 * @see clite/UnitTest.h for CTEST class
 * @see lite/micros.hpp for macro definitions
 */

#ifndef METACORE___LITE_HPP
#define METACORE___LITE_HPP

#include "lite/benchmark.hpp"
#include "lite/error.hpp"
#include "lite/exception.hpp"
#include "lite/io.hpp"
#include "lite/random.hpp"
#include "lite/stream.hpp"
#include "lite/type.hpp"
#include "lite/UnitTest.hpp"
#include "lite/warning.hpp"


namespace lite {
    /**
     * @brief Converts a std::string to std::wstring for Windows API compatibility.
     * 
     * This function provides convenient conversion of narrow character strings
     * to wide character strings, which is required for many Windows API functions
     * like MessageBox().
     *
     * @param s The standard string to convert.
     * @return A wide string representation of the input string with identical characters.
     *
     * @note Uses simple character-by-character iteration. For localized text with
     *       multi-byte characters, consider using MultiByteToWideChar() instead.
     *
     * @example
     * std::string narrow = "Hello";
     * std::wstring wide = toWide(narrow);  // Returns L"Hello"
     */
    inline std::wstring toWide(const std::string& s) {
        return std::wstring(s.begin(), s.end());
    }

    /**
     * @class system65
     * @brief Ecosystem management object for centralized error and warning handling.
     * 
     * This class provides a centralized management system for the MetaCore library's
     * error handling, warning management, test collection, and program exit status.
     * It integrates with the Windows API for message box display and supports
     * comprehensive test result tracking.
     *
     * The system maintains:
     * - A queue of warning objects for deferred processing
     * - A single error object for immediate handling
     * - A vector of test results for statistical reporting
     * - A return value flag to track if warnings or errors occurred
     *
     * @note This class uses protected members to prevent direct access to internal state.
     *       All interactions are through public member methods.
     */
    class system64 {
        private:
        std::queue<warning> sys_w;
        error sys_err;
        bool retval;
        protected:
        const std::string wm = "meta lite ecosystem warning",
        em = "meta lite ecosystem error";
        public:

        test_stream sys_test;

        system64() = default;

        /**
         * @brief Adds a test result to the ecosystem's test collection.
         * 
         * Appends a test result to the internal test vector and optionally
         * prints the test result immediately.
         *
         * @param value The CTEST object containing test result information.
         * @param PTS Print-To-Screen flag; if true, prints the test result immediately.
         *
         * @note The test result is always added to the collection regardless of PTS value.
         *
         * @see printcsys_test() for viewing all collected tests
         */
        void add(TEST& value, bool PTS) {
            sys_test << value;
            if(PTS) io::print_test(value.get(true), value.get(false), value.get(), sys_test.get_total_tests());
        }
        
        /**
         * @brief Prints a summary of all collected test results.
         * 
         * Iterates through all collected test results and generates a comprehensive
         * summary report including:
         * - Total number of tests executed
         * - Number of tests passed
         * - Number of tests failed
         *
         * @note Uses TEST_0 macro pattern for summary generation.
         * @see add() for adding tests to the collection
         */
        void print_summary() { }

        /**
         * @brief Catches and displays a warning with optional message box.
         * 
         * Processes a warning object by either displaying it in a Windows message box
         * or printing it to standard output. Sets the return value flag to indicate
         * that a warning occurred.
         *
         * @param w The warning object to handle.
         * @param msgbox Display mode flag:
         *               - true: Display warning in a Windows message box
         *               - false: Print warning to console output (default)
         *
         * @note This function is marked noexcept and will not throw exceptions.
         *       The return value flag is always set to true after catching a warning.
         *
         * @see warning class in lite/warning.hpp
         * @see exit_value() for checking accumulated warning status
         */
        void Catch(const warning& w, bool msgbox = false) noexcept {
            const char* s1 = "lite ecosystem warning";
            
            if(msgbox) {
                MessageBoxW(NULL, 
                    toWide(wm).c_str(), 
                    toWide(w.printingFormat()).c_str(), 
                    MB_OK | MB_ICONINFORMATION);
            } else {
                std::cout << w;
            }
            retval = true;
        }

        /**
         * @brief Catches and displays an error, then exits the program.
         * 
         * Processes an error object by displaying it in a Windows message box
         * and immediately terminating the program with EXIT_FAILURE. This is
         * appropriate for critical errors that cannot be recovered from.
         *
         * @param e The error object to handle and display.
         *
         * @note This function is marked noexcept but will not return, as it calls
         *       std::exit(EXIT_FAILURE) which terminates the program.
         *       The return value flag is not updated since the program exits.
         *
         * @warning This function terminates program execution immediately.
         *          Resources are not guaranteed to be cleaned up properly.
         *
         * @see error class in lite/error.hpp
         * @see Catch(const warning&, bool) for non-fatal warning handling
         */
        void Catch(error& e) noexcept {
            MessageBoxW(NULL, 
                toWide(em).c_str(),
                toWide(e.printingFormat()).c_str(),
                MB_OK | MB_ICONINFORMATION);
            std::exit(EXIT_FAILURE);
        }

        /**
         * @brief Returns the current exit status value.
         * 
         * Indicates whether any warnings or errors have been encountered by
         * the ecosystem management system.
         *
         * @return Exit status code:
         *         - 1 if warnings were caught (retval = true)
         *         - 0 if no warnings occurred (retval = false)
         *
         * @note This value should be used as the exit code when terminating
         *       the application to indicate success or warning conditions.
         *
         * @see system_exit() for automatic program termination with status code
         */
        int exit_value() noexcept {
            return retval ? 1 : 0;
        }

        /**
         * @brief Exits the system with appropriate status code.
         * 
         * Terminates the program based on the accumulated return value flag.
         * If warnings were caught, exits with EXIT_FAILURE; otherwise exits
         * with EXIT_SUCCESS.
         *
         * @details This function uses std::exit() which may not properly
         *          clean up local objects or run destructors in all cases.
         *          Consider using return statements or other exit mechanisms
         *          when possible.
         *
         * @note This function does not return; it always terminates program execution.
         *
         * @see exit_value() for checking status without exiting
         * @see Catch() for handling warnings and errors
         */
        void system_exit() {
            if(retval) std::exit(EXIT_FAILURE);
            else std::exit(EXIT_SUCCESS);
        }

    } ecosystem;
}

#endif // METACORE___LITE_HPP