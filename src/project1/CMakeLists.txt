cmake_minimum_required(VERSION 3.10)
project(project1 LANGUAGES CXX)

set(CMAKE_CXX_COMPILER "g++")

add_compile_options(-g -O0 -Wall)
include_directories(include)

add_executable(baseline "src/main.cpp;src/baseline.cpp")
add_executable(AVL "src/main.cpp;src/AVL.cpp")
add_executable(splay "src/main.cpp;src/splay.cpp")
