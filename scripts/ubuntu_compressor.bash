#!/usr/bin/env bash

docker run --rm -it --entrypoint Compressor --name ubuntu_compressor --mount type=bind,source=$(pwd),target=/tmp -w /tmp grial1/ubuntu_compressor:latest $@