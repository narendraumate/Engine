#!/bin/bash
find . -type d -name *.xcodeproj -exec rm -rf {} \;
find . -type d -name *.xcworkspace -exec rm -rf {} \;
find . -type d -name build -exec rm -rf {} \;
find . -type d -name obj -exec rm -rf {} \;
