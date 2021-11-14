project(yasuo)

add_executable(yasuo main.cpp small.cpp big.cpp huffman.cpp tempwindow.cpp)

add_definitions(-Wall -g)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  -pthread" )
