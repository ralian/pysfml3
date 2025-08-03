# PySFML3 - Python Bindings for SFML v3

This library is still a work in progress. If you are interested in helping test or want to contribute, please contact me.

## Features

- Inspired by but distinct from the old PySFML library, PySFML3 is redesigned using PyBind11 and only targets Python 3 and SFMLv3+. The goal is to bring together the best of Modern C++ and Modern Python to cleanly wrap a powerful graphics library.

## Prerequisites

### Runtime

- **Python**: 3.10+? Still need to verify.
- **SFML**: 3.0.0+

### Buildtime

- **C++ Compiler**: C++20 and greater? MSVC has been tested, others have not.
- **CMake**: 3.24 or higher
- **PyBind11**: 3.0+

## Building Locally

### Windows

Ensure you have pybind11 and SFML installed. If you want to build them from scratch, it should be as simple as pulling both repos then from VS dev powershell calling `mkdir build; cd build; cmake ..; cmake --build .; cmake --install .` on each. SFML needs the `--config Debug` installed if you are building that. Also, pybind11 is header only and building only creates the tests. You can skip building but not installing if desired.

To configure `pysfml3`, simply run `cmake --preset debug .` in this dir, then `cmake --build --preset debug` to build.

Right now, install the resulting `.pyd` module in your favorite IDE manually to test.

## TODO

- Complete out the bindings, a lot of basic classes are missing
- Vulkan is not something I'm even touching yet
- Better default argument / kwarg handling for some things
- More docstrings. Debating just forwarding the link to the SFML docs in most of them...
