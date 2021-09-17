#!/bin/bash

BUILD_SCRIPT_DIR="$(dirname "$0")"

# prepare build dir
cd $(dirname "$0")/../..
mkdir -p build
cd build

# create makefiles
qmake -r ../candle.pro

# build
make all install -j16

install -m644 ../src/candle/images/icon.svg -D "../bin/candle.svg"
