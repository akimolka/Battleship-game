cmake_minimum_required(VERSION 3.20)
project(Battleship)

set(CMAKE_CXX_STANDARD 17)

add_executable(Battleship
        main.cpp
        src/entities.cpp
        src/board_generators.cpp
        src/interface.cpp
        src/logic.cpp
        src/players.cpp
        src/ship_sets.cpp)

target_include_directories(Battleship PUBLIC include)
