# ecosystem.hpp

## Overview

The provided C++ code is part of a meta-core ecosystem management system, which centralizes error and warning handling for the MetaCore library. The system offers features such as centralized warning queue management, immediate program termination with errors, test result collection and summary reporting, exit status tracking, and Windows integration.

## Key Classes and Functions

### `system65` Class

* **Purpose**: Centralized ecosystem management object for error and warning handling.
* **Features**:
    * Warning Queue: Collects warnings for later processing
    * Error Handling: Catches errors and terminates program gracefully
    * Test Management: Collects and reports test results with pass/fail statistics
    * Windows Integration: Supports message box dialogs for user notification
    * Exit Status Tracking: Tracks whether warnings occurred for proper exit codes

### `metaSystem` Object

* **Purpose**: The main ecosystem management object.
* **Features**:
    * Centralized warning queue management with console and message box display options
    * Error handling with immediate program termination
    * Test result collection and summary reporting
    * Exit status tracking for proper program termination
    * String conversion utilities for Windows wide-character support

## Usage Example

```cpp
#include "clite/micros.h"
#include "lite/micros.hpp"

// Create a new warning object
lite::warning w("Something unexpected happened");

// Add the test result to the ecosystem's test collection
meta::system65::add(w, true);

// Display the warning with an optional message box
meta::system65::Catch(w, true); // Display as message box

// Catch and display an error, then exit the program
lite::error e("Critical failure");
meta::system65::Catch(e); // Display and exit
```
