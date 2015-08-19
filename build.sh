#!/bin/bash

mkdir -p build
cd build
cmake ../
START=$(date +%s)
make -j8
END=$(date +%s)
echo "Total Build time (real) = $(( $END - $START )) seconds"
