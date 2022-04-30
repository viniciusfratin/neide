#!/bin/sh

docker build --tag viniciusfratin/neide_run_main:v0.1 --target neide_run_main --file ./docker/Dockerfile .
docker run --name neide_run_main --rm --tty viniciusfratin/neide_run_main:v0.1