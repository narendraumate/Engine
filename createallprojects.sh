#!/bin/bash

case "$OSTYPE" in
	darwin*) ./Tools/MacOS/premake5/premake5 --file=premake5.lua --os=macosx xcode4;;
	linux*) ./Tools/Linux/premake5/premake5 --file=premake5.lua --os=linux gmake;;
esac
