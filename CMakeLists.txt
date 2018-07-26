cmake_minimum_required(VERSION 3.1)

project(cslib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include)

add_subdirectory(tests)
