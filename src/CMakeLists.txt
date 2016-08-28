find_package(Eigen3 3.0 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
link_directories(${EIGEN3_LIBRARIES})

set (LIBRARY_NAME metaopt)
set (INCLUDE_FILES
    ArrayHelpers.h
    Particle.h
    Swarm.h
    Types.h
    functions.h)

set (SRC_FILES
    Particle.cpp
    Swarm.cpp)

add_library(
    ${LIBRARY_NAME}
    SHARED
    ${SRC_FILES}
    ${INCLUDE_FILES}
    ${EIGEN3_LIBRARIES}
)

target_compile_features(${LIBRARY_NAME} PRIVATE cxx_range_for)

# Python API
add_subdirectory(python)
# Unit tests
add_subdirectory(test)

