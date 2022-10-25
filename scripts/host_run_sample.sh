#!/bin/sh

# This script should be executed from the repository root directory.

set -e

./scripts/host_build.sh
docker run --name neide_run_sample --rm --tty viniciusfratin/neide_run_sample:v0.1
