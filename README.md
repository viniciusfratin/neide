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
- gcc (>= 7.5.0)
- g++ (>= 7.5.0)
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

The target hardware files will be located at "build/code/arduino/". They are the following: 
- arduino-atmega328p.elf
- arduino-atmega328p.lst
- arduino-atmega328p-eeprom.hex
- arduino-atmega328p.hex
- arduino-atmega328p.map

## Burning to microcontroller
In order to burn to ATmega328P, you can use a tool called "avrdude", which is open source and free.

After generating the target files (see above), the following command suffices, but may need to slighty
changed depending on your bootloader version (e.g., by changing the baud rate):

> avrdude -v -p atmega328p -c arduino -P COM5 -b 57600 -D -U flash:w:your/path/to/repo/neide/target_files/arduino/arduino-atmega328p.hex:i

Also make sure that the COM port ("COM5" in the case above) matches the one to which your device is connected.