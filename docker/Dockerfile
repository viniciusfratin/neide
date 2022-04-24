# syntax=docker/dockerfile:1
FROM ubuntu:20.04 AS neide_base
ENV PATH="/opt/cmake-3.23.0-rc5-linux-x86_64/bin:${PATH}"
RUN apt-get update \
    && apt-get install -y \
    build-essential=12.8ubuntu1 \
    curl=7.68.0-1ubuntu2.7 \
    && apt-get clean
RUN curl -sSL https://cmake.org/files/v3.23/cmake-3.23.0-rc5-linux-x86_64.tar.gz \
    | tar -xzC /opt

FROM neide_base AS neide_build
RUN mkdir -p /neide
WORKDIR /neide
COPY ./software /neide/software
RUN cmake -S software/ -B build/ \
    && cmake --build build/
    
FROM neide_build AS neide_test
WORKDIR /neide
CMD ctest --test-dir build/tests/ --rerun-failed --output-on-failure

FROM neide_build AS neide_run_main
WORKDIR /neide
CMD ./build/code/main/main