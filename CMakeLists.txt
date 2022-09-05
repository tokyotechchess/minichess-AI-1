# cmake version
cmake_minimum_required(VERSION 3.21)

# project
project(minichess_AI CXX)

# C++ standards
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(TARGET_source_file
./src/main.cpp
./src/header/piece.cpp
./src/header/board.cpp
./src/header/commandline.cpp
./src/header/util/error.cpp
./src/header/util/util.cpp
)

# executable
add_executable(minichessAI ${TARGET_source_file})