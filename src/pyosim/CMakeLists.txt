include(FindPython3)

find_package(Python3 COMPONENTS Development NumPy)

add_library(pyosim SHARED lib.cpp)
target_link_libraries(lib PUBLIC osim Python3::Python)

