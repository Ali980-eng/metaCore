#include "clite/error.h"
#include <stdio.h>
#include <string.h>

// Example helper function that validates array access
void process_array_element(int *arr, int size, int index) {
    if (index < 0 || index >= size) {
        cerror err = wrong_indexing("Array index out of bounds");
        printError(err);
        return;
    }
    printf("✓ Successfully accessed array[%d] = %d\n\n", index, arr[index]);
}

// Example helper function that validates variable declaration
void validate_variable_type(int value, const char *expected_type) {
    if (value < 0 && strcmp(expected_type, "unsigned") == 0) {
        cerror err = wrong_declaration("Negative value assigned to unsigned variable");
        printError(err);
        return;
    }
    printf("✓ Variable type validation passed\n\n");
}

// Example helper function that validates struct initialization
void validate_struct_init(void *ptr, const char *field_name) {
    if (ptr == NULL) {
        char description[256];
        snprintf(description, sizeof(description), "Struct field '%s' was not initialized", field_name);
        cerror err = wrong_construction(description);
        printError(err);
        return;
    }
    printf("✓ Struct field '%s' initialized correctly\n\n", field_name);
}

// Example helper function that validates input
void process_user_input(int value, int min, int max) {
    if (value < min || value > max) {
        char description[256];
        snprintf(description, sizeof(description), "Input value %d is outside valid range [%d, %d]", value, min, max);
        cerror err = bad_input(description);
        printError(err);
        return;
    }
    printf("✓ Input validation passed: %d is in valid range [%d, %d]\n\n", value, min, max);
}

// Example function that detects undefined behavior
void check_undefined_behavior(int *ptr) {
    if (ptr == NULL) {
        cerror err = undefined_behavior("Attempted to dereference NULL pointer");
        printError(err);
        return;
    }
    printf("✓ Pointer validation passed: pointer is valid\n\n");
}

// Example function that validates function arguments
void divide_numbers(int dividend, int divisor) {
    if (divisor == 0) {
        cerror err = invalid_argument("Division by zero is not allowed");
        printError(err);
        return;
    }
    printf("✓ Division result: %d / %d = %d\n\n", dividend, divisor, dividend / divisor);
}

int main() {
    printf("|========================================================|\n");
    printf("|          Error Handling Library - Examples             |\n");
    printf("|========================================================|\n\n");

    // ============================================================
    // Example 1: cerror_init() - Initialize an error
    // ============================================================
    printf("EXAMPLE 1: Error Initialization\n");
    printf("----------------------------------\n");
    
    cerror basic_error = cerror_init();
    printf("Created empty error object\n");
    printf("  name = %s\n", basic_error.name ? basic_error.name : "NULL");
    printf("  description = %s\n", basic_error.description ? basic_error.description : "NULL");
    printf("  file = %s\n", basic_error.file ? basic_error.file : "NULL");
    printf("  line = %lu\n\n", basic_error.line);

    // ============================================================
    // Example 2: wrong_indexing() - Array access errors
    // ============================================================
    printf("EXAMPLE 2: Wrong Indexing Error\n");
    printf("----------------------------------\n");
    
    int array[] = {10, 20, 30, 40, 50};
    int array_size = 5;
    
    printf("Testing array access with valid index:\n");
    process_array_element(array, array_size, 2);
    
    printf("Testing array access with invalid index (too high):\n");
    process_array_element(array, array_size, 10);
    
    printf("Testing array access with negative index:\n");
    process_array_element(array, array_size, -1);
    
    // ============================================================
    // Example 3: wrong_declaration() - Type mismatch errors
    // ============================================================
    printf("EXAMPLE 3: Wrong Declaration Error\n");
    printf("------------------------------------\n");
    
    printf("Testing valid variable declaration:\n");
    validate_variable_type(42, "signed");
    
    printf("Testing invalid declaration (negative to unsigned):\n");
    validate_variable_type(-5, "unsigned");

    // ============================================================
    // Example 4: wrong_construction() - Struct initialization errors
    // ============================================================
    printf("EXAMPLE 4: Wrong Construction Error\n");
    printf("--------------------------------------\n");
    
    typedef struct {
        char *name;
        int age;
        char *email;
    } Person;
    
    Person person;
    person.name = "John Doe";
    person.age = 30;
    person.email = NULL;  // Missing field
    
    printf("Validating struct fields:\n");
    printf("Checking 'name' field:\n");
    validate_struct_init(person.name, "name");
    
    printf("Checking 'email' field (missing):\n");
    validate_struct_init(person.email, "email");

    // ============================================================
    // Example 5: bad_input() - Invalid user input
    // ============================================================
    printf("EXAMPLE 5: Bad Input Error\n");
    printf("----------------------------\n");
    
    printf("Processing valid user input (within range):\n");
    process_user_input(50, 0, 100);
    
    printf("Processing invalid user input (too high):\n");
    process_user_input(150, 0, 100);
    
    printf("Processing invalid user input (too low):\n");
    process_user_input(-10, 0, 100);

    // ============================================================
    // Example 6: undefined_behavior() - Null pointer dereference
    // ============================================================
    printf("EXAMPLE 6: Undefined Behavior Error\n");
    printf("--------------------------------------\n");
    
    int value = 42;
    int *valid_ptr = &value;
    int *null_ptr = NULL;
    
    printf("Checking valid pointer:\n");
    check_undefined_behavior(valid_ptr);
    
    printf("Checking NULL pointer:\n");
    check_undefined_behavior(null_ptr);

    // ============================================================
    // Example 7: invalid_argument() - Function argument validation
    // ============================================================
    printf("EXAMPLE 7: Invalid Argument Error\n");
    printf("------------------------------------\n");
    
    printf("Valid division operation:\n");
    divide_numbers(20, 4);
    
    printf("Invalid division operation (division by zero):\n");
    divide_numbers(20, 0);

    // ============================================================
    // Example 8: Practical Use Case - File Operation Error Handling
    // ============================================================
    printf("EXAMPLE 8: Practical Use - File Operations\n");
    printf("----------------------------------------------\n");
    
    // Simulate file buffer validation
    typedef struct {
        char filename[256];
        int buffer_size;
        char *buffer;
    } FileHandle;
    
    FileHandle file1 = {"data.txt", 1024, NULL};
    
    printf("Checking file handle initialization:\n");
    if (file1.buffer == NULL) {
        cerror err = wrong_construction("File buffer not allocated");
        printError(err);
    } else {
        printf("✓ File buffer properly allocated\n\n");
    }
    
    // Simulate buffer validation
    FileHandle file2 = {"output.txt", 512, NULL};
    if (file2.buffer_size <= 0) {
        cerror err = bad_input("Invalid buffer size for file");
        printError(err);
    }

    // ============================================================
    // Example 9: Practical Use Case - Configuration Validation
    // ============================================================
    printf("EXAMPLE 9: Practical Use - Configuration Validation\n");
    printf("-----------------------------------------------------\n");
    
    typedef struct {
        int port;
        int timeout;
        int max_connections;
    } ServerConfig;
    
    ServerConfig config = {8080, 30, 100};
    
    // Validate port range
    if (config.port < 1 || config.port > 65535) {
        cerror err = invalid_argument("Server port must be between 1 and 65535");
        printError(err);
    } else {
        printf("✓ Server port validation passed: %d\n", config.port);
    }
    
    // Validate timeout
    if (config.timeout <= 0) {
        cerror err = bad_input("Timeout value must be greater than 0");
        printError(err);
    } else {
        printf("✓ Timeout validation passed: %d seconds\n", config.timeout);
    }
    
    // Validate max connections
    if (config.max_connections > 10000) {
        cerror err = undefined_behavior("Max connections too high may cause resource exhaustion");
        printError(err);
    } else {
        printf("✓ Max connections validation passed: %d\n\n", config.max_connections);
    }

    // ============================================================
    // Example 10: Creating custom errors with context
    // ============================================================
    printf("EXAMPLE 10: Context-Aware Error Handling\n");
    printf("-----------------------------------------\n");
    
    // Simulate database operation
    int database_id = -1;  // Invalid ID
    
    if (database_id < 0) {
        cerror err = invalid_argument("Database record ID must be positive");
        printError(err);
    }
    
    // Simulate memory allocation failure
    int requested_memory = 999999999;  // Too much
    int max_memory = 1048576;  // 1MB
    
    if (requested_memory > max_memory) {
        char desc[256];
        snprintf(desc, sizeof(desc), 
                "Requested memory (%d bytes) exceeds limit (%d bytes)", 
                requested_memory, max_memory);
        cerror err = bad_input(desc);
        printError(err);
    }

    // ============================================================
    // Summary
    // ============================================================
    printf("|========================================================|\n");
    printf("|  Error Handling Library provides comprehensive errors: |\n");
    printf("|                                                        |\n");
    printf("|  • cerror_init()         - Initialize error object     |\n");
    printf("|  • printError()          - Display error details       |\n");
    printf("|  • wrong_indexing()      - Array/index errors          |\n");
    printf("|  • wrong_declaration()   - Type/declaration errors     |\n");
    printf("|  • wrong_construction()  - Initialization errors       |\n");
    printf("|  • bad_input()           - Input validation errors     |\n");
    printf("|  • undefined_behavior()  - Risky operations            |\n");
    printf("|  • invalid_argument()    - Function argument errors    |\n");
    printf("|                                                        |\n");
    printf("|  Each error captures: name, description, file, time,   |\n");
    printf("|                       and line number for debugging    |\n");
    printf("|========================================================|\n");

    return 0;
}