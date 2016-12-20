set(BINDING_FILES
    Swarm.cpp
    Functions.cpp)

pybind11_add_module(pymetaopt MODULE python_bindings.cpp
    ${BINDING_FILES} ${MO_SOURCES} ${MO_INCLUDES})
target_link_libraries(pymetaopt PRIVATE ${LIBRARY_NAME})
set_target_properties(pymetaopt PROPERTIES SUFFIX .so)
