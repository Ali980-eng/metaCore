cbit-check:
	cppcheck CLite/CBit/*.h

clite-check: cbit-check
	cppcheck CLite/*.h

cxxlite-check:
	cppcheck CXXLite/*.hpp

static-check:
	cppcheck CLite/CBit/*.h
	cppcheck CLite/*.h
	cppcheck CXXLite/*.hpp
	
clite-tests:
	gcc -I. tests/CLiteUT.c -o tests/output/clut
	./tests/output/clut

cxxlite-tests:
	g++ -I. tests/CXXLiteUT.cpp -o tests/output/cxlut
	./tests/output/cxlut

jlite-tests:
	javac -cp . -d tests/output tests/JLiteUT.java
	java -cp tests/output JLiteUT

compile-tests:
	gcc -I. tests/CLiteUT.c -o tests/output/clut
	g++ -I. tests/CXXLiteUT.cpp -o tests/output/cxlut
	javac -cp . -d tests/output tests/JLiteUT.java

run-tests:
	./tests/output/clut
	./tests/output/cxlut
	java -cp tests/output JLiteUT

help:
	echo "cbit-check: label will check all libraries in cbit using cppcheck"
	echo "clite-check: label will check all libraries in clite using cppcheck"
	ehco "cxxlite-check: label will check all libraries in cxxlite using cppcheck"
	echo "static-check: label will use the static-analysis tool cppcheck to check all the project libraries."
	echo "clite-tests": label will compile and run clite tests"
	echo "cxxlite-tests: label will compile and run cxxlite tests"
	echo "jlite-tests: label will compile and run jlite tests"
	echo "compile-tests: label will compile all tests programs"
	echo "run-tests: label will run all tests that have compiled"