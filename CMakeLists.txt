cmake_minimum_required(VERSION 3.1)
project(metaopt CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set (CATCH_LIBARY_INCLUDES ${PROJECT_SOURCE_DIR}/Catch/include)

add_subdirectory(pybind11)
add_subdirectory(src)
