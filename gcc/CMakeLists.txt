cmake_minimum_required(VERSION 3.23)
project(tracey-gcc C)

set(CMAKE_C_STANDARD 99)

add_executable(tracey-gcc main.c ../trace/trace.h)
