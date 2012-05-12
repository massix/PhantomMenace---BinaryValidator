# Main CMakeListst file

cmake_minimum_required(VERSION 2.0)

project(PMValidator)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
add_subdirectory(src)
