include(flags.cmake)
cmake_minimum_required(VERSION 3.17)
if (WIN32)
    #    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)
    #    set(VCPKG_TARGET_TRIPLET x64-windows-static)
    #    message("CMAKE_TOOLCHAIN_FILE = ${CMAKE_TOOLCHAIN_FILE}")
endif ()
project(Kotitonttu LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/utility-functions.cmake)
include(cmake/windows-specifics.cmake)

if (WIN32)
    windows_enforce_static_libraries()
endif ()

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/ext-libs/")
    list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
endif ()


find_package(Corrade CONFIG REQUIRED Utility)
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Magnum CONFIG REQUIRED GL Shaders Sdl2Application Text)
find_package(MagnumPlugins REQUIRED FreeTypeFont)
find_package(MagnumExtras REQUIRED Ui)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

include_directories(include)
add_subdirectory(src)
add_subdirectory(apps)

