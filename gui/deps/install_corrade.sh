#!/bin/bash

set -e

if [[ -z "${KOTITONTTU_SRC}" ]]; then
    echo "Please define environment variable \$KOTITONTTU_SRC"
    exit 1
fi

version="2018.10"
install_path=${KOTITONTTU_SRC}/ext-libs/
if [[ ! -e tmp ]]; then
  mkdir tmp
fi
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
