cmake_minimum_required(VERSION 3.21)
project(InputBuffer VERSION 0.1.0)

# Build with the Geode CLI / Geode SDK environment.
# `geode build` should configure and package this project.
add_subdirectory(${GEODE_SDK} ${CMAKE_BINARY_DIR}/geode)
setup_geode_mod()
