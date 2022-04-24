# neide
Home garden sprinkler system.

## If you are using Docker:
### Setup
Make sure you have Docker installed.

In order to create the Docker images after cloning this repository, run

> cd neide/
>
> docker build --tag viniciusfratin/neide_test:v0.1 --target neide_test --file ./docker/Dockerfile .
> docker build --tag viniciusfratin/neide_run_main:v0.1 --target neide_run_main --file ./docker/Dockerfile .

The built code will be inside both images.

**Note**: This command needs not to be executed again, unless there is some change to the code.

### Tests
In order to execute the tests, run

> docker run --name neide_test --rm --tty viniciusfratin/neide_test:v0.1

In case you make a change to the code, refer to the **Note** in the previous section.

### Run sample
In order to run a sample for the system with mocked external data, run

> docker run --name neide_run_main --rm --tty viniciusfratin/neide_run_main:v0.1

In case you make a change to the code, refer to the **Note** in the previous section.

## If you are not using Docker:
### Setup
Make sure you have the following prerequisites:
- CMake (>= 3.23)
- gcc (>= 9.4.0)
- g++ (>= 9.4.0)

### Build
Then, after cloning this repository, you can build by running

> cd neide/
>
> cmake -S software/ -B build/

followed by

> cmake --build build/

### Tests
In order to execute the test suite, build the system and then run

> ctest --test-dir build/tests/

### Run sample
In order to run a sample for the system with mocked external data, run

> ./build/code/main/main

Note that the executable extension can vary between platforms, e.g., it would be called "main" in Linux and "main.exe" in Windows.