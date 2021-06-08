# ------------------------------------------------
# Generic Makefile
#
# Author: Hellkaiser
# Date  : 11-06-2021
#
# Changelog :
#   0.01 - simplified makefile
#	0.02 - more robust makefile with directories, wildcards etc.
# ------------------------------------------------
SRC_DIR := src
OBJ_DIR := build
BIN_DIR := bin

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(wildcard $(OBJ_DIR)/*.o)

#OBJS specifies which files to compile as part of the project
#OBJS = main.c cpu.c graphics.c memory.c rom.c roms/binary_reader.c roms/file.c

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

#CC which compiler to use
CC = cc

#COMPILER_FLAGS additional compilation options
COMPILER_FLAGS = -w -g -O 

#LINKER_FLAGS libraries we're linking
LINKER_FLAGS = -lSDL -lSDL_image -lSDL_ttf

.PHONY: compile
compile :
	cd src/utils; make; cd ../;
	cc -c	$(SRC)

.PHONY: build
build : $(OBJ)
	$(CC) $(OBJ) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)