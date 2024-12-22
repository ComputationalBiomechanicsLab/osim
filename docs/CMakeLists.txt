# ensure the user's build system has 'sphinx-build'
find_program(
    OSC_SPHINX_EXE  # can be overloaded on the cmake command line (`-DOSC_SPHINX_EXE=custom/path/sphinx-build`)
    "sphinx-build"
    DOC "Location of sphinx-build, which is used to compile the documentation"
    REQUIRED
)

# create a build target that builds the documentation using sphinx
add_custom_target(osimdocs
    COMMAND ${OSC_SPHINX_EXE} -M html ${CMAKE_CURRENT_SOURCE_DIR}/source ${CMAKE_CURRENT_BINARY_DIR}/build
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

