cmake_minimum_required(VERSION 3.13)

project(led C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
    
add_executable(calc
    ./main.cpp
    ./GEN_1.cpp
    ./GEN_2.cpp
    ./GEN_3.cpp
)

target_compile_options(calc PRIVATE
    -g 
    -O3
    -Werror 
    -Wall
)
