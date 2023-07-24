cmake_minimum_required(VERSION 3.17)
project(bomberman)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)
find_package(raylib 2.5.0 REQUIRED)

set(SRCS
./src/menu.cpp
./src/bombermanbombs.cpp
./src/bombermanplayer.cpp
)

include_directories(/lib)

add_executable(bomberman ${SRCS})

target_link_libraries(bomberman raylib)