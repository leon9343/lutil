#!/usr/bin/env bash

set -e

INSTALL_PREFIX="${1:-/usr/local}"

mkdir -p build
cd build

cmake -DCMAKE_INSTALL_PREFIX="${INSTALL_PREFIX}" ..

make -j4

sudo make install

if command -v ldconfig &> /dev/null
then
  sudo ldconfig
fi

echo "lutil installed to ${INSTALL_PREFIX}"
echo "Include headers in ${INSTALL_PREFIX}/include"
echo "Library in ${INSTALL_PREFIX}/lib (or lib64 depending on your distro/config)"

