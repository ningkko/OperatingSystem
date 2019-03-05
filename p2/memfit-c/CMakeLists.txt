cmake_minimum_required(VERSION 3.13)
project(memfit_c C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(memfit_c
        block.c
        block.h
        block_test.c
        main.c
        simulation.c
        simulation.h mainTest.c)
