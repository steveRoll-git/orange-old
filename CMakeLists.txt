cmake_minimum_required(VERSION 3.10)

# set the project name
project(Orange)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(orange
	src/main.cpp
	src/repl.cpp
	src/ConsCell.cpp
	src/Parser.cpp
	src/Value.cpp
	src/VM.cpp
	src/Lang/Lexer.cpp
	src/Lang/Token.cpp
)
