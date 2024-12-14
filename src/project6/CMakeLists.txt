cmake_minimum_required(VERSION 3.10)
project(project6 LANGUAGES CXX)

set(CMAKE_CXX_COMPILER "g++")

add_compile_options(-g -O0 -Wall)
include_directories(include)

add_executable(BFDH "src/BFDH.cpp")
add_executable(FFDH "src/FFDH.cpp")
add_executable(NFDH "src/NFDH.cpp")
