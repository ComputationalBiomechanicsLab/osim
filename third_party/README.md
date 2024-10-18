# `third_party`

> All of the source code necessary to "superbuild" `osim` from source

This directory contains:

- The source code for `simbody` and `opensim-core`, which is inlined
  into `osim`'s build (see: `../src/osim/CMakeLists.txt`)

- A separate `CMakeLists.txt` build that users can use to build all of
  `osim`'s dependencies from source, which is an easy way to build the
  project.

Apart from the inlined parts, the main `osim` build uniformly uses
`find_package` to find its dependencies. This means that you don't
*have* to build all dependencies from source. As long as cmake can
find the dependency--usually, via the OS library locations or whatever
`CMAKE_PREFIX_PATH` is set to--and the dependency is compatible with
osim (correct version, compatible API, etc.), then it'll work.

In particular, it can be handy to skip building `OpenBLAS` from source
by setting `-DOSIMDEPS_GET_OPENBLAS=OFF`. This will then cause `osim`'s
`find_package` calls to fall back to whatever the OS has which, on MacOS,
is going to be `Accelerate.framework` (hardware-accelerated) and, on Linux,
is going to be whatever the OS installed (e.g. `apt install openblas`, or
a hardware-specific implementation). Downstream projects can package linux
packages to automatically install those dependencies.

