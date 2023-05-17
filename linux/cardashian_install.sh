#!/bin/bash

# Rpi device ci/cd script

# Compile Emuserail
# cd /home/mp/cardashian/emuserialpc
# rm -r -f ./build
# mkdir build
# cd ./build
# cmake ..
# cmake --build .

# Create log directory
cp /home/mp/cardashian/scripts/cardashian_start.sh /usr/bin
chmod 777 /usr/bin/cardashian_start.sh

cp /home/mp/cardashian/scripts/cardashian_stop.sh /usr/bin
chmod 777 /usr/bin/cardashian_stop.sh

cp /home/mp/cardashian/scripts/cardashian_update.sh /usr/bin
chmod 777 /usr/bin/cardashian_update.sh

cp /home/mp/cardashian/scripts/cardashian_run_emuserial.sh /usr/bin
chmod 777 /usr/bin/cardashian_run_emuserial.sh