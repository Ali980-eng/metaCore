/**
 * @file stream.hpp
 * @brief This header file defines the vstream class, which provides stream-like operations for a vector of type T.
 * The vstream class allows for easy insertion and extraction of elements, as well as various utility functions to manage the underlying vector.
 * Additionally, it includes the benchmark_stream and test_stream classes for benchmarking function execution time and aggregating boolean test results with exception handling, respectively.
 * The stream_t, stream_tp, stream__tp, and stream__t_p classes provide safe execution of function objects with built-in error handling.
 * @note All operations are designed to be noexcept where applicable, ensuring that exceptions are handled gracefully without propagating.
 * @author Ali Lafi
 * @date 2025 / 9 / 25
 * @details This file is part of the MetaCore library, which provides various utilities for C++ programming.
 * - vstream: A stream-like interface for managing a vector of type T, supporting insertion, extraction, and utility functions.
 * - benchmark_stream: A class for benchmarking function execution time with configurable time units and result printing.
 * - test_stream: A class for aggregating boolean test results with exception handling and statistics tracking.
 * - stream_t: A template class for safely executing function objects with built-in error handling.
 * - stream_tp: A template class for safely executing unary functions (T -> T) with built-in error handling.
 * - stream__tp: A template class for safely executing unary transformation functions (T2 -> T1) with built-in error handling.
 * - stream__t_p: A template class for safely executing binary functions (T2, T3 -> T1) with built-in error handling.
 * @note This file is intended to be included in C++ projects that require stream-like operations on vectors, benchmarking capabilities, and safe function execution with error handling.
 */

// std headers
#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <stdexcept>
#include <queue>
#include <type_traits>
#include <string>
#include <cerrno>
#include <stack>

#include "io.hpp"
#include "benchmark.hpp"
#include "UnitTest.hpp"

#pragma once
#ifndef METACORE___LITE_STREAM_HPP
#define METACORE___LITE_STREAM_HPP

namespace lite
{    
    /**
     * @class vstream
     * @brief A class that provides stream-like operations for a vector of type T.
     * This class allows for easy insertion and extraction of elements,
     * as well as various utility functions to manage the underlying vector.
     */
    template <typename T>
    class vstream
    {
    private:
        std::queue<std::vector<T>> vs;

    public:
        /** Default constructor */
        vstream() = default;
        
        /** Constructor from std::vector
         * @param vec The vector to initialize the stream with
         * @note This constructor copies the vector
         */
        vstream(const std::queue<std::vector<T>> &vec) noexcept : vs(vec) {}
        
        /** Constructor from rvalue std::vector
         * @param vec The vector to initialize the stream with
         * @note This constructor moves the vector
         */
        vstream(std::queue<std::vector<T>> &&vec) noexcept : vs(std::move(vec)) {}
        
        /**
         * Constructor from initializer list
         * @param il The initializer list to initialize the stream with
         * @note This constructor copies the elements from the initializer list
         */
        vstream(std::initializer_list<std::vector<T>> il) noexcept : vs(il) {}
        
        /**
         * Copy constructor
         * @param other The other vstream to copy from
         * @note This constructor copies the underlying vector
         */
        vstream(const vstream &other) noexcept : vs(other.vs) {}
        
        /**
         * Move constructor
         * @param other The other vstream to move from
         * @note This constructor moves the underlying vector
         */
        vstream(vstream &&other) noexcept : vs(std::move(other.vs)) {}
        
        /**
         * @brief Returns the number of elements in the vector.
         *
         * @return The current size of the vector.
         * @note This function does not throw exceptions.
         */
        size_t size() const noexcept { return vs.size(); }

        /**
         * @brief Checks whether the container is empty.
         *
         * @return true if the container contains no elements, false otherwise.
         * @note This function does not throw exceptions.
         */
        bool empty() const noexcept { return vs.empty(); }

        /**
         * @brief Removes all elements from the container.
         *
         * After calling this function, the container will be empty.
         * No exceptions are thrown.
         */
        void clear() noexcept { 
            while (!vs.empty())
                vs.pop();
        }

        /**
         * @brief Copy assignment operator for vstream.
         *
         * Assigns the contents of another vstream object to this one.
         * Performs a self-assignment check before copying the internal state.
         *
         * @param other The vstream object to copy from.
         * @return Reference to this vstream object.
         * @note This operator is marked noexcept.
         */
        vstream &operator=(const vstream &other) noexcept
        {
            if (this != &other)
                vs = other.vs;
            return *this;
        }

        /**
         * @brief Move assignment operator for the vstream class.
         *
         * Transfers ownership of resources from another vstream instance to this instance.
         * If the source and destination are not the same object, the internal stream (vs)
         * is moved from the source to this object, leaving the source in a valid but unspecified state.
         *
         * @param other The vstream instance to move from.
         * @return Reference to this vstream instance.
         */
        vstream &operator=(vstream &&other) noexcept
        {
            if (this != &other)
                vs = std::move(other.vs);
            return *this;
        }

        /**
         * @brief Assignment operator from std::vector.
         *
         * Assigns the contents of the given std::vector<T> to the internal vector 'vs'.
         *
         * @param vec The std::vector<T> whose contents will be copied.
         * @note This operation is noexcept.
         */
        void operator=(const std::queue<std::vector<T>> &vec) noexcept { vs = vec; }

        /**
         * @brief Move assignment operator from a std::vector<T>.
         *
         * Replaces the contents of the internal vector 'vs' with those of the given rvalue reference 'vec',
         * transferring ownership of the data without copying.
         *
         * @param vec Rvalue reference to a std::vector<T> whose contents will be moved.
         * @note This operation is noexcept and leaves 'vec' in a valid but unspecified state.
         */
        void operator=(std::queue<std::vector<T>> &&vec) noexcept { vs = std::move(vec); }

        /**
         * @brief Assignment operator for assigning an initializer list to the container.
         *
         * Replaces the contents of the container with the elements from the given initializer list.
         * This operation is noexcept.
         *
         * @param il The initializer list whose elements will be assigned to the container.
         */
        void operator=(std::initializer_list<std::vector<T>> il) noexcept { vs = il; }

        /**
         * @brief Inserts a value into the vector stream.
         *
         * This operator overload allows vectors of type T to be enqueued to the internal queue (vs)
         * using the stream insertion syntax.
         *
         * @param value The vector to be inserted into the queue stream.
         * @note This operation does not support chaining as it returns void.
         */
        void operator<<(const std::vector<T> &value) noexcept { vs.push(value); }

        /**
         * @brief Inserts a value into the vector stream using move semantics.
         *
         * This operator overload allows an rvalue reference of type std::vector<T> to be moved
         * into the internal queue (vs), which improves performance by avoiding unnecessary copies.
         *
         * @param value The rvalue reference to the vector to be inserted.
         * @note This operation does not support chaining as it returns void.
         */
        void operator<<(std::vector<T> &&value) noexcept { vs.push(std::move(value)); }

        /**
         * @brief Extracts the front element from the internal queue and assigns it to the provided value.
         *
         * This operator overload removes the front element from the internal queue `vs` (FIFO order)
         * and assigns it to `value` via move semantics.
         * If the queue is empty, it throws a `std::out_of_range` exception.
         *
         * @tparam T The type of the elements stored in the queue.
         * @param value Reference to the variable where the extracted vector will be stored.
         * @throws std::out_of_range if the internal queue is empty.
         */
        void operator>>(std::vector<T> &value)
        {
            if (!vs.empty())
            {
                value = std::move(vs.front());
                vs.pop();
            }
            else
                throw std::out_of_range("vstream is empty");
        }

        /** @brief Default destructor for vstream. */
        ~vstream() = default;
    };

    namespace function
    {
        #ifdef METACORE___LITE_BENCHMARK_HPP
        /**
         * @brief A template class for benchmarking function execution time.
         *       The benchmark_stream class allows users to measure the execution time
         *      of functions and optionally print the results.
         * @tparam print_result A boolean flag indicating whether to print
         *      the execution time for each test case.
         */
        template <bool print_result>
        class benchmark_stream
        {
        private:
            size_t count = 1;
            std::string s = "s";
            long long factor = 1;
            std::vector<float> time_v;
            std::vector<std::string> test_names;
            float min_time = std::numeric_limits<float>::max();
            float max_time = std::numeric_limits<float>::min();

        protected:
            /**
             * @brief Calculates the arithmetic mean of stored time values
             * @return Float value representing the average of all times in time_v
             *
             * Computes the average by summing all time values and dividing by the count of entries.
             * Returns 0.0f if the vector is empty.
             */
            float average()
            {
                float result = 0.0f;
                for (float time : time_v)
                    result += time;
                return result / time_v.size();
            }

        public:
            /**
             * @brief Constructor for benchmark_stream that sets time measurement units
             *
             * @param TFactor String representing the time unit to use. Valid values are:
             *                "s"  - seconds
             *                "ms" - milliseconds
             *                "us" - microseconds
             *                "ns" - nanoseconds
             *                "ps" - picoseconds
             *
             * @throws std::invalid_argument if TFactor is not one of the valid time units
             *
             * @details Sets the appropriate multiplication factor based on the time unit:
             *          s  = 10^0  = 1
             *          ms = 10^3  = 1,000
             *          us = 10^6  = 1,000,000
             *          ns = 10^9  = 1,000,000,000
             *          ps = 10^12 = 1,000,000,000,000
             */
            benchmark_stream(std::string TFactor)
            {
                if (TFactor == "s")
                {
                    factor = 1;
                    s = "s";
                }
                else if (TFactor == "ms")
                {
                    factor = std::pow(10, 3);
                    s = TFactor;
                }
                else if (TFactor == "us")
                {
                    factor = std::pow(10, 6);
                    s = TFactor;
                }
                else if (TFactor == "ns")
                {
                    factor = std::pow(10, 9);
                    s = TFactor;
                }
                else if (TFactor == "ps")
                {
                    factor = std::pow(10, 12);
                    s = TFactor;
                }
                else
                    throw std::invalid_argument("The size of the time is not defind");
            }

            /**
             * @brief Constructor for benchmark_stream that sets time unit scaling and suffix
             * @param n Power of 10 to scale time measurements (default = 3)
             *
             * Sets the scaling factor as 10^n and corresponding time unit suffix:
             * - n=1: seconds (s)
             * - n=3: milliseconds (ms)
             * - n=6: microseconds (us)
             * - n=9: nanoseconds (ns)
             * - n=12: picoseconds (ps)
             * - other: custom (xs)
             */
            benchmark_stream(short n = 3)
            {
                factor = std::pow(10, n);
                if (n == 1)
                    s = "s";
                else if (n == 3)
                    s = "ms";
                else if (n == 6)
                    s = "us";
                else if (n == 9)
                    s = "ns";
                else if (n == 12)
                    s = "ps";
                else
                    s = "xs";
            }

            /**
             * @brief Overloaded stream operator to benchmark and record execution time of a function
             * @param fx Function to benchmark, must be callable and return bool
             * @details
             * - Executes the given function and records its execution time
             * - If print_result is enabled, prints the execution time for the test
             * - Increments internal test counter
             * - Time values are stored in time_v vector
             * - Results are printed with test number and scaled time (factor * measured_time)
             * @throws noexcept This function does not throw exceptions
             */
            void operator<<(std::function<bool()> fx) noexcept
            {
                time_v.push_back(benchmark::execution_time<bool>(fx));
                float current_time = factor * time_v[count - 1];
                min_time = std::min(min_time, current_time);
                max_time = std::max(max_time, current_time);
                if (print_result)
                     io::println(
                        "execution time for unit test " +
                        std::to_string(count) + ": " +
                        std::to_string(current_time) + s);
                count++;
            }

            /// @brief Overloaded stream operator to retrieve average execution time
            /// @param value Reference to float variable to store average execution time
            void operator>>(float &value) noexcept { value = factor * average(); }

            /**
             * @brief Retrieves the minimum recorded execution time
             * @return Minimum time in the specified unit
             */
            float get_min_time() const noexcept { return min_time; }

            /**
             * @brief Retrieves the maximum recorded execution time
             * @return Maximum time in the specified unit
             */
            float get_max_time() const noexcept { return max_time; }

            /**
             * @brief Retrieves the average execution time
             * @return Average time in the specified unit
             */
            float get_average_time() const noexcept { return factor * average(); }

            /**
             * @brief Retrieves the total number of benchmarked tests
             * @return Number of test cases executed
             */
            size_t get_test_count() const noexcept { return count - 1; }

            /**
             * @brief Clears all benchmark records and resets statistics
             */
            void clear_statistics() noexcept
            {
                time_v.clear();
                test_names.clear();
                count = 1;
                min_time = std::numeric_limits<float>::max();
                max_time = std::numeric_limits<float>::min();
            }

            /**
             * @brief Prints a complete benchmark summary with statistics
             */
            void print_summary() const noexcept
            {
                if (time_v.empty())
                {
                    io::println("No benchmark data available");
                    return;
                }
                io::println("=== Benchmark Summary ===");
                io::println("Total tests: " + std::to_string(time_v.size()));
                io::println("Average time: " + std::to_string(get_average_time()) + s);
                io::println("Min time: " + std::to_string(min_time) + s);
                io::println("Max time: " + std::to_string(max_time) + s);
            }
        };
        #endif // METACORE___LITE_BENCHMARK_HPP

        #ifdef METACORE___LITE_UNITTEST_HPP
        /**
         * @brief A class that aggregates boolean test results with exception handling.
         */
        class test_stream
        {
        private:
            std::vector<TEST> container;
            bool result_ts = true;
            size_t total_tests = 0;
            size_t passed_tests = 0;
            size_t failed_tests = 0;
            std::vector<std::string> error_log;

        public:
            test_stream() = default;

            /**
             * @brief Overloaded operator<< to handle boolean function execution with exception handling
             *
             * This operator takes a function object that returns a boolean value and executes it.
             * The result is combined with the existing result_ts using logical AND operation.
             * If the function is not marked noexcept, it wraps the execution in a try-catch block
             * to handle various types of exceptions.
             *
             * @param fx A std::function object that returns bool and takes no parameters
             * @noexcept This operator itself is marked noexcept, though the contained function may throw
             *
             * Exception handling includes:
             * - std::invalid_argument
             * - std::length_error
             * - std::exception
             * - const char* messages
             * - Any other unhandled exceptions
             *
             * On any exception, result_ts is set to false and an error message is output to std::cerr
             */
            void operator<<(std::function<bool()> fx) noexcept
            {
                total_tests++;
                bool test_result = false;
                if (std::is_nothrow_invocable_r_v<bool, std::function<bool()>, bool>)
                {
                    test_result = fx();
                    result_ts &= test_result;
                }
                else
                {
                    try
                    {
                        test_result = fx();
                        result_ts &= test_result;
                    }
                    catch (const std::invalid_argument &e)
                    {
                        std::string err_msg = "invalid argument: " + std::string(e.what());
                        std::cerr << err_msg << std::endl;
                        error_log.push_back(err_msg);
                        test_result = false;
                        result_ts = false;
                    }
                    catch (const std::length_error &e)
                    {
                        std::string err_msg = "length error: " + std::string(e.what());
                        std::cerr << err_msg << std::endl;
                        error_log.push_back(err_msg);
                        test_result = false;
                        result_ts = false;
                    }
                    catch (const std::exception &e)
                    {
                        std::string err_msg = "Exception: " + std::string(e.what());
                        std::cerr << err_msg << "\n";
                        error_log.push_back(err_msg);
                        test_result = false;
                        result_ts = false;
                    }
                    catch (const char *msg)
                    {
                        std::string err_msg = "Error: " + std::string(msg);
                        std::cerr << err_msg << "\n";
                        error_log.push_back(err_msg);
                        test_result = false;
                        result_ts = false;
                    }
                    catch (...)
                    {
                        std::string err_msg = "Unknown error occurred";
                        std::cerr << err_msg << "\n";
                        error_log.push_back(err_msg);
                        test_result = false;
                        result_ts = false;
                    }
                }
                if (test_result)
                    passed_tests++;
                else
                    failed_tests++;
                container.push_back(TEST{fx()});
            }

            void operator<<(std::function<TEST()> fx) noexcept
            {
                total_tests++;
                bool test_result = false;
                if (std::is_nothrow_invocable_r_v<bool, std::function<bool()>, bool>)
                {
                    test_result = fx().get();
                    result_ts &= test_result;
                }
                else
                {
                    try
                    {
                        test_result = fx().get();
                        result_ts &= test_result;
                    }
                    catch (const std::invalid_argument &e)
                    {
                        std::string err_msg = "invalid argument: " + std::string(e.what());
                        std::cerr << err_msg << std::endl;
                        error_log.push_back(err_msg);
                        test_result = false;
                        result_ts = false;
                    }
                    catch (const std::length_error &e)
                    {
                        std::string err_msg = "length error: " + std::string(e.what());
                        std::cerr << err_msg << std::endl;
                        error_log.push_back(err_msg);
                        test_result = false;
                        result_ts = false;
                    }
                    catch (const std::exception &e)
                    {
                        std::string err_msg = "Exception: " + std::string(e.what());
                        std::cerr << err_msg << "\n";
                        error_log.push_back(err_msg);
                        test_result = false;
                        result_ts = false;
                    }
                    catch (const char *msg)
                    {
                        std::string err_msg = "Error: " + std::string(msg);
                        std::cerr << err_msg << "\n";
                        error_log.push_back(err_msg);
                        test_result = false;
                        result_ts = false;
                    }
                    catch (...)
                    {
                        std::string err_msg = "Unknown error occurred";
                        std::cerr << err_msg << "\n";
                        error_log.push_back(err_msg);
                        test_result = false;
                        result_ts = false;
                    }
                }
                if (test_result)
                    passed_tests++;
                else
                    failed_tests++;
                container.push_back(fx());
            }

            void operator<<(TEST& testResult) noexcept {
                total_tests++;
                if(testResult.get()) {
                    passed_tests++;
                } else {
                    failed_tests++;
                }
                result_ts &= testResult.get();
                container.push_back(testResult);
            }

            /// @brief Overloaded operator>> to retrieve the aggregated test result
            /// @param value Reference to a boolean variable to store the aggregated result
            void operator>>(bool &value) noexcept { value = result_ts; }

            void operator>>(TEST& value) noexcept {
                value = TEST{"stream",
                        "the result of all tests in test stream",
                        result_ts};
            }

            TEST operator[](size_t index) noexcept {
                return container[index];
            }

            /**
             * @brief Retrieves the total number of tests executed
             * @return Total count of tests
             */
            size_t get_total_tests() const noexcept { return total_tests; }

            /**
             * @brief Retrieves the number of passed tests
             * @return Count of tests that passed
             */
            size_t get_passed_tests() const noexcept { return passed_tests; }

            /**
             * @brief Retrieves the number of failed tests
             * @return Count of tests that failed
             */
            size_t get_failed_tests() const noexcept { return failed_tests; }

            /**
             * @brief Retrieves the success rate percentage
             * @return Success rate (0.0 to 100.0)
             */
            float get_success_rate() const noexcept
            {
                if (total_tests == 0)
                    return 0.0f;
                return (passed_tests * 100.0f) / total_tests;
            }

            /**
             * @brief Retrieves the error log
             * @return Vector containing all error messages
             */
            const std::vector<std::string> &get_error_log() const noexcept { return error_log; }

            /**
             * @brief Clears all test statistics and error log
             */
            void reset_statistics() noexcept
            {
                total_tests = 0;
                passed_tests = 0;
                failed_tests = 0;
                error_log.clear();
                container.clear();
                result_ts = true;
            }

            std::vector<size_t> findIndex(bool isFailed) noexcept {
                std::vector<size_t> result;
                for(size_t i = 0; i < container.size(); i++) {
                    if(!isFailed && container[i].get()) {
                        result.push_back(i);
                    } else if(isFailed && !container[i].get()) {
                        result.push_back(i);
                    }
                    return result;
                }
            }

            void find(bool isFailed) noexcept {
                for(size_t i = 0; i < container.size(); i++) {
                    if(!isFailed && container[i].get()) {
                        io::print_test(container[i].get(true), 
                        container[i].get(false), i, container[i].get());
                    } else if(isFailed && !container[i].get()) {
                        io::print_test(container[i].get(true),
                        container[i].get(false), i, container[i].get());
                    }
                }
            }

            /**
             * @brief Prints a complete test summary with statistics
             */
            void print_summary() const noexcept
            {
                io::println("=== Test Summary ===");
                io::println("Total tests: " + std::to_string(total_tests));
                io::println("Passed: " + std::to_string(passed_tests));
                io::println("Failed: " + std::to_string(failed_tests));
                io::println("Success rate: " + std::to_string(get_success_rate()) + "%");
                if (!error_log.empty())
                {
                    io::println("=== Error Log ===");
                    for (size_t i = 0; i < error_log.size(); ++i)
                        io::println("[" + std::to_string(i + 1) + "] " + error_log[i]);
                }
            }
        };
        #endif // METACORE___LITE_UNITTEST_HPP
        
        /**
         * @brief A template class that wraps a function object and provides
         *        safe execution with built-in error handling.
         *
         * The stream_t class acts as a minimal stream-like container for
         * function objects (std::function<T()>). It allows storing a function,
         * retrieving it, and executing it with exception handling.
         *
         * @tparam T The return type of the function object.
         */
        template <typename T, bool immediate_run>
        class stream_t
        {
        private:
            /**
             * @brief Internal function storage.
             *
             * This holds the function object that will be executed when
             * handler() or run_test() is called.
             */
            std::function<T()> f;

        protected:
            /**
             * @brief Executes the stored function with exception handling.
             *
             * This function runs the stored function object `f()` and
             * catches common exceptions:
             * - std::invalid_argument
             * - std::length_error
             * - std::exception
             * - const char* (C-style error messages)
             *
             * All errors are reported to std::cerr.
             *
             * @note This method is intended for internal use and is
             *       exposed through run_test().
             */
            void handler() const noexcept
            {
                try
                {
                    f();
                }
                catch (const std::invalid_argument &e)
                {
                    std::cerr << "invalid argument: " << e.what() << std::endl;
                }
                catch (const std::length_error &e)
                {
                    std::cerr << "length error: " << e.what() << std::endl;
                }
                catch (const std::exception &e)
                {
                    std::cerr << "Exception: " << e.what() << "\n";
                }
                catch (const char *msg)
                {
                    std::cerr << "Error: " << msg << "\n";
                }
            }

        public:
            stream_t() = default;

            /**
             * @brief Assigns a new function to the stream.
             *
             * Example usage:
             * @code
             * stream_t<int> s;
             * s << []() -> int { return 42; };
             * @endcode
             *
             * @param fx The function object to be stored.
             */
            void operator<<(std::function<T()> fx) noexcept
            {
                f = fx;
                if (immediate_run)
                    handler();
            }

            /**
             * @brief Extracts the stored function into another std::function.
             *
             * Example usage:
             * @code
             * std::function<int()> func;
             * s >> func; // func now holds the stored function
             * @endcode
             *
             * @param fx Reference to a function object where the stored function will be copied.
             */
            void operator>>(std::function<T()> &fx) noexcept { fx = f; }
            
            /**
             * @brief Executes the stored function safely.
             *
             * This method runs the stored function using handler(),
             * which ensures that common exceptions are caught and
             * reported instead of propagating.
             *
             * Example usage:
             * @code
             * s.run_test();
             * @endcode
             */
            void run_test() const noexcept { handler(); }
        };

        /**
         * @brief A template class that wraps a unary function (T -> T)
         *        and provides safe execution with built-in error handling.
         *
         * The stream_tp class stores a function of type std::function<T(T)>,
         * allowing input transformation and safe execution with exception handling.
         *
         * @tparam T The input and output type of the function object.
         */
        template <typename T>
        class stream_tp
        {
        private:
            /**
             * @brief Internal function storage.
             *
             * This holds the unary function (T -> T) that will be executed
             * when handler() or run_test() is called.
             */
            std::function<T(T)> f;

        protected:
            /**
             * @brief Executes the stored function with the given input and
             *        provides exception handling.
             *
             * This function runs the stored function `f(input)` and catches:
             * - std::invalid_argument
             * - std::length_error
             * - std::exception
             * - const char* (C-style error messages)
             *
             * All errors are reported to std::cerr.
             *
             * @param input The input value passed to the stored function.
             */
            void handler(const T &input) const noexcept
            {
                try
                {
                    f(input);
                }
                catch (const std::invalid_argument &e)
                {
                    std::cerr << "invalid argument: " << e.what() << std::endl;
                }
                catch (const std::length_error &e)
                {
                    std::cerr << "length error: " << e.what() << std::endl;
                }
                catch (const std::exception &e)
                {
                    std::cerr << "Exception: " << e.what() << "\n";
                }
                catch (const char *msg)
                {
                    std::cerr << "Error: " << msg << "\n";
                }
            }

        public:
            stream_tp() = default;

            /**
             * @brief Assigns a new unary function to the stream.
             *
             * Example usage:
             * @code
             * stream_tp<int> s;
             * s << [](int x) { return x * x; }; // stores a square function
             * @endcode
             *
             * @param fx The function object to be stored.
             */
            void operator<<(std::function<T(T)> fx) noexcept { f = fx; }
            
            /**
             * @brief Extracts the stored function into another std::function.
             *
             * Example usage:
             * @code
             * std::function<int(int)> func;
             * s >> func; // func now holds the stored function
             * @endcode
             *
             * @param fx Reference to a function object where the stored function will be copied.
             */
            void operator>>(std::function<T(T)> &fx) noexcept { fx = f; }
            
            /**
             * @brief Executes the stored function with an lvalue reference input.
             *
             * Example usage:
             * @code
             * int value = 5;
             * s.run_test(value); // safely runs f(value)
             * @endcode
             *
             * @param value Reference to the input value.
             */
            void run_test(T &value) const noexcept { handler(value); }
            
            /**
             * @brief Executes the stored function with an rvalue input.
             *
             * Example usage:
             * @code
             * s.run_test(10); // safely runs f(10)
             * @endcode
             *
             * @param value Rvalue reference to the input value.
             */
            void run_test(T &&value) const noexcept { handler(value); }
        };

        /**
         * @brief A template class that wraps a unary transformation function (T2 -> T1)
         *        and provides safe execution with built-in error handling.
         *
         * The stream__tp class stores a function of type std::function<T1(T2)>,
         * allowing input of type T2 to be transformed into output of type T1.
         * It also provides exception handling for common errors.
         *
         * @tparam T1 The return type of the stored function.
         * @tparam T2 The input type of the stored function.
         */
        template <typename T1, typename T2>
        class stream__tp
        {
        private:
            /**
             * @brief Internal function storage.
             *
             * Holds the unary function (T2 -> T1) that will be executed
             * when handler() or run_test() is called.
             */
            std::function<T1(T2)> f;

        protected:
            /**
             * @brief Executes the stored function with the given input and
             *        provides exception handling.
             *
             * This function runs the stored function `f(input2)` and catches:
             * - std::invalid_argument
             * - std::length_error
             * - std::exception
             * - const char* (C-style error messages)
             *
             * All errors are reported to std::cerr.
             *
             * @param input2 The input value passed to the stored function.
             *
             * @note The return value of the function is currently ignored.
             *       Use run_test() or modify handler() to return the result if needed.
             */
            void handler(const T2 &input2)
            {
                try
                {
                    f(input2);
                }
                catch (const std::invalid_argument &e)
                {
                    std::cerr << "invalid argument: " << e.what() << std::endl;
                }
                catch (const std::length_error &e)
                {
                    std::cerr << "length error: " << e.what() << std::endl;
                }
                catch (const std::exception &e)
                {
                    std::cerr << "Exception: " << e.what() << "\n";
                }
                catch (const char *msg)
                {
                    std::cerr << "Error: " << msg << "\n";
                }
            }

        public:
            stream__tp() = default;

            /**
             * @brief Assigns a new unary transformation function to the stream.
             *
             * Example usage:
             * @code
             * stream__tp<int, double> s;
             * s << [](double x) { return static_cast<int>(x * 2); };
             * @endcode
             *
             * @param fx The function object to be stored.
             */
            void operator<<(std::function<T1(T2)> fx) noexcept { f = fx; }
           
            /**
             * @brief Extracts the stored function into another std::function.
             *
             * Example usage:
             * @code
             * std::function<int(double)> func;
             * s >> func; // func now holds the stored function
             * @endcode
             *
             * @param fx Reference to a function object where the stored function will be copied.
             */
            void operator>>(std::function<T1(T2)> &fx) noexcept { fx = f; }
            
            /**
             * @brief Executes the stored function safely with a given input.
             *
             * Example usage:
             * @code
             * double d = 3.14;
             * s.run_test(d); // safely runs f(d)
             * @endcode
             *
             * @param value2 Input value of type T2 passed to the stored function.
             *
             * @note The return value of the stored function is ignored.
             */
            void run_test(const T2 &value2) { handler(value2); }
        };

        /**
         * @brief A template class that wraps a binary function (T2, T3 -> T1)
         *        and provides safe execution with built-in error handling.
         *
         * The stream__t_p class stores a function of type std::function<T1(T2, T3)>,
         * allowing transformation of two inputs (T2 and T3) into one output (T1).
         * It also provides exception handling for common errors.
         *
         * @tparam T1 The return type of the stored function.
         * @tparam T2 The first input type of the stored function.
         * @tparam T3 The second input type of the stored function.
         */
        template <typename T1, typename T2, typename T3>
        class stream__t_p
        {
        private:
            /**
             * @brief Internal function storage.
             *
             * Holds the binary function (T2, T3 -> T1) that will be executed
             * when handler() or run_test() is called.
             */
            std::function<T1(T2, T3)> f;

        protected:
            /**
             * @brief Executes the stored function with the given inputs and
             *        provides exception handling.
             *
             * This function runs the stored function `f(input2, input3)` and catches:
             * - std::invalid_argument
             * - std::length_error
             * - std::exception
             * - const char* (C-style error messages)
             *
             * All errors are reported to std::cerr.
             *
             * @param input2 The first input value.
             * @param input3 The second input value.
             *
             * @note The return value of the function is currently ignored.
             *       Use run_test() or modify handler() to return the result if needed.
             */
            void handler(const T2 &input2, const T3 &input3)
            {
                try
                {
                    f(input2, input3);
                }
                catch (const std::invalid_argument &e)
                {
                    std::cerr << "invalid argument: " << e.what() << std::endl;
                }
                catch (const std::length_error &e)
                {
                    std::cerr << "length error: " << e.what() << std::endl;
                }
                catch (const std::exception &e)
                {
                    std::cerr << "Exception: " << e.what() << "\n";
                }
                catch (const char *msg)
                {
                    std::cerr << "Error: " << msg << "\n";
                }
            }

        public:
            stream__t_p() = default;

            /**
             * @brief Assigns a new binary function to the stream.
             *
             * Example usage:
             * @code
             * stream__t_p<int, int, int> s;
             * s << [](int a, int b) { return a + b; }; // stores addition function
             * @endcode
             *
             * @param fx The function object to be stored.
             */
            void operator<<(std::function<T1(T2, T3)> fx) noexcept { f = fx; }
            
            /**
             * @brief Extracts the stored function into another std::function.
             *
             * Example usage:
             * @code
             * std::function<int(int,int)> func;
             * s >> func; // func now holds the stored function
             * @endcode
             *
             * @param fx Reference to a function object where the stored function will be copied.
             */
            void operator>>(std::function<T1(T2, T3)> &fx) noexcept { fx = f; }
            
            /**
             * @brief Executes the stored function safely with two inputs.
             *
             * Example usage:
             * @code
             * s.run_test(3, 4); // safely runs f(3, 4)
             * @endcode
             *
             * @param value2 First input argument.
             * @param value3 Second input argument.
             *
             * @note The return value of the stored function is ignored.
             */
            void run_test(const T2 &value2, const T3 &value3) { handler(value2, value3); }
        };
    }
}
#endif // METACORE___LITE_STREAM_HPP