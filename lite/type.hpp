/**
 * @file type.hpp
 * @brief This header file defines functions for getting type names as strings and checking types.
 * The functions are implemented in the corresponding CXXType.tpp file.
 * The type() function returns the name of the type as a string, while the is_*() functions check if a type matches a specific type.
 * The boolean_msg() function converts a boolean value to its string representation.
 * @note The type() function has a default implementation that returns "***" for any type that is not specialized.
 * @note The is_*() functions have a default implementation that returns false for any type that is not specialized.
 * @author Ali Lafi
 * @date 2024-06
 * @details This file is part of the MetaCore library, which provides various utilities for C++ programming.
 * - MetaCore/Lite/type.hpp: This header file declares the functions for type name retrieval and type checking.
 * - MetaCore/Lite/imp/type.tpp: This implementation
 * file defines the actual logic for the functions declared in CXXType.hpp, including specializations for common types and the boolean_msg() function.
 */

// std headers
#include <string>

#pragma once
#ifndef METACORE___LITE_TYPE_HPP
#define METACORE___LITE_TYPE_HPP

namespace lite
{
    /// @brief Get the type name as a string.
    /// @tparam T The type to get the name of.
    /// @return The name of the type as a string.
    template <typename T>
    constexpr std::string type() noexcept { return "unkown"; }

    /// @brief Specializations for common types.
    /// @return The name of the type as a string.
    template <>
    std::string type<bool>() noexcept { return "bool"; }

    /// @brief Specializations for common types.
    /// @return The name of the type as a string.
    template <>
    std::string type<char>() noexcept { return "char"; }

    /// @brief Specializations for common types.
    /// @return The name of the type as a string.
    template <>
    std::string type<short>() noexcept { return "short"; }

    /// @brief Specializations for common types.
    /// @return The name of the type as a string.
    template <>
    std::string type<int>() noexcept { return "int"; }

    /// @brief Specializations for common types.
    /// @return The name of the type as a string.
    template <>
    std::string type<long>() noexcept { return "long"; }

    /// @brief Specializations for common types.
    /// @return The name of the type as a string.
    template <>
    std::string type<long long>() noexcept { return "long long"; }

    /// @brief Specializations for common types.
    /// @return The name of the type as a string.
    template <>
    std::string type<float>() noexcept { return "float"; }

    /// @brief Specializations for common types.
    /// @return The name of the type as a string.
    template <>
    std::string type<double>() noexcept { return "double"; }

    /// @brief Specializations for common types.
    /// @return The name of the type as a string.
    template <>
    std::string type<long double>() noexcept { return "long double"; }

    /// @brief Specializations for common types.
    /// @return The name of the type as a string.
    template <>
    std::string type<std::string>() noexcept { return "std::string"; }

    /// @brief function to get type name from variable.
    /// @tparam T the type of the input.
    /// @param input The input variable.
    /// @return The name of the type as a string.
    template <typename T>
    constexpr std::string type(const T &input) noexcept { return "unkown"; }

    /// @brief Specializations for common types.
    /// @param input The input variable.
    /// @return The name of the type as a string.
    template <>
    std::string type<bool>(const bool &input) noexcept { return "bool"; }

    /// @brief Specializations for common types.
    /// @param input The input variable.
    /// @return The name of the type as a string.
    template <>
    std::string type<char>(const char &input) noexcept { return "char"; }

    /// @brief Specializations for common types.
    /// @param input The input variable.
    /// @return The name of the type as a string.
    template <>
    std::string type<short>(const short &input) noexcept { return "short"; }

    /// @brief Specializations for common types.
    /// @param input The input variable.
    /// @return The name of the type as a string.
    template <>
    std::string type<int>(const int &input) noexcept { return "int"; }

    /// @brief Specializations for common types.
    /// @param input The input variable.
    /// @return The name of the type as a string.
    template <>
    std::string type<long>(const long &input) noexcept { return "long"; }

    /// @brief Specializations for common types.
    /// @param input The input variable.
    /// @return The name of the type as a string.
    template <>
    std::string type<float>(const float &input) noexcept { return "float"; }

    /// @brief Specializations for common types.
    /// @param input The input variable.
    /// @return The name of the type as a string.
    template <>
    std::string type<double>(const double &input) noexcept { return "double"; }

    /// @brief Specializations for common types.
    /// @param input The input variable.
    /// @return The name of the type as a string.
    template <>
    std::string type<long double>(const long double &input) noexcept { return "long double"; }

    /// @brief Specializations for common types.
    /// @param input The input variable.
    /// @return The name of the type as a string.
    template <>
    std::string type<std::string>(const std::string &input) noexcept { return "std: string"; }

    /// @brief Type checking functions.
    /// @tparam T the type to check.
    /// @return true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_bool() noexcept { return false; }

    /// @brief Specialization for bool type.
    /// @return true since T is bool.
    template <>
    constexpr bool is_bool<bool>() noexcept { return true; }

    /// @brief Type checking functions.
    /// @tparam T the type to check.
    /// @return true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_bool(const T &input) noexcept { return false; }

    /// @brief Specialization for bool type.
    /// @param input The input variable.
    /// @return true since T is bool.
    template <>
    constexpr bool is_bool<bool>(const bool &input) noexcept { return true; }

    /// @brief Type checking functions.
    /// @tparam T the type to check.
    /// @return true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_char() noexcept { return false; }

    /// @brief specialization for char type.
    /// @return true since T is char.
    template <>
    constexpr bool is_char<char>() noexcept { return true; }

    /// @brief Type checking functions.
    /// @param input The input variable.
    /// @tparam T the type to check.
    /// @return true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_char(const T &input) noexcept { return false; }

    /// @brief specialization for char type.
    /// @param input The input variable.
    /// @return true since T is char.
    template <>
    constexpr bool is_char<char>(const char &input) noexcept { return true; }

    /// @brief Type checking functions.
    /// @tparam T the type to check.
    /// @return true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_short() noexcept { return false; }

    /// @brief specialization for short type.
    /// @return true since T is short.
    template <>
    constexpr bool is_short<short>() noexcept { return true; }

    /// @brief Type checking functions.
    /// @param input The input variable.
    /// @tparam T the type to check.
    /// @return true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_short(const T &input) noexcept { return false; }

    /// @brief specialization for short type.
    /// @param input The input variable.
    /// @return true since T is short.
    template <>
    constexpr bool is_short<short>(const short &input) noexcept { return true; }

    /// @brief Type checking functions.
    /// @tparam T type of to check.
    /// @return the true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_int() noexcept { return false; }

    /// @brief specialization for int type.
    /// @return true since T is int.
    template <>
    constexpr bool is_int<int>() noexcept { return true; }

    /// @brief Type checking functions.
    /// @tparam T type of to check.
    /// @param input The input variable.
    /// @return the true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_int(const T &input) noexcept { return false; }

    /// @brief specialization for int type.
    /// @param input The input variable.
    /// @return true since T is int.
    template <>
    constexpr bool is_int<int>(const int &input) noexcept { return true; }

    /// @brief Type checking functions.
    /// @tparam T type of to check.
    /// @return the true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_float() noexcept { return false; }

    /// @brief specialization for float type.
    /// @return true since T is float.
    template <>
    constexpr bool is_float<float>() noexcept { return true; }

    /// @brief Type checking functions.
    /// @tparam T type of to check.
    /// @param input The input variable.
    /// @return the true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_float(const T &input) noexcept { return false; }

    /// @brief Specialization for float type.
    /// @param input the input variable.
    /// @return true since T is float.
    template <>
    constexpr bool is_float<float>(const float &input) noexcept { return true; }

    /// @brief Type checking functions.
    /// @tparam T type of to check.
    /// @return the true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_double() noexcept { return false; }

    /// @brief Specialization for double type.
    /// @return true since T is double.
    template <>
    constexpr bool is_double<double>() noexcept { return true; }

    /// @brief Type checking functions.
    /// @tparam T type of to check.
    /// @param input The input variable.
    /// @return the true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_double(const T &input) noexcept { return false; }

    /// @brief Specialization for double type.
    /// @param input The input variable.
    /// @return true since T is double.
    template <>
    constexpr bool is_double<double>(const double &input) noexcept { return true; }

    /// @brief Type checking functions.
    /// @tparam T type of to check.
    /// @return the true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_string() noexcept { return false; }

    /// @brief Specialization for std::string type.
    /// @return true since T is std::string.
    template <>
    constexpr bool is_string<std::string>() noexcept { return true; }

    /// @brief Type checking functions.
    /// @tparam T type of to check.
    /// @param input The input variable.
    /// @return the true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_string(const T &input) noexcept { return false; }

    /// @brief Specialization for std::string type.
    /// @param input The input variable.
    /// @return true since T is std::string.
    template <>
    constexpr bool is_string<std::string>(const std::string &input) noexcept { return true; }

    /// @brief Type checking functions.
    /// @tparam T type of to check.
    /// @return the true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_numeric() noexcept { return false; }

    /// @brief Specializations for numeric types.
    /// @return true since T is a numeric type.
    template <>
    constexpr bool is_numeric<short>() noexcept { return true; }

    /// @brief Specializations for numeric types.
    /// @return true since T is a numeric type.
    template <>
    constexpr bool is_numeric<int>() noexcept { return true; }

    /// @brief Specializations for numeric types.
    /// @return true since T is a numeric type.
    template <>
    constexpr bool is_numeric<long>() noexcept { return true; }

    /// @brief Specializations for numeric types.
    /// @return true since T is a numeric type.
    template <>
    constexpr bool is_numeric<long long>() noexcept { return true; }

    /// @brief Specializations for numeric types.
    /// @return true since T is a numeric type.
    template <>
    constexpr bool is_numeric<float>() noexcept { return true; }

    /// @brief Specializations for numeric types.
    /// @return true since T is a numeric type.
    template <>
    constexpr bool is_numeric<double>() noexcept { return true; }

    /// @brief  Specializations for numeric types.
    /// @return true since T is a numeric type.
    template <>
    constexpr bool is_numeric<long double>() noexcept { return true; }

    /// @brief Type checking functions.
    /// @tparam T type of to check.
    /// @param input The input variable.
    /// @return the true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_numeric(const T &input) noexcept { return false; }

    /// @brief Specializations for numeric types.
    /// @param input The input variable.
    /// @return true since T is a numeric type.
    template <>
    constexpr bool is_numeric<short>(const short &input) noexcept { return true; }

    /// @brief Specializations for numeric types.
    /// @param input The input variable.
    /// @return true since T is a numeric type.
    template <>
    constexpr bool is_numeric<int>(const int &input) noexcept { return true; }

    /// @brief Specializations for numeric types.
    /// @param input The input variable.
    /// @return true since T is a numeric type.
    template <>
    constexpr bool is_numeric<long>(const long &input) noexcept { return true; }

    /// @brief Specializations for numeric types.
    /// @param input The input variable.
    /// @return true since T is a numeric type.
    template <>
    constexpr bool is_numeric<long long>(const long long &input) noexcept { return true; }

    /// @brief Specializations for numeric types.
    /// @param input The input variable.
    /// @return true since T is a numeric type.
    template <>
    constexpr bool is_numeric<float>(const float &input) noexcept { return true; }

    /// @brief Specializations for numeric types.
    /// @param input The input variable.
    /// @return true since T is a numeric type.
    template <>
    constexpr bool is_numeric<double>(const double &input) noexcept { return true; }

    /// @brief Specializations for numeric types.
    /// @param input The input variable.
    /// @return true since T is a numeric type.
    template <>
    constexpr bool is_numeric<long double>(const long double &input) noexcept { return true; }

    /// @brief Converts a boolean value to its string representation.
    /// @param value The boolean value to convert.
    /// @return The string representation of the boolean value.
    std::string boolean_msg(bool value) noexcept { return value ? "true" : "false"; }
}
#endif // METACORE___LITE_TYPE_HPP