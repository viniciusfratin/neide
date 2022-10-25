#!/bin/sh

# This script should be executed from the repository root directory.

set -e

./scripts/target_build.sh
rm -rf target_files
docker run --name neide_build_target --rm --tty --detach viniciusfratin/neide_build_target:v0.1 bash
docker cp neide_build_target:/home/user/neide_out .
docker stop neide_build_target
mv neide_out target_files
