/**
 * @file file.hpp
 * @brief A simple text file manager class for creating, reading, appending, checking existence
 * @brief This library provides a simple text file manager class for creating, reading, appending, checking existence, and removing text files in a specified directory.
 * @author Ali Lafi.
 * @date 2025 / 9 / 25
 * @details This library provides a simple text file manager class for creating, reading, appending, checking existence, and removing text files in a specified directory.
 * The `txtfile_manager` class encapsulates these functionalities, allowing users to easily manage text files without dealing with low-level file handling operations.
 * It ensures that the specified directory exists and provides methods for common file operations, making it a convenient tool for handling text files in C++.
 * - txtfile_manager: A class for managing text files, including creating, reading, appending, checking existence, and removing files in a specified directory.
 * @brief A simple text file manager class for creating, reading, appending, checking existence, and removing text files in a specified directory.
 */

// std headers
#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_map>

#pragma once
#ifndef METACORE___ADVA_FILE_HPP
#define METACORE___ADVA_FILE_HPP

#ifdef METACORE___ADVA_HPP
namespace adva
{
#endif // METACORE___ADVA_HPP

    /// @brief A simple text file manager class for creating, reading, appending, checking existence, and removing text files in a specified directory.
    class file
    {
    private:
        std::filesystem::path directory;

    public:
        file() noexcept {
            directory = std::filesystem::current_path();
        }

        /**
         * @brief Constructs a txtfile_manager for managing text files in a specified directory.
         * @param dirPath The path to the directory where text files will be managed.
         */
        file(const std::string &dirPath) noexcept
        {
            directory = dirPath;
            if (!std::filesystem::exists(directory))
                std::filesystem::create_directories(directory);
        }

        /**
         * @brief Changes the directory where text files are managed.
         * @param dirPath The new path to the directory where text files will be managed.
         * @details This method changes the directory where text files are managed. If the new directory does not exist, it will be created. If the directory cannot be created (e.g., due to permissions issues), an exception may be thrown by the underlying filesystem library, which should be handled by the caller if necessary.
         */
        inline void change_directory(const std::string &dirPath) noexcept
        {
            directory = dirPath;
            if (!std::filesystem::exists(directory))
                std::filesystem::create_directories(directory);
        }

        /**
         * @brief Creates a new directory if it does not exist.
         * @param dirPath The path of the directory to create.
         * @details This method creates a new directory at the specified path if it does not already exist. If the directory already exists, this method does nothing. If the directory cannot be created (e.g., due to permissions issues), an exception may be thrown by the underlying filesystem library, which should be handled by the caller if necessary.
         * @note This method uses the C++17 `<filesystem>` library, which provides a convenient way to work with directories and files. It is important to ensure that the C++17 standard is enabled in your project to use this functionality.
         */
        inline void make_directory(const std::string &dirPath) noexcept
        {
            std::filesystem::create_directories(dirPath);
        }

        /**
         * @brief Creates a new text file.
         * @param filename The name of the file to create.
         * @throws std::runtime_error If the file cannot be created.
         * @details This method creates a new text file with the specified name in the managed directory. If the file already exists, it will be overwritten. If the file cannot be created (e.g., due to permissions issues), a runtime error is thrown with an appropriate message.
         */
        void create(const std::string &filename)
        {
            std::ofstream file(directory / filename);
            if (!file.is_open())
                throw std::runtime_error("Failed to create file: " + filename);
            file.close();
        }

        /**
         * @brief Appends content to an existing text file.
         * @param filename The name of the file to append to.
         * @param content The content to append.
         * @throws std::runtime_error If the file cannot be opened for appending.
         * @details This method appends the specified content to an existing text file. If the file does not exist, it will be created. If the file cannot be opened for appending (e.g., due to permissions issues), a runtime error is thrown with an appropriate message.
         */
        void append(const std::string &filename, const std::string &content)
        {
            std::ofstream file(directory / filename, std::ios::app);
            if (!file.is_open())
                throw std::runtime_error("Failed to open file for appending: " + filename);
            file << content << '\n';
            file.close();
        }

        /**
         * @brief Reads the contents of a text file.
         * @param filename The name of the file to read.
         * @return The contents of the file.
         * @throws std::runtime_error If the file cannot be opened for reading.
         * @details This method reads the contents of the specified text file and returns it as a string. If the file cannot be opened for reading (e.g., if it does not exist or due to permissions issues), a runtime error is thrown with an appropriate message.
         */
        std::string read(const std::string &filename)
        {
            std::ifstream file(directory / filename);
            if (!file.is_open())
                throw std::runtime_error("Failed to open file for reading: " + filename);
            std::string content, line;
            while (std::getline(file, line))
                content += line + '\n';
            file.close();
            return content;
        }

        /**
         * @brief Checks if a text file exists.
         * @param filename The name of the file to check.
         * @return True if the file exists, false otherwise.
         * @details This method checks if a text file with the specified name exists in the managed directory. It returns true if the file exists and false otherwise.
         */
        inline bool exists(const std::string &filename) noexcept
        {
            return std::filesystem::exists(directory / filename);
        }

        /**
         * @brief Removes a text file.
         * @param filename The name of the file to remove.
         * @throws std::runtime_error If the file cannot be removed.
         * @details This method removes the specified text file from the managed directory. If the file does not exist, a runtime error is thrown with an appropriate message.
         */
        inline void remove(const std::string &filename)
        {
            if (!std::filesystem::remove(directory / filename))
                throw std::runtime_error("Failed to remove file (maybe it doesn't exist): " + filename);
        }
    };

    /**
     * @namespace coding: c object data instruction native generator
     * @brief Helper namespace for generating and managing data in files.
     */
    namespace coding
    {
        /**
         * @brief Initializes a file with an include statement.
         * @param fileName The name of the file to initialize.
         * @details Creates or opens a file and adds the include directive for "SDT.h" at the beginning.
         */
        void set(const std::string &fileName)
        {
            std::fstream file(fileName, std::ios::in |
                                            std::ios::out |
                                            std::ios::app);
            if (!file.is_open())
            {
                file.open(fileName, std::ios::out);
                file.open(fileName, std::ios::in |
                                        std::ios::out | std::ios::app);
            }
            file << "#include " << "\"SDT.h\"\n";
            file.close();
        }

        /**
         * @brief Saves a char value to a file.
         * @param fileName The name of the file to save to.
         * @param varName The variable name for the data.
         * @param data The char data to save.
         * @details Appends a formatted cchar() declaration with the variable name and data to the file.
         */
        void save(const std::string &fileName,
                const std::string &varName,
                char data) noexcept
        {
            std::fstream file(fileName, std::ios::in |
                                            std::ios::out |
                                            std::ios::app);
            if (!file.is_open())
            {
                file.open(fileName, std::ios::out);
                file.open(fileName, std::ios::in |
                                        std::ios::out |
                                        std::ios::app);
            }
            file << "cchar(" << varName << ", \'"
                << std::string(1, data) << "\')\n";
            file.close();
        }

        /**
         * @brief Saves a short value to a file.
         * @param fileName The name of the file to save to.
         * @param varName The variable name for the data.
         * @param data The short data to save.
         * @details Appends a formatted cshort() declaration with the variable name and data to the file.
         */
        void save(const std::string &fileName, const std::string &varName, short data) noexcept
        {
            std::fstream file(fileName, std::ios::in |
                                            std::ios::out |
                                            std::ios::app);
            if (!file.is_open())
            {
                file.open(fileName, std::ios::out);
                file.open(fileName, std::ios::in |
                                        std::ios::out |
                                        std::ios::app);
            }
            file << "cshort(" << varName << ", " << std::to_string(data)
                << ")\n";
            file.close();
        }

        /**
         * @brief Saves an int value to a file.
         * @param fileName The name of the file to save to.
         * @param varName The variable name for the data.
         * @param data The int data to save.
         * @details Appends a formatted cint() declaration with the variable name and data to the file.
         */
        void save(const std::string &fileName, const std::string &varName, int data) noexcept
        {
            std::fstream file(fileName, std::ios::in |
                                            std::ios::out |
                                            std::ios::app);
            if (!file.is_open())
            {
                file.open(fileName, std::ios::out);
                file.open(fileName, std::ios::in |
                                        std::ios::out |
                                        std::ios::app);
            }
            file << "cint(" << varName << ", " << std::to_string(data) << ")\n";
            file.close();
        }

        /**
         * @brief Saves a float value to a file.
         * @param fileName The name of the file to save to.
         * @param varName The variable name for the data.
         * @param data The float data to save.
         * @details Appends a formatted cfloat() declaration with the variable name and data to the file.
         */
        void save(const std::string &fileName, const std::string &varName, float data) noexcept
        {
            std::fstream file(fileName, std::ios::in |
                                            std::ios::out |
                                            std::ios::app);
            if (!file.is_open())
            {
                file.open(fileName, std::ios::out);
                file.open(fileName, std::ios::in |
                                        std::ios::out |
                                        std::ios::app);
            }
            file << "cfloat(" << varName << ", "
                << std::to_string(data) << ")\n";
            file.close();
        }

        /**
         * @brief Saves a double value to a file.
         * @param fileName The name of the file to save to.
         * @param varName The variable name for the data.
         * @param data The double data to save.
         * @details Appends a formatted cdouble() declaration with the variable name and data to the file.
         */
        void save(const std::string &fileName, const std::string &varName, double data) noexcept
        {
            std::fstream file(fileName, std::ios::in | std::ios::out | std::ios::app);
            if (!file.is_open())
            {
                file.open(fileName, std::ios::out);
                file.open(fileName, std::ios::in | std::ios::out | std::ios::app);
            }
            file << "cdouble(" << varName << ", "
                << std::to_string(data) << ")\n";
            file.close();
        }

        /**
         * @brief Clears the contents of a file.
         * @param fileName The name of the file to clear.
         * @details Truncates the file, removing all existing content.
         */
        void clear(const std::string &fileName) noexcept
        {
            std::fstream file(fileName, std::ios::out | std::ios::trunc);
            if (!file.is_open())
                return;
            file.close();
        }
    }
#ifdef METACORE___ADVA_HPP
}
#endif // METACORE___ADVA_HPP

#endif // METACORE___LITE_FILE_HPP