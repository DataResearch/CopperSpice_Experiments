#!/bin/bash
# expects the sysvariable CopperSpice_DIR to be set to the cmake directory of a CopperSpice library distribution.
cmake -G "Ninja" \
   -DCMAKE_BUILD_TYPE=Release        \
   -DCMAKE_INSTALL_PREFIX=./build  \
   -B./build
