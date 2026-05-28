# UnitTest.hpp

The provided code is a C++ implementation of the Metacore unit test framework. It defines a set of functions for creating and running unit tests.

Here's a breakdown of what each function does:

1. `function`: This function takes three parameters: a callable object (`fx`), an expected return value (`expected`), and two input values (`value1` and `value2`). It returns the result of calling `fx` with `value1` and `value2`. The function is used to create unit tests.
2. `function_with_metadata`: This function is similar to `function`, but it also takes a second parameter for each input value, which represents the expected return value. It returns the same result as `function`.
3. `reset_count`: This function resets the basic test counter (`index.basic`) to its initial state (1). It is used to reset the internal test counters.
4. `reset_vector_count`: This function resets the vector test counter (`index.vector`) to its initial state (1). It is similar to `reset_count`, but it only resets the vector test counter.
5. `reset_function_count`: This function resets the function test counter (`index.function`) to its initial state (1). Like `reset_count` and `reset_vector_count`, it only resets the function test counter.

All of these functions are marked as `constexpr`, which means they can be evaluated at compile-time, making them suitable for use in unit tests.

The rest of the code defines a Metacore class with various methods for creating and running unit tests. The main interface includes:

* `reset_all_counts`: Resets all internal test counters to their initial state.
* `function` and `function_with_metadata`: Create unit tests using the `function` and `function_with_metadata` functions, respectively.

The code also includes comments that explain how to use each function, including any necessary initialization or setup steps.
