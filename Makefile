bitUtilitys-check:
	cppcheck clite/bitUtilitys/*.h

clite-check: bitUtilitys-check
	cppcheck clite/*.h

lite-check:
	cppcheck lite/*.hpp

static-check:
	cppcheck clite/bitUtilitys/*.h
	cppcheck clite/*.h
	cppcheck lite/*.hpp
	
clite-tests:
	gcc -I. _tests/CLUT/*.c -o _tests/output/clut
	./_tests/output/clut

lite-tests:
	g++ -I. _tests/LUT/*.cpp -o _tests/output/lut
	./_tests/output/lut

compile-tests:
	gcc -I. _tests/CLUT/*.c -o _tests/output/clut
	g++ -I. _tests/LUT/*.cpp -o _tests/output/lut

run-tests:
	./_tests/output/clut
	./_tests/output/lut

help:
	echo "bitUtilitys-check: label will check all libraries in bitUtilitys using cppcheck"
	echo "clite-check: label will check all libraries in clite using cppcheck"
	ehco "lite-check: label will check all libraries in lite using cppcheck"
	echo "static-check: label will use the static-analysis tool cppcheck to check all the project libraries."
	echo "clite-tests": label will compile and run clite tests"
	echo "lite-tests: label will compile and run lite tests"
	echo "compile-tests: label will compile all tests programs"
	echo "run-tests: label will run all tests that have compiled"