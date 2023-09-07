cmake_minimum_required(VERSION 3.26)
project(task1 C)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -pthread)

include_directories(.)

add_executable(task1
        dbl_vector.c
        dbl_vector.h
        test.c)
