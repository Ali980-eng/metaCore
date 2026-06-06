/**
 * @file cgen.h
 * @brief CLite Ecosystem System - Comprehensive management of tests, errors, and warnings
 * @details Provides a complete system for managing CLite environment including:
 *          - Creation and management of system environment for testing
 *          - Safe error and warning handling
 *          - Tracking and support for unit tests
 *          - Proper memory resource cleanup
 *          - Display of error and warning messages to user
 * @author Ali Lafi
 * @date 2026
 * @version 0.1.6
 */


#ifndef METACORE___CGEN_H
#define METACORE___CGEN_H

#include "cgen/IOUtilitys.h"
#include "cgen/UnitTest.h"
#include "cgen/warning.h"
#include "cgen/error.h"
#include "cgen/bitUtilitys.h"
#include "cgen/micros.h"
#include <windows.h>

/** @brief Main system structure for environment management */
cobject(clite_system64,
    CTEST* csys_test; // Array of tests
    size_t csys_tnum; // Number of tests
    cwarning* csys_w; // Array of warnings
    size_t csys_wnum; // Number of warnings
    cerror csys_e;    // Current error
    bool retVal;      // Return value
);

/** @brief Default warning message */
static const char wm_msg[] = "meta clite ecosystem warning";

/** @brief Default error message */
static const char em_msg[] = "meta clite ecosystem error";

/**
 * @brief Initialize the system structure
 * 
 * @details Creates a new system structure and initializes all fields with default values
 * @return clite_system64 The initialized system structure
 */
static inline clite_system64 clite_system64_init() {
    clite_system64 system;
    system.csys_test = NULL;
    system.csys_tnum = 0;
    system.csys_w = NULL;
    system.csys_wnum = 0;
    system.csys_e = cerror_init();
    system.retVal = false;
    return system;
}

/**
 * @brief Add a test to the system structure
 * 
 * @details Adds a new test to the tests array after allocating memory
 *          for the new test
 * @param self The system structure
 * @param ct The test to be added
 * @return clite_system64 The updated system structure
 */
static inline clite_system64 add(clite_system64 self, CTEST ct) {
    if (self.csys_test == NULL) {
        self.csys_test = (CTEST*)malloc(sizeof(CTEST));
    } else {
        self.csys_test = (CTEST*)realloc(self.csys_test, (self.csys_tnum + 1) * sizeof(CTEST));
    }
    
    if (self.csys_test == NULL) {
        self.csys_e = cerror_init();
        self.csys_e.name = (char*)"Memory Allocation Error";
        self.csys_e.description = (char*)"Failed to allocate memory for test";
        self.csys_e.file = __FILE__;
        self.csys_e.line = __LINE__;
        return self;
    }
    
    self.csys_test[self.csys_tnum] = ct;
    self.csys_tnum++;
    return self;
}

/**
 * @brief Handle error and display it to user
 * 
 * @details Saves the error, prints it to console, displays a window message
 *          to the user, then terminates the program with failure status
 * @param self The system structure
 * @param err The error to be handled
 * 
 * @warning This function terminates the program - only call if error is critical
 */
static inline void catch_error(clite_system64 self, cerror err) {
    self.csys_e = err;
    
    // Print error to standard output
    if (err.name != NULL && strlen(err.name) != 0) {
        printf("ERROR NAME: %s\n", err.name);
    }
    if (err.description != NULL && strlen(err.description) != 0) {
        printf("ERROR DESCRIPTION: %s\n", err.description);
    }
    printf("FILE: %s\n", (err.file != NULL) ? err.file : "Unknown");
    printf("LINE: %zu\n", err.line);
    
    // Display error in message box
    char error_msg[512];
    snprintf(error_msg, sizeof(error_msg), 
             "Name: %s\nDescription: %s\nFile: %s\nLine: %zu",
             (err.name != NULL) ? err.name : "Unknown",
             (err.description != NULL) ? err.description : "Unknown",
             (err.file != NULL) ? err.file : "Unknown",
             err.line);
    
    MessageBoxA(NULL, 
                error_msg,
                em_msg,
                MB_OK | MB_ICONERROR);
    
    exit(EXIT_FAILURE);
}

/**
 * @brief Handle warning and add it to the record
 * 
 * @details Adds the warning to the warnings array and prints it to console
 *          Unlike error handling, this does not terminate the program
 * @param self The system structure
 * @param cwar The warning to be handled
 * @return clite_system64 The updated system structure
 */
static inline clite_system64 catch_warning(clite_system64 self, cwarning cwar) {
    // Add warning to array
    if (self.csys_w == NULL) {
        self.csys_w = (cwarning*)malloc(sizeof(cwarning));
    } else {
        self.csys_w = (cwarning*)realloc(self.csys_w, (self.csys_wnum + 1) * sizeof(cwarning));
    }
    
    if (self.csys_w == NULL) {
        self.csys_e = cerror_init();
        self.csys_e.name = (char*)"Memory Allocation Error";
        self.csys_e.description = (char*)"Failed to allocate memory for warning";
        return self;
    }
    
    self.csys_w[self.csys_wnum] = cwar;
    self.csys_wnum++;
    
    // Print warning to console
    if (cwar.name != NULL && strlen(cwar.name) != 0) {
        printf("WARNING NAME: %s\n", cwar.name);
    }
    if (cwar.description != NULL && strlen(cwar.description) != 0) {
        printf("WARNING DESCRIPTION: %s\n", cwar.description);
    }
    printf("FILE: %s\n", (cwar.file != NULL) ? cwar.file : "Unknown");
    printf("LINE: %zu\n", cwar.line);
    
    return self;
}

/**
 * @brief Get the return value of the system
 * 
 * @details Converts the boolean return value to an integer value
 *          (true = 1, false = 0)
 * @param self The system structure
 * @return int The return value (0 or 1)
 */
static inline int exit_value(clite_system64 self) {
    return (int)self.retVal;
}

/**
 * @brief Free system resources
 * 
 * @details Frees all allocated memory for tests, warnings, and errors
 *          Must be called before program termination
 * @param self Pointer to the system structure
 * 
 * @warning This function must be called only once at program end
 */
static inline void free_clite_system64(clite_system64* self) {
    if (self == NULL) {
        return;
    }
    
    // Free tests
    if (self->csys_test != NULL) {
        for (size_t i = 0; i < self->csys_tnum; i++) {
            if (self->csys_test[i].name != NULL) {
                free(self->csys_test[i].name);
            }
            if (self->csys_test[i].description != NULL) {
                free(self->csys_test[i].description);
            }
        }
        free(self->csys_test);
        self->csys_test = NULL;
        self->csys_tnum = 0;
    }
    
    // Free warnings
    if (self->csys_w != NULL) {
        for (size_t i = 0; i < self->csys_wnum; i++) {
            if (self->csys_w[i].name != NULL) {
                free(self->csys_w[i].name);
            }
            if (self->csys_w[i].description != NULL) {
                free(self->csys_w[i].description);
            }
            if (self->csys_w[i].file != NULL) {
                free(self->csys_w[i].file);
            }
            if (self->csys_w[i].time != NULL) {
                free(self->csys_w[i].time);
            }
        }
        free(self->csys_w);
        self->csys_w = NULL;
        self->csys_wnum = 0;
    }
    
    // Free error fields
    if (self->csys_e.name != NULL) {
        free(self->csys_e.name);
    }
    if (self->csys_e.description != NULL) {
        free(self->csys_e.description);
    }
    if (self->csys_e.file != NULL) {
        free(self->csys_e.file);
    }
    if (self->csys_e.time != NULL) {
        free(self->csys_e.time);
    }
}

/** @brief Global system variable for environment */
static clite_system64 clite_ecosystem = {NULL, 0, NULL, 0, {NULL, NULL, NULL, NULL, 0}, false};

#endif // METACORE___CGEN_H