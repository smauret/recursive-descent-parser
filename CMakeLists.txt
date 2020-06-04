cmake_minimum_required(VERSION 3.16)
project(calculator)

set(CMAKE_CXX_STANDARD 14)

add_executable(calculator main.cpp math.cpp math.h)