cmake_minimum_required(VERSION 2.6)

find_package(Boost REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pthread -std=c++11")

include_directories(include)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(demo)
