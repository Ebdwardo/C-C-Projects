cmake_minimum_required(VERSION 3.22)
project(Project_1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(Project_1 parser.cc parser.h lexer.cc lexer.h inputbuf.cc inputbuf.h)
