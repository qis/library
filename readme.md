# Library
C++ library project template (similar to <https://github.com/qis/application>).

## Linux
```sh
# Install tools.
sudo apt install build-essential curl git ninja-build pkg-config unzip wget zip

# Install cmake.
sudo rm -rf /opt/cmake; sudo mkdir -p /opt/cmake
wget https://github.com/Kitware/CMake/releases/download/v3.29.6/cmake-3.29.6-linux-x86_64.tar.gz
sudo tar xf cmake-3.29.6-Linux-x86_64.tar.gz -C /opt/cmake --strip-components=1
rm -f cmake-3.29.6-Linux-x86_64.tar.gz

sudo tee /etc/profile.d/cmake.sh >/dev/null <<'EOF'
export PATH="/opt/cmake/bin:${PATH}"
EOF

sudo chmod 0755 /etc/profile.d/cmake.sh
. /etc/profile.d/cmake.sh

# Install vcpkg.
sudo rm -rf /opt/vcpkg; sudo mkdir -p /opt/vcpkg
sudo chown $(id -u):$(id -g) /opt/vcpkg
git clone https://github.com/microsoft/vcpkg /opt/vcpkg
/opt/vcpkg/bootstrap-vcpkg.sh

sudo tee /etc/profile.d/vcpkg.sh >/dev/null <<'EOF'
export VCPKG_ROOT="/opt/vcpkg"
export PATH="${VCPKG_ROOT}:${PATH}"
EOF

sudo chmod 0755 /etc/profile.d/vcpkg.sh
. /etc/profile.d/vcpkg.sh
```

## Windows
1. Install [Visual Studio][vsc].
2. Install [Ninja][nbs] and add it to `%PATH%`.

## Build
Open the directory as a CMake project in Visual Studio or use [makefile](makefile) commands:

```sh
# Build library.
make # CONFIG=Debug
make CONFIG=Release

# Build and run main.
make run # CONFIG=Debug
make run CONFIG=RelWithDebInfo

# Build and run tests.
make test

# Build and run benchmarks.
make benchmark

# Install library.
make install

# Uninstall library.
make uninstall

# Delete build directory.
make clean
```

## Usage
Add library as git submodule to your project.

```sh
git submodule add https://github.com/qis/library third_party/library
```

Add library as a vcpkg overlay to your `vcpkg-configuration.json` file.

```json
{
  // ...
  "overlay-ports": [
    "./third_party/library"
  ]
}
```

Add library as a dependency to your `vcpkg.json` file.

```json
{
  // ...
  "dependencies": [
    "library"
  ]
}
```

Add library to your `CMakeLists.txt` file.

```cmake
find_package(library CONFIG REQUIRED)
target_link_libraries(main PRIVATE library::library)
```

Use library in your project.

```cpp
#include <library.hpp>
#include <cstdio>

int main() {
  std::puts(library::random().data());
  std::puts(LIBRARY_VERSION);
}
```

## Template
Use template to create a new project.

1. Update this readme file.
2. Update `project` in [CMakeLists.txt](CMakeLists.txt).
3. Update `Project Headers` in [.clang-format](.clang-format).
4. Update info and dependencies in [vcpkg.json](vcpkg.json).
5. Update dependencies in [res/config.cmake.in](res/config.cmake.in).
6. Update [vcpkg-configuration.json](vcpkg-configuration.json) with `vcpkg x-update-baseline`.
7. Rename [include/library](include/library), [include/library.hpp](include/library.hpp)
   and [src/library](src/library) to new project name.
8. Update sources in [include](include) and [src](src).
9. Update project license in [license.txt](license.txt).

[vsc]: https://visualstudio.microsoft.com/vs/community
[nbs]: https://github.com/ninja-build/ninja/releases
