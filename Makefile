CXX = g++
CXX_FLAGS = -Wall -std=c++20

compile:
	${CXX} ${CXX_FLAGS} src/*.cpp main.cpp -o build/main

tests:
	${CXX} ${CXX_FLAGS} tests/tests.cpp -o build/tests