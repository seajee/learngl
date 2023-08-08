#!/usr/bin/env bash

set -xe

CC="g++"
CFLAGS="-Wall -Wextra -std=c++20"
INCLUDE="-I ./src/include"
LIBS="$(pkg-config --cflags --libs glfw3 gl x11 xrandr xi)"

$CC $CFLAGS $INCLUDE $LIBS ./src/triangle.cpp  ./src/shader.cpp ./src/glad.c -o build/triangle
$CC $CFLAGS $INCLUDE $LIBS ./src/rectangle.cpp ./src/shader.cpp ./src/glad.c -o build/rectangle

cp -r ./src/shaders ./build/