cmake_minimum_required(VERSION 3.27)
project(sw_battle_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src/Core)
add_subdirectory(src/IO)
add_subdirectory(src/Features)

file(GLOB MAIN_SOURCES
    src/main.cpp
)

add_executable(sw_battle_test ${MAIN_SOURCES})

target_link_libraries(sw_battle_test PRIVATE Features IO)

target_include_directories(sw_battle_test PUBLIC src/)
