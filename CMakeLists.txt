include(flags.cmake)
cmake_minimum_required(VERSION 3.12)
project(koti)

set(CMAKE_CXX_STANDARD 17)

message(STATUS "PROJECT_SOURCE_DIR is ${PROJECT_SOURCE_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/ext-libs/")

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

find_package(Magnum REQUIRED GL Shaders Sdl2Application Text)
find_package(MagnumPlugins REQUIRED FreeTypeFont)
find_package(MagnumExtras REQUIRED Ui)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

include_directories(include)
add_subdirectory(src)
add_subdirectory(apps)
