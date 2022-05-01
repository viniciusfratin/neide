# neide
Home garden sprinkler system.

## General prerequisites:
Make sure you have bash installed. This project was tested using bash version 4.4.23, but it should work 
with older versions too, as the scripts commands are very simple.

Although it is surely possible to build and run everything without Docker, it is **highly recommended**
to install and use it, as you will not have to worry about setting up the development environments.

## If you are using Docker:
### Setup
Make sure you have Docker installed.

Make sure that the working directory is the intended one by running

> cd neide/

### Tests
In order to execute the tests, run the following in bash:

> ./scripts/build_host_and_run_tests.sh

### Run sample
In order to run a sample for the system with mocked external data, run the following in bash:

> ./scripts/build_host_and_run_sample.sh

### Build files for target hardware
In order to get the target hardware files (current only supporting the Atmel ATmega328P microcontroller), run
the following in bash:

> ./scripts/build_target_and_copy_files.sh

The files will be in a newly created "target_files" folder.

## If you are not using Docker:
### Setup
Make sure you have the following prerequisites:
- CMake (>= 3.23)
- gcc (>= 9.4.0)
- g++ (>= 9.4.0)
- avr-gcc (>= 5.4.0)
- avr-g++ (>= 5.4.0)
- avr-objdump (>= 2.26.20160125)
- avr-objcopy (>= 2.26.20160125)
- avr-size (>= 2.26.20160125)

### Host environment
#### Build
Then, after cloning this repository, you can build by running

> cd neide/
>
> cmake -S software/ -B build/

followed by

> cmake --build build/

#### Tests
In order to execute the test suite, build the system and then run

> ctest --test-dir build/tests/

#### Run sample
In order to run a sample for the system with mocked external data, build the system and then run

> ./build/code/sample/sample

Note that the executable extension can vary between platforms, e.g., it would be called "sample" in Linux and "sample.exe" in Windows.

### Target environment
#### Build
You can build by running

> cd neide/
>
> cmake --toolchain absolute/path/to/neide/software/toolchains/generic-gcc-avr.cmake -S software/ -B build/

followed by

> cmake --build build/

The target hardware files will be located at "build/code/sample/". They are the following: 
- sample-atmega328p.elf
- sample-atmega328p.lst
- sample-atmega328p-eeprom.hex
- sample-atmega328p.hex
- sample-atmega328p.map