#!/bin/sh

set -e

rm -rf target_files
docker build --tag viniciusfratin/neide_build_target:v0.1 --target neide_build_target --file ./docker/Dockerfile .
docker run --name neide_build_target --rm --tty --detach viniciusfratin/neide_build_target:v0.1 bash
docker cp neide_build_target:/neide_out .
docker stop neide_build_target
mv neide_out target_files