#!/usr/bin/env bash

set -xe

CC="g++"
CFLAGS="-Wall -Wextra -std=c++20"
INCLUDE="-I ./include"
LIBS="$(pkg-config --cflags --libs glfw3 gl x11 xrandr xi)"

$CC $CFLAGS $INCLUDE $LIBS ./src/main.cpp ./src/glad.c -o build/out