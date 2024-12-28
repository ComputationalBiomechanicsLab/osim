list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(FindPython3)

find_package(Python COMPONENTS Interpreter REQUIRED)
find_package(Pytest REQUIRED)

add_custom_target(testpyosim ALL
    COMMAND ${CMAKE_COMMAND} -E env PYTHONPATH=$<TARGET_PROPERTY:pyosim,BINARY_DIR> "${Python_EXECUTABLE}" -m pytest
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    DEPENDS pyosim
)
