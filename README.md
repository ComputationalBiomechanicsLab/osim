# osim

> A minimalistic take on OpenSim.

> **Warning**
> This is a very very early alpha concept that's only really used internally by
> [OpenSim Creator](https://www.opensimcreator.com/). Use at your own risk 💥.


# 👓 Overview

`osim` provides an edited form of [OpenSim](https://github.com/opensim-org/opensim-core) that
focuses on build simplicity at the cost of Moco and script bindings. It has several features
that are useful for application builders:

- All of its dependencies *may* be built as static libraries from source
  using only Cmake and a  C/C++ compiler. `osim` uniformly uses `find_package`
  to source those dependencies, which means that you can cusomize where (e.g.)	
  `libBLAS` and `libLACK` are sourced from.

- All of the source files for [simbody](https://github.com/simbody/simbody) and [opensim-core](https://github.com/opensim-org/opensim-core) are
  pulled, mostly unmodified, into a single `CMakeLists.txt` file ([this](src/osim/CMakeLists.txt) one) that
  builds a single statically-linkable CMake target, `osim.{a,lib}`, that contains everything that
  [OpenSim Creator](https://github.com/ComputationalBiomechanicsLab/opensim-creator) uses.

- No compiler flags are customized by the build. This means that downstream code can easily modify the
  build with environment variables (e.g. `CXXFLAGS`), which makes it easier to create custom builds
  (e.g. libASAN, `march=native`, etc.).

- No `CMAKE_` variables are set by `osim`'s `CMakeLists.txt`, which means that you can source build
  `osim` in a downstream project with `add_subdirectory(osim)` and `target_link_libraries(yourapp PUBLIC osim)`,
  rather than having to create a separate pre-build pre-installation (handy for throwaway projects).

- `osim` `install`s in a way that's API-compatible with Simbody/OpenSim (i.e. the same header files are
  installed in the same places). This means that `osim` can be dropped into existing projects as easily
  as swapping something like `add_executable(app STATIC osimCommon osimSimulation...)` to
  `add_executable(app STATIC osim)`. [OpenSim Creator](https://github.com/ComputationalBiomechanicsLab/opensim-creator), a
  ~100kLOC OpenSim codebase, was ported this way with very minimal changes.


# 📋 Differences From Upstream Simbody/OpenSim

- **Moco is not supported**. Moco pulls in a bunch of additional third-party code,
  which makes building osim much more complicated. [OpenSim Creator](https://github.com/ComputationalBiomechanicsLab/opensim-creator),
  the primary downstream user of `osim`, doesn't use Moco, so Moco was entirely
  dropped from the build.

- **Scripting bindings are not supported**. `osim` is only a native build of
  OpenSim that is intended for use in downstream C/C++ projects. The SWIG-based
  binding generation used by OpenSim is not something this project plans on
  supporting because (frankly) it's a giant pain in the ass. Instead, our vision
  would be to create purpose-built bindings to OpenSim that closely match the host
  language's ecosystem, followed by gradually merging those bindings into OpenSim
  once we get an idea of what the community actually wants from bindings.

- **The OpenSim API must be manually initialized**. OpenSim's library initialization
  code now no longer automatically runs during static initialization (e.g. via `RegisterTypes_X`).
  This is because it's potentially incompatible with static linking. Instead, downstream
  code should manually call `osim::init`, provided via `#include <osim/osim.h>`, at
  application initialization time.

- **`osim` adds third-party components**. Additional `OpenSim::Component`s may be added
  by `osim` because researchers have asked for them to be supported in [OpenSim Creator](https://github.com/ComputationalBiomechanicsLab/opensim-creator). If
  those components see increased usage then we plan on upstreaming them to [opensim-core](https://github.com/opensim-org/opensim-core).


# 🏗️ Building

```bash
# get simbody, opensim, OpenBLAS, and spdlog source submodules
git submodule update --init --recursive

# configure third-party dependencies build
cmake -S third_party -B deps-build -DCMAKE_INSTALL_PREFIX=${PWD}/deps-install
# optional: use `-DOSIMDEPS_GET_OPENBLAS=OFF` to skip OpenBLAS if you're
#           planning on using an OS-provided BLAS+LAPACK (Linux/Mac)

# build + install OpenBLAS/spdlog
cmake --build deps-build
# optional: use `-jN` to configure parallelism

# configure osim build (includes OpenSim and Simbody sources)
cmake -S . -B build -DCMAKE_PREFIX_PATH=${PWD}/deps-install

# build osim
cmake --build build
```


# 🤓 Developing

If you want to develop the build system, or `osim`'s minimal offering of source files, then
you can edit those in-tree here.

If you want to develop [opensim-core](https://github.com/opensim-org/opensim-core) or
[simbody](https://github.com/simbody/simbody), but want to use `osim`'s build system (e.g.
because it's easier to set up) then you should change the submodules this project uses to
the fork you're working on, e.g.:

```bash
cd third_party/opensim-core
git remote add dev https://github.com/someuser/somefork
git checkout dev/somefeature

# edit the source code appropriately, make sure to push the changes to `dev/somefeature`

# building `osim` should pull in your changed `opensim-core` sources, because `osim` is
# a source-build of `opensim-core`'s/`simbody`'s `.cpp`/`.h` files
```
