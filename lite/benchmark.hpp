/**
 * @file benchmark.hpp
 * @brief A lightweight code execution timer and memory usage measurement utility.
 * @brief this library provides a lightweight code execution timer utility.
 * It includes the `code_timer` class, which can be used in two modes:
 * RAII mode (in_structure = true): Automatically starts timing upon construction and stops timing upon destruction, printing the duration in milliseconds.
 * Manual mode (in_structure = false): Requires explicit calls to start_time() and stop_time(), with get_duration() to retrieve the result.
 * Additionally, it provides several overloaded execution_time functions to measure the execution time of parameterless functions, single-argument functions, and two-argument functions with different types.
 * The library also includes functions to simulate various time complexities (O(1), O(log n), O(n), O(n log n), O(n^2), O(n^3)) and a function to estimate the time complexity of an algorithm based on measured execution time.
 * Finally, it offers functions to calculate the size of an object in bytes and to measure additional memory usage caused by executing functions.
 * Overall, this library is designed to help developers easily measure and analyze the performance of their code in terms of execution time and memory usage.
 * @author developed by: Ali Lafi.
 * @date 2025 / 9 / 25
 * @details This library is designed to help developers easily measure and analyze the performance of their code in terms of execution time and memory usage.
 * It provides a simple interface for timing code execution and estimating time complexity, making it a useful tool for benchmarking and optimizing C++ code.
 * The `code_timer` class can be used in both RAII and manual modes, allowing for flexible timing of code blocks or specific function calls.
 * The additional functions for simulating time complexities and measuring memory usage further enhance its utility for performance analysis. Overall,
 * - code_timer: A class for timing code execution, with both RAII and manual modes.
 * - execution_time: Overloaded functions to measure execution time of various types of callables.
 * - big_O1, logn, big_On, logn_n, big_On2, big_On3: Functions to simulate different time complexities.
 * - execution_type: A function to estimate the time complexity of an algorithm based on measured execution time.
 * - mata_data: A function to return the size of an object in bytes.
 * - heap_data: Overloaded functions to calculate the heap memory used by vectors and strings.
 * - function_data and function__data: Functions to measure additional memory usage caused by executing callables.
 * @note This library is designed for benchmarking code performance in C++23 and is part of
 * it's a part of the lite library, specifically within the lite module, and is intended for benchmarking code performance in C++23.
 */

// std headers
#include <chrono>
#include <thread>
#include <vector>
#include <functional>
#include <string>
#include <stdexcept>
#include <exception>
#include <windows.h>
#include <psapi.h>
#include <memory>
#include <algorithm>

#pragma once
#ifndef METACORE___LITE_BENCHMARK_HPP
#define METACORE___LITE_BENCHMARK_HPP

namespace lite
{
    namespace benchmark
    {
        /**
         * @brief A lightweight code execution timer utility.
         *
         * The `code_timer` class can be used to measure execution time in two modes:
         *
         * 1. **RAII mode (`in_structure = true`)**:
         *    - Starts timing automatically upon construction.
         *    - Stops timing and prints duration (in milliseconds) automatically
         *      upon destruction.
         *    - No need to call `start_time()` or `stop_time()`.
         *
         * 2. **Manual mode (`in_structure = false`)**:
         *    - Requires explicit calls to `start_time()` and `stop_time()`.
         *    - `get_duration()` can be used after `stop_time()` to retrieve the result.
         *
         * @tparam in_structure A compile-time boolean flag:
         *         - `true`: RAII automatic mode.
         *         - `false`: manual start/stop mode.
         *
         * Example usage:
         * @code
         * {
         *     // RAII mode: automatically times this scope
         *     code_timer<true> t;
         *     // some heavy code...
         * }
         * // Prints: time code duration: X ms
         *
         * {
         *     // Manual mode
         *     code_timer<false> t;
         *     t.start_time();
         *     // some heavy code...
         *     t.stop_time();
         *     std::cout << "manual duration: " << t.get_duration() * 1000.0f << " ms\n";
         * }
         * @endcode
         */
        template <bool in_structure>
        class code_timer
        {
        private:
            bool started = false;
            std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
            std::chrono::duration<float> mycodetime;

        public:
            /// @brief Constructor.
            /// Starts timing if RAII mode is enabled.
            code_timer()
            {
                if constexpr (in_structure)
                    start = std::chrono::high_resolution_clock::now();
            }
            
            /// @brief Returns the last measured duration in seconds.
            float get_duration() const noexcept
            {
                return mycodetime.count();
            }
            
            /// @brief Start timing (only valid in manual mode).
            void start_time()
            {
                if constexpr (in_structure)
                    throw std::logic_error("RAII mode: timer is running by default");
                start = std::chrono::high_resolution_clock::now();
                started = true;
            }

            /// @brief Stop timing (only valid in manual mode).
            void stop_time()
            {
                if constexpr (in_structure)
                    throw std::logic_error("RAII mode: timer is running by default");
                if (!started)
                    throw std::logic_error("Timer is not running");
                end = std::chrono::high_resolution_clock::now();
                mycodetime = end - start;
                started = false;
            }

            /// @brief Destructor.
            /// In RAII mode, prints the measured duration.
            ~code_timer()
            {
                if constexpr (in_structure)
                {
                    end = std::chrono::high_resolution_clock::now();
                    mycodetime = end - start;
                    float ms = mycodetime.count();
                }
            }
        };

        /**
         * @brief Measure the execution time of a parameterless function.
         *
         * This function takes a callable object (e.g., lambda, functor, function pointer)
         * with no parameters, executes it once, and measures the duration of its execution
         * using @ref code_timer in manual mode.
         *
         * @tparam T Return type of the function.
         * @param func A std::function<T()> representing the callable to measure.
         * @return Execution time in seconds as a floating-point value.
         *
         * @note The measured duration is in seconds. Multiply by 1000.0f if milliseconds
         *       are desired.
         *
         * Example usage:
         * @code
         * auto duration = execution_time<void>([]() {
         *     heavy_computation();
         * });
         * std::cout << "Duration: " << duration * 1000.0f << " ms\n";
         * @endcode
         */
        template <typename T>
        float execution_time(std::function<T()> func)
        {
            code_timer<false> timer;
            timer.start_time();
            func();
            timer.stop_time();
            return timer.get_duration();
        }

        /**
         * @brief Measure the execution time of a single-argument function.
         *
         * This overload takes a callable object that accepts a single argument,
         * executes it once with the provided value, and measures the duration
         * of its execution using @ref code_timer in manual mode.
         *
         * @tparam T The type of both the argument and return value of the function.
         * @param func A std::function<T(T)> representing the callable to measure.
         * @param arg The argument to pass to the function.
         * @return Execution time in seconds as a floating-point value.
         *
         * @note The measured duration is in seconds. Multiply by 1000.0f if milliseconds
         *       are desired.
         *
         * Example usage:
         * @code
         * auto duration = execution_time<int>([](int x) {
         *     return fibonacci(x);
         * }, 30);
         *
         * std::cout << "Duration: " << duration * 1000.0f << " ms\n";
         * @endcode
         */
        template <typename T>
        float execution_time(std::function<T(T)> func, T arg)
        {
            code_timer<false> timer;
            timer.start_time();
            func(arg);
            timer.stop_time();
            return timer.get_duration();
        }

        /**
         * @brief Measure the execution time of a function taking two arguments of the same type.
         *
         * Executes the provided callable with two arguments of type @p T2 and
         * measures its execution duration using @ref code_timer in manual mode.
         *
         * @tparam T1 Return type of the function.
         * @tparam T2 Argument type of the function (both arguments are the same type).
         * @param func A std::function<T1(T2, T2)> representing the callable to measure.
         * @param arg1 First argument to pass to the function.
         * @param arg2 Second argument to pass to the function.
         * @return Execution time in seconds as a floating-point value.
         *
         * @example
         * @code
         * auto duration = execution_time<int, int>([](int a, int b) {
         *     return a + b;
         * }, 10, 20);
         *
         * std::cout << "Duration: " << duration * 1000.0f << " ms\n";
         * @endcode
         */
        template <typename T1, typename T2>
        float execution_time(std::function<T1(T2, T2)> func, T2 arg1, T2 arg2)
        {
            code_timer<false> timer;
            timer.start_time();
            func(arg1, arg2);
            timer.stop_time();
            return timer.get_duration();
        }

        /**
         * @brief Measure the execution time of a single-argument function.
         *
         * Executes the provided callable with one argument of type @p T2 and
         * measures its execution duration using @ref code_timer in manual mode.
         *
         * @tparam T1 Return type of the function.
         * @tparam T2 Argument type of the function.
         * @param func A std::function<T1(T2)> representing the callable to measure.
         * @param arg Argument to pass to the function.
         * @return Execution time in seconds as a floating-point value.
         *
         * @example
         * @code
         * auto duration = execution__time<int, int>([](int x) {
         *     return x * x;
         * }, 42);
         *
         * std::cout << "Duration: " << duration * 1000.0f << " ms\n";
         * @endcode
         */
        template <typename T1, typename T2>
        float execution__time(std::function<T1(T2)> func, T2 arg)
        {
            code_timer<false> timer;
            timer.start_time();
            func(arg);
            timer.stop_time();
            return timer.get_duration();
        }

        /**
         * @brief Measure the execution time of a two-argument function with different types.
         *
         * Executes the provided callable with arguments of types @p T2 and @p T3,
         * and measures its execution duration using @ref code_timer in manual mode.
         *
         * @tparam T1 Return type of the function.
         * @tparam T2 Type of the first argument.
         * @tparam T3 Type of the second argument.
         * @param func A std::function<T1(T2, T3)> representing the callable to measure.
         * @param arg1 First argument to pass to the function.
         * @param arg2 Second argument to pass to the function.
         * @return Execution time in seconds as a floating-point value.
         *
         * @example
         * @code
         * auto duration = execution__time<std::string, int, double>(
         *     [](int a, double b) {
         *         return std::to_string(a + static_cast<int>(b));
         *     },
         *     5, 3.7
         * );
         *
         * std::cout << "Duration: " << duration * 1000.0f << " ms\n";
         * @endcode
         */
        template <typename T1, typename T2, typename T3>
        float execution__time(std::function<T1(T2, T3)> func, T2 arg1, T3 arg2)
        {
            code_timer<false> timer;
            timer.start_time();
            func(arg1, arg2);
            timer.stop_time();
            return timer.get_duration();
        }

        /**
         * @brief A collection of simple functions to simulate various time complexities.
         *
         * These functions are used internally to compare execution durations and
         * determine the likely time complexity of an algorithm.
         */
        /** Constant time complexity O(1). */
        void big_O1() noexcept { return; }

        /** Logarithmic time complexity O(log n).
         *  Sleeps for duration proportional to log(num). */
        void logn(size_t num, int n) noexcept
        {
            int iterations = 0;
            size_t temp = num;
            while (temp > 0) {
                temp /= n;
                iterations++;
            }
            std::this_thread::sleep_for(std::chrono::microseconds(iterations));
        }

        /** Linear time complexity O(n).
         *  Sleeps for duration proportional to num. */
        void big_On(size_t num) noexcept
        {
            std::this_thread::sleep_for(std::chrono::microseconds(num));
        }

        /** Linearithmic time complexity O(n log n).
         *  Sleeps for duration proportional to n * log(n). */
        void logn_n(size_t num, int n) noexcept
        {
            int log_iterations = 0;
            int temp = num;
            while (temp > 0) {
                temp /= n;
                log_iterations++;
            }
            size_t sleep_duration = num * log_iterations;
            std::this_thread::sleep_for(std::chrono::microseconds(sleep_duration));
        }

        /** Quadratic time complexity O(n^2). */
        void big_On2(size_t num) noexcept
        {
            size_t sleep_duration = num * num;
            std::this_thread::sleep_for(std::chrono::microseconds(sleep_duration));
        }

        /** Cubic time complexity O(n^3). */
        void big_On3(size_t num) noexcept
        {
            size_t sleep_duration = num * num * num;
            std::this_thread::sleep_for(std::chrono::microseconds(sleep_duration));
        }

        /**
         * @brief Estimate the time complexity of an algorithm based on measured execution time.
         *
         * This function compares the provided execution time against predefined
         * time benchmarks for standard complexities: O(1), O(log n), O(n), O(n log n),
         * O(n^2), O(n^3), and higher exponential or factorial complexities.
         *
         * @param time Measured execution time in seconds.
         * @param num Input size used in the benchmark functions.
         * @param logbase Base for logarithmic calculations (default: 10).
         * @return A string representing the estimated time complexity.
         *
         * @example
         * @code
         * float t = 0.0023f;  // measured execution time
         * int n = 1000;       // input size
         * std::string complexity = execution_type(t, n);
         * std::cout << "Estimated complexity: " << complexity << "\n";
         * @endcode
         */
        std::string execution_type(float time, int num, int logbase = 10) noexcept
        {
            std::function<void()> O1 = big_O1;
            std::function<void(size_t, int)> log_n = logn;
            std::function<void(size_t)> On = big_On;
            std::function<void(size_t, int)> log_n_n = logn_n;
            std::function<void(size_t)> On2 = big_On2;
            std::function<void(size_t)> On3 = big_On3;
            if (time < execution_time<void>(O1))
                return "O(1)";
            else if (time < execution__time<void, size_t, int>(log_n, static_cast<size_t>(num), logbase))
                return "O(log n)";
            else if (time < execution__time<void, size_t>(On, static_cast<size_t>(num)))
                return "O(n)";
            else if (time < execution__time<void, size_t, int>(log_n_n, static_cast<size_t>(num), logbase))
                return "O(n log n)";
            else if (time < execution__time<void, size_t>(On2, static_cast<size_t>(num)))
                return "O(n^2)";
            else if (time < execution__time<void, size_t>(On3, static_cast<size_t>(num)))
                return "O(n^3)";
            else
                return "O(2^n) or O(n!)";
        }

        /**
         * @brief Returns the size of an object in bytes.
         *
         * This function calculates the compile-time size of any object
         * using sizeof.
         *
         * @tparam T Type of the object.
         * @param object Reference to the object.
         * @return Size of the object in bytes.
         *
         * @note This only accounts for the object's immediate size in memory,
         *       not dynamically allocated data (heap).
         */
        template <typename T>
        constexpr size_t mata_data(T &object) noexcept { return sizeof(object); }

        /**
         * @brief Returns the heap memory used by a vector.
         *
         * Calculates the memory allocated on the heap for a std::vector
         * based on its capacity and element size.
         *
         * @tparam T Type of elements in the vector.
         * @param v Reference to the vector.
         * @return Heap memory in bytes.
         */
        template <typename T>
        constexpr size_t heap_data(const std::vector<T> &v) noexcept { return sizeof(T) * v.capacity(); }

        /**
         * @brief Returns the heap memory used by a 2D vector.
         *
         * Calculates the memory allocated on the heap for a std::vector of std::vector
         * based on its capacity and element size.
         *
         * @tparam T Type of elements in the inner vectors.
         * @param v2d Reference to the 2D vector.
         * @return Heap memory in bytes.
         */
        template <typename T>
        constexpr size_t heap_data(const std::vector<std::vector<T>> &v2d) noexcept
        {
            size_t result = 0;
            for (const std::vector<T> &v : v2d)
                result += heap_data(v);
            return result;
        }

        /**
         * @brief Returns the heap memory used by a 3D vector.
         *
         * Calculates the memory allocated on the heap for a std::vector of std::vector of std::vector
         * based on its capacity and element size.
         *
         * @tparam T Type of elements in the innermost vectors.
         * @param v3d Reference to the 3D vector.
         * @return Heap memory in bytes.
         */
        template <typename T>
        constexpr size_t heap_data(const std::vector<std::vector<std::vector<T>>> &v3d) noexcept
        {
            size_t result = 0;
            for (const std::vector<std::vector<T>> &v2d : v3d)
                for (const std::vector<T> &v : v2d)
                    result += heap_data(v);
            return result;
        }

        /**
         * @brief Returns the heap memory used by a std::string.
         *
         * Calculates the memory allocated on the heap based on the string's capacity.
         *
         * @param s Reference to the string.
         * @return Heap memory in bytes.
         */
        size_t heap_data(const std::string &s) noexcept { return sizeof(char) * s.capacity(); }

        /**
         * @brief Measures additional memory usage caused by executing a parameterless function.
         *
         * The function checks the process's working set before and after execution
         * and returns the difference in memory usage.
         *
         * @tparam T Return type of the function.
         * @param f Function to execute.
         * @return Additional memory used in bytes (0 if no increase).
         */
        template <typename T>
        size_t function_data(std::function<T()> f)
        {
            PROCESS_MEMORY_COUNTERS info1, info2;
            GetProcessMemoryInfo(GetCurrentProcess(), &info1, sizeof(info1));
            f();
            GetProcessMemoryInfo(GetCurrentProcess(), &info2, sizeof(info2));
            if (info2.WorkingSetSize > info1.WorkingSetSize)
                return info2.WorkingSetSize - info1.WorkingSetSize;
            else
                return 0;
        }

        /**
         * @brief Measures additional memory usage caused by executing a single-argument function.
         *
         * The function checks the process's working set before and after execution
         * and returns the difference in memory usage.
         *
         * @tparam T Return type and argument type of the function.
         * @param f Function to execute.
         * @param input Argument to pass to the function.
         * @return Additional memory used in bytes (0 if no increase).
         */
        template <typename T>
        size_t function_data(std::function<T(T)> f, T input)
        {
            PROCESS_MEMORY_COUNTERS info1, info2;
            GetProcessMemoryInfo(GetCurrentProcess(), &info1, sizeof(info1));
            f(input);
            GetProcessMemoryInfo(GetCurrentProcess(), &info2, sizeof(info2));
            if (info2.WorkingSetSize > info1.WorkingSetSize)
                return info2.WorkingSetSize - info1.WorkingSetSize;
            else
                return 0;
        }

        /**
         * @brief Measures additional memory usage caused by executing a single-argument function.
         *
         * Overload with template parameters T1 and T2.
         *
         * @tparam T1 Return type of the function.
         * @tparam T2 Argument type of the function.
         * @param f Function to execute.
         * @param input Argument to pass to the function.
         * @return Additional memory used in bytes (0 if no increase).
         */
        template <typename T1, typename T2>
        size_t function__data(std::function<T1(T2)> f, T2 input)
        {
            PROCESS_MEMORY_COUNTERS info1, info2;
            GetProcessMemoryInfo(GetCurrentProcess(), &info1, sizeof(info1));
            f(input);
            GetProcessMemoryInfo(GetCurrentProcess(), &info2, sizeof(info2));
            if (info2.WorkingSetSize > info1.WorkingSetSize)
                return info2.WorkingSetSize - info1.WorkingSetSize;
            else
                return 0;
        }

        /**
         * @brief Measures additional memory usage caused by executing a two-argument function.
         *
         * The function checks the process's working set before and after execution
         * and returns the difference in memory usage.
         *
         * @tparam T1 Return type of the function.
         * @tparam T2 Type of the first argument.
         * @tparam T3 Type of the second argument.
         * @param f Function to execute.
         * @param input1 First argument to pass to the function.
         * @param input2 Second argument to pass to the function.
         * @return Additional memory used in bytes (0 if no increase).
         */
        template <typename T1, typename T2, typename T3>
        size_t function__data(std::function<T1(T2, T3)> f, T2 input1, T3 input2)
        {
            PROCESS_MEMORY_COUNTERS info1, info2;
            GetProcessMemoryInfo(GetCurrentProcess(), &info1, sizeof(info1));
            f(input1, input2);
            GetProcessMemoryInfo(GetCurrentProcess(), &info2, sizeof(info2));
            if (info2.WorkingSetSize > info1.WorkingSetSize)
                return info2.WorkingSetSize - info1.WorkingSetSize;
            else
                return 0;
        }
    }
}

#endif // METACORE___LITE_BENCHMARK_HPP