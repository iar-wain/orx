#!/bin/bash

pushd ~/src/orx/code/build/mac/gmake
make && make config=release64
result=$?
popd
exit $result
