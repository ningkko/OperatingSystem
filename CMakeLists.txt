cmake_minimum_required(VERSION 3.13)
project(PA2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(p2)
include_directories(p2/memfit-c)

add_executable(PA2
        p2/memfit-c/block.c
        p2/memfit-c/block.h
        p2/memfit-c/fits.c
        p2/memfit-c/fits.h
        p2/memfit-c/main.c
        p2/memfit-c/simulation.c
        p2/memfit-c/simulation.h
        p2/input.txt)
