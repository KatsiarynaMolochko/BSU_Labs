cmake_minimum_required(VERSION 3.17)
project(classShape_inherritance)

set(CMAKE_CXX_STANDARD 17)

add_library(shape.cpp shape.hpp)
add_executable(classShape_inherritance main.cpp shape.cpp)