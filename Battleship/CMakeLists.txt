cmake_minimum_required(VERSION 3.20)
project(Battleship)

set(CMAKE_CXX_STANDARD 17)

get_filename_component(LIB_PATH "./src" ABSOLUTE)

file(GLOB_RECURSE LIB_CXX_SOURCES ${LIB_PATH}/*.cpp)
file(GLOB_RECURSE LIB_HEADERS ${LIB_PATH}/*.hpp)

add_library(battleship_lib STATIC ${LIB_CXX_SOURCES} ${LIB_HEADERS})
target_include_directories(battleship_lib PUBLIC ${LIB_PATH})

add_executable(Battleship main.cpp)
target_link_libraries(Battleship battleship_lib)