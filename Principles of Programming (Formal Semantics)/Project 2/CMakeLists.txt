cmake_minimum_required(VERSION 3.22)
project(Project_2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(Project_2 inputbuf.h inputbuf.cc lexer.h lexer.cc parser.h parser.cc)
