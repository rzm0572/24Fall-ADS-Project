cmake_minimum_required(VERSION 3.10)
project(project4 LANGUAGES CXX)

set(CMAKE_CXX_COMPILER "g++")

add_compile_options(-g -O0 -Wall)
include_directories(include)

add_executable(Onm "src/Onm.cpp")
add_executable(BItree "src/BItree.cpp")
