cmake_minimum_required(VERSION 3.20)
project(Battleship)

set(CMAKE_CXX_STANDARD 17)

add_executable(Battleship main.cpp)
add_library(Entities SHARED BattleshipEntities.cpp)
target_link_libraries(Battleship Entities)

