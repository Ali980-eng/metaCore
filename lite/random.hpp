/**
 * @file random.hpp
 * @brief A collection of functions for generating random numbers, characters, and vectors, as well
 * as performing simple shift encryption on strings. These functions utilize the Mersenne Twister
 * algorithm for random number generation and provide both simple and complex encryption methods.
 * @note All functions are designed to be noexcept, ensuring they do not throw exceptions.
 * @details
 * - GRN: Generates a random integer within a specified range.
 * - SES: Encrypts a string by shifting all characters by the same randomly generated key.
 * - SEC: Encrypts a string by shifting each character by a different randomly generated key.
 * - GRC: Generates a random printable ASCII character.
 * - GRV: Generates vectors of random integers, with support for 1D, 2D, and 3D vectors.
 * - GRCV: Generates a vector of random printable ASCII characters.
 * - GRC2DV: Generates a 2D vector of random printable ASCII characters.
 * - GRC3DV: Generates a 3D vector of random printable ASCII characters.
 * @author Ali Lafi
 * @date 2025 / 9 / 25
 */

#if defined(__cpp_modules) && (__cplusplus >= 202302L)
    import std;
#else
    #include <vector>
    #include <string>
    #include <random>
#endif

#pragma once
#ifndef METACORE___LITE_RANDOM_HPP
#define METACORE___LITE_RANDOM_HPP

#ifdef METACORE___META_HPP
namespace meta {
#endif // METACORE___META_HPP
#ifdef METACORE___LITE_HPP
namespace lite {
#endif // METACORE___LITE_HPP

    // GRN: generate random number
    /// @brief Generates a random integer within the specified range using Mersenne Twister algorithm.
    /// @param start The lower bound of the range (inclusive).
    /// @param end The upper bound of the range (inclusive).
    /// @return A random integer between start and end (inclusive).
    /// @note Uses a static random generator initialized once per program execution.
    /// @noexcept Does not throw exceptions.
    int GRN(int start, int end) noexcept
    {
        static std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dis(start, end);
        return dis(gen);
    }

    #ifdef OPENUDT___STRING_STRING_FUNCTIONS_HPP
    // SES: shift encryption simplex
    /// @brief Encrypts a string by shifting all characters by a randomly generated key.
    /// @param input The input string to be encrypted.
    /// @param start The lower bound for the random shift key (inclusive).
    /// @param end The upper bound for the random shift key (inclusive).
    /// @param shift_key_container A vector to store the generated shift key.
    /// @return The encrypted string with all characters shifted by the same key.
    std::string SES(const std::string &input, int start, int end, std::vector<int> &shift_key_container) noexcept
    {
        int shift_key = GRN(start, end);
        shift_key_container.push_back(shift_key);
        return shift_string(input, shift_key);
    }

    // SEC: shift encryption complex
    /// @brief Encrypts a string by shifting each character by a different randomly generated key.
    /// @param input The input string to be encrypted.
    /// @param start The lower bound for the random shift keys (inclusive).
    /// @param end The upper bound for the random shift keys (inclusive).
    /// @param shift_key_container A vector to store the generated shift keys for each character.
    /// @return The encrypted string with each character shifted by its own key.
    std::string SEC(const std::string &input, int start, int end, std::vector<int> &shift_key_container) noexcept
    {
        std::string result;
        for (size_t i = 0; i < input.length(); i++)
        {
            int rnum = GRN(start, end);
            shift_key_container.push_back(rnum);
            result += shift_char(input[i], rnum);
        }
        return result;
    }
    #endif // OPENUDT___STRING_STRING_FUNCTIONS_HPP
    
    // GRC: generate random char
    /// @brief Generates a random printable ASCII character.
    /// @return A random character in the range of printable ASCII characters (32 to 126
    char GRC() noexcept { return static_cast<char>(GRN(32, 126)); }

    // GRV: generate random vector
    /// @brief Generates a vector of random integers within the specified range.
    /// @param ele_num The number of elements in the vector.
    /// @param start The lower bound of the range (inclusive).
    /// @param end The upper bound of the range (inclusive).
    /// @return A vector containing ele_num random integers between start and end (inclusive).
    std::vector<int> GRV(size_t ele_num, int start, int end) noexcept
    {
        std::vector<int> result;
        for (size_t i = 0; i < ele_num; i++)
            result.push_back(GRN(start, end));
        return result;
    }

    /// @brief Generates a 2D vector of random integers within the specified range.
    /// @param vec_num The number of vectors in the 2D vector.
    /// @param ele_num The number of elements in each vector.
    /// @param start The lower bound of the range (inclusive).
    /// @param end The upper bound of the range (inclusive).
    /// @return A 2D vector containing vec_num vectors, each with ele_num random integers between start and end (inclusive).
    std::vector<std::vector<int>> GRV(size_t vec_num, size_t ele_num, int start, int end) noexcept
    {
        std::vector<std::vector<int>> result;
        for (size_t i = 0; i < vec_num; i++)
            result.push_back(GRV(ele_num, start, end));
        return result;
    }

    /// @brief Generates a 3D vector of random integers within the specified range.
    /// @param vv_num The number of 2D vectors in the 3D vector
    /// @param vec_num The number of vectors in each 2D vector.
    /// @param ele_num The number of elements in each vector.
    /// @param start The lower bound of the range (inclusive).
    /// @param end The upper bound of the range (inclusive).
    /// @return A 3D vector containing vv_num 2D vectors, each with
    std::vector<std::vector<std::vector<int>>> GRV(size_t vv_num, size_t vec_num, size_t ele_num, int start, int end) noexcept
    {
        std::vector<std::vector<std::vector<int>>> result;
        for (size_t i = 0; i < vv_num; i++)
            result.push_back(GRV(vec_num, ele_num, start, end));
        return result;
    }

    #ifdef OPENUDT___VECTOR_VECTORFUNCTIONS_HPP
    // vector_cast: cast vector type
    // GRCV: generaterandom char vector
    /// @brief Generates a vector of random printable ASCII characters.
    /// @return A vector containing random characters in the range of printable ASCII characters (32 to
    std::vector<char> GRCV() noexcept { return vector_cast<char, int>(GRV(94, 32, 126)); }

    // GRC2DV: generate random char 2d vector
    /// @brief Generates a 2D vector of random printable ASCII characters.
    /// @return A 2D vector containing random characters in the range of printable ASCII characters
    std::vector<std::vector<char>> GRC2DV() noexcept { return vector_cast<char, int>(GRV(94, 94, 32, 126)); }

    // GRC3DV: generate random char 3d vector
    /// @brief Generates a 3D vector of random printable ASCII characters.
    /// @return A 3D vector containing random characters in the range of printable ASCII characters
    std::vector<std::vector<std::vector<char>>> GRC3DV() noexcept { return vector_cast<char, int>(GRV(94, 94, 94, 32, 126)); }
    #endif // OPENUDT___VECTOR_VECTORFUNCTIONS_HPP

#ifdef METACORE___LITE_HPP
}
#endif // METACORE___LITE_HPP
#ifdef METACORE___META_HPP
}
#endif // METACORE___META_HPP

#endif // METACORE___LITE_RANDOM_HPP