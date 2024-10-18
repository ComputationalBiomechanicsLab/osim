cmake_minimum_required(VERSION 3.15)

project(osim VERSION 0.0.1 LANGUAGES C CXX)

set(OSIM_INSTALL_OPENSIM_HEADERS         ON  CACHE BOOL "enable/disable installing libosim.a with Simbody/OpenSim headers (used by OpenSim Creator)")
set(OSIM_BUILD_BINDINGS                  OFF CACHE BOOL "enable/disable building python bindings")
set(OSIM_BUILD_APPS                      ON  CACHE BOOL "enable/disable building runnable applications")
set(OSIM_BUILD_TESTS                     ON  CACHE BOOL "enable/disable building test suites")

add_subdirectory(src)

if(${OSIM_BUILD_APPS})
    add_subdirectory(apps)
endif()

if(${OSIM_BUILD_TESTS})
    # enable testing in this top-level project, so that `ctest` works when
    # (e.g.) IDEs get a list of tests when they use `ctest --show-only`
    # to list all tests project-wide
    #
    # see:
    #
    # - https://cmake.org/cmake/help/latest/command/enable_testing.html
    # - https://developercommunity.visualstudio.com/t/test-explorer-doesnt-detect-tests/482451
    # - https://stackoverflow.com/a/67984312

    enable_testing()
    add_subdirectory(tests)
endif()

