#!/bin/bash

# RPI device ci/cd script

# Compile Emuserail
cd /home/pi/cardashian/emuserialpc
mkdir -p build
make

# Create log directory
mkdir /home/pi/cardashian/logs

cp /home/pi/cardashian/cardashian_start.sh /usr/bin
chmod 777 /home/pi/cardashian/cardashian_start.sh

cp /home/pi/cardashian/cardashian_stop.sh /usr/bin
chmod 777 /home/pi/cardashian/cardashian_stop.sh