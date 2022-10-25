#!/bin/sh

# This script should be executed from the repository root directory.

set -e

docker build --tag viniciusfratin/neide_build_target:v0.1 --target neide_build_target --file ./docker/Dockerfile .
