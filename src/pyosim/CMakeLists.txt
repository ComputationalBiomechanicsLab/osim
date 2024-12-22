include(FindPython3)

find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(pyosim pyosim.cpp)
target_link_libraries(pyosim PRIVATE pybind11::module osim)
