# Compiler settings
CC      := gcc
CXX     := g++
CFLAGS  := -I.
CXXFLAGS:= -I.

# Output files
CGEN_EXAMPLES_OUT := _output/examples/cgen
LITE_EXAMPLES_OUT  := _output/examples/lite
CGEN_TEST_OUT := _output/tests/cgen
LITE_TEST_OUT  := _output/tests/lite

# Source files
CGEN_EXAMPLES_SRC := _examples/cgen/*.c
CGEN_TEST_SRC := _tests/cgen/*.c
LITE_EXAMPLES_SRC := _examples/lite/*.cpp
LITE_TEST_SRC  := _tests/lite/*.cpp

# Static analysis targets
BITUTILS_HEADERS := clite/bitUtilitys/*.h
CGEN_HEADERS    := clite/*.h
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
	cppcheck $(CGEN_HEADERS)

lite-check:
	cppcheck $(LITE_HEADERS)

static-check:
	cppcheck $(BITUTILS_HEADERS)
	cppcheck $(CGEN_HEADERS)
	cppcheck $(LITE_HEADERS)

# --------------------------------------------------
# Tests
# --------------------------------------------------

clite-tests:
	$(CC) $(CFLAGS) $(CGEN_TEST_SRC) -o $(CGEN_TEST_OUT)
	./$(CGEN_TEST_OUT)

lite-tests:
	$(CXX) $(CXXFLAGS) $(LITE_TEST_SRC) -o $(LITE_TEST_OUT)
	./$(LITE_TEST_OUT)

clite-examples:
	$(CC) $(CFLAGS) $(CGEN_EXAMPLES_SRC) -o $(CGEN_EXAMPLES_OUT)
	./$(CGEN_EXAMPLES_OUT)

lite-examples:
	$(CXX) $(CXXFLAGS) $(LITE_EXAMPLES_SRC) -o $(LITE_EXAMPLES_OUT)
	./$(LITE_EXAMPLES_OUT)

compile-tests:
	$(CC) $(CFLAGS) $(CGEN_TEST_SRC) -o $(CGEN_TEST_OUT)
	$(CXX) $(CXXFLAGS) $(LITE_TEST_SRC) -o $(LITE_TEST_OUT)

compile-examples:
	$(CC) $(CFLAGS) $(CGEN_EXAMPLES_SRC) -o $(CGEN_EXAMPLES_OUT)
	$(CXX) $(CXXFLAGS) $(LITE_EXAMPLES_SRC) -o $(LITE_EXAMPLES_OUT)

run-tests:
	./$(CGEN_TEST_OUT)
	./$(LITE_TEST_OUT)

run-examples:
	./$(CGEN_EXAMPLES_OUT)
	./$(LITE_EXAMPLES_OUT)

# --------------------------------------------------
# Help
# --------------------------------------------------

help:
	@echo "Available targets:"
	@echo ""
	@echo "  bitUtilitys-check : Run cppcheck on bitUtilitys headers"
	@echo "  cgen-check       : Run cppcheck on cgen headers"
	@echo "  lite-check        : Run cppcheck on lite headers"
	@echo "  static-check      : Run cppcheck on all project headers"
	@echo ""
	@echo "  cgen-examples    : Compile and run cgen examples"
	@echo "  lite-examples     : Compile and run lite examples"
	@echo "  cgen-tests       : Compile and run cgen tests"
	@echo "  lite-tests        : Compile and run lite tests"
	@echo "  compile-tests     : Compile all test programs"
	@echo "  compile-examples  : Compile all example programs"
	@echo "  run-tests         : Run all compiled tests"
	@echo "  run-examples      : Run all compiled examples"