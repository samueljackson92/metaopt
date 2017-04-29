
set (LIBRARY_NAME optima)
set (INCLUDE_FILES
    array_helpers.hpp
    functions.hpp
    particle.hpp
    random_generator.hpp
    simulated_annealing.hpp
    swarm.hpp
    types.hpp
)

set (SRC_FILES
    random_generator.cpp
    particle.cpp
    simulated_annealing.cpp
    swarm.cpp
)

add_library(
    ${LIBRARY_NAME}
    SHARED
    ${SRC_FILES}
    ${INCLUDE_FILES}
    ${EIGEN3_LIBRARIES}
)
target_link_libraries(optima tbb)

target_compile_features(optima PRIVATE cxx_range_for)

# Python API
add_subdirectory(python)
# Unit tests
add_subdirectory(test)

