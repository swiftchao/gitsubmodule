#########################################################################
# File Name: install_deps.sh
# Author: chaofei
# mail: chaofeibest@163.com
# Created Time: 2024-12-12 17:00:52
#########################################################################
#!/bin/bash
#zstd
sudo apt-get install doxygen -y
sudo apt-get install graphviz -y
sudo apt-get install libgtest-dev -y

sudo apt-get remove libgtest-dev doxygen graphviz -y
