#!/bin/bash

case "$OSTYPE" in
	darwin*) python setup.py install --prefix=../../MacOS/scons-deploy;;
	linux*) python setup.py install --prefix=../../Linux/scons-deploy;;
esac
