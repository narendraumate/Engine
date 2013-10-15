#!/bin/bash

case "$OSTYPE" in
	darwin*) ./Tools/MacOS/premake4 --file=premake4.lua --os=macosx clean;;
	linux*)  ./Tools/Linux/premake4 --file=premake4.lua --os=linux clean;;
esac
