#!/bin/bash

# travis_build.sh
#
# This file is part of the NEST example module.
#
# Copyright (C) 2004 The NEST Initiative
#
# NEST is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# NEST is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with NEST.  If not, see <http://www.gnu.org/licenses/>.


# This shell script is part of the NEST example module Travis CI build
# and test environment. It is invoked by the top-level Travis script
# '.travis.yml'.
#

# Exit shell if any subcommand or pipline returns a non-zero status.
set -e

# We need to do this, because  update-alternatives is not available on MacOS
# if [[ $OSTYPE = darwin* ]]; then
#   export CC=$(ls /usr/local/bin/gcc-* | grep '^/usr/local/bin/gcc-\d$')
#   export CXX=$(ls /usr/local/bin/g++-* | grep '^/usr/local/bin/g++-\d$')
# fi
if [ "$xNEST_BUILD_COMPILER" = "CLANG" ]; then
    export CC=clang-11
    export CXX=clang++-11
fi

if [ "$(uname -s)" = 'Linux' ]; then
    CONFIGURE_MPI="-Dwith-mpi=ON"
    CONFIGURE_OPENMP="-Dwith-openmp=ON"
else
    CONFIGURE_MPI="-Dwith-mpi=OFF"
    CONFIGURE_OPENMP="-Dwith-openmp=OFF"
fi

SOURCEDIR=$PWD
echo "SOURCEDIR = $SOURCEDIR"
cd ..

# Install current NEST version.
git clone https://github.com/nest/nest-simulator.git
cd nest-simulator

PYTHON_INCLUDE_DIR=`python3 -c "import sysconfig; print(sysconfig.get_path('include'))"`
PYLIB_BASE=lib`basename $PYTHON_INCLUDE_DIR`
PYLIB_DIR=$(dirname `sed 's/include/lib/' <<< $PYTHON_INCLUDE_DIR`)
PYTHON_LIBRARY=`find $PYLIB_DIR \( -name $PYLIB_BASE.so -o -name $PYLIB_BASE.dylib \) -print -quit`
echo "--> Detected PYTHON_LIBRARY=$PYTHON_LIBRARY"
echo "--> Detected PYTHON_INCLUDE_DIR=$PYTHON_INCLUDE_DIR"

# Explicitly allow MPI oversubscription. This is required by Open MPI versions > 3.0.
# Not having this in place leads to a "not enough slots available" error.
NEST_RESULT=result
if [ "$(uname -s)" = 'Linux' ]; then
    NEST_RESULT=$(readlink -f $NEST_RESULT)
else
    NEST_RESULT=$(greadlink -f $NEST_RESULT)
fi
mkdir "$NEST_RESULT"
echo "NEST_RESULT = $NEST_RESULT"
mkdir build && cd build
cmake \
    -Dwith-optimize=ON -Dwith-warning=ON \
    $CONFIGURE_MPI \
    $CONFIGURE_OPENMP \
    -DPYTHON_LIBRARY=$PYTHON_LIBRARY \
    -DPYTHON_INCLUDE_DIR=$PYTHON_INCLUDE_DIR \
    -DCMAKE_INSTALL_PREFIX=$NEST_RESULT\
    ..

VERBOSE=1 make -j 2
make install

cd $SOURCEDIR
mkdir build && cd build
cmake \
    -Dwith-optimize=ON -Dwith-warning=ON \
    -Dwith-nest=$NEST_RESULT/bin/nest-config \
    $CONFIGURE_MPI \
    $CONFIGURE_OPENMP \
    -DPYTHON_LIBRARY=$PYTHON_LIBRARY \
    -DPYTHON_INCLUDE_DIR=$PYTHON_INCLUDE_DIR \
    -DCMAKE_INSTALL_PREFIX=$NEST_RESULT \
    ..

VERBOSE=1 make -j 2
make install

# TODO: replace by proper testsuite!
. $NEST_RESULT/bin/nest_vars.sh
python -c 'import nest; nest.Install("mymodule")'
exit $?
