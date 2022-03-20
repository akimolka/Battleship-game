cmake_minimum_required(VERSION 3.20)
project(Battleship)

set(CMAKE_CXX_STANDARD 17)

add_executable(Battleship main.cpp Entities.cpp BoardGenerators.cpp
        Input.cpp Output.cpp Logic.cpp Players.cpp ShipSets.cpp)
#add_library(Entities SHARED Entities.cpp)
#add_library(BoardGenerators SHARED BoardGenerators.cpp)
#add_library(Input SHARED Input.cpp)
#add_library(Output SHARED Output.cpp)
#add_library(Logic SHARED Logic.cpp)
#add_library(Players SHARED Players.cpp)
#add_library(ShipSets SHARED ShipSets.cpp)
#target_link_libraries(Battleship Entities BoardGenerators Input Output Logic Players ShipSets)

