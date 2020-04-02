#!/bin/bash
function check_for_environment_variables {
  if [[ -z "${KOTITONTTU_SRC}" ]]; then
    echo "Please define environment variable \$KOTITONTTU_SRC"
    exit 1
  fi
}

function test_if_works() {
    echo "test test"
}

function install_magnum_package() {
  version=$1
  package=$2
  cmake_options=$3
  if [ "$#" -ne 3 ]; then
    echo "Illegal number of arguments"
  fi
  install_path=${KOTITONTTU_SRC}/ext-libs/
  tmp_path=${KOTITONTTU_SRC}/tmp
  if [[ ! -e $tmp_path ]]; then
    mkdir $tmp_path
  fi
  cd $tmp_path || exit
  filename=v$version.tar.gz
  wget https://github.com/mosra/$2/archive/$filename
  tar -xvf $filename
  mv $filename $package-$filename # Rename file as other magnum files are otherwise identical names
  cd $package-$version || exit
  mkdir build
  cd build || exit
  cmake .. $cmake_options -DCMAKE_INSTALL_PREFIX=$install_path -DCMAKE_PREFIX_PATH=$install_path
  make -j4
  make install
}