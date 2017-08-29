cmake_minimum_required(VERSION 3.8)
project(Lexer__)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp lexer.h parser.h)
add_executable(Lexer__ ${SOURCE_FILES})