#!/bin/bash

rm -rf bin
rm -rf obj

case "$OSTYPE" in
	darwin*) ./Tools/MacOS/scons-deploy/bin/scons "$@";;
	linux*) scons "$@";;
esac
