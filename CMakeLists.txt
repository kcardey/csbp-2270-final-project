cmake_minimum_required(VERSION 3.15)
project(final-project VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/code)

add_executable(final-project
    app/main.cpp
    code/Line.cpp
    code/Node.cpp
    code/LiChaoTree.cpp
)