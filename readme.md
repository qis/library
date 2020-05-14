# Library
C++ library project template.

## Requirements
Use [Visual Studio 2019](https://visualstudio.microsoft.com/) on Windows
and [LLVM 10](https://llvm.org/) or [GCC 10](https://gcc.gnu.org/) on Linux.

Use [Vcpkg](https://github.com/microsoft/vcpkg) to install dependencies.

```sh
vcpkg install benchmark catch2 fmt
```

## Build
Open the directory as a CMake project in Visual Studio or use [makefile](makefile) commands.

* `make` to build (debug)
* `make run` to run (debug)
* `make test` to run tests (debug and release)
* `make benchmark` to run benchmarks (release)
* `make install` to install into `build/install` (release)
* `make format` to format code with [clang-format](https://llvm.org/builds/)
* `make clean` to remove build files

Add `config=release` to build in release mode.

## Install
Install this library as a vcpkg port.

```sh
vcpkg --overlay-ports=<path-to-library> library
```
