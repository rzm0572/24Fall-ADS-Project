cmake_minimum_required(VERSION 3.10)
project(project4 LANGUAGES CXX)

set(CMAKE_CXX_COMPILER "g++")

add_compile_options(-g -O0 -Wall)
include_directories(include)

function(add_executable_with_deps target deps srcs)
    add_executable(${target} ${srcs})
    target_compile_definitions(
        ${target}
        PRIVATE ALGORITHM_NAME=${deps}
    )
endfunction()

add_executable_with_deps(Baseline Baseline "src/main.cpp;src/Baseline.cpp")
add_executable_with_deps(Merge Merge "src/main.cpp;src/Merge.cpp")
add_executable_with_deps(BItree BItree "src/main.cpp;src/BItree.cpp")
