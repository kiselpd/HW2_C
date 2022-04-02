cmake_minimum_required(VERSION 3.0.0)
project(search)

add_subdirectory(search_lib)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-std=gnu11 -g -fprofile-arcs -ftest-coverage -fPIC -O0 -Wall -Werror -Wpedantic")

option(BUILD_PARALLEL_VERSION "Build the version with parallel search" OFF)

if (BUILD_PARALLEL_VERSION)
	add_executable(${PROJECT_NAME}_shared main.c)
else ()
	add_executable(${PROJECT_NAME}_static main.c)
endif ()

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lm -coverage -lgcov -pthread")

if (BUILD_PARALLEL_VERSION)
	target_include_directories(${PROJECT_NAME}_shared PUBLIC ${SEARCH_REG_LIB_INCLUDE_DIRS})
	target_link_libraries(${PROJECT_NAME}_shared PRIVATE ${SEARCH_LIB_LIBRARIES_REG})
	target_link_libraries(${PROJECT_NAME}_shared PRIVATE ${SEARCH_LIB_LIBRARIES_SHARED})
else ()
	target_include_directories(${PROJECT_NAME}_static PUBLIC ${SEARCH_REG_LIB_INCLUDE_DIRS})
	target_link_libraries(${PROJECT_NAME}_static PRIVATE ${SEARCH_LIB_LIBRARIES_REG})
	target_link_libraries(${PROJECT_NAME}_static PRIVATE ${SEARCH_LIB_LIBRARIES_STATIC})
endif ()

