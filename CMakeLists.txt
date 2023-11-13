cmake_minimum_required(VERSION 3.13)

project(led C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
    
add_executable(calc
    src/main.cpp
    src/GEN_1.cpp
    src/GEN_2.cpp
    src/GEN_3.cpp
    src/helper.cpp
)

target_include_directories(calc PRIVATE
    include
)

target_compile_options(calc PRIVATE
    -g 
    -O3
    -Werror 
    -Wall
)
