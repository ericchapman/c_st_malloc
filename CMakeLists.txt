cmake_minimum_required(VERSION 3.5)
project(st_objects)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES
        main.c
        lib/st_malloc.c
        tests/test_st_malloc.c
        lib/st_object.h
        lib/st_object.c
        lib/st_array.h
        lib/st_array.c
        lib/st_dict.h
        lib/st_link.h tests/test_st_array.c lib/st_link.c lib/st_dict.c tests/test_st_object.c tests/test_st_dict.c lib/st_types.h)

add_executable(st_objects ${SOURCE_FILES})