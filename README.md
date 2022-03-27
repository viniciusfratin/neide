# neide
Home garden sprinkler system.

## If you are using Docker:
### Setup
Make sure you have Docker installed.

In order to create the Docker image after cloning this repository, run

> cd neide/
>
> docker build -t viniciusfratin/neide:v0.1 -f ./docker/Dockerfile .

**Note**: This command needs not to be executed again, unless there is some change to the code.

### Build
In order to build the code and execute the tests, run

> docker run --name neide --rm --tty viniciusfratin/neide:v0.1

In case you make a change to the code, refer to the **Note** in the previous section.

## If you are not using Docker:
### Setup
Make sure you have the following prerequisites:
- CMake (>= 3.23)
- gcc (>= 9.2.0)
- g++ (>= 9.2.0)

### Build and Tests
Then, after cloning this repository, you can build by running

> cd neide/
>
> cmake -S software/ -B build/

followed by

> cmake --build build/

### Tests
In order to execute the test suite, build the system and then run

> ctest --test-dir build/tests/