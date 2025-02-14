#!/bin/bash

set -e

echo "Setting up default XCode version"
if [ -z "${GH_YML_MATRIX_COMPILER}" ]
then
  echo "Error: GH_YML_MATRIX_COMPILER variable is not defined"
  exit 1
fi
XCODE_VER="$(echo ${GH_YML_MATRIX_COMPILER} | sed -e 's|_|.|g' -e 's|xcode||')"
if [ ! -d /Applications/Xcode_${XCODE_VER}.app ]
then
  echo "Error: XCode installation directory /Applications/Xcode_${XCODE_VER}.app does not exist"
  exit 2
fi
sudo xcode-select --switch /Applications/Xcode_${XCODE_VER}.app

echo "Installing CMake"

{
  readonly version="3.23.3"
  readonly checksum="45cda7b87cad41ac407fc150e4682b85c3eb45b1977d8e89319cb3a9a6f341f3"
  readonly pkg="cmake-${version}-macos-universal.tar.gz"
  echo "${checksum}  ${pkg}" > cmake.sha256sum

  curl -OL "https://github.com/Kitware/CMake/releases/download/v${version}/${pkg}"
  shasum -a 256 --check cmake.sha256sum

  sudo tar -xvzf ${pkg} --strip-components 1 -C /Applications/
}


echo "Installing Ninja"
brew install ninja

echo "Installing GCC"
brew install gcc
sudo ln -v -s $(which gfortran-11) /usr/local/bin/gfortran

echo "Installing blosc compression"
brew install c-blosc

echo "Installing python3"
brew install python numpy

if [[ "$GH_YML_JOBNAME" =~ -mpi ]]
then
  echo "Installing OpenMPI"
  brew install openmpi mpi4py
fi
