
cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(InputBuffer VERSION 0.2.0)

# Target Geometry Dash 2.208
set(GEODE_GD_VERSION 2.208 CACHE STRING "Geometry Dash version" FORCE)
set(GEODE_COMP_GD_VERSION 2208 CACHE STRING "Comparable GD version" FORCE)

if(NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK!")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod()

