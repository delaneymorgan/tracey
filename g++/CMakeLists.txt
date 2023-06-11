cmake_minimum_required(VERSION 3.23)
project(tracey-cpp)

set(CMAKE_CXX_STANDARD 98)

add_executable(tracey-cpp main.cpp ../trace/trace.cpp ../trace/trace.h)
