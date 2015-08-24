#!/bin/bash

case "$OSTYPE" in
	darwin*) ./Tools/MacOS/premake4/premake4 --file=premake4.lua --os=macosx xcode4;;
	linux*) ./Tools/Linux/premake4/premake4 --file=premake4.lua --os=linux gmake;;
esac
