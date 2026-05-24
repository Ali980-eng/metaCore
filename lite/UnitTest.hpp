/**
 * @file UnitTest.hpp
 * @brief A header file for a lightweight C++ unit testing framework.
 * This file defines a set of functions and structures for performing basic unit tests on functions, vectors, and other data types.
 * The framework provides utilities for comparing expected and actual values, printing test results, and managing test counts.
 * The functions are designed to be simple and easy to use, allowing developers to quickly write and run tests for their code.
 * The framework includes support for detailed output, customizable separators, and whitespace formatting to enhance the readability of test results.
 * The testing functions are implemented as templates to allow for flexibility in the types of data being tested, and they are marked as noexcept to ensure that they do not throw exceptions during execution.
 * The framework also includes functions for resetting test counts, making it easy to manage and organize tests across different categories.
 * Overall, this header provides a convenient and efficient way to perform unit testing in C++ projects, helping developers ensure the correctness and reliability of their code.
 * @note This framework is intended for use in C++23 projects and may utilize features specific to that standard.
 * @author Ali Lafi
 * @date 2025 / 9 / 25
 */

// local headers
#include "io.hpp"

// std headers
#include <string>
#include <memory>

#pragma once
#ifndef METACORE___LITE_UNITTEST_HPP
#define METACORE___LITE_UNITTEST_HPP

namespace lite
{
        
    class TEST
    {
    private:
        std::string name;
        std::string description;
        bool result;
    public:
        TEST() : name("default"), description("no description"), result(false) {};

        TEST(bool value) noexcept {
            name = "default";
            description = "no description";
            result = value;
        }
        
        TEST(const std::string& name) noexcept { 
            this->name = name;
            description = "no description";
            result = false;
        }
        
        TEST(const std::string& name, const std::string& description) noexcept {
            this->name = name;
            this->description = description;
            result = false;
        }
        
        TEST(const std::string& name, const std::string& description, bool result) noexcept {
            this->name = name;
            this->description = description;
            this->result = result;
        }

        TEST(const TEST& other) {
            name = other.name;
            description = other.description;
            result = other.result;
        }

        ~TEST() noexcept = default;

        constexpr void set(const std::string& name) noexcept {
            this->name = name;
        }

        constexpr void set(bool result) noexcept {
            this->result = result;
        }

        constexpr std::string get(bool isName) noexcept {
            return isName ? name : description;
        }

        constexpr bool get() noexcept {
            return result;
        }

        constexpr void operator=(bool result) noexcept {
            this->result = result;
        }

        constexpr bool operator==(bool value) noexcept {
            return result == value;
        }

        constexpr bool operator!=(bool value) noexcept {
            return result != value;
        }

        constexpr bool operator||(bool value) noexcept {
            return result || value;
        }

        constexpr bool operator&&(bool value) noexcept {
            return result && value;
        }

        constexpr bool operator^(bool value) noexcept {
            return result ^ value;
        }

        constexpr void operator|=(bool value) noexcept {
            result |= value;
        }

        constexpr void operator&=(bool value) noexcept {
            result &= value;
        }

        constexpr void operator^=(bool value) noexcept {
            result ^= value;
        }

        constexpr void operator=(const TEST& other) noexcept {
            name = other.name;
            description = other.description;
            result = other.result;
        }

        constexpr bool operator==(const TEST& value) noexcept {
            return result == value.result;
        }

        constexpr bool operator!=(const TEST& value) noexcept {
            return result != value.result;
        }

        constexpr bool operator||(const TEST& value) noexcept {
            return result || value.result;
        }

        constexpr bool operator&&(const TEST& value) noexcept {
            return result && value.result;
        }

        constexpr bool operator^(const TEST& value) noexcept {
            return result ^ value.result;
        }

        constexpr void operator|=(const TEST& value) noexcept {
            result |= value.result;
        }

        constexpr void operator&=(const TEST& value) noexcept {
            result &= value.result;
        }

        constexpr void operator^=(const TEST& value) noexcept {
            result ^= value.result;
        }

        constexpr bool operator[](const std::string& name) noexcept {
            if(name == this->name) return result;
            io::println_error("Name Error: Unknown name.");
            return bool();
        }
    };

    namespace test
    {
        /**
         * @brief Structure to keep track of test counts for different categories.
         *
         * This structure contains counters for various test categories:
         * - function: Number of function-related tests.
         * - vector: Number of vector-related tests.
         * - basic: Number of basic tests.
         *
         * The default value for each counter is 1.
         */
        struct count
        {
            size_t function = 0;
            size_t vector = 0;
            size_t basic = 0;
        } index;

        /**
         * @brief Returns a message indicating the result of a test.
         *
         * This function returns "Success" if the test_result is true,
         * otherwise it returns "Failed".
         *
         * @param test_result The result of the test (true for success, false for failure).
         * @return const char* A string message representing the test result.
         * @note This function is noexcept and guarantees not to throw exceptions.
         */
        const std::string test_message(bool test_result) noexcept
        {
            return test_result ? 
            "Success" : "Failed";
        }

        template <typename T>
        bool basic(T realvalue, T expvalue) noexcept
        {
            index.basic++;
            return realvalue == expvalue;
        }

        template <typename T>
        TEST basic(
            T realvalue, T expvalue,
            const std::string& name,
            const std::string& description) noexcept
        {
            index.basic++;
            return !(name.empty()) && !(description.empty()) ?
            TEST{name, description, realvalue == expvalue} :
            TEST{realvalue == expvalue};
        }

        template <typename T>
        bool vector(std::vector<T> real_v, std::vector<T> expected_v) noexcept
        {
            index.vector++;
            if (real_v.size() != expected_v.size()) {
                return false;
            }
            for (size_t i = 0; i < real_v.size(); i++) {
                if(real_v[i] != expected_v[j])
                    return false;
            }
            return true;
        }

        template <typename T>
        TEST vector(
            std::vector<T> real_v,
            std::vector<T> expected_v,
            const std::string& name,
            const std::string& description) noexcept
        {
            index.vector++;
            if (real_v.size() != expected_v.size()) {
                return !(name.empty()) && !(description.empty()) ? 
                TEST{name, description, false} : TEST{false};
            }
            for (size_t i = 0; i < real_v.size(); i++) {
                if(real_v[i] != expected_v[i]) {
                    return !(name.empty()) && !(description.empty()) ?
                    TEST{name, description, false} : TEST{false};
                }
            }
            return !(name.empty()) && !(description.empty()) ? 
            TEST{name, description, true} : TEST{true};
        }

        template <typename T>
        bool vector_2d(std::vector<std::vector<T>> real_2dv,
                       std::vector<std::vector<T>> expected_2dv) noexcept
        {
            index.vector++;
            if (real_2dv.size() != expected_2dv.size()) {
                return false;
            }
            for (size_t i = 0; i < real_2dv.size(); i++) {
                if(real_2dv[i].size() != expected_2dv[i].size()) {
                    return false;
                }
                for(size_t j = 0; j < real_2dv[i].size(); j++) {
                    if(real_2dv[i][j] != expected_2dv[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }

        template <typename T>
        TEST vector_2d(std::vector<std::vector<T>> real_2dv,
                       std::vector<std::vector<T>> expected_2dv,
                       const std::string& name,
                       const std::string& description) noexcept
        {
            index.vector++;
            if (real_2dv.size() != expected_2dv.size()) {
                return !(name.empty()) && !(description.empty()) ? 
                TEST{name, description, false} : TEST{false};
            }
            for (size_t i = 0; i < real_2dv.size(); i++) {
                if(real_2dv[i].size() != expected_2dv.size()) {
                    return !(name.empty()) && !(description.empty()) ? 
                    TEST{name, description, false} : TEST{false};
                }
                for(size_t j = 0; j < real_2dv[i].size(); j++) {
                    if(real_v[i] != expected_v[i]) {
                        return !(name.empty()) && !(description.empty()) ?
                        TEST{name, description, false} : TEST{false};
                    }
                }
            }
            return !(name.empty()) && !(description.empty()) ?
            TEST{name, description, false} : TEST{false};
        }

        template <typename T>
        bool vector_3d(const std::vector<std::vector<std::vector<T>>>& real_3dv,
                       const std::vector<std::vector<std::vector<T>>>& expected_3dv) noexcept
        {
            index.vector++;
            if (real_3dv.size() != expected_3dv.size()) {
                return false;
            }
            for (size_t i = 0; i < real_3dv.size(); i++) {
                if(real_3dv[i].size() != expected_3dv[j].size()) {
                    return false;
                }
                for(size_t j = 0; j < real_3dv[i].size(); j++) {
                    if(real_3dv[i][j].size() != expected_3dv[i][j].size()) {
                        return false;
                    }
                    for(size_t z = 0; z < real_3dv[i][j].size(); z++) {
                        if(real_3dv[i][j][z] != expected_3dv[i][j][z]) {
                            return false;
                        }
                    }
                }
            }
            return true;
        }

        template <typename T>
        TEST vector_3d(const std::vector<std::vector<std::vector<T>>>& real_3dv,
                       const std::vector<std::vector<std::vector<T>>>& expected_3dv,
                       const std::string& name, const std::string& description) noexcept
        {
            if (real_3dv.size() != expected_3dv.size()) {
                return !(name.empty()) && !(description.empty()) ? 
                TEST{name, description, false} : TEST{false};
            }
            for (size_t i = 0; i < real_3dv.size(); i++) {
                if(real_3dv[i].size() != expected_3dv[i].size()) {
                    return !(name.empty()) && !(description.empty()) ? 
                    TEST{name, description, false} : TEST{false};
                }
                for(size_t j = 0; j < real_3dv[i].size(); j++) {
                    if(real_3dv[i][j].size() != expected_3dv[i][j].size()) {
                        return !(name.empty()) && !(description.empty()) ? 
                        TEST{name, description, false} : TEST{false};
                    }
                    for(size_t z = 0; z < real_3dv[i][j].size(); z++) {
                        if(real_3dv[i][j][z] != expected_3dv[i][j][z]) {
                            return !(name.empty()) && !(description.empty()) ? 
                            TEST{name, description, false} : TEST{false};
                        }
                    }
                }
            }
            return !(name.empty()) && !(description.empty()) ? 
            TEST{name, description, false} : TEST{false};
        }

        template <typename T>
        bool function(std::function<T()> fx, T expected) noexcept
        {
            index.function++;
            return fx() == expected;
        }

        template <typename T>
        TEST function(std::function<T()> fx, T expected,
                    const std::string& name,
                    const std::string& description) noexcept
        {
            index.function++;
            return !(name.empty()) && !(description.empty()) ? 
            TEST{name, description, fx() == expected} :
            TEST{fx() == expected};
        }

        template <typename T>
        bool function(std::function<T(T)> fx, T value, T expected) noexcept
        {
            index.function++;
            return fx(value) == expected;
        }

        template <typename T>
        TEST function(std::function<T(T)> fx, T value, T expected,
                    const std::string& name,
                    const std::string& description) noexcept
        {
            index.function++;
            return !(name.empty()) && !(description.empty()) ? 
            TEST{name, description, fx(value) == expected} :
            TEST{fx(value) == expected};
        }

        template <typename T1, typename T2>
        bool function(std::function<T1(T2)> fx, T2 value, T1 expected) noexcept
        {
            index.function++;
            return fx(value) == expected;
        }

        template <typename T1, typename T2>
        TEST function(std::function<T1(T2)> fx, T2 value, T1 expected,
                    const std::string& name, const std::string& description) noexcept
        {
            index.function++;
            return !(name.empty()) && !(description.empty()) ? 
            TEST{name, description, fx(value) == expected} :
            TEST{fx(value) == expected};
        }

        template <typename T1, typename T2, typename T3>
        bool function(std::function<T1(T2, T3)> fx, T1 expected, T2 value1, T3 value2) noexcept
        {
            index.function++;
            return fx(value1, value2);
        }

        template <typename T1, typename T2, typename T3>
        TEST function(std::function<T1(T2, T3)> fx, T1 expected,
                    T2 value1, T3 value2, const std::string& name,
                    const std::string& description) noexcept
        {
            index.function++;
            return !(name.empty()) && !(description.empty()) ? 
            TEST{name, description, fx(value) == expected} :
            TEST{fx(value) == expected};
        }

        /**
         * @brief Resets the test count to its initial value.
         *
         * Sets the 'basic' member of the 'index' object to 1.
         * This function is constexpr and noexcept.
         */
        constexpr inline void reset_count() noexcept { index.basic = 1; }

        /**
         * @brief Resets the vector index counter to its initial value.
         *
         * This function sets the `index.vector` variable to 1, effectively resetting
         * any count or position tracking associated with vectors. It is marked as
         * `constexpr` and `noexcept`, ensuring compile-time evaluation and no exceptions.
         */
        constexpr inline void reset_vector_count() noexcept { index.vector = 1; }

        /**
         * @brief Resets the function count index to its initial value.
         *
         * This function sets the `function` member of the `index` object to 1.
         * It is marked as `constexpr` and `noexcept`, ensuring compile-time evaluation
         * and no exceptions thrown.
         */
        constexpr inline void reset_function_count() noexcept { index.function = 1; }

        /**
         * @brief Resets all internal counters to their initial state.
         *
         * This function calls reset_test_count(), reset_vector_count(), and reset_function_count()
         * to reset the respective counters. It is marked as constexpr and noexcept.
         */
        constexpr inline void reset_all_counts() noexcept
        {
            reset_count();
            reset_vector_count();
            reset_function_count();
        }
    };
}
#endif // METACORE___LITE_UNITTEST_HPP