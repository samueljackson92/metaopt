FUNCTION(PREPEND var prefix)
   SET(listVar "")
   FOREACH(f ${ARGN})
      LIST(APPEND listVar "${prefix}/${f}")
   ENDFOREACH(f)
   SET(${var} "${listVar}" PARENT_SCOPE)
ENDFUNCTION(PREPEND)

PREPEND(MO_SOURCES ../ ${SRC_FILES})
PREPEND(MO_INCLUDES ../ ${INC_FILES})

set(BINDING_FILES
    swarm.cpp
    functions.cpp)

pybind11_add_module(pymetaopt python_bindings.cpp
    ${BINDING_FILES} ${MO_SOURCES} ${MO_INCLUDES})
