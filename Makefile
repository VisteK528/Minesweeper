CXX = g++
CXX_FLAGS = -Wall -std=c++20

INCLUDES = -I/usr/include/SFML
LIBS = -L/usr/lib/x86_64-linux-gnu -lsfml-graphics -lsfml-window -lsfml-system

SRC = ${wildcard src/*.cpp}
OBJ = ${wildcard build/*}

compile:
	${CXX} ${CXX_FLAGS} ${SRC} main.cpp -o build/main ${LIBS}

test:
	${CXX} ${CXX_FLAGS} ${SRC} tests/test_board.cpp -o build/tests ${LIBS}

clean: ${OBJ}
	@echo "Removing ${OBJ}"
	rm -f ${OBJ}
