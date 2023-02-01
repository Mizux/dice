# Create a virtual environment with all tools installed
# ref: https://hub.docker.com/_/ubuntu
FROM ubuntu:latest AS env
# Install system build dependencies
ENV PATH=/usr/local/bin:$PATH
RUN ln -snf /usr/share/zoneinfo/Europe/Paris /etc/localtime \
&& echo Europe/Paris > /etc/timezone

# qt6-base-dev
# jammy(22.04): need missing libgl-dev
# kinetic(22.10): libgl-dev already a deps of the package
RUN apt update -qq \
&& apt install -yq \
git wget libssl-dev build-essential cmake qt6-base-dev libgl-dev \
&& apt-get clean \
&& rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

FROM env AS devel
WORKDIR /home/app
COPY . .

FROM devel AS build
RUN cmake -version
RUN cmake -S. -Bbuild
RUN cmake --build build --target all -v
RUN cmake --build build --target install -v -- DESTDIR=install

FROM build AS test
RUN cmake --build build --target test

# Create a production image
FROM ubuntu:latest AS prod
RUN ln -snf /usr/share/zoneinfo/Europe/Paris /etc/localtime \
&& echo Europe/Paris > /etc/timezone

RUN apt-get update -qq \
&& apt-get install -yq qtbase5-dev \
&& apt-get clean \
&& rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# Create app directory
WORKDIR /home/app
COPY --from=build /home/app/build/install/usr/local/ .
