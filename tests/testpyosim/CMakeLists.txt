include(FindPython3)
find_package(Python COMPONENTS Interpreter REQUIRED)

add_custom_target(testpyosim ALL
    COMMAND ${CMAKE_COMMAND} -E env PYTHONPATH=$<TARGET_PROPERTY:pyosim,BINARY_DIR> "${Python_EXECUTABLE}" ${CMAKE_CURRENT_SOURCE_DIR}/testpyosim.py
    SOURCES
        testpyosim.py
)
