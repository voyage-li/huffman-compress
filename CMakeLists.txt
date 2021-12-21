cmake_minimum_required(VERSION 3.5)

project(yasuo)

set (CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread" )

set(SOURCES
    src/main.cpp
    src/big.cpp
    src/small.cpp
    src/tempwindow.cpp
    src/huffman.cpp)

add_executable(yasuo ${SOURCES})

add_definitions(-w)

SET(CMAKE_BUILD_TYPE "Release")
# SET(CMAKE_BUILD_TYPE "Debug")

target_include_directories(yasuo
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

