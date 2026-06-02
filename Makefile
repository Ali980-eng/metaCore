# Compiler settings
CC      := gcc
CXX     := g++
CFLAGS  := -I.
CXXFLAGS:= -I.

# Output files
CLITE_EXAMPLES_OUT := _output/examples/clite
LITE_EXAMPLES_OUT  := _output/examples/lite
CLITE_TEST_OUT := _output/tests/clut
LITE_TEST_OUT  := _output/tests/lut

# Source files
CLITE_EXAMPLES_SRC := _examples/clite/*.c
CLITE_TEST_SRC := _tests/clut/*.c
LITE_EXAMPLES_SRC := _examples/lite/*.cpp
LITE_TEST_SRC  := _tests/lut/*.cpp

# Static analysis targets
BITUTILS_HEADERS := clite/bitUtilitys/*.h
CLITE_HEADERS    := clite/*.h
LITE_HEADERS     := lite/*.hpp

.PHONY: help \
        bitUtilitys-check clite-check lite-check static-check \
        clite-examples lite-examples clite-tests lite-tests compile-tests run-tests

# --------------------------------------------------
# Static analysis
# --------------------------------------------------

bitUtilitys-check:
	cppcheck $(BITUTILS_HEADERS)

clite-check: bitUtilitys-check
	cppcheck $(CLITE_HEADERS)

lite-check:
	cppcheck $(LITE_HEADERS)

static-check:
	cppcheck $(BITUTILS_HEADERS)
	cppcheck $(CLITE_HEADERS)
	cppcheck $(LITE_HEADERS)

# --------------------------------------------------
# Tests
# --------------------------------------------------

clite-tests:
	$(CC) $(CFLAGS) $(CLITE_TEST_SRC) -o $(CLITE_TEST_OUT)
	./$(CLITE_TEST_OUT)

lite-tests:
	$(CXX) $(CXXFLAGS) $(LITE_TEST_SRC) -o $(LITE_TEST_OUT)
	./$(LITE_TEST_OUT)

clite-examples:
	$(CC) $(CFLAGS) $(CLITE_EXAMPLES_SRC) -o $(CLITE_EXAMPLES_OUT)
	./$(CLITE_EXAMPLES_OUT)

lite-examples:
	$(CXX) $(CXXFLAGS) $(LITE_EXAMPLES_SRC) -o $(LITE_EXAMPLES_OUT)
	./$(LITE_EXAMPLES_OUT)

compile-tests:
	$(CC) $(CFLAGS) $(CLITE_TEST_SRC) -o $(CLITE_TEST_OUT)
	$(CXX) $(CXXFLAGS) $(LITE_TEST_SRC) -o $(LITE_TEST_OUT)

compile-examples:
	$(CC) $(CFLAGS) $(CLITE_EXAMPLES_SRC) -o $(CLITE_EXAMPLES_OUT)
	$(CXX) $(CXXFLAGS) $(LITE_EXAMPLES_SRC) -o $(LITE_EXAMPLES_OUT)

run-tests:
	./$(CLITE_TEST_OUT)
	./$(LITE_TEST_OUT)

run-examples:
	./$(CLITE_EXAMPLES_OUT)
	./$(LITE_EXAMPLES_OUT)

# --------------------------------------------------
# Help
# --------------------------------------------------

help:
	@echo "Available targets:"
	@echo ""
	@echo "  bitUtilitys-check : Run cppcheck on bitUtilitys headers"
	@echo "  clite-check       : Run cppcheck on clite headers"
	@echo "  lite-check        : Run cppcheck on lite headers"
	@echo "  static-check      : Run cppcheck on all project headers"
	@echo ""
	@echo "  clite-examples    : Compile and run clite examples"
	@echo "  lite-examples     : Compile and run lite examples"
	@echo "  clite-tests       : Compile and run clite tests"
	@echo "  lite-tests        : Compile and run lite tests"
	@echo "  compile-tests     : Compile all test programs"
	@echo "  compile-examples  : Compile all example programs"
	@echo "  run-tests         : Run all compiled tests"
	@echo "  run-examples      : Run all compiled examples"