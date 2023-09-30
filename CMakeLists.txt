cmake_minimum_required(VERSION 3.24)
project(virtual_memory_manager C)

set(CMAKE_C_STANDARD 23)

add_executable(virtual_memory_manager
        src/main.c
        src/Utility.c
        src/LRU.c)
