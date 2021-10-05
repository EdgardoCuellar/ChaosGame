cmake_minimum_required(VERSION 3.17)
project(ChaosGame)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories( ${SDL2_INCLUDE_DIR} )

add_executable(ChaosGame main.cpp Screen.cpp Point.cpp)

target_link_libraries(ChaosGame ${SDL2_LIBRARY} )