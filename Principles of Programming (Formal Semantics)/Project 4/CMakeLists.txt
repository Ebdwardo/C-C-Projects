cmake_minimum_required(VERSION 3.22)
project(Project_4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(Project_4 compiler.cc inputbuf.cc lexer.cc Parser.cpp)