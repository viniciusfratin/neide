# neide
Home garden sprinkler system.

## If you are using Docker:
### Setup
Make sure you have Docker installed.

In order to create the Docker image after cloning this repository, run

> cd neide/
>
> docker build --no-cache -t viniciusfratin/neide:v0.1 -f ./docker/Dockerfile .

To instantiate a new container from the built image, run

> docker create --tty --name neide viniciusfratin/neide:v0.1

From now on, the build environment is setup in the container and the previous commands need not to be executed again.

### Build
In order to build the code and execute the tests, run

> docker start --attach neide

## If you are not using Docker:
### Setup
Make sure you have the following prerequisites:
- CMake (>= 3.23)
- gcc (>= 11.2.0)
- g++ (>= 11.2.0)

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