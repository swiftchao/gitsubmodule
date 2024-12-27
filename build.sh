#########################################################################
# File Name: build.sh
# Author: chaofei
# mail: chaofeibest@163.com
# Created Time: 2024-11-22 17:20:45
#########################################################################
#!/bin/bash
CLEAN="noclean"
[ -n "${1}" ] && CLEAN="${1}"
if [ -n "${CLEAN}" ] && [ "${CLEAN}" = "clean" ]; then
  rm -rf build
fi
mkdir build
cd build
cmake ../
#cmake --build . -D BoostRoot=src/boost
#cmake -D BoostRoot=src/boost --build .
make
cd ../


#gloghello
ldd ./build/src/main/gloghello
./build/src/main/gloghello 100
#ls -al /tmp/logs/

#gtesthello
ldd ./build/src/main/gtesthello
./build/src/main/gtesthello

#rapidjsonhello
ldd ./build/src/main/rapidjsonhello
./build/src/main/rapidjsonhello

#boosthello
ldd ./build/src/main/boosthello
./build/src/main/boosthello
