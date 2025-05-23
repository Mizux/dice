# Create a virtual environment with all tools installed
# ref: https://hub.docker.com/_/ubuntu
FROM ubuntu:latest AS env
# Install system build dependencies
ENV PATH=/usr/local/bin:$PATH
RUN apt-get update -qq \
&& DEBIAN_FRONTEND=noninteractive apt-get install -yq \
 git wget libssl-dev \
 build-essential ninja-build \
 pkgconf libglib2.0-dev \
 python3 python3-venv \
&& apt-get clean \
&& rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*
ENTRYPOINT ["/usr/bin/bash", "-c"]
CMD ["/usr/bin/bash"]

# Install CMake 3.28.3
RUN wget "https://cmake.org/files/v3.28/cmake-3.28.3-linux-x86_64.sh" \
&& chmod a+x cmake-3.28.3-linux-x86_64.sh \
&& ./cmake-3.28.3-linux-x86_64.sh --prefix=/usr/local/ --skip-license \
&& rm cmake-3.28.3-linux-x86_64.sh

FROM env AS devel
WORKDIR /home/project
COPY . .

ARG TARGET
ENV TARGET=${TARGET:-unknown}

FROM devel AS build
RUN cmake --version
RUN ./tools/cross_compile.sh build

FROM build AS test
RUN ./tools/cross_compile.sh qemu
RUN ./tools/cross_compile.sh test
