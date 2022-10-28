# cmake version
cmake_minimum_required(VERSION 3.16)

# project
project(minichess_AI_test CXX)

# C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(TARGET_source_file
./test_main.cpp
./board_test.cpp
./util_util_test.cpp
)

set(minichessAI_source_file
../src/header/piece.cpp
../src/header/board.cpp
../src/header/commandline.cpp
../src/header/util/error.cpp
../src/header/util/util.cpp
)

# executable
add_executable(minichessAI_test ${TARGET_source_file} ${minichessAI_source_file})