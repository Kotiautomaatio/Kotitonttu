cmake_minimum_required(VERSION 3.12)
project(koti)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

find_package(sdl2)

add_executable(koti apps/main.cpp)

target_include_directories(koti
        SYSTEM PUBLIC
        ${SDL2_INCLUDE_DIRS})
target_include_directories(koti
        PUBLIC
        include)

target_link_libraries(koti
        SDL2)