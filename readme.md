# Library
C++ library project template.

## Dependencies
See [qis/toolchains](https://github.com/qis/toolchains) for vcpkg setup instructions.

```sh
vcpkg install --editable doctest benchmark fmt
```

## Build
Open the directory as a CMake project in Visual Studio or use [makefile](makefile) commands.

* `make` to build (debug)
* `make run` to run (debug)
* `make test` to run tests (debug, release)
* `make benchmark` to run benchmarks (release)
* `make install` to install into `build/install` (release)
* `make format` to format code with [clang-format](https://llvm.org/builds/)
* `make clean` to remove build files

## Install
Install this library as a vcpkg port.

```sh
vcpkg --overlay-ports=<path-to-library> library
```
