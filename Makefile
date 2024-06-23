# General Makefile for C projects #2

PROGRAM_NAME = arduino

# SRC_FILES = test.c
SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(patsubst %.c,%.o,${SRC_FILES})

# Raylib doesn't like clang, use gcc instead!
CC = gcc
CCFLAGS = -xc -std=c89 -Wall -Wextra -Werror -Wpedantic \
		-pedantic -pedantic-errors -Wno-unused -g

IFLAGS = -I. -I./lib/include
# -I./lib/Adafruit_BusIO -I./lib/MCUFRIEND_kbv \
# -I./lib/MCUFRIEND_kbv/extras/unused/ -I./lib/Adafruit_GFX_Library

LDFLAGS = -Wl,-rpath=./lib/raylib/ -L./lib/raylib -lraylib -lGL -lm -lpthread -ldl -lX11
# -lXrandr -lXinerama -lXi -lXcursor

DFLAGS = -DEMULATION_ENABLE=1 -DDEBUG_ENABLE=1

FLAGS = $(CCFLAGS) $(IFLAGS) $(LDFLAGS) $(DFLAGS)

local: build run
build:
	@echo "Compiling... "
	@mkdir -p bin
	$(CC) $(FLAGS) $(SRC_FILES) -o bin/${PROGRAM_NAME}

run:
	@echo "Running... "
	@chmod +x bin/$(PROGRAM_NAME)
	@cd bin && ./$(PROGRAM_NAME)

clean:
	@echo "Cleaning..."
	@rm -rf ./bin

# raylib: ray_clean ray_build
# ray_clean:
# 	cd lib/sources/raylib/src && make clean

# ray_build:
# 	cd lib/sources/raylib/src && make PLATFORM=PLATFORM_DESKTOP GLFW_LINUX_ENABLE_WAYLAND=OFF

# ray_build_shared:
# 	cd lib/sources/raylib/src && make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=SHARED GLFW_LINUX_ENABLE_WAYLAND=OFF
