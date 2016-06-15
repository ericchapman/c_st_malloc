cmake_minimum_required(VERSION 3.5)
project(st_malloc)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES main.c lib/st_malloc.c)
add_executable(st_malloc ${SOURCE_FILES})