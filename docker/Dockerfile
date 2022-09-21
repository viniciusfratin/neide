# syntax=docker/dockerfile:1
FROM ubuntu:18.04 AS neide_base
ENV PATH="/opt/cmake-3.23.0-rc5-linux-x86_64/bin:${PATH}"
RUN apt-get update \
    && apt-get install -y \
    build-essential=12.4ubuntu1 \
    curl=7.58.0-2ubuntu3.20 \
    && apt-get clean
RUN curl -sSL https://cmake.org/files/v3.23/cmake-3.23.0-rc5-linux-x86_64.tar.gz \
    | tar -xzC /opt

FROM neide_base AS neide_base_target
RUN apt-get update \
    && apt-get install -y \
    gcc-avr=1:5.4.0+Atmel3.6.0-1build1 \
    binutils-avr=2.26.20160125+Atmel3.6.0-1 \
    avr-libc=1:2.0.0+Atmel3.6.0-1 \
    && apt-get clean

FROM neide_base AS neide_build_host
RUN mkdir -p /neide
WORKDIR /neide
COPY ./software /neide/software
RUN cmake -S software/ -B build/ \
    && cmake --build build/
    
FROM neide_build_host AS neide_test
WORKDIR /neide
CMD ctest --test-dir build/tests/ --rerun-failed --output-on-failure

FROM neide_build_host AS neide_run_sample
WORKDIR /neide
CMD ./build/code/sample/sample

FROM neide_base_target AS neide_build_target
RUN mkdir -p /neide
RUN mkdir -p /neide_out/arduino
WORKDIR /neide
COPY ./software /neide/software
RUN cmake --toolchain /neide/software/toolchains/generic-gcc-avr.cmake \
    -S software/ -B build/ \
    && cmake --build build/ \
    && cp \
    build/code/arduino/arduino-atmega328p.elf \
    build/code/arduino/arduino-atmega328p.lst \
    build/code/arduino/arduino-atmega328p-eeprom.hex \
    build/code/arduino/arduino-atmega328p.hex \
    build/code/arduino/arduino-atmega328p.map \
    /neide_out/arduino