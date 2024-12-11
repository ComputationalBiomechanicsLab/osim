include(FindPython3)

find_package(Python 3.9 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)
pybind11_add_module(pyosim pyosim.cpp)


