#!/bin/sh

docker build --tag viniciusfratin/neide_test:v0.1 --target neide_test --file ./docker/Dockerfile .
docker run --name neide_test --rm --tty viniciusfratin/neide_test:v0.1