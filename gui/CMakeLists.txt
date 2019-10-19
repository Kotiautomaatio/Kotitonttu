cmake_minimum_required(VERSION 3.12)
project(koti)

set(CMAKE_CXX_STANDARD 17)

message(STATUS "PROJECT_SOURCE_DIR is ${PROJECT_SOURCE_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/ext-libs/")

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/modules/")

find_package(Magnum REQUIRED GL Shaders Sdl2Application Text)
find_package(MagnumPlugins REQUIRED FreeTypeFont)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

corrade_add_resource(TextExample_RESOURCES apps/resources.conf)

add_executable(koti
        apps/main.cpp
        ${TextExample_RESOURCES})

target_include_directories(koti
        PUBLIC
        include)

target_link_libraries(koti
        Magnum::Magnum
        Magnum::Application
        Magnum::GL
        Magnum::Shaders
        Magnum::Text
        MagnumPlugins::FreeTypeFont)
