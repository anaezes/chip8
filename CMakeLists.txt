cmake_minimum_required(VERSION 3.19)
project(chip8)

set(CMAKE_CXX_STANDARD 17)

add_executable(chip8 main.cpp Chip8.cpp Chip8.h utils.h)