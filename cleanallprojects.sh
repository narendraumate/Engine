#!/bin/bash

case "$OSTYPE" in
	darwin*) ./Tools/MacOS/premake5/premake5 --file=premake5.lua --os=macosx clean;rm -rf bin obj;;
	linux*) ./Tools/Linux/premake5/premake5 --file=premake5.lua --os=linux clean;rm -rf bin obj;;
esac
