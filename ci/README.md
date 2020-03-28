# CI: Makefile/Docker testing
To test the build, there is a Makefile in [ci](.) folder using
docker containers to test on various distro.

To get the help simply type:
```sh
make
```

note: you can also use from top directory
```sh
make --directory=ci
```

# Testing
For example to test inside a container:
```sh
make test_devel
```

# Dockerfile for CMake/C++/Qt Development Environment
Currently it build environment for one distribution:
* [Alpine Linux](https://alpinelinux.org/).

## Alpine Image

From [alpine:latest](https://hub.docker.com/r/alpine/)
* [cmake](https://pkgs.alpinelinux.org/package/edge/main/x86_64/cmake)
* [make](https://pkgs.alpinelinux.org/package/edge/main/x86_64/make)
* [gcc](https://pkgs.alpinelinux.org/package/edge/main/x86_64/gcc)
* [clang](https://pkgs.alpinelinux.org/package/edge/main/x86_64/clang)
* [doxygen](https://pkgs.alpinelinux.org/package/edge/main/x86_64/doxygen)
* [graphviz](https://pkgs.alpinelinux.org/package/edge/main/x86_64/graphviz)
