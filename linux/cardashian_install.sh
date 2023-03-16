#!/bin/bash

# RPI device ci/cd script

# Compile Emuserail
cd /home/pi/cardashian/emuserialpc
mkdir -p build
make

# Create log directory
mkdir /home/pi/cardashian/logs

cp /home/pi/cardashian/scripts/cardashian_start.sh /usr/bin
chmod 777 /usr/bin/cardashian_start.sh

cp /home/pi/cardashian/scripts/cardashian_stop.sh /usr/bin
chmod 777 /usr/bin/cardashian_stop.sh

cp /home/pi/cardashian/scripts/cardashian_update.sh /usr/bin
chmod 777 /usr/bin/cardashian_update.sh

cp /home/pi/cardashian/scripts/run_emuserial.sh /usr/bin
chmod 777 /usr/bin/run_emuserial.sh