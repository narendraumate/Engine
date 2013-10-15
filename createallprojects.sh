#!/bin/bash

case "$OSTYPE" in
	darwin*)	./Tools/MacOS/premake4 --file=premake4.lua --os=macosx --platform=universal xcode4;;
	linux*)		./Tools/Linux/premake4 --file=premake4.lua --os=linux gmake;;
esac
