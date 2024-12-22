cmake_minimum_required(VERSION 3.15)

project(osim VERSION 0.0.1 LANGUAGES CXX)

set(OSIM_BUILD_BINDINGS OFF CACHE BOOL "enable/disable building python bindings")
set(OSIM_BUILD_TESTS    OFF CACHE BOOL "enable/disable building test suites")
set(OSIM_BUILD_DOCS     OFF CACHE BOOL "enable/disable building user documentation")

add_subdirectory(src)

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

if(${OSIM_BUILD_DOCS})
    add_subdirectory(docs)
endif()
