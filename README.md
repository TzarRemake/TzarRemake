# TzarRemake [![Build Status](https://travis-ci.org/TzarRemake/TzarRemake.svg?branch=master)](https://travis-ci.org/TzarRemake/TzarRemake)
Is an fanmade remake of game **Tzar: The Burden Of The Crown**.

# Building
You will need CMake tool (3.2+) and modern GCC (or MinGW 6.1+ on Windows) compiler that support C++14.
In addition we'r using SFML (2.4+) for rendering, audio etc. You need to set environment varaiable `SFML_ROOT` to your SFML library directory.

### Linux and MacOS:
```bash
cd path/to/TzarRemake
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

### Windows
```bash
cd path/to/TzarRemake
mkdir build
cd build
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
mingw32-make
```

### Why we are doing this?
Because we can. No seriously we're like to learn new standard of C++ in practice, so why not rewrite our favorite game. Unfortunately, we don't promise that the project will be ever completed.

