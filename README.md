[![Build Status][github_status]][github_link]
[![Build Status][travis_status]][travis_link]
[![Build Status][appveyor_status]][appveyor_link]

[github_status]: https://github.com/Mizux/dice/workflows/C++%20CI/badge.svg
[github_link]: https://github.com/Mizux/dice/actions

[travis_status]: https://travis-ci.com/Mizux/dice.svg?branch=master
[travis_link]: https://travis-ci.com/Mizux/dice

[appveyor_status]: https://ci.appveyor.com/api/projects/status/627v95pcklcn9aey/branch/master?svg=true
[appveyor_link]: https://ci.appveyor.com/project/Mizux/dice/branch/master

# Introduction
Some dice stuff work in progress...

# Project directory layout
Thus the project layout is as follow:

* [CMakeLists.txt](CMakeLists.txt) Top-level for [CMake](https://cmake.org/cmake/help/latest/) based build.
* [cmake](cmake) Subsidiary CMake files.

* [ci](ci) Top-level directory for Makefile/docker CI.

# C++ Project Build
To build the C++ project, as usual:
```sh
cmake -S. -Bbuild -DBUILD_TYPE=Release
cmake --build build --config Release --target all
CTEST_OUTPUT_ON_FAILURE=1 cmake --build build --target test
```
