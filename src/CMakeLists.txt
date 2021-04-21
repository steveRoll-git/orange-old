cmake_minimum_required(VERSION 3.10)

# set the project name
project(Orange)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(orange main.cpp ConsCell.cpp Parser.cpp Value.cpp VM.cpp Lang/Lexer.cpp Lang/Token.cpp)
