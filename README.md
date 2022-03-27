# neide
Home garden sprinkler system.

## Setup
Make sure you have Docker installed.

In order to create the Docker image after cloning this repository, run

> cd neide/
>
> docker build --no-cache -t viniciusfratin/neide:v0.1 -f ./docker/Dockerfile .

To instantiate a new container from the built image, run

> docker create --tty --name neide viniciusfratin/neide:v0.1

From now on, the build environment is setup in the container and the previous commands need not to be executed again.

## Build
In order to build the code and execute the tests, run

> docker start --attach neide