#!/bin/bash

case "$OSTYPE" in
	darwin*) ./Tools/MacOS/scons-deploy/bin/scons "$@";;
	linux*) ./Tools/Linux/scons-deploy/bin/scons "$@";;
esac
