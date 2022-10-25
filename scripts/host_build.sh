#!/bin/sh

# This script should be executed from the repository root directory.

set -e

docker build --tag viniciusfratin/neide_test:v0.1 --target neide_test --file ./docker/Dockerfile .
docker build --tag viniciusfratin/neide_run_sample:v0.1 --target neide_run_sample --file ./docker/Dockerfile .
