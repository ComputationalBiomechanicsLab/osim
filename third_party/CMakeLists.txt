cmake_minimum_required(VERSION 3.15)

project(osim-dependencies)

set(OSCDEPS_BUILD_ALWAYS OFF CACHE BOOL "set BUILD_ALWAYS on all dependency targets, useful when editing dependencies")
set(OSIMDEPS_GET_OPENBLAS ON CACHE BOOL "enable getting + building OpenBLAS from source")
set(OSIMDEPS_GET_SPDLOG ON CACHE BOOL "enable getting + building spdlog from source")
set(OSIMDEPS_GET_PYBIND11 OFF CACHE BOOL "enable getting + building pybind11 from source")
set(OSIMDEPS_GET_CATCH2 OFF CACHE BOOL "enable getting + building catch2 from source")

include(ExternalProject)  # ExternalProject_Add
include(GNUInstallDirs)  # CMAKE_INSTALL_LIBDIR

# setup `OSCDEPS_DEPENDENCY_CMAKE_ARGS`
#
# these are cache args that should be forwarded to external dependency projects
if(TRUE)
    set(OSCDEPS_FORWARDED_VARS

        CMAKE_CXX_COMPILER
        CMAKE_C_COMPILER
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_MINSIZEREL
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_RELWITHDEBINFO
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_MINSIZEREL
        CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_RELWITHDEBINFO
        CMAKE_BUILD_TYPE
        CMAKE_INSTALL_PREFIX
        CMAKE_INSTALL_LIBDIR
    )
    foreach(OSCDEPS_FORWARDED_VAR IN LISTS OSCDEPS_FORWARDED_VARS)
        if(DEFINED OSCDEPS_FORWARDED_VAR)
            list(APPEND OSCDEPS_DEPENDENCY_CMAKE_ARGS -D${OSCDEPS_FORWARDED_VAR}:STRING=${${OSCDEPS_FORWARDED_VAR}})
        endif()
    endforeach()
    unset(OSCDEPS_FORWARDED_VARS)
endif()

if(${OSIMDEPS_GET_OPENBLAS})
    ExternalProject_Add(OpenBLAS
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/OpenBLAS
        BUILD_ALWAYS ${OSCDEPS_BUILD_ALWAYS}
        CMAKE_CACHE_ARGS
            ${OSCDEPS_DEPENDENCY_CMAKE_ARGS}
            -DC_LAPACK:BOOL=ON
            -DBUILD_STATIC_LIBS:BOOL=ON
    )
endif()

if(${OSIMDEPS_GET_SPDLOG})
    if(MSVC)
        # `spdlog` transitively uses a deprecated `stdext::checked_array_iterator`
	set(SPDLOG_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING")
    else()
        set(SPDLOC_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    endif()
    ExternalProject_Add(spdlog
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/spdlog
        BUILD_ALWAYS ${OSCDEPS_BUILD_ALWAYS}
        CMAKE_CACHE_ARGS
            ${OSCDEPS_DEPENDENCY_CMAKE_ARGS}
            -DSPDLOG_BUILD_BENCH:BOOL=OFF
            -DSPDLOG_BUILD_TESTS:BOOL=OFF
            -DSPDLOG_BUILD_EXAMPLE:BOOL=OFF
            -DSPDLOG_BUILD_SHARED:BOOL=OFF
            -DCMAKE_CXX_FLAGS:STRING=${SPDLOG_CXX_FLAGS}
    )
endif()

if(${OSIMDEPS_GET_PYBIND11})
    ExternalProject_Add(pybind11
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/pybind11
        BUILD_ALWAYS ${OSCDEPS_BUILD_ALWAYS}
        CMAKE_CACHE_ARGS
            ${OSCDEPS_DEPENDENCY_CMAKE_ARGS}
            -DPYBIND11_CMAKECONFIG_INSTALL_DIR:PATH=${CMAKE_INSTALL_PREFIX}/lib/cmake/pybind11
            -DPYBIND11_TEST:BOOL=OFF
    )
endif()

if(${OSIMDEPS_GET_CATCH})
    ExternalProject_Add(catch2
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch2
        BUILD_ALWAYS ${OSCDEPS_BUILD_ALWAYS}
        CMAKE_CACHE_ARGS
            ${OSCDEPS_DEPENDENCY_CMAKE_ARGS}
    )
endif()
