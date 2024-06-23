# General Makefile for C projects #2

PROGRAM_NAME = arduino

# SRC_FILES = test.c
# $(wildcard *.c)
SRC_FILES = main.c
OBJ_FILES = $(patsubst %.c,%.o,${SRC_FILES})

# Raylib doesn't like clang, use gcc instead!
CC = gcc
# Disabled `-Wno-pedantic` to allow converting void pointers to function pointers
CCFLAGS = -xc -std=c89 -Wall -Wextra -Werror -Wno-pedantic \
		 -Wno-unused -g
# -pedantic-errors -pedantic

IFLAGS = -I. -I./lib/include
# -I./lib/Adafruit_BusIO -I./lib/MCUFRIEND_kbv \
# -I./lib/MCUFRIEND_kbv/extras/unused/ -I./lib/Adafruit_GFX_Library

LDFLAGS = -lGL -lm -lpthread -ldl -lX11 \
		-Wl,-rpath=./lib/raylib/ -L./lib/raylib -lraylib \
 		-Wl,-rpath=./lib/ -L./lib/ -lhotreload
# -lXrandr -lXinerama -lXi -lXcursor

DFLAGS = -DEMULATION_ENABLE=1 -DDEBUG_ENABLE=1

FLAGS = $(CCFLAGS) $(IFLAGS) $(LDFLAGS) $(DFLAGS)


local: build_so build run
build_so:
	@echo "Compiling... (auto)"
	$(CC) $(CCFLAGS) -fPIC -shared hotreload.c -o lib/libhotreload.so

build:
	@echo "Compiling... "
	@mkdir -p bin
	$(CC) $(FLAGS) $(SRC_FILES) -o bin/${PROGRAM_NAME}

run:
	@echo "Running... "
	@chmod +x bin/$(PROGRAM_NAME)
	@cd bin && ./$(PROGRAM_NAME)


auto: build_auto run_auto
build_auto:
	@echo "Compiling... (auto)"
	@mkdir -p bin
	$(CC) $(CCFLAGS) autocompiler.c -o bin/autocompiler

run_auto:
	@echo "Running... "
	@chmod +x bin/autocompiler
	@cd bin && .autocompiler/


.PHONY: clean
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
