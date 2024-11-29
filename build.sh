#########################################################################
# File Name: build.sh
# Author: chaofei
# mail: chaofeibest@163.com
# Created Time: 2024-11-22 17:20:45
#########################################################################
#!/bin/bash
rm -rf build
mkdir build
cd build
cmake ../
cmake --build .
#./src/cmakehello
#ldd ./src/cmakehello
cd ../

