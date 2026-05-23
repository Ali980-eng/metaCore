
#include <windows.h>
#include <string>
#include "clite/micros.h"
#include "lite/micros.hpp"
#include "lite/stream.hpp"

#pragma once
#ifndef METACORE___LITE_ECOSYSTEM_HPP
#define METACORE___LITE_ECOSYSTEM_HPP

namespace metaCore {
    /**
     * @brief Converts a std::string to std::wstring.
     * @param s The string to convert.
     * @return A wide string representation of the input.
     */
    inline std::wstring toWide(const std::string& s) {
        return std::wstring(s.begin(), s.end());
    }

    /**
     * @brief Ecosystem management object for handling warnings and errors.
     * 
     * Provides centralized error and warning handling with support for message boxes
     * on Windows and console output. Manages program exit status.
     */
    object eco_system {
        private:
        lite::wstream _sys_w;
        lite::error _sys_err;
        std::vector<TEST> _sys_test;
        bool retval;
        protected:
        const str wm = "meta ecosystem warning",
        em = "meta ecosystem error";
        public:

        void add(const TEST& value, bool PTS) {
            _sys_test.push_back(value);
            if(PTS) printTest(value);
        }
        
        void print_sys_test() {
            INIT_TEST("meta ecosystem test")
            for(TEST T : _sys_test) {
                if(T.result) tests_passed++;
                else tests_failed++;
                total_tests++;
            }
            printSummary
        }

        /**
         * @brief Catches and displays a warning.
         * @param w The warning object to handle.
         * @param msgbox If true, displays the warning in a message box; otherwise prints to console.
         */
        void Catch(const lite::warning& w, bool msgbox = false) noexcept {
            const char* s1 = "lite ecosystem warning";
            
            if(msgbox) {
                MessageBox(NULL, 
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
         * @param e The error object to handle.
         * @details Displays the error in a message box and terminates the program with EXIT_FAILURE.
         */
        void Catch(lite::error& e) noexcept {
            MessageBox(NULL, 
                toWide(em).c_str(),
                toWide(e.printingFormat()).c_str(),
                MB_OK | MB_ICONINFORMATION);
            std::exit(EXIT_FAILURE);
        }

        /**
         * @brief Returns the exit status value.
         * @return 1 if a warning was caught, 0 otherwise.
         */
        int exit_value() noexcept {
            return retval ? 1 : 0;
        }

        /**
         * @brief Exits the system with appropriate status code.
         * @details Terminates the program with EXIT_FAILURE if warnings were caught, otherwise EXIT_SUCCESS.
         */
        void system_exit() {
            if(retval) std::exit(EXIT_FAILURE);
            else std::exit(EXIT_SUCCESS);
        }
    } ecoSys;
}

#endif // METACORE___LITE_ECOSYSTEM_HPP