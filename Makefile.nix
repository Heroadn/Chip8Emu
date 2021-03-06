# ------------------------------------------------
# Generic Makefile
#
# Author: Hellkaiser
# Date  : 10-31-2021
#
# Changelog :
#   0.01 - simplified makefile
#	0.02 - more robust makefile with directories, wildcards etc.
#   0.03 - add defined flags to be passed to the preprocessor(cross compiling).
# ------------------------------------------------
SRC_DIR := src
OBJ_DIR := build
BIN_DIR := bin

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(wildcard $(BIN_DIR)/*.o)

#OBJS specifies which files to compile as part of the project
#OBJS = main.c cpu.c graphics.c memory.c rom.c roms/binary_reader.c roms/file.c

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main.exe

#CC which compiler to use
CC = i686-w64-mingw32-gcc

#COMPILER_FLAGS additional compilation options
COMPILER_FLAGS = -w -g -O 

#DEF_FLAGS macros used by the preprocessor
DEF_FLAGS = -D WINDOWS 

#LINKER_FLAGS libraries we're linking
LINKER_FLAGS = -lSDL -lSDL_image -lSDL_ttf -lmingw32

.PHONY: compile
compile :
	$(CC) $(DEF_FLAGS) $(COMPILER_FLAGS)  -c	$(SRC)

.PHONY: build
build : $(OBJ)
	$(CC) $(OBJ) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	
all:
	compile
	build