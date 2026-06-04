# IOUtilitys.h

To write a function that prints the test result for various data types in C, C++, you can use the `print_test_` functions as follows:

```c
void print_test_type(int x) {
    printf("The test result: %s\n", test_msg(x == 5));
    separator(10, '\n');
}

void print_test_type(double y) {
    printf("The test result: %s\n", test_msg(y - 3.14 < 0.01));
    separator(8, '\n');
}

void print_test_type(size_t z) {
    printf("The test result: %s\n", test_msg(z * 2 == 4));
    separator(6, '\n');
}
```

Note that the `separator` function takes two arguments, a length and a character, to create separators for output. The lengths are specified as `10`, `8`, or `6` depending on the data type.

You can then call these functions with different values for their respective parameters to test various data types:

```c
int main() {
    print_test_type(5); // int
    print_test_type(3.14); // double
    print_test_type(4);  // size_t

    return 0;
}
```

This code defines three functions `print_test_type` that take an integer, a double, and a size_t as parameters, respectively, and prints the test result for each data type using the `test_msg` function.
