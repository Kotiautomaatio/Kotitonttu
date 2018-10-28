#!/bin/bash
version="2018.10"
install_path=$(readlink -f ../ext-libs/)
current_path=$(dirname $(readlink -f $0))
mkdir tmp
cd tmp
filename=v$version.tar.gz
wget https://github.com/mosra/magnum/archive/$filename
tar -xvf $filename
cd magnum-$version
mkdir build
cd build
cmake .. \
      -DBUILD_STATIC=YES\
      -DCMAKE_INSTALL_PREFIX=$install_path\
      -DCMAKE_PREFIX_PATH=$install_path\
      -DWITH_SDL2APPLICATION=ON

make -j4
make install
cd $current_path
rm -fr tmp
