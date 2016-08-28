
set(TEST_EXEC_NAME MetaOptTests)
set(ALL_TEST_FILES
    catch_main.cpp
    SwarmTest.cpp
    ParticleTest.cpp
)

add_executable(${TEST_EXEC_NAME} ${ALL_TEST_FILES})
target_include_directories(${TEST_EXEC_NAME} PRIVATE ${CATCH_LIBARY_INCLUDES})
target_link_libraries(${TEST_EXEC_NAME} ${LIBRARY_NAME})
set_property(TARGET ${TEST_EXEC_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${TEST_EXEC_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

