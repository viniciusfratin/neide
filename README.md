# neide
Home garden sprinkler system.

## Build
Make sure you have CMake version 3.23 or above. Then, you can build by running

> cmake -G "<Your preferred generator>" -S software/ -B build/

followed by

> cmake --build build/

## Tests
In order to execute the test suite, build the system and then run

> ctest --test-dir build/tests/