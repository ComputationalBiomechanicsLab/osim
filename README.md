# `osim.{a,lib}`

> A hack to make using/building OpenSim easier.

`osim` provides a build(system) for OpenSim where:

- All of its dependencies *may* be built as static libraries from source
  using only Cmake and a  C/C++ compiler, with the ability to choose where
  to source `libBLAS` and `libLACK` via cmake's `find_package`'s customization
  points.

- Simbody and OpenSim are unified into a single `CMakeLists.txt` file
  that produces a single statically-linkable target: `osim.{a,lib}`.

- No compiler flags are customized by the build, so that downstream code
  can easily modify the build with the appropriate environment variables
  (e.g. `CXXFLAGS`).

- Installs in a way that's mostly API-compatible with Simbody/OpenSim, so
  that it can be dropped into existing projects.

Another goal of this project is to gradually provide simplified CPython
bindings to `osim.so` with the aim of providing a simplified API for
making quick model modifications, plots, etc.


# Differences From Upstream Simbody/OpenSim

- **Moco is not supported**. Moco pulls in a bunch of additional third-party code,
  which makes building osim much more complicated. [OpenSim Creator](https://github.com/ComputationalBiomechanicsLab/opensim-creator),
  the main use-case for `osim`, doesn't use Moco, so we dropped Moco from the build
  entirely.

- **The OpenSim API must be manually initialized**. OpenSim's library initialization
  code now no longer automatically runs (e.g.) `RegisterTypes_X` during static
  initialization. This is because it's potentially incompatible with static
  linking. Instead, downstream code should manually call `RegisterTypes_` when the
  application starts. See `src/example_app.cpp` for an example of this.


# Building

```bash
# get simbody, opensim, OpenBLAS (optional), and spdlog sources
git submodule update --init --recursive

# configure third-party dependencies build
cmake -S third_party -B deps-build -DCMAKE_INSTALL_PREFIX=${PWD}/deps-install
# optional: use `-DOSIMDEPS_GET_OPENBLAS=OFF` to skip OpenBLAS if you're
#           planning on using an OS-provided BLAS+LAPACK

# build + install third-party dependencies
cmake --build deps-build

# configure osim (Simbody + OpenSim) build
cmake -S . -B build -DCMAKE_PREFIX_PATH=${PWD}/deps-install

# build osim
cmake --build build

# e.g.: this is why it's handy to build OpenBLAS /w static linking etc.
lddtree build/example_app
```

