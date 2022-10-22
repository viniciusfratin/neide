#!/bin/sh

set -e

docker build --tag viniciusfratin/neide_run_sample:v0.1 --target neide_run_sample --file ./docker/Dockerfile .
docker run --name neide_run_sample --rm --tty viniciusfratin/neide_run_sample:v0.1