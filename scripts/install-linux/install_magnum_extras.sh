#!/bin/bash

. $(dirname "$(readlink -f "$0")")/../common_functions.sh

check_for_environment_variables()

install_magnum_package("2018.10", "magnum-extras", "-DBUILD_STATIC=YES -DWITH_UI=YES")

