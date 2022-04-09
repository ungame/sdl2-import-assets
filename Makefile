CC = g++
SRC_DIR = src
SRC_FILES = ${shell where /R ${SRC_DIR} *.cpp}
COMPILER_FLAGS = -c -std=c++14 -m64 -g -Wall 
INCLUDE_PATHS = -I include
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
BUILD_DIR = build

build:
	${CC} ${SRC_FILES} ${COMPILER_FLAGS} ${INCLUDE_PATHS}
	- mkdir ${BUILD_DIR}
	move *.o ${BUILD_DIR}

link:
	${CC} ${BUILD_DIR}/*.o -o ${BUILD_DIR}/main ${LINKER_FLAGS}

run:
	${BUILD_DIR}/main

clear:
	- rmdir /q /s ${BUILD_DIR}

all: clear build link run
