cmake_minimum_required(VERSION 3.1)
project(optima CXX)

# Setup build config
# ------------------------------------------------------------------------------
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_compile_options(-std=c++11)

# Find Libraries
# ------------------------------------------------------------------------------
find_package(Eigen3 3.2 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
link_directories(${EIGEN3_LIBRARIES})

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

set(CATCH_LIBARY_INCLUDES ${PROJECT_SOURCE_DIR}/Catch/include)

find_package(TBB REQUIRED)

# Add sub directories 
# ------------------------------------------------------------------------------
set(PYBIND11_CPP_STANDARD -std=c++11)
add_subdirectory(pybind11)
add_subdirectory(src)
add_subdirectory(python_tests)

# Enable ctest 
# ------------------------------------------------------------------------------
enable_testing()
add_test(NAME all COMMAND optima-tests)

