#!/bin/bash

set -e


if [ -d  "./build" ]
then
    echo "rm -rf ./build/"
    rm -rf ./build
fi

echo "mkdir ./build"
mkdir ./build

echo "cd ./build"
cd ./build


echo "cmake .."
cmake ..

echo "make"
make
