CXX = g++
CXX_FLAGS = -Wall -std=c++20

OS := $(shell uname)

LINUX_INCLUDES = -I/usr/include/SFML
LINUX_LIBS = -L/usr/lib/x86_64-linux-gnu -lsfml-graphics -lsfml-window -lsfml-system

MACOS_INCUDES = -I/opt/homebrew/Cellar/sfml/2.5.1_2/include
MACOS_LIBS = -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system

SRC = ${wildcard src/*.cpp}
OBJ = ${wildcard build/*}

ifeq ($(OS), Darwin)
	INCLUDES = $(MACOS_INCUDES)
	LIBS = $(MACOS_LIBS)
else
	INCLUDES = $(LINUX_INCLUDES)
	LIBS = $(LINUX_LIBS)
endif

all:
	${CXX} ${CXX_FLAGS} ${INCLUDES} ${SRC} main.cpp -o build/minesweeper ${LIBS}

test:
	${CXX} ${CXX_FLAGS} ${SRC} tests/test_board.cpp -o build/tests ${LIBS}

clean: ${OBJ}
	@echo "Removing ${OBJ}"
	rm -f ${OBJ}
