cmake_minimum_required(VERSION 3.0.0)
project(search_lib_shared)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-std=gnu11 -g -O0 -fprofile-arcs -ftest-coverage -fPIC -Wall -Werror -Wpedantic")

file(GLOB SOURCES *.c)
file(GLOB INCLUDE_DIRS ${SEARCH_REG_LIB_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})

set(SEARCH_LIB_LIBRARIES_SHARED ${PROJECT_NAME} PARENT_SCOPE)
set(SEARCH_SHARED_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)

