cmake_minimum_required(VERSION 3.26)
project(task2 C)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -lrt -lpthread)



include_directories(.)

add_executable(task2
        operations.h
        shm_ipc.c)
