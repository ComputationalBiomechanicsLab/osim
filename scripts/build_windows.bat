REM this uses hard-coded paths etc. because this is mostly useful for rapidly getting
REM a build environment up on my Windows machine. Use at your own peril etc.

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
cmake -S third_party -B osim-dependencies-build -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_INSTALL_PREFIX=%cd%/install -DOSIMDEPS_GET_OPENBLAS=ON
cmake --build osim-dependencies-build --config RelWithDebInfo
cmake -S . -B osim-build -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_PREFIX_PATH=%cd%/install -DCMAKE_INSTALL_PREFIX=%cd%/install
cmake --build osim-build --config RelWithDebInfo
ctest --test-dir osim-build
