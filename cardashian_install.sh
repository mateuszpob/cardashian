#!/bin/bash

# RPI device ci/cd script

# Compile Emuserail
cd /home/pi/cardashian/emuserialpc
mkdir -p build
make

# Create log directory
mkdir /home/pi/cardashian/logs