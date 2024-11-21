cmake_minimum_required(VERSION 3.28.3)

project(clox C)

set(CMAKE_C_STANDARD 11)

if (NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")

add_executable(hello_world hello_world.c)
add_executable(linked_list linked_list.c)
