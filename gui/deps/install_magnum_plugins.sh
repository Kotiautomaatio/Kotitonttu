#!/bin/bash

set -e

if [[ -z "${KOTITONTTU_SRC}" ]]; then
    echo "Please define environment variable \$KOTITONTTU_SRC"
    exit 1
fi

version="2018.10"
install_path=${KOTITONTTU_SRC}/ext-libs/
current_path=$(dirname "$(readlink -f "$0")")
if [[ ! -e tmp ]]; then
  mkdir tmp
fi
cd tmp
filename=v$version.tar.gz
if [[ -e "$filename" ]]; then
  rm "$filename"
fi
wget https://github.com/mosra/magnum-plugins/archive/$filename
tar -xvf $filename
cd magnum-plugins-$version
if [[ ! -e build ]]; then
  mkdir build
fi
cd build
cmake .. \
      -DBUILD_STATIC=YES\
      -DCMAKE_INSTALL_PREFIX="$install_path"\
      -DCMAKE_PREFIX_PATH="$install_path"\
      -DWITH_FREETYPEFONT=ON\
      -DBUILD_PLUGINS_STATIC=ON

make -j4
make install
cd "$current_path"
rm -fr tmp
