cmake_minimum_required(VERSION 3.10)
project(project2)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 11)

add_compile_options(-g -O0 -Wall)
include_directories(include)

function(add_executable_with_deps target deps srcs)
    add_executable(${target} ${srcs})
    target_compile_definitions(
        ${target}
        PRIVATE HEAPTYPE=${deps}
    )
endfunction()

set(PROJECT2_SOURCES "src/main.cpp;src/BinaryHeap.cpp;src/BinomialHeap.cpp;src/FibonacciHeap.cpp;src/LeftistHeap.cpp")

set(DIFFTEST_SOURCES "src/difftest.cpp;src/BinaryHeap.cpp;src/BinomialHeap.cpp;src/FibonacciHeap.cpp;src/LeftistHeap.cpp")

add_executable_with_deps(Binary Binary "${PROJECT2_SOURCES}")
add_executable_with_deps(Binomial Binomial "${PROJECT2_SOURCES}")
add_executable_with_deps(Fibonacci Fibonacci "${PROJECT2_SOURCES}")
add_executable_with_deps(Leftist Leftist "${PROJECT2_SOURCES}")

add_executable(difftest "${DIFFTEST_SOURCES}")
