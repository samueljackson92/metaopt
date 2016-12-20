set(PYTHON_LIB_NAME pyoptima)
set(BINDING_FILES
    Swarm.cpp
    Functions.cpp)

pybind11_add_module(${PYTHON_LIB_NAME} MODULE python_bindings.cpp
    ${BINDING_FILES})
target_link_libraries(${PYTHON_LIB_NAME} PRIVATE ${LIBRARY_NAME})
set_target_properties(${PYTHON_LIB_NAME} PROPERTIES SUFFIX .so)
