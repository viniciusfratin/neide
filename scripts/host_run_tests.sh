#!/bin/sh

# This script should be executed from the repository root directory.

set -e

./scripts/host_build.sh
docker run --name neide_test --rm --tty viniciusfratin/neide_test:v0.1
