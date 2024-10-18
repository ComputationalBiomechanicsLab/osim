add_subdirectory(osim)

if(${OSIM_BUILD_BINDINGS})
    add_subdirectory(pyosim)
endif()

