
#include <stdbool.h>
#include <stdlib.h>

#ifndef METACORE___CGEN_MICROS_STRING_H
#define METACORE___CGEN_MICROS_STRING_H

    #define cstrptr char *

    #define cstr(name, sizeValue) \
        char name[sizeValue]

    static inline size_t length(const cstrptr value)
    {
        return (value != NULL) ? strlen(value) : 0;
    }

    static inline bool equal(const cstrptr value_1, const cstrptr value_2)
    {
        if (value_1 == NULL || value_2 == NULL)
        return false;
        return strcmp(value_1, value_2) == 0 ? true : false;
    }

    static inline cstrptr concatenate(cstrptr value_1, const cstrptr value_2)
    {
        if (value_1 == NULL || value_2 == NULL)
        return value_1;
        return strcat(value_1, value_2);
    }

    static inline bool is_empty(const cstrptr value)
    {
        return (value == NULL || strlen(value) == 0) ? true : false;
    }

    /**
     * @brief Clear string content by reallocating to empty string
     * @param value The string to clear
     * @return Pointer to cleared string or NULL if input is NULL
     * @note Properly handles memory reallocation for empty string
     */
    static void *cstr_empty(cstrptr value)
    {
        if (value == NULL)
        return NULL;
        
        // Free old memory and allocate fresh 1 byte for empty string
        char *temp = (char *)malloc(1);
        if (temp != NULL) {
        temp[0] = '\0';
        free(value);
        return temp;
        }
        return NULL;
    }

    /**
     * @brief Free allocated string memory
     * @param value The string to free
     * @note Safely handles NULL pointers, frees any non-NULL string regardless of content
     */
    static void cstr_free(cstrptr value)
    {
        if (value == NULL)
        {
        printf("Warning: attempting to free NULL pointer.\n");
        return;
        }
        free(value);
    }

    static bool exist(const cstrptr value, char c)
    {
        if (value == NULL || is_empty(value))
        {
        printf("bad input: input string is empty.\n");
        return false;
        }
        for (size_t i = 0, e = length(value); i < e; i++)
        {
        if (value[i] == c)
            return true;
        }
        return false;
    }

    /**
     * @brief Check if substring exists in string
     * @param value_1 The main string to search in
     * @param value_2 The substring to search for
     * @return true if substring is found, false otherwise
     * @note Uses standard strstr for reliable substring search with proper pattern handling
     */
    static bool sub_exist(const cstrptr value_1, const cstrptr value_2)
    {
        if (value_1 == NULL || value_2 == NULL || is_empty(value_1) || is_empty(value_2))
        {
        printf("bad input: one of the input strings is empty.\n");
        return false;
        }
        
        // Use standard strstr function for reliable substring search
        // This properly handles overlapping patterns and multiple occurrences
        return strstr(value_1, value_2) != NULL ? true : false;
    }

    static size_t count(const cstrptr value, char c)
    {
        if (value == NULL || is_empty(value))
        {
        printf("bad input: input string is empty.");
        return (size_t)0;
        }
        size_t result = 0;
        for (size_t i = 0, e = length(value); i < e; i++)
        {
        if (value[i] == c)
            result++;
        }
        return result;
    }
    
#endif // METACORE___CGEN_MICROS_STRING_H