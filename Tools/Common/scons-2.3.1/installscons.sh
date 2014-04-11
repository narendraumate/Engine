#!/bin/bash

case "$OSTYPE" in
	darwin*) python setup.py install --prefix=../../MacOS/scons-2.3.1;;
	linux*) python setup.py install --prefix=../../Linux/scons-2.3.1;;
esac
