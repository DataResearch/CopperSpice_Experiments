#!/bin/bash
cd build
ninja install | tee error.log
./example_1
