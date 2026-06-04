#include "clite/warning.h"
#include <stdio.h>
#include <string.h>

int main() {
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║        Warning Handling Library - Examples             ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n\n");

    // ============================================================
    // Example 1: cwarning_init() - Initialize an empty warning
    // ============================================================
    printf("📖 EXAMPLE 1: Warning Initialization\n");
    printf("──────────────────────────────────\n");
    
    cwarning basic_warning = cwarning_init();
    printf("Created empty warning object\n");
    printf("  name = %s\n", basic_warning.name ? basic_warning.name : "NULL");
    printf("  description = %s\n", basic_warning.description ? basic_warning.description : "NULL");
    printf("  warning number = %zu\n\n", basic_warning.number);

    // ============================================================
    // Example 2: wrong_indexing() - Array/Index access warnings
    // ============================================================
    printf("📖 EXAMPLE 2: Wrong Indexing Warning\n");
    printf("───────────────────────────────────\n");
    
    int array[] = {10, 20, 30, 40, 50};
    int index = 10;  // Out of bounds
    
    if (index >= 5) {
        cwarning w = wrong_indexing("Array index exceeds valid range [0-4]");
        printWarning(w);
    }

    // ============================================================
    // Example 3: wrong_declaration() - Type mismatch warnings
    // ============================================================
    printf("📖 EXAMPLE 3: Wrong Declaration Warning\n");
    printf("──────────────────────────────────────\n");
    
    unsigned int positive_only = -5;  // Wrong: negative assigned to unsigned
    if (positive_only < 0) {
        cwarning w = wrong_declaration("Negative value assigned to unsigned integer variable");
        printWarning(w);
    }

    // ============================================================
    // Example 4: wrong_construction() - Initialization warnings
    // ============================================================
    printf("📖 EXAMPLE 4: Wrong Construction Warning\n");
    printf("──────────────────────────────────────\n");
    
    typedef struct {
        int *data;
        size_t size;
    } DataBuffer;
    
    DataBuffer buf;
    buf.data = NULL;  // Uninitialized
    buf.size = 0;
    
    if (buf.data == NULL) {
        cwarning w = wrong_construction("DataBuffer.data was not properly initialized");
        printWarning(w);
    }

    // ============================================================
    // Example 5: bad_input() - Invalid input warnings
    // ============================================================
    printf("📖 EXAMPLE 5: Bad Input Warning\n");
    printf("───────────────────────────────\n");
    
    int user_port = 99999;  // Port out of range
    if (user_port > 65535 || user_port < 1) {
        cwarning w = bad_input("Port number must be between 1 and 65535");
        printWarning(w);
    }

    // ============================================================
    // Example 6: undefined_behavior() - Risky operations
    // ============================================================
    printf("📖 EXAMPLE 6: Undefined Behavior Warning\n");
    printf("──────────────────────────────────────\n");
    
    int *null_ptr = NULL;
    if (null_ptr == NULL) {
        cwarning w = undefined_behavior("Attempted to use NULL pointer");
        printWarning(w);
    }

    // ============================================================
    // Example 7: invalid_argument() - Function argument warnings
    // ============================================================
    printf("📖 EXAMPLE 7: Invalid Argument Warning\n");
    printf("─────────────────────────────────────\n");
    
    int divisor = 0;  // Invalid argument
    if (divisor == 0) {
        cwarning w = invalid_argument("Division by zero is not allowed");
        printWarning(w);
    }

    // ============================================================
    // Example 8: OutOfRange() - Value range warnings
    // ============================================================
    printf("📖 EXAMPLE 8: Out Of Range Warning\n");
    printf("──────────────────────────────────\n");
    
    int score = 150;  // Should be 0-100
    if (score > 100 || score < 0) {
        cwarning w = OutOfRange("Score value must be between 0 and 100");
        printWarning(w);
    }

    // ============================================================
    // Example 9: internal_problem() - System/Library warnings
    // ============================================================
    printf("📖 EXAMPLE 9: Internal Problem Warning\n");
    printf("──────────────────────────────────────\n");
    
    cwarning w_internal = internal_problem("Memory allocation failed in buffer manager");
    printWarning(w_internal);

    // ============================================================
    // Example 10: Practical Use Case - API Request Validation
    // ============================================================
    printf("📖 EXAMPLE 10: Practical Use - API Request Validation\n");
    printf("───────────────────────────────────────────────────────\n");
    
    typedef struct {
        char *endpoint;
        int timeout;
        int retry_count;
    } APIRequest;
    
    APIRequest request = {NULL, -1, 0};
    
    // Validate endpoint
    if (request.endpoint == NULL) {
        cwarning w = bad_input("API endpoint URL cannot be empty");
        printWarning(w);
    }
    
    // Validate timeout
    if (request.timeout <= 0) {
        cwarning w = invalid_argument("API timeout must be greater than 0 milliseconds");
        printWarning(w);
    }
    
    // Validate retry count
    if (request.retry_count < 0 || request.retry_count > 5) {
        cwarning w = OutOfRange("Retry count should be between 0 and 5");
        printWarning(w);
    }

    // ============================================================
    // Example 11: Practical Use Case - File Operation Warnings
    // ============================================================
    printf("📖 EXAMPLE 11: Practical Use - File Operations\n");
    printf("──────────────────────────────────────────────\n");
    
    typedef struct {
        char filename[256];
        int file_size;
        char *buffer;
    } FileHandle;
    
    FileHandle file;
    strcpy(file.filename, "data.bin");
    file.file_size = -100;  // Invalid
    file.buffer = NULL;
    
    // Check file size
    if (file.file_size < 0) {
        cwarning w = bad_input("File size cannot be negative");
        printWarning(w);
    }
    
    // Check buffer allocation
    if (file.buffer == NULL && file.file_size > 0) {
        cwarning w = wrong_construction("File buffer not allocated despite positive file size");
        printWarning(w);
    }

    // ============================================================
    // Example 12: Practical Use Case - Database Connection Pool
    // ============================================================
    printf("📖 EXAMPLE 12: Practical Use - Database Connection Pool\n");
    printf("─────────────────────────────────────────────────────────\n");
    
    typedef struct {
        int pool_size;
        int max_connections;
        int active_connections;
    } DBConnectionPool;
    
    DBConnectionPool pool = {0, 1000, 2000};
    
    // Check pool size
    if (pool.pool_size <= 0) {
        cwarning w = bad_input("Connection pool size must be at least 1");
        printWarning(w);
    }
    
    // Check active connections exceed max
    if (pool.active_connections > pool.max_connections) {
        cwarning w = undefined_behavior("Active connections exceed maximum allowed connections");
        printWarning(w);
    }

    // ============================================================
    // Example 13: Warning Counter Tracking
    // ============================================================
    printf("📖 EXAMPLE 13: Warning Counter Tracking\n");
    printf("──────────────────────────────────────\n");
    
    size_t initial_count = cwarningCounter;
    printf("Initial warning counter: %zu\n", initial_count);
    
    cwarning w1 = wrong_indexing("First warning");
    cwarning w2 = bad_input("Second warning");
    cwarning w3 = invalid_argument("Third warning");
    
    printf("After creating 3 warnings:\n");
    printf("  Warning 1 number: %zu\n", w1.number);
    printf("  Warning 2 number: %zu\n", w2.number);
    printf("  Warning 3 number: %zu\n", w3.number);
    printf("  Current counter: %zu\n\n", cwarningCounter);

    // ============================================================
    // Example 14: Batch Warning Processing
    // ============================================================
    printf("📖 EXAMPLE 14: Batch Warning Processing\n");
    printf("─────────────────────────────────────\n");
    
    printf("Validating configuration data:\n\n");
    
    int config_port = 8080;
    int config_timeout = 30;
    char *config_host = "localhost";
    int max_workers = -4;
    
    // Validate each field
    bool has_warnings = false;
    
    if (config_port < 1 || config_port > 65535) {
        cwarning w = invalid_argument("Invalid port configuration");
        printWarning(w);
        has_warnings = true;
    }
    
    if (config_timeout <= 0) {
        cwarning w = bad_input("Timeout must be positive");
        printWarning(w);
        has_warnings = true;
    }
    
    if (config_host == NULL) {
        cwarning w = wrong_declaration("Host cannot be NULL");
        printWarning(w);
        has_warnings = true;
    }
    
    if (max_workers <= 0) {
        cwarning w = OutOfRange("Worker count must be at least 1");
        printWarning(w);
        has_warnings = true;
    }
    
    if (!has_warnings) {
        printf("\n✓ All configuration parameters are valid!\n\n");
    } else {
        printf("\n⚠ Configuration validation completed with warnings\n\n");
    }

    // ============================================================
    // Summary
    // ============================================================
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║  Warning Handling Library provides 9 warning types:    ║\n");
    printf("║                                                        ║\n");
    printf("║  • cwarning_init()       - Create empty warning       ║\n");
    printf("║  • wrong_indexing()      - Index/array warnings       ║\n");
    printf("║  • wrong_declaration()   - Type/declaration warnings  ║\n");
    printf("║  • wrong_construction()  - Initialization warnings    ║\n");
    printf("║  • bad_input()           - Input validation warnings  ║\n");
    printf("║  • undefined_behavior()  - Risky operation warnings   ║\n");
    printf("║  • invalid_argument()    - Function argument warnings ║\n");
    printf("║  • OutOfRange()          - Range violation warnings   ║\n");
    printf("║  • internal_problem()    - System/Library warnings    ║\n");
    printf("║                                                        ║\n");
    printf("║  Each warning tracks: name, description, file, time,  ║\n");
    printf("║                      line number, and sequence count  ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");

    return 0;
}