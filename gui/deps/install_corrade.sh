#!/bin/bash
version="2018.10"
install_path=$(readlink -f ../ext-libs/)
mkdir tmp
cd tmp
filename=v$version.tar.gz
wget https://github.com/mosra/corrade/archive/$filename
tar -xvf $filename
cd corrade-$version
mkdir build
cd build
cmake .. -DBUILD_STATIC=YES -DCMAKE_INSTALL_PREFIX=$install_path
make -j4
make install
